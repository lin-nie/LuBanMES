#include<stdio.h>
#include <stdio.h>
#include <windows.h>
#include<process.h>
#include"Globals.h"
#include<string.h>
#include"MES-ProcessDesigner.h"
//#include"GenericData.h"

#define _CRT_SECURE_NO_DEPRECATE；
#define _CRT_SECURE_NO_WARNINGS；
#pragma warning(disable:4996)；

//可以直接将可输出的坐标表示出来，方便输出时候使用
struct coordinate coord[15] = { {9,9},{31,9},{53,9},{75,9} ,{97,9},{97,15},{75,15},{53,15},{31,15},{9,15} ,{9,21},{31,21},{53,21},{75,21} ,{97,21} };

extern DProcessSeqList  allDProcesslist;//有序动态顺序表存储所有的工艺流程信息

/*----------------------工艺流程信息管理数据结构接口----------------------*/
//数据结构操作1：DProcess界面-初始化有序表 dpsl，size表示初始化容量
void DProcessSeqListInit(DProcessSeqList* dpsl, int size);

//数据结构操作2：对其中的链表初始化，链表使用之前要初始化，同时带有头尾指针赋初值
void PMLinkedListInit(PMLinkedList* list);

//数据结构操作3：DProcess数据操作--数据库信息初始化
int allDProcessInfoReadFromFile(DProcessSeqList* dpsl, char* filename);

/*----------------------界面接口集合----------------------*/
//界面1：工艺流程信息管理界面
void DProcessInterface();

/*----------------------工艺流程信息管理数据操作接口----------------------*/
//数据结构功能函数1，对全新的链表进行增加模块，增加链表的模块，也就是增加流程的模块值，PModule为需要增加进去的内容
//可以用于初始化
void addNewPModuleListTill(PMLinkedList* list, char* PModule);

//数据结构功能函数2,对全新的链表进行遍历模块，且不带有id值，遍历我们创建好的流程图的各个模块链表，id为list在表中的位置 
void ScanNewPModuleList(DProcessInfo newProcess);

//数据结构功能函数3,查询流程图中指定的一个环节出来
struct PModuleNode* FindPModuleNode(DProcessSeqList dpsl, int id, char* tarModule);

//数据结构功能函数4，流程图的清空操作，可以将所有流程图的模块置空
void FreePModuleList(DProcessSeqList* dpsl, int id);

//数据结构功能函数5，在指定的模块位置插入模块，可以实现流程图的编辑（链表的增）
void AddPModuleListRand(DProcessSeqList* dpsl, int id, char* tarModule, char* addModule);

//数据结构功能函数6，在指定的模块位置编辑其内容，可以实现流程图的编辑（链表的改）
void modiPModuleListRand(DProcessSeqList* dpsl, int id, char* oldModule, char* newModule);

//数据结构功能函数7，删除模块操作之删除指定模块
void DeletePModuleListRand(DProcessSeqList* dpsl, int id, char* deleModule);

/*----------------------工艺流程信息管理绘图操作接口----------------------*/
//绘图函数，专门用于绘制流程图，其中num值为传入的模块数量
void processFrame(int num);

//绘制函数，专门用于绘制设计边框
void DProcessFrame();

/*----------------------管理界面接口集合----------------------*/
//功能界面1：工艺流程设计添加界面
void addDProcess();

//功能界面2：查询工艺流程的界面
void checkDProcess();

//功能界面3：工艺流程删除界面
void deleteDProcess();

//功能界面4：修改工艺流程信息
void modifiDProcess();

//功能界面5：编辑工艺流程模块界面
void  modifiDProcessModule();

//功能界面6：保存工艺流程信息界面
void saveDProcess();

//配合功能界面1：功能函数--往链表里面新增全新的一个newDProcess
int addNewDProcess(DProcessSeqList* dpsl, DProcessInfo newDProcess);

//配合功能界面123：功能函数--在工艺流程登记表中根据登记流程编号进行查找，没有该编号所占用库存则返回-1；如果有返回值则是该登记编号已被占用（查找算法用二分查找法）
int searchDProcess(DProcessSeqList dpsl, char* DPsn);

//配合功能界面123：功能函数--深度拷贝新增的工艺流程图纸信息,其中num的作用是设置的模块数
void DProcessCopy(DProcessInfo* to, DProcessInfo from, int num);

//配合功能界面2：功能函数--在工艺流程管理表中删除第index个元素，删除算法为把后面的数据元素覆盖前面，返回0表示删除成功
int delDProcess(DProcessSeqList* dpsl, int index);

//配合功能界面3：功能函数：在工艺流程管理表dpsl中修改第index个流程批次的信息，type表示要修改的类型（取值1（工艺流程登记编号），2（工艺流程登记名称），3（工艺生产方式备注），4（工艺流程模块数量）,5（工艺流程登记时间）），info表示新的信息值，修改成功返回0，否则返回1
int modifyDProcess(DProcessSeqList* dpsl, int index, int type, char* info);

//配合功能界面5：功能函数--保存在系统中增加删除更改后的信息进入数据库中
int allDProcessInfoSaveToFile(DProcessSeqList dpsl, char* filename);

//配合功能界面5：功能函数--按类型保存仓储信息到文件中
int allSaveDProcess();

//特殊接口函数：管理员专用于查询仓储库存原料信息界面
void checkDProcessAdmin();


/*----------------------工艺流程信息管理数据结构接口----------------------*/
//数据结构操作1：DProcess界面-初始化有序表 dpsl，size表示初始化容量
void DProcessSeqListInit(DProcessSeqList* dpsl, int size) {
	dpsl->list = (DProcessInfo*)malloc(size * sizeof(DProcessInfo));
	dpsl->size = size;
	dpsl->length = 0;
}

//数据结构操作2：对其中的链表初始化，链表使用之前要初始化，同时带有头尾指针赋初值
void PMLinkedListInit(PMLinkedList* list) {
	list->head = (PModuleNode*)malloc(sizeof(PModuleNode));
	list->rear = (PModuleNode*)malloc(sizeof(PModuleNode));
	list->head->next = list->rear;
	strcpy(list->head->PModule, "工艺流程开始");
	strcpy(list->rear->PModule, "工艺流程结束");
	list->rear->next = NULL;
	list->count = 0;
}

