#include "Animation.h"

void UpdateAnimation(GameObject *this,Animation *etc)
{
	etc->index = etc->index + 1 >= etc->hBitmapList->count ? 0 : etc->index + 1;
	etc->currentBitmap = etc->hBitmapList->Content[etc->index];
}


Animation* CreateAnimation()
{
	HBITMAPList* list = CreateHBITMAPList();
	Animation* anim = (Animation*)malloc(sizeof(Animation));
	if (anim == NULL)
	{
		return NULL;
	}
	anim->index = 0;
	anim->hBitmapList = list;
	anim->hBitmapList->Content = list->Content;
	anim->Draw = DrawAnimation;
	anim->Play = PlayAnimation;
	anim->Cancel = CancelAnimation;
	anim->PushImage = PushImage;
	return anim;
}

void PlayAnimation(GameObject * this, Animation* animation,float duration, Bool loop)
{
	animation->currentBitmap = animation->hBitmapList->Content[animation->index];
	animation->animationHandler = timer.Delay(this, duration / animation->hBitmapList->count, loop, UpdateAnimation, animation);
}

void DrawAnimation(GameObject * this, Animation* animation,float alpha)
{
	render.DrawBitmap(this, animation->currentBitmap,alpha);
}

void CancelAnimation(Animation* animation)
{
	timer.Cancel(animation->animationHandler);
}
void DestoryAnimation(Animation* animation)
{
	for (int i = 0; i < animation->hBitmapList->count; i++)
	{
		DeleteObject(animation->hBitmapList->Content[i]);
	}
	free(animation->hBitmapList);
	free(animation);
}


void PushImage(Animation* animation,wchar_t* path)
{
	animation->hBitmapList->Add(animation->hBitmapList, render.LoadBitmapImage(path));
}