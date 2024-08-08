#pragma once
#include "define.h"
#include "Win32Api.h"
#include "Engine.h"
#pragma comment(lib, "msimg32.lib")  //이미지 출력 위한 라이브러리

void RenderInit(); //렌더 초기화
void RenderUpdate(Bool* Drawing); //매 순간마다 렌더 업데이트. 
void DrawEllipse(GameObject* this, int size_x, int size_y, COLORREF penColor, COLORREF brushColor);
void DrawDebugRectangle(GameObject* this);
//void DrawEllipse(겜옵젝 자신 포인터, 가로 사이즈, 세로 사이즈, 펜 색깔, 브러시 색깔);
//타원/원 그리기

void DrawRectangle(GameObject* this, int size_x, int size_y, COLORREF penColor, COLORREF brushColor, float alpha);
//void DrawEllipse(겜옵젝 자신 포인터, 가로 사이즈, 세로 사이즈, 펜 색깔, 브러시 색깔);
//직사각형 그리기.

void DrawLine(GameObject* this, int start_x, int start_y, int end_x, int end_y, COLORREF penColor, COLORREF brushColor);
//void DrawLine(겜옵젝 자신 포인터, 선 X축 스타트 지점, 선 Y축 스타트 지점, 
//X축 끝 지점, Y축 끝 지점, 펜 색깔, 브러시 색깔);
//줄 긋기

void DrawBitmap(GameObject* this, HBITMAP image, float alpha);
//void DrawBitmap(겜옵젝 자신 포인터, 이미지 아이디 (#define 유리));
//Bitmap 이미지 그린다. 
void DrawBitmapPre(GameObject*, HBITMAP, float, int, int, int, int);

//DrawBitmapPreSize와 유사, 하지만, 두번째 마지막, 마지막 인자에 x 오프셋, y 오프셋을 넣을 수 있음.
void DrawBitmapWithCustom(GameObject*, HBITMAP, float, int, int, int, int);

//DrawBitmapPreSize와 유사, 하지만, 두번째 마지막, 마지막 인자에 x 좌표, y 좌표를 넣을 수 있음.
void DrawBitmapWithCoords(GameObject* this, HBITMAP bmp, float alpha, int size_x, int size_y, int _posX, int _posY);

//마스킹 처리된 비트맵을 후반부의 좌표에 출력한다.
void DrawMaskedBitmapCoords(GameObject* this, HBITMAP maskBMP, float mask_size_x, float mask_size_y, int mask_pos_x, int mask_pos_y, float mask_alpha, HBITMAP bmp, int pos_x, int pos_y, float scale_x, float scale_y, float alpha);
void DrawMaskedBitmapCoordsM(GameObject* this, HBITMAP maskBMP, float mask_size_x, float mask_size_y, int mask_pos_x, int mask_pos_y, float mask_alpha, HBITMAP bmp, int pos_x, int pos_y, float scale_x, float scale_y, float rot,float alpha);
void DrawTextGeneral(GameObject* this, LPCWSTR str, TCHAR* fontName, int height, int weight, COLORREF penColor, COLORREF brushColor);
void DrawTextPre(GameObject* this, LPCWSTR str, rect2D rect, UINT format, TCHAR* fontName, int height, int weight, COLORREF penColor, COLORREF brushColor);
void DrawDebugText(GameObject* this, LPCWSTR str, rect2D rect, TCHAR* fontName, int height, int weight);
HBITMAP LoadBitmapImage(wchar_t* path);
//HBITMAP LoadBitmapImage(이미지 아이디);
//비트맵 이미지를 HBITMAP 형태로 로드한다. 

void DrawBitmapToDC(GameObject* this, HDC dst, HBITMAP bmp, float alpha, int pos_x, int pos_y, int scale_x,int scale_y);
void DrawDC(GameObject* this, HDC src, float alpha, int size_x, int size_y);
HDC GetMaskedDC(HDC dest, int size_x, int size_y, HBITMAP maskBMP);

Screen screen; //스크린 객체.


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
//외부 사용 위한 객체.