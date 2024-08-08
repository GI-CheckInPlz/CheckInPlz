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

extern GameObject* CreateMonster2();

DWORD WINAPI Monster2Draw(GameObject* this);
void Monster2Update(GameObject* this, double dt);
void Monster2Enter(GameObject* this, CollisionResponse res);
void Monster2Exit(GameObject* this, CollisionResponse res);
void Monster2Stay(GameObject* this, CollisionResponse res);
void Monster2Start(GameObject* this);
void Monster2StateTransition(GameObject* this, void* etc);
void Monster2Jump(GameObject* this, RaycastResponse res);
void Monster2StandJump(GameObject* this);
void Monster2DoubleJump(GameObject* this);
void Monster2Collision(GameObject* this, int xDir, int yDir);
void Monster2OnDestory(GameObject* this);

GameObjectList* MonsterList;
Bool IsPlaying;
extern GameObject* ingame;