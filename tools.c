#include <stdio.h>
#include <getch.h>
#include <stdlib.h>
#include "tools.h"
#include "main.h"




//	显示开始界面
int Start_menu(void)
{
	system("clear");
	printf("\33[01;44m        欢迎学校信息管理系统        \33[00m\n");
    printf("\33[01;33m             1、校长              \33[00m\n");
    printf("\33[01;33m             2、教师              \33[00m\n");
    printf("\33[01;33m             3、学生              \33[00m\n");
    printf("\33[01;45m         请选择您的登入方式         \33[00m\n");
	int cmd = getch();

	return cmd;
}

//	显示学生界面
int Student_menu(void)
{
	system("clear");
	printf("\33[01;44m        欢迎学校信息管理系统        \33[00m\n");
    printf("\33[01;33m           1、查询成绩             \33[00m\n");
    printf("\33[01;33m           2、修改密码             \33[00m\n");
    printf("\33[01;33m           3、查看个人信息          \33[00m\n");
    printf("\33[01;33m           4、退出                 \33[00m\n");
	printf("请输入指令:");
	char cmd = getch();
	printf("%c\n",cmd);		//	回显
	return cmd;
}

//	打印提示信息
void msg_show(const char* msg,float sec)
{
	printf("%s",msg);
	fflush(stdout);		//	刷新输出缓存区
	usleep(sec*100000);	//	sec以秒为单位
}


//	按任意键继续
void anykey_continue(void)
{
	puts("按任意键继续...");
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	getch();
}



//检测人数
int how_many(char* filename)
{
	char i_c;
	char id[20];
	char key[20];
	int  cnt = 0;
	FILE* fwp_hm=fopen(filename,"r");
	if(NULL == fwp_hm)
	{
		perror("fopen");
		return -1;	
	}
	for(;;)
	{
		fscanf(fwp_hm,"%c %s %s\n",&i_c,id,key);
		if(-1 == fscanf(fwp_hm,"%c %s %s",&i_c,id,key))
		{
			fclose(fwp_hm);
			return cnt;
		}
		else
		{
			cnt++;
		}
	}
}


//更改第j个学生的密码
void Student_password_change(int j)
{
	FILE* frp = fopen("Student_password.txt","r+");		//	打开存放学生密码的文件
	if(NULL == frp)		//	判断文件是否被打开
	{
		perror("fopen");	//	记录错误信息
		return;	
	}
	int k=0;
	for(;k<STU_MAX;k++)	//	读取文件中所有信息到结构中
	{
		if(-1==fscanf(frp,"%c %s %s\n",&Student[k].is_clock,Student[k].code,Student[k].key))
		{
			break;
		}
	}
	fclose(frp);		//	关闭存放学生信息的文件
	char pass_w[20]={}; 	//	存放旧变量密码
	char pass_w_t[20]={};	//	存放二次输入的密码
	strcpy(pass_w,Student[j].key);	//	备份旧密码
	
	for(;;)				//	进行密码长度的判断
	{
	
		if(strcmp(Student[j].key,"000000"))
		{
			printf("\n按q退出,其他键继续:\n");				//	退出学生登录操作
			if('q'== getch())
			{
				return;
			}
		}
		conceal(20,Student[j].key);	//	输入要修改的密码
		if(!strcmp(Student[j].key,"000000") || !strcmp(Student[j].key,pass_w))
		{
			printf("\n修改的密码不能和初始密码或旧密码相同\n");
			continue;
		}	
		if(strlen(Student[j].key) < 6 )
		{
			printf("密码长度有误，请重新输入");
		}
		else
		{
			printf("\n二次确认\n");
			conceal(20,pass_w_t);
			if(!strcmp(Student[j].key,pass_w_t))
			{
				break;
			}
			else
			{
				printf("\n重新输入\n");
				continue;
			}
		}
	}
	FILE* fwp = fopen("Student_password.txt","w");	//	打开存放学生信息的文件并清空
	if(NULL == fwp)		//	判断文件是否被打开
	{
		perror("fopen");	//	记录错误信息
		return;	
	}
	for(int t=0;t<k;t++)	//	将结构中的所有信息全部写入文件
	{
		fprintf(fwp,"%c %s %s\n",Student[t].is_clock,Student[t].code,Student[t].key);
	}
	anykey_continue();	
	fclose(fwp);
}


