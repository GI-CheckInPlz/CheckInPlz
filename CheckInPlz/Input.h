#pragma once
#include "define.h"
#include "Win32api.h"
#include "IntegerList.h"  //인티저 리스트 관리, 후술.

//KeyStructure 구조체
typedef struct KeyStructure {
	int keyCode;  //키 코드, WinAPI 관련 Virtual Key 정보 참고.
	Bool pressed; //눌렸는가?
	Bool released; //풀렸는가?
}KeyStructure;


void InitializeInput(); //인풋 기능을 초기화.
vector2 GetMousePosition(); //마우스의 위치를 vector2로 리턴.
Bool GetMouseButton(int btn); //마우스 버튼이 눌려 있을 때 호출.
Bool GetMouseButtonDown(int btn); //마우스 버튼이 막 눌렸을 때 호출.
Bool GetMouseButtonUp(int btn); //마우스 버튼 눌렀다가 막 똈을 때 호출.
int GetMouseWheel(); //마우스 휠 버튼 눌린 것을 감지
Bool GetKeyDown(int key); //키 버튼이 막 눌렸을 때 호출. 
Bool GetKeyUp(int key);
//키 버튼 눌렀다가 막 똈을 때 호출.
Bool GetKey(int key);
//키 버튼이 눌려 있을 때 호출.

void KeyPressed(int key);
void KeyReleased(int key);
void MousePressed(int btn);
void MouseReleased(int btn);
void UpdateInput();

KeyStructure L; //좌클릭
KeyStructure R; //우클릭
KeyStructure M; //마우스 휠

static IntegerList* Pressed; //눌린 키들의 리스트
static IntegerList* Released; //떼어진 키들의 리스트
static KeyStructure Mouse[3];  //마우스 버튼 3개, 배열로 저장
static int MouseWheel; //마우스 휠의 값
HWND m_hWnd;
HDC hdc;


//위와 1대1 대응
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
//static 함수처럼 동작

extern const Input input;
//외부 선언 위한 extern 정의
