#pragma once
#include "define.h" //������ �ڷ��� ��ټ� ����

typedef struct TimerHandler //Ÿ�̸� �ڵ鷯 ����ü
{
	GameObject* t; //�׿��� �ּ� ���޹���.
	callBack CallBack; // �ݹ� 
	double delay; //������ �ð� ���
	double accum; // ���� �ð�
	Bool loop; //���� �� �Ÿ� true, �ܹ߼��� false.
	Bool exit;  //Ż���ϴ� ����.
	void* etc;
}TimerHandler;

void TimerHandlerUpdate(TimerHandler*, double);
//void TimerHandlerUpdate(�ڵ鷯 ��ü �̸�, ��ŸŸ��);

extern TimerHandler* CreateTimerHandler(GameObject*, double, Bool, callBack,void *);
// extern TimerHandler* CreateTimerHandler(��ü �׿���, ������ �ð�(��), ����O/X, �ݹ�);

