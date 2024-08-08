#pragma once

#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "vmath.h"
#include "Ingame.h"
#include "Floor1.h"
#include "Floor2.h"
#include "Floor3.h"
#include "Floor4.h"
#include "Floor5.h"
#include "Floor6.h"
#include "Background.h"
#include "BlockManager.h"
#include "BlockBook.h"
#include "ReturnToHomeBtn.h"
#include "PlayBtnInGame.h"
#include "ResetBtnInGame.h"
#include "CoinInGame.h"
#include "Exit.h"
#include "Exit2.h"
#include "Exit3.h"
#include "Exit4.h"
#include "StageManager.h"
#include "Overlay.h"
#include "MonsterBook.h"

extern GameObject* CreateInGame();
typedef struct PropIngame
{
	HBITMAP sprite;
	GameObject* BlockManager;
	GameObject* BottomUI;
	GameObject* Overlay;
	GameObject* MonsterBook;
}PropIngame;
void IngameOnDestroy(GameObject* this);
void Play(GameObject* this);
void Reset(GameObject* this);
void GameOver(GameObject* this);
void GameClear(GameObject* this);
Bool CheckClear();
void IngameStart(GameObject* this);
void MonsterOut(GameObject* this);
extern int CurrentCoin;
Bool IsPlaying;

StageData stageData[NUMBER_OF_STAGE];

extern GameObject* ingame;
extern int StageSolutionType[4][2];
HBITMAP MonsterBitmap[KIND_OF_MONSTER];