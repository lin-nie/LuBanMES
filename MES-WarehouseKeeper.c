#include<stdio.h>
#include <stdio.h>
#include <windows.h>
#include<process.h>
#include <time.h>
#include"MES-WarehouseKeeper.h"
#include"Globals.h"
#include"MES-Leader.h"

#define _CRT_SECURE_NO_DEPRECATE；
#define _CRT_SECURE_NO_WARNINGS；
#pragma warning(disable:4996)；

extern MWaresSeqList allMWareslist;

/*----------------------仓储原料信息管理数据结构接口----------------------*/
//数据结构操作1：MWare界面-初始化有序表 mwsl，size表示初始化容量
void MWaresSeqListInit(MWaresSeqList* mwsl, int size);
//数据结构操作2：MWare界面--数据库信息初始化
int allMWaresInfoReadFromFile(MWaresSeqList* mwsl, char* filename);

/*----------------------界面接口集合----------------------*/
//界面1：仓储库存信息管理界面
void wareInterface();

/*----------------------管理界面接口集合----------------------*/
//功能界面1：新增原料入库管理界面
void addMaterial();
//功能界面2：仓储原料出库管理界面
void deleteMaterial();
//功能界面3：修改仓储库存原料界面
void modifiMWare();
//功能界面4：查询仓储库存原料信息界面
void queryMWare();
//功能界面5：保存仓储管理信息界面
void saveMWare();

/*----------------------功能函数接口集合----------------------*/
//配合功能界面1：功能函数--增加原材料入库登记信息
int addNewMWare(MWaresSeqList* mwsl, MWareInfo newMWare);
//配合功能界面123：功能函数--在原料入库登记表以及库存中根据登记原料编号进行查找，没有该编号所占用库存则返回-1；如果有返回值则是该登记编号已被占用（查找算法用二分查找法）
int searchMWare(MWaresSeqList mwsl, char* MWsn);
//配合功能界面123：功能函数--深度拷贝新增入库原料登记信息
void MWareCopy(MWareInfo* to, MWareInfo from);
//配合功能界面2：功能函数--在原料仓储管理表中删除第index个元素，删除算法为把后面的数据元素覆盖前面，返回0表示删除成功
int delMWare(MWaresSeqList* mwsl, int index);
//配合功能界面3：功能函数：在仓储管理表mwsl中修改第index个原料批次的信息，type表示要修改的类型（取值1（原料登记编号），2（原料登记名称），3（供应原料所在地），4（供应原料企业名称）），info表示新的信息值，修改成功返回0，否则返回1
int modifyMWare(MWaresSeqList* mwsl, int index, int type, char* info);
//配合功能界面4：功能函数--根据仓储原料的批次信息（tpye取值1（原料登记名称），2（供应原料所在地），3（供应原料企业名称））查询相关记录的仓储库存信息。
//               如果没有找到，则返回 - 1；如果有，查询结果用一个IntSeqList列表返回，列表装的是原料在仓储顺序表中的序号
int searchMWareByOthers(MWaresSeqList mwsl, char* info, int type, IntSeqList* mwindex);
//配合功能界面5：功能函数--保存在系统中增加删除更改后的信息进入数据库中
int allMWaresInfoSaveToFile(MWaresSeqList mwsl, char* filename);
//配合功能界面5：功能函数--按类型保存仓储信息到文件中
int allSaveWare();

//特殊接口函数：管理员专用于查询仓储库存原料信息界面
void queryMWareAdmin();


/*----------------------仓储原料信息管理数据结构接口----------------------*/
//数据结构操作1：MWare界面-初始化有序表 mwsl，size表示初始化容量
void MWaresSeqListInit(MWaresSeqList* mwsl, int size) {
	mwsl->list = (MWareInfo*)malloc(size * sizeof(MWareInfo));
	mwsl->size = size;
	mwsl->length = 0;
}

//数据结构操作2：MWare界面--数据库信息初始化
int allMWaresInfoReadFromFile(MWaresSeqList* mwsl, char* filename) {
	FILE *fp;
	char strline[80];             //每行最大读取的字符数
	if ((fp = fopen(filename, "r")) == NULL) { //判断文件是否存在及可读
		errorTemplate(48, "加载 MES数据库信息出错！");
		return -1;
	}
	MWareInfo newMWare;
	while (!feof(fp)) {
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newMWare.MWare_id, strline);
		else {
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newMWare.MWare_name, strline);
		else {
			errorTemplate(48, "加载 MES数据库信息出错！");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newMWare.MWare_location, strline);
		else {
			errorTemplate(48, "加载 MES数据库信息出错！");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newMWare.MWare_company, strline);
		else {
			errorTemplate(48, "加载 MES数据库信息出错！");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0) {
			newMWare.MWare_num = atof(strline);
		}
		else {
			errorTemplate(48, "加载 MES数据库信息出错！");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0) {
			strcpy(newMWare.in_time, strline);
		}
		else {
			errorTemplate(48, "加载 MES数据库信息出错！");
			fclose(fp);
			return -1;
		}
		addNewMWare(mwsl, newMWare);
	}
	fclose(fp);//关闭文件
	return 0;
}

