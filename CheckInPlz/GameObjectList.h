#pragma once
#include "define.h"
#include "GameObject.h"


typedef struct GameObjectList 
{
	GameObject** Content; //실제 겜옵젝 리스트 보관하는 곳
	int count; //리스트 내 겜옵젝의 개수
	
	void (*Add)(struct GameObjectList*, GameObject*);
	//void (*Add)(옵젝 추가하고 싶은 겜옵젝 리스트 포인터, 추가할 옵젝 포인터);

	char (*Remove)(struct GameObjectList*, GameObject*);
	//void (*Remove)(옵젝 삭제하고 싶은 겜옵젝 리스트 포인터, 삭제할 옵젝 포인터);

	void (*Clear)(struct GameObjectList*);
	//void (*Clear)(내용을 모두 없애고 싶은 겜옵젝 리스트 포인터);

	int (*isEmpty)(struct GameObjectList* sPtr);
	//int (*isEmpty)(인티저 리스트 포인터);
	Bool(*Exist)(struct GameObjectList* list, GameObject* obj);
}GameObjectList;

extern GameObjectList* CreateGameObjectList();

void AddGameObject(GameObjectList*, GameObject*);
GameObject* RemoveGameObject(GameObjectList*, GameObject*);
Bool GameObjectisEmpty(GameObjectList*);
void ClearGameObject(GameObjectList*);
Bool GameObjectExist(GameObjectList* list, GameObject* obj);



