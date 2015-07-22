#ifndef BULLET_H_
#define BULLET_H_

#include "DxLib.h"
#include "defines.h"
#include "math.h"
#include "map.h"
#include "ikura.h"
#include <vector>

struct bullet{
	side aSide;
	point_double aPoint;
	double range;
	double bectle;
	double sizeRate;
	double speed;
	int power;
	int paint;
	int graph;
	int afterImage;
};

class Bullets{
private:
	std::vector<bullet> aBullets;
	std::vector<bullet> afterBullets;
	Map *aMap;
	Ikura *aIkura;
	int myBullet;
	int enemyBullet;
public:
	Bullets(Map *aMap ,Ikura *aIkura){
		this->aMap = aMap;
		this->aIkura = aIkura;
		myBullet =		LoadGraph("graph/bullet_my.png");
		enemyBullet =	LoadGraph("graph/bullet_enemy.png");
		if(enemyBullet == -1) printfDx("!");
	}
	
	int getBulletNum() { return aBullets.size(); }
	int getAfterBulletNum() { return afterBullets.size(); }
	bullet getBullet(int num) {return aBullets[num];}
	bullet getAfterBullet(int num) { return afterBullets[num]; }

	void setBullet(side aSide,point_double aPoint,double range,double bectle, double sizeRate, double speed,int power,int paint){
		//printfDx("setBullet:%f,%f,%f,%f,%f\n",aPoint.x,aPoint.y,range,bectle,sizeRate);
		bullet aBullet = {aSide, aPoint, range, bectle, sizeRate, speed, power,paint};
		if(aSide == MY) aBullet.graph = myBullet;
		else aBullet.graph = enemyBullet;
		aBullets.push_back(aBullet);
	}

	//玉が動く。 同時に残像の処理と、射程による玉の消失もここで行う。
	void moveBullets(){
		int num = afterBullets.size();
		for(int i=0;i<num;i++){
			afterBullets[i].afterImage-=1;
			if(afterBullets[i].afterImage <= 0){
				afterBullets.erase(afterBullets.begin() + i);
				num--;
				i--;
			}
		}
		num = aBullets.size();
		for(int i=0;i<num;i++){
			//現在位置を残像に追加
			bullet aBullet = aBullets[i];
			aBullet.afterImage = 5;
			afterBullets.push_back(aBullet);
			//値の取り出し
			double speed = aBullets[i].speed;
			double bectle = aBullets[i].bectle;
			double range = aBullets[i].range;
			//射程限界の処理
			bool limitFlag = false;
			if(range < speed) { speed = range; limitFlag = true;}
			//移動
			aBullets[i].aPoint.x += aBullets[i].speed * cos(aBullets[i].bectle);
			aBullets[i].aPoint.y -= aBullets[i].speed * sin(aBullets[i].bectle);
			if(limitFlag) {
				aBullets.erase(aBullets.begin() + i);	//限界の弾はおさらば
				num--;
				i--;
			}
			else aBullets[i].range-=speed;
		}
		checkHitWallAndFlat();
	}
	//壁と平地の当たり判定。　壁にぶつかると消える。　平地に当たると確立で塗る。
	void checkHitWallAndFlat(){
		int num = aBullets.size();
		for(int i=0;i<num;i++){
			point_double aPoint = aBullets[i].aPoint;
			double sizeRate = aBullets[i].sizeRate;
			side bulletSide = aBullets[i].aSide;
			double tmp = 6.0 * sizeRate / 2;
			int blockX = ConToBlock(aPoint.x);
			int blockY = ConToBlock(aPoint.y);
			if( aMap->getMapData(blockX, blockY).aArea == A_WALL){
				aBullets.erase(aBullets.begin() + i);	//ぶつかってたのでおさらば
				num--;
				i--;
				break;
			}
			aIkura->hitIkura( aBullets[i].aPoint);
			if(aMap->getMapData(blockX, blockY).aArea == A_FLAT){
				side aSide = aMap->getMapData(blockX, blockY).aSide;
				if(aSide == NONE && RandomCheck(aBullets[i].paint)) aMap->paintArea(blockX,blockY,bulletSide);
				else if(aSide != bulletSide && RandomCheck(aBullets[i].paint * 3 / 4)) aMap->paintArea(blockX,blockY,bulletSide);
				else  if(aSide == bulletSide && RandomCheck(aBullets[i].paint / 4)) aMap->paintArea(blockX -1 + GetRand(2),blockY -1 + GetRand(2),bulletSide);
			}

		}
	}

	void drawBullet(int x,int y,bullet aBullet){
		DrawRotaGraph(x, y, aBullet.sizeRate, -aBullet.bectle, aBullet.graph,true);
	}
	void drawAfterBullet(int x,int y,bullet aBullet){
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , aBullet.afterImage * 10 ) ;
		drawBullet(x,y,aBullet);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	}


};

#endif