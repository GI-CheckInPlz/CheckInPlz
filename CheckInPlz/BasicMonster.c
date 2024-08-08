#include "BasicMonster.h"
static Animation* idleAnimation;

GameObject* CreateBasicMonster()
{
	Transform transform = { {400.f, 400.f}, 0.f, {0.4f,0.4f} };
	MonsterProp* property = (MonsterProp*)malloc(sizeof(MonsterProp));
	if (property == NULL)
	{
		return NULL;
	}
	property->speed = 150.f;
	property->velocity.x = 0.f;
	property->velocity.y = 0.f;
	property->gravity.x = 0.f;
	property->gravity.y = 20.f;
	property->friction = 0.1f;
	property->targetPos.x = 0.f;
	property->targetPos.y = 0.f;
	property->rayCastXRange = 40.0f;
	property->characterState = Idle;
	property->jumpForce.y = -BLOCK_OFFSET*1.5;
	property->doubleJumpFroce.y = -220.f;
	property->fallCheck = false;
	property->walkAnimation = CreateAnimation();
	property->walkAnimation->PushImage(property->walkAnimation, L"Resources\\m1\\walk1.bmp");
	property->walkAnimation->PushImage(property->walkAnimation, L"Resources\\m1\\walk2.bmp");
	property->walkAnimation->PushImage(property->walkAnimation, L"Resources\\m1\\walk3.bmp");
	property->walkAnimation->PushImage(property->walkAnimation, L"Resources\\m1\\walk2.bmp");
	property->idleAnimation = CreateAnimation();
	property->idleAnimation->PushImage(property->idleAnimation, L"Resources\\m1\\idle1.bmp");
	property->idleAnimation->PushImage(property->idleAnimation, L"Resources\\m1\\idle2.bmp");
	property->jumpAnimation = CreateAnimation();
	property->jumpAnimation->PushImage(property->jumpAnimation, L"Resources\\m1\\jump1.bmp");
	property->jumpAnimation->PushImage(property->jumpAnimation, L"Resources\\m1\\jump2.bmp");
	property->fallAnimation = CreateAnimation();
	property->fallAnimation->PushImage(property->fallAnimation, L"Resources\\m1\\fall1.bmp");
	property->fallAnimation->PushImage(property->fallAnimation, L"Resources\\m1\\fall2.bmp");
	property->collideAnimation = CreateAnimation();
	property->collideAnimation->PushImage(property->collideAnimation, L"Resources\\m1\\collide.bmp");
	property->restAnimation = CreateAnimation();
	property->restAnimation->PushImage(property->restAnimation, L"Resources\\m1\\rest1.bmp");
	property->alpha = 1;
	property->type = 0;
	property->TakeARest = TakeARest;
	GameObject* obj = CreateGameObject();
	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Draw = BasicMonsterDraw;
	obj->Start = BasicMonsterStart;
	obj->Update = BasicMonsterUpdate;
	obj->OnCollisionEnter = BasicMonsterEnter;
	obj->OnCollisionExit = BasicMonsterExit;
	obj->OnCollisionStay = BasicMonsterStay;
	obj->OnDestroy = BasicMonsterOnDestory;
	obj->SetRect(obj, 160, 160);
	obj->SetTag(obj, "Monster");
	obj->collider = true;
	obj->rigidbody = true;
	obj->property = property;
	obj->renderOrder = MONSTER_ORDER;

	return obj;
}

DWORD WINAPI BasicMonsterDraw(GameObject* this)
{
	MonsterProp* p = this->property;
	if (p->characterState == Walk || p->characterState == Arrive)
		p->walkAnimation->Draw(this, p->walkAnimation, 1);
	else if (p->characterState == Idle || p->characterState == Pause)
		p->idleAnimation->Draw(this, p->idleAnimation, 1);
	else if (p->characterState == Jump)
		p->jumpAnimation->Draw(this, p->jumpAnimation, 1);
	else if (p->characterState == Fall)
		p->fallAnimation->Draw(this, p->fallAnimation, 1);
	else if (p->characterState == Collision)
		p->collideAnimation->Draw(this, p->collideAnimation, p->alpha);
	else if (p->characterState == Rest)
		p->restAnimation->Draw(this, p->restAnimation, 1);
#if DEBUG
	DrawDebugRectangle(this);
#endif

	return 0;
}

