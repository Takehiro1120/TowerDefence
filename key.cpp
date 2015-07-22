/**************************************************
  キー入力関係の関数群
  前提として入力はジョイパットによるものとしている
  キー入力を利用するには、予め繰り返しの初めにInputKey()でキーの状態を取得しておくこと
**************************************************/

#include "DxLib.h"
#include "defines.h"


// 取得したキー
// 現在のキーと一つ前のキー（長押し防止に使用
static int input_key, pre_input_key;
static int keyCount = 0;

// 一つ前の入力をキープして、現在の入力を取得する
void InputKey(){
	pre_input_key = input_key;	// 一つ前の入力をキープ
	input_key = GetJoypadInputState(DX_INPUT_KEY_PAD1);	// ジョイパッドの入力を取得
	keyCount++;
}

/*
*　キーが押されたかどうかを返す
*/
bool PushKey(key aKey){
	if((input_key & aKey) && !(pre_input_key & aKey)) return true;	//前は押されていなかったけど今は押されているなら真
	return false;	//押されていない、もしくは長押し状態なので偽
}
/*
* キーが長押しされているかを返す
*/
bool HoldKey(key aKey){
	if(input_key & aKey)	return true;			//押されているなら真
	return false;	//押されてなかったら負
}

/*
* キーが長押しされているとき、周期で真を返す
*/
bool PiriodKey(key aKey,int cycle){
	if((input_key & aKey) && (keyCount % cycle == 0))	return true;	//押されてて周期がきたら真を返す
	return false;
}