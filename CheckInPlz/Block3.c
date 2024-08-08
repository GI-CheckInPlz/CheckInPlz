#include "Block3.h"

/// 점프블럭

GameObject* CreateBlock3(HBITMAP hBitmap, int size)
{
	Transform transform = { {0, 0}, 0, {1,1} };
	PropBlock3* property = (PropBlock3*)malloc(sizeof(PropBlock3));
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
	obj->Draw = DrawBlock3;
	obj->Start = StartBlock3;
	obj->SetRect(obj, size, size);
	obj->SetTag(obj, "block3");
	obj->collider = true;
	obj->property = property;
	obj->renderOrder = 2;
	obj->OnDestroy = Block3OnDestroy;
	return obj;
}

void Block3OnDestroy(GameObject* this)
{
	free(this->property);
}

DWORD WINAPI DrawBlock3(GameObject* this)
{
	PropBlock3* prop = this->property;
	render.DrawBitmapPreSize(this, prop->hBitmap, 1, prop->size, prop->size);
	return 0;
}

void StartBlock3(GameObject* this)
{

}