void BasicMonsterUpdate(GameObject* this, double dt)
{
	MonsterProp* prop = this->property;

	char* tag[] = { "block", "block1", "block2", "block3"};
	char* doubleJumpTag[] = { "block3" };
	if (prop->characterState == Idle)
	{
		vector2 from = { this->transform.position.x - BLOCK_OFFSET / 2 , this->transform.position.y - BLOCK_OFFSET };
		vector2 to = { this->transform.position.x + BLOCK_OFFSET, this->transform.position.y - BLOCK_OFFSET };
		RaycastResponse resBlock = physics.Raycast(from, to, tag, 4); //�밢 �����ɽ�Ʈ
		if (!resBlock.hit)
		{
			prop->characterState = Walk;
		}
	}
	else if (prop->characterState == Walk)
	{

		vector2 from3 = { this->transform.position.x,this->transform.position.y };
		vector2 to3 = { this->transform.position.x,this->transform.position.y + BLOCK_OFFSET / 2 };
		RaycastResponse resFall = physics.Raycast(from3, to3, tag, 4);
		prop->velocity.x = prop->speed;
		if (!resFall.hit && !prop->fallCheck)
		{
			prop->fallCheck = true;
			timer.Delay(this, 0.1, false, BasicMonsterStateTransition, Fall);
		}
		else if(!prop->fallCheck)
		{
			// �������� �κ�
			vector2 fromDoubleJump = { this->transform.position.x + 2, this->transform.position.y + BLOCK_OFFSET / 2 };
			vector2 toDoubleJump = { this->transform.position.x + 1, this->transform.position.y + BLOCK_OFFSET / 2 };
			RaycastResponse resDoubleJump = physics.Raycast(fromDoubleJump, toDoubleJump, doubleJumpTag, 1);
			if (resDoubleJump.hit)
			{
				//1ĭ ���� ��Ͽ� �����ִ���
				vector2 checkUpperSrc = { this->transform.position.x + 2, this->transform.position.y - BLOCK_OFFSET };
				vector2 checkUpperDst = { this->transform.position.x + 1, this->transform.position.y - BLOCK_OFFSET };
				RaycastResponse resUpper = physics.Raycast(checkUpperSrc, checkUpperDst, tag, 4);

				//2ĭ ���� ��Ͽ� �����ִ���
				vector2 checkUpper2Src = { this->transform.position.x, this->transform.position.y - (BLOCK_OFFSET * 2 ) };
				vector2 checkUpper2Dst = { this->transform.position.x + 1, this->transform.position.y - (BLOCK_OFFSET * 2 ) };
				RaycastResponse resUpper2 = physics.Raycast(checkUpper2Src, checkUpper2Dst, tag, 4);

				//�밢�� 1ĭ ���� ���� �����ִ���
				vector2 checkDiagonalSrc = { this->transform.position.x + BLOCK_OFFSET, this->transform.position.y - BLOCK_OFFSET };
				vector2 checkDiagonalDst = { this->transform.position.x + BLOCK_OFFSET + 1, this->transform.position.y - BLOCK_OFFSET };
				RaycastResponse resDiagonal = physics.Raycast(checkDiagonalSrc, checkDiagonalDst, tag, 4);

				//�밢�� 2ĭ ���� ��Ͽ� �����ִ���
				vector2 checkDiagonalSrc2 = { this->transform.position.x + BLOCK_OFFSET, this->transform.position.y - BLOCK_OFFSET * 2 };
				vector2 checkDiagonalDst2 = { this->transform.position.x + BLOCK_OFFSET + 1, this->transform.position.y - BLOCK_OFFSET * 2 };
				RaycastResponse resDiagonal2 = physics.Raycast(checkDiagonalSrc2, checkDiagonalDst2, tag, 4);

				//2ĭ ���� ����� ������ ���ڸ� ����
				if (resUpper2.hit && !resDiagonal.hit && !resUpper.hit)
				{
					prop->characterState = Idle;
					BasicMonsterStandJump(this);
				}
				
				//2ĭ ���� ����� ���� �밢�� 2ĭ ���� ���� ������
				else if (!resUpper2.hit && resDiagonal2.hit && !resUpper.hit)
				{
					prop->characterState = Idle;
					BasicMonsterStandJump(this);
				}
				//2ĭ ���� ����� ���� �밢�� 2ĭ ������ ���� ������
				else if (!resUpper2.hit && !resDiagonal2.hit && !resUpper.hit)
				{
					prop->characterState = Idle;
					BasicMonsterDoubleJump(this);
				}

				// ���� ��� ������ �����
				int divideX = (int)(resDoubleJump.position.x - 500) / BLOCK_OFFSET;
				int divideY = (int)(resDoubleJump.position.y - 160) / BLOCK_OFFSET;

				// ĳ���� ���� �ٷ� �� ������ ������� �ʰ� �ɾ�� ��
				if (Board[divideY][divideX].block != NULL && !resUpper.hit)
				{
					Destroy(Board[divideY][divideX].block);
					Board[divideY][divideX].block = NULL;
					Board[divideY][divideX].type = Empty;
				}
			}
			//

			vector2 from1 = { this->transform.position.x + BLOCK_OFFSET / 2,this->transform.position.y };
			vector2 to1 = { this->transform.position.x + BLOCK_OFFSET / 2 + 1,this->transform.position.y };
			RaycastResponse resJump = physics.Raycast(from1, to1, tag, 4); //���� ����ĳ��Ʈ

			if (resJump.hit)
			{
				vector2 from2 = { this->transform.position.x - BLOCK_OFFSET / 2 , this->transform.position.y - BLOCK_OFFSET };
				vector2 to2 = { this->transform.position.x + BLOCK_OFFSET, this->transform.position.y - BLOCK_OFFSET };
				RaycastResponse resBlock = physics.Raycast(from2, to2, tag, 4); //�밢 �����ɽ�Ʈ
				if (!resBlock.hit)
				{
					prop->characterState = Idle;
					BasicMonsterJump(this, resJump);
				}
				else
				{
					prop->characterState = Idle;
				}
			}
		}
		
		
	}
	else if (prop->characterState == Jump)
	{

	}
	else if (prop->characterState == Fall)
	{
		prop->fallCheck = false;
		prop->friction = 0.1f; // �̼� ���� ��� ��� ������ �� ���� �ӵ��� �����ϱ� ����
	}

	//every time
	if (prop->characterState != Rest)
	{
		prop->velocity.y += prop->gravity.y;
		prop->velocity.x += prop->gravity.x;
	}
	prop->velocity.x = prop->velocity.x - prop->velocity.x * prop->friction;
	prop->velocity.y = prop->velocity.y - prop->velocity.y * prop->friction;
	this->transform.position.y += (float)(prop->velocity.y * dt);
	this->transform.position.x += (float)(prop->velocity.x * dt);
}

