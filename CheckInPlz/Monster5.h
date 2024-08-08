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

extern GameObject* CreateMonster5();

DWORD WINAPI Monster5Draw(GameObject* this);
void Monster5Update(GameObject* this, double dt);
void Monster5Enter(GameObject* this, CollisionResponse res);
void Monster5Exit(GameObject* this, CollisionResponse res);
void Monster5Stay(GameObject* this, CollisionResponse res);
void Monster5Start(GameObject* this);
void Monster5StateTransition(GameObject* this, void* etc);
void Monster5Jump(GameObject* this, RaycastResponse res);
void Monster5StandJump(GameObject* this);
void Monster5DoubleJump(GameObject* this);
void Monster5Collision(GameObject* this, int xDir, int yDir);
void Monster5OnDestory(GameObject* this);

GameObjectList* MonsterList;
Bool IsPlaying;
extern GameObject* ingame;