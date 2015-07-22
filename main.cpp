#include "DxLib.h"
#include "map.h"
#include "defines.h"
#include "key.h"
#include "ika.h"
#include "view.h"
#include "bullets.h"
#include "sound.h"
#include "ikura.h"
#include "tdObject.h"

std::map<int, TDObject *> TDObject::objects;
int TDObject::nextID;

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
	// �Q�[���̋N�����̐ݒ�
	//ChangeWindowMode(FALSE),SetDrawScreen(DX_SCREEN_BACK),DxLib_Init();	// �S���
	ChangeWindowMode(TRUE),SetDrawScreen(DX_SCREEN_BACK),DxLib_Init();		// �e�X�g�p
	SetGraphMode(1280, 720, 32);							// �E�B���h�E�T�C�Y
	SetDrawScreen(DX_SCREEN_BACK);											// �`���𗠉�ʂ�
	Map aMap;
	Sound aSound;
	Ikura aIkura(&aMap);
	Bullets aBullets(&aMap, &aIkura);
	Ika aIka(&aMap,&aBullets,&aSound,&aIkura);
	Ika bIka(&aMap,&aBullets,&aSound,&aIkura);
	View aView(&aMap,&aIka,&aBullets, &aIkura);
	aSound.playBGM("field");
	aMap.loadFromGraph("map2",60);
	aIkura.fallIkura(100);
	while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){

		BaseTask();
		InputKey();
		if(Piriod(600)) aIkura.fallIkura(5);
		aMap.setViewBasePoint(aIka.getPoint());
		aIka.ikaTask();
		aBullets.moveBullets();
		if(PushKey(K_X)) aMap.makeMap(150);
		aView.drawAll();
		
	}

	DxLib_End(); // DX���C�u�����I������
	return 0;
} 






 

