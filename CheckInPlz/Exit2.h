#pragma once

#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "vmath.h"
#include "StageManager.h"
#include "CharacterState.h"
#include "Ingame.h"
extern GameObject* CreateExit2();

void Exit2OnDestroy(GameObject* this);
DWORD WINAPI DrawExit2(GameObject* this);
void UpdateExit2(GameObject* this, double dt);
void EnterExit2(GameObject* this, CollisionResponse res);
void ExitExit2(GameObject* this, CollisionResponse res);
void StayExit2(GameObject* this, CollisionResponse res);
void StartExit2(GameObject* this);
Solution StageSolution[4][2];
Bool PlayerSolution[4][2];
typedef struct PropExit2
{
	HBITMAP sprite;
	vector2 solutionPos[2];
}PropExit2;