/*----------------------界面接口集合----------------------*/
//界面1：仓储库存信息管理界面
void wareInterface() {	//存储材料的企业信息管理界面
	int choice;
	system("cls");
	frameShow();
	Gotoxy(44 + 5,7);
	printf("仓储库存信息管理面板");
	Gotoxy(44 + 3, 10);		
	printf("1.仓 储 原 料 入 库 信 息");
	Gotoxy(44 + 3, 12);
	printf("2.仓 储 原 料 出 库 信 息");
	Gotoxy(44 + 3, 14);
	printf("3.仓 储 原 料 信 息 修 改");
	Gotoxy(44 + 3, 16);
	printf("4.仓 储 原 料 信 息 查 询");
	Gotoxy(44 + 3, 18);
	printf("5.保 存 仓 储 原 料 信 息");
	Gotoxy(44 + 3, 20);
	printf("6.退 出 仓 储 原 料 管 理");
	Gotoxy(44 + 3, 24);
	printf("请输入您需要操作的编码： ");
	scanf("%d", &choice);
	Gotoxy(44 + 3 +12*2 + 3, 24);
	charRotation();
	switch (choice) {
		case 1: {
			addMaterial();
		}
		case 2: {
			deleteMaterial();
		}
		case 3: {
			modifiMWare();
		}
		case 4: {
			queryMWare();
		}
		case 5: {
			saveMWare();
		}
		case 6: {
			errorTemplate(47.5, "正在退出仓储库存管理面板！");
			exitMES(2);
		}
		default: {
			errorTemplate(47.5, "输入编号有误，请重新输入！");
			wareInterface();
		}
	}
}

/*----------------------管理界面接口集合----------------------*/
//功能界面1：新增原料入库管理界面
void addMaterial() {
	system("cls");
	frameShow();
	char temp[80];//作为价格的交换值
	MWareInfo newMWare;
	Gotoxy(44 + 5, 9);
	printf("仓储管理原料入库面板");
	Gotoxy(44, 12);
	printf("1.原料入库管理编号：");
	Gotoxy(44 + 20 + 4, 12);
	scanf("%s", newMWare.MWare_id);
	Gotoxy(44, 14);
	printf("2.原料入库登记名称：");
	Gotoxy(44 + 20 + 4, 14);
	scanf("%s", newMWare.MWare_name);
	Gotoxy(44, 16);
	printf("3.入库原料产地备注：");
	Gotoxy(44 + 20 + 4, 16);
	scanf("%s", newMWare.MWare_location);
	Gotoxy(44, 18);
	printf("4.原料供应企业登记：");
	Gotoxy(44 + 20 + 4, 18);
	scanf("%s", newMWare.MWare_company);
	Gotoxy(44, 20);
	printf("5.本批原料入库数量：");
	Gotoxy(44 + 20 + 4, 20);
	scanf("%s", temp);
	newMWare.MWare_num = atof(temp);
	getTimeNow(newMWare.in_time);
	Gotoxy(44 - 3, 24);
	printf("确认将这批次原料登记入库? y/n ：  ");
	int r1;
	scanf("%s", temp);
	Gotoxy(44 - 3, 26);
	if (temp[0] == 'y') {
		r1 = addNewMWare(&allMWareslist, newMWare);
		if (r1 == -1) {
			printf("入库原料失败，请检查该登记信息！  ");
			charRotation();
			wareInterface();
		}
		else {
			printf("入库登记成功，成功添加原料信息！  ");
			charRotation();
			wareInterface();
		}
	}
	//输入no的情况下
	else if (temp[0] == 'n') {
		printf("正在返回仓储面板，请确认后输入！ ");
		charRotation();
		Sleep(5000);
		wareInterface();
	}
	//误输入除去y和n的其它字符的话
	else {
		printf("您的输入有误，请确认要求后输入！ ");
		charRotation();
		Sleep(5000);
		addMaterial();
	}
}

