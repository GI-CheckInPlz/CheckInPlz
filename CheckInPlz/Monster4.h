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

extern GameObject* CreateMonster4();

DWORD WINAPI Monster4Draw(GameObject* this);
void Monster4Update(GameObject* this, double dt);
void Monster4Enter(GameObject* this, CollisionResponse res);
void Monster4Exit(GameObject* this, CollisionResponse res);
void Monster4Stay(GameObject* this, CollisionResponse res);
void Monster4Start(GameObject* this);
void Monster4StateTransition(GameObject* this, void* etc);
void Monster4Jump(GameObject* this, RaycastResponse res);
void Monster4StandJump(GameObject* this);
void Monster4DoubleJump(GameObject* this);
void Monster4Collision(GameObject* this, int xDir, int yDir);
void Monster4OnDestory(GameObject* this);

GameObjectList* MonsterList;
Bool IsPlaying;
extern GameObject* ingame;