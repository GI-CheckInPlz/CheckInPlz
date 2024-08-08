#pragma once
#include "TimerHandler.h" //TimerHandler ����

typedef struct TimerHandlerList TimerHandlerList;
struct TimerHandlerList //TimerHandlerList ����ü 
{
	TimerHandler** Content; //TimerHandler** -> ����.
	int count; //List�� �ѷ�.
	void (*Add)(TimerHandlerList*, TimerHandler**); 
	//TimerHandlerList�� �ڵ鷯 ��ü �߰�.
	TimerHandler* (*Remove)(TimerHandlerList*, TimerHandler**);
	//TimerHandlerList���� Pop�� ���� ������ ����.
	void (*Clear)(TimerHandlerList*);
	//TimerHandlerList ���� Ŭ����!
	int (*isEmpty)(TimerHandlerList* sPtr);
	//TimerHandlerList�� ������� üũ.
	TimerHandler* (*RemoveAt)(TimerHandlerList* list, int index);
};

//�� ���뿡 1��1 ����.
void AddTimerHandler(TimerHandlerList*, GameObject*);
TimerHandler* RemoveTimerHandler(TimerHandlerList*, GameObject*);
Bool TimerHandlerisEmpty(TimerHandlerList*);
void ClearTimerHandler(TimerHandlerList*);
TimerHandler* RemoveAtTimerHandler(TimerHandlerList* list, int index);
extern TimerHandlerList* CreateTimerHandlerList();