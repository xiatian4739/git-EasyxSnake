#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include "Sanke.h"
/************************************
	���뻷���� vs2019
	��Ŀ��̰���ߣ�
	ͼ�ι��ߣ�Easxy
************************************/
extern bool ply;
extern int speed;

int main()
{

	initgraph(Widht, Hight,NULL);
	initSanke();
	setbkcolor(BLACK);
	cleardevice();
	while (ply)
	{
		cleardevice();
		showsanke();
		key_input();
		movesanke();
		showsanke();
		Sleep(speed);
		setorigin(0, 0);
	}
	_getwch();
	closegraph();
	return 0;
}