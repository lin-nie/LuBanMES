#include<stdio.h>
#include <stdio.h>
#include <windows.h>
#include<process.h>
#include <time.h>

/*-----------------------------------------------------------*/

//数据结构定义1-创建每个结构体节点
typedef struct node{
	char PModule[30];		//数据域,用于存放流程模块值
	struct node* next;	//指针域(指向节点的指针）
}PModuleNode;

//单链表结构体
typedef struct {
	PModuleNode* head;
	PModuleNode* rear;
	int count;
}PMLinkedList;

//工艺流程设计发布管理信息
typedef  struct  DProcess {
	char DProcess_id[10];			//工艺流程设计管理编号
	char DProcess_name[50];			//工艺流程登记名称（如：电池-工艺流程）
	char DProcess_method[50];		//工艺流程生产设备（产线、机床加工机制不同）
	int DProcess_num;				//工艺流程所包含的子模块工艺数
	char in_time[20];				//发布工艺流程登记时间
	PMLinkedList processList;
}DProcessInfo;

//采用动态有序顺序表作为数据结构来存放所有的工艺流程设计管理信息   
typedef struct {
	DProcessInfo*  list;
	int length;		//动态有序顺序表的长度
	int size;		//动态有序顺序表的长度2
}DProcessSeqList;

struct coordinate {	//专门用来记录可以输出的坐标值
	int x;			//Gotoxy的参数x
	int y;			//Gotoxy的参数x
};

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