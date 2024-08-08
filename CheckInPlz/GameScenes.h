#pragma once
#include "Scene.h"

#include "TitleBackground.h"
#include "StartBtn.h"
#include "SelectStageBtn.h"
#include "ExitBtn.h"
#include "ChandLeftLight.h"
#include "ChandRightLight.h"


#include "Debug.h"

#include "InGame.h"


#include "SelectStage.h"
#include "GearIcon.h"
#include "BGMSelect.h"
#include "CutSceneManager.h"


#include "CreditsShow.h"
#include "CreditsText.h"

#define SCENE_NUMBER 4
extern Scene* GameScene[SCENE_NUMBER];

extern void InitScenes();

