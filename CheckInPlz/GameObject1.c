#include "GameObject1.h"
#include "Animation.h"

GameObject* CreateGameObject1()
{
	Transform transform = { {200, 100}, 0, {1,1} };
	Prop1* property = (Prop1*)malloc(sizeof(Prop1));
	property->speed = 300.f;
	property->velocity.x = property->speed;
	property->velocity.y = 0.f;
	property->gravity.x = 0.f;
	property->gravity.y = 10.f;
	property->friction = 0.f;
	property->targetPos.x = 0.f;
	property->targetPos.y = 0.f;
	property->rayCastXRange = 1920.f;
	property->baseDistanceMeAndTarget = 100.f;
	property->prevDistanceMeAndTarget = 0.f;

	GameObject* obj = CreateGameObject();
	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Draw = Draw1;
	obj->Start = Start1;
	obj->Update = Update1;
	obj->OnCollisionEnter = Enter1;
	obj->OnCollisionExit = Exit1;
	obj->OnCollisionStay = Stay1;
	obj->SetRect(obj, 100, 100);
	obj->SetTag(obj, "character1");
	obj->property = property;

	return obj;
}

void Draw1(GameObject* this)
{
	Prop1* p = this->property;
	render.DrawEllipse(this, 100, 100, RGB(0, 0, 0), RGB(0, 0, 0));
}

void Update1(GameObject* this, double dt)
{
	Prop1* prop = this->property;

	prop->velocity.y += prop->gravity.y;
	this->transform.position.y = this->transform.position.y + prop->velocity.y * dt;

	char* tag[] = { "box1" };
	prop->targetPos.x = this->transform.position.x + prop->rayCastXRange;
	prop->targetPos.y = this->transform.position.y;

	RaycastResponse res = physics.Raycast(this->transform.position, prop->targetPos, tag, 1);
	if (res.hit)
	{
		prop->targetPos = res.position;

		float curDistanceMeAndTarget = prop->targetPos.x - this->transform.position.x;

		if (curDistanceMeAndTarget > prop->prevDistanceMeAndTarget) // 정면에서 새로운 블록을 바라보는 경우
		{
			prop->velocity.x = prop->speed;
			prop->prevDistanceMeAndTarget = curDistanceMeAndTarget;
		}
		else if (curDistanceMeAndTarget < prop->baseDistanceMeAndTarget) // 같은 블록을 바라보면서 범위에 들어온 경우
		{
			prop->velocity.x -= prop->friction;
			prop->prevDistanceMeAndTarget = curDistanceMeAndTarget;
		}
		else if (curDistanceMeAndTarget > prop->baseDistanceMeAndTarget) // 같은 블록 바라보면서 범위 들어오지 않은 경우
		{
			prop->velocity.x = prop->speed;
		}
	}
	else
	{
		prop->velocity.x = prop->speed;
	}

	this->transform.position.x = this->transform.position.x + prop->velocity.x * dt;
}

void Enter1(GameObject* this, CollisionResponse res)
{

}

void Exit1(GameObject* this, CollisionResponse res)
{

}

void Stay1(GameObject* this, CollisionResponse res)
{
	if (CompareTag(res.other->tag, "box1"))
	{
		Prop1* myProp = this->property;
		Prop2* targetProp = res.other->property;

		if (this->transform.position.y < res.other->transform.position.y)
		{
			myProp->velocity.y = 0;
			this->transform.position.y -= 1;

			myProp->friction = targetProp->friction;
		}
		else if (this->transform.position.y > res.other->transform.position.y)
		{
			myProp->velocity.y = 0;
			this->transform.position.y += 0.8f;
		}

		char* tag[] = { "box1" };
		myProp->targetPos.x = myProp->targetPos.x + myProp->rayCastXRange;
		myProp->targetPos.y = myProp->targetPos.y;

		RaycastResponse rayRes = physics.Raycast(this->transform.position, myProp->targetPos, tag, 1);
		if (rayRes.hit)
		{
			// 캐릭터 위에 블럭 있고 캐릭터와 정면 타겟과의 거리가 정해진 범위 이내인 경우
			if (this->transform.position.y > res.other->transform.position.y && rayRes.position.x - this->transform.position.x < myProp->baseDistanceMeAndTarget)
			{
				this->transform.position.x -= 1;
			}
		}
	}
}

void Start1(GameObject* this)
{
	Prop1* p = this->property;
}