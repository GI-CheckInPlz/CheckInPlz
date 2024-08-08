#pragma once
#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "Physics.h"
#include "GameScenes.h"

#include "audioModule.h"

typedef struct ReturnToHomeBtnProp ReturnToHomeBtnProp;

extern GameObject* CreateReturnToHomeBtn();

void ReturnToHomeBtnStart(GameObject* this);

void ReturnToHomeBtnUpdate(GameObject* this, double dt);

void ReturnToHomeBtnOnDestroy(GameObject* this);

DWORD WINAPI ReturnToHomeBtnDraw(GameObject* this);