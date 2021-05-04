#include<stdio.h>
#include <stdio.h>
#include <windows.h>
#include<process.h>
#include <time.h>

#include"Globals.h"
#include"DynamicEffect .h"
#include"MES-Leader.h"
#include"MainInterface.h"
#include"MES-PLSupervisionEngineer.h"
#include"MES-ProductSalesman.h"

#define _CRT_SECURE_NO_DEPRECATE；
#define _CRT_SECURE_NO_WARNINGS；
#pragma warning(disable:4996)；

extern MComsSeqList allMComslist;
extern PComsSeqList allPComslist;
/*----------------------数据结构接口集合----------------------*/
//数据结构操作1：MCom界面-初始化有序表 mcsl，size表示初始化容量
void MComsSeqListInit(MComsSeqList* mcsl, int size);
//数据结构操作2：MCom界面--数据库信息初始化
int allMComsInfoReadFromFile(MComsSeqList* mcsl, char* filename);

//数据结构操作3：PCom界面-初始化有序表 pcsl，size表示初始化容量
void PComsSeqListInit(PComsSeqList* pcsl, int size);

//数据结构操作4：PCom界面--数据库信息初始化
int allPComsInfoReadFromFile(PComsSeqList* pcsl, char* filename);

/*----------------------用户界面接口集合----------------------*/
//界面1：root超级用户的登陆界面
void rootLeaderInterface();
//界面2：企业管理者的登陆界面
void adminLeaderInterface();
//界面3：原料供应企业信息管理界面
void materialComInterface();
//界面4：产品采购企业信息管理界面
void productComInterface();

/*----------------------管理界面接口集合----------------------*/
//功能界面1：原料供应企业添加界面
void addMaterialCom();
//功能界面2：解除原料供应企业合作关系界面
void deleteMaterialCom();
//功能界面3：修改企业供应原料界面
void modifiMCom();
//功能界面4：查询供应企业信息界面
void queryMCom();
//功能界面5：保存供应企业信息界面
void saveMCom();
//功能界面6：产品采购企业签订界面
void addProductCom();
//功能界面7：解除产品采购企业合作关系界面
void deleteProductCom();
//功能界面8：修改企业供应原料界面
void modifiPCom();
//功能界面9：查询采购企业信息界面
void queryPCom();
//功能界面10：保存采购企业信息界面
void savePCom();

/*----------------------功能函数接口集合----------------------*/
//配合功能界面1：功能函数--增加原材料供应企业
int addNewMCom(MComsSeqList* mcsl, MComInfo newMCom);
//配合功能界面1：功能函数--增加原材料供应企业
int addNewPCom(PComsSeqList* pcsl, PComInfo newPCom);
//配合功能界面123：功能函数--在原料供应企业表中根据签约企业编号进行查找，没有此企业则返回-1；如果有返回值则是该原料供应企业的编号（查找算法用二分查找法）
int searchMCom(MComsSeqList mcsl, char* MCsn);
//配合功能界面123：功能函数--在产品采购企业表中根据签约企业编号进行查找，没有此企业则返回-1；如果有返回值则是该产品采购企业的编号（查找算法用插值查找法）
int searchMComByInterpolationSearch(MComsSeqList mcsl, char* MCsn);
//配合功能界面123：功能函数--在产品采购企业表中根据签约企业编号进行查找，没有此企业则返回-1；如果有返回值则是该产品采购企业的编号（查找算法用二分查找法）
int searchPCom(PComsSeqList pcsl, char* PCsn);
//配合功能界面123：功能函数--在产品采购企业表中根据签约企业编号进行查找，没有此企业则返回-1；如果有返回值则是该产品采购企业的编号（查找算法用插值查找法）
int searchPComByInterpolationSearch(PComsSeqList pcsl, char* PCsn);
//配合功能界面123：功能函数--深度拷贝新增原料供应企业
void MComCopy(MComInfo* to, MComInfo from);
//配合功能界面123：功能函数--深度拷贝新增产品采购企业
void PComCopy(PComInfo* to, PComInfo from);
//配合功能界面2：功能函数--在原料供应企业表中删除第index个元素，删除算法为把后面的数据元素覆盖前面，返回0表示删除成功
int delMCom(MComsSeqList* mcsl, int index);
//配合功能界面2：功能函数--在原料供应企业表中删除第index个元素，删除算法为把后面的数据元素覆盖前面，返回0表示删除成功
int delPCom(PComsSeqList* pcsl, int index);
//配合功能界面3：功能函数：在原料供应企业表mcsl中修改第index个企业的信息，type表示要修改的类型（取值1（企业编号），2（企业名称），3（企业所在地），4（企业所提供产品）），info表示新的信息值，修改成功返回0，否则返回1
int modifyMCom(MComsSeqList* mcsl, int index, int type, char* info);
//配合功能界面3：功能函数：在产品采购企业表mcsl中修改第index个企业的信息，type表示要修改的类型（取值1（企业编号），2（企业名称），3（企业所在地），4（企业所提供产品）），info表示新的信息值，修改成功返回0，否则返回1
int modifyPCom(PComsSeqList* pcsl, int index, int type, char* info);

//配合功能界面4：功能函数--根据提供的原料企业信息（tpye取值1（企业名称），2（企业所在地），3（企业提供原料））查询相关记录的企业信息。
//               如果没有找到，则返回 - 1；如果有，查询结果用一个IntSeqList列表返回，列表装的是企业在顺序表中的序号
int searchMComByOthers(MComsSeqList mcsl, char* info, int type, IntSeqList* mcindex);
//配合功能界面4：功能函数--根据采购产品的企业信息（tpye取值1（企业名称），2（企业所在地），3（企业订购产品））查询相关记录的企业信息。
//               如果没有找到，则返回 - 1；如果有，查询结果用一个IntSeqList列表返回，列表装的是企业在顺序表中的序号
int searchPComByOthers(PComsSeqList pcsl, char* info, int type, IntSeqList* pcindex);
//配合功能界面5：功能函数--保存在系统中增加删除更改后的信息进入数据库中
int allMComsInfoSaveToFile(MComsSeqList mcsl, char* filename);
//配合功能界面5：功能函数--保存在系统中增加删除更改后的信息进入数据库中
int allPComsInfoSaveToFile(PComsSeqList pcsl, char* filename);
//（通用）配合功能界面5：功能函数--按类型保存各类信息到文件中
int allSave(int type);

void BubbleSortPrice(MComsSeqList* mcsl);
void MySwap(MComsSeqList* mcsl, int x, int y);

/*----------------------原料供应企业信息管理数据结构接口----------------------*/
//数据结构操作1：MCom界面-初始化有序表 mcsl，size表示初始化容量
void MComsSeqListInit(MComsSeqList* mcsl, int size) {
	mcsl->list = (MComInfo*)malloc(size * sizeof(MComInfo));
	mcsl->size = size;
	mcsl->length = 0;
}

//数据结构操作2：MCom界面--数据库信息初始化
int allMComsInfoReadFromFile(MComsSeqList* mcsl, char* filename) {
	FILE *fp;
	char strline[80];             //每行最大读取的字符数
	if ((fp = fopen(filename, "r")) == NULL) { //判断文件是否存在及可读
		errorTemplate(48, "加载 MES数据库信息出错！");
		return -1;
	}
	MComInfo newMCom;
	while (!feof(fp)) {
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newMCom.MCom_id, strline);
		else {
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newMCom.MCom_name, strline);
		else {
			errorTemplate(48, "加载 MES数据库信息出错！");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newMCom.MCom_location, strline);
		else {
			errorTemplate(48, "加载 MES数据库信息出错！");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newMCom.MCom_material, strline);
		else {
			errorTemplate(48, "加载 MES数据库信息出错！");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0) {
			newMCom.MCom_price = atof(strline);
		}
		else {
			errorTemplate(48, "加载 MES数据库信息出错！");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0) {
			strcpy(newMCom.in_time, strline);
		}
		else {
			errorTemplate(48, "加载 MES数据库信息出错！");
			fclose(fp);
			return -1;
		}
		addNewMCom(mcsl, newMCom);
	}
	fclose(fp);//关闭文件
	return 0;
}

//数据结构操作3：PCom界面-初始化有序表 pcsl，size表示初始化容量
void PComsSeqListInit(PComsSeqList* pcsl, int size) {
	pcsl->list = (PComInfo*)malloc(size * sizeof(PComInfo));
	pcsl->size = size;
	pcsl->length = 0;
}

