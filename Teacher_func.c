#include <stdio.h>
#include "Teacher_func.h"
#include "tools.h"
#include <string.h>
#include <stdlib.h>
#include <getch.h>
#include "Teacher_main.h"
#include "main.h"

static int cnt=3;
static int i=0;
int Teacher_login_forced_password_change(void) //教师登录后判断密码是否正确
{		
		printf("\n正在进行教师登录操作，按q退出,其他键继续:\n");	
		if('q'== getch())
		{
			return 0;
		}
		Tea tea={};							//建立一个教师结构体
		enter_account(20,tea.code);			//限制输入字符20以内
		conceal(20,tea.key);				//限制输入密码20个字符以内
		
		for(;;)
		{
			if(strlen(tea.key) < 6 || strlen(tea.key) >19)//限制密码不能少于6位
			{
				printf("\n密码长度有误\n");
				conceal(20,tea.key);	
			}
			else
			{
				break;				//通过密码长度检验
			}
		}
		
		
		
		FILE *frp = fopen("Teacher_password.txt","r+");//打开存放教师密码的文件
		
		if(NULL == frp)
		{
			perror("fopen");
			return 0;	
		}
		
		
		int ret = 1;//记录fsanf的返回值，用于在读完文件后终止读文件
		i=0;//记录登录教师的位置
		memset(&Teacher[0],0,sizeof(Teacher)*TEA_MAX);//清空教师结构体
		while(-1 != ret)
		{	
			ret=fscanf(frp,"%c %s %s\n",&Teacher[i].is_clock,Teacher[i].code,Teacher[i].key);//读取文件中的内容，放入结构体
			
			if(!strcmp(Teacher[i].code,tea.code) && strcmp(Teacher[i].code,"\0"))//将输入的账号不断与密码文件中的各项比较，找到相同的后进入密码比较
			{
				if(1 == Teacher[i].is_clock)								//判断是否锁定
				{
					msg_show("\n账号已锁定，请联系校长解锁\n",1.5);
					break;
				}
				
				
				if(!strcmp(tea.key,"000000")&&!strcmp(tea.key,Teacher[i].key))//判断是否是第一次登录
				{
					fclose(frp);
					printf("\n登录成功，由于是第一次登录，请进行密码修改,密码位数6～19\n");//第一次登录修改密码
					Teacher_password_change(i);
					return 1;
				}			
				else if(!strcmp(tea.key,Teacher[i].key))		//不是第一次登录，且密码正确
				{
					printf("\n登录成功\n");
					fclose(frp);
					frp=NULL;
					return 1;
				}
				else								//不是第一次登录，且密码错误
				{
					printf("\n密码输入错误，请重新登录\n");
					cnt--;
					Teacher_lock_account(i,frp);//判断是否已经输入错误3次，3次则锁定
					fclose(frp);
					frp=NULL;
					break;
				}
			}
			i++;
		}
			printf("\n帐号输入错误，请重新登录\n");			//没有找到对应账号
			anykey_continue();				
			return 0;	
}



void Teacher_view_personal_information(void)	//教师查看个人信息
{
	FILE* frp=fopen("Teacher_job_information.txt","r+");
	if(NULL == frp)
	{
		perror("fopen");
		return;
	}
	system("clear");
	for(int k=0;k<=i;k++)
	{
		fscanf(frp,"%s %s %c",Teacher[k].code,Teacher[k].name,&Teacher[k].sex);
	}
	if('m' == Teacher[i].sex)
	{
		printf("姓名：%s 工号：%s 性别：男\n",Teacher[i].name,Teacher[i].code);
	}
	else
	{
		printf("姓名：%s 工号：%s 性别：女\n",Teacher[i].name,Teacher[i].code);
	}
	fclose(frp);
	frp=NULL;
	anykey_continue();
}

