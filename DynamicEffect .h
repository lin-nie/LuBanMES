/*本头文件的内容是关于动态的一些动画界面函数的使用，同时包括一些常用的框架使用*/

/*同时在本头文件中也包含了一些常用的静态框架结构等                            */
#include<stdio.h>
#include <stdio.h>
#include <windows.h>
#include<process.h>
#include <time.h>


typedef struct { double x, y; } Vec;

//特效函数1：隐藏光标
void HideCursor();
//特效函数2：光标按坐标x,y值移动
void Gotoxy(int x, int y);
//特效函数3：绘制进度条专用边框
void DrawBox(int x, int y);
//特效函数4：加载进度条成功函数
void LoadInSuccess(int x, int y);
//特效函数5：加载进度条失败函数
void LoadInFail(int x, int y);
//特效函数6：退出MES系统加载进度条
void LoadExitMES(int x, int y);
//特效函数7：退出MES系统加载进度条
void LoadRoot(int x, int y, int type);
//特效函数8：字符旋转加载特效
void charRotation();
//特效函数9：边框显示功能
void frameShow();

//鲁班MES工厂云智慧看板
void smartFactoryShow();

//特效函数9：绘制进入和退出的地球旋转特效
void calc(double i, double j, double rot, Vec* v);
void earthEffect();

