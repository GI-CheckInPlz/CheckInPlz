
#pragma once

#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "Physics.h"
#include "audioModule.h"
#include "StageManager.h"
#include "GameScenes.h"


typedef struct SelectStageProp SelectStageProp;

extern GameObject* CreateSelectStage();

void SelectStageStart(GameObject* this);

void SelectStageUpdate(GameObject* this, double dt);

DWORD WINAPI SelectStageDraw(GameObject* this);

void SelectStageOnDestroy(GameObject* this);



