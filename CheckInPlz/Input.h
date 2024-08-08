#pragma once
#include "define.h"
#include "Win32api.h"
#include "IntegerList.h"  //��Ƽ�� ����Ʈ ����, �ļ�.

//KeyStructure ����ü
typedef struct KeyStructure {
	int keyCode;  //Ű �ڵ�, WinAPI ���� Virtual Key ���� ����.
	Bool pressed; //���ȴ°�?
	Bool released; //Ǯ�ȴ°�?
}KeyStructure;


void InitializeInput(); //��ǲ ����� �ʱ�ȭ.
vector2 GetMousePosition(); //���콺�� ��ġ�� vector2�� ����.
Bool GetMouseButton(int btn); //���콺 ��ư�� ���� ���� �� ȣ��.
Bool GetMouseButtonDown(int btn); //���콺 ��ư�� �� ������ �� ȣ��.
Bool GetMouseButtonUp(int btn); //���콺 ��ư �����ٰ� �� �I�� �� ȣ��.
int GetMouseWheel(); //���콺 �� ��ư ���� ���� ����
Bool GetKeyDown(int key); //Ű ��ư�� �� ������ �� ȣ��. 
Bool GetKeyUp(int key);
//Ű ��ư �����ٰ� �� �I�� �� ȣ��.
Bool GetKey(int key);
//Ű ��ư�� ���� ���� �� ȣ��.

void KeyPressed(int key);
void KeyReleased(int key);
void MousePressed(int btn);
void MouseReleased(int btn);
void UpdateInput();

KeyStructure L; //��Ŭ��
KeyStructure R; //��Ŭ��
KeyStructure M; //���콺 ��

static IntegerList* Pressed; //���� Ű���� ����Ʈ
static IntegerList* Released; //������ Ű���� ����Ʈ
static KeyStructure Mouse[3];  //���콺 ��ư 3��, �迭�� ����
static int MouseWheel; //���콺 ���� ��
HWND m_hWnd;
HDC hdc;


//���� 1��1 ����
typedef struct Input {
	void (*Init)();
	void (*Update)();
	vector2(*GetMousePosition)();
	Bool(*GetMouseButton)(int btn);
	Bool(* GetMouseButtonDown)(int btn);
	Bool(*GetMouseButtonUp)(int btn);
	Bool(*GetKeyDown)(int key);
	Bool(*GetKeyUp)(int key);
	Bool(*GetKey)(int key);
	void (*KeyPressed)(int key);
	void (*KeyReleased)(int key);
	void (*MousePressed)(int btn);
	void (*MouseReleased)(int btn);
}Input;
//static �Լ�ó�� ����

extern const Input input;
//�ܺ� ���� ���� extern ����
