#pragma once
#define Widht 900			//界面的宽，高
#define Hight  500 
#define sankeRadius 5			//蛇的半径
#define Initlength	 3				//蛇的初始长度
/************************************
	项目：贪吃蛇；
	图形工具：Easxy
************************************/
enum dir			//用于设置蛇的方向
{
	UP = 1, Down = 2, Right = 3, Left = 4
};
//设计蛇结构
typedef struct Sanke
{
	int x;				//蛇的坐标
	int y;
	bool sankeHead;		//用于判断是不是蛇头，是蛇头那蛇头变成红色，不是那就黄色
	dir move;
	struct Sanke* next;		//下一节身体
}Sanke,*pSanke;

//设计食物结构
typedef struct food
{
	int x;			//食物坐标
	int y;
}Food,*pFood;

//初始化
 void initSanke();

//画出界面
void showsanke();

//游戏结束
void end();

//按键检测
void key_input();

//蛇移动
void movesanke();

//判断食物情况
void food();