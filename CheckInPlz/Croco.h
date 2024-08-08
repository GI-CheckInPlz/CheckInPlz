#pragma once
#include "GameObject.h"
#include "Win32Api.h"
#include "define.h"
#include "Input.h"
#include "Render.h"
#include "Physics.h"
#include "CharacterState.h"
#include "Animation.h"
#include "resource.h"
#include "Tween.h"

extern GameObject* CreateCroco();

void CrocoDraw(GameObject* this);
void CrocoUpdate(GameObject* this, double dt);
void CrocoEnter(GameObject* this, CollisionResponse res);
void CrocoExit(GameObject* this, CollisionResponse res);
void CrocoStay(GameObject* this, CollisionResponse res);
void CrocoStart(GameObject* this);

typedef struct CrocoProp
{
	vector2 velocity; // 가속도
	vector2 gravity; // 중력
	float friction; // 마찰력
	vector2 targetPos;
	vector2 jumpForce;
	float speed; // 기본 속도
	float rayCastXRange;
	CharacterState characterState;
	Animation* idleAnimation;
	Animation* walkAnimation;
	Animation* jumpAnimation;
	Animation* fallAnimation;
	Bool fallCheck;
}CrocoProp;

void CrocoStateTransition(GameObject* this, void* etc);
void CrocoJump(GameObject* this, RaycastResponse res);