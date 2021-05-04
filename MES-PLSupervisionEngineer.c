#include<stdio.h>
#include <stdlib.h>
#include <windows.h>
#include<process.h>
#include<string.h>
#include"MES-PLSupervisionEngineer.h"
#include"Globals.h"

#define _CRT_SECURE_NO_DEPRECATE；
#define _CRT_SECURE_NO_WARNINGS；
#pragma warning(disable:4996)；

struct ProductionLine P1 = { 1 ,"产线 1","等待中","无",0 };
struct ProductionLine P2 = { 2 ,"产线 2","等待中","无",0 };
struct ProductionLine P3 = { 3 ,"产线 3","等待中","无",0 };
struct ProductionLine P4 = { 4 ,"产线 4","等待中","无",0 };

struct ProductionTool T1 = { 1 ,"机床 1","等待中","无",0 };
struct ProductionTool T2 = { 2 ,"机床 2","等待中","无",0 };
struct ProductionTool T3 = { 3 ,"机床 3","等待中","无",0 };

//1.智慧工厂产线初始化功能
void ProductionLineInit();

//2.智慧工厂机床初始化功能
void ProductionToolInit();

//界面设计
void SuperPLInterface();

//1.工厂产线工作安排
void arrangePLine(int type);

//2.工厂产线工作查看
void checkPLine(int type);

//3.工厂产线工作取消
void cancelPLine(int type);

//4.工厂产线检修维护
void fixPLine(int type);

//5.工厂机床工作安排
void arrangePTool(int type);

//6.工厂机床工作查看
void checkPTool(int type);

//7.工厂机床工作取消
void cancelPTool(int type);

//8.工厂机床检修维护
void fixPTool(int type);

//9.特殊接口函数--管理员工厂产线工作查看
void checkPLineAdmin();

//10.特殊接口函数--管理员工厂机床工作查看
void checkPToolAdmin();


//1.智慧工厂产线初始化功能
void ProductionLineInit() {
	struct ProductionLine P1 = { 1 ,"产线 1","等待中","无",0 };
	struct ProductionLine P2 = { 2 ,"产线 2","等待中","无",0 };
	struct ProductionLine P3 = { 3 ,"产线 3","等待中","无",0 };
	struct ProductionLine P4 = { 4 ,"产线 4","等待中","无",0 };
}

//2.智慧工厂机床初始化功能
void ProductionToolInit() {
	struct ProductionTool T1 = { 1 ,"机床 1","等待中","无",0 };
	struct ProductionTool T2 = { 2 ,"机床 2","等待中","无",0 };
	struct ProductionTool T3 = { 3 ,"机床 3","等待中","无",0 };
}

//界面设计
void SuperPLInterface() {
	int choice;
	smartFactoryShow();
	Gotoxy(68+13+2, 4);
	printf("产线监督工程师管理面板");
	Gotoxy(68 + 13, 7);
	printf("1.工 厂 产 线 工 作 安 排");
	Gotoxy(68 + 13, 9);
	printf("2.工 厂 产 线 工 作 查 看");
	Gotoxy(68 + 13, 11);
	printf("3.工 厂 产 线 工 作 取 消");
	Gotoxy(68 + 13, 13);
	printf("4.工 厂 产 线 检 修 维 护");
	Gotoxy(68 + 13, 15);
	printf("5.工 厂 机 床 工 作 安 排");
	Gotoxy(68 + 13, 17);
	printf("6.工 厂 机 床 工 作 查 看");
	Gotoxy(68 + 13, 19);
	printf("7.工 厂 机 床 工 作 取 消");
	Gotoxy(68 + 13, 21);
	printf("8.工 厂 机 床 检 修 维 护");
	Gotoxy(68 + 13, 23);
	printf("9.退 出 鲁班  云MES 面 板");
	Gotoxy(68 + 13, 25);
	printf("请输入您需要操作的编码：");
	scanf("%d", &choice);
	Gotoxy(68 + 13 + 26, 25);
	charRotation();
	switch (choice) {
		//1.工 厂 产 线 工 作 安 排
		case 1: {
			int type;
			int  PLineID;
			smartFactoryShow();
			Gotoxy(68 + 13 - 5 + 7, 7);
			printf("智慧系统产线工作安排");
			Gotoxy(68+13 - 5,10);
			printf("请输入需要安排工作的产线：    ");
			scanf("%d", &PLineID);
			Gotoxy(68 + 13 +29+4, 10);
			charRotation();
			arrangePLine(PLineID);
		}
		//2.工 厂 产 线 工 作 查 看
		case 2: {
			int type;
			int  PLineID;
			smartFactoryShow();
			Gotoxy(68 + 13 - 5 + 7, 7);
			printf("智慧系统产线工作查看");
			Gotoxy(68 + 13 - 5, 10);
			printf("请输入需要查看工作的产线：     ");
			scanf("%d", &PLineID);
			Gotoxy(68 + 13 + 29 + 4, 10);
			charRotation();
			checkPLine(PLineID);
		}
		//3.工 厂 产 线 工 作 取 消
		case 3: {
			int type;
			int  PLineID;
			smartFactoryShow();
			Gotoxy(68 + 13 - 5 + 7, 7);
			printf("智慧系统产线工作取消");
			Gotoxy(68 + 13 - 5, 10);
			printf("请输入需要取消工作的产线：    ");
			scanf("%d", &PLineID);
			Gotoxy(68 + 13 + 29 + 4, 10);
			charRotation();
			cancelPLine(PLineID);
		}
		//4.工 厂 产 线 检 修 维 护
		case 4: {
			int type;
			int  PLineID;
			smartFactoryShow();
			Gotoxy(68 + 13 - 5 + 7, 7);
			printf("智慧系统产线检修维护");
			Gotoxy(68 + 13 - 5, 10);
			printf("请输入需要维护工作的产线：    ");
			scanf("%d", &PLineID);
			Gotoxy(68 + 13 + 29 + 4, 10);
			charRotation();
			fixPLine(PLineID);
		}
		//5.工 厂 机 床 工 作 安 排
		case 5: {
			int type;
			int  PToolID;
			smartFactoryShow();
			Gotoxy(68 + 13 - 5 + 7, 7);
			printf("智慧系统机床工作安排");
			Gotoxy(68 + 13 - 5, 10);
			printf("请输入需要安排工作的机床：    ");
			scanf("%d", &PToolID);
			Gotoxy(68 + 13 + 29 + 4, 10);
			charRotation();
			arrangePTool(PToolID);
		}
		//6.工 厂 机 床 工 作 查 看
		case 6: {
			int type;
			int  PToolID;
			smartFactoryShow();
			Gotoxy(68 + 13 - 5 + 7, 7);
			printf("智慧系统机床工作查看");
			Gotoxy(68 + 13 - 5, 10);
			printf("请输入需要查看工作的机床：     ");
			scanf("%d", &PToolID);
			Gotoxy(68 + 13 + 29 + 4, 10);
			charRotation();
			checkPTool(PToolID);
		}
		//7.工 厂 机 床 工 作 取 消
		case 7: {
			int type;
			int  PToolID;
			smartFactoryShow();
			Gotoxy(68 + 13 - 5 + 7, 7);
			printf("智慧系统机床工作取消");
			Gotoxy(68 + 13 - 5, 10);
			printf("请输入需要取消工作的机床：    ");
			scanf("%d", &PToolID);
			Gotoxy(68 + 13 + 29 + 4, 10);
			charRotation();
			cancelPTool(PToolID);
		}
		//8.工 厂 机 床 检 修 维 护
		case 8: {
			int type;
			int  PToolID;
			smartFactoryShow();
			Gotoxy(68 + 13 - 5 + 7, 7);
			printf("智慧系统机床检修维护");
			Gotoxy(68 + 13 - 5, 10);
			printf("请输入需要维护工作的机床：    ");
			scanf("%d", &PToolID);
			Gotoxy(68 + 13 + 29 + 4, 10);
			charRotation();
			fixPTool(PToolID);
		}
		//9.退 出 鲁班 云MES 面 板
		case 9: {
			errorTemplate(47, "正在退出鲁班云MES智慧面板！");
			exitMES(4);
		}
		//输入编号有误的情况下
		default: {
			errorTemplate(47.5, "输入编号有误，请重新输入！");
			SuperPLInterface();
		}	
	}
}

