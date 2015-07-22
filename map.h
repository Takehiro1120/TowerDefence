#ifndef MAP_H_
#define MAP_H_

#include "DxLib.h"
#include "defines.h"
#include "math.h"
#include "curcurate.h"
#include <string>

//�e�G���A�̏��B�@����ǉ��\��
struct areaData{
	area aArea;
	side aSide;
};

class Map{
private:
	areaData mapData[MAXBLOCK][MAXBLOCK];	//�}�b�v�f�[�^
	int bSize;	//�u���b�N�P�ʂ̃T�C�Y
	double dSize;	//�h�b�g�P�ʂ̃T�C�Y
	point_double viewBasePoint; //�\�����W�n�̌��_
	int aHandle;

public:
	/*
	* �}�b�v�̃R���g���N�^�B�@�Ƃ肠�����K���Ƀ}�b�v�𐶐�����B
	*/
	Map(){
		makeMap(10);
	}

	int getBSize() { return bSize; }
	double getDSize() { return dSize; }
	point_double getViewBasePoint(){ return viewBasePoint; }
	areaData getMapData(int x,int y){ return mapData[x][y]; }
	areaData getMapData(point_double aPoint){return mapData[ConToBlock(aPoint.x)][ConToBlock(aPoint.y)];}
	void paintArea(int x,int y,side aSide){ mapData[x][y].aSide = aSide; } 


	/*
	* ������bSize�i�O���܂ށj�̃}�b�v��������������B
	*/
	void makeMap(int aSize){
		bSize = aSize ;
		dSize = ConToDot(aSize);
		for(int x = 0;x < MAXBLOCK; x++){
			for(int y = 0;y < MAXBLOCK; y++){
				//�O����ǂ�
				if(x==0 || aSize-1 <= x || y == 0 || aSize-1 <= y){
					mapData[x][y].aArea = A_WALL;
				}
				//���̂ق��͂Ƃ肠�������n��
				else mapData[x][y].aArea = A_FLAT;
				mapData[x][y].aSide = NONE;

			}
		}
		makeWall(0);
	}

	void makeWall(int num){
		int maked = 0;
		int rate[5] = {0,70,80,30,100};
		while(maked < num){
			int x = GetRand(bSize-1);
			int y = GetRand(bSize-1);
			if(mapData[x][y].aArea == A_FLAT){
				//�ꕔ�͊��S�����_���Ŕz�u
				if(maked < num/25){
					mapData[x][y].aArea = A_WALL;
					maked++;
				}
				//�c��͎��͂̃}�X�̕ǐ�������ƍ����B
				else{
					int count = 0;
					for(int i=0;i<4;i++){
						int aX = x + urdlX[i];
						int aY = y + urdlY[i];
						point tmp = {aX,aY};
						if(CheckContain(tmp,1,1,bSize-2,bSize-2)){
							if(mapData[aX][aY].aArea == A_WALL){
								count ++;
							}
						}

					}
					if(RandomCheck(rate[count])){
						mapData[x][y].aArea = A_WALL;
						maked++;
					}

				}
			}
		}
	}

	/*
	* �\���̒��S�ƂȂ�}�b�v���W�n�̍��Wtarget�����ɁA�\�����W�n�̌��_�������I�ɐݒ肷�B
	*/
	void setViewBasePoint(point_double target){
		double size = dSize;
		double tmp = MAPWIDTH / 2;
		//���ڍ��W���[�̂ق��ɂ���Ƃ��A���肬��̈ʒu�܂Œ��ڍ��W��߂�
		if(target.x < tmp) target.x = tmp;
		if(target.x > size - tmp) target.x = size - tmp;
		if(target.y < tmp) target.y = tmp;
		if(target.y > size - tmp) target.y = size - tmp;
		//���W������̈ʒu�ցB�@
		target.x -= tmp;
		target.y -= tmp;
		viewBasePoint = target;
		//clsDx();
		//printfDx("basepoint:(%f,%f)\n",viewBasePoint.x,viewBasePoint.y);
	}

	/*
	* �}�b�v���W�n��\�����W�n�ɒ����B
	*/
	point adjustToViewPoint(point_double target){
		point answer = {int(target.x - viewBasePoint.x), int(target.y - viewBasePoint.y)};
		return answer;
	}
	/*
	*�@�u���b�N���W��\�����W�n�ɕϊ�����B
	*/
	point adjustBlockToViewPoint(point target){
		point_double aPoint = {ConToDot(target.x),ConToDot(target.y)};
		return adjustToViewPoint(aPoint);
	}

