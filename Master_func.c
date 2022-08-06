#include <stdio.h>
#include "Master_func.h"
#include "tools.h"
#include <string.h>
#include <stdlib.h>
#include "Master_main.h"

extern Tea *Teacher;
//第一次登录强制修改密码
void Master_first_password_change(void)
{
	char new_password[20];
	if(!(strcmp(init_M(),"000000")))//读取校长密码,与初始密码比较
	{
		system("clear");
		printf("这是第一次登录，请设置您的密码(6-20位，不可与初始密码“000000”相同):\n");
		anykey_continue();	
		
		for(;;)
		{
			system("clear");
			conceal(20,new_password);	//调用密码格式判断函数进行检查密码输入的格式
			if(strlen(new_password)>=6 && strcmp(new_password,"000000"))//判断密码格式是否符合规范
			{
				break;
			}
			else
			{
				system("clear");
				printf("密码格式错误(6-20位，不可与初始密码“000000”相同)，请重新输入\n");
				anykey_continue();	
			}
		}
		
		FILE* fwp_mp=fopen("Master_password.txt","w");//清空存放校长密码的文件
		if(NULL == fwp_mp)
		{
			perror("fopen");
			return;	
		}
		fprintf(fwp_mp,"%s",new_password);//写入新密码
		fclose(fwp_mp);
	}

}
//重置自己的密码
void Master_reset_master_self_password(void)
{
	char old_password[20]={};
	char new_password1[20]={}; 
	char new_password2[20]={}; 
	char Master_pass[20]={};
	FILE* fwp_mp=fopen("Master_password.txt","r+"); //打开校长密码文本
	if(NULL == fwp_mp)
	{
		perror("fopen");
		return;	
	}
	fscanf(fwp_mp,"%s",Master_pass);
	system("clear");
	for(;;)
	{	
		
		stdin->_IO_read_ptr = stdin->_IO_read_end;
		conceal(20,old_password);					
		if(0 != strcmp(old_password,Master_pass))	//对比文本密码
		{
			printf("\n当前密码错误请重新输入(输入q退出!)\n");
			if(0 == strcmp(old_password,"q"))		//判断是否退出该项功能
			{
				return;
			}
		}
		else 
		{
			system("clear");
			printf("校验成功，请输入您的新密码\n");
			break;
		}
	}
	for(;;)
	{
		conceal(20,new_password1);
		if(!strcmp(new_password1,"000000"))		//对比初始密码
		{
			printf("\n当前密码与初始密码相同请重新输入(输入q退出!)\n");
			continue;
		}
		if(0 == strcmp(new_password1,"q"))		//判断是否退出该项功能
		{
			return;
		}
		
		if(0 == strcmp(new_password1,old_password)) //与旧密码对比
		{
			printf("\n与旧密码相同(输入q退出!)\n");
			continue;
		}
		if(strlen(new_password1)<6)					//判断过短格式
		{
			printf("输入格式过短(至少六位,输入q退出!)\n");
			continue;
		}
		if(strlen(new_password1)>=6)				//判断格式		
		{
			printf("\n请二次确认再次");
		}
		conceal(20,new_password2);
		if(0 == strcmp(new_password1,new_password2))	//二次确认密码
		{									
			fclose(fwp_mp);
			fwp_mp=fopen("Master_password.txt","w");//打开教师密码文本
			fprintf(fwp_mp,"%s",new_password2);
			//system("clear");
			msg_show("\n修改成功!\n",2);
			fclose(fwp_mp);
			return;
		}
		else
		{
			printf("\n输入错误重新确认(输入q退出!)\n");
		}
	}
}
//重置教师密码
void Master_reset_teacher_password(void)
{	
	int num = Teacher_location_search();	//使用教师位置查找函数进行查找返回-1查找失败成功执行该函数第一项赋值功能
	if(-1 == num)							
	{
		msg_show("查无此人!\n",2);
		return;	
	}
	else
	{
			msg_show("重置成功!\n",2);
			Teacher_password_reset(num,1);//执行教师密码重置函数第一项开关赋值密码为"000000"
	}
}
//添加教师
void Master_add_teacher(void)
{
	int id;
	char name[100]={};
	char sex;
	FILE* fwp_tj=fopen("Teacher_job_information.txt","r+");//打开在职教师文本
	if(NULL == fwp_tj)
	{
		perror("fopen");
		return;	
	}
	system("clear");
	printf("请输入教师的姓名 性别:\n");
	for(;;)
	{
		for(;;)
		{
			if(limit_input(19,name)==-1)	//使用字符串限定函数进行输入工号长度限定
			{
				stdin->_IO_read_ptr = stdin->_IO_read_end;
				system("clear");
				printf("教师名过长请重新输入\n");			
			}
			else
			{
				break;
			}
		}
		sex=getchar();						//使用字符串限定函数进行输入性别长度限定
		if('w' == sex || 'm' == sex)
		{
			if(getchar()=='\n')				//判断输入性别格式是否合法	
			{
				break;
			}
			else
			{
				printf("\n您输入的格式有误请重新输入:\n");
			}
		}
		else
		{
			printf("\n您输入的格式有误请重新输入:\n");
		}
	}
	FILE* fwp_tl=fopen("Teacher_lastcode.txt","r+");//打开教师工号自加文本
	if(NULL == fwp_tl)
	{
		perror("fopen");
		return;	
	}
	fscanf(fwp_tl,"%d",&id);id++;				//每次读取往后自加工号
	fclose(fwp_tl);
	fwp_tl=fopen("Teacher_lastcode.txt","w");
	if(NULL == fwp_tl)
	{
		perror("fopen");
		return;	
	}
	fprintf(fwp_tl,"%d",id);
	fclose(fwp_tl);
	fseek(fwp_tj,0,SEEK_END);
	fprintf(fwp_tj,"%d %s %c\n",id,name,sex);//使用自加工号文本自动对添加的教师工号赋值
	fclose(fwp_tj);
	FILE* fwp_tp=fopen("Teacher_password.txt","r+");//打开教师密码文本
	if(NULL == fwp_tp)
	{
		perror("fopen");
		return;	
	}
	fseek(fwp_tp,0,SEEK_END);
	fprintf(fwp_tp,"%c %d %s\n",'0',id,"000000");//同时对教师密码文本工号赋值
	fclose(fwp_tp);
	msg_show("录入成功!\n",1);
}



