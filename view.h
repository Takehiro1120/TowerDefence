#ifndef VIEW_H_
#define VIEW_H_

#define MAP_X 200
#define MAP_Y 10
#define MINI_X 910
#define MINI_Y 10
#define MINI_WIDTH 360

#include "DxLib.h"
#include "defines.h"
#include "math.h"
#include "curcurate.h"
#include "map.h"
#include "ika.h"
#include "bullets.h"
#include "ikura.h"

#include <vector>

class View{
private:
	Map *aMap;
	Ika *aIka;
	Bullets *aBullets;
	Ikura *aIkura;
	int flame;
public:
	View(Map *aMap, Ika *aIka, Bullets *aBullets, Ikura *aIkura){
		this->aMap = aMap;
		this->aIka = aIka;
		this->aBullets = aBullets;
		this->aIkura = aIkura;
		flame = LoadGraph("graph/flame.png");
	}
	
	void drawFlame(){
		int aColor = GetColor(190,0,0);
		DrawBox(0,0,1280,10,aColor,true);
		DrawBox(0,0,10,720,aColor,true);
		DrawBox(0,710,1280,720,aColor,true);
		DrawBox(1270,0,1280,720,aColor,true);
		DrawBox(190,0,200,720,aColor,true);
		DrawBox(0,355,200,365,aColor,true);
		DrawBox(900,0,910,720,aColor,true);
		DrawBox(900,370,1280,380,aColor,true);
	}
	void drawMap(){
		DrawBox(MAP_X,MAP_Y,MAP_X+ MAPWIDTH,MAP_Y+MAPWIDTH,BLACK,true);
		aMap->drawMap(MAP_X,MAP_Y);
	}
	void drawIka(){
		point viewPoint = aMap->adjustToViewPoint(aIka->getPoint());
		aIka->drawAll(viewPoint.x + MAP_X, viewPoint.y + MAP_Y);
	}
	void drawMiniMap(){
		DrawBox(MINI_X,MINI_Y,MINI_X+ MINI_WIDTH,MAP_Y+MINI_WIDTH,BLACK,true);
		double redu = MINI_WIDTH / aMap->getDSize();
		DrawFormatString(10,500,BLUE,"%f",redu);
		aMap->drawMapMini(MINI_X,MINI_Y,redu);
		point_double aPoint = aIka->getPoint();
		int x = int(aPoint.x * redu) + MINI_X;
		int y = int(aPoint.y * redu) + MINI_Y;
		aIka->drawMini(x,y,redu);
	}
	void drawStaitus_1(){
		DrawBox(10,10,190,355,LITEGRAY,true);
		DrawString(30,170,"ステータス画面1",BLACK);
	}
	void drawStaitus_2(){
		DrawBox(10,365,190,710,LITEGRAY,true);
	}
	void drawBullets(){
		int num = aBullets->getBulletNum();
		//clsDx();
		for(int i=0;i<num;i++){
			bullet aBullet = aBullets->getBullet(i);
			point viewPoint = aMap->adjustToViewPoint(aBullet.aPoint);
			aBullets->drawBullet(viewPoint.x + MAP_X,viewPoint.y + MAP_Y,aBullet);
		}
		drawAfterBullets();
	}
	void drawAfterBullets(){
		int num = aBullets->getAfterBulletNum();
		for(int i=0;i<num;i++){
			bullet aBullet = aBullets->getAfterBullet(i);
			point viewPoint = aMap->adjustToViewPoint(aBullet.aPoint);
			aBullets->drawAfterBullet(viewPoint.x + MAP_X,viewPoint.y + MAP_Y,aBullet);
		}
	}

	void drawFallIkuras(){
		int num = aIkura->getFallIkuraNum();
		for(int i=0;i<num;i++){
			point_double aPoint = aIkura->getFallIkura(i);
			if(aMap->checkInSite(aPoint)){
				point viewPoint = aMap->adjustToViewPoint(aPoint);
				aIkura->drawFallIkura(viewPoint.x + MAP_X,viewPoint.y + MAP_Y);
			}
		}
	}

	void drawIkuraCounter(){
		aIkura->drawIkuraCounter(MAP_X+30,MAP_Y+10);
	}
	void drawMessageWindow(){
		DrawBox(910,380,1270,710,LITEGRAY,true);
		DrawString(1000,550,"メッセージウィンドウ",BLACK);
	}
	void drawAll(){
		drawMap();
		drawIka();
		drawBullets();
		drawFallIkuras();
		drawMiniMap();
		drawIkuraCounter();
		drawStaitus_1();
		drawStaitus_2();
		drawMessageWindow();
		
		drawFlame();
	}
};

#endif