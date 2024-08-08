#include "Block1.h"

/// 기본블럭

GameObject* CreateBlock1(HBITMAP hBitmap,int size)
{
	Transform transform = { {0, 0}, 0, {1,1} };
	PropBlock1* property = (PropBlock1*)malloc(sizeof(PropBlock1));
	if (property == NULL)
	{
		return NULL;
	}
	property->hBitmap = hBitmap;
	property->size = size;
	GameObject* obj = CreateGameObject();
	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Draw = DrawBlock1;
	obj->Start = StartBlock1;
	obj->Update = UpdateBlock1;
	obj->OnCollisionEnter = EnterBlock1;
	obj->OnCollisionExit = ExitBlock1;
	obj->OnCollisionStay = StayBlock1;
	obj->SetRect(obj, size, size);
	obj->SetTag(obj, "block1");
	obj->collider = true;
	obj->property = property;
	obj->renderOrder = 2;
	obj->OnDestroy = Block1OnDestroy;
	return obj;
}

void Block1OnDestroy(GameObject* this)
{
	free(this->property);
}

DWORD WINAPI DrawBlock1(GameObject* this)
{
	PropBlock1* prop = this->property;
	render.DrawBitmapPreSize(this, prop->hBitmap, 1, (int)(prop->size* this->transform.scale.x), (int)(prop->size* this->transform.scale.y));
	return 0;
}

void UpdateBlock1(GameObject* this, double dt)
{

}

void EnterBlock1(GameObject* this, CollisionResponse res)
{

}

void ExitBlock1(GameObject* this, CollisionResponse res)
{

}

void StayBlock1(GameObject* this, CollisionResponse res)
{

}

void StartBlock1(GameObject* this)
{
	this->transform.scale.x = 0.5;
	this->transform.scale.y = 0.5;
	Animate(this, &this->transform.scale.x, PLAYBACK_ONCE_FORWARD, 1, EASING_INBOUNCE,0.2f, NULL);
	Animate(this, &this->transform.scale.y, PLAYBACK_ONCE_FORWARD, 1, EASING_INBOUNCE, 0.2f, NULL);
}