//1.工厂产线工作安排
void arrangePLine(int type) {
	//产线1工作安排
	if (type == 1) {
		if (strcmp(P1.Line_condition, "待维护") == 0) {
			errorTemplate(47, "产线 1待维护中，安排失败！");
			SuperPLInterface();
		}
		else if (strcmp(P1.Line_condition, "工作中") == 0) {
			errorTemplate(47, "产线 1正在工作，安排失败！");
			SuperPLInterface();
		}
		else {
			int newTime = 0;
			char newProduct[30];
			memset(P1.Line_Product, 0, sizeof(P1.Line_Product));	//先清空数组再赋值
			Gotoxy(68 + 13 - 5, 12);
			printf("请您输入需要加工的产品： ");
			scanf("%s", newProduct);
			strcpy(P1.Line_Product, newProduct);		//将输入的内容重新拷贝进去
			Gotoxy(68 + 13 + 29 + 4, 12);
			charRotation();
			Gotoxy(68 + 13 - 5, 14);
			printf("请您输入产线加工的工时：      ");
			scanf("%d", &newTime);
			P1.Line_Worktime = newTime;		//将输入的内容重新拷贝进去
			Gotoxy(68 + 13 + 29 + 4, 14);
			charRotation();
			memset(P1.Line_condition, 0, sizeof(P1.Line_condition));	//先清空数组再赋值
			strcpy(P1.Line_condition, "工作中");
			errorTemplate(47.5, "智慧系统开始安排产线工作！");
			SuperPLInterface();
		}
	}
	//产线2工作安排
	else if (type == 2) {
		if (strcmp(P2.Line_condition, "待维护") == 0) {
			errorTemplate(47, "产线 2待维护中，安排失败！");
			SuperPLInterface();
		}
		else if (strcmp(P2.Line_condition, "工作中") == 0) {
			errorTemplate(47, "产线 2正在工作，安排失败！");
			SuperPLInterface();
		}
		else {
			int newTime = 0;
			char newProduct[30];
			memset(P2.Line_Product, 0, sizeof(P2.Line_Product));	//先清空数组再赋值
			Gotoxy(68 + 13 - 5, 12);
			printf("请您输入需要加工的产品： ");
			scanf("%s", newProduct);
			strcpy(P2.Line_Product, newProduct);		//将输入的内容重新拷贝进去
			Gotoxy(68 + 13 + 29 + 4, 12);
			charRotation();
			Gotoxy(68 + 13 - 5, 14);
			printf("请您输入产线加工的工时：      ");
			scanf("%d", &newTime);
			P1.Line_Worktime = newTime;		//将输入的内容重新拷贝进去
			Gotoxy(68 + 13 + 29 + 4, 14);
			charRotation();
			memset(P2.Line_condition, 0, sizeof(P2.Line_condition));	//先清空数组再赋值
			strcpy(P2.Line_condition, "工作中");
			errorTemplate(47.5, "智慧系统开始安排产线工作！");
			SuperPLInterface();
		}
	}
	//产线3工作安排
	else if (type==3) {
		if (strcmp(P3.Line_condition, "待维护") == 0) {
			errorTemplate(47, "产线 3待维护中，安排失败！");
			SuperPLInterface();
		}
		else if (strcmp(P3.Line_condition, "工作中") == 0) {
			errorTemplate(47, "产线 3正在工作，安排失败！");
			SuperPLInterface();
		}
		else {
			int newTime = 0;
			char newProduct[30];
			memset(P3.Line_Product, 0, sizeof(P3.Line_Product));	//先清空数组再赋值
			Gotoxy(68 + 13 - 5, 12);
			printf("请您输入需要加工的产品： ");
			scanf("%s", newProduct);
			strcpy(P3.Line_Product, newProduct);		//将输入的内容重新拷贝进去
			Gotoxy(68 + 13 + 29 + 4, 12);
			charRotation();
			Gotoxy(68 + 13 - 5, 14);
			printf("请您输入产线加工的工时：      ");
			scanf("%d", &newTime);
			P1.Line_Worktime = newTime;		//将输入的内容重新拷贝进去
			Gotoxy(68 + 13 + 29 + 4, 14);
			charRotation();
			memset(P3.Line_condition, 0, sizeof(P3.Line_condition));	//先清空数组再赋值
			strcpy(P3.Line_condition, "工作中");
			errorTemplate(47.5, "智慧系统开始安排产线工作！");
			SuperPLInterface();
		}
		
	}
	//产线4工作安排
	else if (type == 4) {
		if(strcmp(P4.Line_condition, "待维护") == 0) {
			errorTemplate(47, "产线 4待维护中，安排失败！");
			SuperPLInterface();
		}
		else if (strcmp(P4.Line_condition, "工作中") == 0) {
			errorTemplate(47, "产线 4正在工作，安排失败！");
			SuperPLInterface();
		}
		else {
			int newTime = 0;
			char newProduct[30];
			memset(P4.Line_Product, 0, sizeof(P4.Line_Product));	//先清空数组再赋值
			Gotoxy(68 + 13 - 5, 12);
			printf("请您输入需要加工的产品： ");
			scanf("%s", newProduct);
			strcpy(P4.Line_Product, newProduct);		//将输入的内容重新拷贝进去
			Gotoxy(68 + 13 + 29 + 4, 12);
			charRotation();
			Gotoxy(68 + 13 - 5, 14);
			printf("请您输入产线加工的工时：      ");
			scanf("%d", &newTime);
			P1.Line_Worktime = newTime;		//将输入的内容重新拷贝进去
			Gotoxy(68 + 13 + 29 + 4, 14);
			charRotation();
			memset(P4.Line_condition, 0, sizeof(P4.Line_condition));	//先清空数组再赋值
			strcpy(P4.Line_condition, "工作中");
			errorTemplate(47.5, "智慧系统开始安排产线工作！");
			SuperPLInterface();
		}
	}
	//当输入的产线编号有问题的时候
	else{
		errorTemplate(48.5, "智慧系统查找无此产线！");
		SuperPLInterface();
	}
}

