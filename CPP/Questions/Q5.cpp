// Q5：C++内存分区？
// 地址由高至低：堆→自由存储区→栈→全局/静态存储区→常量存储区→代码区

#include <iostream>
using namespace std;

/*
说明：C++中不再区分初始化和未初始化的全局变量、静态变量的存储区，
如果非要区分，下述程序标注在了括号中
*/

int g_var = 0; // g_var在全局区(.data段)
char *gp_var;  // gp_var在全局区(.bss段)

int main()
{
    int var;                    // var在栈区
    char *p_var;                // p_var在栈区
    char arr[] = "abc";         // arr为数组变量，存储在栈区； "abc"为字符串常量，存储在常量区
    char *p_var1 = "123456";    // p_var1在栈区； "123456"为字符串常量，存储在常量区
    static int s_var = 0;       // s_var为静态变量，存在静态存储区(.data段)
    p_var = (char *)malloc(10); // 分配得来的10个字节的区域在堆区
    free(p_var);
    return 0;
}
