#pragma once
#include<stdio.h>
#include <stdio.h>
#include <windows.h>
#include<process.h>
#include <time.h>
#include <math.h>
#include"DynamicEffect .h"
#define LEN 50

/*地球动态效果显示部分*/
#define PI 3.1415926
#define SX 8
#define SY 16
#define DX PI / SX
#define DY PI * 2 / SY
#define X(a, b) (cx + v[a][b].x * r), (cy + v[a][b].y * r)

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
//特效函数7：字符旋转加载特效
void charRotation();
//特效函数8：边框显示功能
void frameShow();
//特效函数9：绘制进入和退出的地球旋转特效
void calc(double i, double j, double rot, Vec* v);
void earthEffect();


//隐藏光标
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };//后边的0代表光标不可见
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//光标移动
void Gotoxy(int x, int y)
{
	HANDLE hout; //定义句柄变量hout
	COORD coord; //定义结构体coord
	coord.X = x;
	coord.Y = y;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);//获得标准输出（屏幕）句柄
	SetConsoleCursorPosition(hout, coord);//移动光标
}

//画边框
void DrawBox(int x, int y)
{
	Gotoxy(x, y);
	printf("╔══════════════════════════════════════════════════╗");
	putchar('\n');
	Gotoxy(x, y + 1);
	printf("║                                                  ║");
	putchar('\n');
	Gotoxy(x, y + 2);
	printf("╚══════════════════════════════════════════════════╝");
}

//登陆成功进度条
void LoadInSuccess(int x, int y)
{
	int len;
	HideCursor();

	DrawBox(x, y);
	for (len = x; len <= LEN * 2 / 2 + x - 2; len++) {
		Gotoxy(len + 1, y + 1);
		printf("█");
		Gotoxy(x + 20, y + 4);
		printf("正在加载%d%%", 2 * len - 62);
		Sleep(500);
	}
	//printf("  ");
	//Gotoxy(x + 54, y + 1);
	//charRotation();
	Gotoxy(x + 10, y + 4);
	printf("加载成功，欢迎来到鲁班MES系统");
}

//登陆失败进度条
void LoadInFail(int x, int y)
{
	int len;
	HideCursor();
	DrawBox(x, y);
	for (len = x; len <= (LEN * 2 / 2 + x - 2) / 2; len++) {
		Gotoxy(len + 1, y + 1);
		printf("█");
		Gotoxy(x + 20, y + 4);
		printf("正在加载%d%%", 2 * len - 62);
		Sleep(500);
	}
	Sleep(5000);
	Gotoxy(x + 10, y + 4);
	printf("加载失败，请您重新输入个人密码   ");
	Sleep(5);
	//Gotoxy(x + 40, y + 4);
	charRotation();

}

//加载退出界面
void LoadExitMES(int x, int y)
{
	int len;
	HideCursor();

	DrawBox(x, y);
	for (len = x; len <= LEN * 2 / 2 + x - 2; len++) {
		Gotoxy(len + 1, y + 1);
		printf("█");
		Gotoxy(x + 14, y + 4);
		printf("正在退出鲁班MES系统  ");
		printf("%d%%", 2 * len - 62);
		Sleep(500);
	}
	//printf("  ");
	//Gotoxy(x + 54, y + 1);
	//charRotation();
	Gotoxy(x + 10, y + 4);
	printf("加载成功，欢迎来到鲁班MES系统");
}

//加载超级用户ROOT界面动画
void LoadRoot(int x, int y,int type) {
	int len;
	HideCursor();
	DrawBox(x, y);
	for (len = x; len <= LEN * 2 / 2 + x - 2; len++) {
		Gotoxy(len + 1, y + 1);
		printf("█");
		Gotoxy(x + 13, y + 4);
		//1.执 行 仓 储 管 理 员 权 限 
		if (type==1) printf("正在加载仓储Root管理模块%d%%", 2 * len - 62);
		//2.执 行 产 品 设 计 师 权 限
		else if (type == 2)printf("正在加载产品Root设计模块%d%%", 2 * len - 62);
		//3.执 行 工艺流程设计师 权 限
		else if (type == 3)printf("正在加载工艺Root流程模块%d%%", 2 * len - 62);
		//4.执 行 产线监督工程师 权 限
		else if (type == 4)printf("正在加载产线Root监督模块%d%%", 2 * len - 62);
		//5.执 行 产 品 销 售 员 权 限
		else printf("正在加载产品Root销售模块%d%%", 2 * len - 62);
		Sleep(500);
	}
	//printf("  ");
	//Gotoxy(x + 54, y + 1);
	//charRotation();
	Gotoxy(x + 8, y + 4);
	printf("加载成功，欢迎来到鲁班Root-MES系统");
}

//动态加载符号函数，函数内部参数time用于修改加载时间
void charRotation()
{

	char a[] = { '-','\\','|','/' };          //这里需要注意的是反斜杠字符，想要定义一个反斜杠字符，需要输入的是'\\'而不是'\'
	int i = 0;								  //定义整形i，做下标
	int time = 4;								  //时间管理大师
	while (time--)                            //当while语句的条件非零时，循环执行while语句
	{
		for (i = 0; i < 4; ++i)
		{
			printf("%c", a[i]);				  //输出字符数组a[]中的第i个字符（字符数组共有四个字符分a[0]~a[3]四个）
			Sleep(100);                       //输出字符a[i]之后停滞100ms（注意括号内的数字单位为毫秒）
			printf("\b");                     //输出"\b"为退格的意思（类似键盘上Backspace的作用）
		}

	}
}

