#pragma once
#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "Physics.h"
#include "GameScenes.h"

extern GameObject* CreateStageStopBtn();

DWORD WINAPI StageStopBtnDraw(GameObject* this);
void StageStopBtnUpdate(GameObject* this, double dt);
void StageStopBtnOnDestroy(GameObject* this);