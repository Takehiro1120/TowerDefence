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
	* �R���X�g���N�^�BID������U���āA�I�u�W�F�N�g�Q�ɉ�����B
	*/
	TDObject(){
		ID = nextID;
		objects[ID] = this;
		nextID++;
	}
	/*
	* �����̍��W���I�u�W�F�N�g�͈͓����ǂ�����Ԃ�
	*/
	bool checkContain(point_double target){
		return CheckContain(target,aPoint.x-size/2,aPoint.y-size/2,aPoint.x+size/2,aPoint.y+size/2);
	}
	/*
	* �I�u�W�F�N�g���m�̓����蔻��
	*/
	bool checkHitObject(TDObject otherObject){
		return checkContain(otherObject.aPoint) || otherObject.checkContain(aPoint);
	}

	/*
	* �I�u�W�F�N�g�S�ĂƂ̓����蔻��
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
	* �I�u�W�F�N�g��`��B�@�K�v�ɂ��I�[�o�[���C�h���ĕύX
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
	* �_���[�W���󂯂�
	*/
	void damage(int aDamage){
		HP -= aDamage;
	}
	/*
	* ���̃I�u�W�F�N�g�Ƃ�����΂���Ƃ��A�I�u�W�F�N�g�Q����폜����B�@�f�X�g���N�^�ł����v���E�E�E�H
	*/
	void erace(){
		objects.erase(ID);
	}
};

#endif