#pragma once
#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "vmath.h"
#include "StageManager.h"
#include "GameScenes.h"

extern GameObject* CreateDebug();
void DebugStart(GameObject* this);
void DebugUpdate(GameObject* this, double dt);
DWORD WINAPI DebugDraw(GameObject* this);
void ResetFrameCnt(GameObject* this, int* fc);
typedef struct PropDebug
{
	int frameCnt;
	int current;

	HBITMAP maskBMP;
	HBITMAP printBMP;

	


}PropDebug;
void DebugOnDestroy(GameObject* this);
