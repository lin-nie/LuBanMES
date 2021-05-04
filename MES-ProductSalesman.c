#include<stdio.h>
#include <stdio.h>
#include <windows.h>
#include<process.h>
#include <time.h>
#include"Globals.h"
#include"MES-ProductSalesman.h"

#define _CRT_SECURE_NO_DEPRECATE；
#define _CRT_SECURE_NO_WARNINGS；
#pragma warning(disable:4996)；

extern PSalesSeqList allPSaleslist;


/*----------------------采购订单信息管理数据结构接口----------------------*/
//数据结构操作1：PSale界面-初始化有序表 pssl，size表示初始化容量
void PSalesSeqListInit(PSalesSeqList* pssl, int size);

//数据结构操作2：PSale界面--数据库信息初始化
int allPSalesInfoReadFromFile(PSalesSeqList* pssl, char* filename);

/*----------------------界面接口集合----------------------*/
//界面1：采购订单信息管理界面
void proSalesInterface();

/*----------------------管理界面接口集合----------------------*/
//功能界面1：新增产品订单管理界面
void addProduct();

//功能界面2：删除采购订单管理界面
void deleteProduct();

//功能界面3：修改采购订单信息界面
void modifiPSale();

//功能界面4：查询采购订单信息界面
void queryPSale();

//功能界面5：交付采购订单管理界面
void deliveryPSale();

//功能界面6：保存采购订单信息界面
void savePSale();

//配合功能界面1：功能函数--增加采购订单登记信息
int addNewPSale(PSalesSeqList* pssl, PSaleInfo newPSale);

//配合功能界面123：功能函数--在采购订单登记表以及库存中根据采购订单编号进行查找，没有该编号所占用订单则返回-1；如果有返回值则是该登记编号已被占用（查找算法用二分查找法）
int searchPSale(PSalesSeqList pssl, char* PSsn);

//配合功能界面123：功能函数--深度拷贝新增订单登记信息
void PSaleCopy(PSaleInfo* to, PSaleInfo from);

//配合功能界面2：功能函数--在订单管理表中删除第index个元素，删除算法为把后面的数据元素覆盖前面，返回0表示删除成功
int delPSale(PSalesSeqList* pssl, int index);

//配合功能界面3：功能函数：在订单管理表pssl中修改第index个订单批次的信息，type表示要修改的类型（取值1（订单登记编号），2（订单需求产品名称），3（供应产品目的地），4（采购产品企业登记名称）），info表示新的信息值，修改成功返回0，否则返回1
int modifyPSale(PSalesSeqList* pssl, int index, int type, char* info);

//配合功能界面4：功能函数--根据订单的批次信息（tpye取值1（订单登记名称），2（供应产品发往目的地），3（采购产品企业名称））查询相关记录的采购订单信息。
//               如果没有找到，则返回 - 1；如果有，查询结果用一个IntSeqList列表返回，列表装的是订单在订单顺序表中的序号
int searchPSaleByOthers(PSalesSeqList pssl, char* info, int type, IntSeqList* psindex);

//配合功能界面5：功能函数--保存在系统中增加删除更改后的信息进入数据库中
int allPSalesInfoSaveToFile(PSalesSeqList pssl, char* filename);

//配合功能界面5：功能函数--按类型保存采购订单信息到文件中
int allSaveSale();



/*----------------------采购订单信息管理数据结构接口----------------------*/
//数据结构操作1：PSale界面-初始化有序表 pssl，size表示初始化容量
void PSalesSeqListInit(PSalesSeqList* pssl, int size) {
	pssl->list = (PSaleInfo*)malloc(size * sizeof(PSaleInfo));
	pssl->size = size;
	pssl->length = 0;
}

//数据结构操作2：PSale界面--数据库信息初始化
int allPSalesInfoReadFromFile(PSalesSeqList* pssl, char* filename) {
	FILE *fp;
	char strline[80];             //每行最大读取的字符数
	if ((fp = fopen(filename, "r")) == NULL) { //判断文件是否存在及可读
		errorTemplate(48, "加载 MES数据库信息出错！");
		return -1;
	}
	PSaleInfo newPSale;
	while (!feof(fp)) {
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newPSale.PSale_id, strline);
		else {
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newPSale.PSale_name, strline);
		else {
			errorTemplate(48, "加载 MES数据库信息出错！");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newPSale.PSale_destination, strline);
		else {
			errorTemplate(48, "加载 MES数据库信息出错！");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newPSale.PSale_company, strline);
		else {
			errorTemplate(48, "加载 MES数据库信息出错！");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0) {
			newPSale.PSale_num = atof(strline);
		}
		else {
			errorTemplate(48, "加载 MES数据库信息出错！");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0) {
			strcpy(newPSale.in_time, strline);
		}
		else {
			errorTemplate(48, "加载 MES数据库信息出错！");
			fclose(fp);
			return -1;
		}
		addNewPSale(pssl, newPSale);
	}
	fclose(fp);//关闭文件
	return 0;
}


