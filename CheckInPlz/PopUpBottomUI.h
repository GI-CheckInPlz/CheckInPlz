#pragma once
#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "Physics.h"
#include "Tween.h"
#include "Animation.h"

typedef struct PopUpBottomUIProp PopUpBottomUIProp;

extern GameObject* CreatePopUpBottomUI();

void PopUpBottomUIStart(GameObject* this);

void PopUpBottomUIUpdate(GameObject* this, double dt);


DWORD WINAPI PopUpBottomUIDraw(GameObject* this);



