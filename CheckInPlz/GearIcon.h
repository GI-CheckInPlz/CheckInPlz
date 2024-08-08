#pragma once

#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "Physics.h"
#include "audioModule.h"

typedef struct GearIconProp GearIconProp;

extern GameObject* CreateGearIcon();

void GearIconStart(GameObject* this);

void GearIconUpdate(GameObject* this, double dt);

DWORD WINAPI GearIconDraw(GameObject* this);

void GearIconOnDestroy(GameObject* this);


