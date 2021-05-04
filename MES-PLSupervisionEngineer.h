#include<stdio.h>
#include <stdio.h>
#include <windows.h>
#include<process.h>
#include <time.h>

//因为工厂产线和机床较为复杂，一般不会有增删改查，在鲁班MES中
//我直接使用结构体变变量作为原始状态来使用，并设置四条产线，三台机床

typedef struct ProductionLine {		//工厂产线结构
	int  Line_id;					//工厂产线编号
	char Line_name[20];				//工厂产线名称
	char Line_condition[30];		//工厂产线工作状态
	char Line_Product[30];			//工厂产线加工产品名称
	int  Line_Worktime;				//工厂产线加工时间
};

typedef struct ProductionTool {		//工厂机床结构
	int  Tool_id;					//工厂机床编号
	char Tool_name[20];				//工厂机床名称
	char Tool_condition[30];		//工厂机床工作状态
	char Tool_Product[30];			//工厂机床加工产品名称
	int  Tool_Worktime;				//工厂机床加工时间
};

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