void BasicMonsterEnter(GameObject* this, CollisionResponse res)
{
	MonsterProp* myProp = this->property;
	MonsterProp* yourProp = res.other->property;

	if (myProp->characterState == Idle)
	{ // ���� �����ִµ�
		if (CompareTag(res.other->tag, "Monster"))
		{
			if (yourProp->characterState == Walk)
			{ // �ڿ��� �ɾ ���� ġ��
				if (this->transform.position.x > res.other->transform.position.x)
				{
					MonsterCollision(this, 1, 0);
					MonsterCollision(res.other, -1, 0);
				}
			}
			else if (yourProp->characterState == Fall || yourProp->characterState == Jump)
			{ // ���� �߿� ���� ġ�� �Ǵ� ���� �߿� ���� ġ��

				MonsterCollision(res.other, -1, -1);

				if (this->transform.position.x > res.other->transform.position.x)
				{
					MonsterCollision(this, 1, 0);
				}
				else
				{
					MonsterCollision(this, -1, 0);
				}
			}
		}
	}
	else if (myProp->characterState == Fall)
	{ // ���� �������ε�
		if (CompareTag(res.other->tag, "Monster")) 
		{ // ���Ͷ� �浹�߰�
			if (yourProp->characterState == Idle || yourProp->characterState == Walk)
			{
				MonsterCollision(this, -1, -1);

				if (this->transform.position.x > res.other->transform.position.x)
				{
					MonsterCollision(res.other, -1, 0);
				}
				else
				{
					MonsterCollision(res.other, 1, 0);
				}
			}
			else if (yourProp->characterState == Jump)
			{
				MonsterCollision(this, -1, -1);
				MonsterCollision(res.other, -1, 1);
			}
		}

	}
	else if (myProp->characterState == Walk)
	{ // ���� �Ȱ� �ִµ�
		if (CompareTag(res.other->tag, "Monster"))
		{
			if (yourProp->characterState == Idle || yourProp->characterState == Walk)
			{ // �� ģ���� �����ְų� �ȴ� ���̰�
				if (this->transform.position.x < res.other->transform.position.x)
				{ // ���� �� ģ���� ġ��
					MonsterCollision(this, -1, 0);
					MonsterCollision(res.other, 1, 0);
				}
			}
			else if (yourProp->characterState == Fall)
			{ // ������ ģ���� �����ϴ� ���ε�

				MonsterCollision(res.other, -1, -1);

				if (this->transform.position.x > res.other->transform.position.x)
				{
					MonsterCollision(this, 1, 0);
				}
				else
				{
					MonsterCollision(this, -1, 0);
				}
			}
			else if (yourProp->characterState == Jump)
			{
				//�ٸ� ���� �������϶�
				MonsterCollision(this, 1, 0);
				MonsterCollision(res.other, -1, 0);
			}
		}
		else if (CompareTag(res.other->tag, "exit"))
		{
				
		}
	}
	else if (myProp->characterState == Jump)
	{ // ���� �������ε�
		if (CompareTag(res.other->tag, "Monster"))
		{ // ���Ͷ� �浹�߰�
			if (yourProp->characterState == Fall)
			{ // ���Ͱ� ���� ���̸�
				MonsterCollision(this, -1, 1);
				MonsterCollision(res.other, -1, -1);
			}
			else if (yourProp->characterState == Idle)
			{
				MonsterCollision(this, -1, -1);
				MonsterCollision(res.other, 1, 0); // ���ִ� ���͸� ���� �����߿� ġ�� ���� ���ʿ��� �����ؼ� ġ�� ��츸 ����
			}
			else if (yourProp->characterState == Jump)
			{
				//�Ѵ� �������϶�
				MonsterCollision(this, -1, 1);
				MonsterCollision(res.other, -1, -1);
			}
			else if (yourProp->characterState == Walk)
			{
				//�ٸ� ���� �ȴ� ���϶�
				MonsterCollision(this, -1, 0);
				MonsterCollision(res.other, 1, 0);
			}

		}
	}
}