//功能界面2：仓储原料出库管理界面
void deleteMaterial() {
	system("cls");
	frameShow();
	char temp[30];
	Gotoxy(44 + 3, 8);
	printf("仓储管理原料出库面板");
	Gotoxy(43, 11);
	printf("请您输入需要出库的原料编号：");
	scanf("%s", temp);
	Gotoxy(43 + 32, 11);
	charRotation();
	int r1 = searchMWare(allMWareslist, temp);
	//在这里出现查找失败的情况
	if (r1 < 0) {
		Gotoxy(44, 13);
		printf("查询原料失败，确认后输入  ");
		charRotation();
		deleteMaterial();
	}
	else {
		Gotoxy(43, 13);
		printf("请您确认需要出库的原料信息：");
		Gotoxy(44, 15);
		printf("1.原料入库管理编号： %s", allMWareslist.list[r1].MWare_id);
		Gotoxy(44, 17);
		printf("2.原料入库登记名称： %s", allMWareslist.list[r1].MWare_name);
		Gotoxy(44, 19);
		printf("3.入库原料产地备注： %s", allMWareslist.list[r1].MWare_location);
		Gotoxy(44, 21);
		printf("4.原料供应企业登记： %s", allMWareslist.list[r1].MWare_company);
		Gotoxy(44, 23);
		printf("5.本批原料入库数量： %.2f", allMWareslist.list[r1].MWare_num);
		Gotoxy(44, 25);
		printf("6.原料入库登记时间： %s", allMWareslist.list[r1].in_time);
		Gotoxy(44 - 2, 28);
		printf("确认将该批次原料出库吗？ y/n:  ");
		scanf("%s", temp);
		Gotoxy(44 - 2 + 33, 28);
		charRotation();
		Gotoxy(44 - 2, 29);
		if (temp[0] == 'y') {
			int r3 = delMWare(&allMWareslist, r1);
			if (r3 == -1) {
				printf("出库失败，无法检验该批次信息！");
				Sleep(5000);
				wareInterface();
			}
			else {
				printf("出库成功，库存中已无该批次信息！");
				Sleep(1000);
				wareInterface();
			}
		}
		//输入no的情况下
		else if (temp[0] == 'n') {
			printf("正在返回仓储面板，请确认后输入！ ");
			charRotation();
			Sleep(3000);
			wareInterface();
		}
		//误输入除去y和n的其它字符的话
		else {
			printf("您的输入有误，请确认要求后输入！ ");
			charRotation();
			Sleep(3000);
			deleteMaterial();
		}
	}
}

//功能界面3：修改仓储库存原料界面
void modifiMWare() {
	system("cls");
	frameShow();
	Gotoxy(44 + 3, 5);
	printf("仓储管理原料修改面板");
	char temp[30];
	Gotoxy(43, 8);
	printf("请您输入需要修改的原料编号：");
	scanf("%s", temp);
	Gotoxy(43 + 32, 8);
	charRotation();
	int r1 = searchMWare(allMWareslist, temp);
	int r2 = 0, r3 = 0;
	//在这里出现查找失败的情况
	if (r1 < 0) {
		Gotoxy(44, 10);
		printf("查询原料失败，确认后输入  ");
		charRotation();
		wareInterface();
	}
	else {
		Gotoxy(43, 10);
		printf("请您确认需要修改的原料信息：");
		Gotoxy(44, 12);
		printf("1.原料入库管理编号： %s", allMWareslist.list[r1].MWare_id);
		Gotoxy(44, 14);
		printf("2.原料入库登记名称： %s", allMWareslist.list[r1].MWare_name);
		Gotoxy(44, 16);
		printf("3.入库原料产地备注： %s", allMWareslist.list[r1].MWare_location);
		Gotoxy(44, 18);
		printf("4.原料供应企业登记： %s", allMWareslist.list[r1].MWare_company);
		Gotoxy(44, 20);
		printf("5.本批原料入库数量： %.2f", allMWareslist.list[r1].MWare_num);
		Gotoxy(44, 22);
		printf("6.原料入库登记时间： %s", allMWareslist.list[r1].in_time);
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
				r3 = modifyMWare(&allMWareslist, r1, r2, newContent);
				if (r3 == -1) {
					Gotoxy(44 - 2, 28);
					printf("修改原料信息失败！  ");
					charRotation();
					Sleep(5000);
					wareInterface();
				}
				else {
					Gotoxy(44 - 2, 28);
					printf("选择修改原料信息成功！ ");
					charRotation();
					Sleep(3000);
					wareInterface();
				}
				break;
			}
			//输入的编号不在范围内的
			else {
				Gotoxy(44 - 2, 26);
				printf("您输入的选项编号错误！ ");
				charRotation();
				Sleep(5000);
				wareInterface();
			}
		}
	}

}

