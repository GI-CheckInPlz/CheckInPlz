#pragma once
#include "Timer.h"
#include "HBITMAPList.h"
#include "Render.h"

//애니메이션은 프로퍼티를 만들어서 Animation 객체를 선언하는 방식이 가장 좋다.
//단, 주의가 따름. 애니메이션을 만들때, 반복문에서의 호출 절대 금지!


typedef struct Animation Animation;
void PlayAnimation(GameObject* ,Animation* ,float, Bool );
//void PlayAnimation(자신의 겜옵젝 포인터, 플레이할 애니메이션 포인터, 총 지속 시간(초), 반복 여부);

void DrawAnimation(GameObject* ,Animation*,float alpha);
//void DrawAnimation(자신의 겜옵젝 포인터,렌더할 애니메이션 포인터);

void CancelAnimation(Animation*);
//void CancelAnimation(멈출 애니메이션 포인터);

void DestoryAnimation(Animation*);

void PushImage(Animation*, wchar_t* path);
//void PushImage(이미지 추가하고 싶은 애니메이션 포인터, 이미지 아이디)


extern Animation* CreateAnimation();
//Animation을 만들때 외부에서 호출하는 함수.
//단! Update에서 반복문으로 돌리면 버퍼 오버로드가 나고, 
//animation.Play를 Start 대응 함수에서 쓰더라도,
//animation.Draw를 Draw 대응 함수에서 반드시 함께 써줘야 한다.
//애니메이션을 멈출 때, CancelAnimation을 반드시 사용해야 한다. 

struct Animation {
	Animation* this;
	HBITMAPList* hBitmapList;
	HBITMAP* currentBitmap;
	TimerHandler* animationHandler;
	int index;
	void (*Play)(GameObject*,Animation* ,float , Bool );
	void (*Cancel)(Animation*);
	void (*Draw)(GameObject*,Animation*,float);
	void (*CancelAnimation)(Animation*);
	void (*PushImage)(Animation* , wchar_t* path);
};

