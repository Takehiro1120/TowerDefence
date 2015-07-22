#ifndef KEY_H_
#define KEY_H_

#include "defines.h"

void InputKey();
bool PushKey(key aKey);
bool HoldKey(key aKey);
bool PiriodKey(key aKey,int cycle);

#endif