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

extern GameObject* CreateStump();

void StumpDraw(GameObject* this);
void StumpUpdate(GameObject* this, double dt);
void StumpEnter(GameObject* this, CollisionResponse res);
void StumpExit(GameObject* this, CollisionResponse res);
void StumpStay(GameObject* this, CollisionResponse res);
void StumpStart(GameObject* this);

typedef struct StumpProp
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
}StumpProp;

void StumpStateTransition(GameObject* this, void* etc);
void StumpJump(GameObject* this, RaycastResponse res);