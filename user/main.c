
#include "hardware.h"

void lcd_dis_page01(void)
{
	printf("%s\n","-----Board Sensor Data-----");
	char time[30] = {0};
	struct time_st rtc_time;
	
	char temp_buf[10] = {0};
	
	char hum_buf[5] = {0};
	char hum_str[20] = {0};
	
	int pm25_value = 0;
	char pm25_str[20] = {0};
	
	int led_status[3];
	int relay_status[3];
	int button_status[4];
	
	char lcd_led_sta_dis_str[30];
	char lcd_relay_sta_dis_str[30];
	char lcd_but_sta_dis_str[30];
	
	
	BRUSH_COLOR = YELLOW;
	BACK_COLOR = BLACK;
	LCD_Clear(BACK_COLOR);
 //dislplay head	
	LCD_DisplayString(0, 0, 16, (u8 *)"-STM32F407ZGT6 Dev Board Test-");
	
	
	//dispay time
	BRUSH_COLOR = GREEN;
	get_time(&rtc_time);
	sprintf(time, "Time:20%02d-%02d-%02d %02d:%02d:%02d Wk:%02d", rtc_time.Y, rtc_time.M, rtc_time.D,rtc_time.h, rtc_time.m,rtc_time.s,rtc_time.W);
	LCD_DisplayString(0, 303, 16, (u8 *)time);
	
	
	//display temp buf
	get_temperature(temp_buf);
	LCD_DisplayString(0, 16, 16, (u8 *)"Temperature:");
	LCD_DisplayString(96, 16, 16, (u8 *)temp_buf);
	printf("Temperature:%s\n",temp_buf);
	
	//display humity
	get_dht_value(hum_buf);
	sprintf(hum_str,"Humidity:%d",hum_buf[0]);
	LCD_DisplayString(0, 32, 16,(u8 *)hum_str);
	printf("%s\n",hum_str);
  
	
	//display pm2.5
	pm25_value = get_pm_value();

	sprintf(pm25_str,"PM2.5 Value:%d",pm25_value);
	LCD_DisplayString(0, 48, 16,(u8 *)pm25_str);
	printf("%s\n",pm25_str);
	
	
	//display led status
	led_on(1);
	led_status[0] = get_led_status(0);
	led_status[1] = get_led_status(1);
	led_status[2] = get_led_status(2);
	
	printf("-----Board Leds Status-----\n");
	printf("led0  :%s\n",led_status[0]?"OFF":"ON");
	printf("led1  :%s\n",led_status[1]?"OFF":"ON");
	printf("led2  :%s\n",led_status[2]?"OFF":"ON");
	
	LCD_DisplayString(0, 64, 16, (u8 *)"Leds:");
	LCD_DisplayString(48, 64, 16, (u8 *)"0:");
	LCD_DisplayString(64, 64, 16, (u8 *)(led_status[0]?"OFF":"ON"));
	
	LCD_DisplayString(96, 64, 16, (u8 *)"1:");
	LCD_DisplayString(112, 64, 16, (u8 *)(led_status[1]?"OFF":"ON"));
	
	LCD_DisplayString(144, 64, 16, (u8 *)"2:");
	LCD_DisplayString(160, 64, 16, (u8 *)(led_status[2]?"OFF":"ON"));
	
	
	
	//display relay status
	relay_status[0] =  get_relay_status(0);
	relay_status[1] =  get_relay_status(1);
	relay_status[2] =  get_relay_status(2);
	
	relay_on(1);
	printf("-----Board Relay Status-----\n");
	printf("relay0  :%s\n",!relay_status[0]?"OFF":"ON");
	printf("relay1  :%s\n",!relay_status[1]?"OFF":"ON");
	printf("relay2  :%s\n",!relay_status[2]?"OFF":"ON");	
	
	LCD_DisplayString(0, 80, 16, (u8 *)"Relays:");
	
	LCD_DisplayString(64, 80, 16, (u8 *)"0:");
	LCD_DisplayString(80, 80, 16, (u8 *)(relay_status[0]?"OFF":"ON"));
	
	LCD_DisplayString(112, 80, 16, (u8 *)"1:");
	LCD_DisplayString(128, 80, 16, (u8 *)(relay_status[1]?"OFF":"ON"));
	
	LCD_DisplayString(160, 80, 16, (u8 *)"2:");
	LCD_DisplayString(176, 80, 16, (u8 *)(relay_status[2]?"OFF":"ON"));
	
	//display buzzer status
	//buzzer_on();
	printf("-----Board Buzzer Status-----\n");
	printf("buzzer  :%s\n",!get_buzzer_status()?"OFF":"ON");

	LCD_DisplayString(0, 96, 16, (u8 *)"Buzzer:");
	LCD_DisplayString(64, 96, 16, (u8 *)(!get_buzzer_status()?"OFF":"ON"));
	
	
	//display button status
	printf("-----Board Button Press Detect-----\n");
	button_status[0] = get_button_status(0);
	button_status[1] = get_button_status(1);
	button_status[2] = get_button_status(2);
	button_status[3] = get_button_status(3);
	
	printf("button0  :%s\n",button_status[0]?"Detect":"Undetect");
	printf("button1  :%s\n",button_status[1]?"Detect":"Undetect");
	printf("button2  :%s\n",button_status[2]?"Detect":"Undetect");
	printf("button3  :%s\n",button_status[3]?"Detect":"Undetect");
	
	LCD_DisplayString(0, 112, 16, (u8 *)"Buttons:");
	
	LCD_DisplayString(72, 112, 16, (u8 *)"B0:");
	LCD_DisplayString(96, 112, 16, (u8 *)(button_status[0]?"1":"0"));
	
	LCD_DisplayString(112, 112, 16, (u8 *)"B1:");
	LCD_DisplayString(136, 112, 16, (u8 *)(button_status[1]?"1":"0"));

	LCD_DisplayString(152, 112, 16, (u8 *)"B2:");
	LCD_DisplayString(176, 112, 16, (u8 *)(button_status[2]?"1":"0"));
	
	LCD_DisplayString(192, 112, 16, (u8 *)"B3:");
	LCD_DisplayString(216, 112, 16, (u8 *)(button_status[3]?"1":"0"));
	
	
	delay_ms(1000);
	delay_ms(1000);
	
	
	
}	

int main(void)
{
	struct time_st t = {19, 5, 27, 3, 17, 35, 0};
	led_init();
	systick_init();
	DS18B20_Init();
	rtc_init(&t);
	dht_init();
	adc_pm_init();
	pm_init();
	relay_init();
	USARTx_Config();
	buzzer_init();
	button_init();
	
	LCD_Init();
	printf("STM32F407ZGT6 Develop Board Test\n");
	
	while(1)
	{
		lcd_dis_page01();
		
	}
}


