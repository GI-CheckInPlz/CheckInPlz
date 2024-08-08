#include "Timer.h"

void TimerInit()
{
	timerHandlerList=CreateTimerHandlerList();
}

void TimerUpdate(double dt)
{
	if (!timerHandlerList->isEmpty(timerHandlerList))
	{
		for (int i = 0; i < timerHandlerList->count; i++)
		{
			if(!timerHandlerList->Content[i]->exit)
				TimerHandlerUpdate(timerHandlerList->Content[i], dt);
		}
	}
	for (int i = timerHandlerList->count - 1; i >= 0; i--)
	{
		if (!timerHandlerList->Content[i])
		{
			timerHandlerList->RemoveAt(timerHandlerList, i);
		}
		else if(timerHandlerList->Content[i]->exit)
		{
			TimerHandler* tmp = timerHandlerList->Content[i];
			timerHandlerList->RemoveAt(timerHandlerList,i);
			free(tmp);
		}
	}
}

TimerHandler* TimerDelay(GameObject* this,double delay, Bool loop, callBack CallBack,void *etc)
{
	TimerHandler* handler = CreateTimerHandler(this,delay,loop,CallBack, etc);
	timerHandlerList->Add(timerHandlerList,handler);
	return handler;
}

void TimerCancel(TimerHandler* handler)
{
	for (int i = timerHandlerList->count - 1; i >= 0; i--)
	{
		if (timerHandlerList->Content[i]==handler)
		{
			TimerHandler* tmp = timerHandlerList->Content[i];
			timerHandlerList->Content[i]->exit = true;
			return;
		}
	}
}

void TimerCancelAllInObject(GameObject* this)
{
	for (int i = timerHandlerList->count - 1; i >= 0; i--)
	{
		if (timerHandlerList->Content[i]->t == this)
		{
			TimerHandler* tmp = timerHandlerList->Content[i];
			timerHandlerList->Content[i]->exit = true;
		}
	}
}

const Timer timer = {
	TimerInit,
	TimerUpdate,
	TimerDelay,
	TimerCancel,
	TimerCancelAllInObject
};