#pragma once
#include "define.h"
#include "GameObjectList.h"
#include "ConstructorList.h"
typedef struct Scene Scene;
void StartScene(Scene*);
void UpdateScene(Scene* ,double);  //(�� �ڽ� ������, ��ŸŸ��) 
void Push(Scene* ,GameObject*); //(�����ϰ��� �ϴ� ��, �׿��� ������)
void Hold(Scene*, Constructor); //(�׿����� ������ �ϴ� ��, �׿��� ������)
void Pop(Scene* ,GameObject*);
void OnEnableScene(Scene*);
void OnDisableScene(Scene*);
void DrawScene(Scene* this, Bool* Drawing);
void CollideScene(Scene*);



struct Scene
{
	struct Scene* t;
	void (*Start)(Scene*);
	void (*Update)(Scene*, double);
	void (*Draw)(Scene*, Bool*);
	void (*Push)(Scene*, GameObject*);
	void (*Hold)(Scene*, Constructor);
	void (*Pop)(Scene*, GameObject*);
	void (*OnEnable)(Scene*);
	void (*OnDisable)(Scene*);
	void (*Collide)(Scene*);
	GameObjectList* gameObjectList;
	GameObjectList* drawList;
	ConstructorList* constructorList;

};

extern Scene* CreateScene();
extern void RenderSort(GameObjectList* list);