//数据结构操作4：PCom界面--数据库信息初始化
int allPComsInfoReadFromFile(PComsSeqList* pcsl, char* filename) {
	FILE *fp;
	char strline[80];             //每行最大读取的字符数
	if ((fp = fopen(filename, "r")) == NULL) { //判断文件是否存在及可读
		errorTemplate(48, "加载 MES数据库信息出错！");
		return -1;
	}
	PComInfo newPCom;
	while (!feof(fp)) {
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newPCom.PCom_id, strline);
		else {
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newPCom.PCom_name, strline);
		else {
			errorTemplate(48, "加载 MES数据库信息出错！");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newPCom.PCom_location, strline);
		else {
			errorTemplate(48, "加载 MES数据库信息出错！");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newPCom.PCom_material, strline);
		else {
			errorTemplate(48, "加载 MES数据库信息出错！");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0) {
			newPCom.PCom_price = atof(strline);
		}
		else {
			errorTemplate(48, "加载 MES数据库信息出错！");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0) {
			strcpy(newPCom.in_time, strline);
		}
		else {
			errorTemplate(48, "加载 MES数据库信息出错！");
			fclose(fp);
			return -1;
		}
		addNewPCom(pcsl, newPCom);
	}
	fclose(fp);//关闭文件
	return 0;
}

//界面1：root超级用户的登陆界面
void rootLeaderInterface() {
	int choice = 0;
	frameShow();
	Gotoxy(44 + 5, 9.5);
	printf("鲁班MES智慧控制面板");
	Gotoxy(44, 12);		//动态移动光标，同时本页面以坐标（48，10）作为基准移动下面的光标
	printf("1.执 行 仓 储 管 理 员 权 限 ");
	Gotoxy(44, 14);
	printf("2.执 行 工艺流程设计师 权 限 ");
	Gotoxy(44, 16);
	printf("3.执 行 产线监督工程师 权 限 ");
	Gotoxy(44, 18);
	printf("4.执 行 产 品 销 售 员 权 限 ");
	Gotoxy(44, 20);
	printf("5.退 出 超 级 用户ROOT 权 限 ");
	Gotoxy(44, 24);
	printf("请输入需要执行的权限编码：");//23
	Gotoxy(44 + 23 + 4, 24);
	scanf("%d", &choice);
	switch (choice) {
		case 1: {
			rootWelcome(44+3, "欢迎您，鲁班超级Root用户！","提示：您可以执行仓储管理员的所有权限！" ,choice);
			wareInterface();
		}
		case 2: {
			rootWelcome(44 + 3, "欢迎您，鲁班超级Root用户！", "提示：您可以执行流程设计师的所有权限！", choice);
			DProcessInterface();
		}
		case 3: {
			rootWelcome(44 + 3, "欢迎您，鲁班超级Root用户！", "提示：您可以执行生产工程师的所有权限！", choice);
			SuperPLInterface();
		}
		case 4: {
			rootWelcome(44 + 3, "欢迎您，鲁班超级Root用户！", "提示：您可以执行产品销售员的所有权限！", choice);
			proSalesInterface();
		}
		case 5: {
			exitMES(0);
		}
		default: {
			errorTemplate(47.5, "输入编号有误，请重新输入！");
			rootLeaderInterface();
		}
	}
}

//界面2：企业管理者的登陆界面
void adminLeaderInterface() {			//企业管理者的角色进入MES系统界面
	system("cls");
	int choice = 0;
	frameShow();
	Gotoxy(44 + 5, 6.5);
	printf("鲁班MES智慧控制面板");
	Gotoxy(44 + 2, 9);		//动态移动光标，同时本页面以坐标（48，10）作为基准移动下面的光标
	printf("1.原 料 供 应 信 息 维 护 ");
	Gotoxy(44 + 2, 11);
	printf("2.仓 库 存 储 信 息 查 看 ");
	Gotoxy(44 + 2, 13);
	printf("3.工 艺 流 程 信 息 查 看 ");
	Gotoxy(44 + 2, 15);
	printf("4.产 线 工 作 信 息 查 看 ");
	Gotoxy(44 + 2, 17);
	printf("5.机 床 工 作 信 息 查 看 ");
	Gotoxy(44 + 2, 19);
	printf("6.产 品 采 购 信 息 维 护 ");
	Gotoxy(44 + 2, 21);
	printf("7.退 出 智 慧 控 制 面 板 ");
	Gotoxy(44 + 2, 24);
	printf("请输入您需要操作的编码：");
	Gotoxy(44 + 23 + 3, 24);
	scanf("%d", &choice);
	Gotoxy(44 + 2+27, 24);
	charRotation();
	switch (choice){
		case 1: {
			materialComInterface();
		}
		case 2: {
			queryMWareAdmin();
		}	
		case 3: {
			checkDProcessAdmin();
		}
		case 4: {
			//9.特殊接口函数--管理员工厂产线工作查看
			checkPLineAdmin();
		}
		case 5: {
			//10.特殊接口函数--管理员工厂机床工作查看
			checkPToolAdmin();
		}
		case 6: {
			productComInterface();
		}
		case 7: {
			exitMES(1);
		}
		default: {
			errorTemplate(47.5, "输入编号有误，请重新输入！");
			adminLeaderInterface();
		}
	}
}

//界面3：原料供应企业信息管理界面
void materialComInterface() {	//原料供应企业信息管理界面
	int choice;
	system("cls");
	frameShow();
	Gotoxy(44 + 5, 7.5);
	printf("原料供应企业信息管理");
	Gotoxy(44 + 4, 10);		//动态移动光标，同时本页面以坐标（48，10）作为基准移动下面的光标
	printf("1.签定原料供应企业合作");
	Gotoxy(44 + 4, 12);
	printf("2.解除原料供应企业合作");
	Gotoxy(44 + 4, 14);
	printf("3.原料供应企业信息修改");
	Gotoxy(44 + 4, 16);
	printf("4.原料供应企业信息查询");
	Gotoxy(44 + 4, 18);
	printf("5.保存原料供应企业信息 ");
	Gotoxy(44 + 4, 20);
	printf("6.退出原料供应企业管理");
	Gotoxy(44 +3, 24);
	printf("请输入您需要操作的编码： ");
	scanf("%d", &choice);
	Gotoxy(44 + 3 +12*2 + 0.5 +2, 24);
	charRotation();
	switch (choice) {
	case 1: {
		addMaterialCom();
	}
	case 2: {
		deleteMaterialCom();
	}
	case 3: {
		modifiMCom();
	}
	case 4: {
		queryMCom();
	}
	case 5: {
		saveMCom();
	}
	case 6: {
		errorTemplate(47.5, "正在退出供应企业管理面板！");
		adminLeaderInterface();
	}
	default: {
		errorTemplate(47.5, "输入编号有误，请重新输入！");
		materialComInterface();
	}
	}
}

//界面4：产品采购企业信息管理界面
void productComInterface() {	//产品采购企业信息管理界面
	int choice;
	system("cls");
	frameShow();
	Gotoxy(44 + 5, 7.5);
	printf("产品采购企业信息管理");
	Gotoxy(44 + 4, 10);		//动态移动光标，同时本页面以坐标（48，10）作为基准移动下面的光标
	printf("1.签定产品采购企业合作");
	Gotoxy(44 + 4, 12);
	printf("2.解除产品采购企业合作");
	Gotoxy(44 + 4, 14);
	printf("3.原料产品采购信息修改");
	Gotoxy(44 + 4, 16);
	printf("4.原料产品采购信息查询");
	Gotoxy(44 + 4, 18);
	printf("5.保存产品采购企业信息 ");
	Gotoxy(44 + 4, 20);
	printf("6.退出产品采购企业管理");
	Gotoxy(44 + 3, 24);
	printf("请输入您需要操作的编码： ");
	scanf("%d", &choice);
	Gotoxy(44 + 3 + 12 * 2 + 0.5 + 2, 24);
	charRotation();
	switch (choice) {
		case 1: {
			addProductCom();
		}
		case 2: {
			deleteProductCom();
		}
		case 3: {
			modifiPCom();
		}
		case 4: {
			queryPCom();
		}
		case 5: {
			savePCom();
		}
		case 6: {
			errorTemplate(47.5, "正在退出采购企业管理面板！");
			adminLeaderInterface();
		}
		default: {
			errorTemplate(47.5, "输入编号有误，请重新输入！");
			materialComInterface();
		}
	}
}

//界面5：企业员工信息管理界面（功能类似的接口：暂不启用）
/*暂不启用的企业员工信息管理界面
void employeeInterface() {		//企业员工信息管理界面
	int choice;
	system("cls");
	frameShow();
	Gotoxy(44 + 7, 7.5);
	printf("企业员工信息管理");
	Gotoxy(44 + 5, 10);		//动态移动光标，同时本页面以坐标（48，10）作为基准移动下面的光标
	printf("1.添加企业员工信息");
	Gotoxy(44 + 5, 12);
	printf("2.删除企业员工信息");
	Gotoxy(44 + 5, 14);
	printf("3.企业员工信息修改");
	Gotoxy(44 + 5, 16);
	printf("4.企业员工信息查询 ");
	Gotoxy(44 + 5, 18);
	printf("5.保存企业员工信息 ");
	Gotoxy(44 + 5, 20);
	printf("6.退出员工信息管理");
	Gotoxy(44 + 5, 24);
	printf("请输入您需要操作的编码：");
	Gotoxy(44 + 23 + 1, 24);
	scanf("%d", &choice);
	
}
*/

