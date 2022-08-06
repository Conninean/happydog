#ifndef STUDENT_TOOLS_H
#define STUDENT_TOOLS_H

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


#ifdef DEBUG
	#define debug(...) printf(__VA_ARGS__)
#else
	#define debug(...)
#endif

#define STU_MAX 1024
#define TEA_MAX 256

void anykey_continue(void);					//按任意键继续
void msg_show(const char* msg,float sec);	//打印提示信息
void anykey_continue(void);					//按任意键继续
void conceal(int len,char *password);		//隐藏密码
void enter_account(int len,char *password);	//输入帐号
void enter_name(int len,char *password);	//输入NAME
int how_many(char* filename);				//检测人数



int limit_input(int len,char *str);			//输入字符串到str中，如果超过len的长度，就返回-1，否则返回输入字符个数;




int Start_menu(void);						//开始界面
int Student_menu(void);						//显示学生界面
int Master_menu(void);						//显示校长界面
int Teacher_menu(void);						//显示教师界面


void Student_password_change(int j);		//更改第j行学生的密码
int Student_location_search(void);			//提示输入学生学号，读取学生数据至结构体并返回学生位置，没有找到返回-1
int Student_find_location(char* code);		//传入学生学号，返回学生位置
int load_all_students(void);				//重新载入所有在校学生数据
void write_all_students(void);				//写入所有在校学生数据

void Teacher_password_change(int j);		//更改第j行teacher的密码
int  Teacher_location_search(void);			//提示输入教师工号，返回教师位置，没有找到返回-1
void Teacher_password_reset(int j,int mode);//输入教师位置和模式，mode=1重置教师密码，mode=2解除教师锁定
void del_Teacher(int i);					//输入已删除在职教师位置，移入离职教师文件

bool Master_password_compare(void);			//判断初始化密码
char *init_M(void);							//返回校长密码





typedef struct Stu
{    

	float Chinese_mark;
	float English_mark;
	float Math_mark;
	char name[20];
	char sex;
	char code[20];
	char key[20];
	char is_clock;
}Stu;


typedef struct Tea
{
	
	int clock_cnt;
	char name[20];
	char sex;
	char code[20];
	char key[20];
	char is_clock;//是否被锁定,初始为0，锁定后为1；
}Tea;





#endif//STUDENT_TOOLS_H
