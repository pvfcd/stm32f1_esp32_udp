
#include "stm32f10x.h" //STM32头文件
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "oled0561.h"
u8 ip_buffer[17];
u8 data_buffer[30];
int main (void){//主程序
	
	
	u16 i,j;
	delay_ms(100); //上电时等待其他器件就绪
	RCC_Configuration(); //系统时钟初始化 

	I2C_Configuration();//I2C初始化
	USART1_Init(115200); //串口初始化（参数是波特率）
	USART3_Init(115200); //串口初始化（参数是波特率）

	OLED0561_Init(); //OLED初始化
	OLED_DISPLAY_LIT(100);//亮度设置
//	OLED_DISPLAY_PIC1();//显示全屏图片
	delay_ms(500); //延时
	OLED_DISPLAY_CLEAR();
	OLED_DISPLAY_8x16_BUFFER(0,"TALOS LABORATORY");


	for (i = 0;i<17;i++)//清空数组
						{
						ip_buffer[i] = 0;
						}
	OLED_DISPLAY_8x16_BUFFER(6,"waiting..."); //显示字符串
	while(1){
		if (USART3_RX_BUF[0]=='C')
		{
				delay_ms(20);//让串口接收完剩余数据
				for (i = 0;i<17;i++)
				{
				ip_buffer[i]=USART3_RX_BUF[i+22];//将IP地址存入数组中
				}
				for(i = 0;i<17;i++)
				{
					if (0x29 < ip_buffer[i]&&ip_buffer[i]< 0x40)
					{
						OLED_DISPLAY_8x16(6,i*8,ip_buffer[i]);//ip地址不是.的位置
					}	
					else if (ip_buffer[i] == '.')
					{
						OLED_DISPLAY_8x16(6,i*8,'.');//ip地址不是.的位置
					}	
					else
					{
						i = 20;//代表ip位数到了，跳出循环
						for (j = 0;j<201;j++){
							USART3_RX_BUF[j] = 0;}
							USART3_RX_STA = 0;
					}
				}
		}
		
		if(USART3_RX_BUF[0]=='R')
		{
			Res = 1;//防止进入接收中断
			OLED_DISPLAY_8x16_BUFFER(3,"                              ");
			for (i = 2 ; i < 19;i++){
				if(0x21 < USART3_RX_BUF[i]&& USART3_RX_BUF[i]< 0x7D){
					if (USART3_RX_BUF[i] != '?')
					{
						OLED_DISPLAY_8x16(3,(i-2)*8,USART3_RX_BUF[i]);
						data_buffer[i] = USART3_RX_BUF[i];
					}				
					}
			}
			for (j = 0;j<201;j++){
				USART3_RX_BUF[j] = 0;}
				USART3_RX_STA = 0;
		}
		
		delay_ms(200); //延时
	}
}
/*

【变量定义】
u32     a; //定义32位无符号变量a
u16     a; //定义16位无符号变量a
u8     a; //定义8位无符号变量a
vu32     a; //定义易变的32位无符号变量a
vu16     a; //定义易变的 16位无符号变量a
vu8     a; //定义易变的 8位无符号变量a
uc32     a; //定义只读的32位无符号变量a
uc16     a; //定义只读 的16位无符号变量a
uc8     a; //定义只读 的8位无符号变量a

#define ONE  1   //宏定义

delay_us(1); //延时1微秒
delay_ms(1); //延时1毫秒
delay_s(1); //延时1秒

GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1)); //LED控制

*/



