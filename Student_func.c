#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getch.h>
#include "main.h"
#include "Student_func.h"
#include "Student_main.h"
#include "tools.h"

static int cnt[1024]={};	//	计数
static int i=0;				//	定位
static int first_start=1;	//	第一次启动标志

//	第一次登录强制修改密码
int Student_login_forced_password_change(void)
{
	if(1 == first_start)	//	第一次启动判断
	{
		for(int a=0;a<1024;a++)	
		{
			cnt[a]=3;
		}
		first_start=0;		//	标志置0
	}
	for(;;)
	{
		Stu stu={};
		stdin->_IO_read_ptr = stdin->_IO_read_end;	//	输入缓冲区
		printf("\n按q退出,其他键继续:\n");				//	退出学生登录操作
		if('q'== getch())
		{
			return 1;
		}
		enter_account(20,stu.code);					//	输入账号
		printf(" \n");					
		stdin->_IO_read_ptr = stdin->_IO_read_end;	//	输入缓冲区
		for(;;)
		{
			conceal(20,stu.key);					//	输入密码
			if(strlen(stu.key) < 6)		//	判断输入的密码长度
			{
				printf("密码长度有误");
			}
			else
			{
				break;
			}
		}
		FILE *frp = fopen("Student_password.txt","r+");		//	打开存放学生密码的文件
		if(NULL == frp)			//	判断文件是否打开
		{
			perror("fopen");	//	记录错误信息
			return 0;	
		}
		
		
		int ret = 1;			//	ret为fscanf成功读取的变量个数，初始化设为1
		//printf("code:%s key:%s\n",Student->code,Student->key);
		i=0;
		while(-1 != ret)		//	当fscanf没有读到变量的时候结束循环
		{	
			ret=fscanf(frp,"%hhd %s %s\n",&Student[i].is_clock,Student[i].code,Student[i].key);
			
			if(!strcmp(Student[i].code,stu.code) && strcmp(stu.code,"\0"))	//	判断输入账号与文件中是否一致
			{
				if(1 == Student[i].is_clock)	//	判断账号是否被锁定
				{
					msg_show("账号已锁定，请联系教师解锁\n",1.5);
					break;
				}
				if(!strcmp(stu.key,"000000")&&!strcmp(stu.key,Student[i].key))// 判断账号是否是第一次登录
				{
					fclose(frp);	//	关闭文件
					printf("\n登录成功，请进行密码修改,密码位数7～19\n");
					Student_password_change(i);		//	调用密码修改函数，参数是当前对应的人
					return 0;
				}
				
				else if(!strcmp(stu.key,Student[i].key))	//	判断账号和密码是否一致
				{
					printf("\n登录成功\n");
					cnt[i]=3;
					fclose(frp);	//	关闭文件
					return 0;
				}
				else				//	密码输入错误
				{
					printf("账号或密码输入错误，请重新登录\n");
					//printf("code:%s\n",Student[i].code);
					cnt[i]--;				//	计数
					Student_lock_account(frp);	//	调用密码三次输错进行账号锁定函数
					fclose(frp);		//	关闭文件
					break;
				}
			}
			i++;
		}
		if(strcmp(Student[i].code,stu.code) || !strcmp(stu.code,"\0"))	//	判断账号输入是否错误
		{
			printf("账号或密码输入错误，请重新登录\n");
		}
	}
	
}

