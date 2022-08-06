#include <stdio.h>
#include <getch.h>
#include <string.h>
#include "Master_func.h"
#include "tools.h"
#include <stdlib.h>
#include "Master_main.h"
#include "main.h"


int Master_main(void)
{
	if(0 == init_M())
		return 0;
	for(;;)
	{
		
		if(Master_password_compare())//提示输入密码并与文件中的密码进行比较，相同返回1,不同返回0
		{
			Master_first_password_change();
			break;
		}
		printf("\n密码错误,请重新输入(按q退出，其他键继续):\n");
		if(getch()=='q')
		{
			return 0;
		}
	}
	for(;;)
	{
		switch(Master_menu())
		{
			case '1': Master_reset_master_self_password(); 		break;	
			case '2': Master_reset_teacher_password(); 			break;	
			case '3': Master_add_teacher(); 					break;	
			case '4': Master_del_teacher();						break;	
			case '5': Master_show_job_teacher();				break;	
			case '6': Master_show_quit_teacher();				break;	
			case '7': Master_unlock_teacher_account();			break;	
			case '8': return 0;
		}
		sleep(1);
	}
}
