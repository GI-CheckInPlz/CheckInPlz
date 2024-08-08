#include "Floor5.h"

GameObject* CreateFloor5()
{
	Transform transform = { {1700, 565}, 0, {1,1} };
	PropFloor5* property = (PropFloor5*)malloc(sizeof(PropFloor5));
	GameObject* obj = CreateGameObject();
	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Draw = DrawFloor5;
	obj->Start = StartFloor5;
	obj->Update = UpdateFloor5;
	obj->OnCollisionEnter = EnterFloor5;
	obj->OnCollisionExit = ExitFloor5;
	obj->OnCollisionStay = StayFloor5;
	obj->SetRect(obj, 600, 5);
	obj->SetTag(obj, "block");
	obj->property = property;
	obj->renderOrder = 5;
	obj->collider = true;
	obj->OnDestroy = Floor5OnDestroy;
	return obj;
}

DWORD WINAPI DrawFloor5(GameObject* this)
{
	PropFloor5* prop = this->property;
	return 0;
}

void UpdateFloor5(GameObject* this, double dt)
{

}

void EnterFloor5(GameObject* this, CollisionResponse res)
{

}

void ExitFloor5(GameObject* this, CollisionResponse res)
{

}

void StayFloor5(GameObject* this, CollisionResponse res)
{

}

void StartFloor5(GameObject* this)
{

}

void Floor5OnDestroy(GameObject* this)
{
	free(this->property);
}