//2.工厂产线工作查看
void checkPLine(int type) {
	//查看产线1工作状况
	if (type == 1) {
		Gotoxy(68 + 13 - 5, 12);
		printf("产线1 正在加工的产品：   ");
		if (strcmp(P1.Line_Product, "无")==0){
			Gotoxy(68 + 13 - 5 + 26 + 5, 12);
			printf("%s", P1.Line_Product);
		}
		else  printf("%s", P1.Line_Product);
		Gotoxy(68 + 13 - 5, 14);
		printf("产线1 加工产品的工时：         ");
		printf("%d", P1.Line_Worktime);
		Gotoxy(68 + 13 - 5, 16);
		printf("产线1 目前的工作状态：       ");
		printf("%s", P1.Line_condition);
		char yes[3];
		Gotoxy(68 + 13 - 5, 18);
		printf("查看后输入任意键返回面板：     ");
		scanf("%s", yes);
		//输入任意值情况下,执行相同的效果
		if (yes[0] == 'y') {
			Gotoxy(68 + 13 - 5 + 32+2, 18);
			charRotation();
			Sleep(1000);
			SuperPLInterface();
		}
		//输入任意值情况下,执行相同的效果
		else {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			SuperPLInterface();
		}
	}
	//查看产线2工作状况
	else if (type == 2) {
		Gotoxy(68 + 13 - 5, 12);
		printf("产线2 正在加工的产品：   ");
		if (strcmp(P2.Line_Product, "无") == 0) {
			Gotoxy(68 + 13 - 5 + 26 + 5, 12);
			printf("%s", P2.Line_Product);
		}
		else  printf("%s", P2.Line_Product);
		Gotoxy(68 + 13 - 5, 14);
		printf("产线2 加工产品的工时：         ");
		printf("%d", P2.Line_Worktime);
		Gotoxy(68 + 13 - 5, 16);
		printf("产线2 目前的工作状态：       ");
		printf("%s", P2.Line_condition);
		char yes[3];
		Gotoxy(68 + 13 - 5, 18);
		printf("查看后输入任意键返回面板：     ");
		scanf("%s", yes);
		//输入任意值情况下,执行相同的效果
		if (yes[0] == 'y') {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			SuperPLInterface();
		}
		//输入任意值情况下,执行相同的效果
		else {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			SuperPLInterface();
		}
	}
	//查看产线3工作状况
	else if (type == 3) {
		Gotoxy(68 + 13 - 5, 12);
		printf("产线3 正在加工的产品：   ");
		if (strcmp(P3.Line_Product, "无") == 0) {
			Gotoxy(68 + 13 - 5 + 26 + 5, 12);
			printf("%s", P3.Line_Product);
		}
		else  printf("%s", P3.Line_Product);
		Gotoxy(68 + 13 - 5, 14);
		printf("产线3 加工产品的工时：         ");
		printf("%d", P3.Line_Worktime);
		Gotoxy(68 + 13 - 5, 16);
		printf("产线3 目前的工作状态：       ");
		printf("%s", P3.Line_condition);
		char yes[3];
		Gotoxy(68 + 13 - 5, 18);
		printf("查看后输入任意键返回面板：     ");
		scanf("%s", yes);
		//输入任意值情况下,执行相同的效果
		if (yes[0] == 'y') {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			SuperPLInterface();
		}
		//输入任意值情况下,执行相同的效果
		else {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			SuperPLInterface();
		}
	}
	//查看产线4工作状况
	else if (type = 4) {
		Gotoxy(68 + 13 - 5, 12);
		printf("产线4 正在加工的产品：   ");
		if (strcmp(P4.Line_Product, "无") == 0) {
			Gotoxy(68 + 13 - 5 + 26 + 5, 12);
			printf("%s", P4.Line_Product);
		}
		else  printf("%s", P4.Line_Product);
		Gotoxy(68 + 13 - 5, 14);
		printf("产线4 加工产品的工时：         ");
		printf("%d", P4.Line_Worktime);
		Gotoxy(68 + 13 - 5, 16);
		printf("产线4 目前的工作状态：       ");
		printf("%s", P4.Line_condition);
		char yes[3];
		Gotoxy(68 + 13 - 5, 18);
		printf("查看后输入任意键返回面板：     ");
		scanf("%s", yes);
		//输入任意值情况下,执行相同的效果
		if (yes[0] == 'y') {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			SuperPLInterface();
		}
		//输入任意值情况下,执行相同的效果
		else {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			SuperPLInterface();
		}
}
	//当输入产线编号错误的时候
	else {
		errorTemplate(48.5, "智慧系统查找无此产线！");
		SuperPLInterface();
	}
}

