#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "main.h"
#include "tools.h"
#include "Student_main.h"
#include "Master_main.h"
#include "Teacher_main.h"

Stu *Student =NULL;
Tea *Teacher =NULL;
int main(int argc,const char* argv[])
{
	Student = calloc(sizeof(Stu),STU_MAX);
	Teacher = calloc(sizeof(Stu),STU_MAX);
	
	for(;;)
	{
		switch(Start_menu())
		{
			case 49:Master_main();break;
			case 50:Teacher_main();break;
			case 51:Student_main();break;
			default:printf(" :) \n"); sleep(1);break;
		}
	}

}
