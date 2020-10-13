#include "rtc.h"

void rtc_init(struct time_st *t)
{
	RTC_InitTypeDef Rtc_Value;
	
	PWR_BackupAccessCmd(ENABLE);//通过PWR打开RTC的寄存器写访问
	
	if(RTC_ReadBackupRegister(RTC_BKP_DR10) != 0x9527)//判断是否是第一次操作RTC
	{
		RCC_LSEConfig(RCC_LSE_ON);//开启LSE时钟
		while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);//等待LSE时钟稳定
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);//选择LSE作为RTC的时钟
		RCC_RTCCLKCmd(ENABLE);//使能RTC
		Rtc_Value.RTC_AsynchPrediv = 127;//设置异步分频
		Rtc_Value.RTC_HourFormat = RTC_HourFormat_24;//选择24小时制
		Rtc_Value.RTC_SynchPrediv = 255;//设置同步分频(硬件上会默认+1)
		RTC_Init(&Rtc_Value);//按照上述配置初始化RTC
		set_time(t);//设置时间
		RTC_WriteBackupRegister(RTC_BKP_DR10, 0x9527);//给备份寄存器写入特定值
	}
	PWR_BackupAccessCmd(DISABLE);//通过PWR开启RTC的寄存器的写保护
}

void set_time(struct time_st *t)
{
	RTC_DateTypeDef Date_Value;
	RTC_TimeTypeDef Time_Value;
	
	Date_Value.RTC_Year = t->Y;
	Date_Value.RTC_Month = t->M;
	Date_Value.RTC_Date = t->D;
	Date_Value.RTC_WeekDay = t->W;
	Time_Value.RTC_Hours = t->h;
	Time_Value.RTC_Minutes = t->m;
	Time_Value.RTC_Seconds = t->s;//把参数的数据赋值给结构体的成员
	
	RTC_SetDate(RTC_Format_BIN, &Date_Value); //设置RTC的日期
	RTC_SetTime(RTC_Format_BIN, &Time_Value); //设置RTC的时间
}

void get_time(struct time_st *t)
{
	RTC_DateTypeDef Date_Value;
	RTC_TimeTypeDef Time_Value;
	
	RTC_GetDate(RTC_Format_BIN, &Date_Value); //获取RTC的日期
	RTC_GetTime(RTC_Format_BIN, &Time_Value); //获取RTC的时间
	
	t->Y = Date_Value.RTC_Year;
	t->M = Date_Value.RTC_Month;
	t->D = Date_Value.RTC_Date;
	t->W = Date_Value.RTC_WeekDay;
	t->h = Time_Value.RTC_Hours;
	t->m = Time_Value.RTC_Minutes;
	t->s = Time_Value.RTC_Seconds;//把获取的日期和时间赋值给参数
}