	/*
	* �E�B���h�E���W�n(wX,wY)�Ƀ}�b�v��`�悷��
	*/
	void drawMap(int wX,int wY){
		static int flatHandle = LoadGraph("graph/flat.png");
		static int myHandle = LoadGraph("graph/flat_my.png");
		static int enemyHandle = LoadGraph("graph/flat_enemy.png");
		static int wallHandle = LoadGraph("graph/wall.png");
		static int waterHandle = LoadGraph("graph/water.png");


		for(int x = 0; x < bSize;x++){
			for(int y = 0; y < bSize;y++){
				int aHandle;
				area aArea = mapData[x][y].aArea;
				side aSide = mapData[x][y].aSide;
				if(aArea == A_FLAT){
						if(aSide == MY)aHandle = myHandle;
						else if(aSide == ENEMY) aHandle = enemyHandle;
						else if(aSide == NONE) aHandle = flatHandle;
				}
				else if(aArea == A_WALL)aHandle = wallHandle; 
				else if(aArea == A_WATER) aHandle = waterHandle;
				else aHandle = -1; 
				//�u���b�N���W��\�����W�n�ɕϊ�
				point aPoint = {x,y};
				aPoint = adjustBlockToViewPoint(aPoint);
				aPoint.x += wX;
				aPoint.y += wY;
				DrawGraph(aPoint.x,aPoint.y,aHandle,true);
			}
		}
	}

	void drawMapMini(int wX, int wY, double redu){
		static int flatHandle = LoadGraph("graph/flat.png");
		static int myHandle = LoadGraph("graph/flat_my.png");
		static int enemyHandle = LoadGraph("graph/flat_enemy.png");
		static int wallHandle = LoadGraph("graph/wall.png");
		static int waterHandle = LoadGraph("graph/water.png");
		for(int x = 0; x < bSize;x++){
			for(int y = 0; y < bSize;y++){
				int aHandle;
				area aArea = mapData[x][y].aArea;
				side aSide = mapData[x][y].aSide;
				if(aArea == A_FLAT){
						if(aSide == MY)aHandle = myHandle;
						else if(aSide == ENEMY) aHandle = enemyHandle;
						else if(aSide == NONE) aHandle = flatHandle;
				}
				else if(aArea == A_WALL)aHandle = wallHandle; 
				else if(aArea == A_WATER) aHandle = waterHandle;
				else aHandle = -1; 
				//�u���b�N���W��\�����W�n�ɕϊ�
				int aX = int(ConToDot(x) * redu) + wX;
				int aY = int(ConToDot(y) * redu) + wY;
				DrawRotaGraph(aX ,aY,redu,0,aHandle,true);
			}
		}
		point start = {int(viewBasePoint.x * redu),int(viewBasePoint.y * redu)};
		point goal = {int((viewBasePoint.x + MAPWIDTH) * redu),int((viewBasePoint.y + MAPWIDTH) * redu)};
		DrawBox(start.x + wX,start.y + wY,goal.x + wX, goal.y + wY,BLUE,false);
		
	}

	//�}�b�v�摜����f�[�^�ǂݍ��݁B�@�g�p��͕ςȉ摜���c��̂ŁB�g�p�^�C�~���O�ɒ���

	void loadFromGraph(std::string name,int size){
		bSize = size ;
		dSize = ConToDot(bSize);
		std::string filename = "graph/" + name + ".png";
		int handle = LoadGraph(filename.c_str());
		DrawGraph(0,0,handle,true);
		int wallColor = GetPixel(0,0);
		int flatColor = GetPixel(1,0);
		int waterColor = GetPixel(2,0);
		int homeColor = GetPixel(3,0);
		int myColor = GetPixel(4,0);
		int enemyColor = GetPixel(5,0);

		for(int x=0;x<size;x++){
			for(int y=0;y<size;y++){
				int aColor = GetPixel(x,y+1);
				//printfDx("%d,",aColor);
				if(aColor == flatColor) {mapData[x][y].aArea = A_FLAT; mapData[x][y].aSide = NONE;}
				else if(aColor == myColor) {mapData[x][y].aArea = A_FLAT; mapData[x][y].aSide = MY;}
				else if(aColor == enemyColor) {mapData[x][y].aArea = A_FLAT; mapData[x][y].aSide = ENEMY;}
				else if(aColor == wallColor) mapData[x][y].aArea = A_WALL;
				else if(aColor == waterColor) mapData[x][y].aArea = A_WATER;
				else if(aColor == homeColor) mapData[x][y].aArea = A_HOME;
				else mapData[x][y].aArea = A_WALL;
				
				
			}
			printfDx("\n");
		}

	}

	bool checkInSite(point_double aPoint){
		return CheckContain(aPoint,viewBasePoint.x,viewBasePoint.y,viewBasePoint.x + MAPWIDTH,viewBasePoint.y + MAPWIDTH);
	}


};


#endif