#pragma once
#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "Physics.h"
#include "GameScenes.h"
#include "audioModule.h"
#include "StageManager.h"

DWORD WINAPI StartBtnDraw(GameObject* this);
void StartBtnUpdate(GameObject* this, double dt);
extern GameObject* CreateStartBtn();
void StartBtnOnDestroy(GameObject* this);

int currentStage;