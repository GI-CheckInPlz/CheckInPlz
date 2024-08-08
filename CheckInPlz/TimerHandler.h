#pragma once
#include "define.h" //재정의 자료형 대다수 포함

typedef struct TimerHandler //타이머 핸들러 구조체
{
	GameObject* t; //겜옵젝 주소 전달받음.
	callBack CallBack; // 콜백 
	double delay; //딜레이 시간 등록
	double accum; // 누산 시간
	Bool loop; //루프 돌 거면 true, 단발성은 false.
	Bool exit;  //탈출하는 시점.
	void* etc;
}TimerHandler;

void TimerHandlerUpdate(TimerHandler*, double);
//void TimerHandlerUpdate(핸들러 객체 이름, 델타타임);

extern TimerHandler* CreateTimerHandler(GameObject*, double, Bool, callBack,void *);
// extern TimerHandler* CreateTimerHandler(자체 겜옵젝, 딜레이 시간(초), 루프O/X, 콜백);

