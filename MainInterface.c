#include<stdio.h>
#include <stdio.h>
#include <windows.h>
#include<process.h>
#include <time.h>
#include "string.h"
#include"Globals.h"
#include"MES-Leader.h"      //导入领导者
#include"DynamicEffect .h"  //加载动态效果
#include"MainInterface.h"	
#include"MES-WarehouseKeeper.h"
#include"MES-ProcessDesigner.h"
#include"MES-PLSupervisionEngineer.h"

#define _CRT_SECURE_NO_DEPRECATE；
#define _CRT_SECURE_NO_WARNINGS；
#pragma warning(disable:4996)；

int resultID = 1;			//全局变量resultID作为输入ID检测的返回值
char password[6] = "root";	//定义密码初始化值为root
char employeeID[4] = "00";	//工人编号初始化值为00

//界面函数1：登陆界面函数
int interFacemainWrong();
//功能函数1：专门用于还原现场的密码输入错误函数
int interFacemainWrong();
//功能函数1：身份信息验证函数
int sys_loginID(char* employeeID);

//界面函数1：登陆界面函数
void interFacemain() {
	int x = 0;
	char c = '0';
	system("cls");
	frameShow();
	Gotoxy(48, 10);		//动态移动光标，同时本页面以坐标（48，10）作为基准移动下面的光标
	printf("鲁班MES智能制造执行系统\n");
	Gotoxy(48 - 9, 12);		//动态移动光标
	printf("员工编号：");
	Gotoxy(45 + 14, 12);		//动态移动光标
	for (int i = 0; i < 5; i++) {
		scanf("%c", &employeeID[i]);
		if (employeeID[i] == '\n') {
			break;
		}
	}
	resultID = sys_loginID(employeeID);	//返回身份验证ID
	Gotoxy(48 + 26, 12);
	charRotation();			
	Gotoxy(48 - 9, 14);					
	printf("员工岗位：");
	/*---1.企业领导者验证接口---*/
	if (resultID==0||resultID==1){
		Gotoxy(45 + 14, 14);			
		printf("企业领导者");
		Gotoxy(48 + 26, 14);
		charRotation();					//在这里执行验证身份信息
		Gotoxy(48 - 9, 16);				
		printf("员工密码：\n");
		Gotoxy(45 + 14, 16);		//动态移动光标
		while (x < 4 && c != 13)   //13是回车符的ASCII码
		{
			c = getch();
			password[x++] = c;
			if (c != 13)
				putchar('*');
		}
		password[x] = '\0';
		Gotoxy(48 + 26, 16);
		charRotation();
		if (strcmp("root\0", password) == 0) {	//root用户密码检测
			Gotoxy(48 + 26, 16);
			charRotation();			//在这里执行验证身份信息
			//*测试浪费时间锁
			LoadInSuccess(48 - 15, 20);
			Sleep(1000);
			//*/
			system("cls");			//清除屏幕进入下一界面
			rootLeaderInterface();
		}
		else if (strcmp("0000\0", password) == 0) {	//管理者密码检测
			Gotoxy(48 + 26, 16);
			charRotation();			//在这里执行验证身份信息
			///*测试浪费时间锁
			LoadInSuccess(48 - 15, 20);
			Sleep(1000);
			//*/
			system("cls");			//清除屏幕进入下一界面
			adminLeaderInterface();
		}
		else {
			Gotoxy(48 - 20, 18);
			LoadInFail(48 - 15, 20);
			system("cls");			//清除屏幕进入下一界面
			interFacemainWrong();
		}
	}
	/*---2.仓储管理员验证接口---*/
	else if (resultID == 2) {
		Gotoxy(45 + 14, 14);		//动态移动光标
		printf("仓储管理员");
		Gotoxy(48 + 26, 14);
		charRotation();			//在这里执行验证身份信息
		Gotoxy(48 - 9, 16);		//动态移动光标
		printf("员工密码：\n");
		Gotoxy(45 + 14, 16);		//动态移动光标
	    while (x < 4 && c != 13)   //13是回车符的ASCII码
		{
			c = getch();
			password[x++] = c;
			if (c != 13)
				putchar('*');
		}
		password[x] = '\0';
		Gotoxy(48 + 26, 16);
		charRotation();
		if (strcmp("0001\0", password) == 0) {
			Gotoxy(48 + 26, 16);
			charRotation();			//在这里执行验证身份信息
			/*测试浪费时间锁
			LoadInSuccess(48 - 15, 20);
			Sleep(1000);
			//*/
			system("cls");			//清除屏幕进入下一界面
			wareInterface();
		}
		else {
			Gotoxy(48 - 20, 18);
			LoadInFail(48 - 15, 20);
			system("cls");			//清除屏幕进入下一界面
			interFacemainWrong();
		}
	}
	/*---3.流程设计师验证接口---*/
	else if (resultID == 3) {
		Gotoxy(45 + 14, 14);		//动态移动光标
		printf("工艺流程设计师");
		Gotoxy(48 + 26, 14);
		charRotation();			//在这里执行验证身份信息
		Gotoxy(48 - 9, 16);		//动态移动光标
		printf("员工密码：\n");
		Gotoxy(45 + 14, 16);		//动态移动光标
		while (x < 4 && c != 13)   //13是回车符的ASCII码
		{
			c = getch();
			password[x++] = c;
			if (c != 13)
				putchar('*');
		}
		password[x] = '\0';
		Gotoxy(48 + 26, 16);
		charRotation();
		if (strcmp("0002\0", password) == 0) {
			Gotoxy(48 + 26, 16);
			charRotation();			//在这里执行验证身份信息
			/*测试浪费时间锁
			LoadInSuccess(48 - 15, 20);
			Sleep(1000);
			//*/
			system("cls");			//清除屏幕进入下一界面
			DProcessInterface();
		}
		else {
			Gotoxy(48 - 20, 18);
			LoadInFail(48 - 15, 20);
			system("cls");			//清除屏幕进入下一界面
			interFacemainWrong();
		}
	}
	/*---4.产线监督工程师验证接口---*/
	else if (resultID == 4) {
		Gotoxy(45 + 14, 14);		//动态移动光标
		printf("产线监督工程师");
		Gotoxy(48 + 26, 14);
		charRotation();			//在这里执行验证身份信息
		Gotoxy(48 - 9, 16);		//动态移动光标
		printf("员工密码：\n");
		Gotoxy(45 + 14, 16);		//动态移动光标
		while (x < 4 && c != 13)   //13是回车符的ASCII码
		{
			c = getch();
			password[x++] = c;
			if (c != 13)
				putchar('*');
		}
		password[x] = '\0';
		Gotoxy(48 + 26, 16);
		charRotation();
	    if (strcmp("0003\0", password) == 0) {
			Gotoxy(48 + 26, 16);
			charRotation();			//在这里执行验证身份信息
			/*测试浪费时间锁
			LoadInSuccess(48 - 15, 20);
			Sleep(1000);
			//*/
			system("cls");			//清除屏幕进入下一界面
			SuperPLInterface();
		}
		else {
			Gotoxy(48 - 20, 18);
			LoadInFail(48 - 15, 20);
			system("cls");			//清除屏幕进入下一界面
			interFacemainWrong();
		}
	}
	/*---5.产品销售员验证接口---*/
	else if (resultID == 5) {
		Gotoxy(45 + 14, 14);		//动态移动光标
		printf("产品销售员");
		Gotoxy(48 + 26, 14);
		charRotation();			//在这里执行验证身份信息
		Gotoxy(48 - 9, 16);		//动态移动光标
		printf("员工密码：\n");
		Gotoxy(45 + 14, 16);		//动态移动光标
		while (x < 4 && c != 13)   //13是回车符的ASCII码
		{
			c = getch();
			password[x++] = c;
			if (c != 13)
				putchar('*');
		}
		password[x] = '\0';
		Gotoxy(48 + 26, 16);
		charRotation();
		if (strcmp("0004\0", password) == 0) {
			Gotoxy(48 + 26, 16);
			charRotation();			//在这里执行验证身份信息
			/*测试浪费时间锁
			LoadInSuccess(48 - 15, 20);
			Sleep(1000);
			//*/
			system("cls");			//清除屏幕进入下一界面
			proSalesInterface();
		}
		//密码输入错误的情况下
		else {
			Gotoxy(48 - 20, 18);
			LoadInFail(48 - 15, 20);
			system("cls");			//清除屏幕进入下一界面
			interFacemainWrong();	//密码输入错误
		}
	}
	/*---6.输入的编号错误接口---*/
	else{
		Gotoxy(45 + 14, 14);
		printf("无编号对应工位");
		Gotoxy(48 + 26, 14);
		charRotation();
		Gotoxy(48 - 9-3, 19);
		printf("您输入的员工编号有误，请您查正后再重新输入  ");
		charRotation();
		memset(employeeID, 0, sizeof(employeeID));	//输入错误后，需要重新对employee数组赋空值
		Sleep(3000);
		interFacemain();
	}
}

