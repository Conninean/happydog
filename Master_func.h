#ifndef MASTER_FUNC_H
#define MASTER_FUNC_H


void Master_first_password_change(void);					//第一次登录强制修改密码
void Master_reset_master_self_password(void);				//重置自己的密码
void Master_reset_teacher_password(void);					//重置教师密码
void Master_add_teacher(void);								//添加教师
void Master_del_teacher(void);								//删除教师
void Master_show_job_teacher(void);							//显示所有在职教师
void Master_show_quit_teacher(void);						//显示所有离职教师
void Master_unlock_teacher_account(void);					//由校长解锁教师账号

#endif//MASTER_FUNC_H
