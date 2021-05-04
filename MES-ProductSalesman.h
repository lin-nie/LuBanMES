#include<stdio.h>
#include <stdio.h>
#include <windows.h>
#include<process.h>
#include <time.h>

//采购订单管理信息
typedef  struct  PSale {
	char PSale_id[10];				//采购产品订单登记编号
	char PSale_name[50];			//采购产品登记名称
	char PSale_destination[50];		//采购订单发往的目的地
	char PSale_company[60];			//采购订单需求企业名称
	float PSale_num;				//采购产品出库批次数量
	char in_time[20];				//采购订单交付登记时间
}PSaleInfo;

//采用动态有序顺序表作为数据结构来存放所有的采购订单管理信息   
typedef struct {
	PSaleInfo*  list;
	int length;		//动态有序顺序表的长度
	int size;		//动态有序顺序表的长度2
}PSalesSeqList;

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

//配合功能界面5：功能函数--保存在系统中增加删除更改后的信息进入数据库中
int allPSalesInfoSaveToFile(PSalesSeqList pssl, char* filename);

//配合功能界面5：功能函数--按类型保存采购订单信息到文件中
int allSaveSale();