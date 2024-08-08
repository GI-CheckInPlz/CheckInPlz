#pragma once
#include "TimerHandler.h" //TimerHandler 포함

typedef struct TimerHandlerList TimerHandlerList;
struct TimerHandlerList //TimerHandlerList 구조체 
{
	TimerHandler** Content; //TimerHandler** -> 내용.
	int count; //List의 총량.
	void (*Add)(TimerHandlerList*, TimerHandler**); 
	//TimerHandlerList에 핸들러 객체 추가.
	TimerHandler* (*Remove)(TimerHandlerList*, TimerHandler**);
	//TimerHandlerList에서 Pop과 같은 역할을 수행.
	void (*Clear)(TimerHandlerList*);
	//TimerHandlerList 내용 클리어!
	int (*isEmpty)(TimerHandlerList* sPtr);
	//TimerHandlerList가 비었는지 체크.
	TimerHandler* (*RemoveAt)(TimerHandlerList* list, int index);
};

//위 내용에 1대1 대응.
void AddTimerHandler(TimerHandlerList*, GameObject*);
TimerHandler* RemoveTimerHandler(TimerHandlerList*, GameObject*);
Bool TimerHandlerisEmpty(TimerHandlerList*);
void ClearTimerHandler(TimerHandlerList*);
TimerHandler* RemoveAtTimerHandler(TimerHandlerList* list, int index);
extern TimerHandlerList* CreateTimerHandlerList();