/*----------------------界面接口集合----------------------*/
//界面1：采购订单信息管理界面
void proSalesInterface() {	
	int choice;
	system("cls");
	frameShow();
	Gotoxy(44 + 5, 7);
	printf("采购订单信息管理面板");
	Gotoxy(44 + 3, 10);		//动态移动光标，同时本页面以坐标（48，10）作为基准移动下面的光标
	printf("1.添 加 采 购 订 单 信 息");
	Gotoxy(44 + 3, 12);
	printf("2.删 除 采 购 订 单 信 息");
	Gotoxy(44 + 3, 14);
	printf("3.采 购 订 单 信 息 修 改");
	Gotoxy(44 + 3, 16);
	printf("4.采 购 订 单 信 息 查 询");
	Gotoxy(44 + 3, 18);
	printf("5.核 对 采 购 订 单 交 付 ");
	Gotoxy(44 + 3, 20);
	printf("6.保 存 采 购 订 单 信 息 ");
	Gotoxy(44 + 3, 22);
	printf("7.退 出 采 购 订 单 管 理");
	Gotoxy(44 + 3, 26);
	printf("请输入您需要操作的编码：");
	Gotoxy(44 + 23 + 3, 26);
	scanf("%d", &choice);
	switch (choice) {
		case 1: {
			addProduct();
		}
	
		case 2: {
			deleteProduct();
		}
		case 3: {
			modifiPSale();
		}
		case 4: {
			queryPSale();
		}
		case 5: {
			deliveryPSale();
		}
		case 6: {
			savePSale();
		}
		case 7: {
			errorTemplate(47.5, "正在退出仓储库存管理面板！");
			exitMES(6);
		}
		default: {
			errorTemplate(47.5, "输入编号有误，请重新输入！");
			proSalesInterface();
		}
	}
}

/*----------------------管理界面接口集合----------------------*/
//功能界面1：新增产品订单管理界面
void addProduct() {
	system("cls");
	frameShow();
	char temp[80];//作为价格的交换值
	PSaleInfo newPSale;
	Gotoxy(44 + 5, 9);
	printf("添加采购订单信息面板");
	Gotoxy(44, 12);
	printf("1.采购订单管理编号：");
	Gotoxy(44 + 20 + 4, 12);
	scanf("%s", newPSale.PSale_id);
	Gotoxy(44, 14);
	printf("2.采购订单产品名称：");
	Gotoxy(44 + 20 + 4, 14);
	scanf("%s", newPSale.PSale_name);
	Gotoxy(44, 16);
	printf("3.订单发往的目的地：");
	Gotoxy(44 + 20 + 4, 16);
	scanf("%s", newPSale.PSale_destination);
	Gotoxy(44, 18);
	printf("4.采购订单企业登记：");
	Gotoxy(44 + 20 + 4, 18);
	scanf("%s", newPSale.PSale_company);
	Gotoxy(44, 20);
	printf("5.本批采购产品数量：");
	Gotoxy(44 + 20 + 4, 20);
	scanf("%s", temp);
	newPSale.PSale_num = atof(temp);
	getTimeNow(newPSale.in_time);
	Gotoxy(44 - 3, 24);
	printf("确认将这批次订单登进系统? y/n ：  ");
	int r1;
	scanf("%s", temp);
	Gotoxy(44 - 3, 26);
	if (temp[0] == 'y') {
		r1 = addNewPSale(&allPSaleslist, newPSale);
		if (r1 == -1) {
			printf("登记订单失败，请检查该登记信息！  ");
			charRotation();
			proSalesInterface();
		}
		else {
			printf("采购登记成功，成功添加订单信息！  ");
			charRotation();
			proSalesInterface();
		}
	}
	//输入no的情况下
	else if (temp[0] == 'n') {
		printf("正在返回采购面板，请确认后输入！ ");
		charRotation();
		Sleep(5000);
		proSalesInterface();
	}
	//误输入除去y和n的其它字符的话
	else {
		printf("您的输入有误，请确认要求后输入！ ");
		charRotation();
		Sleep(5000);
		addProduct();
	}
}

