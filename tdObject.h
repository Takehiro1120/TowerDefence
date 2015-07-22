#ifndef TDOBJECT_H_
#define TDOBJECT_H_

#include "DxLib.h"
#include "defines.h"
#include "curcurate.h"
#include <map>



class TDObject{
private:
	static std::map<int ,TDObject *> objects;
	static int nextID;
protected:
	int ID;
	int MaxHP;
	int HP;
	side aSide;
	point_double aPoint;
	double size;
	bool isJama;
	int graph;
public:
	/*
	* コンストラクタ。IDを割り振って、オブジェクト群に加える。
	*/
	TDObject(){
		ID = nextID;
		objects[ID] = this;
		nextID++;
	}
	/*
	* 引数の座標がオブジェクト範囲内かどうかを返す
	*/
	bool checkContain(point_double target){
		return CheckContain(target,aPoint.x-size/2,aPoint.y-size/2,aPoint.x+size/2,aPoint.y+size/2);
	}
	/*
	* オブジェクト同士の当たり判定
	*/
	bool checkHitObject(TDObject otherObject){
		return checkContain(otherObject.aPoint) || otherObject.checkContain(aPoint);
	}

	/*
	* オブジェクト全てとの当たり判定
	*/
	bool checlHitAllObject(){
		int num = objects.size();
		for(int i = 0; i < num; i ++){
			TDObject aObject = *objects.at(i);
			if(ID != aObject.ID){
				if(checkHitObject(aObject)) return true;
			}
		}
		return false;
	}


	/*
	* オブジェクトを描画。　必要によりオーバーライドして変更
	*/
	void draw(int wX,int wY){
		DrawGraph(wX,wY,graph,true);
	}

	void drawAll(int wX,int wY){
		int num = objects.size();
		printfDx("\n ",num);
		for(int i = 0; i < num; i ++){
			TDObject aObject = *objects.at(i);
			printfDx("%d\t",aObject.graph);
			aObject.draw(wX,wY);
		}
	}
	/*
	* ダメージを受ける
	*/
	void damage(int aDamage){
		HP -= aDamage;
	}
	/*
	* このオブジェクトとおさらばするとき、オブジェクト群から削除する。　デストラクタでも大丈夫か・・・？
	*/
	void erace(){
		objects.erase(ID);
	}
};

#endif