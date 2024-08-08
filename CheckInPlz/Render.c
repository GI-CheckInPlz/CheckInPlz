#include "Render.h"
HBITMAP GetRotatedBitmap(HDC hdc, HBITMAP hBitmap, int source_x, int source_y, int dest_width, int dest_height, float angle)
{
	HDC sourceDC = CreateCompatibleDC(hdc);
	HDC destDC = CreateCompatibleDC(hdc);
	HBITMAP hbmResult = CreateCompatibleBitmap(hdc, dest_width, dest_height);
	HBITMAP hbmOldSource = (HBITMAP)SelectObject(sourceDC, hBitmap);
	HBITMAP hbmOldDest = (HBITMAP)SelectObject(destDC, hbmResult);
	HBRUSH hbrBack = CreateSolidBrush(RGB(255, 0, 255));
	HBRUSH hbrOld = (HBRUSH)SelectObject(destDC, hbrBack);
	PatBlt(destDC, 0, 0, dest_width, dest_height, PATCOPY);
	DeleteObject(SelectObject(destDC, hbrOld));
	angle = (float)(angle * PI / 180);
	float cosine = (float)cos(angle);
	float sine = (float)sin(angle);

	SetGraphicsMode(destDC, GM_ADVANCED);

	XFORM xform;
	xform.eM11 = cosine;
	xform.eM12 = sine;
	xform.eM21 = -sine;
	xform.eM22 = cosine;
	xform.eDx = (FLOAT)dest_width / 2.0f;
	xform.eDy = (FLOAT)dest_height / 2.0f;

	SetWorldTransform(destDC, &xform);
	BitBlt(destDC, -(dest_width / 2), -(dest_height / 2), dest_width, dest_height, sourceDC, source_x, source_y, SRCCOPY);


	SelectObject(sourceDC, hbmOldSource);
	SelectObject(destDC, hbmOldDest);
	DeleteObject(sourceDC);
	DeleteObject(destDC);
	return hbmResult;
}

void DrawEllipse(GameObject* this, int size_x, int size_y, COLORREF penColor, COLORREF brushColor)
{

	HPEN hNewPen = CreatePen(PS_SOLID, 1, penColor);
	HPEN hOldPen = (HPEN)SelectObject(MemDC, hNewPen);

	HBRUSH hNewBrush = CreateSolidBrush(brushColor);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(MemDC, hNewBrush);

	Transform transform = this->transform;
	vector2 pos = { transform.position.x ,transform.position.y };
	vector2 size = { size_x * transform.scale.x, size_y * transform.scale.x };
	Ellipse(MemDC, (int)(pos.x - size.x / 2), (int)(pos.y - size.y / 2), (int)(pos.x + size.x / 2), (int)(pos.y + size.y / 2));

	SelectObject(MemDC, hOldPen);
	DeleteObject(hNewPen);

	SelectObject(MemDC, hOldBrush);
	DeleteObject(hNewBrush);
}




void DrawLine(GameObject* this, int start_x, int start_y, int end_x, int end_y, COLORREF penColor, COLORREF brushColor)
{
	int radius = 10;
	HPEN hNewPen = CreatePen(PS_SOLID, 1, penColor);
	HPEN hOldPen = (HPEN)SelectObject(MemDC, hNewPen);

	HBRUSH hNewBrush = CreateSolidBrush(brushColor);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(MemDC, hNewBrush);

	Transform transform = this->transform;
	vector2 pos = { transform.position.x ,transform.position.y };

	MoveToEx(MemDC, start_x, start_y, NULL);
	LineTo(MemDC, end_x, end_y);

	SelectObject(MemDC, hOldPen);
	DeleteObject(hNewPen);

	SelectObject(MemDC, hOldBrush);
	DeleteObject(hNewBrush);
}

void DrawDebugText(GameObject* this, LPCWSTR str, rect2D rect, TCHAR* fontName, int height, int weight)
{
	HFONT hFont = CreateFont(height, 0, 0, 0,weight,0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, fontName);
	HFONT hOldFont = (HFONT)SelectObject(MemDC, hFont);
	Transform transform = this->transform;
	vector2 pos = { transform.position.x ,transform.position.y };
	RECT r = { (long)(transform.position.x + rect.min.x),(long)(transform.position.y + rect.min.y),(long)(transform.position.x + rect.max.x),(long)(transform.position.y + rect.max.y) };
	SetTextColor(MemDC, RGB(255,0,0));
	SetBkColor(MemDC, RGB(0, 0, 0));
	SetBkMode(MemDC, OPAQUE);
	DrawText(MemDC, str, -1, &r, DT_CENTER | DT_WORDBREAK);
	SelectObject(MemDC, hOldFont);
	DeleteObject(hFont);
}