//3.工厂产线工作取消
void cancelPLine(int type) {
	if (type == 1) {
		if (strcmp(P1.Line_condition, "待维护") == 0) {
			errorTemplate(47, "产线 1待维护中，取消失败！");
			SuperPLInterface();
		}
		else if (strcmp(P1.Line_condition, "等待中") == 0) {
			errorTemplate(47.5, "产线 1等待中，取消失败！");
			SuperPLInterface();
		}
		else {
			int condition;
			//因为取消产线的工作产线很容易进入需维护的状态
			//随机生产种子值，对产线的状态需要进行模拟，这里范围（1~100）
			condition = rand() % 100 + 1;
			if (condition <= 100 && condition >= 40) strcpy(P1.Line_condition, "待维护");
			else strcpy(P1.Line_condition, "等待中");
			strcpy(P1.Line_Product, "无");
			P1.Line_Worktime = 0;
			errorTemplate(48, "智慧系统取消产线工作中！");
			if (strcmp(P1.Line_condition, "待维护") == 0) {
				errorTemplate(48, "提示： 产线1待维护中！！");
				SuperPLInterface();
			}
			SuperPLInterface();
		}
	}
	//取消产线 2的工作
	else if( type== 2) {
		if (strcmp(P2.Line_condition, "待维护") == 0) {
			errorTemplate(47, "产线 2待维护中，取消失败！");
			SuperPLInterface();
		}
		else if (strcmp(P2.Line_condition, "等待中") == 0) {
			errorTemplate(47.5, "产线 2等待中，取消失败！");
			SuperPLInterface();
		}
		else {
			int condition;
			//因为取消产线的工作产线很容易进入需维护的状态
			//随机生产种子值，对产线的状态需要进行模拟，这里范围（1~100）
			condition = rand() % 100 + 1;
			if (condition <= 100 && condition >= 40) strcpy(P2.Line_condition, "待维护");
			else strcpy(P2.Line_condition, "等待中");
			strcpy(P2.Line_Product, "无");
			P2.Line_Worktime = 0;
			errorTemplate(48, "智慧系统取消产线工作中！");
			if (strcmp(P2.Line_condition, "待维护") == 0) {
				errorTemplate(48, "提示： 产线2待维护中！！");
				SuperPLInterface();
			}
			SuperPLInterface();
		}
	}
	//取消产线 3的工作
	else if (type == 3) {
		if (strcmp(P3.Line_condition, "待维护") == 0) {
			errorTemplate(47, "产线 3待维护中，取消失败！");
			SuperPLInterface();
		}
		else if (strcmp(P3.Line_condition, "等待中") == 0) {
			errorTemplate(47.5, "产线 3等待中，取消失败！");
			SuperPLInterface();
		}
		else{
			int condition;
			//因为取消产线的工作产线很容易进入需维护的状态
			//随机生产种子值，对产线的状态需要进行模拟，这里范围（1~100）
			condition = rand() % 100 + 1;
			if (condition <= 100 && condition >= 40) strcpy(P3.Line_condition, "待维护");
			else strcpy(P3.Line_condition, "等待中");
			strcpy(P3.Line_Product, "无");
			P3.Line_Worktime = 0;
			errorTemplate(48, "智慧系统取消产线工作中！");
			if (strcmp(P3.Line_condition, "待维护") == 0) {
				errorTemplate(48, "提示： 产线3待维护中！！");
				SuperPLInterface();
			}
			SuperPLInterface();
		}
	}
	//取消产线 4的工作
	else if (type ==  4) {
		if (strcmp(P4.Line_condition, "待维护") == 0) {
			errorTemplate(47, "产线 4待维护中，取消失败！");
			SuperPLInterface();
		}
		else if (strcmp(P4.Line_condition, "等待中") == 0) {
			errorTemplate(47.5, "产线 4等待中，取消失败！");
			SuperPLInterface();
		}
		else {
			int condition;
			//因为取消产线的工作产线很容易进入需维护的状态
			//随机生产种子值，对产线的状态需要进行模拟，这里范围（1~100）
			condition = rand() % 100 + 1;
			if (condition <= 100 && condition >= 40) strcpy(P4.Line_condition, "待维护");
			else strcpy(P4.Line_condition, "等待中");
			strcpy(P4.Line_Product, "无");
			P4.Line_Worktime = 0;
			errorTemplate(48, "智慧系统取消产线工作中！");
			if (strcmp(P4.Line_condition, "待维护") == 0) {
				errorTemplate(48, "提示： 产线4待维护中！！");
				SuperPLInterface();
			}
			SuperPLInterface();
		}
	}
	//当输入的编号错误的时候
	else {
		errorTemplate(48.5, "智慧系统查找无此产线！");
		SuperPLInterface();
	}
}

