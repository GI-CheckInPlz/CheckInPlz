#pragma once
#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "Physics.h"
#include "GameScenes.h"
#include "StageManager.h"
extern GameObject* CreateStageStartBtn();

DWORD WINAPI StageStartBtnDraw(GameObject* this);
void StageStartBtnUpdate(GameObject* this, double dt);
void StageStartBtnOnDestroy(GameObject* this);