void Teacher_add_one_student(void)//添加单个学生
{
	int id;
	char name[30];
	char sex;
	FILE* fwp_tj=fopen("Student_job_information.txt","r+");
	if(NULL == fwp_tj)
	{
		perror("fopen");
		return;	
	}
	printf("请输入学生的姓名 性别:\n");
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	for(;;)
	{
						
		if(-1==	limit_input(20,name))//输入姓名
		{
			printf("输入格式有误\n");
			anykey_continue();	
			return;
		}
		scanf("%c",&sex);//输入性别
		if('w' == sex || 'm' == sex)
		{
			break;
		}
		else
		{
			system("clear");
			printf("您输入的格式有误请重新输入:\n");
		}
	}
	FILE* fwp_tl=fopen("Student_lastcode.txt","r+");//读取学号文件
	if(NULL == fwp_tl)
	{
		perror("fopen");
		return;	
	}
	fscanf(fwp_tl,"%d",&id);id++;
	fclose(fwp_tl);
	fwp_tl=NULL;
	fwp_tl=fopen("Student_lastcode.txt","w");
	if(NULL == fwp_tl)
	{
		perror("fopen");
		return;	
	}
	fprintf(fwp_tl,"%d",id);
	fclose(fwp_tl);
	fwp_tl=NULL;
	fseek(fwp_tj,0,SEEK_END);
	fprintf(fwp_tj,"%d %s %c %g %g %g\n",id,name,sex,0.0,0.0,0.0);//将新学生数据写入学生信息文件
	fclose(fwp_tj);
	FILE* fwp_tp=fopen("Student_password.txt","r+");
	if(NULL == fwp_tp)
	{
		perror("fopen");
		return;	
	}
	fseek(fwp_tp,0,SEEK_END);
	fprintf(fwp_tp,"%c %d %s\n",'0',id,"000000");//将新学生数据写入学生密码文件
	fclose(fwp_tp);
	fwp_tl=NULL;
	msg_show("录入成功!\n",1);
}



void Teacher_del_student(void)//删除学生
{
	char num[20];
	char num2[20];
	printf("请输入所要删除的学生学号:");
	for(;;)
	{
		
		if(-1==limit_input(20,num))
		{
		printf("输入格式有误\n");
		anykey_continue();	
		return;
		}		
		if(0 == strcmp(num,"xxxxxx"))
		{
			msg_show("查无此人!\n",2);
			return;
		}
		else
		{
			break;
		}
	}
	printf("请再次输入所要删除的学生学号:");
	if(-1==limit_input(20,num2))
	{
		printf("输入格式有误\n");
		anykey_continue();	
		return;
	}	
	if(strcmp(num,num2))
	{
		printf("两次输入不同！删除失败！\n");
		sleep(1);
		return;
	}
	
	int num_of_student=0;
	num_of_student=load_all_students();
	for(int i=0;i<num_of_student;i++)
	{
		if(!strcmp(Student[i].code,num))
		{
			Student[i].sex='\0';
			break;
		}
		if(i==num_of_student-1)
		{
			msg_show("查无此人!\n",2);
			return;
		}
		
	}
	write_all_students();	
	msg_show("删除成功!\n",2);
	return;
	
}



void Teacher_find_student(void)
{
	int i=Student_location_search();
	system("clear");
	if(-1==i)
	{
		printf("未找到该学生\n");
		sleep(1);
		return;
	}
	else
	{
		load_all_students();
		
		printf("查询成功：\n 序号：%d\n 学号：%s\n 姓名：%s\n 性别：%c\n 语文成绩：%.1f\n 英语成绩：%.1f\n 数学成绩：%.1f\n",i,Student[i].code,Student[i].name,Student[i].sex,Student[i].Chinese_mark,Student[i].English_mark,Student[i].Math_mark);
		
		anykey_continue();		
	}
	
	
}

