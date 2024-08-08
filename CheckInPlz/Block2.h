#pragma once
#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "vmath.h"

DWORD WINAPI DrawBlock2(GameObject* t);
void StartBlock2(GameObject* t);

typedef struct PropBlock2
{
	HBITMAP hBitmap;
	int size;
}PropBlock2;

extern GameObject* CreateBlock2(HBITMAP hBitmap, int size);
void Block2OnDestroy(GameObject* this);