//功能界面1：原料供应企业签订界面
void addMaterialCom() {
	system("cls");
	frameShow();
	char temp[80];//作为价格的交换值
	MComInfo newMCom;
	Gotoxy(44 + 5, 9.5);
	printf("原料供应企业签约面板");
	Gotoxy(44, 12);
	printf("1.原料供应企业编号：");
	Gotoxy(44+20.5+4, 12);
	scanf("%s", newMCom.MCom_id);
	Gotoxy(44, 14);
	printf("2.原料供应企业名称：");
	Gotoxy(44 + 20.5 + 4, 14);
	scanf("%s", newMCom.MCom_name);
	Gotoxy(44, 16);
	printf("3.供应原料的所在地：");
	Gotoxy(44 + 20.5 + 4, 16);
	scanf("%s", newMCom.MCom_location);
	Gotoxy(44, 18);
	printf("4.供应企业提供货品：");
	Gotoxy(44 + 20.5 + 4, 18);
	scanf("%s", newMCom.MCom_material);
	Gotoxy(44, 20);
	printf("5.企业供应原料价格：");
	Gotoxy(44 + 20.5 + 4, 20);
	scanf("%s", temp);
	newMCom.MCom_price= atof(temp);
	getTimeNow(newMCom.in_time);
	Gotoxy(44-3, 24);
	printf("确认签约该家原料供应企业? y/n ：  ");
	int r1;
	scanf("%s", temp);
	Gotoxy(44-3, 26);
	if (temp[0] == 'y') {
		r1 = addNewMCom(&allMComslist, newMCom);
		if (r1 == -1) {
			printf("签约企业失败，请检查该企业信息！  ");
			charRotation();
			materialComInterface();
		}
		else {
			printf("签约企业成功，成功添加企业信息！  ");
			charRotation();
			materialComInterface();
		}
	}
	//输入no的情况下
	else if (temp[0] == 'n') {
		printf("正在返回签约面板，请确认后输入！ ");
		charRotation();
		Sleep(5000);
		materialComInterface();
	}
	//误输入除去y和n的其它字符的话
	else {
		printf("您的输入有误，请确认要求后输入！ ");
		charRotation();
		Sleep(5000);
		addMaterialCom();
	}
}

//功能界面2：解除原料供应企业合作关系界面
void deleteMaterialCom() {
	system("cls");
	frameShow();
	char temp[30];
	Gotoxy(44 + 3,8);
	printf("原料供应企业解约面板");
	Gotoxy(43,11);
	printf("请您输入需要解约的企业编号：");
	scanf("%s", temp);
	Gotoxy(43+31.5, 11);
	charRotation();
	int r1 = searchMCom(allMComslist, temp);
	//在这里出现查找失败的情况
	if (r1 < 0) {
		Gotoxy(44, 13);
		printf("查询企业失败，确认后输入  ");
		charRotation();
		deleteMaterialCom();
	}
	else {
		Gotoxy(43, 13);
		printf("请您确认需要解约的企业信息：");
		Gotoxy(44, 15);
		printf("1.原料供应企业编号： %s",allMComslist.list[r1].MCom_id);
		Gotoxy(44, 17);
		printf("2.原料供应企业名称： %s",allMComslist.list[r1].MCom_name);
		Gotoxy(44, 19);
		printf("3.供应企业的所在地： %s",allMComslist.list[r1].MCom_location);
		Gotoxy(44, 21);
		printf("4.原料供应提供货品： %s",allMComslist.list[r1].MCom_material);
		Gotoxy(44, 23);
		printf("5.原料供应企业价格： %.2f",allMComslist.list[r1].MCom_price);
		Gotoxy(44, 25);
		printf("6.签订企业合约时间： %s",allMComslist.list[r1].in_time);
		Gotoxy(44-2, 28);
		printf("确认解除该企业合作关系？ y/n:  ");
		scanf("%s", temp);
		Gotoxy(44 - 2 + 33 , 28);
		charRotation();
		Gotoxy(44 - 2,29);
		if (temp[0] == 'y') {
			int r3 = delMCom(&allMComslist, r1);
			if (r3 == -1){
				printf("解约失败，检验该企业信息失败！");
				Sleep(5000);
				materialComInterface();
			}
			else {
				printf("解约成功，已成功删除该企业信息！");
				Sleep(1000);
				materialComInterface();
			}
				
		}
		//输入no的情况下
		else if (temp[0] == 'n') {
			printf("正在返回管理面板，请确认后输入！ ");
			charRotation();
			Sleep(5000);
			materialComInterface();
		}
		//误输入除去y和n的其它字符的话
		else {
			printf("您的输入有误，请确认要求后输入！ ");
			charRotation();
			Sleep(5000);
			deleteMaterialCom();
		}
	}
}

//功能界面3：修改企业供应原料界面
void modifiMCom() {
	system("cls");
	frameShow();
	Gotoxy(44 + 3, 5);
	printf("原料供应企业修改面板");
	char temp[30];
	Gotoxy(43, 8);
	printf("请您输入需要修改的企业编号：");
	scanf("%s", temp);
	Gotoxy(43 + 31.5, 8);
	charRotation();
	int r1 = searchMCom(allMComslist, temp);
	int r2=0, r3 = 0;
	//在这里出现查找失败的情况
	if (r1 < 0) {
		Gotoxy(44, 10);
		printf("查询企业失败，确认后输入  ");
		charRotation();
		modifiMCom();
	}
	else {
		Gotoxy(43, 10);
		printf("请您确认需要修改的企业信息：");
		Gotoxy(44, 12);
		printf("1.原料供应企业编号： %s", allMComslist.list[r1].MCom_id);
		Gotoxy(44, 14);
		printf("2.原料供应企业名称： %s", allMComslist.list[r1].MCom_name);
		Gotoxy(44, 16);
		printf("3.原料供应的所在地： %s", allMComslist.list[r1].MCom_location);
		Gotoxy(44, 18);
		printf("4.原料供应提供货品： %s", allMComslist.list[r1].MCom_material);
		Gotoxy(44, 20);
		printf("5.原料供应企业价格： %.2f", allMComslist.list[r1].MCom_price);
		Gotoxy(44, 22);
		printf("6.签订企业合约时间： %s", allMComslist.list[r1].in_time);
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
				r3 = modifyMCom(&allMComslist, r1, r2, newContent);
				if (r3 == -1) {
					Gotoxy(44 - 2, 28);
					printf("修改企业信息失败！  ");
					charRotation();
					Sleep(5000);
					materialComInterface();
				}
				else {
					Gotoxy(44 - 2, 28);
					printf("选择修改企业信息成功！ ");
					charRotation();
					Sleep(3000);
					materialComInterface();
				}
				break;
			}
			//输入的编号不在范围内的
			else {
				Gotoxy(44 - 2, 26);
				printf("您输入的选项编号错误！ ");
				charRotation();
				Sleep(5000);
				materialComInterface();
			}
		}
	}

}