//界面框架
void frameShow() {
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("┃                                                                                                                    ┃\n");
	printf("┃                                                                                                                    ┃\n");
	printf("┃                                                                                                                    ┃\n");
	printf("┃                                                                                                                    ┃\n");
	printf("┃                                                                                                                    ┃\n");
	printf("┃                                                                                                                    ┃\n");
	printf("┃                                                                                                                    ┃\n");
	printf("┃                                                                                                                    ┃\n");
	printf("┃                                                                                                                    ┃\n");
	printf("┃                                                                                                                    ┃\n");
	printf("┃                                                                                                                    ┃\n");
	printf("┃                                                                                                                    ┃\n");
	printf("┃                                                                                                                    ┃\n");
	printf("┃                                                                                                                    ┃\n");
	printf("┃                                                                                                                    ┃\n");
	printf("┃                                                                                                                    ┃\n");
	printf("┃                                                                                                                    ┃\n");
	printf("┃                                                                                                                    ┃\n");
	printf("┃                                                                                                                    ┃\n");
	printf("┃                                                                                                                    ┃\n");
	printf("┃                                                                                                                    ┃\n");
	printf("┃                                                                                                                    ┃\n");
	printf("┃                                                                                                                    ┃\n");
	printf("┃                                                                                                                    ┃\n");
	printf("┃                                                                                                                    ┃\n");
	printf("┃                                                                                                                    ┃\n");
	printf("┃                                                                                                                    ┃\n");
	printf("┃                                                                                                                    ┃\n");
	printf("┃                                                                                                                    ┃\n");
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
}

//专门用于各自刷新后的界面框架
void checkFrameShow() {
	frameShow();
	Gotoxy(35, 10);
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	Gotoxy(35, 11);
	printf("┃                                              ┃");
	Gotoxy(35, 12);
	printf("┃                                              ┃");
	Gotoxy(35, 13);
	printf("┃                                              ┃");
	Gotoxy(35, 14);
	printf("┃                                              ┃");
	Gotoxy(35, 15);
	printf("┃                                              ┃");
	Gotoxy(35, 16);
	printf("┃                                              ┃");
	Gotoxy(35, 17);
	printf("┃                                              ┃");
	Gotoxy(35, 18);
	printf("┃                                              ┃");
	Gotoxy(35, 19);
	printf("┃                                              ┃");
	Gotoxy(35, 20);
	printf("┃                                              ┃");
	Gotoxy(35, 21);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	Sleep(100);
}

void smartFactoryShow() {
	system("cls");
	frameShow();
	Gotoxy(57 + 11, 0);
	printf("┓");
	for (int i = 0; i < 29; i++) {
		Gotoxy(57+11, 1+i);
		printf("┃");
	}
	Gotoxy(57 + 11, 30);
	printf("┗");
	Gotoxy(23, 4);
	printf("鲁班 MES 云智慧工厂看板");
	for (int i = 0; i < 4; i++) {
		Gotoxy(9,7+i*3);
		printf("██████████████████████████");
		Gotoxy(9+23, 7 + i * 3+1);
		printf("产线 %d",i+1);
	}
	//绘制机床 1
	for (int i = 0; i < 5;i++) {
		Gotoxy(13,21+i);
		printf("█████");
	}
	Gotoxy(14+1, 26);
	printf("机床 1");
	//绘制机床 2
	for (int i = 0; i < 5; i++) {
		Gotoxy(13+5+13 , 21 + i);
		printf("█████");
	}
	Gotoxy(14+5+14, 26);
	printf("机床 2");
	//绘制机床 3
	for (int i = 0; i < 5; i++) {
		Gotoxy(13+5+13+5+13 , 21 + i);
		printf("█████");
	}
	Gotoxy(14+5+14+5+13, 26);
	printf("机床 3");
}

//绘制启动时的地球效果
void calc(double i, double j, double rot, Vec* v) {
	double x = sin(i) * cos(j), y = sin(i) * sin(j), z = cos(i),
		s = sin(rot), c = cos(rot), c1 = 1 - c, u = 1 / sqrt(3.0f), u2 = u * u;
	v->x = x * (c + u2 * c1) + y * (u2 * c1 - u * s) + z * (u2 * c1 + u * s);
	v->y = x * (u2 * c1 + u * s) + y * (c + u2 * c1) + z * (u2 * c1 - u * s);
}
void earthEffect() {
	HWND hwnd = GetConsoleWindow(); HDC hdc1 = GetDC(hwnd);
	double rot = 0;
	int time = 500;
	while (time--) {
		RECT rect; GetClientRect(hwnd, &rect); int w = rect.right, h = rect.bottom, cx = w / 2, cy = h / 2, r = h * 0.375;
		HDC hdc2 = CreateCompatibleDC(hdc1); HBITMAP bmp = CreateCompatibleBitmap(hdc1, w, h); SelectObject(hdc2, bmp);
		SelectObject(hdc2, GetStockObject(WHITE_PEN));
		Vec v[SX + 1][SY + 1];
		for (int i = 0; i <= SX; ++i) for (int j = 0; j <= SY; ++j) calc(i * DX, j * DY, rot, &v[i][j]);
		for (int i = 0; i < SX; ++i) for (int j = 0; j < SY; ++j) {
			MoveToEx(hdc2, X(i, j), NULL); LineTo(hdc2, X(i + 1, j));
			MoveToEx(hdc2, X(i, j), NULL); LineTo(hdc2, X(i, j + 1));
		}
		BitBlt(hdc1, 0, 0, w, h, hdc2, 0, 0, SRCCOPY); DeleteObject(bmp); DeleteDC(hdc2);
		rot += 0.01; Sleep(5);
	}
	Sleep(20);
}
