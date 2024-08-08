#pragma once

#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "Physics.h"

#include "audioModule.h"


typedef struct BGMSelectProp BGMSelectProp;

extern GameObject* CreateBGMSelect();

void BGMSelectStart(GameObject* this);

void BGMSelectUpdate(GameObject* this, double dt);

DWORD WINAPI BGMSelectDraw(GameObject* this);

void BGMSelectOnDestroy(GameObject* this);