//功能界面4：查询供应企业信息界面
void queryMCom() {
	system("cls");
	frameShow();
	Gotoxy(22+1.5,8);
	printf("原料供应企业查询面板");
	Gotoxy(22, 10);
	printf("请您确认查询企业信息的方式：");
	int choice, r2;
	while (1) {
		Gotoxy(22, 12);
		printf("1.原料供应企业编号");
		Gotoxy(22, 14);
		printf("2.原料供应企业名称");
		Gotoxy(22, 16);
		printf("3.原料供应的所在地");
		Gotoxy(22, 18);
		printf("4.企业提供原料名称");
		Gotoxy(22, 20);
		printf("5.显示所有供应企业");
		Gotoxy(22, 22);
		printf("6.返回企业管理面板");
		Gotoxy(22, 25);
		printf("请输入查询方式的编号： ");
		char temp[80];
		scanf("%s", temp);
		Gotoxy(22 + 23 + 2,25);//待定
		charRotation();
		choice = atoi(temp);
		switch (choice) {
			//输入的查询方式为1时，此时查询方式为企业编号
			case 1: {
				char content[50];
				Gotoxy(22, 27);
				printf("请输入需要查询的内容： ");
				scanf("%s", content);
				Gotoxy(22 + 20 + 5 , 27);
				charRotation();
				r2 = searchMCom(allMComslist, content);
				if (r2 < 0) {
					Gotoxy(22+20+10, 27);
					printf("查询内容失败，确认后输入  ");
					charRotation();
					queryMCom();
				}
				else {
					Gotoxy(58 + 22-16, 10);
					printf("1.原料供应企业编号： %s", allMComslist.list[r2].MCom_id);
					Gotoxy(58 + 22 - 16, 12);
					printf("2.原料供应企业名称： %s", allMComslist.list[r2].MCom_name);
					Gotoxy(58 + 22 - 16, 14);
					printf("3.原料供应的所在地： %s", allMComslist.list[r2].MCom_location);
					Gotoxy(58 + 22 - 16, 16);
					printf("4.原料供应提供货品： %s", allMComslist.list[r2].MCom_material);
					Gotoxy(58 + 22 - 16, 18);
					printf("5.原料供应企业价格： %.2f", allMComslist.list[r2].MCom_price);
					Gotoxy(58 + 22 - 16, 20);
					printf("6.签订企业合约时间： %s", allMComslist.list[r2].in_time);
					Gotoxy(58 + 22 - 16, 24);
					printf("查看结果后，请输入y返回上一层： ");
					scanf("%s", temp);
					if (temp[0] == 'y') {
						Gotoxy(58 + 22+16*2+1.5-16+1, 24);
						charRotation();
						Sleep(1000);
						queryMCom();
					}
					else {
						Gotoxy(58 + 22 + 16 * 2 + 1.5 - 16 + 1, 24);
						printf("输入有误，为您返回主面板 ");
						charRotation();
						Sleep(1000);
						materialComInterface();
					}
				}
				break;
			}
			//输入的查询方式为2时，此时查询方式为企业名称
			case 2: {
				char content[50];
				Gotoxy(22, 27);
				printf("请输入需要查询的内容： ");
				scanf("%s", content);
				Gotoxy(22 + 23 + 28 , 27);
				charRotation();
				IntSeqList result;
				intListInit(&result, 5);
				searchMComByOthers(allMComslist, content, choice, &result);
				if (result.length == 0) {
					errorTemplate(48,"没有满足条件的企业信息！");
					queryMCom();
				}
				//假如成功找到有对应的值
				else {
					system("cls");
					frameShow();
					//测试一下
					Gotoxy(6, 4);
					printf("企业编号               企业名称             企业所在地    企业供应原料      供应原料价格           企业签约时间");
					for (int i = 0; i < result.length; i++) {
						Gotoxy(8, 8 + i);
						printf("%s         %s    %s     %s         %.2f           %s", allMComslist.list[result.list[i]].MCom_id, allMComslist.list[result.list[i]].MCom_name, allMComslist.list[result.list[i]].MCom_location, allMComslist.list[result.list[i]].MCom_material, allMComslist.list[result.list[i]].MCom_price, allMComslist.list[result.list[i]].in_time);
					}
					//用于退出的接口
					char yes[3];
					Gotoxy((117 - 16 * 2) / 2, 28);
					printf("查看结果后，请输入y返回上一层： ");
					scanf("%s", yes);
					if (yes[0] == 'y') {
						Gotoxy((117 - 16 * 2) / 2 + 16 * 2 + 2, 28);
						charRotation();
						Sleep(1000);
						queryMCom();
					}
					//输入错误情况下
					else {
						Gotoxy(58 + 22, 28);
						printf("输入有误，为您返回主面板 ");
						charRotation();
						Sleep(1000);
						materialComInterface();
					}
				}
				errorTemplate(48, "没有满足条件的企业信息！");
				materialComInterface();
				break;
			}
			//输入的查询方式为3时，此时查询方式为企业地点
			case 3: {
				char content[50];
				Gotoxy(22, 27);
				printf("请输入需要查询的内容： ");
				scanf("%s", content);
				Gotoxy(22 + 23 + 28-15, 27);
				charRotation();
				IntSeqList result;
				intListInit(&result, 5);
				searchMComByOthers(allMComslist, content, choice, &result);
				if (result.length == 0) {
					errorTemplate(48, "没有满足条件的企业信息！");
					queryMCom();
				}
				//假如成功找到有对应的值
				else {
					system("cls");
					frameShow();
					//测试一下
					Gotoxy(6, 4);
					printf("企业编号               企业名称             企业所在地    企业供应原料      供应原料价格       企业签约时间");
					for (int i = 0; i < result.length; i++) {
						Gotoxy(8 + 0.5, 8 + i * 1.5);
						printf("%s         %s    %s     %s         %.2f           %s", allMComslist.list[result.list[i]].MCom_id, allMComslist.list[result.list[i]].MCom_name, allMComslist.list[result.list[i]].MCom_location, allMComslist.list[result.list[i]].MCom_material, allMComslist.list[result.list[i]].MCom_price, allMComslist.list[result.list[i]].in_time);
					}
					//用于退出的接口
					char yes[3];
					Gotoxy((117 - 16 * 2) / 2, 28);
					printf("查看结果后，请输入y返回上一层： ");
					scanf("%s", yes);
					if (yes[0] == 'y') {
						Gotoxy((117 - 16 * 2) / 2 + 16 * 2 + 2, 28);
						charRotation();
						Sleep(1000);
						queryMCom();
					}
					//输入错误情况下
					else {
						Gotoxy(58 + 22, 28);
						printf("输入有误，为您返回主面板 ");
						charRotation();
						Sleep(1000);
						materialComInterface();
					}
				}
				errorTemplate(48, "没有满足条件的企业信息！");
				materialComInterface();
				break;
			}
			//输入的查询方式为4时，此时查询方式为企业提供原料
			case 4: {
				char content[50];
				Gotoxy(22, 27);
				printf("请输入需要查询的内容： ");
				scanf("%s", content);
				Gotoxy(22 + 23 + 28 - 15, 27);
				charRotation();
				IntSeqList result;
				intListInit(&result, 5);
				searchMComByOthers(allMComslist, content, choice, &result);
				if (result.length == 0) {
					errorTemplate(48, "没有满足条件的企业信息！");
					queryMCom();
				}
				//假如成功找到有对应的值
				else {
					system("cls");
					frameShow();
					//测试一下
					Gotoxy(6, 4);
					printf("企业编号               企业名称             企业所在地    企业供应原料      供应原料价格       企业签约时间");
					for (int i = 0; i < result.length; i++) {
						Gotoxy(8 + 0.5, 8 + i * 1.5);
						printf("%s         %s    %s     %s         %.2f           %s", allMComslist.list[result.list[i]].MCom_id, allMComslist.list[result.list[i]].MCom_name, allMComslist.list[result.list[i]].MCom_location, allMComslist.list[result.list[i]].MCom_material, allMComslist.list[result.list[i]].MCom_price, allMComslist.list[result.list[i]].in_time);
					}
					//用于退出的接口
					char yes[3];
					Gotoxy((117 - 16 * 2) / 2, 28);
					printf("查看结果后，请输入y返回上一层： ");
					scanf("%s", yes);
					if (yes[0] == 'y') {
						Gotoxy((117 - 16 * 2) / 2 + 16 * 2 + 2, 28);
						charRotation();
						Sleep(1000);
						queryMCom();
					}
					//输入错误情况下
					else {
						Gotoxy(58 + 22, 28);
						printf("输入有误，为您返回主面板 ");
						charRotation();
						Sleep(1000);
						materialComInterface();
					}
				}
				errorTemplate(48, "没有满足条件的企业信息！");
				materialComInterface();
				break;
			}
			//输入的查询方式为4时，此时查询方式为显示所有企业
			case 5:{
				if (allMComslist.length == 0) {
					errorTemplate(48, "合作企业信息数据库为空！");
					queryMCom();
				}
				system("cls");
				frameShow();
				//测试一下
				Gotoxy(6, 4);
				printf("企业编号               企业名称             企业所在地    企业供应原料      供应原料价格       企业签约时间");
				for (int i = 0; i < allMComslist.length; i++) {
					Gotoxy(8 + 0.5, 8 + i * 1.5);
					printf("%s         %s    %s     %s         %.2f           %s\n", allMComslist.list[i].MCom_id, allMComslist.list[i].MCom_name, allMComslist.list[i].MCom_location, allMComslist.list[i].MCom_material, allMComslist.list[i].MCom_price, allMComslist.list[i].in_time);
				}
				//用于退出的接口
				char yes[3];
				Gotoxy((117 - 16 * 2) / 2, 28);
				printf("查看结果后，请输入y返回上一层： ");
				scanf("%s", yes);
				if (yes[0] == 'y') {
					Gotoxy((117 - 16 * 2) / 2 + 16 * 2 + 2, 28);
					charRotation();
					Sleep(1000);
					queryMCom();
				}
				//输入错误情况下
				else {
					Gotoxy(58 + 22, 28);
					printf("输入有误，为您返回主面板 ");
					charRotation();
					Sleep(1000);
					materialComInterface();
				}
			}
		    //输入的查询方式为6时，此时退出查询企业面板
			case 6: {
				errorTemplate(48.5, "正在返回企业管理面板！");
				materialComInterface();
			}
			//errorTemplate(48, "没有满足条件的企业信息！");
			//materialComInterface();
			//break;
			//输入的查询方式不在查询方式的范围内时（1~6）
			//当输入的查询方式不在范围内的时候，会执行defult
			default: {
				errorTemplate(48, "输入的查询方式编号有误！");
				queryMCom();
			}
			}
	}
}

