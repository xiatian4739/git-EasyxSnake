#pragma once
#include "Sanke.h"
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <time.h>
#include <conio.h>
int speed;
			//��������ͷ->next = ��ͷ
pSanke Headsanke, sanke;		//sanke������ʱ�õġ����Բ��õ�ʱ�򴴽�һ���Ϳ��ԡ�
pFood  sankefood;					//����ʳ�����
int score;									//��¼����
int Highscore;
bool ply;									//�����ж���Ϸ�Ƿ����
char Text_Game[200];			//����������ڴ��ַ������ڴ�ӡ����Ļ��

//��ӡ��Ϣ		
//�⺯���úÿ�������һ�仰���Ǹ��������ӡ������ַ��������մ������ɫ��ӡ
void showPrint(int left, int top, int right, int bottom, char Text[], COLORREF color)
{
	settextcolor(color);
	// ����Ļ��������ַ���				//���º���ȥEasxy�����ĵ������˽�
	RECT r = { left, top, right , bottom };
	drawtext(_T(Text), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

}

//���ٵȼ�  ��ܺ����Ͳ��������
void initSpeed()
{
	char te[] = "	��ѡ����Ϸ�ٶ�: �� A  �� S  �� D ��\n";
	showPrint(0, 0, 639, 479, te, RED);
	//ѡ���ٶ� �����У���
	char sp;
	sp = _getch();
	switch (sp)
	{
	case 'A':
	case 'a':
		speed = 260;				//����ֵ�ĸı��Ӱ�����������Sleep();�ٶ�
		break;
	case 'S':
	case 's':
		speed = 150;
		break;
	case 'D':
	case 'd':
		speed = 55;
		break;
	}

}

//���ö�ȡ
int peifile()
{
	FILE* fp;
	fopen_s(&fp,"../init.ini","r+");
	if (fp == NULL)
	{
		perror("open:");
	}

	int var;
	while ((var = fgetc(fp)) != EOF)
	{
	}

	if (fp != NULL)
	{
		fclose(fp);
		fp = NULL;
	}
	return var;
}

//д������
void wirfile(int var)
{
	FILE* fp;
	fopen_s(&fp, "../init.ini", "w");
	if (fp == NULL)
	{
		perror("open:");
	}

	fputc(var,fp);

	if (fp != NULL)
	{
		fclose(fp);
		fp = NULL;
	}
}

//��ʼ��
void initSanke()
{
	srand((unsigned int)time(NULL));				//����
	//�Ա�����ʼ��
	score = 0;
	speed = 0;
	Highscore = peifile();
	ply = true;
	Headsanke = NULL;								
	sanke = NULL;
	Headsanke = (pSanke)malloc(sizeof(Sanke));		//������ͷ����ռ�
	if (Headsanke == NULL)			//�ж��ڴ�����Ƿ�ɹ�
	{
		return;
	}
	//Ĭ�ϸ����߳���������
	int sanke_x, sanke_y;
	sanke_x = 200;
	sanke_y = 200;
	for (int i = 0; i < Initlength; i++)		//Initlength(�궨��) �ߵĳ�ʼ���� 
	{
		pSanke Newsanke = (pSanke)malloc(sizeof(Sanke));
		if (Newsanke == NULL)				//�ж��ڴ�����Ƿ�ɹ�
			{
				return;
			}
		if (i == 0)			//��һ���ڵ㵽�������ߵ�β�ͣ���Ϊ��ͷ�巨��
		{							//������sankeָ������Ȼ�������β��->next = NULL
			sanke = Newsanke;
		}
		Newsanke->x = sanke_x;
		Newsanke->y = sanke_y;
		//��Ϊ�ߵ�Ĭ�Ϸ�����---->
		//����ֻ��x��ֵyֵ��Ҫ������Ϊ�ߵİ뾶��5����ֱ����10
		sanke_x = sankeRadius*2 + sanke_x;
		//��ΪĿǰ��֪���ĸ�����ͷ�������ó�false , sankeHead = false;
		Newsanke->sankeHead = false;
		//���������������ģ����黭ͼ��
		Newsanke->next = Headsanke->next;		
		Headsanke->next = Newsanke;					

		}
	//����ͷ->��ͷ �� ���԰�sankeHead = true�� ��ΪҪ��ͷΪ��ɫ������Ϊ��ɫ
	Headsanke->next->sankeHead = true;
	//�ߵ�Ĭ�Ϸ���--->
	Headsanke->next->move = Right;
	//���������汣������β�ͣ� ��β��->next = MULL;
	sanke->next = NULL;
	//���ó�ʼ��ʳ��
	food();
	//���ó�ʼ���ٶ�
	initSpeed();
}

//ʳ������
void food()
{
		srand((unsigned int)time(NULL));			//����
		sankefood = (pFood)malloc(sizeof(Food));		//��ʳ�����ռ�
		bool temp = true;			//ѭ������
		int sankefood_x, sankefood_y;			//ʳ������
		while (temp)
		{
			while (1)
			{
				//��Ϊ��Χǽʳ������겻�ܺ�Χǽ��ȣ�����Ҫ����Χǽ�Ŀ�ȣ�
				//Ȼ�����ɷ�Χ(15~(Widht-315)),��֮Ҫ��Χǽ֮��
				sankefood_x = rand() % (Widht-315) + 15;		
				sankefood_y = rand() % (Hight - 25) + 15;
				//������Ϊ���ƶ���Ҫ+10(ֱ��)����ÿ���ƶ����Ǽ�10
				//���겻����� ��:123,343 ��Щ����,�������Щ���꣬���ߵ�������Զ�������
				//��Щ���꣬Ҳ����ζ�ųԲ���ʳ��
				//����ʳ������Ϊ10,20,30......,�жϷ�������ȡ������ĸ�λ���ж��ǵ���0
				//��Ϊ��λ����0����֤�������(10,110,20,440,30...)��
				if ((sankefood_x % 10) == 0 && (sankefood_y % 10) == 0)
				{
					break;
				}
			}

			sanke = Headsanke->next;
			while (sanke != NULL)
			{
				//�ж�ʳ�������Ƿ���ߵ�������ͬ
				if (sanke->x == sankefood_x && sanke->y == sankefood_y)
				{
					break;
				}
				else
				{
					temp = false;
				}
				sanke = sanke->next;
			}
		}
		//��ֵ��ʳ������
		sankefood->x = sankefood_x;
		sankefood->y = sankefood_y;
}

//����/ʳ��
void showsanke()
{
	pSanke p = Headsanke->next;
	//�ж�ʳ��
	if (sankefood != NULL)
	{
		setfillcolor(LIGHTGREEN);
		setlinecolor(LIGHTBLUE);
		fillcircle(sankefood->x, sankefood->y, sankeRadius);
	}

	if (p == NULL)
	{
		return;
	}
	//��һ����Ȼ�ж��һ�٣�����û����ж�һ��
	//�ж��ǲ�����ͷ������Ǿ���ͷΪ��ɫ
	if (p->sankeHead == true)
	{
		setfillcolor(RED);
		setlinecolor(LIGHTBLUE);
		fillcircle(p->x, p->y, sankeRadius);
		p = p->next;
	}
	//������
	while (p != NULL )
	{
		setfillcolor(YELLOW);
		setlinecolor(LIGHTBLUE);
		fillcircle(p->x, p->y, sankeRadius);
		p = p->next;
	}
	//��ӡΧǽ
	settextcolor(CYAN);
	for (int i = 0; i <= Widht-300; i += 12)		//��ӡ����
	{
		outtextxy(i, 0, "��");
		outtextxy(i, Hight-15, "��");
	}
	
	for (int  i = 15; i < Hight-25; i +=12)	//��ӡ����
	{
		outtextxy(0, i, "��");
		outtextxy(Widht - 300, i, "��");
	}

	//�ж���Ϸ�Ƿ����,���ply = false���ǾͲ���ӡ��ȥ��Ϸ���������ӡ
	//����sprintf ����ȥ�ٶȲ��
	if (ply)
	{
		sprintf_s(Text_Game, "��ǰ����Ϊ��%d", score);
		showPrint(Widht, 150, Widht - 300, 100, Text_Game, CYAN);
	}
	sprintf_s(Text_Game, "����: W ��    S ��    R ��    A ��");
	showPrint(Widht, 150, Widht - 300, 300, Text_Game, CYAN);
}

//��Ϸ����
void end()
{
	ply = false;
	sprintf_s(Text_Game," ��Ϸ��������ǰ����Ϊ��%d",score);
	showPrint(Widht, 150, Widht - 300, 100, Text_Game, RED);
	showsanke();
}

//�������
void key_input()
{
	char key;
	if (_kbhit())					//��Ҫ�ú��˽�һ���������
	{
		key = _getch();
		switch (key)
		{
		case'w':
		case'W':
		case 72:
			if (Headsanke->next->move == Down)					//��ֹ�߻�ͷ����һ��
				break;
			Headsanke->next->move = UP;
			break;
		case's':
		case'S':
		case 80:
			if (Headsanke->next->move == UP)
				break;
			Headsanke->next->move = Down;
			break;
		case'a':
		case'A':
		case 75:
			if (Headsanke->next->move == Right)
				break;
			Headsanke->next->move = Left;
			break;
		case'd':
		case'D':
		case 77:
			if (Headsanke->next->move == Left)
				break;
			Headsanke->next->move = Right;
			break;
		}
	}
	
}


//���ƶ�
void movesanke()
{
	//����ͷ�ڵ�����꣬�Ȼ��ƶ������µĽڵ�Ҫ�õ���
	int sanke_x = Headsanke->next->x;
	int sanke_y = Headsanke->next->y;

	//�ƶ��жϣ�Ȼ����м���
	if (Headsanke->next->move == UP )
	{
		Headsanke->next->y -= 10;
	}
	else if(Headsanke->next->move == Down )
	{
		Headsanke->next->y +=10;

	}
	else if (Headsanke->next->move == Right)
	{
		Headsanke->next->x +=10;

	}
	else if (Headsanke->next->move == Left)
	{
		Headsanke->next->x -=10;

	}
	
	/*
	���������ͷ�����ƶ�X,Y�Ѿ��ı��ˣ��߲��Ӷ��ˣ����������µĽڵ�����ոձ��������꣬
	�������Ӿ��������ˣ���ס�ͷ�β�ͣ�
	*/
	pSanke  Newsanke = (pSanke)malloc(sizeof(Sanke));
	Newsanke->x = sanke_x;												//���ӣ��µĽڵ㣩������
	Newsanke->y = sanke_y;
	Newsanke->sankeHead = false;
	Newsanke->next = Headsanke->next->next;			//�µĽڵ�ָ����ͷ�Ĳ��ӣ���һ���ڵ㣩
	Headsanke->next->next = Newsanke;						//����ͷ->nextָ���µĽڵ㣬��������������

	//�ж���ͷ�Ƿ�����ǽ����Ϊ��ӡ��Χǽ��ΪΧǽ����15���Եô�15��ʼ�ж�
	if (Headsanke->next->x <=15 || Headsanke->next->x >= Widht-300 || 
		Headsanke->next->y <= 15 || Headsanke->next->y >= Hight-25)
	{
		//�������ý�������
		end();
	}

	//�ж���ͷ�Ƿ��ʳ��������ͬ
	if ( sankefood != NULL && sankefood->x == Headsanke->next->x && 
		sankefood->y == Headsanke->next->y)
	{
		//��ͬ ����ʳ�ﺯ��������++
		score++;
		food();
	}
	else			//�������ʳ����ͬ�Ǿ��ж���ͷ�Ƿ��������ͬ������ͷ��ÿһ������Ƚ�
	{
		pSanke p = Headsanke->next;
		while (p->next->next != NULL)
		{
			//����Ҫ����ⲻ�ˣ����Խ��е��Խ��в鿴���߻�ͼ
			if (p->next->next->x == Headsanke->next->x && p->next->next->y == Headsanke->next->y)
			{
				end();
			}
			p = p->next;
		}
		//�ͷ�β��
		free(p->next);
		p->next = NULL;
	}

}