//4.工厂产线检修维护
void fixPLine(int type) {
	//产线1需要提供检修维护
	if (type == 1) {
		//产线1正处于待维护状态时
		if (strcmp(P1.Line_condition, "待维护") == 0) {
			strcpy(P1.Line_condition, "等待中");
			errorTemplate(49, "工程师正在维护产线中！");
			errorTemplate(49, "   产线 1维护成功！   ");
			SuperPLInterface();
		}
		//其余情况
		else {
			errorTemplate(46, "智慧系统检测到产线无需维护！");
			SuperPLInterface();
		}
	}
	//产线2需要提供检修维护
	else if (type == 2) {
		if (strcmp(P2.Line_condition, "待维护") == 0) {
			strcpy(P2.Line_condition, "等待中");
			errorTemplate(49, "工程师正在维护产线中！");
			errorTemplate(49, "   产线 2维护成功！   ");
			SuperPLInterface();
		}
		//其余情况
		else {
			errorTemplate(46, "智慧系统检测到产线无需维护！");
			SuperPLInterface();
		}
	}
	//产线3需要提供检修维护
	else if (type == 3) {
		if (strcmp(P3.Line_condition, "待维护") == 0) {
			strcpy(P3.Line_condition, "等待中");
			errorTemplate(49, "工程师正在维护产线中！");
			errorTemplate(49, "   产线 3维护成功！   ");
			SuperPLInterface();
		}
		//其余情况
		else {
			errorTemplate(46, "智慧系统检测到产线无需维护！");
			SuperPLInterface();
		}
	}
	//产线3需要提供检修维护
	else if (type == 4) {
		if (strcmp(P4.Line_condition, "待维护") == 0) {
			strcpy(P4.Line_condition, "等待中");
			errorTemplate(49, "工程师正在维护产线中！");
			errorTemplate(49, "   产线 4维护成功！   ");
			SuperPLInterface();
		}
		//其余情况
		else {
			errorTemplate(46, "智慧系统检测到产线无需维护！");
			SuperPLInterface();
		}
	}
	//输入产线编号错误时
	else {
		errorTemplate(48.5, "智慧系统查找无此产线！");
		SuperPLInterface();
	}
}

//5.工厂机床工作安排
void arrangePTool(int type) {
	//机床 1工作安排
	if (type == 1) {
		if (strcmp(T1.Tool_condition, "待维护") == 0) {
			errorTemplate(47, "机床 1待维护中，安排失败！");
			SuperPLInterface();
		}
		else if (strcmp(T1.Tool_condition, "工作中") == 0) {
			errorTemplate(47, "机床 1正在工作，安排失败！");
			SuperPLInterface();
		}
		else {
			int newTime = 0;
			char newProduct[30];
			memset(T1.Tool_Product, 0, sizeof(T1.Tool_Product));	//先清空数组再赋值
			Gotoxy(68 + 13 - 5, 12);
			printf("请您输入需要加工的产品： ");
			scanf("%s", newProduct);
			strcpy(T1.Tool_Product, newProduct);		//将输入的内容重新拷贝进去
			Gotoxy(68 + 13 + 29 + 4, 12);
			charRotation();
			Gotoxy(68 + 13 - 5, 14);
			printf("请您输入机床加工的工时：      ");
			scanf("%d", &newTime);
			T1.Tool_Worktime = newTime;		//将输入的内容重新拷贝进去
			Gotoxy(68 + 13 + 29 + 4, 14);
			charRotation();
			memset(T1.Tool_condition, 0, sizeof(T1.Tool_condition));	//先清空数组再赋值
			strcpy(T1.Tool_condition, "工作中");
			errorTemplate(47.5, "智慧系统开始安排机床工作！");
			SuperPLInterface();
		}
	}
	//机床2工作安排
	else if (type == 2) {
		if (strcmp(T2.Tool_condition, "待维护") == 0) {
			errorTemplate(47, "机床 2待维护中，安排失败！");
			SuperPLInterface();
		}
		else if (strcmp(T2.Tool_condition, "工作中") == 0) {
			errorTemplate(47, "机床 2正在工作，安排失败！");
			SuperPLInterface();
		}
		else {
			int newTime = 0;
			char newProduct[30];
			memset(T2.Tool_Product, 0, sizeof(T2.Tool_Product));	//先清空数组再赋值
			Gotoxy(68 + 13 - 5, 12);
			printf("请您输入需要加工的产品： ");
			scanf("%s", newProduct);
			strcpy(T2.Tool_Product, newProduct);		//将输入的内容重新拷贝进去
			Gotoxy(68 + 13 + 29 + 4, 12);
			charRotation();
			Gotoxy(68 + 13 - 5, 14);
			printf("请您输入机床加工的工时：      ");
			scanf("%d", &newTime);
			T2.Tool_Worktime = newTime;		//将输入的内容重新拷贝进去
			Gotoxy(68 + 13 + 29 + 4, 14);
			charRotation();
			memset(T2.Tool_condition, 0, sizeof(T2.Tool_condition));	//先清空数组再赋值
			strcpy(T2.Tool_condition, "工作中");
			errorTemplate(47.5, "智慧系统开始安排机床工作！");
			SuperPLInterface();
		}
	}
	//产线3工作安排
	else if (type == 3) {
		if (strcmp(T3.Tool_condition, "待维护") == 0) {
			errorTemplate(47, "机床 3待维护中，安排失败！");
			SuperPLInterface();
		}
		else if (strcmp(T3.Tool_condition, "工作中") == 0) {
			errorTemplate(47, "机床 3正在工作，安排失败！");
			SuperPLInterface();
		}
		else {
			int newTime = 0;
			char newProduct[30];
			memset(T3.Tool_Product, 0, sizeof(T3.Tool_Product));	//先清空数组再赋值
			Gotoxy(68 + 13 - 5, 12);
			printf("请您输入需要加工的产品： ");
			scanf("%s", newProduct);
			strcpy(T3.Tool_Product, newProduct);		//将输入的内容重新拷贝进去
			Gotoxy(68 + 13 + 29 + 4, 12);
			charRotation();
			Gotoxy(68 + 13 - 5, 14);
			printf("请您输入机床加工的工时：      ");
			scanf("%d", &newTime);
			T3.Tool_Worktime = newTime;		//将输入的内容重新拷贝进去
			Gotoxy(68 + 13 + 29 + 4, 14);
			charRotation();
			memset(T3.Tool_condition, 0, sizeof(T3.Tool_condition));	//先清空数组再赋值
			strcpy(T3.Tool_condition, "工作中");
			errorTemplate(47.5, "智慧系统开始安排机床工作！");
			SuperPLInterface();
		}
	}
	//当输入的产线编号有问题的时候
	else {
		errorTemplate(48.5, "智慧系统查找无此机床！");
		SuperPLInterface();
	}
}