//功能界面5：保存供应企业信息界面
void saveMCom() {
	int r1 = allSave(1);
	if (r1 == -1 ) {
		errorTemplate(48, "保存当前的企业信息失败！");
		materialComInterface();
	}
	else {
		errorTemplate(48, "正在保存所有的企业信息！");
		errorTemplate(48, "保存所有的企业信息成功！");
		materialComInterface();
	}
}

//功能界面6：产品采购企业签订界面
void addProductCom() {
	system("cls");
	frameShow();
	char temp[80];//作为价格的交换值
	PComInfo newPCom;
	Gotoxy(44 + 5, 9.5);
	printf("产品采购企业签约面板");
	Gotoxy(44, 12);
	printf("1.产品采购企业编号：");
	Gotoxy(44 + 20.5 + 4, 12);
	scanf("%s", newPCom.PCom_id);
	Gotoxy(44, 14);
	printf("2.产品采购企业名称：");
	Gotoxy(44 + 20.5 + 4, 14);
	scanf("%s", newPCom.PCom_name);
	Gotoxy(44, 16);
	printf("3.采购企业的所在地：");
	Gotoxy(44 + 20.5 + 4, 16);
	scanf("%s", newPCom.PCom_location);
	Gotoxy(44, 18);
	printf("4.采购企业订购产品：");
	Gotoxy(44 + 20.5 + 4, 18);
	scanf("%s", newPCom.PCom_material);
	Gotoxy(44, 20);
	printf("5.采购企业订购价格：");
	Gotoxy(44 + 20.5 + 4, 20);
	scanf("%s", temp);
	newPCom.PCom_price = atof(temp);
	getTimeNow(newPCom.in_time);
	Gotoxy(44 - 3, 24);
	printf("确认签约该家产品采购企业? y/n ：  ");
	int r1;
	scanf("%s", temp);
	Gotoxy(44 - 3, 26);
	if (temp[0] == 'y') {
		r1 = addNewPCom(&allPComslist, newPCom);
		if (r1 == -1) {
			printf("签约企业失败，请检查该企业信息！  ");
			charRotation();
			productComInterface();
		}
		else {
			printf("签约企业成功，成功添加企业信息！  ");
			charRotation();
			productComInterface();
		}
	}
	//输入no的情况下
	else if (temp[0] == 'n') {
		printf("正在返回签约面板，请确认后输入！ ");
		charRotation();
		Sleep(5000);
		productComInterface();
	}
	//误输入除去y和n的其它字符的话
	else {
		printf("您的输入有误，请确认要求后输入！ ");
		charRotation();
		Sleep(5000);
		addProductCom();
	}
}

//功能界面7：解除产品采购企业合作关系界面
void deleteProductCom() {
	system("cls");
	frameShow();
	char temp[30];
	Gotoxy(44 + 3, 8);
	printf("产品采购企业解约面板");
	Gotoxy(43, 11);
	printf("请您输入需要解约的企业编号：");
	scanf("%s", temp);
	Gotoxy(43 + 31.5, 11);
	charRotation();
	int r1 = searchPCom(allPComslist, temp);
	//在这里出现查找失败的情况
	if (r1 < 0) {
		Gotoxy(44, 13);
		printf("查询企业失败，确认后输入  ");
		charRotation();
		deleteProductCom();
	}
	else {
		Gotoxy(43, 13);
		printf("请您确认需要解约的企业信息：");
		Gotoxy(44, 15);
		printf("1.产品采购企业编号： %s", allPComslist.list[r1].PCom_id);
		Gotoxy(44, 17);
		printf("2.产品采购企业名称： %s", allPComslist.list[r1].PCom_name);
		Gotoxy(44, 19);
		printf("3.采购企业的所在地： %s", allPComslist.list[r1].PCom_location);
		Gotoxy(44, 21);
		printf("4.采购企业订购产品： %s", allPComslist.list[r1].PCom_material);
		Gotoxy(44, 23);
		printf("5.采购企业订购价格： %.2f", allPComslist.list[r1].PCom_price);
		Gotoxy(44, 25);
		printf("6.签订企业合约时间： %s", allPComslist.list[r1].in_time);
		Gotoxy(44 - 2, 28);
		printf("确认解除该企业合作关系？ y/n:  ");
		scanf("%s", temp);
		Gotoxy(44 - 2 + 33, 28);
		charRotation();
		Gotoxy(44 - 2, 29);
		if (temp[0] == 'y') {
			int r3 = delPCom(&allPComslist, r1);
			if (r3 == -1) {
				printf("解约失败，检验该企业信息失败！");
				Sleep(5000);
				productComInterface();
			}
			else {
				printf("解约成功，已成功删除该企业信息！");
				Sleep(1000);
				productComInterface();
			}
		}
		//输入no的情况下
		else if (temp[0] == 'n') {
			printf("正在返回管理面板，请确认后输入！ ");
			charRotation();
			Sleep(5000);
			productComInterface();
		}
		//误输入除去y和n的其它字符的话
		else {
			printf("您的输入有误，请确认要求后输入！ ");
			charRotation();
			Sleep(5000);
			deleteProductCom();
		}
	}
}

//功能界面8：修改企业供应原料界面
void modifiPCom() {
	system("cls");
	frameShow();
	Gotoxy(44 + 3, 5);
	printf("产品采购企业修改面板");
	char temp[30];
	Gotoxy(43, 8);
	printf("请您输入需要修改的企业编号：");
	scanf("%s", temp);
	Gotoxy(43 + 31.5, 8);
	charRotation();
	int r1 = searchPCom(allPComslist, temp);
	int r2 = 0, r3 = 0;
	//在这里出现查找失败的情况
	if (r1 < 0) {
		Gotoxy(44, 10);
		printf("查询企业失败，确认后输入  ");
		charRotation();
		modifiPCom();
	}
	else {
		Gotoxy(43, 10);
		printf("请您确认需要修改的企业信息：");
		Gotoxy(44, 12);
		printf("1.产品采购企业编号： %s", allPComslist.list[r1].PCom_id);
		Gotoxy(44, 14);
		printf("2.产品采购企业名称： %s", allPComslist.list[r1].PCom_name);
		Gotoxy(44, 16);
		printf("3.采购企业的所在地： %s", allPComslist.list[r1].PCom_location);
		Gotoxy(44, 18);
		printf("4.采购企业订购产品： %s", allPComslist.list[r1].PCom_material);
		Gotoxy(44, 20);
		printf("5.采购企业订购价格： %.2f", allPComslist.list[r1].PCom_price);
		Gotoxy(44, 22);
		printf("6.签订企业合约时间： %s", allPComslist.list[r1].in_time);
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
				r3 = modifyPCom(&allPComslist, r1, r2, newContent);
				if (r3 == -1) {
					Gotoxy(44 - 2, 28);
					printf("修改企业信息失败！  ");
					charRotation();
					Sleep(5000);
					productComInterface();
				}
				else {
					Gotoxy(44 - 2, 28);
					printf("选择修改企业信息成功！ ");
					charRotation();
					Sleep(3000);
					productComInterface();
				}
				break;
			}
			//输入的编号不在范围内的
			else {
				Gotoxy(44 - 2, 26);
				printf("您输入的选项编号错误！ ");
				charRotation();
				Sleep(5000);
				productComInterface();
			}
		}
	}
}