//数据结构操作3：DProcess数据操作--数据库信息初始化
int allDProcessInfoReadFromFile(DProcessSeqList* dpsl, char* filename) {
	FILE *fp;
	char strline[80];						   //每行最大读取的字符数
	if ((fp = fopen(filename, "r")) == NULL) { //判断文件是否存在及可读
		errorTemplate(48, "加载 MES数据库信息出错！");
		return -1;
	}
	DProcessInfo newDProcess;
	PMLinkedListInit(&newDProcess.processList);//千万不要忘记了初始化！！！这里出错了好多次了
	while (!feof(fp)) {
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newDProcess.DProcess_id, strline);
		else {
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newDProcess.DProcess_name, strline);
		else {
			errorTemplate(48, "加载 MES数据库信息出错！");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newDProcess.DProcess_method, strline);
		else {
			errorTemplate(48, "加载 MES数据库信息出错！");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0) {
			newDProcess.DProcess_num = atof(strline);
		}
		else {
			errorTemplate(48, "加载 MES数据库信息出错！");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0) {
			strcpy(newDProcess.in_time, strline);
		}
		else {
			errorTemplate(48, "加载 MES数据库信息出错！");
			fclose(fp);
			return -1;
		}
		for (int i = 0; i < newDProcess.DProcess_num+2; i++) {
			if (fscanf(fp, "%s", strline) > 0) {
				if(!(strcmp(strline, "工艺流程开始") == 0 || strcmp(strline, "工艺流程结束") == 0))
				addNewPModuleListTill(&newDProcess.processList, &strline);
			}
			else {
				fclose(fp);
				return -1;
			}
		}
		addNewDProcess(dpsl, newDProcess);
	}
	fclose(fp);//关闭文件
	return 0;
}

/*----------------------界面接口集合----------------------*/
//界面1：工艺流程信息管理界面
void DProcessInterface() {	//产品图纸管理界面
	int choice;
	system("cls");
	frameShow();
	Gotoxy(44 + 6, 7);
	printf("工艺流程信息管理");
	Gotoxy(44 + 2, 10);		//动态移动光标，同时本页面以坐标（48，10）作为基准移动下面的光标
	printf("1.设 计 添 加 工 艺 流 程");
	Gotoxy(44 + 2, 12);
	printf("2.查 看 工 艺 流 程 信 息");
	Gotoxy(44 + 2, 14);
	printf("3.修 改 工 艺 流 程 信 息");
	Gotoxy(44 + 2, 16);
	printf("4.编 辑 流 程 模 块 信 息");
	Gotoxy(44 + 2, 18);
	printf("5.删 除 工 艺 流 程 信 息");
	Gotoxy(44 + 2, 20);
	printf("6.保 存 工 艺 流 程 信 息");
	Gotoxy(44 + 2, 22);
	printf("7.退 出 工 艺 流 程 管 理");
	Gotoxy(44 + 2, 24);
	printf("请输入您需要操作的编码：");
	Gotoxy(44 + 23 + 3, 24);
	scanf("%d", &choice);
	Gotoxy(44 + 23 + 3+2, 24);
	charRotation();
	switch (choice) {
	case 1: {
		DProcessFrame();
		addDProcess();
	}
	case 2: {
		checkDProcess();
	}
	case 3: {
		modifiDProcess();
	}
	case 4: {
		modifiDProcessModule();
	}
	case 5: {
		deleteDProcess();
	}
	case 6: {
		saveDProcess();
	}
	case 7: {
		errorTemplate(47.5, "正在退出工艺流程设计面板！");
		exitMES(3);
	}
	default: {
		errorTemplate(47.5, "输入编号有误，请重新输入！");
		DProcessInterface();
	}
	}
}


/*----------------------工艺流程信息管理数据操作接口----------------------*/
//数据结构功能函数1，对全新的链表进行增加模块，增加链表的模块，也就是增加流程的模块值，PModule为需要增加进去的内容
//可以用于初始化
void addNewPModuleListTill(PMLinkedList* list,char* PModule)
{
	//创建一个节点
	PModuleNode* temp = (PModuleNode*)malloc(sizeof(PModuleNode)); //此处注意强制类型转换
	//节点数据进行赋值
	strcpy(temp->PModule, PModule);
	//链表指向下一节
	temp->next = NULL;
	//连接分两种情况1.一个节点都没有2.已经有节点了，添加到尾巴上
	//第一种就是头节点都是空的，那就让头节点本身变为temp第一个值strcpy(list->head->PModule,"工艺流程开始");
	if ( list->head->next == list->rear){
		list->head->next = temp;
		temp->next = list->rear;
		//	end=temp;
	}
	//第二种，因为前面已经把 temp的指针域指向了NULL，所以这里只要操作rear
	else{
		//先创建一个节点，保存好尾节点的前一个值
		PModuleNode* before_rear = (PModuleNode*)malloc(sizeof(PModuleNode)); //此处注意强制类型转换
		PModuleNode* p = (PModuleNode*)malloc(sizeof(PModuleNode)); //此处注意强制类型转换
		p = list->head;
		while (!(strcmp(p->PModule, "工艺流程结束") == 0)) {
			before_rear =p;
			p = p->next;
		}
		//newProcess->processList.rear->next = temp;
		before_rear->next = temp;
		temp->next= list->rear;
		//newProcess->processList.rear = temp;
	}
	//尾结点应该始终指向最后一个，此时为temp
}

//数据结构功能函数2,对全新的链表进行遍历模块，且不带有id值，遍历我们创建好的流程图的各个模块链表，id为list在表中的位置 
void ScanNewPModuleList(DProcessInfo newProcess)
{
	PModuleNode *temp = newProcess.processList.head;		//定义一个临时变量来指向头
	//当temp值指向空的时候可以停止，说明流程图已经遍历完毕
	//第一种情况就是说这个链表是空的链表
	if (newProcess.processList.head->next==newProcess.processList.rear){
		errorTemplate(48, "该工艺流程没有模块信息！");
		//在这里返回查询面板吧
	}
	else {
		int i = 0;
		while (temp != NULL)
		{
			Gotoxy(coord[i].x, coord[i].y);
			//打印PModule模块内字符内容
			printf("%s  ", temp->PModule);
			temp = temp->next;		//temp指向下一个的地址 即实现自加操作
			i = i++;
		}
	}
}

//数据结构功能函数3,查询流程图中指定的一个环节出来
struct PModuleNode* FindPModuleNode(DProcessSeqList dpsl, int id,char* tarModule)
{
	PModuleNode *temp = dpsl.list[id].processList.head;
	//先有可能是该节点该流程内不含有任何的模块信息
	if (NULL == dpsl.list[id].processList.head) {
		errorTemplate(48, "该工艺流程没有模块信息！");
		return NULL;
	}
	else {
		while (temp != NULL) {
			//专门使用strcmp函数做流程模块的匹配，查找出该流程图中使用了此模块的
			if (strcmp(temp->PModule, tarModule) == 0) {
				//如果查到指定环节，就返还temp值出来
				return temp;
			}
			//不然就往下继续找
			temp = temp->next;
		}
		//没找到的话，此时该节点承接值为空值
		errorTemplate(46, "该流程中没有满足条件的模块信息！");
		//返回空值时，不需要返回了
		return NULL;
	}
}

