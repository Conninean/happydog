#ifndef TEACHER_FUNC_H
#define TEACHER_FUNC_H

int Teacher_login_forced_password_change(void);//教师第一次登录修改密码

void Teacher_change_password(void);//从主界面进入密码修改
void Teacher_view_personal_information(void);//教师查看个人信息
void Teacher_add_one_student(void);//添加单个学生
void Teacher_add_many_student(void);//批量添加学生
void Teacher_del_student(void);//删除学生 （把学号置为xxxxxx）
void Teacher_find_student(void);// 查找学生 
void Teacher_change_student_message(void);//  修改学生信息 
void Teacher_input_student_score(void);//       录入学生成绩  
void Teacher_input_one_student_score(void);//       批量录入学生成绩  
void Teacher_input_many_student_score(void);//       批量录入学生成绩  
void Teacher_reset_student_password(void);//   重置学生密码 
void Teacher_show_job_student(void);//         显示所有学生信息 
void Teacher_show_quit_student(void);//     显示所有退出学生信息 
void Teacher_lock_account(int j,FILE *fp);//    三次密码错误锁定帐号
void Teacher_unlock_student_account(void);	//	解锁学生账号
 

#endif