//更改第j个教师的密码
void Teacher_password_change(int j)
{
	FILE* frp = fopen("Teacher_password.txt","r+");
	if(NULL == frp)
	{
		perror("fopen");
		return;	
	}
	int k=0;
	for(;k<STU_MAX;k++)
	{
		if(-1==fscanf(frp,"%c %s %s\n",&Teacher[k].is_clock,Teacher[k].code,Teacher[k].key))
		{
			break;
		}
	}
	fclose(frp);
	char pass_w[20]={}; 	//	存放旧变量密码
	char pass_w_t[20]={};	//	存放二次输入的密码
	strcpy(pass_w,Teacher[j].key);	//	备份旧密码
	FILE* fwp = fopen("Teacher_password.txt","w");
	if(NULL == fwp)
	{
		perror("fopen");
		return;	
	}
	for(;;)
	{
		conceal(20,Teacher[j].key);	
		if(!strcmp(Teacher[j].key,"000000"))
		{
			printf("\n修改的密码不能和初始密码相同\n");
			continue;
		}	
		else if(strlen(Teacher[j].key) < 6 || strlen(Teacher[j].key) >19)
		{
			printf("密码长度有误，请重新输入(7-18位)");
		}
		else
		{
			printf("\n二次确认\n");
			conceal(20,pass_w_t);
			if(!strcmp(Teacher[j].key,pass_w_t))
			{
				break;
			}
			else
			{
				printf("\n两次输入的密码不同，请重新输入\n");
				continue;
			}
		}
	}
	for(int t=0;t<k;t++)
	{
		fprintf(fwp,"%c %s %s\n",Teacher[t].is_clock,Teacher[t].code,Teacher[t].key);
	}
	fclose(fwp);
	printf("修改成功！\n");
	sleep(1);
}


//	隐藏密码
void conceal(int len,char *password)
{
	int x = 0;
	char c=0;
	printf("请输入密码\n");
	while(c != 10)   //10是回车符的ASCII码
	{
		stdin->_IO_read_ptr = stdin->_IO_read_end;
	 	c = getch();
	 	stdin->_IO_read_ptr = stdin->_IO_read_end;
		password[x++] = c;
	    if(c == 10)
		{
	    	break;
	    }
	    else if(c == 127&&x>=2)
	    {
	    	
	    	putchar('\b');
	    	putchar(' ');
	    	putchar('\b');
	    	x-=2;
	    }
	    else if(x==len-1)
	    {
	    	x--;
	    	continue;
	    }
	    else if(c == 127)
		{
	    	x--;
	    }
	    else
	    {
	    	putchar('*');
	    }
	}		
	x--; 
	password[x] = '\0';
	//printf("%s\n",password);
}


//	输入账号
void enter_account(int len,char *password)
{
	int x = 0;
	char c ;
	printf("\n请输入账号\n");
	while(c != 10)   //10是回车符的ASCII码
	{
		stdin->_IO_read_ptr = stdin->_IO_read_end;
	 	c = getch();
		password[x++] = c;
		if(c == 10)
		{
	    	break;
	    }
	    else if(c == 127&&x>=2)
	    {
	    	
	    	putchar('\b');
	    	putchar(' ');
	    	putchar('\b');
	    	x-=2;
	    }
	    else if(x==len-1)
	    {
	    	x--;
	    	continue;
	  		//putchar((int)c);
	    }
	   else if(c == 127)
		{
	    	x--;
	    }
	    else
	    {
	    	putchar(c);
	    }
	}		
	x--; 
	password[x] = '\0';
}

