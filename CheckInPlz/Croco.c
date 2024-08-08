#include "Croco.h"
static Animation* idleAnimation;

GameObject* CreateCroco()
{
	Transform transform = { {400, 400}, 0, {0.3,0.3} };
	CrocoProp* property = (CrocoProp*)malloc(sizeof(CrocoProp));
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
	property->jumpForce.y = -160.f;
	property->fallCheck = false;
	property->walkAnimation = CreateAnimation();


	property->walkAnimation->PushImage(property->walkAnimation, L"Resources\\Croco\\walk1.bmp");
	property->walkAnimation->PushImage(property->walkAnimation, L"Resources\\Croco\\walk2.bmp");
	property->walkAnimation->PushImage(property->walkAnimation, L"Resources\\Croco\\walk3.bmp");
	property->walkAnimation->PushImage(property->walkAnimation, L"Resources\\Croco\\walk4.bmp");
	property->walkAnimation->PushImage(property->walkAnimation, L"Resources\\Croco\\walk5.bmp");
	property->idleAnimation = CreateAnimation();
	property->idleAnimation->PushImage(property->idleAnimation, L"Resources\\Croco\\idle1.bmp");
	property->idleAnimation->PushImage(property->idleAnimation, L"Resources\\Croco\\idle2.bmp");
	property->jumpAnimation = CreateAnimation();
	property->jumpAnimation->PushImage(property->jumpAnimation, L"Resources\\Croco\\jump1.bmp");
	property->jumpAnimation->PushImage(property->jumpAnimation, L"Resources\\Croco\\jump2.bmp");
	property->fallAnimation = CreateAnimation();
	property->fallAnimation->PushImage(property->fallAnimation, L"Resources\\Croco\\fall1.bmp");
	property->fallAnimation->PushImage(property->fallAnimation, L"Resources\\Croco\\fall2.bmp");

	GameObject* obj = CreateGameObject();
	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Draw = CrocoDraw;
	obj->Start = CrocoStart;
	obj->Update = CrocoUpdate;
	obj->OnCollisionEnter = CrocoEnter;
	obj->OnCollisionExit = CrocoExit;
	obj->OnCollisionStay = CrocoStay;
	obj->SetRect(obj, 160, 160);
	obj->SetTag(obj, "Croco");
	obj->property = property;
	obj->renderOrder = 1;
	return obj;
}

void CrocoDraw(GameObject* this)
{
	CrocoProp* p = this->property;
	if (p->characterState == Walk)
		p->walkAnimation->Draw(this, p->walkAnimation, 1);
	else if (p->characterState == Idle)
		p->idleAnimation->Draw(this, p->idleAnimation, 1);
	else if (p->characterState == Jump)
		p->jumpAnimation->Draw(this, p->jumpAnimation, 1);
	else if (p->characterState == Fall)
		p->fallAnimation->Draw(this, p->fallAnimation, 1);
}

