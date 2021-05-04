#include<stdio.h>
#include <stdio.h>
#include <windows.h>
#include<process.h>
#include <time.h>

//原料供应企业信息
typedef  struct  MCom {
	char MCom_id[10];				//原料供应企业编号
	char MCom_name[50];			//原料供应企业名称
	char MCom_location[20];			//原料供应企业所在地
	char MCom_material[20];				//原料供应企业提供货品
	float MCom_price;				//原料供应企业供应价格
	char in_time[20];				//签约企业时间
}MComInfo;

//原料供应企业信息
typedef  struct  PCom {
	char PCom_id[10];				//产品采购企业编号
	char PCom_name[50];			//产品采购企业名称
	char PCom_location[20];			//产品采购企业所在地
	char PCom_material[20];				//产品采购企业提供货品
	float PCom_price;				//产品采购企业供应价格
	char in_time[20];				//签约产品采购企业时间
}PComInfo;

//采用动态有序顺序表作为数据结构来存放所有的原料供应企业信息   
typedef struct {
	MComInfo*  list;
	int length;		//动态有序顺序表的长度
	int size;		//动态有序顺序表的长度2
}MComsSeqList;

//采用动态有序顺序表作为数据结构来存放所有的产品采购企业信息   
typedef struct {
	PComInfo*  list;
	int length;		//动态有序顺序表的长度
	int size;		//动态有序顺序表的长度2
}PComsSeqList;

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
//配合功能界面123：功能函数--在产品采购企业表中根据签约企业编号进行查找，没有此企业则返回-1；如果有返回值则是该产品采购企业的编号（查找算法用二分查找法）
int searchPCom(PComsSeqList pcsl, char* PCsn);
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

//配合功能界面5：功能函数--保存在系统中增加删除更改后的信息进入数据库中
int allMComsInfoSaveToFile(MComsSeqList mcsl, char* filename);
//配合功能界面5：功能函数--保存在系统中增加删除更改后的信息进入数据库中
int allPComsInfoSaveToFile(PComsSeqList pcsl, char* filename);
//（通用）配合功能界面5：功能函数--按类型保存各类信息到文件中
int allSave(int type);