//数据结构功能函数4，流程图的清空操作，可以将所有流程图的模块置空
void FreePModuleList(DProcessSeqList* dpsl, int id)
{
	PModuleNode *temp = dpsl->list[id].processList.head;		//定义一个临时变量来指向头
	//先有可能是该节点该流程内不含有任何的模块信息
	if (NULL == dpsl->list[id].processList.head) {
		errorTemplate(48, "该工艺流程没有模块信息！");
		DProcessInterface();
	}
	else{
		while (temp != NULL){
			PModuleNode* pt = temp;
			temp = temp->next;		    //temp指向下一个的地址 即实现链表的模块不断移动操作
			free(pt);					//释放当前
		}
		//头尾清空都要清空好，才算完全删除干净
		dpsl->list[id].processList.head = NULL;
		dpsl->list[id].processList.rear = NULL;
		errorTemplate(46, "清空完成，该流程已没有模块信息！");
	}
}

//数据结构功能函数5，在指定的模块位置插入模块，可以实现流程图的编辑（链表的增）
void AddPModuleListRand(DProcessSeqList* dpsl, int id,char* tarModule, char* addModule)
{
	//说明此时该节点为空
	if ( dpsl->list[id].processList.head->next==dpsl->list[id].processList.rear){
		errorTemplate(48, "该工艺流程没有模块信息！");
		modifiDProcessModule();
	}
	else {
		PModuleNode* pt = FindPModuleNode(allDProcesslist,id,tarModule);
		//如果返回的pt值为空，那证明没有此匹配的流程环节，说明输入的id是错误
		if (NULL == pt) modifiDProcessModule();
		else{
			//有此节点
			//创建临时节点，申请内存
			PModuleNode* temp = (PModuleNode *)malloc(sizeof(PModuleNode));
			//节点成员进行赋值,将我们要加入的模块增加进入临时节点中
			strcpy(temp->PModule, addModule);
			temp->next = NULL;
			//需要将我们要连接的模块增加到工艺流程链表上 
			//增加的情况也分为两种，但因为头尾节点固定，所以只用考虑一种通用情况 
			// 先连后面 （先将要插入的节点指针指向原来找到节点的下一个）
			temp->next = pt->next;
			//后连前面
			pt->next = temp;
		}
		
	}
	
}

//数据结构功能函数6，在指定的模块位置编辑其内容，可以实现流程图的编辑（链表的改）
void modiPModuleListRand(DProcessSeqList* dpsl, int id, char* oldModule, char* newModule) {
	//说明此时该节点为空
	if (dpsl->list[id].processList.head->next == dpsl->list[id].processList.rear) {
		errorTemplate(48, "该工艺流程没有模块信息！");
		modifiDProcessModule();
	}
	else {
		PModuleNode* pt = FindPModuleNode(allDProcesslist, id, oldModule);
		//如果返回的pt值为空，那证明没有此匹配的流程环节，说明输入的id是错误
		if (NULL == pt) modifiDProcessModule();
		else {
			memset(pt->PModule, 0, sizeof(pt->PModule));	//先清空数组再赋值
			strcpy(pt->PModule, newModule);
		}
	}
}

//数据结构功能函数7，删除模块操作之删除指定模块
void DeletePModuleListRand(DProcessSeqList* dpsl, int id,char* deleModule)
{
	//链表检测 .判断是否为空
	if (dpsl->list[id].processList.head->next == dpsl->list[id].processList.rear) {
		errorTemplate(48, "该工艺流程没有模块信息！");
		modifiDProcessModule();
	}
	//链表不为空的话，就去寻找这个需要删除掉的模块
	PModuleNode* temp = FindPModuleNode(allDProcesslist, id, deleModule);
	if (NULL == temp) modifiDProcessModule();
	//找到需要删除的工艺流程图模块时,流程图有多个节点的情况下
	else{
		//删除中间某个节点，找要删除temp前一个，遍历
		PModuleNode* pt = dpsl->list[id].processList.head;
		while (pt->next != temp) {
			pt = pt->next;
		}
		//找到了了该模块以后，就直接让前一个直接连接后一个
		//然后释放掉需要删除的模块即可自动
		pt->next = temp->next;
		free(temp);
		}
	}