//功能界面2：删除采购订单管理界面
void deleteProduct() {
	system("cls");
	frameShow();
	char temp[30];
	Gotoxy(44 + 3, 8);
	printf("删除采购订单管理面板");
	Gotoxy(43, 11);
	printf("请您输入需要删除的订单编号：");
	scanf("%s", temp);
	Gotoxy(43 + 32, 11);
	charRotation();
	int r1 = searchPSale(allPSaleslist, temp);
	//在这里出现查找失败的情况
	if (r1 < 0) {
		Gotoxy(44, 13);
		printf("查询订单失败，确认后输入  ");
		charRotation();
		deleteProduct();
	}
	else {
		Gotoxy(43, 13);
		printf("请您确认需要删除的订单信息：");
		Gotoxy(44, 15);
		printf("1.采购订单管理编号： %s", allPSaleslist.list[r1].PSale_id);
		Gotoxy(44, 17);
		printf("2.采购订单产品名称： %s", allPSaleslist.list[r1].PSale_name);
		Gotoxy(44, 19);
		printf("3.订单发往的目的地： %s", allPSaleslist.list[r1].PSale_destination);
		Gotoxy(44, 21);
		printf("4.采购订单企业登记： %s", allPSaleslist.list[r1].PSale_company);
		Gotoxy(44, 23);
		printf("5.本批采购产品数量： %.2f", allPSaleslist.list[r1].PSale_num);
		Gotoxy(44, 25);
		printf("6.采购订单登记时间： %s", allPSaleslist.list[r1].in_time);
		Gotoxy(44 - 2, 28);
		printf("确认要删除该批次订单吗？ y/n:  ");
		scanf("%s", temp);
		Gotoxy(44 - 2 + 33, 28);
		charRotation();
		Gotoxy(44 - 2, 29);
		if (temp[0] == 'y') {
			int r3 = delPSale(&allPSaleslist, r1);
			if (r3 == -1) {
				printf("删除失败，无法检验该订单信息！");
				Sleep(5000);
			}
			else {
				printf("删除成功，系统中已无该订单信息！");
				Sleep(1000);
				proSalesInterface();
			}
		}
		//输入no的情况下
		else if (temp[0] == 'n') {
			printf("正在返回采购面板，请确认后输入！ ");
			charRotation();
			Sleep(3000);
			proSalesInterface();
		}
		//误输入除去y和n的其它字符的话
		else {
			printf("您的输入有误，请确认要求后输入！ ");
			charRotation();
			Sleep(3000);
			deleteProduct();
		}
	}
}

//功能界面3：修改采购订单信息界面
void modifiPSale() {
	system("cls");
	frameShow();
	Gotoxy(44 + 3, 5);
	printf("采购订单信息修改面板");
	char temp[30];
	Gotoxy(43, 8);
	printf("请您输入需要修改的订单编号：");
	scanf("%s", temp);
	Gotoxy(43 + 32, 8);
	charRotation();
	int r1 = searchPSale(allPSaleslist, temp);
	int r2 = 0, r3 = 0;
	//在这里出现查找失败的情况
	if (r1 < 0) {
		Gotoxy(44, 10);
		printf("查询订单失败，确认后输入  ");
		charRotation();
		proSalesInterface();
	}
	else {
		Gotoxy(43, 10);
		printf("请您确认需要修改的订单信息：");
		Gotoxy(44, 12);
		printf("1.采购订单管理编号： %s", allPSaleslist.list[r1].PSale_id);
		Gotoxy(44, 14);
		printf("2.采购订单产品名称： %s", allPSaleslist.list[r1].PSale_name);
		Gotoxy(44, 16);
		printf("3.订单发往的目的地： %s", allPSaleslist.list[r1].PSale_destination);
		Gotoxy(44, 18);
		printf("4.采购订单企业登记： %s", allPSaleslist.list[r1].PSale_company);
		Gotoxy(44, 20);
		printf("5.本批采购产品数量： %.2f", allPSaleslist.list[r1].PSale_num);
		Gotoxy(44, 22);
		printf("6.采购订单登记时间： %s", allPSaleslist.list[r1].in_time);
		while (1) {
			Gotoxy(44 - 2, 24);
			printf("选择要修改的内容编号： ");
			char temp[30];
			scanf("%s", temp);
			r2 = atoi(temp);
			//输入的编号在范围之内的（1~6）
			if (r2 >= 1 && r2 <= 6) {
				char newContent[50];
				Gotoxy(44 - 2, 26);
				printf("需修改部分的新内容为： ");
				scanf("%s", newContent);
				r3 = modifyPSale(&allPSaleslist, r1, r2, newContent);
				if (r3 == -1) {
					Gotoxy(44 - 2, 28);
					printf("修改订单信息失败！  ");
					charRotation();
					Sleep(5000);
					proSalesInterface();
				}
				else {
					Gotoxy(44 - 2, 28);
					printf("选择修改订单信息成功！ ");
					charRotation();
					Sleep(3000);
					proSalesInterface();
				}
				break;
			}
			//输入的编号不在范围内的
			else {
				Gotoxy(44 - 2, 26);
				printf("您输入的选项编号错误！ ");
				charRotation();
				Sleep(5000);
				proSalesInterface();
			}
		}
	}

}

