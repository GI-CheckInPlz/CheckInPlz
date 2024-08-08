#pragma once
#include "define.h"
#include "GameObject.h"


typedef struct GameObjectList 
{
	GameObject** Content; //���� �׿��� ����Ʈ �����ϴ� ��
	int count; //����Ʈ �� �׿����� ����
	
	void (*Add)(struct GameObjectList*, GameObject*);
	//void (*Add)(���� �߰��ϰ� ���� �׿��� ����Ʈ ������, �߰��� ���� ������);

	char (*Remove)(struct GameObjectList*, GameObject*);
	//void (*Remove)(���� �����ϰ� ���� �׿��� ����Ʈ ������, ������ ���� ������);

	void (*Clear)(struct GameObjectList*);
	//void (*Clear)(������ ��� ���ְ� ���� �׿��� ����Ʈ ������);

	int (*isEmpty)(struct GameObjectList* sPtr);
	//int (*isEmpty)(��Ƽ�� ����Ʈ ������);
	Bool(*Exist)(struct GameObjectList* list, GameObject* obj);
}GameObjectList;

extern GameObjectList* CreateGameObjectList();

void AddGameObject(GameObjectList*, GameObject*);
GameObject* RemoveGameObject(GameObjectList*, GameObject*);
Bool GameObjectisEmpty(GameObjectList*);
void ClearGameObject(GameObjectList*);
Bool GameObjectExist(GameObjectList* list, GameObject* obj);