/*----------------------工艺流程信息管理绘图操作接口----------------------*/
//绘图函数，专门用于绘制流程图，其中num值为传入的模块数量
void processFrame(int num) {
	if (num <= 5) {
		for (int i = 0; i < num - 1; i++) {
			Gotoxy(7 + i * 22, 8);
			printf("┏━━━━━━━━━━━━━━┓");
			Gotoxy(7 + i * 22, 9);
			printf("┃              ┃");
			Gotoxy(7 + i * 22, 10);
			printf("┗━━━━━━━━━━━━━━┛");
			Gotoxy(23 + 22 * i, 9);
			printf("━━━━━>");
		}
		Gotoxy(7 + (num - 1) * 22, 8);
		printf("┏━━━━━━━━━━━━━━┓");
		Gotoxy(7 + (num - 1) * 22, 9);
		printf("┃              ┃");
		Gotoxy(7 + (num - 1) * 22, 10);
		printf("┗━━━━━━━━━━━━━━┛");
	}
	else {
		Gotoxy(103, 10);
		printf("┓");
		for (int i = 0; i < 4; i++) {
			Gotoxy(103, 11 + i);
			printf("┃");
		}
		Gotoxy(103, 14);
		printf("┛");
		//刚刚好6个模块
		if (num == 6) {
			Gotoxy(7 + (5 - 1) * 22, 14);
			printf("┏━━━━━━━━━━━━━━┓");
			Gotoxy(7 + (5 - 1) * 22, 15);
			printf("┃              ┃");
			Gotoxy(7 + (5 - 1) * 22, 16);
			printf("┗━━━━━━━━━━━━━━┛");
		}
		//大于6个模块，且小于等于10个模块时
		else if (num >= 6 && num <= 10) {
			for (int i = 0; i < 5 - 1; i++) {
				Gotoxy(7 + i * 22, 8);
				printf("┏━━━━━━━━━━━━━━┓");
				Gotoxy(7 + i * 22, 9);
				printf("┃              ┃");
				Gotoxy(7 + i * 22, 10);
				printf("┗━━━━━━━━━━━━━━┛");
				Gotoxy(23 + 22 * i, 9);
				printf("━━━━━>");
			}
			Gotoxy(7 + (5 - 1) * 22, 8);
			printf("┏━━━━━━━━━━━━━━┓");
			Gotoxy(7 + (5 - 1) * 22, 9);
			printf("┃              ┃");
			Gotoxy(7 + (5 - 1) * 22, 10);
			printf("┗━━━━━━━━━━━━━━┛");

			Gotoxy(7 + (5 - 1) * 22, 14);
			printf("┏━━━━━━━━━━━━━━┓");
			Gotoxy(7 + (5 - 1) * 22, 15);
			printf("┃              ┃");
			Gotoxy(7 + (5 - 1) * 22, 16);
			printf("┗━━━━━━━━━━━━━━┛");
			for (int i = 0; i < num - 6; i++) {
				Gotoxy(95 - 6 - (6 + 16)*i, 15);
				printf("<━━━━━");
				Gotoxy(95 - 6 - 16 - (6 + 16)*i, 14);
				printf("┏━━━━━━━━━━━━━━┓");
				Gotoxy(95 - 6 - 16 - (6 + 16)*i, 15);
				printf("┃              ┃");
				Gotoxy(95 - 6 - 16 - (6 + 16)*i, 16);
				printf("┗━━━━━━━━━━━━━━┛");
			}
		}
		//大于10个模块
		else {
			for (int i = 0; i < 5 - 1; i++) {
				Gotoxy(7 + i * 22, 8);
				printf("┏━━━━━━━━━━━━━━┓");
				Gotoxy(7 + i * 22, 9);
				printf("┃              ┃");
				Gotoxy(7 + i * 22, 10);
				printf("┗━━━━━━━━━━━━━━┛");
				Gotoxy(23 + 22 * i, 9);
				printf("━━━━━>");
			}
			Gotoxy(7 + (5 - 1) * 22, 8);
			printf("┏━━━━━━━━━━━━━━┓");
			Gotoxy(7 + (5 - 1) * 22, 9);
			printf("┃              ┃");
			Gotoxy(7 + (5 - 1) * 22, 10);
			printf("┗━━━━━━━━━━━━━━┛");


			Gotoxy(7 + (5 - 1) * 22, 14);
			printf("┏━━━━━━━━━━━━━━┓");
			Gotoxy(7 + (5 - 1) * 22, 15);
			printf("┃              ┃");
			Gotoxy(7 + (5 - 1) * 22, 16);
			printf("┗━━━━━━━━━━━━━━┛");
			for (int i = 0; i < 4; i++) {
				Gotoxy(95 - 6 - (6 + 16)*i, 15);
				printf("<━━━━━");
				Gotoxy(95 - 6 - 16 - (6 + 16)*i, 14);
				printf("┏━━━━━━━━━━━━━━┓");
				Gotoxy(95 - 6 - 16 - (6 + 16)*i, 15);
				printf("┃              ┃");
				Gotoxy(95 - 6 - 16 - (6 + 16)*i, 16);
				printf("┗━━━━━━━━━━━━━━┛");
			}
			Gotoxy(7 + 8, 16);
			printf("┓");
			for (int i = 0; i < 4; i++) {
				Gotoxy(7 + 8, 17 + i);
				printf("┃");
			}
			Gotoxy(7 + 8, 20);
			printf("┛");
			//当子模块数等于11个时
			if (num == 11) {
				Gotoxy(7, 20);
				printf("┏━━━━━━━━━━━━━━┓");
				Gotoxy(7, 21);
				printf("┃              ┃");
				Gotoxy(7, 22);
				printf("┗━━━━━━━━━━━━━━┛");
			}
			//当子模块数大于11个时,且小于15时
			else {

				Gotoxy(7, 20);
				printf("┏━━━━━━━━━━━━━━┓");
				Gotoxy(7, 21);
				printf("┃              ┃");
				Gotoxy(7, 22);
				printf("┗━━━━━━━━━━━━━━┛");
				for (int i = 0; i < num - 11; i++) {
					Gotoxy(23 + 22 * i, 21);
					printf("━━━━━>");
					Gotoxy(7 + (i + 1) * 22, 20);
					printf("┏━━━━━━━━━━━━━━┓");
					Gotoxy(7 + (i + 1) * 22, 21);
					printf("┃              ┃");
					Gotoxy(7 + (i + 1) * 22, 22);
					printf("┗━━━━━━━━━━━━━━┛");

				}
			}
		}

	}
}

//绘制函数，专门用于绘制设计边框
void DProcessFrame() {
	system("cls");
	frameShow();
	Gotoxy(57 + 11, 0);
	printf("┓");
	for (int i = 0; i < 29; i++) {
		Gotoxy(57 + 11, 1 + i);
		printf("┃");
	}
	Gotoxy(57 + 11, 30);
	printf("┗");
	Gotoxy(23, 4);
}

/*----------------------管理界面接口集合----------------------*/
//功能界面1：工艺流程设计添加界面
void addDProcess() {
	char temp[80];//作为价格的交换值
	char module[30];
	DProcessInfo newDProcess;
	PMLinkedListInit(&newDProcess.processList);
	Gotoxy(22+5, 7);
	printf("工艺流程规划设计面板");
	Gotoxy(84, 7);
	printf("工艺流程模块设计面板");
	Gotoxy(22, 11);
	printf("1.工艺流程登记编号：");
	Gotoxy(22 + 20 + 4, 11);
	scanf("%s", newDProcess.DProcess_id);
	Gotoxy(22 + 20 + 4+17, 11);
	charRotation();
	Gotoxy(22, 13);
	printf("2.工艺流程登记名称：");
	Gotoxy(22 + 20 + 4, 13);
	scanf("%s", newDProcess.DProcess_name);
	Gotoxy(22 + 20 + 4 + 17, 13);
	charRotation();
	Gotoxy(22, 15);
	printf("3.工艺生产方式备注：");
	Gotoxy(22 + 20 + 4, 15);
	scanf("%s", newDProcess.DProcess_method);
	Gotoxy(22 + 20 + 4 + 17, 15);
	charRotation();
	Gotoxy(22, 17);
	printf("4.工艺流程模块数量：");
	Gotoxy(22 + 20 + 4, 17);
	scanf("%s", temp);
	Gotoxy(22 + 20 + 4 + 17, 17);
	charRotation();
	newDProcess.DProcess_num = atof(temp);
	getTimeNow(newDProcess.in_time);
	//Gotoxy(80, 11);
	//printf("1.工艺模块1：  ");
	//scanf("%s", test);
	for (int i = 0; i < newDProcess.DProcess_num; i++) {
		Gotoxy(80, 11+i);
		printf("%d.工艺模块%d：  ",i+1,i+1);
		scanf("%s", module);
		Gotoxy(80+18+12+1, 11 + i);
		charRotation();
		addNewPModuleListTill(&newDProcess.processList, &module);
		memset(module, 0, sizeof(module));	//先清空数组再赋值
	}
	Gotoxy(75, 11+ newDProcess.DProcess_num+3);
	printf("确认发布这版工艺设计流程? y/n ：  ");
	int r1;
	scanf("%s", temp);
	Gotoxy(117-4, 11 + newDProcess.DProcess_num + 3);
	charRotation();
	if (temp[0] == 'y') {
		r1 = addNewDProcess(&allDProcesslist, newDProcess);
		if (r1 == -1) {
			errorTemplate(44, "设计流程失败，请检查各模块信息！");
			DProcessInterface();
		}
		else {
			errorTemplate(44, "设计流程成功，成功添加工艺信息！");
			DProcessInterface();
		}
	}
	//输入no的情况下
	else if (temp[0] == 'n') {
		errorTemplate(44, "正在返回工艺面板，请确认后输入！");
		charRotation();
		Sleep(5000);
		DProcessInterface();
	}
	//误输入除去y和n的其它字符的话
	else {
		errorTemplate(44, "您的输入有误，请确认要求后输入！");
		addDProcess();
	}
}