void BasicMonsterExit(GameObject* this, CollisionResponse res)
{

}

void BasicMonsterStay(GameObject* this, CollisionResponse res)
{
	MonsterProp* prop = this->property;

	if (CompareTag(res.other->tag, "block") || CompareTag(res.other->tag, "block1") || CompareTag(res.other->tag, "block2") || CompareTag(res.other->tag, "block3"))
	{
		if (prop->characterState == Idle || prop->characterState == Arrive || prop->characterState == Pause)
		{
			prop->velocity.y = 0;
			this->transform.position.y -= 1;
		}
		else if (prop->characterState == Fall)
		{
			if (res.other->transform.position.y > this->transform.position.y)
			{
				prop->velocity.y = 0;
				this->transform.position.y -= 1;
				prop->characterState = Walk;
			}
		}
		else if (prop->characterState == Walk)
		{
			if (CompareTag(res.other->tag, "block2"))
			{
				prop->friction = 0.7f;
			}

			prop->velocity.y = 0;
			this->transform.position.y -= 0.1f;
		}


		else if (prop->characterState == Jump)
		{

		}
	}

}

void BasicMonsterStart(GameObject* this)
{
	if (!IsPlaying)
	{
		Destroy(this);
	}
	MonsterProp* p = this->property;
	p->characterState = Walk;
	p->walkAnimation->Play(this, p->walkAnimation, 0.8f, true);
	p->idleAnimation->Play(this, p->idleAnimation, 1, true);
	p->fallAnimation->Play(this, p->fallAnimation, 0.5, true);
	p->collideAnimation->Play(this, p->collideAnimation, 0.5, true);
	p->restAnimation->Play(this, p->restAnimation, 1, true);
	
	//Animate(this, &this->transform.scale.y, PLAYBACK_LOOP_PINGPONG, this->transform.scale.y * 2, EASING_OUTELASTIC, 3, NULL);
	//Animate(this, &this->transform.scale.x, PLAYBACK_LOOP_PINGPONG, this->transform.scale.x * 2, EASING_OUTELASTIC, 3, NULL);
}


