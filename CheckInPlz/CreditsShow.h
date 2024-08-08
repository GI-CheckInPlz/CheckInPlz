#pragma once
#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "Physics.h"
#include "GameScenes.h"
#include "audioModule.h"

#include "Animation.h"
#include "Tween.h"

typedef struct CreditsProp CreditsProp;

extern GameObject* CreateCredits();

void CreditsStart(GameObject* this);

void CreditsUpdate(GameObject* this, double dt);

DWORD WINAPI CreditsDraw(GameObject* this);

void CreditsOnDestroy(GameObject* this);


