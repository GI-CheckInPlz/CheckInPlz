#pragma once
#include "define.h" //���� �� �ڷ��� �� ������ ����

extern HINSTANCE m_hInstance; ; //WinAPI�� HINSTANCE, ����
extern HWND m_hWnd; //WinAPI�� HWND, ����
extern HDC hdc; //WinAPI�� HDC, ����
HBITMAP hBit;
HDC MemDC;
HDC PreMemDC;
Screen screen; //��ũ�� ��ü.


static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//������ ���ν��� �Լ�


extern Bool Init(HINSTANCE hInstance);
//InitInstance�� ���� ���

extern EngineState UpdateMsg(MSG* msg);
//�޼��� ����, EngineState�� �����Ѵ�.
//EngineState�� �� Stop, Run, Error�� ������ ������. ���� ���� ǥ��

extern void release();
//���α׷� ���� �� ���� �޸� ����. 