//功能界面4：查询采购订单信息界面
void queryPSale() {
	system("cls");
	frameShow();
	Gotoxy(22 + 2, 8);
	printf("采购订单信息查询面板");
	Gotoxy(22, 10);
	printf("请您确认查询订单信息的方式：");
	int choice, r2;
	while (1) {
		Gotoxy(22, 12);
		printf("1.采购订单管理编号");
		Gotoxy(22, 14);
		printf("2.采购订单产品名称");
		Gotoxy(22, 16);
		printf("3.订单发往的目的地");
		Gotoxy(22, 18);
		printf("4.采购订单登记企业");
		Gotoxy(22, 20);
		printf("5.显示所有订单信息");
		Gotoxy(22, 22);
		printf("6.返回采购管理面板");
		Gotoxy(22, 25);
		printf("请输入查询方式的编号： ");
		char temp[80];
		scanf("%s", temp);
		Gotoxy(22 + 23 + 2, 25);//待定
		charRotation();
		choice = atoi(temp);
		switch (choice) {
			//输入的查询方式为1时，此时查询方式为订单编号
		case 1: {
			char content[50];
			Gotoxy(22, 27);
			printf("请输入需要查询的内容： ");
			scanf("%s", content);
			Gotoxy(22 + 20 + 5, 27);
			charRotation();
			r2 = searchPSale(allPSaleslist, content);
			if (r2 < 0) {
				Gotoxy(22 + 20 + 10, 27);
				printf("查询内容失败，确认后输入  ");
				charRotation();
				queryPSale();
			}
			else {
				Gotoxy(58 + 22 - 16, 10);
				printf("1.采购订单管理编号： %s", allPSaleslist.list[r2].PSale_id);
				Gotoxy(58 + 22 - 16, 12);
				printf("2.采购订单产品名称： %s", allPSaleslist.list[r2].PSale_name);
				Gotoxy(58 + 22 - 16, 14);
				printf("3.订单发往的目的地： %s", allPSaleslist.list[r2].PSale_destination);
				Gotoxy(58 + 22 - 16, 16);
				printf("4.采购订单登记企业： %s", allPSaleslist.list[r2].PSale_company);
				Gotoxy(58 + 22 - 16, 18);
				printf("5.本批采购产品数量： %.2f", allPSaleslist.list[r2].PSale_num);
				Gotoxy(58 + 22 - 16, 20);
				printf("6.采购订单登记时间： %s", allPSaleslist.list[r2].in_time);
				Gotoxy(58 + 22 - 16, 24);
				printf("查看结果后，请输入y返回上一层： ");
				scanf("%s", temp);
				if (temp[0] == 'y') {
					Gotoxy(58 + 22 + 16 * 2 + 2 - 16 + 1, 24);
					charRotation();
					Sleep(1000);
					queryPSale();
				}
				else {
					Gotoxy(58 + 22 + 16 * 2 + 2 - 16 + 1, 24);
					printf("输入有误，为您返回主面板 ");
					charRotation();
					Sleep(1000);
					proSalesInterface();
				}
			}
			break;
		}
		//输入的查询方式为2时，此时查询方式为订单需求产品名称
		case 2: {
			char content[50];
			Gotoxy(22, 27);
			printf("请输入需要查询的内容： ");
			scanf("%s", content);
			Gotoxy(22 + 23 + 8, 27);
			charRotation();
			IntSeqList result;
			intListInit(&result, 5);
			searchPSaleByOthers(allPSaleslist, content, choice, &result);
			if (result.length == 0) {
				errorTemplate(48, "没有满足条件的订单信息！");
				queryPSale();
			}
			//假如成功找到有对应的值
			else {
				system("cls");
				frameShow();
				//测试一下
				Gotoxy(6, 4);
				printf("订单编号     采购产品      发往目的地              采购产品企业         采购产品数量       登记订单时间");
				for (int i = 0; i < result.length; i++) {
					Gotoxy(8, 8 + i);
					printf(" %s        %s           %s       %s    %.2f          %s", allPSaleslist.list[result.list[i]].PSale_id, allPSaleslist.list[result.list[i]].PSale_name, allPSaleslist.list[result.list[i]].PSale_destination, allPSaleslist.list[result.list[i]].PSale_company, allPSaleslist.list[result.list[i]].PSale_num, allPSaleslist.list[result.list[i]].in_time);
				}
				//用于退出的接口
				char yes[3];
				Gotoxy(43, 28);
				printf("查看结果后，请输入y返回上一层： ");
				scanf("%s", yes);
				if (yes[0] == 'y') {
					Gotoxy(43 + 16 * 2 + 2, 28);
					charRotation();
					Sleep(1000);
					queryPSale();
				}
				//输入错误情况下
				else {
					Gotoxy(58 + 22, 28);
					printf("输入有误，为您返回主面板 ");
					charRotation();
					Sleep(1000);
					proSalesInterface();
				}
			}
			errorTemplate(48, "没有满足条件的订单信息！");
			proSalesInterface();
			break;
		}
		//输入的查询方式为3时，此时查询方式为产品发往目的地
		case 3: {
			char content[50];
			Gotoxy(22, 27);
			printf("请输入需要查询的内容： ");
			scanf("%s", content);
			Gotoxy(22 + 23 + 28 - 15, 27);
			charRotation();
			IntSeqList result;
			intListInit(&result, 5);
			searchPSaleByOthers(allPSaleslist, content, choice, &result);
			if (result.length == 0) {
				errorTemplate(48, "没有满足条件的订单信息！");
				queryPSale();
			}
			//假如成功找到有对应的值
			else {
				system("cls");
				frameShow();
				//测试一下
				Gotoxy(6, 4);
				printf("订单编号     采购产品      发往目的地              采购产品企业         采购产品数量       登记订单时间");
				for (int i = 0; i < result.length; i++) {
					Gotoxy(8, 8 + i);
					printf(" %s        %s           %s       %s    %.2f          %s", allPSaleslist.list[result.list[i]].PSale_id, allPSaleslist.list[result.list[i]].PSale_name, allPSaleslist.list[result.list[i]].PSale_destination, allPSaleslist.list[result.list[i]].PSale_company, allPSaleslist.list[result.list[i]].PSale_num, allPSaleslist.list[result.list[i]].in_time);
				}
				//用于退出的接口
				char yes[3];
				Gotoxy(43, 28);
				printf("查看结果后，请输入y返回上一层： ");
				scanf("%s", yes);
				if (yes[0] == 'y') {
					Gotoxy(43 + 16 * 2 + 2, 28);
					charRotation();
					Sleep(1000);
					queryPSale();
				}
				//输入错误情况下
				else {
					Gotoxy(58 + 22, 28);
					printf("输入有误，为您返回主面板 ");
					charRotation();
					Sleep(1000);
					proSalesInterface();
				}
			}
			errorTemplate(48, "没有满足条件的订单信息！");
			proSalesInterface();
			break;
		}
		//输入的查询方式为4时，此时查询方式为采购订单的企业名称
		case 4: {
			char content[50];
			Gotoxy(22, 27);
			printf("请输入需要查询的内容： ");
			scanf("%s", content);
			Gotoxy(22 + 23 + 29, 27);
			charRotation();
			IntSeqList result;
			intListInit(&result, 5);
			searchPSaleByOthers(allPSaleslist, content, choice, &result);
			if (result.length == 0) {
				errorTemplate(48, "没有满足条件的订单信息！");
				queryPSale();
			}
			//假如成功找到有对应的值
			else {
				system("cls");
				frameShow();
				//测试一下
				Gotoxy(6, 4);
				printf("订单编号     采购产品      发往目的地              采购产品企业         采购产品数量       登记订单时间");
				for (int i = 0; i < result.length; i++) {
					Gotoxy(8, 8 + i);
					printf(" %s        %s           %s       %s    %.2f          %s", allPSaleslist.list[result.list[i]].PSale_id, allPSaleslist.list[result.list[i]].PSale_name, allPSaleslist.list[result.list[i]].PSale_destination, allPSaleslist.list[result.list[i]].PSale_company, allPSaleslist.list[result.list[i]].PSale_num, allPSaleslist.list[result.list[i]].in_time);
				}
				//用于退出的接口
				char yes[3];
				Gotoxy(43, 28);
				printf("查看结果后，请输入y返回上一层： ");
				scanf("%s", yes);
				if (yes[0] == 'y') {
					Gotoxy(43 + 16 * 2 + 2, 28);
					charRotation();
					Sleep(1000);
					queryPSale();
				}
				//输入错误情况下
				else {
					Gotoxy(58 + 22, 28);
					printf("输入有误，为您返回主面板 ");
					charRotation();
					Sleep(1000);
					proSalesInterface();
				}
			}
			errorTemplate(48, "没有满足条件的订单信息！");
			proSalesInterface();
			break;
		}
		//输入的查询方式为4时，此时查询方式为显示所有订单
		case 5: {
			if (allPSaleslist.length == 0) {
				errorTemplate(48, "采购订单信息数据库为空！");
				queryPSale();
			}
			system("cls");
			frameShow();
			//测试一下
			Gotoxy(6, 4);
			printf("订单编号     采购产品      发往目的地              采购产品企业         采购产品数量       登记订单时间");
			for (int i = 0; i < allPSaleslist.length; i++) {
				Gotoxy(8, 8 + i);
				printf(" %s        %s           %s       %s    %.2f          %s", allPSaleslist.list[i].PSale_id, allPSaleslist.list[i].PSale_name, allPSaleslist.list[i].PSale_destination, allPSaleslist.list[i].PSale_company, allPSaleslist.list[i].PSale_num, allPSaleslist.list[i].in_time);
			}
			//用于退出的接口
			char yes[3];
			Gotoxy(43, 28);
			printf("查看结果后，请输入y返回上一层： ");
			scanf("%s", yes);
			if (yes[0] == 'y') {
				Gotoxy(43 + 16 * 2 + 2, 28);
				charRotation();
				Sleep(1000);
				queryPSale();
			}
			//输入错误情况下
			else {
				Gotoxy(58 + 22, 28);
				printf("输入有误，为您返回主面板 ");
				charRotation();
				Sleep(1000);
				proSalesInterface();
			}
		}
		//输入的查询方式为6时，此时退出查询订单面板
		case 6: {
			errorTemplate(49, "正在返回采购管理面板！");
			proSalesInterface();
		}
		default: {
			errorTemplate(48, "输入的查询方式编号有误！");
			queryPSale();
		}
		}
	}
}

