#pragma once

#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "vmath.h"

extern GameObject* CreateFloor6();

DWORD WINAPI DrawFloor6(GameObject* this);
void UpdateFloor6(GameObject* this, double dt);
void EnterFloor6(GameObject* this, CollisionResponse res);
void ExitFloor6(GameObject* this, CollisionResponse res);
void StayFloor6(GameObject* this, CollisionResponse res);
void StartFloor6(GameObject* this);

void Floor6OnDestroy(GameObject* this);
typedef struct PropFloor6
{
	HBITMAP sprite;
}PropFloor6;