void DrawTextGeneral(GameObject* this, LPCWSTR str,TCHAR* fontName, int height, int weight, COLORREF textColor, COLORREF bkColor)
{
	HFONT hFont = CreateFont(height, 0, 0, 0, weight, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, fontName);
	HFONT hOldFont = (HFONT)SelectObject(MemDC, hFont);

	Transform transform = this->transform;
	vector2 pos = { transform.position.x ,transform.position.y };
	RECT r = { (long)(transform.position.x + this->rect.min.x),(long)(transform.position.y + this->rect.min.y),(long)(transform.position.x + this->rect.max.x),(long)(transform.position.y + this->rect.max.y) };
	SetTextColor(MemDC, textColor);
	SetBkColor(MemDC, bkColor);
	SetBkMode(MemDC, TRANSPARENT);
	DrawText(MemDC, str, -1, &r, DT_CENTER | DT_WORDBREAK);

	SelectObject(MemDC, hOldFont);
	DeleteObject(hFont);
}
void DrawTextPre(GameObject* this, LPCWSTR str, rect2D rect, UINT format, TCHAR* fontName, int height, int weight, COLORREF textColor, COLORREF bkColor)
{

	HFONT hFont = CreateFont(height, 0, 0, 0, weight, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, fontName);
	HFONT hOldFont = (HFONT)SelectObject(MemDC, hFont);

	Transform transform = this->transform;
	vector2 pos = { transform.position.x ,transform.position.y };
	RECT r = { (long)(transform.position.x + rect.min.x),(long)(transform.position.y + rect.min.y),(long)(transform.position.x + rect.max.x),(long)(transform.position.y + rect.max.y) };
	SetTextColor(MemDC, textColor);
	SetBkColor(MemDC, bkColor);
	SetBkMode(MemDC, TRANSPARENT);
	DrawText(MemDC, str, -1, &r, format);

	SelectObject(MemDC, hOldFont);
	DeleteObject(hFont);
}

