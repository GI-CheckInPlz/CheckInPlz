#pragma once

#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "vmath.h"

extern GameObject* CreateFloor1();

DWORD WINAPI DrawFloor1(GameObject* this);
void UpdateFloor1(GameObject* this, double dt);
void EnterFloor1(GameObject* this, CollisionResponse res);
void ExitFloor1(GameObject* this, CollisionResponse res);
void StayFloor1(GameObject* this, CollisionResponse res);
void StartFloor1(GameObject* this);
void Floor1OnDestroy(GameObject* this);

typedef struct PropFloor1
{
	HBITMAP sprite;
}PropFloor1;