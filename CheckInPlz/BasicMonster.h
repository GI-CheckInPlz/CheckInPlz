#pragma once
#include "GameObject.h"
#include "Win32Api.h"
#include "define.h"
#include "Input.h"
#include "Render.h"
#include "Physics.h"
#include "CharacterState.h"
#include "resource.h"
#include "Tween.h"
#include "StageManager.h"

#include "audioModule.h"

extern GameObject* CreateBasicMonster();

DWORD WINAPI BasicMonsterDraw(GameObject* this);
void BasicMonsterUpdate(GameObject* this, double dt);
void BasicMonsterEnter(GameObject* this, CollisionResponse res);
void BasicMonsterExit(GameObject* this, CollisionResponse res);
void BasicMonsterStay(GameObject* this, CollisionResponse res);
void BasicMonsterStart(GameObject* this);
void BasicMonsterStateTransition(GameObject* this, void* etc);
void BasicMonsterJump(GameObject* this, RaycastResponse res);
void BasicMonsterStandJump(GameObject* this);
void MonsterCollision(GameObject* this, int xDir, int yDir);
void BasicMonsterOnDestory(GameObject* this);
void BasicMonsterDoubleJump(GameObject* this);

GameObjectList* MonsterList;
Bool IsPlaying;
extern GameObject* ingame;