//删除教师
void Master_del_teacher(void)
{
	del_Teacher(Teacher_location_search());//使用教师查找函数的返回值作为删除教师函数的参数 全部读取出来进行对该教师的移除重新写入 具体可移步tools.c介绍
}


//显示所有在职教师
void Master_show_job_teacher(void)
{	
	FILE* fwp_ji=fopen("Teacher_job_information.txt","r+");//打开在职教师文本
	if(NULL == fwp_ji)
	{
		perror("fopen");
		return;	
	}
	system("clear");
	for(int i=0;i<256;i++)		//遍历在职教师文档
	{	
		if(-1 == fscanf(fwp_ji,"%s %s %c",Teacher[i].code,Teacher[i].name,&Teacher[i].sex))			//判断是否到达文本末尾
		{
			break;
		}
		printf("%s %s %s\n",Teacher[i].code,'w'==Teacher[i].sex?"女":"男",Teacher[i].name);							//打印所有遍历到的教师名单
	}
	fclose(fwp_ji);
	anykey_continue();
}
//显示所有离职教师
void Master_show_quit_teacher(void)
{
	FILE* fwp_qi=fopen("Teacher_quit_information.txt","r+");//打开离职教师文本
	system("clear");
	if(NULL == fwp_qi)
	{
		perror("fopen");
		return;	
	}
	for(int i=0;i<256;i++)		//遍历离职教师文档
	{
		if(-1 == fscanf(fwp_qi,"%s %s %c",Teacher[i].code,Teacher[i].name,&Teacher[i].sex))			//判断是否到达末尾
		{
			break;
		}
		printf("%s %s %s\n",Teacher[i].code,Teacher[i].name,'w'==Teacher[i].sex?"女":"男");					//打印所有遍历到的教师名单
	}
	fclose(fwp_qi);
	anykey_continue();
}
//由校长解锁教师账号
void Master_unlock_teacher_account(void)
{
	int num = Teacher_location_search();	//使用教师查找函数返回值给num赋值
	system("clear");
	if(-1 == num)							//函数返回值为-1时并未找到该教师
	{
		msg_show("查无此人!\n",2);
		return;	
	}
	else
	{
		printf("解锁成功\n");
		anykey_continue();
		Teacher_password_reset(num,2);	//查找成功使用教师密码重置函数第二项开关给其赋值为'0'
	}
}
