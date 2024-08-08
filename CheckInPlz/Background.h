#pragma once

#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "Ingame.h"
typedef struct PropBackground
{
	HBITMAP sprite;
}PropBackground;


extern GameObject* CreateBackground();

DWORD WINAPI DrawBackground(GameObject* this);
void BackgroundOnDestroy(GameObject* this);