//6.工厂机床工作查看
void checkPTool(int type) {
	//查看机床1工作状况
	if (type == 1) {
		Gotoxy(68 + 13 - 5, 12);
		printf("机床1 正在加工的产品：   ");
		if (strcmp(T1.Tool_Product, "无") == 0) {
			Gotoxy(68 + 13 - 5 + 26 + 5, 12);
			printf("%s", T1.Tool_Product);
		}
		else  printf("%s", T1.Tool_Product);
		Gotoxy(68 + 13 - 5, 14);
		printf("机床1 加工产品的工时：         ");
		printf("%d", T1.Tool_Worktime);
		Gotoxy(68 + 13 - 5, 16);
		printf("机床1 目前的工作状态：       ");
		printf("%s", T1.Tool_condition);
		char yes[3];
		Gotoxy(68 + 13 - 5, 18);
		printf("查看后输入任意键返回面板：     ");
		scanf("%s", yes);
		//输入任意值情况下,执行相同的效果
		if (yes[0] == 'y') {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			SuperPLInterface();
		}
		//输入任意值情况下,执行相同的效果
		else {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			SuperPLInterface();
		}
	}
	//查看机床 2工作状况
	else if (type == 2) {
		Gotoxy(68 + 13 - 5, 12);
		printf("机床 2正在加工的产品：   ");
		if (strcmp(T2.Tool_Product, "无") == 0) {
			Gotoxy(68 + 13 - 5 + 26 + 5, 12);
			printf("%s", T2.Tool_Product);
		}
		else  printf("%s", T2.Tool_Product);
		Gotoxy(68 + 13 - 5, 14);
		printf("机床 2加工产品的工时：         ");
		printf("%d", T2.Tool_Worktime);
		Gotoxy(68 + 13 - 5, 16);
		printf("机床 2目前的工作状态：       ");
		printf("%s", T2.Tool_condition);
		char yes[3];
		Gotoxy(68 + 13 - 5, 18);
		printf("查看后输入任意键返回面板：     ");
		scanf("%s", yes);
		//输入任意值情况下,执行相同的效果
		if (yes[0] == 'y') {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			SuperPLInterface();
		}
		//输入任意值情况下,执行相同的效果
		else {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			SuperPLInterface();
		}
	}
	//查看机床 3工作状况
	else if (type == 3) {
		Gotoxy(68 + 13 - 5, 12);
		printf("机床 3正在加工的产品：   ");
		if (strcmp(T3.Tool_Product, "无") == 0) {
			Gotoxy(68 + 13 - 5 + 26 + 5, 12);
			printf("%s", T3.Tool_Product);
		}
		else  printf("%s", T3.Tool_Product);
		Gotoxy(68 + 13 - 5, 14);
		printf("机床 3加工产品的工时：         ");
		printf("%d", T3.Tool_Worktime);
		Gotoxy(68 + 13 - 5, 16);
		printf("机床 3目前的工作状态：       ");
		printf("%s", T3.Tool_condition);
		char yes[3];
		Gotoxy(68 + 13 - 5, 18);
		printf("查看后输入任意键返回面板：     ");
		scanf("%s", yes);
		//输入任意值情况下,执行相同的效果
		if (yes[0] == 'y') {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			SuperPLInterface();
		}
		//输入任意值情况下,执行相同的效果
		else {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			SuperPLInterface();
		}
	}

	//当输入产线编号错误的时候
	else {
		errorTemplate(48.5, "智慧系统查找无此机床！");
		SuperPLInterface();
	}
}

//7.工厂机床工作取消
void cancelPTool(int type) {
	if (type == 1) {
		if (strcmp(T1.Tool_condition, "待维护") == 0) {
			errorTemplate(47, "机床 1待维护中，取消失败！");
			SuperPLInterface();
		}
		else if (strcmp(T1.Tool_condition, "等待中") == 0) {
			errorTemplate(47.5, "机床 1等待中，取消失败！");
			SuperPLInterface();
		}
		else {
			int condition;
			//因为取消机床的工作机床很容易进入需维护的状态
			//随机生产种子值，对机床的状态需要进行模拟，这里范围（1~100）
			condition = rand() % 100 + 1;
			if (condition <= 100 && condition >= 40) strcpy(T1.Tool_condition, "待维护");
			else strcpy(T1.Tool_condition, "等待中");
			strcpy(T1.Tool_Product, "无");
			T1.Tool_Worktime = 0;
			errorTemplate(48, "智慧系统取消机床工作中！");
			if (strcmp(T1.Tool_condition, "待维护") == 0) {
				errorTemplate(48, "提示： 机床1待维护中！！");
				SuperPLInterface();
			}
			SuperPLInterface();
		}
	}
	//取消机床 2的工作
	else if (type == 2) {
		if (strcmp(T2.Tool_condition, "待维护") == 0) {
			errorTemplate(47, "机床 2待维护中，取消失败！");
			SuperPLInterface();
		}
		else if (strcmp(T2.Tool_condition, "等待中") == 0) {
			errorTemplate(47.5, "机床 2等待中，取消失败！");
			SuperPLInterface();
		}
		else {
			int condition;
			//因为取消机床的工作机床很容易进入需维护的状态
			//随机生产种子值，对机床的状态需要进行模拟，这里范围（1~100）
			condition = rand() % 100 + 1;
			if (condition <= 100 && condition >= 40) strcpy(T2.Tool_condition, "待维护");
			else strcpy(T2.Tool_condition, "等待中");
			strcpy(T2.Tool_Product, "无");
			T2.Tool_Worktime = 0;
			errorTemplate(48, "智慧系统取消机床工作中！");
			if (strcmp(T2.Tool_condition, "待维护") == 0) {
				errorTemplate(48, "提示： 机床2待维护中！！");
				SuperPLInterface();
			}
			SuperPLInterface();
		}
	}
	//取消机床 3的工作
	else if (type == 3) {
		if (strcmp(T3.Tool_condition, "待维护") == 0) {
			errorTemplate(47, "机床 3待维护中，取消失败！");
			SuperPLInterface();
		}
		else if (strcmp(T3.Tool_condition, "等待中") == 0) {
			errorTemplate(47.5, "机床 3等待中，取消失败！");
			SuperPLInterface();
		}
		else {
			int condition;
			//因为取消机床的工作机床很容易进入需维护的状态
		//随机生产种子值，对机床的状态需要进行模拟，这里范围（1~100）
			condition = rand() % 100 + 1;
			if (condition <= 100 && condition >= 40) strcpy(T3.Tool_condition, "待维护");
			else strcpy(T3.Tool_condition, "等待中");
			strcpy(T3.Tool_Product, "无");
			T3.Tool_Worktime = 0;
			errorTemplate(48, "智慧系统取消机床工作中！");
			if (strcmp(T3.Tool_condition, "待维护") == 0) {
				errorTemplate(48, "提示： 机床3待维护中！！");
				SuperPLInterface();
			}
			SuperPLInterface();
		}
	}
	//当输入的编号错误的时候
	else {
		errorTemplate(48.5, "智慧系统查找无此机床！");
		SuperPLInterface();
	}
}

