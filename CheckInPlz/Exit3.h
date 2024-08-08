#pragma once

#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "vmath.h"
#include "StageManager.h"
#include "CharacterState.h"
#include "Ingame.h"
extern GameObject* CreateExit3();

void Exit3OnDestroy(GameObject* this);
DWORD WINAPI DrawExit3(GameObject* this);
void UpdateExit3(GameObject* this, double dt);
void EnterExit3(GameObject* this, CollisionResponse res);
void ExitExit3(GameObject* this, CollisionResponse res);
void StayExit3(GameObject* this, CollisionResponse res);
void StartExit3(GameObject* this);
Solution StageSolution[4][2];
Bool PlayerSolution[4][2];
typedef struct PropExit3
{
	HBITMAP sprite;
	vector2 solutionPos[2];
}PropExit3;