void BasicMonsterJump(GameObject* this, RaycastResponse res)
{
	MonsterProp* prop = this->property;
	prop->jumpForce.y = -BLOCK_OFFSET * 1.5;
	Animate(this, &this->transform.position.x, PLAYBACK_ONCE_FORWARD, res.position.x + BLOCK_OFFSET/2, EASING_OUTSINE, 1, NULL);
	Animate(this, &this->transform.position.y, PLAYBACK_ONCE_FORWARD, this->transform.position.y + prop->jumpForce.y, EASING_OUTCIRC, 0.5, NULL);
	timer.Delay(this, 0.5, false, BasicMonsterStateTransition, Fall);
	prop->jumpAnimation->Play(this, prop->jumpAnimation, 0.3f, false);
	prop->characterState = Jump;
}

//���ڸ� ���� Y��ǥ�� ����
void BasicMonsterStandJump(GameObject* this)
{
	MonsterProp* prop = this->property;
	prop->velocity.x = 0;
	prop->jumpForce.y = -BLOCK_OFFSET * 1.1f;
	Animate(this, &this->transform.position.y, PLAYBACK_ONCE_FORWARD, this->transform.position.y + prop->jumpForce.y * 1.2f, EASING_OUTCIRC, 0.5, NULL);
	timer.Delay(this, 0.5, false, BasicMonsterStateTransition, Fall);
	prop->jumpAnimation->Play(this, prop->jumpAnimation, 0.3f, false);
	prop->characterState = Jump;
}

void BasicMonsterDoubleJump(GameObject* this)
{
	MonsterProp* prop = this->property;
	Animate(this, &this->transform.position.x, PLAYBACK_ONCE_FORWARD, this->transform.position.x + 200, EASING_INOUTSINE, 1.2f, NULL);
	Animate(this, &this->transform.position.y, PLAYBACK_ONCE_FORWARD, this->transform.position.y + prop->doubleJumpFroce.y, EASING_OUTSINE, 0.6f, NULL);
	timer.Delay(this, 0.6, false, BasicMonsterStateTransition, Fall);
	prop->jumpAnimation->Play(this, prop->jumpAnimation, 0.7f, false);
	prop->characterState = Jump;
}

void BasicMonsterOnDestory(GameObject* this)
{
	// reset ������ �� faderetry�� 0���� ���õǰ��� ondestroy�� ����Ǹ鼭 GameOver�� ȣ��Ǽ� faderetry �ִϸ��̼��� �����
	//GameOver(ingame);

	MonsterProp* prop = this->property;
	timer.CancelAllInObject(this);
	DestoryAnimation(prop->walkAnimation);
	DestoryAnimation(prop->fallAnimation);
	DestoryAnimation(prop->idleAnimation);
	DestoryAnimation(prop->jumpAnimation);
	DestoryAnimation(prop->collideAnimation);
	DestoryAnimation(prop->restAnimation);
	free(this->property);
	MonsterList->Remove(MonsterList,this);
	
}

void BasicMonsterStateTransition(GameObject* this, void* etc)
{
	MonsterProp* prop = this->property;
	prop->characterState = (CharacterState)etc;
}

void MonsterCollision(GameObject* this, int xDir, int yDir)
{
	// ���Ͱ� �浹���� �� gameover�� ����
	// �� �����߿� reset������ �׳� gameover���� �ʵ��� ����
	MonsterProp* p = this->property;

	p->characterState = Collision;
	GameOver(ingame);
	this->collider = false;
	//this->rigidbody = false;
	AUDIO_PlayAudio("Resources\\Sound\\Collision.wav", 4);
	Animate(this, &this->transform.position.x, PLAYBACK_ONCE_FORWARD, this->transform.position.x + 80 * xDir, EASING_INOUTBOUNCE, 0.3f, NULL);
	Animate(this, &this->transform.position.y, PLAYBACK_ONCE_PINGPONG, this->transform.position.y + 80 * yDir - 20, EASING_INOUTBOUNCE, 0.3f, NULL);
	Animate(this, &p->alpha, PLAYBACK_ONCE_FORWARD, p->alpha - 0.5f, EASING_OUTCUBIC, 0.3f, NULL);

	// �ʹ� ���� destroy�ϰ� �Ǹ� fall-jump �浹���� ���α׷� �ٿ�
	// ����: destroy�� ���ӿ�����Ʈ�� ���Ŀ� jump���� fall�� ��ȯ�ϴ� Ÿ�̸ӿ��� �̹� ������ ������Ʈ�� property�� �����ϱ� ����
	// destroy�� ���� �� õõ�� �ϵ��� ����
	timer.Delay(this, 0.5, false, Destroy, this);
	
}