//功能界面5：交付采购订单管理界面
void deliveryPSale() {
	system("cls");
	frameShow();
	char temp[30];
	Gotoxy(44 + 3, 8);
	printf("核对交付采购订单面板");
	Gotoxy(43, 11);
	printf("请您输入需要交付的订单编号：");
	scanf("%s", temp);
	Gotoxy(43 + 32, 11);
	charRotation();
	int r1 = searchPSale(allPSaleslist, temp);
	//在这里出现查找失败的情况
	if (r1 < 0) {
		Gotoxy(44, 13);
		printf("查询订单失败，确认后输入  ");
		charRotation();
		deliveryPSale();
	}
	else {
		Gotoxy(43, 13);
		printf("请您核对需要交付的订单信息：");
		Gotoxy(44, 15);
		printf("1.采购订单管理编号： %s", allPSaleslist.list[r1].PSale_id);
		Gotoxy(44, 17);
		printf("2.采购订单产品名称： %s", allPSaleslist.list[r1].PSale_name);
		Gotoxy(44, 19);
		printf("3.订单发往的目的地： %s", allPSaleslist.list[r1].PSale_destination);
		Gotoxy(44, 21);
		printf("4.采购订单企业登记： %s", allPSaleslist.list[r1].PSale_company);
		Gotoxy(44, 23);
		printf("5.本批采购产品数量： %.2f", allPSaleslist.list[r1].PSale_num);
		Gotoxy(44, 25);
		printf("6.采购订单登记时间： %s", allPSaleslist.list[r1].in_time);
		Gotoxy(44 - 2, 28);
		printf("确认要交付该批次订单吗？ y/n:  ");
		scanf("%s", temp);
		Gotoxy(44 - 2 + 33, 28);
		charRotation();
		Gotoxy(44 - 2, 29);
		if (temp[0] == 'y') {
			int r3 = delPSale(&allPSaleslist, r1);
			if (r3 == -1) {
				errorTemplate(48, "核对当前的订单信息失败！");
				deliveryPSale();
				Sleep(5000);
			}
			else {
				errorTemplate(48, "核对成功，正在完成订单交付");
				Sleep(1000);
				errorTemplate(48, "交付成功，系统已无订单信息");
				proSalesInterface();
			}
		}
		//输入no的情况下
		else if (temp[0] == 'n') {
			printf("正在返回采购面板，请确认后输入！ ");
			charRotation();
			Sleep(3000);
			proSalesInterface();
		}
		//误输入除去y和n的其它字符的话
		else {
			printf("您的输入有误，请确认要求后输入！ ");
			charRotation();
			Sleep(3000);
			deliveryPSale();
		}
	}
}