//功能界面2：查询工艺流程的界面
void checkDProcess() {
	system("cls");
	frameShow();
	char temp[30];
	Gotoxy(48, 6);
	printf("已发布工艺流程查看面板");
	Gotoxy(41, 14);
	printf("请您输入需要查询的工艺流程编号：  ");
	scanf("%s", temp);
	Gotoxy(44 + 34, 14);
	charRotation();
	errorTemplate(47, "正在查询相关的流程信息！");
	int r1 = searchDProcess(allDProcesslist, temp);
	//在这里出现查找失败的情况
	if (r1 < 0) {
		errorTemplate(46, "查询失败，没有相关流程信息！");
		errorTemplate(47, "正在退出查询面板，请稍等！");
		DProcessInterface();
	}
	else {
		system("cls");
		frameShow();
		Gotoxy(48, 2);
		printf("已发布工艺流程查看面板");
		Gotoxy(8, 4);
		printf("1.流程登记编号： %s", allDProcesslist.list[r1].DProcess_id);
		Gotoxy(36, 4);
		printf("2.流程名称： %s", allDProcesslist.list[r1].DProcess_name);
		Gotoxy(8, 6);
		printf("3.生产方式： %s", allDProcesslist.list[r1].DProcess_method);
		Gotoxy(36, 6);
		printf("4.模块数量： %d", allDProcesslist.list[r1].DProcess_num);
		Gotoxy(60, 6);
		printf("5.发布时间： %s", allDProcesslist.list[r1].in_time);
		processFrame(allDProcesslist.list[r1].DProcess_num+2);
		ScanNewPModuleList(allDProcesslist.list[r1]);
		Gotoxy(39, 24);
		printf("查看结果后，请输入任意值返回工艺面板： ");
		scanf("%s", temp);
		if (temp[0] == 'y') {
			errorTemplate(48, "正在返回工艺流程面板！");
			DProcessInterface();
		}
		else {
			errorTemplate(48, "正在返回工艺流程面板！");
			DProcessInterface();
		}	
	}
}

//功能界面3：工艺流程删除界面
void deleteDProcess() {
	system("cls");
	frameShow();
	char temp[30];
	Gotoxy(44 + 3, 8);
	printf("工艺流程信息删除面板");
	Gotoxy(43, 11);
	printf("请您输入需要删除的流程编号：");
	scanf("%s", temp);
	Gotoxy(43 + 32, 11);
	charRotation();
	int r1 = searchDProcess(allDProcesslist, temp);
	//在这里出现查找失败的情况
	if (r1 < 0) {
		Gotoxy(44, 13);
		printf("查询流程失败，确认后输入  ");
		charRotation();
		DProcessInterface();
	}
	else {
		Gotoxy(43, 13);
		printf("请您确认需要删除的流程信息：");
		Gotoxy(44, 15);
		printf("1.工艺流程登记编号： %s", allDProcesslist.list[r1].DProcess_id);
		Gotoxy(44, 17);
		printf("2.工艺流程登记名称： %s", allDProcesslist.list[r1].DProcess_name);
		Gotoxy(44, 19);
		printf("3.工艺生产方式备注： %s", allDProcesslist.list[r1].DProcess_method);
		Gotoxy(44, 21);
		printf("4.工艺流程模块数量： %d", allDProcesslist.list[r1].DProcess_num);
		Gotoxy(44, 23);
		printf("5.工艺流程登记时间： %s", allDProcesslist.list[r1].in_time);
		Gotoxy(44 - 2, 28);
		printf("确认将删除该工艺流程吗？ y/n:  ");
		scanf("%s", temp);
		Gotoxy(44 - 2 + 33, 28);
		charRotation();
		Gotoxy(44 - 2, 29);
		if (temp[0] == 'y') {
			int r3 = delDProcess(&allDProcesslist, r1);
			FreePModuleList(&allDProcesslist, r1);
			if (r3 == -1) {
				errorTemplate(47, "删除失败，无法检验信息！");
				Sleep(5000);
				DProcessInterface();
			}
			else {
				errorTemplate(47, "删除成功，系统已无信息！");
				Sleep(1000);
				DProcessInterface();
			}
		}
		//输入no的情况下
		else if (temp[0] == 'n') {
			printf("正在返回工艺面板，请确认后输入！ ");
			charRotation();
			Sleep(3000);
			DProcessInterface();
		}
		//误输入除去y和n的其它字符的话
		else {
			printf("您的输入有误，请确认要求后输入！ ");
			charRotation();
			Sleep(3000);
			deleteDProcess();
		}
	}
}

