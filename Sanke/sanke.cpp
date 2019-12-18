#pragma once
#include "Sanke.h"
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <time.h>
#include <conio.h>
int speed;
			//用于连接头->next = 蛇头
pSanke Headsanke, sanke;		//sanke用于临时用的。可以不用到时候创建一个就可以。
pFood  sankefood;					//创建食物变量
int score;									//记录分数
int Highscore;
bool ply;									//用于判断游戏是否结束
char Text_Game[200];			//这个变量用于存字符串用于打印到屏幕上

//打印信息		
//这函数好好看参数，一句话就是给定坐标打印传入的字符串，按照传入的颜色打印
void showPrint(int left, int top, int right, int bottom, char Text[], COLORREF color)
{
	settextcolor(color);
	// 在屏幕中央输出字符串				//以下函数去Easxy帮助文档进行了解
	RECT r = { left, top, right , bottom };
	drawtext(_T(Text), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

}

//加速等级  这很好理解就不过多解释
void initSpeed()
{
	char te[] = "	请选择游戏速度: 慢 A  中 S  快 D ！\n";
	showPrint(0, 0, 639, 479, te, RED);
	//选择速度 慢，中，快
	char sp;
	sp = _getch();
	switch (sp)
	{
	case 'A':
	case 'a':
		speed = 260;				//这里值的改变会影响主函数里的Sleep();速度
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

//配置读取
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

//写入配置
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

//初始化
void initSanke()
{
	srand((unsigned int)time(NULL));				//种子
	//对变量初始化
	score = 0;
	speed = 0;
	Highscore = peifile();
	ply = true;
	Headsanke = NULL;								
	sanke = NULL;
	Headsanke = (pSanke)malloc(sizeof(Sanke));		//给连接头分配空间
	if (Headsanke == NULL)			//判断内存分配是否成功
	{
		return;
	}
	//默认给定蛇出生的坐标
	int sanke_x, sanke_y;
	sanke_x = 200;
	sanke_y = 200;
	for (int i = 0; i < Initlength; i++)		//Initlength(宏定义) 蛇的初始长度 
	{
		pSanke Newsanke = (pSanke)malloc(sizeof(Sanke));
		if (Newsanke == NULL)				//判断内存分配是否成功
			{
				return;
			}
		if (i == 0)			//第一个节点到最后会变成蛇的尾巴，因为是头插法，
		{							//所以用sanke指向他，然后最后让尾巴->next = NULL
			sanke = Newsanke;
		}
		Newsanke->x = sanke_x;
		Newsanke->y = sanke_y;
		//因为蛇的默认方向是---->
		//所以只加x的值y值不要动，因为蛇的半径是5所以直径是10
		sanke_x = sankeRadius*2 + sanke_x;
		//因为目前不知道哪个是蛇头所以设置成false , sankeHead = false;
		Newsanke->sankeHead = false;
		//下面两步看不懂的，建议画图，
		Newsanke->next = Headsanke->next;		
		Headsanke->next = Newsanke;					

		}
	//连接头->蛇头 ， 所以把sankeHead = true， 因为要蛇头为红色，蛇身为黄色
	Headsanke->next->sankeHead = true;
	//蛇的默认方向--->
	Headsanke->next->move = Right;
	//这里在上面保留了蛇尾巴， 让尾巴->next = MULL;
	sanke->next = NULL;
	//调用初始化食物
	food();
	//调用初始化速度
	initSpeed();
}

//食物生成
void food()
{
		srand((unsigned int)time(NULL));			//种子
		sankefood = (pFood)malloc(sizeof(Food));		//给食物分配空间
		bool temp = true;			//循环条件
		int sankefood_x, sankefood_y;			//食物坐标
		while (temp)
		{
			while (1)
			{
				//因为有围墙食物的坐标不能和围墙相等，所以要加上围墙的宽度，
				//然后生成范围(15~(Widht-315)),总之要在围墙之内
				sankefood_x = rand() % (Widht-315) + 15;		
				sankefood_y = rand() % (Hight - 25) + 15;
				//这里因为蛇移动是要+10(直径)这样每次移动都是加10
				//坐标不会等于 如:123,343 这些坐标,如果是这些坐标，那蛇的坐标永远不会等于
				//这些坐标，也就意味着吃不了食物
				//所以食物坐标为10,20,30......,判断方法就是取出坐标的个位数判断是等于0
				//因为个位等于0，就证明这个是(10,110,20,440,30...)等
				if ((sankefood_x % 10) == 0 && (sankefood_y % 10) == 0)
				{
					break;
				}
			}

			sanke = Headsanke->next;
			while (sanke != NULL)
			{
				//判断食物坐标是否和蛇的坐标相同
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
		//赋值给食物坐标
		sankefood->x = sankefood_x;
		sankefood->y = sankefood_y;
}

//画蛇/食物
void showsanke()
{
	pSanke p = Headsanke->next;
	//判断食物
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
	//这一步虽然有多此一举，但最好还是判断一下
	//判断是不是蛇头如果是那就蛇头为红色
	if (p->sankeHead == true)
	{
		setfillcolor(RED);
		setlinecolor(LIGHTBLUE);
		fillcircle(p->x, p->y, sankeRadius);
		p = p->next;
	}
	//画蛇身
	while (p != NULL )
	{
		setfillcolor(YELLOW);
		setlinecolor(LIGHTBLUE);
		fillcircle(p->x, p->y, sankeRadius);
		p = p->next;
	}
	//打印围墙
	settextcolor(CYAN);
	for (int i = 0; i <= Widht-300; i += 12)		//打印上下
	{
		outtextxy(i, 0, "■");
		outtextxy(i, Hight-15, "■");
	}
	
	for (int  i = 15; i < Hight-25; i +=12)	//打印左右
	{
		outtextxy(0, i, "■");
		outtextxy(Widht - 300, i, "■");
	}

	//判断游戏是否结束,如果ply = false，那就不打印，去游戏结束里面打印
	//不懂sprintf 函数去百度查查
	if (ply)
	{
		sprintf_s(Text_Game, "当前分数为：%d", score);
		showPrint(Widht, 150, Widht - 300, 100, Text_Game, CYAN);
	}
	sprintf_s(Text_Game, "按键: W ↑    S ↓    R →    A ←");
	showPrint(Widht, 150, Widht - 300, 300, Text_Game, CYAN);
}

//游戏结束
void end()
{
	ply = false;
	sprintf_s(Text_Game," 游戏结束！当前分数为：%d",score);
	showPrint(Widht, 150, Widht - 300, 100, Text_Game, RED);
	showsanke();
}

//按键检测
void key_input()
{
	char key;
	if (_kbhit())					//需要好好了解一下这个函数
	{
		key = _getch();
		switch (key)
		{
		case'w':
		case'W':
		case 72:
			if (Headsanke->next->move == Down)					//防止蛇回头下面一样
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


//蛇移动
void movesanke()
{
	//保留头节点的坐标，等会移动生成新的节点要用到，
	int sanke_x = Headsanke->next->x;
	int sanke_y = Headsanke->next->y;

	//移动判断，然后进行计算
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
	上面代码蛇头经过移动X,Y已经改变了，蛇脖子断了，所以生成新的节点填入刚刚保留的坐标，
	这样脖子就连接上了，记住释放尾巴；
	*/
	pSanke  Newsanke = (pSanke)malloc(sizeof(Sanke));
	Newsanke->x = sanke_x;												//脖子（新的节点）的坐标
	Newsanke->y = sanke_y;
	Newsanke->sankeHead = false;
	Newsanke->next = Headsanke->next->next;			//新的节点指向蛇头的脖子（下一个节点）
	Headsanke->next->next = Newsanke;						//把蛇头->next指向新的节点，这样就连接上了

	//判断蛇头是否碰到墙，因为打印了围墙因为围墙宽是15所以得从15开始判断
	if (Headsanke->next->x <=15 || Headsanke->next->x >= Widht-300 || 
		Headsanke->next->y <= 15 || Headsanke->next->y >= Hight-25)
	{
		//碰到调用结束函数
		end();
	}

	//判断蛇头是否和食物坐标相同
	if ( sankefood != NULL && sankefood->x == Headsanke->next->x && 
		sankefood->y == Headsanke->next->y)
	{
		//相同 调用食物函数，分数++
		score++;
		food();
	}
	else			//如果不和食物相同那就判断蛇头是否和蛇身相同，用蛇头和每一节身体比较
	{
		pSanke p = Headsanke->next;
		while (p->next->next != NULL)
		{
			//这里要是理解不了，可以进行调试进行查看或者画图
			if (p->next->next->x == Headsanke->next->x && p->next->next->y == Headsanke->next->y)
			{
				end();
			}
			p = p->next;
		}
		//释放尾巴
		free(p->next);
		p->next = NULL;
	}

}