//功能界面6：保存采购订单信息界面
void savePSale() {
	int r1 = allSaveSale();
	if (r1 == -1) {
		errorTemplate(48, "保存当前的订单信息失败！");
		proSalesInterface();
	}
	else {
		errorTemplate(48, "正在保存所有的订单信息！");
		errorTemplate(48, "保存所有的订单信息成功！");
		proSalesInterface();
	}
}

//配合功能界面1：功能函数--增加采购订单登记信息
int addNewPSale(PSalesSeqList* pssl, PSaleInfo newPSale) {

	//首先在采购订单信息表中查找是否有此采购订单信息，如果有，返回 - 1，表示订单登记失败
	int r = searchPSale(*pssl, newPSale.PSale_id);
	if (r >= 0) {
		errorTemplate(48, "采购订单登记编号已存在！");
		proSalesInterface();
	}
	//如果有序表空间不够，则扩充空间
	if (pssl->length >= pssl->size) {
		PSaleInfo* t = pssl->list;
		pssl->list = (PSaleInfo*)malloc(2 * pssl->size * sizeof(PSaleInfo));
		if (pssl->list == NULL) {
			errorTemplate(48, "保存无效，内存分配失败！");
			proSalesInterface();
		}
		pssl->size = 2 * pssl->size;
		for (int i = 0; i < pssl->length; i++)
			PSaleCopy(&(pssl->list[i]), t[i]);
		free(t);
	}
	//	较采购订单登记编号插入到合适的位置，保证据采购订单编号有序
	int i = 0;
	for (i = pssl->length - 1; i >= 0; i--) {
		r = strcmp(pssl->list[i].PSale_id, newPSale.PSale_id);
		if (r > 0)
			PSaleCopy(&(pssl->list[i + 1]), pssl->list[i]);
		else
			break;

	}
	PSaleCopy(&(pssl->list[i + 1]), newPSale);
	pssl->length++;
	//添加成功返回0
	return 0;
}