//功能界面4：修改工艺流程信息
void modifiDProcess() {
	system("cls");
	frameShow();
	Gotoxy(44 + 3, 5);
	printf("工艺流程信息修改面板");
	char temp[30];
	Gotoxy(43, 8);
	printf("请您输入需要修改的流程编号：");
	scanf("%s", temp);
	Gotoxy(43 + 32, 8);
	charRotation();
	int r1 = searchDProcess(allDProcesslist, temp);
	int r2 = 0, r3 = 0;
	//在这里出现查找失败的情况
	if (r1 < 0) {
		Gotoxy(44, 10);
		printf("查询流程失败，确认后输入  ");
		charRotation();
		DProcessInterface();
	}
	else {
		Gotoxy(43, 10);
		printf("请您确认需要修改的流程信息：");
		Gotoxy(44, 12);
		printf("1.工艺流程登记编号： %s", allDProcesslist.list[r1].DProcess_id);
		Gotoxy(44, 14);
		printf("2.工艺流程登记名称： %s", allDProcesslist.list[r1].DProcess_name);
		Gotoxy(44, 16);
		printf("3.工艺生产方式备注： %s", allDProcesslist.list[r1].DProcess_method);
		Gotoxy(44, 18);
		//printf("4.工艺流程模块数量： %d", allDProcesslist.list[r1].DProcess_num);
		//Gotoxy(44, 20);			工艺流程模块数量不能轻易的编辑
		//printf("4.工艺流程登记时间： %.s", allDProcesslist.list[r1].in_time);
		while (1) {
			Gotoxy(44 - 2, 24);
			printf("选择要修改的内容编号： ");
			char temp[30];
			scanf("%s", temp);
			Gotoxy(44 - 2+24+16, 24);
			charRotation();
			r2 = atoi(temp);
			//输入的编号在范围之内的（1~6）
			if (r2 >= 1 && r2 <= 5) {
				char newContent[50];
				Gotoxy(44 - 2, 26);
				printf("需修改部分的新内容为： ");
				scanf("%s", newContent);
				Gotoxy(44 - 2 + 24 + 16, 26);
				charRotation();
				r3 = modifyDProcess(&allDProcesslist, r1, r2, newContent);
				if (r3 == -1) {
					Gotoxy(44 - 2, 28);
					printf("修改流程信息失败！  ");
					charRotation();
					Sleep(3000);
					DProcessInterface();
				}
				else {
					Gotoxy(44 - 2, 28);
					printf("选择修改流程信息成功！ ");
					charRotation();
					Sleep(3000);
					DProcessInterface();
				}
				break;
			}
			//输入的编号不在范围内的
			else {
				Gotoxy(44 - 2, 26);
				printf("您输入的选项编号错误！ ");
				charRotation();
				Sleep(5000);
				DProcessInterface();
			}
		}
	}

}

//功能界面5：编辑工艺流程模块界面
void  modifiDProcessModule() {
	system("cls");
	frameShow();
	char temp[30];
	Gotoxy(48, 6);
	printf("已发布工艺流程编辑面板");
	Gotoxy(41, 14);
	printf("请您输入需要编辑的工艺流程编号：  ");
	scanf("%s", temp);
	Gotoxy(44 + 34, 14);
	charRotation();
	errorTemplate(47, "正在查询相关的流程信息！");
	int r1 = searchDProcess(allDProcesslist, temp);
	//在这里出现查找失败的情况
	if (r1 < 0) {
		errorTemplate(46, "查询失败，没有相关流程信息！");
		errorTemplate(47, "正在退出编辑面板，请稍等！");
		DProcessInterface();
	}
	else {
		system("cls");
		frameShow();
		Gotoxy(48, 2);
		printf("已发布工艺流程编辑面板");
		Gotoxy(8, 4);
		printf("1.流程登记编号： %s", allDProcesslist.list[r1].DProcess_id);
		Gotoxy(36, 4);
		printf("2.流程名称： %s", allDProcesslist.list[r1].DProcess_name);
		Gotoxy(8, 6);
		printf("3.生产方式： %s", allDProcesslist.list[r1].DProcess_method);
		Gotoxy(36, 6);
		printf("4.模块数量： %d", allDProcesslist.list[r1].DProcess_num);
		Gotoxy(60, 6);
		printf("5.发布时间： %s", allDProcesslist.list[r1].in_time);
		processFrame(allDProcesslist.list[r1].DProcess_num + 2);
		ScanNewPModuleList(allDProcesslist.list[r1]);
		//从这里开始重新设定
		int choice;
		Gotoxy(9 + 30+2, 24);
		printf("(提示：1.为增加，2为修改，3为删除)");
		Gotoxy(9, 24);
		printf("请输入编辑工艺流程方式：  ");
		scanf("%d", &choice);
		Gotoxy(9+28, 24);
		charRotation();
		//比如说编辑工艺流程方式 1是增加
		if (choice == 1) {
			char addContent[50];
			char before_addContent[50];
			Gotoxy(9, 26);
			printf("请输入需要增加模块内容： ");
			scanf("%s", addContent);
			Gotoxy(9 +41, 26);
			charRotation();
			Gotoxy(10, 29);
			printf("提示：输入增加模块位置的前一个流程模块内容");
			Gotoxy(9, 28);
			printf("请输入增加模块放置的位置：");
			scanf("%s", before_addContent);
			Gotoxy(9+41, 29);
			charRotation();
			/*-------------------------数据结构操作---------------------------*/
			AddPModuleListRand(&allDProcesslist, r1, &before_addContent, &addContent);
			allDProcesslist.list[r1].DProcess_num = allDProcesslist.list[r1].DProcess_num + 1;
			Gotoxy(73, 27);
			printf("正在编辑内部工艺流程模块，请稍后...  ");
			charRotation();
			Sleep(2000);
			errorTemplate(46, "正在生成全新的工艺流程模块图！");
			frameShow();
			Gotoxy(48, 2);
			printf("已发布工艺流程查看面板");
			Gotoxy(8, 4);
			printf("1.流程登记编号： %s", allDProcesslist.list[r1].DProcess_id);
			Gotoxy(36, 4);
			printf("2.流程名称： %s", allDProcesslist.list[r1].DProcess_name);
			Gotoxy(8, 6);
			printf("3.生产方式： %s", allDProcesslist.list[r1].DProcess_method);
			Gotoxy(36, 6);
			printf("4.模块数量： %d", allDProcesslist.list[r1].DProcess_num);
			Gotoxy(60, 6);
			printf("5.发布时间： %s", allDProcesslist.list[r1].in_time);
			processFrame(allDProcesslist.list[r1].DProcess_num + 2);
			ScanNewPModuleList(allDProcesslist.list[r1]);
			Gotoxy(39, 24);
			printf("查看结果后，请输入任意值返回工艺面板： ");
			scanf("%s", temp);
			if (temp[0] == 'y') {
				errorTemplate(48, "正在返回工艺流程面板！");
				DProcessInterface();
			}
			else {
				errorTemplate(48, "正在返回工艺流程面板！");
				DProcessInterface();
			}
		}
		//比如说编辑工艺流程方式 2是修改
		else if (choice == 2) {
			char newContent[50];
			char oldContent[50];
			Gotoxy(9, 26);
			printf("请输入需要替换的模块内容： ");
			scanf("%s", oldContent);
			Gotoxy(9, 28);
			printf("请输入替换后模块新的内容： ");
			scanf("%s", newContent);
			/*-------------------------数据结构操作---------------------------*/
			modiPModuleListRand(&allDProcesslist, r1, &oldContent, &newContent);
			Gotoxy(73, 27);
			printf("正在编辑内部工艺流程模块，请稍后...");
			charRotation();
			Sleep(2000);
			errorTemplate(46, "正在生成全新的工艺流程模块图！");
			system("cls");
			frameShow();
			Gotoxy(48, 2);
			printf("已发布工艺流程查看面板");
			Gotoxy(8, 4);
			printf("1.流程登记编号： %s", allDProcesslist.list[r1].DProcess_id);
			Gotoxy(36, 4);
			printf("2.流程名称： %s", allDProcesslist.list[r1].DProcess_name);
			Gotoxy(8, 6);
			printf("3.生产方式： %s", allDProcesslist.list[r1].DProcess_method);
			Gotoxy(36, 6);
			printf("4.模块数量： %d", allDProcesslist.list[r1].DProcess_num);
			Gotoxy(60, 6);
			printf("5.发布时间： %s", allDProcesslist.list[r1].in_time);
			processFrame(allDProcesslist.list[r1].DProcess_num + 2);
			ScanNewPModuleList(allDProcesslist.list[r1]);
			Gotoxy(39, 24);
			printf("查看结果后，请输入任意值返回工艺面板： ");
			scanf("%s", temp);
			if (temp[0] == 'y') {
				errorTemplate(48, "正在返回工艺流程面板！");
				DProcessInterface();
			}
			else {
				errorTemplate(48, "正在返回工艺流程面板！");
				DProcessInterface();
			}
		}
		//比如说编辑工艺流程方式 3是删除
		else if (choice == 3) {
			char deleContent[50];
			Gotoxy(9, 26);
			printf("请输入需要删除的模块内容： ");
			scanf("%s", deleContent);
			/*-------------------------数据结构操作---------------------------*/
			DeletePModuleListRand(&allDProcesslist, r1, &deleContent);
			allDProcesslist.list[r1].DProcess_num = allDProcesslist.list[r1].DProcess_num - 1;
			Gotoxy(73, 27);
			printf("正在编辑内部工艺流程模块，请稍后...");
			charRotation();
			Sleep(2000);
			errorTemplate(46, "正在生成全新的工艺流程模块图！");
			system("cls");
			frameShow();
			Gotoxy(48, 2);
			printf("已发布工艺流程查看面板");
			Gotoxy(8, 4);
			printf("1.流程登记编号： %s", allDProcesslist.list[r1].DProcess_id);
			Gotoxy(36, 4);
			printf("2.流程名称： %s", allDProcesslist.list[r1].DProcess_name);
			Gotoxy(8, 6);
			printf("3.生产方式： %s", allDProcesslist.list[r1].DProcess_method);
			Gotoxy(36, 6);
			printf("4.模块数量： %d", allDProcesslist.list[r1].DProcess_num);
			Gotoxy(60, 6);
			printf("5.发布时间： %s", allDProcesslist.list[r1].in_time);
			processFrame(allDProcesslist.list[r1].DProcess_num + 2);
			ScanNewPModuleList(allDProcesslist.list[r1]);
			Gotoxy(39, 24);
			printf("查看结果后，请输入任意值返回工艺面板： ");
			scanf("%s", temp);
			if (temp[0] == 'y') {
				errorTemplate(48, "正在返回工艺流程面板！");
				DProcessInterface();
			}
			else {
				errorTemplate(48, "正在返回工艺流程面板！");
				DProcessInterface();
			}
		}
		//输出工艺流程方式是 错误的不在1到3范围内
		else {
			errorTemplate(46, "输入有误，没有相关流程操作！");
			modifiDProcessModule();
		}
	}

}

