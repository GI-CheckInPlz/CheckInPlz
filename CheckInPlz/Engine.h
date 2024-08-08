#pragma once
#include "define.h" //게임 내 활용 자료형 재정의 포함 헤더.
#include "Win32api.h" //Win32API 기본 함수 내장
#include "Input.h" //Input을 받아오는 헤더.
#include "Scene.h" //Scene을 담당하는 헤더.
#include "Timer.h" //Timer를 담당하는 헤더. 

//Engine Inner Func

DWORD WINAPI EngineRender(LPVOID data);
extern EngineState EngineDraw();
//엔진 내 그래픽 출력

static GameObjectList* objectBuffer; //Instantiate Buffer
//대부분의 겜옵젝들은 objectBuffer에 모인 뒤, 루프 시작과 함께 씬에 추가.
static GameObjectList* removeObjectBuffer; //Destroy Buffer
//removeObjectBuffer에 들어간 겜옵젝들은, 루프 특정 지점에서 씬으로부터 제거됨.
extern Scene* currentScene;
//현재 씬을 가리킨다. 
Scene* nextScene; //Changed Scene Buffer
EngineState state;
//현재 엔진의 상태, Stop, Run, Error 사이.

//extern
extern GameObject* Instantiate(GameObject* newObject);
//extern GameObject* Instantiate(GameObject* 생성할 오브젝트);
//라이프사이클에 어긋나지 않게 씬 스크립트 안에서 겜옵젝 동적 생성.
extern void Destroy(GameObject* obj); //오브젝트 파괴.
extern void RunEngine(Scene* scene); //엔진을 돌리는 함수
extern void ChangeScene(Scene* scene); //씬을 바꾸는 함수.
extern void SetRenderOrder(GameObject* t, int order); //렌더 순서 바꾸기