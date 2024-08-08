#pragma once

#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "vmath.h"
#include "StageManager.h"
extern GameObject* CreateStage1();

void Stage1OnDestroy(GameObject* this);

typedef struct PropStage1
{
	HBITMAP sprite;
}PropStage1;