//功能界面6：保存工艺流程信息界面
void saveDProcess() {
	int r1 = allSaveDProcess();
	if (r1 == -1) {
		errorTemplate(48, "保存当前的流程信息失败！");
		DProcessInterface();
	}
	else {
		errorTemplate(48, "正在保存所有的流程信息！");
		errorTemplate(48, "保存所有的流程信息成功！");
		DProcessInterface();
	}
}

//配合功能界面1：功能函数--往链表里面新增全新的一个newDProcess
int addNewDProcess(DProcessSeqList* dpsl,DProcessInfo newDProcess) {

	//首先在仓储库存管理信息中查找是否有此登记的流程，如果有，返回 - 1，表示入库登记失败
	int r = searchDProcess(*dpsl, newDProcess.DProcess_id);
	if (r >= 0) {
		errorTemplate(48, "工艺流程登记编号已存在！");
		DProcessInterface();
	}
	//如果有序表空间不够，则扩充空间
	if (dpsl->length >= dpsl->size) {
		DProcessInfo* t = dpsl->list;
		dpsl->list = (DProcessInfo*)malloc(2 * dpsl->size * sizeof(DProcessInfo));
		if (dpsl->list == NULL) {
			errorTemplate(48, "保存无效，内存分配失败！");
			DProcessInterface();
		}
		dpsl->size = 2 * dpsl->size;
		for (int i = 0; i < dpsl->length; i++)
			DProcessCopy(&(dpsl->list[i]),t[i],newDProcess.DProcess_num);//这里的num完全可以用newDProcess的num替换
		free(t);
	}
	//	较原料入库登记编号插入到合适的位置，保证据原料供应企业编号有序
	int i = 0;
	for (i = dpsl->length - 1; i >= 0; i--) {
		r = strcmp(dpsl->list[i].DProcess_id, newDProcess.DProcess_id);
		if (r > 0)
			DProcessCopy(&(dpsl->list[i + 1]), dpsl->list[i], newDProcess.DProcess_num);
		else
			break;

	}
	DProcessCopy(&(dpsl->list[i + 1]), newDProcess, newDProcess.DProcess_num);
	dpsl->length++;
	//添加成功返回0
	return 0;
}

//配合功能界面123：功能函数--在工艺流程登记表中根据登记流程编号进行查找，没有该编号所占用库存则返回-1；如果有返回值则是该登记编号已被占用（查找算法用二分查找法）
int searchDProcess(DProcessSeqList dpsl, char* DPsn) {	
	int low = 0;
	int high = dpsl.length - 1;
	int mid;
	while (low <= high) {
		mid = (low + high) / 2;		//二分查找法
		if (strcmp(dpsl.list[mid].DProcess_id, DPsn) == 0)
			return mid;
		else
			if (strcmp(dpsl.list[mid].DProcess_id, DPsn) < 0)
				low = mid + 1;
			else
				high = mid - 1;
	}
	return -1;
}

