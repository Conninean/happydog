#ifndef STUDENT_FUNC_H
#define STUDENT_FUNC_H

#include <stdio.h>


//	第一次登录强制修改密码
int Student_login_forced_password_change(void);

//	查询成绩
void Student_query_results(void);

//	修改密码
void Student_change_password(void);

//	查看个人信息
void Student_view_personal_information(void);

//	三次密码错误锁定帐号
void Student_lock_account(FILE* fp);

//	排序
float *sort(float* s,int len);

#endif//STUDENT_FUNC_H