void Teacher_change_student_message(void)//修改学生信息
{
	int i=Student_location_search();
	system("clear");
	if(-1==i)
	{
		printf("未找到该学生\n");
		sleep(1);
		return;
	}
	else
	{
		load_all_students();
		printf("该学生信息如下：\n");
		printf("学号：%s\n姓名：%s\n性别：%c\n语文成绩：%.1f\n英语成绩：%.1f\n数学成绩：%.1f\n",Student[i].code,Student[i].name,Student[i].sex,Student[i].Chinese_mark,Student[i].English_mark,Student[i].Math_mark);
		printf("输入r确认修改，其他键退出\n");
		stdin->_IO_read_ptr = stdin->_IO_read_end;
		char key;
		scanf("%c",&key);
		
		if(key=='r')
		{

			printf("请输入学生姓名 性别（m/w）：\n");
			stdin->_IO_read_ptr = stdin->_IO_read_end;
			if(-1==limit_input(20,Student[i].name))
			{
				printf("输入格式有误\n");
				anykey_continue();	
				return;
			}
			Student[i].sex=getchar();
			if(Student[i].sex!='m'&& Student[i].sex!='w')
			{
				printf("输入格式错误！\n");
				anykey_continue();	
				return;
			}
			
			printf("依次输入语文 英语 数学三科成绩，要求大于0的阿拉伯数字，中间用空格间隔\n");
			stdin->_IO_read_ptr = stdin->_IO_read_end;
			scanf("%f %f %f",&Student[i].Chinese_mark,&Student[i].English_mark,&Student[i].Math_mark);	

			if(Student[i].Chinese_mark>=0 && Student[i].Chinese_mark<=100 && Student[i].English_mark >=0 && Student[i].English_mark <=100 && Student[i].Math_mark >=0 && Student[i].Math_mark <= 100)
			{
				write_all_students();
				printf("成功修改！\n修改后的信息如下：\n");
				printf("学号：%s\n姓名：%s\n性别：%c\n语文成绩：%.1f\n英语成绩：%.1f\n数学成绩：%.1f\n",Student[i].code,Student[i].name,Student[i].sex,Student[i].Chinese_mark,Student[i].English_mark,Student[i].Math_mark);
				anykey_continue();	

			}
			else
			{
				printf("格式有误\n");
				anykey_continue();
				return;
			}
		}
		
	}

}


void Teacher_input_student_score(void)//       录入学生成绩  
{
	system("clear");
	printf("请选择模式：按1导入单个学生成绩，按2批量导入学生成绩,其他键退出\n");
	if(getch()=='1')
	{
		Teacher_input_one_student_score();
	}
	else if(getch()=='2')
	{
		Teacher_input_many_student_score();
	}
	else
	{
		return;
	}

}


void Teacher_input_one_student_score(void)
{
	system("clear");
	int i=Student_location_search();
	system("clear");
	if(-1==i)
	{
		printf("未找到该学生\n");
		sleep(1);
		return;
	}
	else
	{
		load_all_students();
		printf("该学生信息如下：\n");
		printf("学号：%s\n姓名：%s\n性别：%c\n语文成绩：%.1f\n英语成绩：%.1f\n数学成绩：%.1f\n",Student[i].code,Student[i].name,Student[i].sex,Student[i].Chinese_mark,Student[i].English_mark,Student[i].Math_mark);
		printf("输入r确认修改，其他键退出\n");
		stdin->_IO_read_ptr = stdin->_IO_read_end;
		char key;
		scanf("%c",&key);
		
		if(key=='r')
		{
			printf("依次输入语文 英语 数学三科成绩，要求大于0的阿拉伯数字，中间用空格间隔\n");
			stdin->_IO_read_ptr = stdin->_IO_read_end;
			scanf("%f %f %f",&Student[i].Chinese_mark,&Student[i].English_mark,&Student[i].Math_mark);

			

			if(Student[i].Chinese_mark>=0 && Student[i].Chinese_mark<=100 && Student[i].English_mark >=0 && Student[i].English_mark <=100 && Student[i].Math_mark >=0 && Student[i].Math_mark <= 100)
			{
				write_all_students();
				printf("成功修改！\n修改后的信息如下：\n");
				printf("学号：%s\n姓名：%s\n性别：%c\n语文成绩：%.1f\n英语成绩：%.1f\n数学成绩：%.1f\n",Student[i].code,Student[i].name,Student[i].sex,Student[i].Chinese_mark,Student[i].English_mark,Student[i].Math_mark);
				anykey_continue();	

			}
			else
			{
				printf("格式有误\n");
				anykey_continue();
				return;
			}
		}
		
	}

}


void Teacher_input_many_student_score(void)

