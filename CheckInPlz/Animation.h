#pragma once
#include "Timer.h"
#include "HBITMAPList.h"
#include "Render.h"

//�ִϸ��̼��� ������Ƽ�� ���� Animation ��ü�� �����ϴ� ����� ���� ����.
//��, ���ǰ� ����. �ִϸ��̼��� ���鶧, �ݺ��������� ȣ�� ���� ����!


typedef struct Animation Animation;
void PlayAnimation(GameObject* ,Animation* ,float, Bool );
//void PlayAnimation(�ڽ��� �׿��� ������, �÷����� �ִϸ��̼� ������, �� ���� �ð�(��), �ݺ� ����);

void DrawAnimation(GameObject* ,Animation*,float alpha);
//void DrawAnimation(�ڽ��� �׿��� ������,������ �ִϸ��̼� ������);

void CancelAnimation(Animation*);
//void CancelAnimation(���� �ִϸ��̼� ������);

void DestoryAnimation(Animation*);

void PushImage(Animation*, wchar_t* path);
//void PushImage(�̹��� �߰��ϰ� ���� �ִϸ��̼� ������, �̹��� ���̵�)


extern Animation* CreateAnimation();
//Animation�� ���鶧 �ܺο��� ȣ���ϴ� �Լ�.
//��! Update���� �ݺ������� ������ ���� �����ε尡 ����, 
//animation.Play�� Start ���� �Լ����� ������,
//animation.Draw�� Draw ���� �Լ����� �ݵ�� �Բ� ����� �Ѵ�.
//�ִϸ��̼��� ���� ��, CancelAnimation�� �ݵ�� ����ؾ� �Ѵ�. 

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

