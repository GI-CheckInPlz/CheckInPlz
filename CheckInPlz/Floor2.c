#include "Floor2.h"

GameObject* CreateFloor2()
{
	Transform transform = { {200, 760}, 0, {1,1} };
	PropFloor2* property = (PropFloor2*)malloc(sizeof(PropFloor2));
	GameObject* obj = CreateGameObject();
	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Draw = DrawFloor2;
	obj->Start = StartFloor2;
	obj->Update = UpdateFloor2;
	obj->OnCollisionEnter = EnterFloor2;
	obj->OnCollisionExit = ExitFloor2;
	obj->OnCollisionStay = StayFloor2;
	obj->SetRect(obj, 600, 5);
	obj->collider = true;
	obj->SetTag(obj, "block");
	obj->property = property;
	obj->renderOrder = 5;
	obj->OnDestroy = Floor2OnDestroy;
	return obj;
}

DWORD WINAPI DrawFloor2(GameObject* this)
{
	PropFloor2* prop = this->property;
	return 0;
}

void UpdateFloor2(GameObject* this, double dt)
{

}

void EnterFloor2(GameObject* this, CollisionResponse res)
{

}

void ExitFloor2(GameObject* this, CollisionResponse res)
{

}

void StayFloor2(GameObject* this, CollisionResponse res)
{

}

void StartFloor2(GameObject* this)
{

}

void Floor2OnDestroy(GameObject* this)
{
	free(this->property);
}