//功能界面4：查询仓储库存原料信息界面
void queryMWare() {
	system("cls");
	frameShow();
	Gotoxy(22 + 2, 8);
	printf("仓储管理原料查询面板");
	Gotoxy(22, 10);
	printf("请您确认查询原料信息的方式：");
	int choice, r2;
	while (1) {
		Gotoxy(22, 12);
		printf("1.原料入库管理编号");
		Gotoxy(22, 14);
		printf("2.原料入库登记名称");
		Gotoxy(22, 16);
		printf("3.入库原料产地备注");
		Gotoxy(22, 18);
		printf("4.原料供应企业登记");
		Gotoxy(22, 20);
		printf("5.显示所有仓储原料");
		Gotoxy(22, 22);
		printf("6.返回仓储管理面板");
		Gotoxy(22, 25);
		printf("请输入查询方式的编号： ");
		char temp[80];
		scanf("%s", temp);
		Gotoxy(22 + 23 + 2, 25);//待定
		charRotation();
		choice = atoi(temp);
		switch (choice) {
		//输入的查询方式为1时，此时查询方式为企业编号
		case 1: {
			char content[50];
			Gotoxy(22, 27);
			printf("请输入需要查询的内容： ");
			scanf("%s", content);
			Gotoxy(22 + 20 + 5, 27);
			charRotation();
			r2 = searchMWare(allMWareslist, content);
			if (r2 < 0) {
				Gotoxy(22 + 20 + 10, 27);
				printf("查询内容失败，确认后输入  ");
				charRotation();
				queryMWare();
			}
			else {
				Gotoxy(58 + 22 - 16, 10);
				printf("1.原料入库管理编号： %s", allMWareslist.list[r2].MWare_id);
				Gotoxy(58 + 22 - 16, 12);
				printf("2.原料入库登记名称： %s", allMWareslist.list[r2].MWare_name);
				Gotoxy(58 + 22 - 16, 14);
				printf("3.入库原料产地备注： %s", allMWareslist.list[r2].MWare_location);
				Gotoxy(58 + 22 - 16, 16);
				printf("4.原料供应企业登记： %s", allMWareslist.list[r2].MWare_company);
				Gotoxy(58 + 22 - 16, 18);
				printf("5.本批原料入库数量： %.2f", allMWareslist.list[r2].MWare_num);
				Gotoxy(58 + 22 - 16, 20);
				printf("6.原料入库登记时间： %s", allMWareslist.list[r2].in_time);
				Gotoxy(58 + 22 - 16, 24);
				printf("查看结果后，请输入y返回上一层： ");
				scanf("%s", temp);
				if (temp[0] == 'y') {
					Gotoxy(58 + 22 + 16 * 2 + 2 - 16 + 1, 24);
					charRotation();
					Sleep(1000);
					queryMWare();
				}
				else {
					Gotoxy(58 + 22 + 16 * 2 + 2 - 16 + 1, 24);
					printf("输入有误，为您返回主面板 ");
					charRotation();
					Sleep(1000);
					wareInterface();
				}
			}
			break;
		}
		//输入的查询方式为2时，此时查询方式为原料名称
		case 2: {
			char content[50];
			Gotoxy(22, 27);
			printf("请输入需要查询的内容： ");
			scanf("%s", content);
			Gotoxy(22 + 23 + 8, 27);
			charRotation();
			IntSeqList result;
			intListInit(&result, 5);
			searchMWareByOthers(allMWareslist, content, choice, &result);
			if (result.length == 0) {
				errorTemplate(48, "没有满足条件的仓储信息！");
				queryMWare();
			}
			//假如成功找到有对应的值
			else {
				system("cls");
				frameShow();
				//测试一下
				Gotoxy(6, 4);
				printf("原料编号     原料名称      原料来源地              供应原料企业         仓储原料数量       原料入库时间");
				for (int i = 0; i < result.length; i++) {
					Gotoxy(8 , 8 + i);
					printf(" %s        %s           %s       %s    %.2f          %s", allMWareslist.list[result.list[i]].MWare_id, allMWareslist.list[result.list[i]].MWare_name, allMWareslist.list[result.list[i]].MWare_location, allMWareslist.list[result.list[i]].MWare_company, allMWareslist.list[result.list[i]].MWare_num, allMWareslist.list[result.list[i]].in_time);
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
					queryMWare();
				}
				//输入错误情况下
				else {
					Gotoxy(58 + 22, 28);
					printf("输入有误，为您返回主面板 ");
					charRotation();
					Sleep(1000);
					wareInterface();
				}
			}
			errorTemplate(48, "没有满足条件的仓储信息！");
			wareInterface();
			break;
		}
				//输入的查询方式为3时，此时查询方式为原料的来源地
		case 3: {
			char content[50];
			Gotoxy(22, 27);
			printf("请输入需要查询的内容： ");
			scanf("%s", content);
			Gotoxy(22 + 23 + 28 - 15, 27);
			charRotation();
			IntSeqList result;
			intListInit(&result, 5);
			searchMWareByOthers(allMWareslist, content, choice, &result);
			if (result.length == 0) {
				errorTemplate(48, "没有满足条件的仓储信息！");
				queryMWare();
			}
			//假如成功找到有对应的值
			else {
				system("cls");
				frameShow();
				//测试一下
				Gotoxy(6, 4);
				printf("原料编号     原料名称      原料来源地              供应原料企业         仓储原料数量       原料入库时间");
				for (int i = 0; i < result.length; i++) {
					Gotoxy(8 , 8 + i );
					printf(" %s        %s           %s       %s    %.2f          %s", allMWareslist.list[result.list[i]].MWare_id, allMWareslist.list[result.list[i]].MWare_name, allMWareslist.list[result.list[i]].MWare_location, allMWareslist.list[result.list[i]].MWare_company, allMWareslist.list[result.list[i]].MWare_num, allMWareslist.list[result.list[i]].in_time);
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
					queryMWare();
				}
				//输入错误情况下
				else {
					Gotoxy(58 + 22, 28);
					printf("输入有误，为您返回主面板 ");
					charRotation();
					Sleep(1000);
					wareInterface();
				}
			}
			errorTemplate(48, "没有满足条件的库存信息！");
			wareInterface();
			break;
		}
		//输入的查询方式为4时，此时查询方式为提供原料的企业名称
		case 4: {
			char content[50];
			Gotoxy(22, 27);
			printf("请输入需要查询的内容： ");
			scanf("%s", content);
			Gotoxy(22 + 23 + 29, 27);
			charRotation();
			IntSeqList result;
			intListInit(&result, 5);
			searchMWareByOthers(allMWareslist, content, choice, &result);
			if (result.length == 0) {
				errorTemplate(48, "没有满足条件的仓储信息！");
				queryMWare();
			}
			//假如成功找到有对应的值
			else {
				system("cls");
				frameShow();
				//测试一下
				Gotoxy(6, 4);
				printf("原料编号     原料名称      原料来源地              供应原料企业         仓储原料数量       原料入库时间");
				for (int i = 0; i < result.length; i++) {
					Gotoxy(8, 8 + i );
					printf(" %s        %s           %s       %s    %.2f          %s", allMWareslist.list[result.list[i]].MWare_id, allMWareslist.list[result.list[i]].MWare_name, allMWareslist.list[result.list[i]].MWare_location, allMWareslist.list[result.list[i]].MWare_company, allMWareslist.list[result.list[i]].MWare_num, allMWareslist.list[result.list[i]].in_time);
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
					queryMWare();
				}
				//输入错误情况下
				else {
					Gotoxy(58 + 22, 28);
					printf("输入有误，为您返回主面板 ");
					charRotation();
					Sleep(1000);
					wareInterface();
				}
			}
			errorTemplate(48, "没有满足条件的仓储信息！");
			wareInterface();
			break;
		}
		//输入的查询方式为4时，此时查询方式为显示所有企业
		case 5: {
			if (allMWareslist.length == 0) {
				errorTemplate(48, "仓储管理信息数据库为空！");
				queryMWare();
			}
			system("cls");
			frameShow();
			//测试一下
			Gotoxy(6, 4);
			printf("原料编号     原料名称      原料来源地              供应原料企业         仓储原料数量       原料入库时间");
			for (int i = 0; i < allMWareslist.length; i++) {
				Gotoxy(8, 8 + i );
				printf(" %s        %s           %s       %s    %.2f          %s", allMWareslist.list[i].MWare_id, allMWareslist.list[i].MWare_name, allMWareslist.list[i].MWare_location, allMWareslist.list[i].MWare_company, allMWareslist.list[i].MWare_num, allMWareslist.list[i].in_time);
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
				queryMWare();
			}
			//输入错误情况下
			else {
				Gotoxy(58 + 22, 28);
				printf("输入有误，为您返回主面板 ");
				charRotation();
				Sleep(1000);
				wareInterface();
			}
		}
		//输入的查询方式为6时，此时退出查询企业面板
		case 6: {
			errorTemplate(49, "正在返回仓储管理面板！");
			wareInterface();
		}
		default: {
			errorTemplate(48, "输入的查询方式编号有误！");
			queryMWare();
		}
		}
	}
}