//	输入NAME
void enter_name(int len,char *password)
{
	int x = 0;
	char c ;
	printf("请输入NAME\n");
	while(c != 10)   //10是回车符的ASCII码
	{
		stdin->_IO_read_ptr = stdin->_IO_read_end;
	 	c = getch();
		password[x++] = c;
		if(c == 10)
		{
	    	break;
	    }
	    else if(c == 127&&x>=2)
	    {
	    	
	    	putchar('\b');
	    	putchar(' ');
	    	putchar('\b');
	    	x-=2;
	    }
	    else if(x==len-1)
	    {
	    	x--;
	    	continue;
	  		//putchar((int)c);
	    }
	   else if(c == 127)
		{
	    	x--;
	    }
	    else
	    {
	    	putchar(c);
	    }
	}		
	x--; 
	password[x] = '\0';
}


char Master_Pass[20];

//显示界面
int Master_menu(void)
{
	system("clear");
	printf("\33[01;44m        欢迎学校信息管理系统        \33[00m\n");
	printf("\33[01;45m             尊敬的校长            \33[00m\n");
    printf("\33[01;33m           1、重置个人密码          \33[00m\n");
    printf("\33[01;33m           2、重置教师密码          \33[00m\n");
    printf("\33[01;33m           3、添加教师             \33[00m\n");
    printf("\33[01;33m           4、删除教师             \33[00m\n");
    printf("\33[01;33m           5、显示在职教师          \33[00m\n");
    printf("\33[01;33m           6、显示离职教师          \33[00m\n");
    printf("\33[01;33m           7、解锁教师账号          \33[00m\n");
    printf("\33[01;33m           8、退出系统              \33[00m\n");
	printf("请输入指令:");
	char cmd = getch();
	printf("%c\n",cmd);		
	return cmd;
}
//读取校长密码
char* init_M(void)
{
	FILE* frp_mp=fopen("Master_password.txt","r");
	if(NULL == frp_mp)
	{
		perror("fopen");
		return NULL;
	}
	fscanf(frp_mp,"%s",Master_Pass);
	fclose(frp_mp);
	return Master_Pass;
}


int Teacher_location_search(void)
{
	system("clear");
	char num[20];
	printf("请输入教师的工号:");
	for(;;)
	{
		if(-1==limit_input(10,num))
		{
			stdin->_IO_read_ptr = stdin->_IO_read_end;
			system("clear");
			printf("教师工号过长，请重新输入\n");
			return -1;
		}	
		else
		{
			break;
		}
	}

	FILE* fwp_tp=fopen("Teacher_password.txt","r");
	if(NULL == fwp_tp)
	{
		perror("fopen");
		return 0;
	}
	for(int i=0;i<TEA_MAX;i++)
	{
		if(-1 == fscanf(fwp_tp,"%c %s %s\n",&Teacher[i].is_clock,Teacher[i].code,Teacher[i].key))
		{
			break;
		}
		if(0 == strcmp(num,Teacher[i].code))
		{
			Teacher_password_reset(i,1);
			return i;	
		}
	}
	return -1;
}

int Student_location_search(void)
{
	system("clear");
	printf("请输入学生的学号:");
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	char num[20];
	if(-1==limit_input(10,num))
	{
		return -1;
	}
	
	FILE* fwp_tp=fopen("Student_password.txt","r");
	if(NULL == fwp_tp)
	{
		perror("fopen");
		return 0;
	}
	for(int i=0;i<TEA_MAX;i++)
	{
		if(-1 == fscanf(fwp_tp,"%c %s %s\n",&Student[i].is_clock,Student[i].code,Student[i].key))
		{
			break;
		}
		if(0 == strcmp(num,Student[i].code))
		{
			return i;	
		}
	}
	return -1;
}