//功能界面9：查询采购企业信息界面
void queryPCom() {
	system("cls");
	frameShow();
	Gotoxy(22 + 1.5, 8);
	printf("产品采购企业查询面板");
	Gotoxy(22, 10);
	printf("请您确认查询企业信息的方式：");
	int choice, r2;
	while (1) {
		Gotoxy(22, 12);
		printf("1.产品采购企业编号");
		Gotoxy(22, 14);
		printf("2.产品采购企业名称");
		Gotoxy(22, 16);
		printf("3.采购企业的所在地");
		Gotoxy(22, 18);
		printf("4.采购企业订购产品");
		Gotoxy(22, 20);
		printf("5.显示所有采购企业");
		Gotoxy(22, 22);
		printf("6.返回企业管理面板");
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
				r2 = searchPCom(allPComslist, content);
				if (r2 < 0) {
					Gotoxy(22 + 20 + 10, 27);
					printf("查询内容失败，确认后输入  ");
					charRotation();
					queryPCom();
				}
				else {
					Gotoxy(58 + 22 - 16, 10);
					printf("1.产品采购企业编号： %s", allPComslist.list[r2].PCom_id);
					Gotoxy(58 + 22 - 16, 12);
					printf("2.产品采购企业名称： %s", allPComslist.list[r2].PCom_name);
					Gotoxy(58 + 22 - 16, 14);
					printf("3.采购企业的所在地： %s", allPComslist.list[r2].PCom_location);
					Gotoxy(58 + 22 - 16, 16);
					printf("4.采购企业订购产品： %s", allPComslist.list[r2].PCom_material);
					Gotoxy(58 + 22 - 16, 18);
					printf("5.采购产品企业价格： %.2f", allPComslist.list[r2].PCom_price);
					Gotoxy(58 + 22 - 16, 20);
					printf("6.签订企业合约时间： %s", allPComslist.list[r2].in_time);
					Gotoxy(58 + 22 - 16, 24);
					printf("查看结果后，请输入y返回上一层： ");
					scanf("%s", temp);
					if (temp[0] == 'y') {
						Gotoxy(58 + 22 + 16 * 2 + 1.5 - 16 + 1, 24);
						charRotation();
						Sleep(1000);
						queryPCom();
					}
					else {
						Gotoxy(58 + 22 + 16 * 2 + 1.5 - 16 + 1, 24);
						printf("输入有误，为您返回主面板 ");
						charRotation();
						Sleep(1000);
						productComInterface();
					}
				}
				break;
			}
			//输入的查询方式为2时，此时查询方式为企业名称
			case 2: {
				char content[50];
				Gotoxy(22, 27);
				printf("请输入需要查询的内容： ");
				scanf("%s", content);
				Gotoxy(22 + 23 + 28, 27);
				charRotation();
				IntSeqList result;
				intListInit(&result, 5);
				searchPComByOthers(allPComslist, content, choice, &result);
				if (result.length == 0) {
					errorTemplate(48, "没有满足条件的企业信息！");
					queryPCom();
				}
				//假如成功找到有对应的值
				else {
					system("cls");
					frameShow();
					Gotoxy(6, 4);
					printf("企业编号               企业名称             企业所在地    企业采购产品      采购产品价格       企业签约时间");
					for (int i = 0; i < result.length; i++) {
						Gotoxy(8, 8 + i);
						printf("%s         %s    %s     %s         %.2f           %s", allPComslist.list[result.list[i]].PCom_id, allPComslist.list[result.list[i]].PCom_name, allPComslist.list[result.list[i]].PCom_location, allPComslist.list[result.list[i]].PCom_material, allPComslist.list[result.list[i]].PCom_price, allPComslist.list[result.list[i]].in_time);
					}
					//用于退出的接口
					char yes[3];
					Gotoxy((117 - 16 * 2) / 2, 28);
					printf("查看结果后，请输入y返回上一层： ");
					scanf("%s", yes);
					if (yes[0] == 'y') {
						Gotoxy((117 - 16 * 2) / 2 + 16 * 2 + 2, 28);
						charRotation();
						Sleep(1000);
						queryPCom();
					}
					//输入错误情况下
					else {
						Gotoxy(58 + 22, 28);
						printf("输入有误，为您返回主面板 ");
						charRotation();
						Sleep(1000);
						productComInterface();
					}
				}
				errorTemplate(48, "没有满足条件的企业信息！");
				productComInterface();
				break;
			}
			//输入的查询方式为3时，此时查询方式为企业地点
			case 3: {
				char content[50];
				Gotoxy(22, 27);
				printf("请输入需要查询的内容： ");
				scanf("%s", content);
				Gotoxy(22 + 23 + 28 - 15, 27);
				charRotation();
				IntSeqList result;
				intListInit(&result, 5);
				searchPComByOthers(allPComslist, content, choice, &result);
				if (result.length == 0) {
					errorTemplate(48, "没有满足条件的企业信息！");
					queryPCom();
				}
				//假如成功找到有对应的值
				else {
					system("cls");
					frameShow();
					Gotoxy(6, 4);
					printf("企业编号               企业名称             企业所在地    企业采购产品      采购产品价格       企业签约时间");
					for (int i = 0; i < result.length; i++) {
						Gotoxy(8 + 0.5, 8 + i * 1.5);
						printf("%s         %s    %s     %s         %.2f           %s", allPComslist.list[result.list[i]].PCom_id, allPComslist.list[result.list[i]].PCom_name, allPComslist.list[result.list[i]].PCom_location, allPComslist.list[result.list[i]].PCom_material, allPComslist.list[result.list[i]].PCom_price, allPComslist.list[result.list[i]].in_time);
					}
					//用于退出的接口
					char yes[3];
					Gotoxy((117 - 16 * 2) / 2, 28);
					printf("查看结果后，请输入y返回上一层： ");
					scanf("%s", yes);
					if (yes[0] == 'y') {
						Gotoxy((117 - 16 * 2) / 2 + 16 * 2 + 2, 28);
						charRotation();
						Sleep(1000);
						queryPCom();
					}
					//输入错误情况下
					else {
						Gotoxy(58 + 22, 28);
						printf("输入有误，为您返回主面板 ");
						charRotation();
						Sleep(1000);
						productComInterface();
					}
				}
				errorTemplate(48, "没有满足条件的企业信息！");
				productComInterface();
				break;
			}
			//输入的查询方式为4时，此时查询方式为企业提供原料
			case 4: {
				char content[50];
				Gotoxy(22, 27);
				printf("请输入需要查询的内容： ");
				scanf("%s", content);
				Gotoxy(22 + 23 + 28 - 15, 27);
				charRotation();
				IntSeqList result;
				intListInit(&result, 5);
				searchMComByOthers(allMComslist, content, choice, &result);
				if (result.length == 0) {
					errorTemplate(48, "没有满足条件的企业信息！");
					queryPCom();
				}
				//假如成功找到有对应的值
				else {
					system("cls");
					frameShow();
					Gotoxy(6, 4);
					printf("企业编号               企业名称             企业所在地    企业采购产品      采购产品价格       企业签约时间");
					for (int i = 0; i < result.length; i++) {
						Gotoxy(8 + 0.5, 8 + i * 1.5);
						printf("%s         %s    %s     %s         %.2f           %s", allPComslist.list[result.list[i]].PCom_id, allPComslist.list[result.list[i]].PCom_name, allPComslist.list[result.list[i]].PCom_location, allPComslist.list[result.list[i]].PCom_material, allPComslist.list[result.list[i]].PCom_price, allPComslist.list[result.list[i]].in_time);
					}
					//用于退出的接口
					char yes[3];
					Gotoxy((117 - 16 * 2) / 2, 28);
					printf("查看结果后，请输入y返回上一层： ");
					scanf("%s", yes);
					if (yes[0] == 'y') {
						Gotoxy((117 - 16 * 2) / 2 + 16 * 2 + 2, 28);
						charRotation();
						Sleep(1000);
						queryPCom();
					}
					//输入错误情况下
					else {
						Gotoxy(58 + 22, 28);
						printf("输入有误，为您返回主面板 ");
						charRotation();
						Sleep(1000);
						productComInterface();
					}
				}
				errorTemplate(48, "没有满足条件的企业信息！");
				productComInterface();
				break;
			}
			//输入的查询方式为5时，此时查询方式为显示所有企业
			case 5: {
				if (allPComslist.length == 0) {
					errorTemplate(48, "合作企业信息数据库为空！");
					queryPCom();
				}
				system("cls");
				frameShow();
				Gotoxy(6, 4);
				printf("企业编号               企业名称             企业所在地    企业采购产品      采购产品价格       企业签约时间");
				for (int i = 0; i < allPComslist.length; i++) {
					Gotoxy(8 + 0.5, 8 + i * 1.5);
					printf("%s         %s    %s     %s         %.2f           %s", allPComslist.list[i].PCom_id, allPComslist.list[i].PCom_name, allPComslist.list[i].PCom_location, allPComslist.list[i].PCom_material, allPComslist.list[i].PCom_price, allPComslist.list[i].in_time);
				}
				//用于退出的接口
				char yes[3];
				Gotoxy((117 - 16 * 2) / 2, 28);
				printf("查看结果后，请输入y返回上一层： ");
				scanf("%s", yes);
				if (yes[0] == 'y') {
					Gotoxy((117 - 16 * 2) / 2 + 16 * 2 + 2, 28);
					charRotation();
					Sleep(1000);
					queryPCom();
				}
				//输入错误情况下
				else {
					Gotoxy(58 + 22, 28);
					printf("输入有误，为您返回主面板 ");
					charRotation();
					Sleep(1000);
					productComInterface();
				}
			}
			//输入的查询方式为6时，此时退出查询企业面板
			case 6: {
				errorTemplate(48.5, "正在返回企业管理面板！");
				productComInterface();
			}
		    //errorTemplate(48, "没有满足条件的企业信息！");
			//productComInterface();
			//break;
		    //当输入的查询方式不在范围内的时候，会执行defult
			default: {
				errorTemplate(48, "输入的查询方式编号有误！");
				queryPCom();
			}
		}
	}
}

//功能界面10：保存采购企业信息界面
void savePCom() {
	int r1 = allSave(2);
	if (r1 == -1) {
		errorTemplate(48, "保存当前的企业信息失败！");
		productComInterface();
	}
	else {
		errorTemplate(48, "正在保存所有的企业信息！");
		errorTemplate(48, "保存所有的企业信息成功！");
		productComInterface();
	}
}