//功能界面5：保存供应企业信息界面
void saveMWare() {
	int r1 = allSaveWare();
	if (r1 == -1) {
		errorTemplate(48, "保存当前的仓储信息失败！");
		wareInterface();
	}
	else {
		errorTemplate(48, "正在保存所有的仓储信息！");
		errorTemplate(48, "保存所有的仓储信息成功！");
		wareInterface();
	}
}

//配合功能界面1：功能函数--增加原材料入库登记信息
int addNewMWare(MWaresSeqList* mwsl, MWareInfo newMWare) {

	//首先在仓储库存管理信息中查找是否有此原料的库存，如果有，返回 - 1，表示入库登记失败
	int r = searchMWare(*mwsl, newMWare.MWare_id);
	if (r >= 0) {
		errorTemplate(48, "原料入库登记编号已存在！");
		wareInterface();
	}
	//如果有序表空间不够，则扩充空间
	if (mwsl->length >= mwsl->size) {
		MWareInfo* t = mwsl->list;
		mwsl->list = (MWareInfo*)malloc(2 * mwsl->size * sizeof(MWareInfo));
		if (mwsl->list == NULL) {
			errorTemplate(48, "保存无效，内存分配失败！");
			wareInterface();
		}
		mwsl->size = 2 * mwsl->size;
		for (int i = 0; i < mwsl->length; i++)
			MWareCopy(&(mwsl->list[i]), t[i]);
		free(t);
	}
	//	较原料入库登记编号插入到合适的位置，保证据原料供应企业编号有序
	int i = 0;
	for (i = mwsl->length - 1; i >= 0; i--) {
		r = strcmp(mwsl->list[i].MWare_id, newMWare.MWare_id);
		if (r > 0)
			MWareCopy(&(mwsl->list[i + 1]), mwsl->list[i]);
		else
			break;

	}
	MWareCopy(&(mwsl->list[i + 1]), newMWare);
	mwsl->length++;
	//添加成功返回0
	return 0;
}