int Student_find_location(char* code)
{
	FILE* fwp_tp=fopen("Student_password.txt","r");
	if(NULL == fwp_tp)
	{
		perror("fopen");
		return 0;
	}
	for(int i=0;i<TEA_MAX;i++)
	{
		if(-1 == fscanf(fwp_tp,"%c %s %s\n",&Student[i].is_clock,Student[i].code,Student[i].key))
		{
			break;
		}
		if(0 == strcmp(code,Student[i].code))
		{
			return i;	
		}
	}
	return -1;
}


int load_all_students(void)
{
	FILE* frp_ji=fopen("Student_job_information.txt","r");
	FILE* frp_sp=fopen("Student_password.txt","r");
	memset(&Student[0],0,sizeof(Student)*STU_MAX);//将学生结构体置空
	if(NULL == frp_ji)
	{
		perror("fopen");
		return 0;
	}
	int i=0;
	for(i=0;i<STU_MAX;i++)
	{
		if(-1 == fscanf(frp_ji,"%s %s %c %f %f %f\n",Student[i].code,Student[i].name,&Student[i].sex,&Student[i].Chinese_mark,&Student[i].English_mark,&Student[i].Math_mark))
		{
			break;
		}
		
		if(-1 == fscanf(frp_sp,"%c %s %s\n",&Student[i].is_clock,Student[i].code,Student[i].key))
		{
			break;
		}
	}
	
	fclose(frp_ji);
	fclose(frp_sp);
	return i;
	
}


void write_all_students(void)
{
	FILE* fwp_ji=fopen("Student_job_information.txt","w");
	FILE* fwp_sp=fopen("Student_password.txt","w");
	if(NULL == fwp_ji)
	{
		perror("fopen");
		return;
	}
	for(int i=0;i<STU_MAX;i++)
	{
		if(Student[i].sex=='w'||Student[i].sex=='m')
		{
			fprintf(fwp_ji,"%s %s %c %f %f %f\n",Student[i].code,Student[i].name,Student[i].sex,Student[i].Chinese_mark,Student[i].English_mark,Student[i].Math_mark);
			
			fprintf(fwp_sp,"%c %s %s\n",Student[i].is_clock,Student[i].code,Student[i].key);
		}
		else
		{
			break;		
		}
		
	}
	fclose(fwp_ji);
	fclose(fwp_sp);
	
}
//判断密码
bool Master_password_compare(void)
{
	char str[20] = {};
	system("clear");
	conceal(20,str);
	if(NULL == init_M())
	{
		return 0;
	}
	if(0==strcmp(str,init_M()))
	{
		printf("密码正确!\n");
		return true;
	}
	else
	{
		
		return false;
	}
}


//mode=1重置密码，mode=2解除锁定
void Teacher_password_reset(int j,int mode)
{
	FILE* frp = fopen("Teacher_password.txt","r+");
	if(NULL == frp)
	{
		perror("fopen");
		return;	
	}
	int k=0;
	for(;k<TEA_MAX;k++)
	{
		if(-1==fscanf(frp,"%c %s %s\n",&Teacher[k].is_clock,Teacher[k].code,Teacher[k].key))
		{
			break;
		}
	}
	fclose(frp);
	FILE* fwp = fopen("Teacher_password.txt","w");
	if(NULL == fwp)
	{
		perror("fopen");
		return;	
	}
	switch(mode)
	{
		case 1: strcpy(Teacher[j].key,"000000"); break;
		case 2: Teacher[j].is_clock = '0'; 	     break;
	}
	for(int t=0;t<k;t++)
	{
		fprintf(fwp,"%c %s %s\n",Teacher[t].is_clock,Teacher[t].code,Teacher[t].key);
	}
	fclose(fwp);
}


