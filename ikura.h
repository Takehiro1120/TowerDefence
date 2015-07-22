#ifndef IKURA_H_
#define IKURA_H_

#include "DxLib.h"
#include "defines.h"
#include "map.h"
#include "math.h"
#include <vector>
class Ikura{
private:
	Map *aMap;
	int handle;
	std::vector<point_double> fallIkuras;
	int totalIkura;
public:
	Ikura(Map *aMap){
		handle = LoadGraph("graph/ikura.png");
		this->aMap = aMap;
		totalIkura = 1000;
	}

	void setTotalIkura(int num) {totalIkura = num;}
	void addTotalIkura(int num) {totalIkura += num;}
	int getFallIkuraNum() {return fallIkuras.size();}
	point_double  getFallIkura(int num){return fallIkuras[num];}

	void fallIkura(int num){
		for(int i=0;i<num;i++){
			point_double aPoint = {GetRand(int(aMap->getDSize()) - 1 ) , GetRand(int(aMap->getDSize()) - 1) };
			area aArea = aMap->getMapData(aPoint).aArea;
			if(aArea == A_FLAT || aArea == A_WATER){
				fallIkuras.push_back(aPoint);
			}
		}
	}
	void drawFallIkura(int x,int y){
		
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , 30 ) ;
		DrawOval(x+6,y+4,8,5,BLACK,true);
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;
		DrawRotaGraph(x,y,0.6,0,handle,true,0);

	}

	void hitIkura(point_double aPoint){
		int num = fallIkuras.size();
		for(int i=0;i<num;i++){
			double x = fallIkuras[i].x;
			double y = fallIkuras[i].y;
			if(CheckContain(aPoint,x-10,y-10,x+10,y+10)){
				handFallIkura(i);
				i--;
				num--;
			}
		}
	}

	void handFallIkura(int num){
		fallIkuras.erase(fallIkuras.begin() + num);
		totalIkura++;
	}

	void drawIkuraCounter(int wX,int wY){
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , 50 ) ;
		DrawBox(wX,wY,wX + 140,wY + 32,BLACK,true);
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;
		static int stringHandle = CreateFontToHandle(NULL,30,10,DX_FONTTYPE_ANTIALIASING_EDGE);
		DrawGraph(wX,wY, handle,true);
		DrawFormatStringToHandle(wX + 40 ,wY,BRIGHTORANGE,stringHandle,"%5d",totalIkura);
	}


};

#endif