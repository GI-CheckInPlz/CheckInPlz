#include "GameObjectList.h"

GameObjectList* CreateGameObjectList()
{
	GameObjectList* list = (GameObjectList*)malloc(sizeof(GameObjectList));
	if (list == NULL)
	{
		return NULL;
	}
	list->Content = (GameObject**)malloc(sizeof(GameObject*) * MAX_GAMEOBJECT);
	list->count = 0;
	list->Add = AddGameObject;
	list->Remove = RemoveGameObject;
	list->Clear = ClearGameObject;
	list->isEmpty = GameObjectisEmpty;
	list->Exist = GameObjectExist;
	return list;
}


void AddGameObject(GameObjectList* list, GameObject* obj)
{
	list->Content[list->count] = obj;
	list->count++;
}
GameObject* RemoveGameObject(GameObjectList* list, GameObject* obj)
{
	GameObject* check = NULL;
	for (int i = 0; i < list->count; i++)
	{
		if (check)
		{
			list->Content[i - 1] = list->Content[i];
		}
		if (list->Content[i] == obj)
		{
			check = list->Content[i];	
		}
	}
	if (check)
	{
		list->count--;
	}
	return check;
}
Bool GameObjectisEmpty(GameObjectList* list)
{
	return list->count ? 0:1;
}
void ClearGameObject(GameObjectList* list) 
{
	list->count = 0;
}

Bool GameObjectExist(GameObjectList* list, GameObject* obj)
{
	for (int i = 0; i < list->count; i++)
	{
		if (list->Content[i] == obj)
		{
			return true;
		}
	}
	return false;
}