//8.工厂机床检修维护
void fixPTool(int type) {
	//机床 1需要提供检修维护
	if (type == 1) {
		//机床 1正处于待维护状态时
		if (strcmp(T1.Tool_condition, "待维护") == 0) {
			strcpy(T1.Tool_condition, "等待中");
			errorTemplate(49, "工程师正在维护机床中！");
			errorTemplate(49, "   机床 1维护成功！   ");
			SuperPLInterface();
		}
		//其余情况
		else {
			errorTemplate(46, "智慧系统检测到机床无需维护！");
			SuperPLInterface();
		}
	}
	//机床 2需要提供检修维护
	else if (type == 2) {
		if (strcmp(T2.Tool_condition, "待维护") == 0) {
			strcpy(T2.Tool_condition, "等待中");
			errorTemplate(49, "工程师正在维护机床中！");
			errorTemplate(49, "   机床 2维护成功！   ");
			SuperPLInterface();
		}
		//其余情况
		else {
			errorTemplate(46, "智慧系统检测到机床无需维护！");
			SuperPLInterface();
		}
	}
	//机床3需要提供检修维护
	else if (type == 3) {
		if (strcmp(T3.Tool_condition, "待维护") == 0) {
			strcpy(T3.Tool_condition, "等待中");
			errorTemplate(49, "工程师正在维护机床中！");
			errorTemplate(49, "   机床 3维护成功！   ");
			SuperPLInterface();
		}
		//其余情况
		else {
			errorTemplate(46, "智慧系统检测到机床无需维护！");
			SuperPLInterface();
		}
	}	
	//输入产线编号错误时
	else {
		errorTemplate(48.5, "智慧系统查找无此机床！");
		SuperPLInterface();
	}
}

//9.特殊接口函数--管理员工厂产线工作查看
void checkPLineAdmin(){
	int  PLineID;
	smartFactoryShow();
	Gotoxy(68 + 13 - 5 + 7, 7);
	printf("智慧系统产线工作查看");
	Gotoxy(68 + 13 - 5, 10);
	printf("请输入需要查看工作的产线：     ");
	scanf("%d", &PLineID);
	Gotoxy(68 + 13 + 29 + 4, 10);
	charRotation();
	//查看产线1工作状况
	if (PLineID == 1) {
		Gotoxy(68 + 13 - 5, 12);
		printf("产线1 正在加工的产品：   ");
		if (strcmp(P1.Line_Product, "无") == 0) {
			Gotoxy(68 + 13 - 5 + 26 + 5, 12);
			printf("%s", P1.Line_Product);
		}
		else  printf("%s", P1.Line_Product);
		Gotoxy(68 + 13 - 5, 14);
		printf("产线1 加工产品的工时：         ");
		printf("%d", P1.Line_Worktime);
		Gotoxy(68 + 13 - 5, 16);
		printf("产线1 目前的工作状态：       ");
		printf("%s", P1.Line_condition);
		char yes[3];
		Gotoxy(68 + 13 - 5, 18);
		printf("查看后输入任意键返回面板：     ");
		scanf("%s", yes);
		//输入任意值情况下,执行相同的效果
		if (yes[0] == 'y') {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			adminLeaderInterface();
		}
		//输入任意值情况下,执行相同的效果
		else {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			adminLeaderInterface();
		}
	}
	//查看产线2工作状况
	else if (PLineID == 2) {
		Gotoxy(68 + 13 - 5, 12);
		printf("产线2 正在加工的产品：   ");
		if (strcmp(P2.Line_Product, "无") == 0) {
			Gotoxy(68 + 13 - 5 + 26 + 5, 12);
			printf("%s", P2.Line_Product);
		}
		else  printf("%s", P2.Line_Product);
		Gotoxy(68 + 13 - 5, 14);
		printf("产线2 加工产品的工时：         ");
		printf("%d", P2.Line_Worktime);
		Gotoxy(68 + 13 - 5, 16);
		printf("产线2 目前的工作状态：       ");
		printf("%s", P2.Line_condition);
		char yes[3];
		Gotoxy(68 + 13 - 5, 18);
		printf("查看后输入任意键返回面板：     ");
		scanf("%s", yes);
		//输入任意值情况下,执行相同的效果
		if (yes[0] == 'y') {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			adminLeaderInterface();
		}
		//输入任意值情况下,执行相同的效果
		else {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			adminLeaderInterface();
		}
	}
	//查看产线3工作状况
	else if (PLineID == 3) {
		Gotoxy(68 + 13 - 5, 12);
		printf("产线3 正在加工的产品：   ");
		if (strcmp(P3.Line_Product, "无") == 0) {
			Gotoxy(68 + 13 - 5 + 26 + 5, 12);
			printf("%s", P3.Line_Product);
		}
		else  printf("%s", P3.Line_Product);
		Gotoxy(68 + 13 - 5, 14);
		printf("产线3 加工产品的工时：         ");
		printf("%d", P3.Line_Worktime);
		Gotoxy(68 + 13 - 5, 16);
		printf("产线3 目前的工作状态：       ");
		printf("%s", P3.Line_condition);
		char yes[3];
		Gotoxy(68 + 13 - 5, 18);
		printf("查看后输入任意键返回面板：     ");
		scanf("%s", yes);
		//输入任意值情况下,执行相同的效果
		if (yes[0] == 'y') {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			adminLeaderInterface();
		}
		//输入任意值情况下,执行相同的效果
		else {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			adminLeaderInterface();
		}
	}
	//查看产线4工作状况
	else if (PLineID = 4) {
		Gotoxy(68 + 13 - 5, 12);
		printf("产线4 正在加工的产品：   ");
		if (strcmp(P4.Line_Product, "无") == 0) {
			Gotoxy(68 + 13 - 5 + 26 + 5, 12);
			printf("%s", P4.Line_Product);
		}
		else  printf("%s", P4.Line_Product);
		Gotoxy(68 + 13 - 5, 14);
		printf("产线4 加工产品的工时：         ");
		printf("%d", P4.Line_Worktime);
		Gotoxy(68 + 13 - 5, 16);
		printf("产线4 目前的工作状态：       ");
		printf("%s", P4.Line_condition);
		char yes[3];
		Gotoxy(68 + 13 - 5, 18);
		printf("查看后输入任意键返回面板：     ");
		scanf("%s", yes);
		//输入任意值情况下,执行相同的效果
		if (yes[0] == 'y') {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			adminLeaderInterface();
		}
		//输入任意值情况下,执行相同的效果
		else {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			adminLeaderInterface();
		}
	}
	//当输入产线编号错误的时候
	else {
		errorTemplate(48.5, "智慧系统查找无此产线！");
		adminLeaderInterface();
	}
}

