#pragma once
#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "vmath.h"
#include "Tween.h"

DWORD WINAPI DrawBlock1(GameObject* t);
void UpdateBlock1(GameObject* t, double dt);
void EnterBlock1(GameObject* t, CollisionResponse res);
void ExitBlock1(GameObject* t, CollisionResponse res);
void StayBlock1(GameObject* t, CollisionResponse res);
void StartBlock1(GameObject* t);

typedef struct PropBlock1
{
	HBITMAP hBitmap;
	int size;
}PropBlock1;

extern GameObject* CreateBlock1(HBITMAP hBitmap, int size);
void Block1OnDestroy(GameObject* this);