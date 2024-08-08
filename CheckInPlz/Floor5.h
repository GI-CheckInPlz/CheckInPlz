#pragma once

#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "vmath.h"

extern GameObject* CreateFloor5();

DWORD WINAPI DrawFloor5(GameObject* this);
void UpdateFloor5(GameObject* this, double dt);
void EnterFloor5(GameObject* this, CollisionResponse res);
void ExitFloor5(GameObject* this, CollisionResponse res);
void StayFloor5(GameObject* this, CollisionResponse res);
void StartFloor5(GameObject* this);
void Floor5OnDestroy(GameObject* this);

typedef struct PropFloor5
{
	HBITMAP sprite;
}PropFloor5;