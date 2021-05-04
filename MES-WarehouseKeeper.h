#include<stdio.h>
#include <stdio.h>
#include <windows.h>
#include<process.h>
#include <time.h>

typedef int Elemtype;

//原料入库管理信息
typedef  struct  MWare {
	char MWare_id[10];				//原料入库后仓储管理编号
	char MWare_name[50];			//原料入库后仓储登记名称
	char MWare_location[50];		//入库原料产地（可追溯）
	char MWare_company[60];			//原料供应企业名称登记
	float MWare_num;				//原料入库批次数量
	char in_time[20];				//原料入库后仓储登记时间
}MWareInfo;

//采用动态有序顺序表作为数据结构来存放所有的仓储库存原料管理信息   
typedef struct {
	MWareInfo*  list;
	int length;		//动态有序顺序表的长度
	int size;		//动态有序顺序表的长度2
}MWaresSeqList;

/* 定义二叉树结构 */
typedef struct BTNode {
	Elemtype data;
	struct BTNode *lchild, *rchild;
}BTree;

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
//配合功能界面5：功能函数--保存在系统中增加删除更改后的信息进入数据库中
int allMWaresInfoSaveToFile(MWaresSeqList mwsl, char* filename);
//配合功能界面5：功能函数--按类型保存仓储信息到文件中
int allSaveWare();
//特殊接口函数：管理员专用于查询仓储库存原料信息界面
void queryMWareAdmin();