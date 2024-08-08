#include "Floor4.h"

GameObject* CreateFloor4()
{
	Transform transform = { {1700, 765}, 0, {1,1} };
	PropFloor4* property = (PropFloor4*)malloc(sizeof(PropFloor4));
	GameObject* obj = CreateGameObject();
	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Draw = DrawFloor4;
	obj->Start = StartFloor4;
	obj->Update = UpdateFloor4;
	obj->OnCollisionEnter = EnterFloor4;
	obj->OnCollisionExit = ExitFloor4;
	obj->OnCollisionStay = StayFloor4;
	obj->SetRect(obj, 600, 5);
	obj->SetTag(obj, "block");
	obj->property = property;
	obj->renderOrder = 5;
	obj->collider = true;
	obj->OnDestroy = Floor4OnDestroy;
	return obj;
}

DWORD WINAPI DrawFloor4(GameObject* this)
{
	PropFloor4* prop = this->property;
	return 0;
}

void UpdateFloor4(GameObject* this, double dt)
{

}

void EnterFloor4(GameObject* this, CollisionResponse res)
{

}

void ExitFloor4(GameObject* this, CollisionResponse res)
{

}

void StayFloor4(GameObject* this, CollisionResponse res)
{

}

void StartFloor4(GameObject* this)
{

}

void Floor4OnDestroy(GameObject* this)
{
	free(this->property);
}