void CrocoUpdate(GameObject* this, double dt)
{
	CrocoProp* prop = this->property;
	if (prop->characterState == Idle)
	{
		char* tag[] = { "block" };
		vector2 from = { this->transform.position.x,this->transform.position.y - 80 };
		vector2 to = { this->transform.position.x + prop->rayCastXRange,this->transform.position.y - 80 };
		RaycastResponse res2 = physics.Raycast(from, to, tag, 1);
		if (!res2.hit)
		{
			prop->characterState = Walk;
		}
		vector2 down = { this->transform.position.x,this->transform.position.y + 80 };
		RaycastResponse res = physics.Raycast(this->transform.position, down, tag, 1);
		if (!res.hit)
		{
			prop->characterState = Fall;
		}
	}
	else if (prop->characterState == Walk)
	{
		prop->velocity.x = prop->speed;
		prop->targetPos.x = this->transform.position.x + prop->rayCastXRange;
		prop->targetPos.y = this->transform.position.y;
		char* tag[] = { "block" };
		RaycastResponse res1 = physics.Raycast(this->transform.position, prop->targetPos, tag, 1);

		vector2 from = { this->transform.position.x,this->transform.position.y - 80 };
		vector2 to = { this->transform.position.x + prop->rayCastXRange,this->transform.position.y - 80 };
		RaycastResponse res2 = physics.Raycast(from, to, tag, 1);
		if (res1.hit && !res2.hit)
		{
			prop->characterState = Idle;
			CrocoJump(this, res1);
		}
		else if (res1.hit && res2.hit)
		{
			prop->characterState = Idle;
		}
		prop->targetPos.x = this->transform.position.x;
		prop->targetPos.y = this->transform.position.y + prop->rayCastXRange;
		RaycastResponse res = physics.Raycast(this->transform.position, prop->targetPos, tag, 1);
		if (!res.hit && !prop->fallCheck)
		{
			prop->fallCheck = true;
			timer.Delay(this, 0.2, false, CrocoStateTransition, Fall);
		}
	}
	else if (prop->characterState == Jump)
	{

	}
	else if (prop->characterState == Fall)
	{
		prop->fallCheck = false;
	}

	//every time
	prop->velocity.y += prop->gravity.y;
	prop->velocity.x += prop->gravity.x;
	this->transform.position.y += prop->velocity.y * dt;
	this->transform.position.x += prop->velocity.x * dt;
	prop->velocity.x = prop->velocity.x - prop->velocity.x * prop->friction;
	prop->velocity.y = prop->velocity.y - prop->velocity.y * prop->friction;
}

void CrocoEnter(GameObject* this, CollisionResponse res)
{
	CrocoProp* prop = this->property;

	if (prop->characterState == Idle)
	{

	}
	else if (prop->characterState == Fall)
	{

	}
	else if (prop->characterState == Walk)
	{

	}
	else if (prop->characterState == Jump)
	{

	}
}

void CrocoExit(GameObject* this, CollisionResponse res)
{

}

void CrocoStay(GameObject* this, CollisionResponse res)
{
	CrocoProp* prop = this->property;
	if (CompareTag(res.other->tag, "block"))
	{
		if (prop->characterState == Idle)
		{
			prop->velocity.y = 0;
			this->transform.position.y -= 1;
		}
		else if (prop->characterState == Fall)
		{
			prop->velocity.y = 0;
			this->transform.position.y -= 1;
			prop->characterState = Walk;
		}
		else if (prop->characterState == Walk)
		{
			prop->velocity.y = 0;
			this->transform.position.y -= 1;
		}
		else if (prop->characterState == Jump)
		{

		}
	}
}

void CrocoStart(GameObject* this)
{
	CrocoProp* p = this->property;
	p->characterState = Walk;
	p->walkAnimation->Play(this, p->walkAnimation, 0.5, true);
	p->idleAnimation->Play(this, p->idleAnimation, 1, true);
	p->fallAnimation->Play(this, p->fallAnimation, 1, true);

	//Animate(this, &this->transform.scale.y, PLAYBACK_LOOP_PINGPONG, this->transform.scale.y * 2, EASING_OUTELASTIC, 3, NULL);
	//Animate(this, &this->transform.scale.x, PLAYBACK_LOOP_PINGPONG, this->transform.scale.x * 2, EASING_OUTELASTIC, 3, NULL);
}

void CrocoJump(GameObject* this, RaycastResponse res)
{
	CrocoProp* prop = this->property;
	Animate(this, &this->transform.position.x, PLAYBACK_ONCE_FORWARD, res.position.x + 40, EASING_OUTSINE, 1, NULL);
	Animate(this, &this->transform.position.y, PLAYBACK_ONCE_FORWARD, this->transform.position.y + prop->jumpForce.y, EASING_OUTCIRC, 0.5, NULL);
	timer.Delay(this, 1, false, CrocoStateTransition, Fall);
	prop->jumpAnimation->Play(this, prop->jumpAnimation, 0.7, false);
	prop->characterState = Jump;
}

void CrocoStateTransition(GameObject* this, void* etc)
{
	CrocoProp* prop = this->property;
	prop->characterState = (CharacterState)etc;
}
