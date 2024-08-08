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

extern GameObject* CreateMonster3();

DWORD WINAPI Monster3Draw(GameObject* this);
void Monster3Update(GameObject* this, double dt);
void Monster3Enter(GameObject* this, CollisionResponse res);
void Monster3Exit(GameObject* this, CollisionResponse res);
void Monster3Stay(GameObject* this, CollisionResponse res);
void Monster3Start(GameObject* this);
void Monster3StateTransition(GameObject* this, void* etc);
void Monster3Jump(GameObject* this, RaycastResponse res);
void Monster3StandJump(GameObject* this);
void Monster3DoubleJump(GameObject* this);
void Monster3Collision(GameObject* this, int xDir, int yDir);
void Monster3OnDestory(GameObject* this);

GameObjectList* MonsterList;
Bool IsPlaying;
extern GameObject* ingame;