//	teacher显示界面
int Teacher_menu(void)
{
	system("clear");
	printf("\33[01;44m        欢迎学校信息管理系统        \33[00m\n");
	printf("\33[01;45m             尊敬的老师             \33[00m\n");
    printf("\33[01;33m           1、重置个人密码          \33[00m\n");
    printf("\33[01;33m           2、查看个人信息          \33[00m\n");
    printf("\33[01;33m           3、添加学生             \33[00m\n");
    printf("\33[01;33m           a、批量添加学生          \33[00m\n");
    printf("\33[01;33m           4、删除学生              \33[00m\n");
    printf("\33[01;33m           5、查找学生              \33[00m\n");
    printf("\33[01;33m           6、修改学生信息          \33[00m\n");
    printf("\33[01;33m           7、录入学生成绩          \33[00m\n");
    printf("\33[01;33m           8、重置学生密码          \33[00m\n");
    printf("\33[01;33m           9、显示在校学生信息       \33[00m\n");
    printf("\33[01;33m           t、显示退学学生信息       \33[00m\n");
    printf("\33[01;33m           k、解锁学生              \33[00m\n");
    printf("\33[01;33m           0、退出登录              \33[00m\n");
	printf("请输入指令:");
	char cmd = getch();
	printf("%c\n",cmd);		//	回显
	return cmd;
}


//输入已删除在职教师位置，移入离职教师文件
void del_Teacher(int i)
{
	if(i==-1)
	{
		printf("未找到该教师：(\n");
		anykey_continue();		
		return;
	}
	FILE* frp_ji = fopen("Teacher_job_information.txt","r+");	//打开在职教师信息文件
	if(NULL == frp_ji)
	{
		perror("fopen");
		return;	
	}
	FILE* frp_p = fopen("Teacher_password.txt","r+");//打开在职教师密码文件
	if(NULL == frp_p)
	{
		perror("fopen");
		return;	
	}
	FILE*  frp_qi = fopen("Teacher_quit_information.txt","r+");//打开离职教师信息文件
	if(NULL == frp_qi)
	{
		perror("fopen");
		return;	
	}
	int k=0;
	for(;k<TEA_MAX;k++)//重新导入教师数据至Teacher结构体，k表示在职教师总人数
	{
		if(-1==fscanf(frp_p,"%c %s %s\n",&Teacher[k].is_clock,Teacher[k].code,Teacher[k].key) || -1 == fscanf(frp_ji,"%s %s %c",Teacher[k].code,Teacher[k].name,&Teacher[k].sex))
		{
			break;
		}
		printf("d1:%s %s %c\n",Teacher[k].code,Teacher[k].name,Teacher[k].sex);
	}
	fclose(frp_p);
	fclose(frp_ji);
	frp_p = fopen("Teacher_password.txt","w");//清空两个在职教师相关文件
	frp_ji = fopen("Teacher_job_information.txt","w");
	rewind(frp_p);
	rewind(frp_ji);
	for(int j=0;j<k;j++)
	{
		if(j!=i)//重新写入除了要删除教师之外的教师
		{
			fprintf(frp_ji,"%s %s %c\n",Teacher[j].code,Teacher[j].name,Teacher[j].sex);
			fprintf(frp_p,"%c %s %s\n",Teacher[j].is_clock,Teacher[j].code,Teacher[j].key);
		}	
	}
	
	fclose(frp_p);
	fclose(frp_ji);
	fseek(frp_qi,0,SEEK_END);// 把离职教师的文件指针放到末尾
	fprintf(frp_qi,"%s %s %c\n",Teacher[i].code,Teacher[i].name,Teacher[i].sex);
	fclose(frp_qi);
	system("clear");
	printf("删除成功！\n");
	void anykey_continue(void);		
}

int limit_input(int len,char *str)
{
	int i=0;
	for(i=0;i<len;i++)
	{
		str[i]=getchar();
		if(str[i] == ' ' || str[i] == '\n')
		{
			str[i]='\0';
			break;
		}
	}	
	if(i==len)
	{
		return -1;		
	}
	else
	{
		return i;
	}
}

