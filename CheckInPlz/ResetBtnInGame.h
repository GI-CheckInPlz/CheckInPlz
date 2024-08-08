#pragma once

#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "Physics.h"
#include "Ingame.h"

#include "audioModule.h"
typedef struct ResetBtnInGameProp ResetBtnInGameProp;

extern GameObject* CreateResetBtnInGame();

void ResetBtnInGameStart(GameObject* this);
		
void ResetBtnInGameUpdate(GameObject* this, double dt);
		
DWORD WINAPI ResetBtnInGameDraw(GameObject* this);

void ResetBtnInGameOnDestroy(GameObject* this);

GameObject* ingame;