{
	system("clear");
	load_all_students();
	char stu_code[20]={};//存放学号
	float Chinese_mark=0.0;//存放三科成绩
	float English_mark=0.0;
	float Math_mark=0.0;
	int location=0;
	
	int ok_num=0;//成功写入的个数
	
	printf("开始批量导入成绩，请按如下格式输入学生成绩至本文件目录下的“score.txt”，每行一组：\n");
	printf("学生学号 语文成绩 英语成绩 数学成绩\n");
	printf("按y继续，其他键退出\n");
	if(getch()!='y')//退出
	{
		return;
	}
	FILE* frp=fopen("score.txt","r");//打开存放成绩的文件
	if(NULL == frp)			//	判断文件是否打开	
	{
		perror("fopen");	//	记录错误信息
		printf("\n没有找到“score.txt”文件\n");
		anykey_continue();		
		return;
	}
	
	for(;;)
	{
		if(-1==fscanf(frp,"%s",stu_code))
		{
			break;
		}
		fscanf(frp,("%f%f%f\n"),&Chinese_mark,&English_mark,&Math_mark);
		
		if(!(Student[i].Chinese_mark>=0 && Student[i].Chinese_mark<=100 && Student[i].English_mark >=0 && Student[i].English_mark <=100 && Student[i].Math_mark >=0 && Student[i].Math_mark <= 100))
		{
			system("clear");
			printf("文件格式错误！\n");
			anykey_continue();		
			return;
			
		}
		location=Student_find_location(stu_code);//查找对应学号在学生信息中的位置，
		if(-1==location)//找不到则输出一行报错;
		{
			printf("学号 %s 成绩录入失败！\n",stu_code);
			continue;
		}
		Student[location].Chinese_mark=Chinese_mark;
		Student[location].English_mark=English_mark;
		Student[location].Math_mark=Math_mark;
		printf("录入成功：%s %.1f %.1f %.1f\n",stu_code,Chinese_mark,English_mark,Math_mark);//找到了则更改成绩
		ok_num++;
		
		
	}	
	write_all_students();	//写入学生信息
	printf("本次共录入成功%d 条成绩\n",ok_num);
	anykey_continue();		
	
}


void Teacher_add_many_student(void)
{
	system("clear");
	int start_cnt=0;//已经添加的学生的最后位置
	
	start_cnt=load_all_students();
	
	char stu_code[20]={};//存放学号
	char sex;
	
	int flag=0;//记录文件中连续文本的字符数
	char ch;//暂时存放数据
	int id=0;//存放学号
	int ok_num=0;//成功写入的个数
	
	printf("开始批量导入学生，请按如下格式输入学生信息至本文件目录下的“add_student.txt”，每行一组：\n");
	printf("学生姓名 学生性别（男生输入m，女生输入w）\n");
	printf("按y继续，其他键退出\n");
	if(getch()!='y')//退出
	{
		return;
	}
	
	FILE* frp_add=fopen("add_student.txt","r");//打开记录添加学生数据的文件
	if(NULL == frp_add)
	{
		perror("fopen");
		return;
	}
	
	while(fscanf(frp_add,"%c",&ch)!=-1)//确保文件中没有大于20字节的连续字符串
	{
		if(flag>=20)
		{
			printf("文件格式非法！\n");
			anykey_continue();	
			return;
		}
		if(ch==' '||ch=='\n')
		{
			flag=0;
		}
		flag++;
	}


		FILE* fwp_tl=fopen("Student_lastcode.txt","r+");//打开存放学号的文件
		if(NULL == fwp_tl)
		{
			perror("fopen");
			return;	
		}
		
		rewind(frp_add);//将文件位置指针置于文件开头
		while(fscanf(frp_add,"%s %c\n",Student[start_cnt].name,&Student[start_cnt].sex)!=-1)//将文件中的信息写入结构体
		{
			if(Student[start_cnt].sex!='m' && Student[start_cnt].sex!='w')
			{
				printf("文件格式错误\n");
				anykey_continue();	
				return;	
			}
			
			
			
			rewind(fwp_tl);
			fscanf(fwp_tl,"%s",Student[start_cnt].code);//以字符形式读取学号到学生结构体
			
			rewind(fwp_tl);
			fscanf(fwp_tl,"%d",&id);					//以整形读取学号到id
			id++;										//学号值+1
			rewind(fwp_tl);
			fprintf(fwp_tl,"%d",id);					//重新写入学号文件以更新学号
			
			strcpy(Student[start_cnt].key,"000000");	//写入初始密码和锁定状态
			Student[start_cnt].is_clock='0';
			
			ok_num++;									//成功添加的人数+1
			if(start_cnt++ >= STU_MAX)					//是否到达人数上限
			{
				printf("请升级系统！\n");
				anykey_continue();	
				return;	
				
			}
			
		}
		
		
		//fprintf(fwp_tl,"%d",id);//写入最后一位的学号
		fclose(fwp_tl);
		fwp_tl=NULL;
		fclose(frp_add);
		frp_add=NULL;
		write_all_students();//将结构体内的数据写入文件	
		
		printf("本次共录入成功%d 位学生\n",ok_num);
		anykey_continue();	

}


