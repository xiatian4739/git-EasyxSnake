#pragma once
#define Widht 900			//����Ŀ���
#define Hight  500 
#define sankeRadius 5			//�ߵİ뾶
#define Initlength	 3				//�ߵĳ�ʼ����
/************************************
	��Ŀ��̰���ߣ�
	ͼ�ι��ߣ�Easxy
************************************/
enum dir			//���������ߵķ���
{
	UP = 1, Down = 2, Right = 3, Left = 4
};
//����߽ṹ
typedef struct Sanke
{
	int x;				//�ߵ�����
	int y;
	bool sankeHead;		//�����ж��ǲ�����ͷ������ͷ����ͷ��ɺ�ɫ�������Ǿͻ�ɫ
	dir move;
	struct Sanke* next;		//��һ������
}Sanke,*pSanke;

//���ʳ��ṹ
typedef struct food
{
	int x;			//ʳ������
	int y;
}Food,*pFood;

//��ʼ��
 void initSanke();

//��������
void showsanke();

//��Ϸ����
void end();

//�������
void key_input();

//���ƶ�
void movesanke();

//�ж�ʳ�����
void food();