//配合功能界面123：功能函数--深度拷贝新增的工艺流程图纸信息,其中num的作用是设置的模块数
void DProcessCopy(DProcessInfo* to, DProcessInfo from,int num) {
	PMLinkedListInit(&to->processList);		//千万不能忘记初始化
	strcpy(to->DProcess_id, from.DProcess_id);
	strcpy(to->DProcess_name, from.DProcess_name);
	strcpy(to->DProcess_method, from.DProcess_method);
	PModuleNode *temp = from.processList.head->next;
	for (int i = 0; i < num; i++) {
		addNewPModuleListTill(&to->processList, temp->PModule);
		temp = temp->next;
	}
	to->DProcess_num = from.DProcess_num;
	strcpy(to->in_time, from.in_time);
}

//配合功能界面2：功能函数--在工艺流程管理表中删除第index个元素，删除算法为把后面的数据元素覆盖前面，返回0表示删除成功
int delDProcess(DProcessSeqList* dpsl, int index) {
	if (dpsl->length <= 0) {
		errorTemplate(48, "工艺流程数据库信息为空！");
		DProcessInterface();
		return -1;
	}
	if (index < 0 || index >= dpsl->length) {
		errorTemplate(47, "需要删除的流程超出执行范围！");
		DProcessInterface();
		return -1;
	}

	for (int i = index + 1; i < dpsl->length; i++) {
		DProcessCopy(&(dpsl->list[i - 1]), dpsl->list[i], dpsl->list[i].DProcess_num);
	}
	dpsl->length--;
	return 0;
}

//配合功能界面3：功能函数：在工艺流程管理表dpsl中修改第index个流程批次的信息，type表示要修改的类型（取值1（工艺流程登记编号），2（工艺流程登记名称），3（工艺生产方式备注），4（工艺流程模块数量）,5（工艺流程登记时间）），info表示新的信息值，修改成功返回0，否则返回1
int modifyDProcess(DProcessSeqList* dpsl, int index, int type, char* info) {
	if (index < 0 && index >= dpsl->length) {
		errorTemplate(47, "需要删除的流程超出执行范围！");
		DProcessInterface();
	}
	switch (type) {
		case 1: strcpy(dpsl->list[index].DProcess_id, info); break;
		case 2: strcpy(dpsl->list[index].DProcess_name, info); break;
		case 3: strcpy(dpsl->list[index].DProcess_method, info); break;
		//case 4: dpsl->list[index].DProcess_num = atof(info); break;
		case 4: strcpy(dpsl->list[index].in_time, info); break;
		default: {
			errorTemplate(48, "修改的流程信息编号有误！");
			DProcessInterface();
		}
	}
	return 0;
}

//配合功能界面5：功能函数--保存在系统中增加删除更改后的信息进入数据库中
int allDProcessInfoSaveToFile(DProcessSeqList dpsl, char* filename) {
	FILE *fp;
	char strline[80];
	if ((fp = fopen(filename, "w")) == NULL) {
		errorTemplate(47, "工艺流程的相关数据库不存在！");
		DProcessInterface();
	}

	for (int i = 0; i < dpsl.length; i++) {
		fputs(dpsl.list[i].DProcess_id, fp);
		fputc('\n', fp);
		fputs(dpsl.list[i].DProcess_name, fp);
		fputc('\n', fp);
		fputs(dpsl.list[i].DProcess_method, fp);
		fputc('\n', fp);
		sprintf(strline, "%d", dpsl.list[i].DProcess_num);
		fputs(strline, fp);
		fputc('\n', fp);
		fputs(dpsl.list[i].in_time, fp);
		fputc('\n', fp);
		/*-------------------------------------------*/
		PModuleNode *temp = dpsl.list[i].processList.head;	//定义一个临时变量来指向头
	//先有可能是该节点该流程内不含有任何的模块信息
		while (temp != NULL) {
			PModuleNode* pt = temp;
			temp = temp->next;		    //temp指向下一个的地址 即实现链表的模块不断移动操作
			fputs(pt->PModule, fp);
			fputc('\n', fp);
		}
	}
	fclose(fp);
	return 0;
}

//配合功能界面5：功能函数--按类型保存仓储信息到文件中
int allSaveDProcess() {
	int r1 = allDProcessInfoSaveToFile(allDProcesslist, "工艺流程链及模块信息信息数据库.txt");  //保存所有的工艺流程信息到文件中
	if (r1 == -1) {
		errorTemplate(48, "保存当前的流程信息失败！");
		DProcessInterface();
	}
	return 0;
}

//特殊接口函数：管理员专用于查询仓储库存原料信息界面
void checkDProcessAdmin() {
	system("cls");
	frameShow();
	char temp[30];
	Gotoxy(48, 6);
	printf("已发布工艺流程查看面板");
	Gotoxy(41, 14);
	printf("请您输入需要查询的工艺流程编号：  ");
	scanf("%s", temp);
	Gotoxy(44 + 34, 14);
	charRotation();
	errorTemplate(47, "正在查询相关的流程信息！");
	int r1 = searchDProcess(allDProcesslist, temp);
	//在这里出现查找失败的情况
	if (r1 < 0) {
		errorTemplate(46, "查询失败，没有相关流程信息！");
		errorTemplate(49, "正在返回管理员的面板！");
		adminLeaderInterface();
	}
	else {
		system("cls");
		frameShow();
		Gotoxy(48, 2);
		printf("已发布工艺流程查看面板");
		Gotoxy(8, 4);
		printf("1.流程登记编号： %s", allDProcesslist.list[r1].DProcess_id);
		Gotoxy(36, 4);
		printf("2.流程名称： %s", allDProcesslist.list[r1].DProcess_name);
		Gotoxy(8, 6);
		printf("3.生产方式： %s", allDProcesslist.list[r1].DProcess_method);
		Gotoxy(36, 6);
		printf("4.模块数量： %d", allDProcesslist.list[r1].DProcess_num);
		Gotoxy(60, 6);
		printf("5.发布时间： %s", allDProcesslist.list[r1].in_time);
		processFrame(allDProcesslist.list[r1].DProcess_num + 2);
		ScanNewPModuleList(allDProcesslist.list[r1]);
		Gotoxy(39, 24);
		printf("查看结果后，请输入任意值返回管理面板： ");
		scanf("%s", temp);
		if (temp[0] == 'y') {
			errorTemplate(49, "正在返回管理员的面板！");
			adminLeaderInterface();
		}
		else {
			errorTemplate(49, "正在返回管理员的面板！");
			adminLeaderInterface();
		}
	}
}