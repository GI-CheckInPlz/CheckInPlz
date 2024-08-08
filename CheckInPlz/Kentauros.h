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

extern GameObject* CreateKentauros();

void KentaurosDraw(GameObject* this);
void KentaurosUpdate(GameObject* this, double dt);
void KentaurosEnter(GameObject* this, CollisionResponse res);
void KentaurosExit(GameObject* this, CollisionResponse res);
void KentaurosStay(GameObject* this, CollisionResponse res);
void KentaurosStart(GameObject* this);

typedef struct KentaurosProp
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
}KentaurosProp;

void KentaurosStateTransition(GameObject* this, void* etc);
void KentaurosJump(GameObject* this, RaycastResponse res);