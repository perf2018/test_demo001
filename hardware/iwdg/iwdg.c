#include "iwdg.h"

void iwdg_init(int ms)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//�ر�д����(����д����)
	IWDG_SetPrescaler(IWDG_Prescaler_32);//����32��Ƶ
	IWDG_SetReload(ms);//���ü���ֵ
	IWDG_ReloadCounter();//������ֵ�Ĵ�����ֵ���ص���������
	IWDG_Enable();//�������Ź�
}

void feed_dog(void)
{
	IWDG_ReloadCounter();//ι��
}
/*
1.��iwdg�Ĳ����޸ĳɲ����Ĵ����İ汾
2.�Լ��Ķ����Ĳο��ֲ�,�������ڿ��Ź�
*/












