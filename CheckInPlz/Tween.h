#pragma once
#include "define.h"
#include "Timer.h"

#define TWEEN_STEP 0.01f

typedef enum PLAYBACK
{
	PLAYBACK_ONCE_FORWARD,
	PLAYBACK_ONCE_BACKWARD,
	PLAYBACK_ONCE_PINGPONG,
	PLAYBACK_LOOP_FORWARD,
	PLAYBACK_LOOP_BACKWARD,
	PLAYBACK_LOOP_PINGPONG
}PLAYBACK;

typedef enum EASING
{
	EASING_LINEAR,
	EASING_INBACK,
	EASING_OUTBACK,
	EASING_INOUTBACK,
	EASING_INBOUNCE,
	EASING_OUTBOUNCE,
	EASING_INOUTBOUNCE,
	EASING_INELASTIC,
	EASING_OUTELASTIC,
	EASING_INOUTELASTIC,
	EASING_INSINE,
	EASING_OUTSINE,
	EASING_INOUTSINE,
	EASING_INEXPO,
	EASING_OUTEXPO,
	EASING_INOUTEXPO,
	EASING_INCIRC,
	EASING_OUTCIRC,
	EASING_INOUTCIRC,
	EASING_INQUAD,
	EASING_OUTQUAD,
	EASING_INOUTQUAD,
	EASING_INCUBIC,
	EASING_OUTCUBIC,
	EASING_INOUTCUBIC,
	EASING_INQUART,
	EASING_OUTQUART,
	EASING_INOUTQUART,
	EASING_INQUINT,
	EASING_OUTQUINT,
	EASING_INOUTQUINT
}EASING;

typedef struct AnimationData {
	float* src;
	PLAYBACK playback;
	float (*easeFunc)(float x);
	float to;
	float duration;
	float delta;
	callBack Callback;
	float acum;
	float original;
	int direction;
	TimerHandler* handler;
}AnimationData;


float easeLinear(float x);
float easeInSine(float x);
float easeOutSine(float x);
float easeInOutSine(float x);
float easeInCubic(float x);
float easeOutCubic(float x);
float easeInOutCubic(float x);
float easeInQuint(float x);
float easeOutQuint(float x);
float easeInOutQuint(float x);
float easeInCirc(float x);
float easeOutCirc(float x);
float easeInOutCirc(float x);
float easeInElastic(float x);
float easeOutElastic(float x);
float easeInOutElastic(float x);
float easeInQuad(float x);
float easeOutQuad(float x);
float easeInOutQuad(float x);
float easeInQuart(float x);
float easeOutQuart(float x);
float easeInOutQuart(float x);
float easeInExpo(float x);
float easeOutExpo(float x);
float easeInOutExpo(float x);
float easeInBack(float x);
float easeOutBack(float x);
float easeInOutBack(float x);
float easeOutBounce(float x);
float easeInBounce(float x);
float easeInOutBounce(float x);
void step(GameObject* t, void* d);

float (*EaseFunctionList[31])(float);

extern void CancleAnimate(AnimationData*);
extern AnimationData* Animate(GameObject* t, float* src, PLAYBACK playback, float to, EASING easing, float duration, void* Callback);