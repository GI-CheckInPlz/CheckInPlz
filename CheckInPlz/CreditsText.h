#pragma once


#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "Physics.h"
#include "Timer.h"
#include "GameScenes.h"

#include "Animation.h"
#include "Tween.h"

typedef struct CreditsTextProp CreditsTextProp;

extern GameObject* CreateCreditsText();

void CreditsTextStart(GameObject* this);

void CreditsTextUpdate(GameObject* this, double dt);

DWORD WINAPI CreditsTextDraw(GameObject* this);

void CreditsTextOnDestroy(GameObject* this);


