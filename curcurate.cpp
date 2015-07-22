/****************************
��{�I�Ȍv�Z�֐����܂Ƃ߂����́B
****************************/


#include "DxLib.h"
#include "map.h"
#include "defines.h"

static int count = 0;

void BaseTask(){
	count ++;
}
//rate%�̌��ʂ�Ԃ�
bool RandomCheck(int rate){
	if(GetRand(99) < rate) return true;
	else return false;
}

//�h�b�g�P�ʂ̒l���u���b�N�P�ʂɕϊ�����B�@�[���͐؎̂āB
int ConToBlock(double dotValue){
	return int(dotValue / BLOCKSIZE) ;
}

//�u���b�N�P�ʂ̒l���h�b�g�P�ʂɕϊ�����B ���ݒ�̏ꍇ����̒l���Ԃ����B
double ConToDot(int blockValue,bool isCenter){
	if(isCenter) return blockValue * BLOCKSIZE + (BLOCKSIZE / 2.0);
	else return blockValue * BLOCKSIZE * 1.0;
}

//�w����W���͈͓��Ɋ܂܂�邩�ǂ����`�F�b�N����B�@
bool CheckContain(point aPoint,int x1,int y1,int x2,int y2){
	if(x1 <= aPoint.x && aPoint.x < x2 && y1 <= aPoint.y && aPoint.y < y2) return true;
	else return false;
}
bool CheckContain(point_double aPoint,double x1,double y1,double x2, double y2){
	if(x1 <= aPoint.x && aPoint.x < x2 && y1 <= aPoint.y && aPoint.y < y2) return true;
	else return false;
}

//�w����W���͈͊O�ł���Β��Ɏ��߂����W��Ԃ��B�@�͈͓��ł���΂��̂܂܁B
point AutoContain(point aPoint,int x1,int y1,int x2,int y2){
	if(aPoint.x < x1) aPoint.x = x1;
	if(x2 < aPoint.x) aPoint.x = x2;
	if(aPoint.y < y1) aPoint.y = y1;
	if(y2 < aPoint.y) aPoint.y = y2;
	return aPoint;
}

//�����`�̓����蔻��
bool CheckHit(point_double aPoint,double aSize,point_double bPoint,double bSize){
	point_double aPoints[4] = {{aPoint.x-aSize/2,aPoint.y-aSize/2},{aPoint.x+aSize/2,aPoint.y-aSize/2},{aPoint.x+aSize/2,aPoint.y+aSize/2},{aPoint.x-aSize/2,aPoint.y+aSize/2}};
	point_double bPoints[4] = {{bPoint.x-bSize/2,bPoint.y-bSize/2},{bPoint.x+bSize/2,bPoint.y-bSize/2},{bPoint.x+bSize/2,bPoint.y+bSize/2},{bPoint.x-bSize/2,bPoint.y+bSize/2}};
	for(int i=0;i<4;i++){
		if(CheckContain(aPoints[i],bPoints[0].x,bPoints[0].y,bPoints[2].x,bPoints[2].y)) return true;
	}
	for(int i=0;i<4;i++){
		if(CheckContain(bPoints[i],aPoints[0].x,aPoints[0].y,aPoints[2].x,aPoints[2].y)) return true;
	}
	return false;
}

bool Piriod(int cycle){
	if((count % cycle) == 0) return true;
	return false;
}


