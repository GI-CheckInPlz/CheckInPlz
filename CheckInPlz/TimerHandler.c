#include "TimerHandler.h"


void NullCallback(GameObject* this, void* etc)
{

}

void TimerHandlerUpdate(TimerHandler* handler, double dt)
{
	handler->accum += dt;
	if (handler->accum >= handler->delay)
	{
		handler->accum = 0;
		handler->CallBack(handler->t,handler->etc);
		if (!handler->loop)
			handler->exit = true;
	}
}


TimerHandler* CreateTimerHandler(GameObject* this, double delay, Bool loop, callBack CallBack, void * etc)
{
	TimerHandler* handler = (TimerHandler*)malloc(sizeof(TimerHandler));
	handler->t = this;
	handler->accum = 0;
	handler->delay = delay;
	handler->loop = loop;
	handler->CallBack = CallBack;
	handler->exit = false;
	handler->etc = etc ? etc : NULL;
	return handler;
}