//配合功能界面123：功能函数--在采购订单登记表以及库存中根据采购订单编号进行查找，没有该编号所占用订单则返回-1；如果有返回值则是该登记编号已被占用（查找算法用二分查找法）
int searchPSale(PSalesSeqList pssl, char* PSsn) {		//传递了两个参数，一个是pssl，一个是PSsn
	int low = 0;
	int high = pssl.length - 1;
	int mid;
	while (low <= high) {
		mid = (low + high) / 2;		//二分查找法
		if (strcmp(pssl.list[mid].PSale_id, PSsn) == 0)
			return mid;
		else
			if (strcmp(pssl.list[mid].PSale_id, PSsn) < 0)
				low = mid + 1;
			else
				high = mid - 1;
	}
	return -1;
}

//配合功能界面123：功能函数--深度拷贝新增订单登记信息
void PSaleCopy(PSaleInfo* to, PSaleInfo from) {
	strcpy(to->PSale_id, from.PSale_id);
	strcpy(to->PSale_name, from.PSale_name);
	strcpy(to->PSale_destination, from.PSale_destination);
	strcpy(to->PSale_company, from.PSale_company);
	to->PSale_num = from.PSale_num;
	strcpy(to->in_time, from.in_time);
}

//配合功能界面2：功能函数--在订单管理表中删除第index个元素，删除算法为把后面的数据元素覆盖前面，返回0表示删除成功
int delPSale(PSalesSeqList* pssl, int index) {
	if (pssl->length <= 0) {
		errorTemplate(48, "采购订单数据库信息为空！");
		proSalesInterface();
		return -1;
	}
	if (index < 0 || index >= pssl->length) {
		errorTemplate(47, "需要删除的订单超出执行范围！");
		proSalesInterface();
		return -1;
	}

	for (int i = index + 1; i < pssl->length; i++) {
		PSaleCopy(&(pssl->list[i - 1]), pssl->list[i]);
	}
	pssl->length--;
	return 0;
}

