#pragma once
#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "Physics.h"
#include "GameScenes.h"
#include "audioModule.h"




DWORD WINAPI SelectStageBtnDraw(GameObject* this);
void SelectStageBtnUpdate(GameObject* this, double dt);
extern GameObject* CreateSelectStageBtn();
void SelectStateBtnOnDestroy(GameObject* this);