//配合功能界面123：功能函数--在原料入库登记表以及库存中根据登记原料编号进行查找，没有该编号所占用库存则返回-1；如果有返回值则是该登记编号已被占用（查找算法用二分查找法）
int searchMWare(MWaresSeqList mwsl, char* MWsn) {		//传递了两个参数，一个是mcsl，一个是MWsn
	int low = 0;
	int high = mwsl.length - 1;
	int mid;
	while (low <= high) {
		mid = (low + high) / 2;		//二分查找法
		if (strcmp(mwsl.list[mid].MWare_id, MWsn) == 0)
			return mid;
		else
			if (strcmp(mwsl.list[mid].MWare_id, MWsn) < 0)
				low = mid + 1;
			else
				high = mid - 1;
	}
	return -1;
}

//配合功能界面123：功能函数--深度拷贝新增入库原料登记信息
void MWareCopy(MWareInfo* to, MWareInfo from) {
	strcpy(to->MWare_id, from.MWare_id);
	strcpy(to->MWare_name, from.MWare_name);
	strcpy(to->MWare_location, from.MWare_location);
	strcpy(to->MWare_company, from.MWare_company);
	to->MWare_num = from.MWare_num;
	strcpy(to->in_time, from.in_time);
}

//配合功能界面2：功能函数--在原料仓储管理表中删除第index个元素，删除算法为把后面的数据元素覆盖前面，返回0表示删除成功
int delMWare(MWaresSeqList* mwsl, int index) {
	if (mwsl->length <= 0) {
		errorTemplate(48, "仓储管理数据库信息为空！");
		wareInterface();
		return -1;
	}
	if (index < 0 || index >= mwsl->length) {
		errorTemplate(47, "需要出库的原料超出执行范围！");
		wareInterface();
		return -1;
	}

	for (int i = index + 1; i < mwsl->length; i++) {
		MWareCopy(&(mwsl->list[i - 1]), mwsl->list[i]);
	}
	mwsl->length--;
	return 0;
}

//配合功能界面3：功能函数：在仓储管理表mwsl中修改第index个原料批次的信息，type表示要修改的类型（取值1（原料登记编号），2（原料登记名称），3（供应原料所在地），4（供应原料企业名称）），info表示新的信息值，修改成功返回0，否则返回1
int modifyMWare(MWaresSeqList* mwsl, int index, int type, char* info) {
	if (index < 0 && index >= mwsl->length) {
		errorTemplate(47, "需要出库的原料超出执行范围！");
		wareInterface();
	}
	switch (type) {
		case 1: strcpy(mwsl->list[index].MWare_id, info); break;
		case 2: strcpy(mwsl->list[index].MWare_name, info); break;
		case 3: strcpy(mwsl->list[index].MWare_location, info); break;
		case 4: strcpy(mwsl->list[index].MWare_company, info); break;
		case 5: mwsl->list[index].MWare_num = atof(info); break;
		case 6: strcpy(mwsl->list[index].in_time, info); break;
		default: {
			errorTemplate(48, "修改的原料信息编号有误！");
			wareInterface();
		}
	}
	return 0;
}

//配合功能界面4：功能函数--根据仓储原料的批次信息（tpye取值1（原料登记名称），2（供应原料所在地），3（供应原料企业名称））查询相关记录的仓储库存信息。
//               如果没有找到，则返回 - 1；如果有，查询结果用一个IntSeqList列表返回，列表装的是原料在仓储顺序表中的序号
int searchMWareByOthers(MWaresSeqList mwsl, char* info, int type, IntSeqList* mwindex) {
	for (int i = 0; i < mwsl.length; i++) {
		switch (type - 1) {
			//当输入的选项为2时，type值对应为1，则执行按照原料登记名称查询的手法；
			case 1: if (strcmp(mwsl.list[i].MWare_name, info) == 0)
				addInt(mwindex, i);
				break;
			//当输入的选项为3时，type值对应为2，则执行按照供应原料所在地的查询的手法：
			case 2: if (strcmp(mwsl.list[i].MWare_location, info) == 0)
				addInt(mwindex, i);
				break;
			//当输入的选项为4时，type值对应为3，则执行按照供应原料企业名称的查询手法；
			case 3: if (strcmp(mwsl.list[i].MWare_company, info) == 0)
				addInt(mwindex, i);
				break;
			default: {
				errorTemplate(47.5, "查询库存信息方式编号有误！");
				wareInterface();
			}
		}
	}
	return 0;
}

//配合功能界面5：功能函数--保存在系统中增加删除更改后的信息进入数据库中
int allMWaresInfoSaveToFile(MWaresSeqList mwsl, char* filename) {
	FILE *fp;
	char strline[80];
	if ((fp = fopen(filename, "w")) == NULL) {
		errorTemplate(48, "仓储管理的数据库不存在！");
		wareInterface();
	}

	for (int i = 0; i < mwsl.length; i++) {
		fputs(mwsl.list[i].MWare_id, fp);
		fputc('\n', fp);
		fputs(mwsl.list[i].MWare_name, fp);
		fputc('\n', fp);
		fputs(mwsl.list[i].MWare_location, fp);
		fputc('\n', fp);
		fputs(mwsl.list[i].MWare_company, fp);
		fputc('\n', fp);
		sprintf(strline, "%.2f", mwsl.list[i].MWare_num);
		fputs(strline, fp);
		fputc('\n', fp);
		fputs(mwsl.list[i].in_time, fp);
		fputc('\n', fp);
	}
	fclose(fp);
	return 0;
}

