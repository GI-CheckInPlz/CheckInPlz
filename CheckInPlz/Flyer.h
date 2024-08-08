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

extern GameObject* CreateFlyer();

void FlyerDraw(GameObject* this);
void FlyerUpdate(GameObject* this, double dt);
void FlyerEnter(GameObject* this, CollisionResponse res);
void FlyerExit(GameObject* this, CollisionResponse res);
void FlyerStay(GameObject* this, CollisionResponse res);
void FlyerStart(GameObject* this);

typedef struct FlyerProp
{
	vector2 velocity; // ���ӵ�
	vector2 gravity; // �߷�
	float friction; // ������
	vector2 targetPos;
	vector2 jumpForce;
	float speed; // �⺻ �ӵ�
	float rayCastXRange;
	CharacterState characterState;
	Animation* idleAnimation;
	Animation* walkAnimation;
	Animation* jumpAnimation;
	Animation* fallAnimation;
	Bool fallCheck;
}FlyerProp;

void FlyerStateTransition(GameObject* this, void* etc);
void FlyerJump(GameObject* this, RaycastResponse res);