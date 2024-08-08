#pragma once

#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "StageManager.h"

#include "audioModule.h"
typedef struct CoinInGameProp CoinInGameProp;

extern GameObject* CreateCoinInGame();

void CoinInGameStart(GameObject* this);

void CoinInGameUpdate(GameObject* this, double dt);

int CurrentCoin;
DWORD WINAPI CoinInGameDraw(GameObject* this);
void CoinInGameOnDestroy(GameObject* this);