//功能函数1：专门用于还原现场的密码输入错误函数
int interFacemainWrong() {
	int x = 0;
	char c = '0';
	while (1) {
		frameShow();
		Gotoxy(48, 10);		//动态移动光标，同时本页面以坐标（48，10）作为基准移动下面的光标
		printf("鲁班MES智能制造执行系统\n");
		Gotoxy(48 - 9, 12);		//动态移动光标
		printf("员工编号：");
		Gotoxy(45 + 14, 12);		//动态移动光标
		printf("%s",employeeID);
		Gotoxy(48 + 26, 12);
		printf("/");			//在这里执行验证身份信息
		Gotoxy(48 - 9, 14);		//动态移动光标
		printf("员工岗位：");
		Gotoxy(45 + 14, 14);		//动态移动光标
		//1.还原企业管理员的登陆现场
		if (resultID == 0 || resultID == 1) {
			printf("企业领导者");
			Gotoxy(48 + 26, 14);
			printf("/");
			Gotoxy(48 - 9, 16);		//动态移动光标
			printf("员工密码：\n");
			Gotoxy(45 + 14, 16);		//动态移动光标
			while (x < 4 && c != 13)   //13是回车符的ASCII码
			{
				c = getch();
				password[x++] = c;
				if (c != 13)
					putchar('*');
			}
			password[x] = '\0';
			Gotoxy(48 + 26, 16);
			charRotation();
			if (strcmp("root\0", password) == 0) {
				Gotoxy(48 + 26, 16);
				charRotation();			//在这里执行验证身份信息
				///*测试浪费时间锁
				LoadInSuccess(48 - 15, 20);
				Sleep(1000);
				//*/
				system("cls");			//清除屏幕进入下一界面
				rootLeaderInterface();
			}
			else if (strcmp("0000\0", password) == 0) {
				Gotoxy(48 + 26, 16);
				charRotation();			//在这里执行验证身份信息
				///*测试浪费时间锁
				LoadInSuccess(48 - 15, 20);
				Sleep(1000);
				//*/
				system("cls");			//清除屏幕进入下一界面
				adminLeaderInterface();
			}
			else {
				Gotoxy(48 - 20, 18);
				LoadInFail(48 - 15, 20);
				system("cls");			//清除屏幕进入下一界面
				interFacemainWrong();	//密码输入错误的情况下重新回到函数头
			}
		}
		//2.还原仓储管理员的登陆现场
		else if (resultID == 2) {
			printf("仓储管理员");
			Gotoxy(48 + 26, 14);
			printf("/");
			Gotoxy(48 - 9, 16);		//动态移动光标
			printf("员工密码：\n");
			Gotoxy(45 + 14, 16);		//动态移动光标
			while (x < 4 && c != 13)   //13是回车符的ASCII码
			{
				c = getch();
				password[x++] = c;
				if (c != 13)
					putchar('*');
			}
			password[x] = '\0';
			Gotoxy(48 + 26, 16);
			charRotation();
			if (strcmp("0001\0", password) == 0) {
				Gotoxy(48 + 26, 16);
				charRotation();			//在这里执行验证身份信息
				/*测试浪费时间锁
				LoadInSuccess(48 - 15, 20);
				Sleep(1000);
				//*/
				system("cls");			//清除屏幕进入下一界面
				wareInterface();
			}
			else {
				Gotoxy(48 - 20, 18);
				LoadInFail(48 - 15, 20);
				system("cls");			//清除屏幕进入下一界面
				interFacemainWrong();	//密码输入错误的情况下重新回到函数头
			}
		}
		//3.还原工艺流程设计师的登陆现场
		else if (resultID == 3) {
			printf("工艺流程设计师");
			Gotoxy(48 + 26, 14);
			printf("/");
			Gotoxy(48 - 9, 16);		//动态移动光标
			printf("员工密码：\n");
			Gotoxy(45 + 14, 16);		//动态移动光标
			while (x < 4 && c != 13)   //13是回车符的ASCII码
			{
				c = getch();
				password[x++] = c;
				if (c != 13)
					putchar('*');
			}
			password[x] = '\0';
			Gotoxy(48 + 26, 16);
			charRotation();
			if (strcmp("0002\0", password) == 0) {
				Gotoxy(48 + 26, 16);
				charRotation();			//在这里执行验证身份信息
				/*测试浪费时间锁
				LoadInSuccess(48 - 15, 20);
				Sleep(1000);
				//*/
				system("cls");			//清除屏幕进入下一界面
			    DProcessInterface();
			}
			else {
				Gotoxy(48 - 20, 18);
				LoadInFail(48 - 15, 20);
				system("cls");			//清除屏幕进入下一界面
				interFacemainWrong();	//密码输入错误的情况下重新回到函数头
			}
		}
		//5.还原产线监督工程师的登陆现场
		else if (resultID == 4) {
			printf("产线监督工程师");
			Gotoxy(48 + 26, 14);
			printf("/");
			Gotoxy(48 - 9, 16);		//动态移动光标
			printf("员工密码：\n");
			Gotoxy(45 + 14, 16);		//动态移动光标
			while (x < 4 && c != 13)   //13是回车符的ASCII码
			{
				c = getch();
				password[x++] = c;
				if (c != 13)
					putchar('*');
			}
			password[x] = '\0';
			Gotoxy(48 + 26, 16);
			charRotation();
			if (strcmp("0003\0", password) == 0) {
				Gotoxy(48 + 26, 16);
				charRotation();			//在这里执行验证身份信息
				/*测试浪费时间锁
				LoadInSuccess(48 - 15, 20);
				Sleep(1000);
				//*/
				system("cls");			//清除屏幕进入下一界面
				SuperPLInterface();
			}
			else {
				Gotoxy(48 - 20, 18);
				LoadInFail(48 - 15, 20);
				system("cls");			//清除屏幕进入下一界面
				interFacemainWrong();	//密码输入错误的情况下重新回到函数头
			}
		}
		//6还原产品销售员的登陆现场
		else if (resultID == 5) {
			printf("产品销售员");
			Gotoxy(48 + 26, 14);
			printf("/");
			Gotoxy(48 - 9, 16);		//动态移动光标
			printf("员工密码：\n");
			Gotoxy(45 + 14, 16);		//动态移动光标
			while (x < 4 && c != 13)   //13是回车符的ASCII码
			{
				c = getch();
				password[x++] = c;
				if (c != 13)
					putchar('*');
			}
			password[x] = '\0';
			Gotoxy(48 + 26, 16);
			charRotation();
			if (strcmp("0004\0", password) == 0) {
				Gotoxy(48 + 26, 16);
				charRotation();			//在这里执行验证身份信息
				/*测试浪费时间锁
				LoadInSuccess(48 - 15, 20);
				Sleep(1000);
				//*/
				system("cls");			//清除屏幕进入下一界面
				proSalesInterface();
			}
			else {
				Gotoxy(48 - 20, 18);
				LoadInFail(48 - 15, 20);
				system("cls");			//清除屏幕进入下一界面
				interFacemainWrong();	//密码输入错误的情况下重新回到函数头
			}
		}
	}
}