//	查询成绩
void Student_query_results(void)
{
	FILE* frp=fopen("Student_job_information.txt","r+");//	打开带有学生成绩的文件
	if(NULL == frp)			//	判断文件是否打开	
	{
		perror("fopen");	//	记录错误信息
		return;
	}
	float avg_c=0,avg_e=0,avg_m=0,sum_m[1024]={},sum[i],mark_c[1024]={},mark_e[1024]={},mark_m[1024]={};
	float max_c=0,max_e=0,max_m=0,min_c=0,min_e=0,min_m=0;		// 	定义各种成绩相关变量
	int ret1 = 1,k=0;		//	ret1为fscanf成功读取的变量个数，初始化为1,k用来控制每个人
	//	读取文档中所有数据
	while(-1 != ret1 )
	{
		ret1=fscanf(frp,"%s %s %c %f %f %f",Student[k].code,Student[k].name,&Student[k].sex,&Student[k].Chinese_mark,&Student[k].English_mark,&Student[k].Math_mark); //读取文件中每行数据
		if(k<=i)	//	记录当前学生总成绩，方便之后查找
		{
			sum[k]=Student[k].Chinese_mark+Student[k].English_mark+Student[k].Math_mark;
		}
		if(-1 != ret1)
		{
			avg_c=avg_c+Student[k].Chinese_mark;		//	语文总分
			avg_e=avg_e+Student[k].English_mark;		//	英语总分
			avg_m=avg_m+Student[k].Math_mark;			//	数学总分
			mark_c[k]=Student[k].Chinese_mark;			//	取出每个学生的语文成绩
			mark_e[k]=Student[k].English_mark;			//	取出每个学生的英语成绩
			mark_m[k]=Student[k].Math_mark;				//	取出每个学生的数学成绩
			sum_m[k]=Student[k].Chinese_mark+Student[k].English_mark+Student[k].Math_mark;	//	取出每个学生的总成绩
			k++;
		}
	}
	avg_c/=k;				//	语文平均分
	avg_e/=k;				//	英语平均分
	avg_m/=k;				//	数学平均分
	sort(sum_m,k);			//	将总成绩进行排序
	sort(mark_c,k);			//	将语文成绩进行排序
	sort(mark_e,k);			//	将英语成绩进行排序
	sort(mark_m,k);			//	将数学成绩进行排序
	max_c=mark_c[0];		//	下标0对应的数是语文最高分
	max_e=mark_e[0];		//	下标0对应的数是英语最高分
	max_m=mark_m[0];		//	下标0对应的数是数学最高分
	min_c=mark_c[k-1];		//	下标k-1对应的数是语文最低分
	min_e=mark_e[k-1];		//	下标k-1对应的数是英语最低分
	min_m=mark_m[k-1];		//	下标k-1对应的数是数学最低分
	printf("各科成绩从高到低排，后面总分与前面各科成绩并无直接关联\n");
	for(int a=0;a<k;a++)		//	列出所有同学的总分,各科成绩
	{
		printf("语文成绩：%9g 数学成绩：%9g 英语成绩：%9g 第%d名同学总分：%g \n",mark_c[a],mark_m[a],mark_e[a],a+1,sum_m[a]);
	}
	printf("语文平均分：%7g 数学平均分：%7g 英语平均分：%7g\n", avg_c,avg_m,avg_e);
	printf("语文最高分：%7g 数学最高分：%7g 英语最高分：%7g\n",max_c,max_m,max_e);
	printf("语文最低分：%7g 数学最低分：%7g 英语最低分：%7g\n",min_c,min_m,min_e);
	printf("%s同学 语文成绩：%2g 数学成绩：%2g 英语成绩：%2g\n",Student[i].name,Student[i].Chinese_mark,Student[i].Math_mark,Student[i].English_mark);
	for(int a=0;a<k;a++)
	{
		if(sum[i]==sum_m[a])	//	找到当前学生对应的总分排名
		{
			printf("总分：%g 总排名：%d\n",sum[i],a+1);
					
		}
	}
	fclose(frp);
	anykey_continue();
}

//	降序
float *sort(float* s,int len)
{
	int temp=s[0];	//		中间变量，专门记录数据
	for(int a=0;a<len;a++)
	{
		for(int b=a+1;b<=len;b++)
		{
			if(s[b]>s[a])		//	比较换位，大的在前
			{
				temp=s[a];
				s[a]=s[b];
				s[b]=temp;
			}
		}
	}
	return s;
}


//	修改密码
void Student_change_password(void)
{
	printf("请输入要修改的密码\n");
	Student_password_change(i);		//	调用密码修改函数，利用'w'打开文件的方式
}




//	查看个人信息
void Student_view_personal_information(void)
{
	FILE* frp=fopen("Student_job_information.txt","r+");	//	打开记录学生基本信息的文件
	if(NULL == frp)		// 判断文件是否被打开
	{
		perror("fopen");	//	记录错误信息
		return;
	}
	for(int k=0;k<=i;k++)	// 读取当前学生信息
	{
		fscanf(frp,"%s %s %c %f %f %f",Student[k].code,Student[k].name,&Student[k].sex,&Student[k].Chinese_mark,&Student[k].English_mark,&Student[k].Math_mark);
	}
	printf("姓名：%s 学号：%s 性别：%s\n",Student[i].name,Student[i].code,'w'==Student[i].sex?"女":"男");
	fclose(frp);		//	关闭文件
	anykey_continue();	//	调用按任意键函数
}

//	三次密码错误锁定账号
void Student_lock_account(FILE *fp)
{	
	if(0 == cnt[i])
	{
		printf("账号已锁定，请联系教师解锁\n");
		cnt[i] = 3;			//	计数重置
		Student[i].is_clock=1;		//	账号锁定
		fseek(fp,-(strlen(Student[i].code)+strlen(Student[i].key)+4),SEEK_CUR);// 移动读取指针位置
		fprintf(fp,"%hhd",Student[i].is_clock);	//	在文件中记录
	}
}
