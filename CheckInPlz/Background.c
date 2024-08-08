#include "Background.h"
#include "vmath.h"


GameObject* CreateBackground()
{
	Transform transform = { {0, 0}, 0, {1,1} };
	PropBackground* property = (PropBackground*)malloc(sizeof(PropBackground));
	if (property == NULL)
	{
		return NULL;
	}
	property->sprite = render.LoadBitmapImage(L"Resources\\Map\\Background.bmp");
	GameObject* obj = CreateGameObject();
	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Draw = DrawBackground;
	obj->renderOrder = 0;
	obj->property = property;
	obj->OnDestroy = BackgroundOnDestroy;

	return obj;
}

void DrawBackgroundImage(GameObject* this, HBITMAP bmp, float alpha, int pos_x, int pos_y, int size_x, int size_y)
{
	HDC tmp;
	static HDC tmpAlpha;
	//HBITMAP OldBit = (HBITMAP)SelectObject(MemDC, hBit);
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

	BitBlt(tmpAlpha, 0, 0, size_x, size_y, MemDC, pos_x, pos_y, SRCCOPY);
	//TransparentBlt(tmpAlpha, 0, 0, size_x, size_y, tmp, 0, 0, btSize.bmWidth, btSize.bmHeight, RGB(255, 0, 255));
	BitBlt(tmpAlpha, 0, 0, size_x, size_y, tmp, 0, 0, SRCCOPY);
	BitBlt(MemDC, pos_x, pos_y, size_x, size_y, tmpAlpha, 0, 0, SRCCOPY);
	
	SelectObject(tmp, hOldBitmap);
	DeleteObject(tBit);
	DeleteDC(tmp);
	DeleteDC(tmpAlpha);
}

DWORD WINAPI DrawBackground(GameObject* this)
{
	PropBackground* prop = this->property;
	DrawBackgroundImage(this, prop->sprite, 1, 960, 500, 1920, 1080);

	return 0;
}

void BackgroundOnDestroy(GameObject* this)
{
	free(this->property);
}