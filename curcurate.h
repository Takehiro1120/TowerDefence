#ifndef CURCURATE_H_	//二重インクルード防止
#define CURCURATE_H_

#include "defines.h"

void BaseTask();
bool RandomCheck(int rate);
int ConToBlock(double dotValue);
double ConToDot(int blockValue,bool isCenter = false);
bool CheckContain(point aPoint,int x1,int y1,int x2,int y2);
bool CheckContain(point_double aPoint,double x1,double y1,double x2, double y2);
point AutoContain(point aPoint,int x1,int y1,int x2,int y2);
bool CheckHit(point_double aPoint,double aSize,point_double bPoint,double bSize);
bool Piriod(int cycle);
#endif
