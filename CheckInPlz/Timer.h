#pragma once
#include "define.h"
#include "TimerHandler.h"
#include "TimerHandlerList.h"

typedef struct Timer
{
	void  (*Init)();
	// = TimerInit, 타이머 핸들러 리스트를 받는다.
	void  (*Update)(double);
	// = TimerUpdate, 타이머를 매개변수 초마다 업데이트.
	TimerHandler* (*Delay)(GameObject* , double , Bool , callBack , void* );
	//딜레이 함수
	// = Delay(게임오브젝트,'미룰' 초 수, 반복O/X, 콜백함수)
	void (*Cancel)(TimerHandler*);
	void (*CancelAllInObject)(GameObject*);
	//타이머 핸들러 기준, 더 이상 타이머 루프 실행X.
}Timer;

//위 구조체에 1대1 대응
void TimerInit();
void TimerUpdate(double);
TimerHandler* TimerDelay(GameObject*, double, Bool, callBack, void*);
void TimerCancel(TimerHandler*);
void TimerCancelAllInObject(GameObject*);

//TimerHandler 관리 위한 리스트 객체 설정. 
TimerHandlerList* timerHandlerList;
//Timer 외부 활용 허용.
extern const Timer timer;
 