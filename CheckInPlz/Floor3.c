#include "Floor3.h"

GameObject* CreateFloor3()
{
	Transform transform = { {200, 560}, 0, {1,1} };
	PropFloor3* property = (PropFloor3*)malloc(sizeof(PropFloor3));
	GameObject* obj = CreateGameObject();
	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Draw = DrawFloor3;
	obj->Start = StartFloor3;
	obj->Update = UpdateFloor3;
	obj->OnCollisionEnter = EnterFloor3;
	obj->OnCollisionExit = ExitFloor3;
	obj->OnCollisionStay = StayFloor3;
	obj->SetRect(obj, 600, 5);
	obj->collider = true;
	obj->SetTag(obj, "block");
	obj->property = property;
	obj->renderOrder = 5;
	obj->OnDestroy = Floor3OnDestroy;
	return obj;
}

DWORD WINAPI DrawFloor3(GameObject* this)
{
	PropFloor3* prop = this->property;
	return 0;
}

void UpdateFloor3(GameObject* this, double dt)
{

}

void EnterFloor3(GameObject* this, CollisionResponse res)
{

}

void ExitFloor3(GameObject* this, CollisionResponse res)
{

}

void StayFloor3(GameObject* this, CollisionResponse res)
{

}

void StartFloor3(GameObject* this)
{

}

void Floor3OnDestroy(GameObject* this)
{
	free(this->property);
}