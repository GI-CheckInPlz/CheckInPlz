#pragma once

#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "vmath.h"
#include "StageManager.h"
#include "CharacterState.h"
#include "Ingame.h"

extern GameObject* CreateExit4();

void Exit4OnDestroy(GameObject* this);
DWORD WINAPI DrawExit4(GameObject* this);
void UpdateExit4(GameObject* this, double dt);
void EnterExit4(GameObject* this, CollisionResponse res);
void ExitExit4(GameObject* this, CollisionResponse res);
void StayExit4(GameObject* this, CollisionResponse res);
void StartExit4(GameObject* this);
Solution StageSolution[4][2];
Bool PlayerSolution[4][2];

typedef struct PropExit4
{
	HBITMAP sprite;
	vector2 solutionPos[2];
}PropExit4;
