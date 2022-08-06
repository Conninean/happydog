#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include "Student_func.h"
#include "main.h"


int Student_main(void)
{
	system("clear");
	
	if(1==Student_login_forced_password_change())
	{
		return 0;
	}
	for(;;)
	{
		//	显示主界面
		switch(Student_menu())
		{
			case '1':	Student_query_results(); break;	
			case '2':	Student_change_password(); break;	
			case '3':	Student_view_personal_information(); break;		
			case '4':	return 0;
		}	
	}
}
