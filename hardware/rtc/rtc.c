#include "rtc.h"

void rtc_init(struct time_st *t)
{
	RTC_InitTypeDef Rtc_Value;
	
	PWR_BackupAccessCmd(ENABLE);//ͨ��PWR��RTC�ļĴ���д����
	
	if(RTC_ReadBackupRegister(RTC_BKP_DR10) != 0x9527)//�ж��Ƿ��ǵ�һ�β���RTC
	{
		RCC_LSEConfig(RCC_LSE_ON);//����LSEʱ��
		while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);//�ȴ�LSEʱ���ȶ�
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);//ѡ��LSE��ΪRTC��ʱ��
		RCC_RTCCLKCmd(ENABLE);//ʹ��RTC
		Rtc_Value.RTC_AsynchPrediv = 127;//�����첽��Ƶ
		Rtc_Value.RTC_HourFormat = RTC_HourFormat_24;//ѡ��24Сʱ��
		Rtc_Value.RTC_SynchPrediv = 255;//����ͬ����Ƶ(Ӳ���ϻ�Ĭ��+1)
		RTC_Init(&Rtc_Value);//�����������ó�ʼ��RTC
		set_time(t);//����ʱ��
		RTC_WriteBackupRegister(RTC_BKP_DR10, 0x9527);//�����ݼĴ���д���ض�ֵ
	}
	PWR_BackupAccessCmd(DISABLE);//ͨ��PWR����RTC�ļĴ�����д����
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
	Time_Value.RTC_Seconds = t->s;//�Ѳ��������ݸ�ֵ���ṹ��ĳ�Ա
	
	RTC_SetDate(RTC_Format_BIN, &Date_Value); //����RTC������
	RTC_SetTime(RTC_Format_BIN, &Time_Value); //����RTC��ʱ��
}

void get_time(struct time_st *t)
{
	RTC_DateTypeDef Date_Value;
	RTC_TimeTypeDef Time_Value;
	
	RTC_GetDate(RTC_Format_BIN, &Date_Value); //��ȡRTC������
	RTC_GetTime(RTC_Format_BIN, &Time_Value); //��ȡRTC��ʱ��
	
	t->Y = Date_Value.RTC_Year;
	t->M = Date_Value.RTC_Month;
	t->D = Date_Value.RTC_Date;
	t->W = Date_Value.RTC_WeekDay;
	t->h = Time_Value.RTC_Hours;
	t->m = Time_Value.RTC_Minutes;
	t->s = Time_Value.RTC_Seconds;//�ѻ�ȡ�����ں�ʱ�丳ֵ������
}




