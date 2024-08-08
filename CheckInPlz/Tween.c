#include "Tween.h"

void step(GameObject* t, void* d)
{
	AnimationData* data = (AnimationData*)d;
	if (data->playback == PLAYBACK_ONCE_PINGPONG || data->playback == PLAYBACK_LOOP_PINGPONG)
	{
		if (data->direction == 1)
		{
			(*data->src) = data->original + data->easeFunc(data->acum / (data->duration / 2)) * data->delta;
		}
		else if (data->direction == -1)
		{
			(*data->src) = data->original + data->easeFunc(((data->duration / 2) - data->acum) / (data->duration / 2)) * data->delta;
		}
	}
	else if (data->direction == 1)
	{
		(*data->src) = data->original + data->easeFunc(data->acum / data->duration) * data->delta;
	}
	else if (data->direction == -1)
	{
		(*data->src) = data->original + data->easeFunc((data->duration - data->acum) / data->duration) * data->delta;
	}

	data->acum += TWEEN_STEP;
	if (data->acum >= data->duration / 2 && data->playback == PLAYBACK_LOOP_PINGPONG)
	{
		if (data->direction == 1)
		{
			data->direction = -1;
			data->acum = 0;
		}
		else
		{
			data->direction = 1;
			data->acum = 0;
		}
	}
	else if (data->acum >= data->duration / 2 && data->playback == PLAYBACK_ONCE_PINGPONG)
	{
		if (data->direction == 1)
		{
			data->direction = -1;
			data->acum = 0;
		}
		else
		{
			(*data->src) = data->original;
			if (data->Callback)
			{
				callBack func = data->Callback;
				func(t, NULL);
			}
			timer.Cancel(data->handler);
			data->handler = NULL;
			free(data);
		}
	}
	else if (data->acum >= data->duration)
	{
		if (data->playback == PLAYBACK_ONCE_FORWARD)
		{
			(*data->src) = data->to;
			if (data->Callback)
			{
				callBack func = data->Callback;
				func(t, NULL);
			}
			timer.Cancel(data->handler);
			data->handler = NULL;
			free(data);
		}
		else if (data->playback == PLAYBACK_ONCE_BACKWARD)
		{
			(*data->src) = data->original;
			if (data->Callback)
			{
				callBack func = data->Callback;
				func(t, NULL);
			}
			timer.Cancel(data->handler);
			data->handler = NULL;
			free(data);
		}
		else if (data->playback == PLAYBACK_LOOP_FORWARD)
		{
			data->acum = 0;
		}
		else if (data->playback == PLAYBACK_LOOP_BACKWARD)
		{
			(*data->src) = data->to;
			data->acum = 0;
		}
	}
}

 AnimationData* Animate(GameObject* t, float* src, PLAYBACK playback, float to, EASING easing, float duration, void* Callback)
{
	AnimationData* data = (AnimationData*)malloc(sizeof(AnimationData));
	if (data == NULL)
	{
		return NULL;
	}
	data->Callback = Callback ? (callBack)Callback : NULL;
	data->src = src;
	data->duration = duration;
	data->acum = 0;
	data->easeFunc = EaseFunctionList[easing];
	data->playback = playback;
	data->original = (*src);
	data->to = to;
	data->delta = (to - *src);
	if (data->playback == PLAYBACK_ONCE_FORWARD || data->playback == PLAYBACK_LOOP_FORWARD)
	{
		data->direction = 1;

	}
	else if (data->playback == PLAYBACK_ONCE_BACKWARD || data->playback == PLAYBACK_LOOP_BACKWARD)
	{
		data->direction = -1;
		*(data->src) = data->to;
	}
	else if (data->playback == PLAYBACK_ONCE_PINGPONG || data->playback == PLAYBACK_LOOP_PINGPONG)
	{
		data->direction = 1;
	}
	data->handler = timer.Delay(t, TWEEN_STEP, true, step, data);
	return data;
}

void CancleAnimate(AnimationData* anim)
{
	if (anim != NULL)
	{
		timer.Cancel(anim->handler);
		free(anim);
	}
}


float easeInSine(float x)
{
	return (float)(1 - cos((x * PI) / 2));
}

float easeOutSine(float x)
{
	return (float)(sin((x * PI) / 2));
}

float easeInOutSine(float x)
{
	return (float)(-(cos(PI * x) - 1) / 2);
}

float easeInCubic(float x)
{
	return x * x * x;
}

float easeOutCubic(float x)
{
	return (float)(1 - pow(1 - x, 3));
}

float easeInOutCubic(float x)
{
	return x < 0.5 ? 4 * x * x * x : (float)(1 - pow(-2 * x + 2, 3) / 2);
}

float easeInQuint(float x)
{
	return x * x * x * x * x;
}

float easeOutQuint(float x)
{
	return (float)(1 - pow(1 - x, 5));
}

float easeInOutQuint(float x)
{
	return x < 0.5 ? 16 * x * x * x * x * x : (float)(1 - pow(-2 * x + 2, 5) / 2);
}

