#include<stdio.h>
#include <stdio.h>
#include <windows.h>
#include<process.h>
#include <time.h>
#include <string.h>
#include "Globals.h"
#include"DynamicEffect .h"
#include"MES-Leader.h"
#include"MES-WarehouseKeeper.h"
#include"MES-PLSupervisionEngineer.h"
#include"MES-ProductSalesman.h"
#include"MES-ProcessDesigner.h"
#define _CRT_SECURE_NO_DEPRECATE；
#define _CRT_SECURE_NO_WARNINGS；
#pragma warning(disable:4996)；


MComsSeqList allMComslist;   //有序动态顺序表存储所有原料供应企业信息
PComsSeqList allPComslist;   //有序动态顺序表存储所有产品采购企业信息
MWaresSeqList allMWareslist; //有序动态顺序表存储所有仓储原料管理信息
PSalesSeqList allPSaleslist; //有序动态顺序表存储所有采购订单管理信息
DProcessSeqList  allDProcesslist;//有序动态顺序表存储所有的工艺流程信息

//通用函数1：得到当前的日期
void getTimeNow(char d[]);
//通用函数2：初始化动态顺序表，size为初始化容量
void intListInit(IntSeqList* s, int size);
//通用函数3：添加一个整数到动态顺序表中
int addInt(IntSeqList* s, int data);
//通用函数4：通用的退出当前程序界面的函数,不同面板均可通过参数type调用
void exitMES(int type);
//通用函数5：通用的报错程序模板，在任何地方均可以使用,x和y分别表示显示语句的坐标，error为错误信息
void errorTemplate(int x, char error[40]);

//通用函数6：通用的ROOT用户加载模板，x和y分别表示显示语句的坐标，welcom为加载的欢迎信息
void rootWelcome(int x, char welcome[40], char tip[40], int type);

//通用函数1：得到当前的日期
void getTimeNow(char d[]) {
	time_t tnow;
	time(&tnow);
	struct tm* sttm;
	sttm = localtime(&tnow);
	sprintf(d, "%d-%d-%d", sttm->tm_year + 1900, sttm->tm_mon + 1, sttm->tm_mday);
}

//通用函数2：初始化动态顺序表，size为初始化容量
void intListInit(IntSeqList* s, int size) {
	s->list = (int*)malloc(size * sizeof(int));
	s->length = 0;
	s->size = size;
}

//通用函数3：添加一个整数到动态顺序表中
int addInt(IntSeqList* s, int data) {
	if (s->length >= s->size) {
		int* t = s->list;
		s->list = (int*)malloc(2 * s->size * sizeof(int));
		if (s->list == NULL)
			return -1;
		s->size = 2 * s->size;
		for (int i = 0; i < s->length; i++)
			s->list[i] = t[i];
		free(t);
	}
	s->list[s->length] = data;
	s->length++;
	return 0;
}

//通用函数4：通用的退出当前程序界面的函数,不同面板均可通过参数type调用
void exitMES(int type) {
	int check;
	system("cls");		//1.	
	checkFrameShow();
	Gotoxy(35 + 13, 13);
	printf("您确认要退出MES系统吗？");
	Gotoxy(35 + 13, 14);
	printf("确认输入 1,返回输入 0：");
	Gotoxy(35 + 13+ 11, 17);
	scanf("%d", &check);
	Gotoxy(35 + 13 + 11+3, 17);
	charRotation();
	if (check == 1) {
		system("cls");
		LoadExitMES(33, 15);
		system("cls");
		earthEffect();
		exit(0);
	}
	//输入了除0或1的其它数字
	else if (check!=0&&check!=1) {
		system("cls");
		exitMES(type);
	}
	else {
		//因为返回的界面面板不一致，所以需要做不同的设定
		//0是返回root界面面板
		if (type == 0) {
			system("cls");
			Sleep(100);
			system("cls");
			rootLeaderInterface();
		}
		//1是返回企业管理者界面面板
		else if (type == 1) {
			system("cls");
			Sleep(100);
			system("cls");
			adminLeaderInterface();
		}
		//2是返回仓储管理者界面面板
		else if (type == 2) {
			system("cls");
			Sleep(100);
			system("cls");
			wareInterface();
		}
		//3是返回工艺流程设计师
		else if (type == 3) {
			system("cls");
			Sleep(100);
			system("cls");
			DProcessInterface();
			return 0;
		}
		//4是返回生产监督工程师
		else if (type == 4) {	
			system("cls");
			Sleep(100);
			system("cls");
			SuperPLInterface();
			return 0;
		}
		//5是返回产品销售员
		else{
			system("cls");
			Sleep(100);
			system("cls");
			proSalesInterface();
			return 0;
		}
	}
	while (1);
	//earthEffect();

}

//通用函数5：通用的报错程序模板，在任何地方均可以使用,x和y分别表示显示语句的坐标，error为错误信息
void errorTemplate(int x,char error[40]) {
	//error最好设置在12字内
	system("cls");	
	checkFrameShow();
	Gotoxy(x ,14);
	printf("%s",error);
	Gotoxy(117/2,16);
	charRotation();
	Sleep(2000);
	system("cls");
}

//通用函数6：通用的ROOT用户加载模板，x和y分别表示显示语句的坐标，welcom为加载的欢迎信息
void rootWelcome(int x, char welcome[40],char tip[40],int type) {
	system("cls");
	checkFrameShow();
	Gotoxy(x, 14);
	printf("%s", welcome);
	Gotoxy(41, 14+2);
	printf("%s", tip);
	LoadRoot(33, 20, type);
	Sleep(3000);
}

//通用函数7:完成所有的初始化步骤
void initAll() {
	//第一步：初始化原料供应企业链表
	MComsSeqListInit(&allMComslist, 100);
	//第二步：从数据库中读取数据到原料供应企业链表
	allMComsInfoReadFromFile(&allMComslist, "合作的供应企业信息数据库.txt");
	//第三步：初始化产品采购企业链表
	PComsSeqListInit(&allPComslist, 100);
	//第四步：从数据库中读取数据到产品采购企业链表
	allPComsInfoReadFromFile(&allPComslist, "合作的采购企业信息数据库.txt");
	//第五步：初始化仓储原料管理链表
	MWaresSeqListInit(&allMWareslist, 100);
	//第六步：从数据库中读取数据到仓储原料管理链表
	allMWaresInfoReadFromFile(&allMWareslist, "仓储管理信息数据库.txt");
	//第七步：初始化工艺流程管理链表
	DProcessSeqListInit(&allDProcesslist, 100);
	//第八步：从数据库中读取数据到工艺流程管理链表
	allDProcessInfoReadFromFile(&allDProcesslist, "工艺流程链及模块信息信息数据库.txt");
	//第九步：完成工厂产线的初始化状态
	ProductionLineInit();
	//第十步：完成工厂机床的初始化状态
	ProductionLineInit();
	//第九步：初始化采购订单管理链表
	PSalesSeqListInit(&allPSaleslist, 100);
	//第十步：从数据库中读取数据到采购订单管理链表
	allPSalesInfoReadFromFile(&allPSaleslist, "采购订单信息数据库.txt");
}