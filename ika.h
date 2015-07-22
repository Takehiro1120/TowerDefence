#ifndef IKA_H_
#define IKA_H_

#include "DxLib.h"
#include "defines.h"
#include "math.h"
#include "curcurate.h"
#include "map.h"
#include "bullets.h"
#include "sound.h"
#include "TDObject.h"
#include "ikura.h"
#include <string>

class Ika :public TDObject{
private:
	Map *aMap;		//降り立つマップ
	Bullets *aBullets;
	Ikura *aIkura;
	Sound *aSound;
	double bectle;
	double speed;
	side underSide;
public:
	Ika(Map *aMap,Bullets *aBullets, Sound *aSound ,Ikura *aIkura) {
		MaxHP = HP = 100;
		aSide = MY;
		aPoint.x = 100;
		aPoint.y = 100;
		size = BLOCKSIZE;
		isJama = true;
		graph = LoadGraph("graph/ika_s.png");
		this->aMap = aMap;
		this->aBullets = aBullets;
		this -> aSound = aSound;
		this->aIkura = aIkura;

		bectle = PI_2;
		speed = 0;
		int w,h;
		GetGraphSize(graph,&w,&h);
		underSide = NONE;
	}
	point_double getPoint(){ return aPoint; }
	double getBectle() { return bectle;}

	/*
	* イカをウィンド座標系(wX,wY)のマップに描画する。
	*/
	void draw(int x,int y){
		DrawRotaGraph(x, y,1, -bectle, graph, true);
	}
	void drawMini(int x, int y,double redu){
		DrawRotaGraph(x, y, redu * 1.5, -bectle, graph, true);
	}



	//スピードを更新する
	void resetSpeed(){
		const double accel = 0.1;
		double maxspeed;
		if(HoldKey(K_A)) maxspeed = 0.4;
		else maxspeed = 1.5;
		if(underSide == MY) maxspeed *= 3;
		else if(underSide == ENEMY) maxspeed *= 0.3;
		
		//前が押されていたら加速する
		if(HoldKey(K_UP)) {
			speed += accel * 1.5;
			if(speed > maxspeed) speed = maxspeed;
		}
		//押されていない時前進状態であれば、0に向かう
		else if(speed > 0){
			speed -= accel;
			if(speed < 0) speed = 0;
		}

		//後ろが押されていたら減速する
		if(HoldKey(K_DOWN)){
			speed -= accel ;
			if(speed < -maxspeed) speed = -maxspeed;
		}
		//押されていないとき後退状態であれば、０に向かう
		else if(speed < 0){
			speed += accel;
			if(speed > 0) speed = 0;
		}
	}

	//向きを更新する。
	void resetBectle(){
		int turn;
		if(HoldKey(K_A)) turn = 100;
		else turn = 70;
		if(HoldKey(K_R)){bectle -= PI / turn;}
		if(HoldKey(K_L)){bectle += PI / turn;}
		if(PushKey(K_Y)){bectle += PI; speed *= -0.5;}	//反転
	}

	void moveIka(){
		//clsDx();
		//printfDx("x:%f\ty:%f\nspeed:%f\nbectle:%f",aPoint.x,aPoint.y,speed,bectle);
		resetSpeed();
		resetBectle();
		point_double nextPoint = aPoint;
		nextPoint.x = aPoint.x + speed * cos(bectle);
		nextPoint.y = aPoint.y - speed * sin(bectle);
		if(HoldKey(K_RIGHT)){
			nextPoint.x = nextPoint.x + 1.0 * cos(bectle-PI_2);
			nextPoint.y = nextPoint.y - 1.0 * sin(bectle-PI_2);
		}
		if(HoldKey(K_LEFT)){
			nextPoint.x = nextPoint.x + 1.0 * cos(bectle+PI_2);
			nextPoint.y = nextPoint.y - 1.0 * sin(bectle+PI_2);
		}
		//壁への衝突を考慮して座標を更新
		if(aMap->getMapData(ConToBlock(nextPoint.x),ConToBlock(aPoint.y)).aArea != A_WALL){
			aPoint.x = nextPoint.x;
		}
		if(aMap->getMapData(ConToBlock(aPoint.x),ConToBlock(nextPoint.y)).aArea != A_WALL){
			aPoint.y = nextPoint.y;
		}
		if(aMap->getMapData(ConToBlock(nextPoint.x),ConToBlock(nextPoint.y)).aArea != A_WALL){
			aPoint = nextPoint;
		}
		underSide = aMap->getMapData(ConToBlock(aPoint.x),ConToBlock(aPoint.y)).aSide;
		int num = aIkura->getFallIkuraNum();
		for(int i=0;i<num;i++){
			if(checkContain(aIkura->getFallIkura(i))) {
				aIkura->handFallIkura(i);
				i--;
				num--;
			}
		}
		
	}

	void shot(){
		double range = BLOCKSIZE * 12;
		double speed = 7;
		double angle = 0.03;
		int paint = 10;
		if(PiriodKey(K_A,6)){
			if(HoldKey(K_B)){ range *= 0.8; speed *= 0.8; paint *= 3;}
			aBullets->setBullet(MY,aPoint,range,bectle + (GetRand(20) -10) * angle ,1.0,speed,10,paint);
			aSound->playSE("shoot");
		}
	}

	void ikaTask(){
		moveIka();
		shot();
	}


};


#endif