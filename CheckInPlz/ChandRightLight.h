#pragma once

#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "Physics.h"

#include "Animation.h"
#include "Tween.h"

typedef struct ChandRightLightProp ChandRightLightProp;

extern GameObject* CreateChandRightLight();

void ChandRightLightStart(GameObject* this);

void ChandRightLightUpdate(GameObject* this, double dt);

DWORD WINAPI ChandRightLightDraw(GameObject* this);

void ChandRightLightOnDestroy(GameObject* this);