//功能函数1：身份信息验证函数
int sys_loginID(char* employeeID) {		//用户身份验证
	//root权限身份验证
	if (strcmp( "root\n",employeeID)==0) {
		return 0;
	}
	//企业管理员身份验证
	if (strcmp("00\n", employeeID) == 0) {
		return 1;
	}
	//仓储管理员身份验证
	else if (strcmp("01\n", employeeID) == 0 || strcmp(employeeID, "02\n") == 0 || strcmp("03\n", employeeID) == 0 || strcmp("04\n", employeeID) == 0 || strcmp("05\n", employeeID) == 0){
		return 2;
	}
	//工艺流程链设计师身份验证
	else if (strcmp("06\n",employeeID ) == 0 || strcmp(employeeID, "07\n") == 0 || strcmp("08\n",employeeID ) == 0 || strcmp("09\n", employeeID) == 0 || strcmp("10\n",employeeID) == 0) {
		return 3;
	}
	//产线监督工程师身份验证	
	else if (strcmp("11\n", employeeID) == 0 || strcmp(employeeID, "12\n") == 0 || strcmp("13\n", employeeID) == 0 || strcmp("14\n", employeeID) == 0 || strcmp("15\n", employeeID) == 0) {
		return 4;
	}
	//产品销售员身份验证
	else if (strcmp("16\n", employeeID) == 0 || strcmp(employeeID, "17\n") == 0 || strcmp("18\n", employeeID) == 0 || strcmp("19\n", employeeID) == 0 || strcmp("20\n", employeeID) == 0) {
		return 5;
	}
	else return 7;
}