#include "iwdg.h"

void iwdg_init(int ms)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//关闭写保护(开启写访问)
	IWDG_SetPrescaler(IWDG_Prescaler_32);//设置32分频
	IWDG_SetReload(ms);//设置计数值
	IWDG_ReloadCounter();//把重载值寄存器的值加载到计数器中
	IWDG_Enable();//开启看门狗
}

void feed_dog(void)
{
	IWDG_ReloadCounter();//喂狗
}
/*
1.把iwdg的操作修改成操作寄存器的版本
2.自己阅读中文参考手册,操作窗口看门狗
*/