//配合功能界面1：功能函数--增加原材料供应企业
int addNewMCom(MComsSeqList* mcsl, MComInfo newMCom) {

	//首先在原料供应企业表中查找是否有此企业，如果有，返回 - 1，表示签约失败
	int r = searchMCom(*mcsl, newMCom.MCom_id);
	if (r >= 0) {
		errorTemplate(48, "此原料供应企业编号存在！");
		materialComInterface();
	}
	//如果有序表空间不够，则扩充空间
	if (mcsl->length >= mcsl->size) {
		MComInfo* t = mcsl->list;
		mcsl->list = (MComInfo*)malloc(2 * mcsl->size * sizeof(MComInfo));
		if (mcsl->list == NULL) {
			errorTemplate(48, "保存无效，内存分配失败！");
			materialComInterface();
		}
		mcsl->size = 2 * mcsl->size;
		for (int i = 0; i < mcsl->length; i++)
			MComCopy(&(mcsl->list[i]), t[i]);
		free(t);
	}
	//	较原料供应合作企业序号插入到合适的位置，保证据原料供应企业编号有序
	int i = 0;
	for (i = mcsl->length - 1; i >= 0; i--) {
		r = strcmp(mcsl->list[i].MCom_id, newMCom.MCom_id);
		if (r > 0)
			MComCopy(&(mcsl->list[i + 1]), mcsl->list[i]);
		else
			break;

	}
	MComCopy(&(mcsl->list[i + 1]), newMCom);
	mcsl->length++;
	//添加成功返回0
	return 0;

}

//配合功能界面1：功能函数--增加新产品采购企业
int addNewPCom(PComsSeqList* pcsl, PComInfo newPCom) {

	//首先在产品采购企业表中查找是否有此企业，如果有，返回 - 1，表示签约失败
	int r = searchPCom(*pcsl, newPCom.PCom_id);
	if (r >= 0) {
		errorTemplate(48, "此产品采购企业编号存在！");
		productComInterface();
	}
	//如果有序表空间不够，则扩充空间
	if (pcsl->length >= pcsl->size) {
		PComInfo* t = pcsl->list;
		pcsl->list = (PComInfo*)malloc(2 * pcsl->size * sizeof(PComInfo));
		if (pcsl->list == NULL) {
			errorTemplate(48, "保存无效，内存分配失败！");
			productComInterface();
		}
		pcsl->size = 2 * pcsl->size;
		for (int i = 0; i < pcsl->length; i++)
			PComCopy(&(pcsl->list[i]), t[i]);
		free(t);
	}
	//	较原料供应合作企业序号插入到合适的位置，保证据原料供应企业编号有序
	int i = 0;
	for (i = pcsl->length - 1; i >= 0; i--) {
		r = strcmp(pcsl->list[i].PCom_id, newPCom.PCom_id);
		if (r > 0)
			PComCopy(&(pcsl->list[i + 1]), pcsl->list[i]);
		else
			break;

	}
	PComCopy(&(pcsl->list[i + 1]), newPCom);
	pcsl->length++;
	//添加成功返回0
	return 0;
}

//配合功能界面123：功能函数--在原料供应企业表中根据签约企业编号进行查找，没有此企业则返回-1；如果有返回值则是该原料供应企业的编号（查找算法用二分查找法）
int searchMCom(MComsSeqList mcsl, char* MCsn) {		//(采用的是 二分查找法)
	int low = 0;
	int high = mcsl.length - 1;
	int mid;
	while (low <= high) {
		mid = (low + high) / 2;		//二分查找法
		if (strcmp(mcsl.list[mid].MCom_id, MCsn) == 0)
			return mid;
		else
			if (strcmp(mcsl.list[mid].MCom_id, MCsn) < 0)
				low = mid + 1;
			else
				high = mid - 1;
	}
	return -1;
}

//配合功能界面123：功能函数--在产品采购企业表中根据签约企业编号进行查找，没有此企业则返回-1；如果有返回值则是该产品采购企业的编号（查找算法用插值查找法）
int searchMComByInterpolationSearch(MComsSeqList mcsl, char* MCsn) {
	int low, high, mid;
	low = 0;
	high = mcsl.length - 1;
	int key = atoi(MCsn);
	while (low <= high) {
		int MComHigh = atoi(mcsl.list[high].MCom_id);
		int MComLow = atoi(mcsl.list[low].MCom_id);
		mid = low + (high - low)*(key - MComLow) / (MComHigh - MComLow);  //插值查找法
		if (strcmp(mcsl.list[mid].MCom_id, MCsn) == 0) return mid;
		else
			if (strcmp(mcsl.list[mid].MCom_id, MCsn) < 0) low = mid + 1;
			else high = mid - 1;
	}
	return -1;
}

/*
//配合功能界面123：功能函数--在原料供应企业表中根据签约企业编号进行查找，没有此企业则返回-1；如果有返回值则是该原料供应企业的编号
int searchMComByFibonacciSearch(MComsSeqList mcsl, char* MCsn) {//()
//无法使用的斐波那契查找	
}
*/

//配合功能界面123：功能函数--在产品采购企业表中根据签约企业编号进行查找，没有此企业则返回-1；如果有返回值则是该产品采购企业的编号（查找算法用二分查找法）
int searchPCom(PComsSeqList pcsl, char* PCsn) {		
	int low = 0;
	int high = pcsl.length - 1;
	int mid;
	while (low <= high) {
		mid = (low + high) / 2;		//二分查找法
		if (strcmp(pcsl.list[mid].PCom_id, PCsn) == 0)
			return mid;
		else
			if (strcmp(pcsl.list[mid].PCom_id, PCsn) < 0)
				low = mid + 1;
			else
				high = mid - 1;
	}
	return -1;
}

//配合功能界面123：功能函数--在产品采购企业表中根据签约企业编号进行查找，没有此企业则返回-1；如果有返回值则是该产品采购企业的编号（查找算法用插值查找法）
int searchPComByInterpolationSearch(PComsSeqList pcsl, char* PCsn) {		
	int low, high, mid;
	low = 0;
	high = pcsl.length - 1;
	int key = atoi(PCsn);
	while (low <= high) {
		int PComHigh = atoi(pcsl.list[high].PCom_id);
		int PComLow = atoi(pcsl.list[low].PCom_id);
		mid = low + (high - low)*(key - PComLow) / (PComHigh - PComLow);  //插值查找法
		if (strcmp(pcsl.list[mid].PCom_id, PCsn) == 0) return mid;
		else
			if (strcmp(pcsl.list[mid].PCom_id, PCsn) < 0) low = mid + 1;
			else high = mid - 1;
	}
	return -1;
}

//配合功能界面123：功能函数--深度拷贝新增原料供应企业
void MComCopy(MComInfo* to, MComInfo from) {
	strcpy(to->MCom_id, from.MCom_id);
	strcpy(to->MCom_name, from.MCom_name);
	strcpy(to->MCom_location, from.MCom_location);
	strcpy(to->MCom_material, from.MCom_material);
	to->MCom_price = from.MCom_price;
	strcpy(to->in_time, from.in_time);
}

//配合功能界面123：功能函数--深度拷贝新增产品采购企业
void PComCopy(PComInfo* to, PComInfo from) {
	strcpy(to->PCom_id, from.PCom_id);
	strcpy(to->PCom_name, from.PCom_name);
	strcpy(to->PCom_location, from.PCom_location);
	strcpy(to->PCom_material, from.PCom_material);
	to->PCom_price = from.PCom_price;
	strcpy(to->in_time, from.in_time);
}

//配合功能界面2：功能函数--在原料供应企业表中删除第index个元素，删除算法为把后面的数据元素覆盖前面，返回0表示删除成功
int delMCom(MComsSeqList* mcsl, int index) {
	if (mcsl->length <= 0) {
		errorTemplate(48, "供应企业数据库信息为空！");
		materialComInterface();
		return -1;
	}
	if (index < 0 || index >= mcsl->length) {
		errorTemplate(47, "解除的企业信息超出执行范围！");
		materialComInterface();
		return -1;
	}

	for (int i = index + 1; i < mcsl->length; i++) {
		MComCopy(&(mcsl->list[i - 1]), mcsl->list[i]);
	}
	mcsl->length--;
	return 0;
}

//配合功能界面2：功能函数--在产品采购企业表中删除第index个元素，删除算法为把后面的数据元素覆盖前面，返回0表示删除成功
int delPCom(PComsSeqList* pcsl, int index) {
	if (pcsl->length <= 0) {
		errorTemplate(48, "采购企业数据库信息为空！");
		productComInterface();
		return -1;
	}
	if (index < 0 || index >= pcsl->length) {
		errorTemplate(47, "解除的企业信息超出执行范围！");
		productComInterface();
		return -1;
	}

	for (int i = index + 1; i < pcsl->length; i++) {
		PComCopy(&(pcsl->list[i - 1]), pcsl->list[i]);
	}
	pcsl->length--;
	return 0;
}

