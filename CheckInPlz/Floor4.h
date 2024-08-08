#pragma once

#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "vmath.h"

extern GameObject* CreateFloor4();

DWORD WINAPI DrawFloor4(GameObject* this);
void UpdateFloor4(GameObject* this, double dt);
void EnterFloor4(GameObject* this, CollisionResponse res);
void ExitFloor4(GameObject* this, CollisionResponse res);
void StayFloor4(GameObject* this, CollisionResponse res);
void StartFloor4(GameObject* this);
void Floor4OnDestroy(GameObject* this);

typedef struct PropFloor4
{
	HBITMAP sprite;
}PropFloor4;