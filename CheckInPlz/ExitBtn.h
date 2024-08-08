#pragma once
#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "Physics.h"
#include "GameScenes.h"
#include "audioModule.h"


DWORD WINAPI ExitBtnDraw(GameObject* this);
void ExitBtnUpdate(GameObject* this, double dt);
extern GameObject* CreateExitBtn();
void ExitBtnOnDestroy(GameObject* this);