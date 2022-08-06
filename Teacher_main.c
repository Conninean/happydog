#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include "Teacher_func.h"
#include "Teacher_main.h"


int Teacher_main(void)
{
	system("clear");
	if(!Teacher_login_forced_password_change())
	{
		return 0;
	}
	for(;;)
	{
		//	显示主界面
		switch(Teacher_menu())
		{
			case '1':Teacher_change_password(); 		break;	//修改密码
			case '2':Teacher_view_personal_information(); break;	//查看个人信息
			case '3':Teacher_add_one_student(); 		break;	//添加学生
			case 'a':Teacher_add_many_student(); 		break;	//批量添加学生
			case '4':Teacher_del_student(); 			break;	//删除学生
			case '5':Teacher_find_student(); 			break;//查找学生
			case '6':Teacher_change_student_message();	break;//修改学生信息
			case '7':Teacher_input_student_score();	 	break;//录入学生成绩
			case '8':Teacher_reset_student_password(); 	break;//重置学生密码
			case '9':Teacher_show_job_student();	 	break;//显示所有学生信息
			case 't':Teacher_show_quit_student();		break;
			case 'k':Teacher_unlock_student_account();  break;
			case '0':	return 0;//退出登录
		}	
		sleep(1);
	}
	return 0;
}

