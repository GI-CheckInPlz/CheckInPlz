#pragma once
#include "define.h" //게임 내 자료형 등 정의한 파일

extern HINSTANCE m_hInstance; ; //WinAPI의 HINSTANCE, 전역
extern HWND m_hWnd; //WinAPI의 HWND, 전역
extern HDC hdc; //WinAPI의 HDC, 전역
HBITMAP hBit;
HDC MemDC;
HDC PreMemDC;
Screen screen; //스크린 객체.


static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//윈도우 프로시져 함수


extern Bool Init(HINSTANCE hInstance);
//InitInstance와 동일 기능

extern EngineState UpdateMsg(MSG* msg);
//메세지 루프, EngineState를 리턴한다.
//EngineState는 총 Stop, Run, Error로 구성된 열거형. 엔진 상태 표기

extern void release();
//프로그램 종료 시 관련 메모리 놔줌. 
