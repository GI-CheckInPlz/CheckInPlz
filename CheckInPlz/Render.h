#pragma once
#include "define.h"
#include "Win32Api.h"
#include "Engine.h"
#pragma comment(lib, "msimg32.lib")  //�̹��� ��� ���� ���̺귯��

void RenderInit(); //���� �ʱ�ȭ
void RenderUpdate(Bool* Drawing); //�� �������� ���� ������Ʈ. 
void DrawEllipse(GameObject* this, int size_x, int size_y, COLORREF penColor, COLORREF brushColor);
void DrawDebugRectangle(GameObject* this);
//void DrawEllipse(�׿��� �ڽ� ������, ���� ������, ���� ������, �� ����, �귯�� ����);
//Ÿ��/�� �׸���

void DrawRectangle(GameObject* this, int size_x, int size_y, COLORREF penColor, COLORREF brushColor, float alpha);
//void DrawEllipse(�׿��� �ڽ� ������, ���� ������, ���� ������, �� ����, �귯�� ����);
//���簢�� �׸���.

void DrawLine(GameObject* this, int start_x, int start_y, int end_x, int end_y, COLORREF penColor, COLORREF brushColor);
//void DrawLine(�׿��� �ڽ� ������, �� X�� ��ŸƮ ����, �� Y�� ��ŸƮ ����, 
//X�� �� ����, Y�� �� ����, �� ����, �귯�� ����);
//�� �߱�

void DrawBitmap(GameObject* this, HBITMAP image, float alpha);
//void DrawBitmap(�׿��� �ڽ� ������, �̹��� ���̵� (#define ����));
//Bitmap �̹��� �׸���. 
void DrawBitmapPre(GameObject*, HBITMAP, float, int, int, int, int);

//DrawBitmapPreSize�� ����, ������, �ι�° ������, ������ ���ڿ� x ������, y �������� ���� �� ����.
void DrawBitmapWithCustom(GameObject*, HBITMAP, float, int, int, int, int);

//DrawBitmapPreSize�� ����, ������, �ι�° ������, ������ ���ڿ� x ��ǥ, y ��ǥ�� ���� �� ����.
void DrawBitmapWithCoords(GameObject* this, HBITMAP bmp, float alpha, int size_x, int size_y, int _posX, int _posY);

//����ŷ ó���� ��Ʈ���� �Ĺݺ��� ��ǥ�� ����Ѵ�.
void DrawMaskedBitmapCoords(GameObject* this, HBITMAP maskBMP, float mask_size_x, float mask_size_y, int mask_pos_x, int mask_pos_y, float mask_alpha, HBITMAP bmp, int pos_x, int pos_y, float scale_x, float scale_y, float alpha);
void DrawMaskedBitmapCoordsM(GameObject* this, HBITMAP maskBMP, float mask_size_x, float mask_size_y, int mask_pos_x, int mask_pos_y, float mask_alpha, HBITMAP bmp, int pos_x, int pos_y, float scale_x, float scale_y, float rot,float alpha);
void DrawTextGeneral(GameObject* this, LPCWSTR str, TCHAR* fontName, int height, int weight, COLORREF penColor, COLORREF brushColor);
void DrawTextPre(GameObject* this, LPCWSTR str, rect2D rect, UINT format, TCHAR* fontName, int height, int weight, COLORREF penColor, COLORREF brushColor);
void DrawDebugText(GameObject* this, LPCWSTR str, rect2D rect, TCHAR* fontName, int height, int weight);
HBITMAP LoadBitmapImage(wchar_t* path);
//HBITMAP LoadBitmapImage(�̹��� ���̵�);
//��Ʈ�� �̹����� HBITMAP ���·� �ε��Ѵ�. 

void DrawBitmapToDC(GameObject* this, HDC dst, HBITMAP bmp, float alpha, int pos_x, int pos_y, int scale_x,int scale_y);
void DrawDC(GameObject* this, HDC src, float alpha, int size_x, int size_y);
HDC GetMaskedDC(HDC dest, int size_x, int size_y, HBITMAP maskBMP);

Screen screen; //��ũ�� ��ü.


typedef struct Render {
	void (*Init)();
	void (*Update)(Bool*);
	void (*DrawLine)(GameObject*, int, int, int, int, COLORREF, COLORREF);
	void (*DrawRectangle)(GameObject*, int, int, COLORREF, COLORREF, float);
	void (*DrawEllipse)(GameObject*, int, int, COLORREF, COLORREF);
	void (*DrawBitmap)(GameObject*, HBITMAP, float);
	void (*DrawBitmapPreSize)(GameObject*, HBITMAP, float, int, int);
	void (*DrawBitmapPre)(GameObject*, HBITMAP, float, int, int, int, int);
	void (*DrawBitmapWithCustom)(GameObject*, HBITMAP, float, int, int, int, int);
	void (*DrawBitmapWithCoords)(GameObject*, HBITMAP, float, int, int, int, int);
	void(*DrawMaskedBitmapCoords)(GameObject* this, HBITMAP bmp, int size_x, int size_y, int _posX, int _posY,HBITMAP maskBMP);
	HBITMAP(*LoadBitmapImage)(wchar_t* path);
	void (*DrawTextGeneral)(GameObject* this, LPCWSTR str, TCHAR* fontName, int height, int weight, COLORREF penColor, COLORREF brushColor);
	void (*DrawTextPre)(GameObject* this, LPCWSTR str, rect2D rect, UINT format, TCHAR* fontName, int height, int weight, COLORREF penColor, COLORREF brushColor);
	void (*DrawDebugText)(GameObject* this, LPCWSTR str, rect2D rect, TCHAR* fontName, int height, int weight);
	void(*DrawDebugRectangle)(GameObject* this);
}Render;

extern const Render render;
//�ܺ� ��� ���� ��ü.