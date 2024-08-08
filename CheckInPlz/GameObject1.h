#pragma once

#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "vmath.h"
#include "Physics.h"
#include "GameObject2.h"

extern GameObject* CreateGameObject1();

void Draw1(GameObject* this);
void Update1(GameObject* this, double dt);
void Enter1(GameObject* this, CollisionResponse res);
void Exit1(GameObject* this, CollisionResponse res);
void Stay1(GameObject* this, CollisionResponse res);
void Start1(GameObject* this);

typedef struct Prop1
{
	vector2 velocity; // 가속도
	vector2 gravity; // 중력
	float friction; // 마찰력
	vector2 targetPos;
	float speed; // 기본 속도
	float rayCastXRange;
	float baseDistanceMeAndTarget;
	float prevDistanceMeAndTarget;
}Prop1;