//10.特殊接口函数--管理员工厂机床工作查看
void checkPToolAdmin() {
	int  PToolID;
	smartFactoryShow();
	Gotoxy(68 + 13 - 5 + 7, 7);
	printf("智慧系统机床工作查看");
	Gotoxy(68 + 13 - 5, 10);
	printf("请输入需要查看工作的机床：     ");
	scanf("%d", &PToolID);
	Gotoxy(68 + 13 + 29 + 4, 10);
	charRotation();
	//查看机床1工作状况
	if (PToolID == 1) {
		Gotoxy(68 + 13 - 5, 12);
		printf("机床1 正在加工的产品：   ");
		if (strcmp(T1.Tool_Product, "无") == 0) {
			Gotoxy(68 + 13 - 5 + 26 + 5, 12);
			printf("%s", T1.Tool_Product);
		}
		else  printf("%s", T1.Tool_Product);
		Gotoxy(68 + 13 - 5, 14);
		printf("机床1 加工产品的工时：         ");
		printf("%d", T1.Tool_Worktime);
		Gotoxy(68 + 13 - 5, 16);
		printf("机床1 目前的工作状态：       ");
		printf("%s", T1.Tool_condition);
		char yes[3];
		Gotoxy(68 + 13 - 5, 18);
		printf("查看后输入任意键返回面板：     ");
		scanf("%s", yes);
		//输入任意值情况下,执行相同的效果
		if (yes[0] == 'y') {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			adminLeaderInterface();
		}
		//输入任意值情况下,执行相同的效果
		else {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			adminLeaderInterface();
		}
	}
	//查看机床 2工作状况
	else if (PToolID == 2) {
		Gotoxy(68 + 13 - 5, 12);
		printf("机床 2正在加工的产品：   ");
		if (strcmp(T2.Tool_Product, "无") == 0) {
			Gotoxy(68 + 13 - 5 + 26 + 5, 12);
			printf("%s", T2.Tool_Product);
		}
		else  printf("%s", T2.Tool_Product);
		Gotoxy(68 + 13 - 5, 14);
		printf("机床 2加工产品的工时：         ");
		printf("%d", T2.Tool_Worktime);
		Gotoxy(68 + 13 - 5, 16);
		printf("机床 2目前的工作状态：       ");
		printf("%s", T2.Tool_condition);
		char yes[3];
		Gotoxy(68 + 13 - 5, 18);
		printf("查看后输入任意键返回面板：     ");
		scanf("%s", yes);
		//输入任意值情况下,执行相同的效果
		if (yes[0] == 'y') {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			adminLeaderInterface();
		}
		//输入任意值情况下,执行相同的效果
		else {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			adminLeaderInterface();
		}
	}
	//查看机床 3工作状况
	else if (PToolID == 3) {
		Gotoxy(68 + 13 - 5, 12);
		printf("机床 3正在加工的产品：   ");
		if (strcmp(T3.Tool_Product, "无") == 0) {
			Gotoxy(68 + 13 - 5 + 26 + 5, 12);
			printf("%s", T3.Tool_Product);
		}
		else  printf("%s", T3.Tool_Product);
		Gotoxy(68 + 13 - 5, 14);
		printf("机床 3加工产品的工时：         ");
		printf("%d", T3.Tool_Worktime);
		Gotoxy(68 + 13 - 5, 16);
		printf("机床 3目前的工作状态：       ");
		printf("%s", T3.Tool_condition);
		char yes[3];
		Gotoxy(68 + 13 - 5, 18);
		printf("查看后输入任意键返回面板：     ");
		scanf("%s", yes);
		//输入任意值情况下,执行相同的效果
		if (yes[0] == 'y') {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			adminLeaderInterface();
		}
		//输入任意值情况下,执行相同的效果
		else {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			adminLeaderInterface();
		}
	}
	//当输入产线编号错误的时候
	else {
		errorTemplate(48.5, "智慧系统查找无此机床！");
		adminLeaderInterface();
	}
}
