#ifndef DEFINES_H_	//二重インクルード防止
#define DEFINES_H_

#include "DxLib.h"

struct point{
	int x;
	int y;
};
struct point_double{
	double x;
	double y;
};



//表示するブロック数やブロックの数、最大マップサイズなど
const int BLOCKSIZE = 32;
const int MAPWIDTH = 700;
const int MAXBLOCK = 200;
const int MINIMAP_X = 600;
const int MINIMAP_Y = 0;

const double PI =	3.1415926535;
const double PI_2 =	1.5707963267;

const int urdlX[4] = {0,1,0,-1};
const int urdlY[4] = {-1,0,1,0};


// define for colors
const int WHITE = GetColor(255, 255, 255);	// white
const int LITEGRAY = GetColor(190,190,190); //litegray
const int GRAY  = GetColor(125,125,125);	// gray
const int DARKGRAY = GetColor(65,65,65); //darkgray
const int BLACK = GetColor(0, 0, 0);		// bluck
const int RED   = GetColor(255, 0, 0);		// red
const int BLUE  = GetColor(0, 0, 255);		// blue
const int GREEN = GetColor(0,255,0);		// green
const int YELLOW = GetColor(255,255,0);
const int ORANGE = GetColor(255,64,0);
const int BRIGHTORANGE = GetColor(255,128,0);
const int PERPLE = GetColor(255,0,255);


enum area {A_WALL=0, A_FLAT=1, A_TOWER=2,A_HOME=3,A_WATER=4};
enum side {MY,ENEMY,NONE};
enum key {K_UP = PAD_INPUT_UP, K_RIGHT = PAD_INPUT_RIGHT, K_DOWN = PAD_INPUT_DOWN, K_LEFT = PAD_INPUT_LEFT, 
	K_A = PAD_INPUT_1, K_B = PAD_INPUT_2, K_X = PAD_INPUT_3, K_Y = PAD_INPUT_4, 
	K_L = PAD_INPUT_5, K_R = PAD_INPUT_6, K_SELECT = PAD_INPUT_7, K_START = PAD_INPUT_8};


#endif