float easeInCirc(float x)
{
	return (float)(1 - sqrt(1 - pow(x, 2)));
}

float easeOutCirc(float x)
{
	return (float)(sqrt(1 - pow(x - 1, 2)));
}

float easeInOutCirc(float x)
{
	return x < 0.5 ? (float)(1 - sqrt(1 - pow(2 * x, 2))) / 2 : (float)(sqrt(1 - pow(-2 * x + 2, 2)) + 1) / 2;
}


float easeInElastic(float x)
{
	const float c4 = (float)((2 * PI) / 3);
	return x == 0 ? 0 : x == 1 ? 1 : (float)(-pow(2, 10 * x - 10) * sin((x * 10 - 10.75) * c4));
}


float easeOutElastic(float x)
{
	const float c4 = (float)((2 * PI) / 3);
	return x == 0 ? 0 : x == 1 ? 1 : (float)(pow(2, -10 * x) * sin((x * 10 - 0.75) * c4) + 1);
}

float easeInOutElastic(float x)
{
	const float c5 = (float)((2 * PI) / 4.5);
	return x == 0 ? 0 : x == 1 ? 1 : x < 0.5 ? (float)(- (pow(2, 20 * x - 10) * sin((20 * x - 11.125) * c5)) / 2) : (float)((pow(2, -20 * x + 10) * sin((20 * x - 11.125) * c5)) / 2 + 1);
}

float easeInQuad(float x)
{
	return x * x;
}

float easeOutQuad(float x)
{
	return 1 - (1 - x) * (1 - x);
}

float easeInOutQuad(float x)
{
	return x < 0.5 ? 2 * x * x : (float)(1 - pow(-2 * x + 2, 2) / 2);
}

float easeInQuart(float x)
{
	return x * x * x * x;
}

float easeOutQuart(float x)
{
	return (float)(1 - pow(1 - x, 4));
}

float easeInOutQuart(float x)
{
	return x < 0.5 ? 8 * x * x * x * x : (float)(1 - pow(-2 * x + 2, 4) / 2);
}

float easeInExpo(float x)
{
	return x == 0 ? 0 : (float)pow(2, 10 * x - 10);
}

float easeOutExpo(float x)
{
	return x == 1 ? 1 : (float)(1 - pow(2, -10 * x));
}

float easeInOutExpo(float x)
{
	return x == 0 ? 0 : x == 1 ? 1 : x < 0.5 ? (float)(pow(2, 20 * x - 10) / 2) : (float)((2 - pow(2, -20 * x + 10)) / 2);
}

float easeInBack(float x)
{
	const float c1 = 1.70158f;
	const float c3 = c1 + 1;
	return c3 * x * x * x - c1 * x * x;
}

float easeOutBack(float x)
{
	const float c1 = 1.70158f;
	const float c3 = c1 + 1;
	return (float)(1 + c3 * pow(x - 1, 3) + c1 * pow(x - 1, 2));
}

float easeInOutBack(float x)
{
	const float c1 = 1.70158f;
	const float c2 = c1 * 1.525f;
	return x < 0.5 ? (float)((pow(2 * x, 2) * ((c2 + 1) * 2 * x - c2)) / 2) : (float)((pow(2 * x - 2, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2);
}

float easeOutBounce(float x)
{
	const float n1 = 7.5625;
	const float d1 = 2.75;

	if (x < 1 / d1) {
		return n1 * x * x;
	}
	else if (x < 2 / d1) {
		return n1 * (x -= 1.5f / d1) * x + 0.75f;
	}
	else if (x < 2.5 / d1) {
		return n1 * (x -= 2.25f / d1) * x + 0.9375f;
	}
	else {
		return n1 * (x -= 2.625f / d1) * x + 0.984375f;
	}
}

float easeInBounce(float x)
{
	return 1 - easeOutBounce(1 - x);
}

float easeInOutBounce(float x)
{
	return x < 0.5 ? (1 - easeOutBounce(1 - 2 * x)) / 2 : (1 + easeOutBounce(2 * x - 1)) / 2;
}

float easeLinear(float x)
{
	return x;
}

float (*EaseFunctionList[31])(float) = {
	easeLinear,
	easeInBack,
	easeOutBack,
	easeInOutBack,
	easeInBounce,
	easeOutBounce,
	easeInOutBounce,
	easeInElastic,
	easeOutElastic,
	easeInOutElastic,
	easeInSine,
	easeOutSine,
	easeInOutSine,
	easeInExpo,
	easeOutExpo,
	easeInOutExpo,
	easeInCirc,
	easeOutCirc,
	easeInOutCirc,
	easeInQuad,
	easeOutQuad,
	easeInOutQuad,
	easeInCubic,
	easeOutCubic,
	easeInOutCubic,
	easeInQuart,
	easeOutQuart,
	easeInOutQuart,
	easeInQuint,
	easeOutQuint,
	easeInOutQuint
};
