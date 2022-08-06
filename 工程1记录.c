 项目：
        项目介绍（10）
            设计思路、分工、文档、PPT
            一、设计思路：经过分析，想要实现该系统的功能
                1、需要如下函数：
                    教师：
                        1、添加学生函数 Teacher_add_student()
                        2、删除学生 Teacher_del_student()
                        3、查找学生 Teacher_find_student()
                        4、修改学生信息 Teacher_change_student_message()
                        5、录入学生成绩  Teacher_input_student_score
                        6、重置学生密码 Teacher_reset_student_password
                        7、显示所有学生信息 Teacher_show_job_student
                        9、显示所有退出学生信息 Teacher_show_quit_student
                        10、三次密码错误锁定帐号，Teacher_lock_teacher_account
        
                    校长：
                        1、第一次登录强制修改密码。  Master_first_ password_change
                        2、能重置自己的密码     Master_reset_master_self_password
                        3、能重置教师密码       Master_reset_teacher_password

                        4、添加教师            Master_add_teacher
                                创建一个记录在职教师文档
                        5、删除教师             Master_del_teacher
                                创建一个记录离职教师文档
                        6、显示所有在职教师     Master_show_job_teacher
                                打印在职教师文档
                        7、显示所有离职教师     Master_show_quit_teacher
                                打印离职教师文档
                    
                        8、由校长解锁教师账号 Master_unlock_teacher_account

                    学生：
                        1、第一次登录强制修改密码。              Student_login_forced_password_change
                        2、查询成绩                              Student_query_results
                        3、修改密码                             Student_change_Password
                        4、查看个人信息                          Student_view_personal_information
                        5、三次密码错误锁定帐号，由教师解锁      Student_lock_account


                    在后续编程中，添加了如下工具函数：
                        void anykey_continue(void);					//按任意键继续
                        void msg_show(const char* msg,float sec);	//打印提示信息
                        void anykey_continue(void);					//按任意键继续
                        void conceal(int len,char *password);		//输入时显示“*”，并限制输入长度
                        void enter_account(int len,char *password);	//限制输入长度
                        int how_many(char* filename);				//检测人数


                        int Start_menu(void);						//开始界面
                        int Student_menu(void);						//显示学生界面
                        int Master_menu(void);						//显示校长界面
                        int Teacher_menu(void);						//显示教师界面


                        void Student_password_change(int j);		//更改第j行学生的密码
                        int Student_location_search(void);			//提示输入学生学号，读取学生数据至结构体并返回学生位置，没有找到返回-1
                        void load_all_students(void);				//重新载入所有在校学生数据
                        void write_all_students(void);				//写入所有在校学生数据

                        void Teacher_password_change(int j);		//更改第j行teacher的密码
                        int  Teacher_location_search(void);			//提示输入教师工号，返回教师位置，没有找到返回-1
                        void Teacher_password_reset(int j,int mode);//输入教师位置和模式，mode=1重置教师密码，mode=2解除教师锁定
                        void del_Teacher(int i);					//输入已删除在职教师位置，移入离职教师文件

                        bool Master_password_compare(void);			//判断初始化密码
                        char *init_M(void);							//返回校长密码

                2、需要如下文件来保存数据：
                        1、Master_password.txt//存放校长密码(唯一)
                        2、Teacher_password.txt//存放格式 每行 "是否被锁定 教师工号 密码"
                        3、Student_password.txt//存放格式 每行 "是否被锁定 学生学号 密码"

                        4、Teacher_job_information.txt//存放在职教师信息 格式每行 "工号 姓名 性别"
                        5、Student_job_information.txt//存放在校学生信息 格式每行 "学号 姓名 性别 语文成绩 数学成绩 英语成绩"

                        6、Teacher_quit_information.txt//存放力职教师信息 格式每行 "工号 姓名 性别"
                        7、Student_quit_information.txt//存放离校学生信息 格式每行 "学号 姓名 性别 语文成绩 数学成绩 英语成绩"
                        
                        8、Student_lastcode.txt//存放最后一个学生学号
                        9、Teacher_lastcode.txt//存放最后一个教师工号


                3、需要定义如下结构体来读取文件：
                    typedef struct Stu//学生
                    {
                        char name[20];
                        char sex;
                        char code[20];
                        char key[20];
                        float Chinese_mark;
                        float English_mark;
                        float Math_mark;
                        bool  ;//是否被锁定,初始为0，锁定后为1；
                    }Stu；
                
                
                    typedef struct Tea//教师
                    {
                        char name[20];
                        char sex;
                        char code[20];
                        char key[20];
                        bool is_clock;//是否被锁定,初始为0，锁定后为1；
                        
                    }Tea；

                4、经过讨论，我们写下了一份《学生信息管理系统标准守则1.0》，规定了函数名、文件名和工程文件名，并人手一份，按照守则进行编程

                5、完成子系统后，对多次用的、功能相似的代码进行函数封装，并将三个子系统组合；

            
            二、分工：本项目是校园信息管理系统，可分为校长、教师、学生三个子系统，我们根据三个系统的实现难度和个人能力分配了任务，
                一人负责学生系统，一人负责校长系统，组长负责教师系统和三个系统的整合。

            三、流程记录
                    第一天：
                    分析题目、完成分工、三人分别列出自己需要的函数以及函数需要的全局变量、结构体、文件，
                    然后汇总进行统一命名，保证没有重名并提高区分度。
                    进行头文件和基本框架的编写（未完成）。

                    第二天：
                    继续进行头文件和基本框架的编写
                     进行功能函数的编写（完成约20%）

                    第三天：
                    进行功能函数的编写（完成约50%）

                    第四天
                    进行功能函数的编写（完成约95%，剩余一个函数仍存在bug）
                    组长进行组合，由于前期制定了标准，过程很顺利。


                    第五天
                    休息一天

                    第六天：
                    调试程序并解决bug，添加注释，进行总结文档的编写

        
            
        项目总结（25）
            项目心得体会、经验总结 犯过什么错误，走过什么弯路、给自己带来什么启示
            哪些知识点更深刻、更熟练
            如果再给你一次机会，你会有哪些改变、新计划

                遇到的困难：
                    输密码显示***
                        使用getchar（）代替scanf（）；
                    使用添加'\0'删除文件导致文件乱码
                        不再使用'\0',转为全部读取文件，修改后清空文件，再次写入的方法。

                遇到的bug：
                    账号超出数组限制后段错误
                    添加教师到上限
                    直接使用==比较字符串（大量）
                    函数修改参数后未及时同步修改至头文件（大量）
                    （待补充）
                    









    

        功能介绍（30）
            一人操作 一人介绍
        个人代码展示（15）
            可读性 健壮性 安全性 可扩展性
            例如：代码格式、注释、命令、实现方法是否简便

        提问（20）
            技术问题
            人事问题

   




        
        