HBITMAP LoadBitmapImage(wchar_t* path)
{
	return (HBITMAP)LoadImage(m_hInstance, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
}

void DrawBitmap(GameObject* this, HBITMAP bmp, float alpha)
{
	if (alpha > 0)
	{
		HDC tmp;
		HDC tmpAlpha;
		HBITMAP OldBit = (HBITMAP)SelectObject(MemDC, hBit);
		BITMAP btSize;
		HBITMAP tBit;
		HBITMAP hTempBitmap, hOldBitmap;
		tmp = CreateCompatibleDC(hdc);
		tmpAlpha = CreateCompatibleDC(hdc);

		GetObject(bmp, sizeof(BITMAP), &(btSize));
		tBit = CreateCompatibleBitmap(hdc, (int)(screen.resolution.x), (int)(screen.resolution.y));
		SelectObject(tmpAlpha, tBit);
		int size_x = (int)(btSize.bmWidth * this->transform.scale.x);
		int size_y = (int)(btSize.bmHeight * this->transform.scale.y);
		hTempBitmap = GetRotatedBitmap(hdc, bmp, 0, 0, btSize.bmWidth, btSize.bmHeight, this->transform.rotation);
		hOldBitmap = (HBITMAP)SelectObject(tmp, hTempBitmap);

		int pos_x = (int)(this->transform.position.x - size_x / 2);
		int pos_y = (int)(this->transform.position.y - size_y / 2);

		BLENDFUNCTION bf;
		bf.AlphaFormat = 0; // 비트맵 종류로 일반 비트맵의 경우 0, 32비트 비트맵의 경우 AC_SRC_ALPHA
		bf.BlendFlags = 0; // 무조건 0이어야 한다
		bf.BlendOp = AC_SRC_OVER; // 무조건 AC_SRC_OVER이어야 하고 원본과 대상 이미지를 합친다는 의미
		bf.SourceConstantAlpha = 255 * alpha; // 투명도(투명 0 - 불투명 255)
		BitBlt(tmpAlpha, 0, 0, size_x, size_y, MemDC, pos_x, pos_y, SRCCOPY);
		TransparentBlt(tmpAlpha, 0, 0, size_x, size_y, tmp, 0, 0, btSize.bmWidth, btSize.bmHeight, RGB(255, 0, 255));
		if (alpha < 1)
		{
			AlphaBlend(MemDC, pos_x, pos_y, size_x, size_y, tmpAlpha, 0, 0, size_x, size_y, bf);
		}
		else
		{
			BitBlt(MemDC, pos_x, pos_y, size_x, size_y, tmpAlpha, 0, 0, SRCCOPY);
		}
		SelectObject(tmp, hOldBitmap);
		DeleteObject(hTempBitmap);
		DeleteObject(tBit);
		DeleteDC(tmp);
		DeleteDC(tmpAlpha);


	}
	
}

void DrawRectangle(GameObject* this, int size_x, int size_y, COLORREF penColor, COLORREF brushColor, float alpha)
{
	if (alpha > 0)
	{
		HDC tmp;
		HBITMAP tBit;
		tmp = CreateCompatibleDC(hdc);
		tBit = CreateCompatibleBitmap(hdc, (int)(screen.resolution.x), (int)(screen.resolution.y));
		SelectObject(tmp, tBit);
		HPEN hNewPen = CreatePen(PS_SOLID, 1, penColor);
		HPEN hOldPen = (HPEN)SelectObject(tmp, hNewPen);

		HBRUSH hNewBrush = CreateSolidBrush(brushColor);
		HBRUSH hOldBrush = (HBRUSH)SelectObject(tmp, hNewBrush);

		Transform transform = this->transform;
		vector2 pos = { transform.position.x ,transform.position.y };
		vector2 size = { size_x * transform.scale.x, size_y * transform.scale.x };
		Rectangle(tmp, 0, 0, (int)(size.x), (int)(pos.y + size.y));
		BLENDFUNCTION bf;
		bf.AlphaFormat = 0; // 비트맵 종류로 일반 비트맵의 경우 0, 32비트 비트맵의 경우 AC_SRC_ALPHA
		bf.BlendFlags = 0; // 무조건 0이어야 한다
		bf.BlendOp = AC_SRC_OVER; // 무조건 AC_SRC_OVER이어야 하고 원본과 대상 이미지를 합친다는 의미
		bf.SourceConstantAlpha = 255 * alpha; // 투명도(투명 0 - 불투명 255)

		if (alpha < 1)
		{
			AlphaBlend(MemDC, (int)(pos.x - size.x / 2), (int)(pos.y - size.y / 2), (int)(size.x), (int)(size.y), tmp, 0, 0, (int)(size.x), (int)(size.y), bf);
		}
		else
		{
			BitBlt(MemDC, (int)(pos.x - size.x / 2), (int)(pos.y - size.y / 2), (int)(size.x), (int)(size.y), tmp, 0, 0, SRCCOPY);
		}


		SelectObject(tmp, hOldPen);
		DeleteObject(hNewPen);
		SelectObject(tmp, hOldBrush);
		DeleteObject(hNewBrush);
		DeleteObject(tBit);
		DeleteDC(tmp);
	}
}


void DrawBitmapWithCustom(GameObject* this, HBITMAP bmp, float alpha, int size_x, int size_y, int xOffset, int yOffset)
{
	if (alpha > 0)
	{
		HDC tmp;
		HDC tmpAlpha;
		HBITMAP OldBit = (HBITMAP)SelectObject(MemDC, hBit);
		BITMAP btSize;
		HBITMAP tBit;
		HBITMAP hOldBitmap;
		

		tmp = CreateCompatibleDC(hdc);
		tmpAlpha = CreateCompatibleDC(hdc);

		GetObject(bmp, sizeof(BITMAP), &(btSize));
		tBit = CreateCompatibleBitmap(hdc, (int)(screen.resolution.x), (int)(screen.resolution.y));
		SelectObject(tmpAlpha, tBit);
		hOldBitmap = (HBITMAP)SelectObject(tmp, bmp);

		int pos_x = (int)(this->transform.position.x - size_x / 2) + xOffset;
		int pos_y = (int)(this->transform.position.y - size_y / 2) + yOffset;

		BLENDFUNCTION bf;
		bf.AlphaFormat = 0; // 비트맵 종류로 일반 비트맵의 경우 0, 32비트 비트맵의 경우 AC_SRC_ALPHA
		bf.BlendFlags = 0; // 무조건 0이어야 한다
		bf.BlendOp = AC_SRC_OVER; // 무조건 AC_SRC_OVER이어야 하고 원본과 대상 이미지를 합친다는 의미
		bf.SourceConstantAlpha = 255 * alpha; // 투명도(투명 0 - 불투명 255)
		BitBlt(tmpAlpha, 0, 0, size_x, size_y, MemDC, pos_x, pos_y, SRCCOPY);
		TransparentBlt(tmpAlpha, 0, 0, size_x, size_y, tmp, 0, 0, btSize.bmWidth, btSize.bmHeight, RGB(255, 0, 255));
		if (alpha < 1)
		{
			AlphaBlend(MemDC, pos_x, pos_y, size_x, size_y, tmpAlpha, 0, 0, size_x, size_y, bf);
		}
		else
		{
			BitBlt(MemDC, pos_x, pos_y, size_x, size_y, tmpAlpha, 0, 0, SRCCOPY);
		}
		SelectObject(tmp, hOldBitmap);
		DeleteObject(tBit);
		DeleteDC(tmp);
		DeleteDC(tmpAlpha);
	}
}

void DrawBitmapWithCoords(GameObject* this, HBITMAP bmp, float alpha, int size_x, int size_y, int _posX, int _posY)
{
	if (alpha > 0)
	{
		HDC tmp;
		HDC tmpAlpha;
		HBITMAP OldBit = (HBITMAP)SelectObject(MemDC, hBit);
		BITMAP btSize;
		HBITMAP tBit;
		//HBITMAP hOldBitmap;


		tmp = CreateCompatibleDC(hdc);
		tmpAlpha = CreateCompatibleDC(hdc);

		GetObject(bmp, sizeof(BITMAP), &(btSize));
		tBit = CreateCompatibleBitmap(hdc, (int)(screen.resolution.x), (int)(screen.resolution.y));
		SelectObject(tmpAlpha, tBit);
		

		int pos_x = _posX - size_x / 2;
		int pos_y = _posY - size_y / 2;

		BLENDFUNCTION bf;
		bf.AlphaFormat = 0; // 비트맵 종류로 일반 비트맵의 경우 0, 32비트 비트맵의 경우 AC_SRC_ALPHA
		bf.BlendFlags = 0; // 무조건 0이어야 한다
		bf.BlendOp = AC_SRC_OVER; // 무조건 AC_SRC_OVER이어야 하고 원본과 대상 이미지를 합친다는 의미
		bf.SourceConstantAlpha = 255 * alpha; // 투명도(투명 0 - 불투명 255)
		BitBlt(tmpAlpha, 0, 0, size_x, size_y, MemDC, pos_x, pos_y, SRCCOPY);
		TransparentBlt(tmpAlpha, 0, 0, size_x, size_y, tmp, 0, 0, btSize.bmWidth, btSize.bmHeight, RGB(255, 0, 255));
		if (alpha < 1)
		{
			AlphaBlend(MemDC, pos_x, pos_y, size_x, size_y, tmpAlpha, 0, 0, size_x, size_y, bf);
		}
		else
		{
			BitBlt(MemDC, pos_x, pos_y, size_x, size_y, tmpAlpha, 0, 0, SRCCOPY);
		}
		DeleteObject(tBit);
		DeleteDC(tmp);
		DeleteDC(tmpAlpha);
	}
}





void DrawBitmapPreSize(GameObject* this, HBITMAP bmp, float alpha, int size_x, int size_y)
{
	if (alpha > 0)
	{
		HDC tmp;
		HDC tmpAlpha;
		HBITMAP OldBit = (HBITMAP)SelectObject(MemDC, hBit);
		BITMAP btSize;
		HBITMAP tBit;
		HBITMAP hOldBitmap;
		tmp = CreateCompatibleDC(hdc);
		tmpAlpha = CreateCompatibleDC(hdc);

		GetObject(bmp, sizeof(BITMAP), &(btSize));
		tBit = CreateCompatibleBitmap(hdc, (int)(screen.resolution.x), (int)(screen.resolution.y));
		SelectObject(tmpAlpha, tBit);
		hOldBitmap = (HBITMAP)SelectObject(tmp, bmp);

		int pos_x = (int)(this->transform.position.x - size_x / 2);
		int pos_y = (int)(this->transform.position.y - size_y / 2);

		BLENDFUNCTION bf;
		bf.AlphaFormat = 0; // 비트맵 종류로 일반 비트맵의 경우 0, 32비트 비트맵의 경우 AC_SRC_ALPHA
		bf.BlendFlags = 0; // 무조건 0이어야 한다
		bf.BlendOp = AC_SRC_OVER; // 무조건 AC_SRC_OVER이어야 하고 원본과 대상 이미지를 합친다는 의미
		bf.SourceConstantAlpha = 255 * alpha; // 투명도(투명 0 - 불투명 255)
		BitBlt(tmpAlpha, 0, 0, size_x, size_y, MemDC, pos_x, pos_y, SRCCOPY);
		TransparentBlt(tmpAlpha, 0, 0, size_x, size_y, tmp, 0, 0, btSize.bmWidth, btSize.bmHeight, RGB(255, 0, 255));


		if (alpha < 1)
		{
			AlphaBlend(MemDC, pos_x, pos_y, size_x, size_y, tmpAlpha, 0, 0, size_x, size_y, bf);
		}
		else
		{
			BitBlt(MemDC, pos_x, pos_y, size_x, size_y, tmpAlpha, 0, 0, SRCCOPY);
		}

		SelectObject(tmp, hOldBitmap);
		DeleteObject(tBit);
		DeleteDC(tmp);
		DeleteDC(tmpAlpha);
	}
}


HDC GetMaskedDC(HDC dest, int size_x, int size_y, HBITMAP maskBMP)
{
	HDC tmpMasked, maskDC;
	HBITMAP /*hOldBitmap,*/ hOldMaskBitMap;
	HBITMAP tBit;

	tmpMasked = CreateCompatibleDC(hdc);
	maskDC = CreateCompatibleDC(hdc);
	tBit = CreateCompatibleBitmap(hdc, (int)(screen.resolution.x), (int)(screen.resolution.y));
	SelectObject(tmpMasked, tBit);

	hOldMaskBitMap = (HBITMAP)SelectObject(maskDC, maskBMP);



	BitBlt(tmpMasked, 0, 0, size_x, size_y, dest, 0, 0, SRCINVERT);
	BitBlt(tmpMasked, 0, 0, size_x, size_y, maskDC, 0, 0, SRCAND);
	BitBlt(tmpMasked, 0, 0, size_x, size_y, dest, 0, 0, SRCINVERT);

	SelectObject(maskDC, hOldMaskBitMap);
	DeleteObject(tBit);
	DeleteDC(maskDC);
	return tmpMasked;
}
void DrawMaskedBitmapCoordsM(GameObject* this, HBITMAP maskBMP, float mask_size_x, float mask_size_y, int mask_pos_x, int mask_pos_y, float mask_alpha, HBITMAP bmp, int pos_x, int pos_y, float scale_x, float scale_y, float rotation, float alpha)
{
	HDC tmp, tmpMasked, maskDC;
	HBITMAP hOldBitmap, hOldMaskBitMap;
	BITMAP btSize;

	HBITMAP tBit1, tBit2, tBit3;
	HDC tmpAlpha1, tmpAlpha2;

	HBITMAP hTempBitmap;



	tmpAlpha1 = CreateCompatibleDC(hdc);
	tmpAlpha2 = CreateCompatibleDC(hdc);
	tmp = CreateCompatibleDC(hdc);
	tmpMasked = CreateCompatibleDC(hdc);
	maskDC = CreateCompatibleDC(hdc);
	tBit1 = CreateCompatibleBitmap(hdc, (int)(screen.resolution.x), (int)(screen.resolution.y));
	tBit2 = CreateCompatibleBitmap(hdc, (int)(screen.resolution.x), (int)(screen.resolution.y));
	tBit3 = CreateCompatibleBitmap(hdc, (int)(screen.resolution.x), (int)(screen.resolution.y));
	SelectObject(tmpMasked, tBit1);
	SelectObject(tmpAlpha1, tBit2);
	SelectObject(tmpAlpha2, tBit3);
	GetObject(bmp, sizeof(BITMAP), &(btSize));
	//hOldBitmap = (HBITMAP)SelectObject(tmp, bmp);
	hTempBitmap = GetRotatedBitmap(hdc, bmp, 0, 0, btSize.bmWidth, btSize.bmHeight, rotation);
	hOldBitmap = (HBITMAP)SelectObject(tmp, hTempBitmap);

	hOldMaskBitMap = (HBITMAP)SelectObject(maskDC, maskBMP);

	TransparentBlt(tmpAlpha1, 0, 0, btSize.bmWidth , btSize.bmHeight, tmp, 0, 0, btSize.bmWidth, btSize.bmHeight, RGB(255, 0, 255));


	BitBlt(tmpMasked, pos_x, pos_y, btSize.bmWidth, btSize.bmHeight, tmpAlpha1, 0, 0, SRCINVERT);

	BitBlt(tmpMasked, 0, 0, 900, 500, maskDC, 0, 0, SRCAND);

	BitBlt(tmpMasked, pos_x, pos_y, btSize.bmWidth, btSize.bmHeight, tmpAlpha1, 0, 0, SRCINVERT);

	//BitBlt(MemDC, _posX, _posY, size_x, size_y, tmpMasked, 0, 0, SRCCOPY);

	BitBlt(tmpAlpha2, 0, 0, (int)mask_size_x, (int)mask_size_y, MemDC, (int)(mask_pos_x - mask_size_x / 2), (int)(mask_pos_y - mask_size_y / 2), SRCCOPY);

	

	TransparentBlt(tmpAlpha2, 0, 0, (int)(mask_size_x), (int)(mask_size_y), tmpMasked, 0, 0, 900, 500, RGB(0, 0, 0));



	BLENDFUNCTION bf;
	bf.AlphaFormat = 0; // 비트맵 종류로 일반 비트맵의 경우 0, 32비트 비트맵의 경우 AC_SRC_ALPHA
	bf.BlendFlags = 0; // 무조건 0이어야 한다
	bf.BlendOp = AC_SRC_OVER; // 무조건 AC_SRC_OVER이어야 하고 원본과 대상 이미지를 합친다는 의미
	bf.SourceConstantAlpha = 255 * alpha; // 투명도(투명 0 - 불투명 255)

	if (alpha < 1)
	{
		AlphaBlend(MemDC, (int)(mask_pos_x - mask_size_x / 2), (int)(mask_pos_y - mask_size_y / 2), (int)(mask_size_x), (int)(mask_size_y), tmpAlpha2, 0, 0, (int)(mask_size_x), (int)(mask_size_y), bf);
	}
	else
	{
		BitBlt(MemDC, (int)(mask_pos_x - mask_size_x / 2), (int)(mask_pos_y - mask_size_y / 2), (int)(mask_size_x), (int)(mask_size_y), tmpAlpha2, 0, 0, SRCCOPY);
	}

	
	
	SelectObject(tmp, hOldBitmap);
	DeleteObject(hTempBitmap);
	SelectObject(maskDC, hOldMaskBitMap);
	DeleteObject(tBit1);
	DeleteObject(tBit2);
	DeleteObject(tBit3);
	DeleteDC(tmp);
	DeleteDC(tmpMasked);
	DeleteDC(tmpAlpha1);
	DeleteDC(tmpAlpha2);
	DeleteDC(maskDC);
}
void DrawMaskedBitmapCoords(GameObject* this, HBITMAP maskBMP, float mask_size_x, float mask_size_y, int mask_pos_x, int mask_pos_y, float mask_alpha, HBITMAP bmp, int pos_x,int pos_y, float scale_x,float scale_y, float alpha)
{
	HDC tmp, tmpMasked, maskDC;
	HBITMAP hOldBitmap, hOldMaskBitMap;
	BITMAP btSize;

	HBITMAP tBit1,tBit2/*,tBit3*/;
	HDC tmpAlpha1;
	tmpAlpha1 = CreateCompatibleDC(hdc);
	tmp = CreateCompatibleDC(hdc);
	tmpMasked = CreateCompatibleDC(hdc);
	maskDC = CreateCompatibleDC(hdc);
	tBit1 = CreateCompatibleBitmap(hdc, (int)(screen.resolution.x), (int)(screen.resolution.y));
	tBit2= CreateCompatibleBitmap(hdc, (int)(screen.resolution.x), (int)(screen.resolution.y));
	SelectObject(tmpMasked, tBit1);
	SelectObject(tmpAlpha1, tBit2);

	GetObject(bmp, sizeof(BITMAP), &(btSize));
	hOldBitmap = (HBITMAP)SelectObject(tmp, bmp);
	hOldMaskBitMap = (HBITMAP)SelectObject(maskDC, maskBMP);


	BitBlt(tmpMasked, pos_x, pos_y, btSize.bmWidth, btSize.bmHeight, tmp, 0, 0, SRCINVERT);

	BitBlt(tmpMasked, 0, 0, 900, 500, maskDC, 0, 0, SRCAND);

	BitBlt(tmpMasked, pos_x, pos_y, btSize.bmWidth, btSize.bmHeight, tmp, 0, 0, SRCINVERT);

	//BitBlt(MemDC, _posX, _posY, size_x, size_y, tmpMasked, 0, 0, SRCCOPY);
	BitBlt(tmpAlpha1, 0, 0, (int)(mask_size_x), (int)(mask_size_y), MemDC, (int)(mask_pos_x - mask_size_x / 2), (int)(mask_pos_y - mask_size_y / 2), SRCCOPY);

	//BitBlt(tmpAlpha2, 0, 0, mask_size_x, mask_size_y, MemDC, mask_pos_x - mask_size_x / 2, mask_pos_y - mask_size_y / 2, SRCCOPY);
	
	TransparentBlt(tmpAlpha1,0, 0, (int)(mask_size_x), (int)(mask_size_y), tmpMasked, 0, 0, 900, 500, RGB(0, 0, 0));


	BLENDFUNCTION bf;
	bf.AlphaFormat = 0; // 비트맵 종류로 일반 비트맵의 경우 0, 32비트 비트맵의 경우 AC_SRC_ALPHA
	bf.BlendFlags = 0; // 무조건 0이어야 한다
	bf.BlendOp = AC_SRC_OVER; // 무조건 AC_SRC_OVER이어야 하고 원본과 대상 이미지를 합친다는 의미
	bf.SourceConstantAlpha = 255 * alpha; // 투명도(투명 0 - 불투명 255)

	if (alpha < 1)
	{
		AlphaBlend(MemDC, (int)(mask_pos_x- mask_size_x/2), (int)(mask_pos_y- mask_size_y / 2), (int)(mask_size_x), (int)(mask_size_y), tmpAlpha1, 0, 0, (int)(mask_size_x), (int)(mask_size_y), bf);
	}
	else
	{
		BitBlt(MemDC, (int)(mask_pos_x - mask_size_x / 2), (int)(mask_pos_y - mask_size_y / 2), (int)(mask_size_x), (int)(mask_size_y), tmpAlpha1, 0, 0, SRCCOPY);
	}

	SelectObject(tmp, hOldBitmap);
	SelectObject(maskDC, hOldMaskBitMap);
	DeleteObject(tBit1);
	DeleteObject(tBit2);
	DeleteDC(tmp);
	DeleteDC(tmpMasked);
	DeleteDC(tmpAlpha1);
	DeleteDC(maskDC);
}


void DrawDebugRectangle(GameObject* this)
{
	int radius = 10;
	HPEN hNewPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HPEN hOldPen = (HPEN)SelectObject(MemDC, hNewPen);

	HBRUSH hNewBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(MemDC, hNewBrush);

	Transform transform = this->transform;
	vector2 pos = { transform.position.x ,transform.position.y };
	vector2 size = { (this->rect.max.x - this->rect.min.x) * this->transform.scale.x, (this->rect.max.y - this->rect.min.y) * this->transform.scale.y };
	Rectangle(MemDC, (int)(pos.x - size.x / 2), (int)(pos.y - size.y / 2), (int)(pos.x + size.x / 2), (int)(pos.y + size.y / 2));

	SelectObject(MemDC, hOldPen);
	DeleteObject(hNewPen);

	SelectObject(MemDC, hOldBrush);
	DeleteObject(hNewBrush);
}

void DrawBitmapPre(GameObject* this, HBITMAP bmp, float alpha, int pos_x, int pos_y, int size_x, int size_y)
{
	if (alpha > 0)
	{
		HDC tmp;
		HDC tmpAlpha;
		HBITMAP OldBit = (HBITMAP)SelectObject(hdc, hBit);
		BITMAP btSize;
		HBITMAP tBit;
		HBITMAP hOldBitmap;
		tmp = CreateCompatibleDC(hdc);
		tmpAlpha = CreateCompatibleDC(hdc);

		GetObject(bmp, sizeof(BITMAP), &(btSize));
		tBit = CreateCompatibleBitmap(hdc, (int)(screen.resolution.x), (int)(screen.resolution.y));
		SelectObject(tmpAlpha, tBit);
		hOldBitmap = (HBITMAP)SelectObject(tmp, bmp);

		pos_x = pos_x - size_x / 2;
		pos_y = pos_y - size_y / 2;

		BLENDFUNCTION bf;
		bf.AlphaFormat = 0; // 비트맵 종류로 일반 비트맵의 경우 0, 32비트 비트맵의 경우 AC_SRC_ALPHA
		bf.BlendFlags = 0; // 무조건 0이어야 한다
		bf.BlendOp = AC_SRC_OVER; // 무조건 AC_SRC_OVER이어야 하고 원본과 대상 이미지를 합친다는 의미
		bf.SourceConstantAlpha = 255 * alpha; // 투명도(투명 0 - 불투명 255)
		BitBlt(tmpAlpha, 0, 0, size_x, size_y, MemDC, pos_x, pos_y, SRCCOPY);
		TransparentBlt(tmpAlpha, 0, 0, size_x, size_y, tmp, 0, 0, btSize.bmWidth, btSize.bmHeight, RGB(255, 0, 255));

		if (alpha < 1)
		{
			AlphaBlend(MemDC, pos_x, pos_y, size_x, size_y, tmpAlpha, 0, 0, size_x, size_y, bf);
		}
		else
		{
			BitBlt(MemDC, pos_x, pos_y, size_x, size_y, tmpAlpha, 0, 0, SRCCOPY);
		}

		SelectObject(tmp, hOldBitmap);
		DeleteObject(tBit);
		DeleteDC(tmp);
		DeleteDC(tmpAlpha);
	}
}


void RenderInit()
{
	AddFontResource(L"Resources\\Font\\CinzelDecorative-Black.ttf");
	AddFontResource(L"Resources\\Font\\CinzelDecorative-Bold.ttf");
	//SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);
	SetWindowPos(m_hWnd, NULL, 0, 0, (int)(screen.resolution.x), (int)(screen.resolution.y), 0);
	SetMenu(m_hWnd, NULL);
	hdc = GetDC(m_hWnd);
	hBit = CreateCompatibleBitmap(hdc, (int)(screen.resolution.x), (int)(screen.resolution.y));
	MemDC = CreateCompatibleDC(hdc);
	PreMemDC = CreateCompatibleDC(hdc);
	HBITMAP OldBit = (HBITMAP)SelectObject(MemDC, hBit);
	OldBit = (HBITMAP)SelectObject(PreMemDC, hBit);
	DeleteObject(OldBit);
}

void RenderUpdate(Bool* Drawing)
{
	Rectangle(MemDC, -1, -1, (int)(screen.resolution.x + 1), (int)(screen.resolution.y + 1));
	EngineDraw(Drawing);
	BitBlt(hdc, 0, 0, (int)(screen.resolution.x), (int)(screen.resolution.y), MemDC, 0, 0, SRCCOPY);
	InvalidateRect(m_hWnd, NULL, false);
}

const Render render = {
	RenderInit,
	RenderUpdate,
	DrawLine,
	DrawRectangle,
	DrawEllipse,
	DrawBitmap,
	DrawBitmapPreSize,
	DrawBitmapPre,
	DrawBitmapWithCustom,
	DrawBitmapWithCoords,
	DrawMaskedBitmapCoords,
	LoadBitmapImage,
	DrawTextGeneral,
	DrawTextPre,
	DrawDebugText,
	DrawDebugRectangle
};
/*DrawMaskedBitmap,*/