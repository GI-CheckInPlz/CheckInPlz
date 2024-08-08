#pragma once

#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "vmath.h"

extern GameObject* CreateFloor2();

DWORD WINAPI DrawFloor2(GameObject* this);
void UpdateFloor2(GameObject* this, double dt);
void EnterFloor2(GameObject* this, CollisionResponse res);
void ExitFloor2(GameObject* this, CollisionResponse res);
void StayFloor2(GameObject* this, CollisionResponse res);
void StartFloor2(GameObject* this);
void Floor2OnDestroy(GameObject* this);

typedef struct PropFloor2
{
	HBITMAP sprite;
}PropFloor2;