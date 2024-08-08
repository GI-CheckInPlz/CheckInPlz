#pragma once
#include "define.h"


typedef enum CollisionState //�ݸ��� ���� �����ϴ� ������
{
	Enter, //�� �浹�ߴ�. 
	Exit, //�� �浹 ���¿��� �����. 
	Stay, //�浹 ���°� �����ǰ� �ִ�.
	Not //�浹���� �ʰ� �ִ�.
}CollisionState;

//collision
typedef struct CollisionResponse //�浹��, �ѵ� ���¿� �Բ� �ε��� �׿������� ǥ��
{
	CollisionState state;  //�浹 ���� ��Ÿ���� ��ü.
	struct GameObject* other;  //�� �׿����� �浹�� Ÿ ���� ����.
}CollisionResponse;

CollisionResponse CheckAABB(GameObject* t, GameObject* other);
//AABB��(������ ��) �浹 üũ �Լ��̴�. 
//(�ڽ�, ��� ����) ������� ��, 
//CollisionResponse ����.

Bool GameObjectCollide(GameObject* t, struct 
GameObject* other, Bool collide);
//Bool GameObjectCollide(�׿��� �ڽ�, üũ�� ���� ������Ʈ, �浹�ߴ����� ���� Bool);
//���� CheckAABB Ȱ�� ����
//�ε������� Bool �ڷ������� �����ϴ� �Լ�

void GameObjectSetRect(GameObject* t, int size_x, int size_y);
//GameObject�� ������ ����(������)�� �����ϴ� �Լ�

void SetTag(GameObject* t, char* tag);
//void SetTag(�׿��� �ڽ�, �±�);
//���� ������Ʈ�� �±׸� �ο��Ѵ�.

extern Bool CompareTag(char*, char*);
//extern Bool CompareTag(�±�, �±�);
//�Ű����� �� ������ ��� �±װ� ����, �̰� ������ Bool������ ����.

//virtual func
void DefaultGameObjectFunction(GameObject* t);
void DefaultUpdate(GameObject* t, double dt);
void DefaultCollisionFunction(GameObject* t, CollisionResponse response);
DWORD WINAPI DefaultDrawFunction(GameObject*);
//C���� �����Լ��� �����ϴ� �����̴�.
//�� ������Ʈ���� '���' (���������δ� �Լ� ������ ������)�� ����
//Ŀ���� ���� ����.

//register
 struct GameObject {
	GameObject* t; //�� ������Ʈ
	///���⼭���� �ٸ� �׿����� c/h���� �������ؾ� �ϴ� ����.
	void (*Start)(GameObject* t);
	//�� ���۽� �ߵ��Ǵ� �Լ�
	void (*Update)(GameObject* t,double dt);
	//�� ���� ������Ʈ�Ǵ� �Լ�.
	DWORD (WINAPI *Draw)(LPVOID t);
	void (*OnDestroy)(GameObject* t);
	void (*OnEnable)(GameObject* t);
	void (*OnDisable)(GameObject* t);
	void (*OnCollisionEnter)(GameObject*, CollisionResponse);
	void (*OnCollisionExit)(GameObject* , CollisionResponse);
	void (*OnCollisionStay)(GameObject* , CollisionResponse);
	void (*SetRect)(GameObject* t, int size_x, int size_y);
	void (*SetTag)(GameObject* t, char* tag);

	Bool (*Collide)(GameObject* t, GameObject* other, Bool collided);
	//�浹�ߴ��� Bool���� �����ϴ� �Լ�, ���� ���.
	Transform transform; //Transform �� ����(2���� ��ǥ, ����, ������)
	Bool collider; //true�� �ݶ��̴��� Ű�� ��(�浹 ó�� ����)
	Bool enter;
	Bool started;
	Bool isEnabled;
	rect2D rect;  //������Ʈ�� ������ �����ϴ� rect.
	char tag[30]; //������Ʈ�� ���� �ִ� �±� ����.
	void* property; //�߰������� void �������� property, 
	//�߰� ����ü �������� �߰����� ������ Ư�� ���� ����. 
	int renderOrder;
	Bool rigidbody;
};
//


extern void Enable(GameObject* t); //���� Ȱ��ȭ
extern void Disable(GameObject* t); //���� ��Ȱ��ȭ
GameObject* CreateGameObject(); //�ܺο��� �׿��� ���� �� �����ϴ� �Լ�. 