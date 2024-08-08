#include "Floor1.h"

GameObject* CreateFloor1()
{
	Transform transform = { {960, 1000}, 0, {1,1} };
	PropFloor1* property = (PropFloor1*)malloc(sizeof(PropFloor1));
	if (property == NULL)
	{
		return NULL;
	}
	property->sprite = render.LoadBitmapImage(L"Resources\\Map\\Floor1.bmp");
	GameObject* obj = CreateGameObject();
	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Draw = DrawFloor1;
	obj->Start = StartFloor1;
	obj->Update = UpdateFloor1;
	obj->OnCollisionEnter = EnterFloor1;
	obj->OnCollisionExit = ExitFloor1;
	obj->OnCollisionStay = StayFloor1;
	obj->SetRect(obj, 2500, 80);
	obj->collider = true;
	obj->SetTag(obj, "block");
	obj->property = property;
	obj->renderOrder = 1;
	obj->OnDestroy = Floor1OnDestroy;
	
	return obj;
}

DWORD WINAPI DrawFloor1(GameObject* this)
{
	PropFloor1* prop = this->property;
	render.DrawBitmapPreSize(this,prop->sprite,1,1920, 80);
	return 0;
}

void UpdateFloor1(GameObject* this, double dt)
{

}

void EnterFloor1(GameObject* this, CollisionResponse res)
{

}

void ExitFloor1(GameObject* this, CollisionResponse res)
{

}

void StayFloor1(GameObject* this, CollisionResponse res)
{

}

void StartFloor1(GameObject* this)
{

}

void Floor1OnDestroy(GameObject* this)
{
	free(this->property);
}