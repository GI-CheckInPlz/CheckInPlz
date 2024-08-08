#include "Stage1.h"

GameObject* CreateStage1()
{
	Transform transform = { {960, 900}, 0, {1,1} };
	PropStage1* property = (PropStage1*)malloc(sizeof(PropStage1));
	GameObject* obj = CreateGameObject();
	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->SetRect(obj, 1920, 10);
	obj->SetTag(obj, "block");
	obj->property = property;
	InitializeStageManager(obj,"Resources\/Stage1M.CSV","Resources\/Stage1S.CSV",1000);
	obj->OnDestroy = Stage1OnDestroy;
	return obj;
}

void Stage1OnDestroy(GameObject* this)
{
	free(this->property);
}