#include<stdio.h>
#include <stdio.h>
#include <windows.h>
#include<process.h>
#include <time.h>


//顺序表容器结构体，存放整数
typedef struct {
	int* list;
	int size;
	int length;
}IntSeqList;

typedef  struct  time   //表示日期
{
	int year;			//年
	int month;			//月
	int day;			//日
} Date;

//得到当前的工作时间
void getTimeNow(char d[]);

//链表初始化函数
void intListInit(IntSeqList* s, int size);

//添加一个整数到动态顺序表中
int addInt(IntSeqList* s, int data);

//通用界面功能函数1--退出MES系统
void  exitMES();

//通用的报错程序模板，在任何地方均可以使用,x和y分别表示显示语句的坐标，error为错误信息
void errorTemplate(int x, char error[40]);

//通用函数6：通用的ROOT用户加载模板，x和y分别表示显示语句的坐标，welcom为加载的欢迎信息
void rootWelcome(int x, char welcome[40], char tip[40], int type);

//通用函数7:完成所有的初始化步骤
void initAll();