//配合功能界面5：功能函数--按类型保存仓储信息到文件中
int allSaveWare() {
	int r1 = allMWaresInfoSaveToFile(allMWareslist, "仓储管理信息数据库.txt");  //保存所有的仓储信息到文件中
	if (r1 == -1) {
		errorTemplate(48, "保存当前的仓储信息失败！");
		wareInterface();
	}
	return 0;
}

//特殊接口函数：管理员专用于查询仓储库存原料信息界面
void queryMWareAdmin() {
	system("cls");
	frameShow();
	Gotoxy(22 + 2, 8);
	printf("仓储管理原料查询面板");
	Gotoxy(22, 10);
	printf("请您确认查询原料信息的方式：");
	int choice, r2;
	while (1) {
		Gotoxy(22, 12);
		printf("1.原料入库管理编号");
		Gotoxy(22, 14);
		printf("2.原料入库登记名称");
		Gotoxy(22, 16);
		printf("3.入库原料产地备注");
		Gotoxy(22, 18);
		printf("4.原料供应企业登记");
		Gotoxy(22, 20);
		printf("5.显示所有仓储原料");
		Gotoxy(22, 22);
		printf("6.返回管理员的面板");
		Gotoxy(22, 25);
		printf("请输入查询方式的编号： ");
		char temp[80];
		scanf("%s", temp);
		Gotoxy(22 + 23 + 2, 25);//待定
		charRotation();
		choice = atoi(temp);
		switch (choice) {
			//输入的查询方式为1时，此时查询方式为企业编号
		case 1: {
			char content[50];
			Gotoxy(22, 27);
			printf("请输入需要查询的内容： ");
			scanf("%s", content);
			Gotoxy(22 + 20 + 5, 27);
			charRotation();
			r2 = searchMWare(allMWareslist, content);
			if (r2 < 0) {
				Gotoxy(22 + 20 + 10, 27);
				printf("查询内容失败，确认后输入  ");
				charRotation();
				queryMWare();
			}
			else {
				Gotoxy(58 + 22 - 16, 10);
				printf("1.原料入库管理编号： %s", allMWareslist.list[r2].MWare_id);
				Gotoxy(58 + 22 - 16, 12);
				printf("2.原料入库登记名称： %s", allMWareslist.list[r2].MWare_name);
				Gotoxy(58 + 22 - 16, 14);
				printf("3.入库原料产地备注： %s", allMWareslist.list[r2].MWare_location);
				Gotoxy(58 + 22 - 16, 16);
				printf("4.原料供应企业登记： %s", allMWareslist.list[r2].MWare_company);
				Gotoxy(58 + 22 - 16, 18);
				printf("5.本批原料入库数量： %.2f", allMWareslist.list[r2].MWare_num);
				Gotoxy(58 + 22 - 16, 20);
				printf("6.原料入库登记时间： %s", allMWareslist.list[r2].in_time);
				Gotoxy(58 + 22 - 16, 24);
				printf("查看结果后，请输入y返回上一层： ");
				scanf("%s", temp);
				if (temp[0] == 'y') {
					Gotoxy(58 + 22 + 16 * 2 + 2 - 16 + 1, 24);
					charRotation();
					Sleep(1000);
					queryMWare();
				}
				else {
					Gotoxy(58 + 22 + 16 * 2 + 2 - 16 + 1, 24);
					printf("输入有误，为您返回主面板 ");
					charRotation();
					Sleep(1000);
					adminLeaderInterface();
				}
			}
			break;
		}
				//输入的查询方式为2时，此时查询方式为原料名称
		case 2: {
			char content[50];
			Gotoxy(22, 27);
			printf("请输入需要查询的内容： ");
			scanf("%s", content);
			Gotoxy(22 + 23 + 8, 27);
			charRotation();
			IntSeqList result;
			intListInit(&result, 5);
			searchMWareByOthers(allMWareslist, content, choice, &result);
			if (result.length == 0) {
				errorTemplate(48, "没有满足条件的仓储信息！");
				queryMWare();
			}
			//假如成功找到有对应的值
			else {
				system("cls");
				frameShow();
				//测试一下
				Gotoxy(6, 4);
				printf("原料编号     原料名称      原料来源地              供应原料企业         仓储原料数量       原料入库时间");
				for (int i = 0; i < result.length; i++) {
					Gotoxy(8, 8 + i);
					printf(" %s        %s           %s       %s    %.2f          %s", allMWareslist.list[result.list[i]].MWare_id, allMWareslist.list[result.list[i]].MWare_name, allMWareslist.list[result.list[i]].MWare_location, allMWareslist.list[result.list[i]].MWare_company, allMWareslist.list[result.list[i]].MWare_num, allMWareslist.list[result.list[i]].in_time);
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
					queryMWare();
				}
				//输入错误情况下
				else {
					Gotoxy(58 + 22, 28);
					printf("输入有误，为您返回主面板 ");
					charRotation();
					Sleep(1000);
					adminLeaderInterface();
				}
			}
			errorTemplate(48, "没有满足条件的仓储信息！");
			adminLeaderInterface();
			break;
		}
				//输入的查询方式为3时，此时查询方式为原料的来源地
		case 3: {
			char content[50];
			Gotoxy(22, 27);
			printf("请输入需要查询的内容： ");
			scanf("%s", content);
			Gotoxy(22 + 23 + 28 - 15, 27);
			charRotation();
			IntSeqList result;
			intListInit(&result, 5);
			searchMWareByOthers(allMWareslist, content, choice, &result);
			if (result.length == 0) {
				errorTemplate(48, "没有满足条件的仓储信息！");
				queryMWare();
			}
			//假如成功找到有对应的值
			else {
				system("cls");
				frameShow();
				//测试一下
				Gotoxy(6, 4);
				printf("原料编号     原料名称      原料来源地              供应原料企业         仓储原料数量       原料入库时间");
				for (int i = 0; i < result.length; i++) {
					Gotoxy(8, 8 + i);
					printf(" %s        %s           %s       %s    %.2f          %s", allMWareslist.list[result.list[i]].MWare_id, allMWareslist.list[result.list[i]].MWare_name, allMWareslist.list[result.list[i]].MWare_location, allMWareslist.list[result.list[i]].MWare_company, allMWareslist.list[result.list[i]].MWare_num, allMWareslist.list[result.list[i]].in_time);
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
					queryMWare();
				}
				//输入错误情况下
				else {
					Gotoxy(58 + 22, 28);
					printf("输入有误，为您返回主面板 ");
					charRotation();
					Sleep(1000);
					adminLeaderInterface();
				}
			}
			errorTemplate(48, "没有满足条件的库存信息！");
			adminLeaderInterface();
			break;
		}
				//输入的查询方式为4时，此时查询方式为提供原料的企业名称
		case 4: {
			char content[50];
			Gotoxy(22, 27);
			printf("请输入需要查询的内容： ");
			scanf("%s", content);
			Gotoxy(22 + 23 + 29, 27);
			charRotation();
			IntSeqList result;
			intListInit(&result, 5);
			searchMWareByOthers(allMWareslist, content, choice, &result);
			if (result.length == 0) {
				errorTemplate(48, "没有满足条件的仓储信息！");
				queryMWare();
			}
			//假如成功找到有对应的值
			else {
				system("cls");
				frameShow();
				//测试一下
				Gotoxy(6, 4);
				printf("原料编号     原料名称      原料来源地              供应原料企业         仓储原料数量       原料入库时间");
				for (int i = 0; i < result.length; i++) {
					Gotoxy(8, 8 + i);
					printf(" %s        %s           %s       %s    %.2f          %s", allMWareslist.list[result.list[i]].MWare_id, allMWareslist.list[result.list[i]].MWare_name, allMWareslist.list[result.list[i]].MWare_location, allMWareslist.list[result.list[i]].MWare_company, allMWareslist.list[result.list[i]].MWare_num, allMWareslist.list[result.list[i]].in_time);
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
					queryMWare();
				}
				//输入错误情况下
				else {
					Gotoxy(58 + 22, 28);
					printf("输入有误，为您返回主面板 ");
					charRotation();
					Sleep(1000);
					adminLeaderInterface();
				}
			}
			errorTemplate(48, "没有满足条件的仓储信息！");
			adminLeaderInterface();
			break;
		}
				//输入的查询方式为4时，此时查询方式为显示所有企业
		case 5: {
			if (allMWareslist.length == 0) {
				errorTemplate(48, "仓储管理信息数据库为空！");
				queryMWare();
			}
			system("cls");
			frameShow();
			//测试一下
			Gotoxy(6, 4);
			printf("原料编号     原料名称      原料来源地              供应原料企业         仓储原料数量       原料入库时间");
			for (int i = 0; i < allMWareslist.length; i++) {
				Gotoxy(8, 8 + i);
				printf(" %s        %s           %s       %s    %.2f          %s", allMWareslist.list[i].MWare_id, allMWareslist.list[i].MWare_name, allMWareslist.list[i].MWare_location, allMWareslist.list[i].MWare_company, allMWareslist.list[i].MWare_num, allMWareslist.list[i].in_time);
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
				queryMWare();
			}
			//输入错误情况下
			else {
				Gotoxy(58 + 22, 28);
				printf("输入有误，为您返回主面板 ");
				charRotation();
				Sleep(1000);
				adminLeaderInterface();
			}
		}
				//输入的查询方式为6时，此时退出查询企业面板
		case 6: {
			errorTemplate(49, "正在返回管理员的面板！");
			adminLeaderInterface();
		}
		default: {
			errorTemplate(48, "输入的查询方式编号有误！");
			queryMWare();
		}
		}
	}
}