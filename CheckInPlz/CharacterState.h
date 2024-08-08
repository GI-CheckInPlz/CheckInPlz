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

// ��ȣ���� ������ BlockManger.h ��Ŭ��� �Ұ�
// ��� ���Ͱ� characterstate.h �����ϰ� �־ �� �κп� extern ����
extern Cell** Board;