//配合功能界面3：功能函数：在原料供应企业表mcsl中修改第index个企业的信息，type表示要修改的类型（取值1（企业编号），2（企业名称），3（企业所在地），4（企业所提供产品）），info表示新的信息值，修改成功返回0，否则返回1
int modifyMCom(MComsSeqList* mcsl, int index, int type, char* info) {
	if (index < 0 && index >= mcsl->length) {
		errorTemplate(47, "解除的企业信息超出执行范围！");
		materialComInterface();
	}
	switch (type) {
		case 1: strcpy(mcsl->list[index].MCom_id, info); break;
		case 2: strcpy(mcsl->list[index].MCom_name, info); break;
		case 3: strcpy(mcsl->list[index].MCom_location, info); break;
		case 4: strcpy(mcsl->list[index].MCom_material, info); break;
		case 5: mcsl->list[index].MCom_price = atof(info); break;
		case 6: strcpy(mcsl->list[index].in_time, info); break;
		default: {
			errorTemplate(48, "修改的企业信息编号有误！");
			materialComInterface();
		}	
	}
	return 0;
}

//配合功能界面3：功能函数：在产品采购企业表mcsl中修改第index个企业的信息，type表示要修改的类型（取值1（企业编号），2（企业名称），3（企业所在地），4（企业所提供产品）），info表示新的信息值，修改成功返回0，否则返回1
int modifyPCom(PComsSeqList* pcsl, int index, int type, char* info) {
	if (index < 0 && index >= pcsl->length) {
		errorTemplate(47, "解除的企业信息超出执行范围！");
		productComInterface();
	}
	switch (type) {
		case 1: strcpy(pcsl->list[index].PCom_id, info); break;
		case 2: strcpy(pcsl->list[index].PCom_name, info); break;
		case 3: strcpy(pcsl->list[index].PCom_location, info); break;
		case 4: strcpy(pcsl->list[index].PCom_material, info); break;
		case 5: pcsl->list[index].PCom_price = atof(info); break;
		case 6: strcpy(pcsl->list[index].in_time, info); break;
		default: {
			errorTemplate(48, "修改的企业信息编号有误！");
			productComInterface();
		}
	}
	return 0;
}

//配合功能界面4：功能函数--根据提供原料的企业信息（tpye取值1（企业名称），2（企业所在地），3（企业提供原料））查询相关记录的企业信息。
//               如果没有找到，则返回 - 1；如果有，查询结果用一个IntSeqList列表返回，列表装的是企业在顺序表中的序号
int searchMComByOthers(MComsSeqList mcsl, char* info, int type, IntSeqList* mcindex) {
	for (int i = 0; i < mcsl.length; i++) {
		switch (type-1) {
			//当输入的选项为2时，type值对应为1，则执行按照原料企业名称查询的手法；
			case 1: if (strcmp(mcsl.list[i].MCom_name, info) == 0)
				addInt(mcindex, i);
				break;
			//当输入的选项为3时，type值对应为2，则执行按照原料企业地点的查询的手法：
			case 2: if (strcmp(mcsl.list[i].MCom_location, info) == 0)
				addInt(mcindex, i);
				break;
			//当输入的选项为4时，type值对应为3，则执行按照原料企业所提供的原料信息的查询手法；
			case 3: if (strcmp(mcsl.list[i].MCom_material, info) == 0)
				addInt(mcindex, i);
				break;
			default: {
				errorTemplate(47.5, "查询企业信息方式编号有误！");
				materialComInterface();
			}
		}
	}
	return 0;
}

//配合功能界面4：功能函数--根据采购产品的企业信息（tpye取值1（企业名称），2（企业所在地），3（企业订购产品））查询相关记录的企业信息。
//               如果没有找到，则返回 - 1；如果有，查询结果用一个IntSeqList列表返回，列表装的是企业在顺序表中的序号
int searchPComByOthers(PComsSeqList pcsl, char* info, int type, IntSeqList* pcindex) {
	for (int i = 0; i < pcsl.length; i++) {
		switch (type - 1) {
			//当输入的选项为2时，type值对应为1，则执行按照采购企业名称查询的手法；
			case 1: if (strcmp(pcsl.list[i].PCom_name, info) == 0)
				addInt(pcindex, i);
				break;
				//当输入的选项为3时，type值对应为2，则执行按照采购企业地点的查询的手法：
			case 2: if (strcmp(pcsl.list[i].PCom_location, info) == 0)
				addInt(pcindex, i);
				break;
				//当输入的选项为4时，type值对应为3，则执行按照采购企业所订购的产品信息的查询手法；
			case 3: if (strcmp(pcsl.list[i].PCom_material, info) == 0)
				addInt(pcindex, i);
				break;
			default: {
				errorTemplate(47.5, "查询企业信息方式编号有误！");
				productComInterface();
			}
		}
	}
	return 0;
}

//配合功能界面5：功能函数--保存在系统中增加删除更改后的信息进入数据库中
int allMComsInfoSaveToFile(MComsSeqList mcsl, char* filename) {
	FILE *fp;
	char strline[80];						   
	if ((fp = fopen(filename, "w")) == NULL) { 
		errorTemplate(48, "供应企业的数据库不存在！");
		materialComInterface();
	}

	for (int i = 0; i < mcsl.length; i++) {
		fputs(mcsl.list[i].MCom_id, fp);
		fputc('\n', fp);
		fputs(mcsl.list[i].MCom_name, fp);
		fputc('\n', fp);
		fputs(mcsl.list[i].MCom_location, fp);
		fputc('\n', fp);
		fputs(mcsl.list[i].MCom_material, fp);
		fputc('\n', fp);
		sprintf(strline, "%.2f", mcsl.list[i].MCom_price);
		fputs(strline, fp);
		fputc('\n', fp);
		fputs(mcsl.list[i].in_time, fp);
		fputc('\n', fp);
	}
	fclose(fp);
	return 0;
}

//配合功能界面5：功能函数--保存在系统中增加删除更改后的信息进入数据库中
int allPComsInfoSaveToFile(PComsSeqList pcsl, char* filename) {
	FILE *fp;
	char strline[80];
	if ((fp = fopen(filename, "w")) == NULL) {
		errorTemplate(48, "采购企业的数据库不存在！");
		productComInterface();
	}
	for (int i = 0; i < pcsl.length; i++) {
		fputs(pcsl.list[i].PCom_id, fp);
		fputc('\n', fp);
		fputs(pcsl.list[i].PCom_name, fp);
		fputc('\n', fp);
		fputs(pcsl.list[i].PCom_location, fp);
		fputc('\n', fp);
		fputs(pcsl.list[i].PCom_material, fp);
		fputc('\n', fp);
		sprintf(strline, "%.2f", pcsl.list[i].PCom_price);
		fputs(strline, fp);
		fputc('\n', fp);
		fputs(pcsl.list[i].in_time, fp);
		fputc('\n', fp);
	}
	fclose(fp);
	return 0;
}

//（通用）配合功能界面5：功能函数--按类型保存各类信息到文件中
int allSave(int type) {
	switch (type) {
		//当type值取1的时候，说明需要保存的企业信息为合作的供应企业的信息
		case 1: {
			int r1 = allMComsInfoSaveToFile(allMComslist, "合作的供应企业信息数据库.txt");  //保存所有的供应企业信息到文件中
			if (r1 == -1) {
				errorTemplate(48, "保存当前的企业信息失败！");
				materialComInterface();
			}
			return 0;
		}
		//当type值取2的时候，说明需要保存的企业信息为合作的采购企业的信息
		case 2: {
			int r1 = allPComsInfoSaveToFile(allPComslist, "合作的采购企业信息数据库.txt");  //保存所有的合作企业信息到文件中
			if (r1 == -1) {
				errorTemplate(48, "保存当前的企业信息失败！");
				productComInterface();
			}
			return 0;
		}
		default: {
			errorTemplate(47, "选项有误，保存失败！");
			adminLeaderInterface();
		}
	}

}

//未测试的冒泡排序算法
void BubbleSortPrice(MComsSeqList *mcsl) {
	int i, j;
	for (i = 1; i < mcsl->length;i++) {
		for (j = mcsl->length - 1; j >= i; j++) {
			if (mcsl->list[j].MCom_price > mcsl->list[j + 1].MCom_price) {
				MySwap(mcsl, j, j + 1);		//交换二者值
			}
		}
	}
}

void MySwap(MComsSeqList* mcsl, int x, int y) {
	char temp= "";
	temp = mcsl->list[x].MCom_id;
	memset(mcsl->list[x].MCom_id, 0, sizeof(mcsl->list[x].MCom_id));
	strcpy(mcsl->list[x].MCom_id, mcsl->list[y].MCom_id);
	memset(mcsl->list[y].MCom_id, 0, sizeof(mcsl->list[y].MCom_id));
	strcpy(mcsl->list[y].MCom_id, temp);
}