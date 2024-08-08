#pragma once

#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "vmath.h"

extern GameObject* CreateFloor3();

DWORD WINAPI DrawFloor3(GameObject* this);
void UpdateFloor3(GameObject* this, double dt);
void EnterFloor3(GameObject* this, CollisionResponse res);
void ExitFloor3(GameObject* this, CollisionResponse res);
void StayFloor3(GameObject* this, CollisionResponse res);
void StartFloor3(GameObject* this);
void Floor3OnDestroy(GameObject* this);

typedef struct PropFloor3
{
	HBITMAP sprite;
}PropFloor3;