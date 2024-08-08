#pragma once
#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "vmath.h"

DWORD WINAPI DrawBlock3(GameObject* t);
void StartBlock3(GameObject* t);

typedef struct PropBlock3
{
	HBITMAP hBitmap;
	int size;
}PropBlock3;

extern GameObject* CreateBlock3(HBITMAP hBitmap, int size);
void Block3OnDestroy(GameObject* this);