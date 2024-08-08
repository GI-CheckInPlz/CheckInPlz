#pragma once
#include "define.h" //���� �� Ȱ�� �ڷ��� ������ ���� ���.
#include "Win32api.h" //Win32API �⺻ �Լ� ����
#include "Input.h" //Input�� �޾ƿ��� ���.
#include "Scene.h" //Scene�� ����ϴ� ���.
#include "Timer.h" //Timer�� ����ϴ� ���. 

//Engine Inner Func

DWORD WINAPI EngineRender(LPVOID data);
extern EngineState EngineDraw();
//���� �� �׷��� ���

static GameObjectList* objectBuffer; //Instantiate Buffer
//��κ��� �׿������� objectBuffer�� ���� ��, ���� ���۰� �Բ� ���� �߰�.
static GameObjectList* removeObjectBuffer; //Destroy Buffer
//removeObjectBuffer�� �� �׿�������, ���� Ư�� �������� �����κ��� ���ŵ�.
extern Scene* currentScene;
//���� ���� ����Ų��. 
Scene* nextScene; //Changed Scene Buffer
EngineState state;
//���� ������ ����, Stop, Run, Error ����.

//extern
extern GameObject* Instantiate(GameObject* newObject);
//extern GameObject* Instantiate(GameObject* ������ ������Ʈ);
//����������Ŭ�� ��߳��� �ʰ� �� ��ũ��Ʈ �ȿ��� �׿��� ���� ����.
extern void Destroy(GameObject* obj); //������Ʈ �ı�.
extern void RunEngine(Scene* scene); //������ ������ �Լ�
extern void ChangeScene(Scene* scene); //���� �ٲٴ� �Լ�.
extern void SetRenderOrder(GameObject* t, int order); //���� ���� �ٲٱ