#include "Block2.h"

/// 슬로우블럭

GameObject* CreateBlock2(HBITMAP hBitmap, int size)
{
	Transform transform = { {0, 0}, 0, {1,1} };
	PropBlock2* property = (PropBlock2*)malloc(sizeof(PropBlock2));
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
	obj->Draw = DrawBlock2;
	obj->Start = StartBlock2;
	obj->SetRect(obj, size, size);
	obj->SetTag(obj, "block2");
	obj->collider = true;
	obj->property = property;
	obj->renderOrder = 2;
	obj->OnDestroy = Block2OnDestroy;
	return obj;
}

void Block2OnDestroy(GameObject* this)
{
	free(this->property);
}

DWORD WINAPI DrawBlock2(GameObject* this)
{
	PropBlock2* prop = this->property;
	render.DrawBitmapPreSize(this, prop->hBitmap, 1, prop->size, prop->size);
	return 0;
}

void StartBlock2(GameObject* this)
{

}
