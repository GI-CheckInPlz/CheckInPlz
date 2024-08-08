#pragma once

#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "Physics.h"

#include "Animation.h"
#include "Tween.h"

typedef struct ChandLeftLightProp ChandLeftLightProp;

extern GameObject* CreateChandLeftLight();

void ChandLeftLightStart(GameObject* this);

void ChandLeftLightUpdate(GameObject* this, double dt);

DWORD WINAPI ChandLeftLightDraw(GameObject* this);

void ChandLeftLightOnDestroy(GameObject* this);

