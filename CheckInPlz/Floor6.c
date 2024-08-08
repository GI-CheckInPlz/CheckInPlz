#include "Floor6.h"

GameObject* CreateFloor6()
{
	Transform transform = { {1700, 365}, 0, {1,1} };
	PropFloor6* property = (PropFloor6*)malloc(sizeof(PropFloor6));
	GameObject* obj = CreateGameObject();
	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Draw = DrawFloor6;
	obj->Start = StartFloor6;
	obj->Update = UpdateFloor6;
	obj->OnCollisionEnter = EnterFloor6;
	obj->OnCollisionExit = ExitFloor6;
	obj->OnCollisionStay = StayFloor6;
	obj->SetRect(obj, 600, 5);
	obj->SetTag(obj, "block");
	obj->property = property;
	obj->renderOrder = 5;
	obj->collider = true;
	obj->OnDestroy = Floor6OnDestroy;
	return obj;
}

DWORD WINAPI DrawFloor6(GameObject* this)
{
	PropFloor6* prop = this->property;
	return 0;
}

void UpdateFloor6(GameObject* this, double dt)
{

}

void EnterFloor6(GameObject* this, CollisionResponse res)
{

}

void ExitFloor6(GameObject* this, CollisionResponse res)
{

}

void StayFloor6(GameObject* this, CollisionResponse res)
{

}

void StartFloor6(GameObject* this)
{

}

void Floor6OnDestroy(GameObject* this)
{
	free(this->property);
}