//配合功能界面3：功能函数：在订单管理表pssl中修改第index个订单批次的信息，type表示要修改的类型（取值1（订单登记编号），2（订单需求产品名称），3（供应产品目的地），4（采购产品企业登记名称）），info表示新的信息值，修改成功返回0，否则返回1
int modifyPSale(PSalesSeqList* pssl, int index, int type, char* info) {
	if (index < 0 && index >= pssl->length) {
		errorTemplate(47, "需要修改的订单超出执行范围！");
		proSalesInterface();
	}
	switch (type) {
		case 1: strcpy(pssl->list[index].PSale_id, info); break;
		case 2: strcpy(pssl->list[index].PSale_name, info); break;
		case 3: strcpy(pssl->list[index].PSale_destination, info); break;
		case 4: strcpy(pssl->list[index].PSale_company, info); break;
		case 5: pssl->list[index].PSale_num = atof(info); break;
		case 6: strcpy(pssl->list[index].in_time, info); break;
		default: {
			errorTemplate(48, "修改的订单信息编号有误！");
			proSalesInterface();
		}
	}
	return 0;
}

//配合功能界面4：功能函数--根据订单的批次信息（tpye取值1（订单登记名称），2（供应产品发往目的地），3（采购产品企业名称））查询相关记录的采购订单信息。
//               如果没有找到，则返回 - 1；如果有，查询结果用一个IntSeqList列表返回，列表装的是订单在订单顺序表中的序号
int searchPSaleByOthers(PSalesSeqList pssl, char* info, int type, IntSeqList* psindex) {
	for (int i = 0; i < pssl.length; i++) {
		switch (type - 1) {
			//当输入的选项为2时，type值对应为1，则执行按照订单需求产品名称查询的手法；
		case 1: if (strcmp(pssl.list[i].PSale_name, info) == 0)
			addInt(psindex, i);
			break;
			//当输入的选项为3时，type值对应为2，则执行按照订单发往目的地的查询的手法：
		case 2: if (strcmp(pssl.list[i].PSale_destination, info) == 0)
			addInt(psindex, i);
			break;
			//当输入的选项为4时，type值对应为3，则执行按照采购订单企业名称的查询手法；
		case 3: if (strcmp(pssl.list[i].PSale_company, info) == 0)
			addInt(psindex, i);
			break;
		default: {
			errorTemplate(47.5, "查询订单信息方式编号有误！");
			proSalesInterface();
		}
		}
	}
	return 0;
}

//配合功能界面5：功能函数--保存在系统中增加删除更改后的信息进入数据库中
int allPSalesInfoSaveToFile(PSalesSeqList pssl, char* filename) {
	FILE *fp;
	char strline[80];
	if ((fp = fopen(filename, "w")) == NULL) {
		errorTemplate(48, "采购订单的数据库不存在！");
		proSalesInterface();
	}

	for (int i = 0; i < pssl.length; i++) {
		fputs(pssl.list[i].PSale_id, fp);
		fputc('\n', fp);
		fputs(pssl.list[i].PSale_name, fp);
		fputc('\n', fp);
		fputs(pssl.list[i].PSale_destination, fp);
		fputc('\n', fp);
		fputs(pssl.list[i].PSale_company, fp);
		fputc('\n', fp);
		sprintf(strline, "%.2f", pssl.list[i].PSale_num);
		fputs(strline, fp);
		fputc('\n', fp);
		fputs(pssl.list[i].in_time, fp);
		fputc('\n', fp);
	}
	fclose(fp);
	return 0;
}

//配合功能界面5：功能函数--按类型保存采购订单信息到文件中
int allSaveSale() {
	int r1 = allPSalesInfoSaveToFile(allPSaleslist, "采购订单信息数据库.txt");  //保存所有的采购订单信息到文件中
	if (r1 == -1) {
		errorTemplate(48, "保存当前的订单信息失败！");
		proSalesInterface();
	}
	return 0;
}