void Teacher_reset_student_password(void)
{
	int i=Student_location_search();
	system("clear");
	if(-1==i)
	{
		printf("未找到该学生\n");
		sleep(1);
		return;
	}
	else
	{	
		load_all_students();
		strcpy(Student[i].key,"000000");
		Student[i].key[6]='\0';
		write_all_students();
		system("clear");
		printf("学生：%s 密码重置成功！\n",Student[i].name);
		anykey_continue();	
		
	}
}


void Teacher_show_job_student(void)
{
	system("clear");
	load_all_students();
	for(int i=0;i<STU_MAX;i++)
	{
		if(Student[i].sex=='m'||Student[i].sex=='w')
		{
			printf("\n 序号：%d\n 学号：%s\n 姓名：%s\n 性别：%s\n 语文成绩：%.1f\n 英语成绩：%.1f\n 数学成绩：%.1f\n",i,Student[i].code,Student[i].name,'w'==Student[i].sex?"女":"男",Student[i].Chinese_mark,Student[i].English_mark,Student[i].Math_mark);
		}
		else
		{
			break;
		}
		
		
	}
	anykey_continue();		
	
}


void Teacher_show_quit_student(void)
{
	system("clear");
	printf("找到如下退学学生：\n");
	FILE* frp_qi=fopen("Student_quit_information.txt","r");
	Stu Student_quit={};
	if(NULL == frp_qi)
	{
		perror("fopen");
		return;
	}
	for(int i=0;i<STU_MAX;i++)
	{
		if(-1 == fscanf(frp_qi,"%s %s %c\n",Student_quit.code,Student_quit.name,&Student_quit.sex))
		{
			break;
		}
		printf("%s %s %s\n",Student_quit.code,Student_quit.name,'w'==Student_quit.sex?"女":"男");
	}
	fclose(frp_qi);
	frp_qi=NULL;
	anykey_continue();	
	
}
//	三次密码错误锁定帐号
void Teacher_lock_account(int j,FILE *fp)
{
	if(cnt > 0)
	{
		printf("还剩%d次机会\n",cnt);
	}
	else
	{
		printf("帐号已锁定，请联系校长解锁\n");
		cnt = 3;
		Teacher[j].is_clock=1;
		fseek(fp,-(strlen(Teacher[j].code)+strlen(Teacher[j].key)+4),SEEK_CUR);
		fprintf(fp,"%hhd",Teacher[j].is_clock);
	}
}


//	修改密码
void Teacher_change_password(void)
{
	system("clear");
	//debug("%s\n",__func__);
	printf("请输入要修改的密码\n");
	//strcpy(Student[i].key,"000000");
	Teacher_password_change(i);
}

void Teacher_unlock_student_account(void)
{
	int i=Student_location_search();
	system("clear");
	if(-1==i)
	{
		printf("未找到该学生\n");
		sleep(1);
		return;
	}
	else
	{	
		load_all_students();
		Student[i].is_clock='0';
		write_all_students();
		printf("\n学生：%s 解锁成功！\n",Student[i].name);
		anykey_continue();	
		
	}
}

