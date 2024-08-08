#pragma once
#include "Animation.h"

typedef enum CharacterState
{
	Idle,
	Walk,
	Jump,
	Fall,
	Collision,
	Arrive,
	Rest,
	Pause
}CharacterState;

typedef struct MonsterProp
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
	Animation* collideAnimation;
	Animation* restAnimation;
	Bool fallCheck;
	float alpha;
	vector2 doubleJumpFroce;
	callBack TakeARest;
	int type;
}MonsterProp;

void TakeARest(GameObject* this, void* etc);
void EnterAnimation(GameObject* this, void* etc);

// 상호참조 문제로 BlockManger.h 인클루드 불가
// 모든 몬스터가 characterstate.h 참조하고 있어서 이 부분에 extern 선언
extern Cell** Board;