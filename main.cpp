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
	// ゲームの起動時の設定
	//ChangeWindowMode(FALSE),SetDrawScreen(DX_SCREEN_BACK),DxLib_Init();	// 全画面
	ChangeWindowMode(TRUE),SetDrawScreen(DX_SCREEN_BACK),DxLib_Init();		// テスト用
	SetGraphMode(1280, 720, 32);							// ウィンドウサイズ
	SetDrawScreen(DX_SCREEN_BACK);											// 描画先を裏画面に
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

	DxLib_End(); // DXライブラリ終了処理
	return 0;
} 






 

