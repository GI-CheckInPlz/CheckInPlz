#pragma once


#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "Physics.h"
#include "audioModule.h"

typedef struct TitleBackgroundProp TitleBackgroundProp;

extern GameObject* CreateTitleBackground();

void TitleBackgroundStart(GameObject* this);

void TitleBackgroundUpdate(GameObject* this, double dt);

DWORD WINAPI TitleBackgroundDraw(GameObject* this);

void TitleBackgroundOnDestroy(GameObject* this);


