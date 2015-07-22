/**************************************************
  �L�[���͊֌W�̊֐��Q
  �O��Ƃ��ē��͂̓W���C�p�b�g�ɂ����̂Ƃ��Ă���
  �L�[���͂𗘗p����ɂ́A�\�ߌJ��Ԃ��̏��߂�InputKey()�ŃL�[�̏�Ԃ��擾���Ă�������
**************************************************/

#include "DxLib.h"
#include "defines.h"


// �擾�����L�[
// ���݂̃L�[�ƈ�O�̃L�[�i�������h�~�Ɏg�p
static int input_key, pre_input_key;
static int keyCount = 0;

// ��O�̓��͂��L�[�v���āA���݂̓��͂��擾����
void InputKey(){
	pre_input_key = input_key;	// ��O�̓��͂��L�[�v
	input_key = GetJoypadInputState(DX_INPUT_KEY_PAD1);	// �W���C�p�b�h�̓��͂��擾
	keyCount++;
}

/*
*�@�L�[�������ꂽ���ǂ�����Ԃ�
*/
bool PushKey(key aKey){
	if((input_key & aKey) && !(pre_input_key & aKey)) return true;	//�O�͉�����Ă��Ȃ��������Ǎ��͉�����Ă���Ȃ�^
	return false;	//������Ă��Ȃ��A�������͒�������ԂȂ̂ŋU
}
/*
* �L�[������������Ă��邩��Ԃ�
*/
bool HoldKey(key aKey){
	if(input_key & aKey)	return true;			//������Ă���Ȃ�^
	return false;	//������ĂȂ������畉
}

/*
* �L�[������������Ă���Ƃ��A�����Ő^��Ԃ�
*/
bool PiriodKey(key aKey,int cycle){
	if((input_key & aKey) && (keyCount % cycle == 0))	return true;	//������ĂĎ�����������^��Ԃ�
	return false;
}