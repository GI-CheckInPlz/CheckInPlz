#pragma once
#include "define.h"
#include "TimerHandler.h"
#include "TimerHandlerList.h"

typedef struct Timer
{
	void  (*Init)();
	// = TimerInit, Ÿ�̸� �ڵ鷯 ����Ʈ�� �޴´�.
	void  (*Update)(double);
	// = TimerUpdate, Ÿ�̸Ӹ� �Ű����� �ʸ��� ������Ʈ.
	TimerHandler* (*Delay)(GameObject* , double , Bool , callBack , void* );
	//������ �Լ�
	// = Delay(���ӿ�����Ʈ,'�̷�' �� ��, �ݺ�O/X, �ݹ��Լ�)
	void (*Cancel)(TimerHandler*);
	void (*CancelAllInObject)(GameObject*);
	//Ÿ�̸� �ڵ鷯 ����, �� �̻� Ÿ�̸� ���� ����X.
}Timer;

//�� ����ü�� 1��1 ����
void TimerInit();
void TimerUpdate(double);
TimerHandler* TimerDelay(GameObject*, double, Bool, callBack, void*);
void TimerCancel(TimerHandler*);
void TimerCancelAllInObject(GameObject*);

//TimerHandler ���� ���� ����Ʈ ��ü ����. 
TimerHandlerList* timerHandlerList;
//Timer �ܺ� Ȱ�� ���.
extern const Timer timer;
 