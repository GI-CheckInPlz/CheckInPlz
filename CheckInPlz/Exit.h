#pragma once
#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "vmath.h"
#include "StageManager.h"
#include "CharacterState.h"
#include "Ingame.h"
#include "StageManager.h"
extern GameObject* CreateExit();

DWORD WINAPI DrawExit(GameObject* this);
void UpdateExit(GameObject* this, double dt);
void EnterExit(GameObject* this, CollisionResponse res);
void ExitExit(GameObject* this, CollisionResponse res);
void StayExit(GameObject* this, CollisionResponse res);
void StartExit(GameObject* this);
void ExitOnDestroy(GameObject* this);
Solution StageSolution[4][2];
Bool PlayerSolution[4][2];
typedef struct PropExit
{
	HBITMAP sprite;
	vector2 solutionPos[2];
}PropExit;
