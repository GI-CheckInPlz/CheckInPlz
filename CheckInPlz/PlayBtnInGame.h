#pragma once

#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "Physics.h"
#include "Ingame.h"

#include "audioModule.h"
typedef struct PlayBtnInGameProp PlayBtnInGameProp;

extern GameObject* CreatePlayBtnInGame();

void PlayBtnInGameStart(GameObject* this);

void PlayBtnInGameUpdate(GameObject* this, double dt);

DWORD WINAPI PlayBtnInGameDraw(GameObject* this);

void PlayBtnInGameOnDestroy(GameObject* this);

GameObject* ingame;
