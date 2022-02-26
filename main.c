
#include "stm32f10x.h" //STM32ͷ�ļ�
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "oled0561.h"
u8 ip_buffer[17];
u8 data_buffer[30];
int main (void){//������
	
	
	u16 i,j;
	delay_ms(100); //�ϵ�ʱ�ȴ�������������
	RCC_Configuration(); //ϵͳʱ�ӳ�ʼ�� 

	I2C_Configuration();//I2C��ʼ��
	USART1_Init(115200); //���ڳ�ʼ���������ǲ����ʣ�
	USART3_Init(115200); //���ڳ�ʼ���������ǲ����ʣ�

	OLED0561_Init(); //OLED��ʼ��
	OLED_DISPLAY_LIT(100);//��������
//	OLED_DISPLAY_PIC1();//��ʾȫ��ͼƬ
	delay_ms(500); //��ʱ
	OLED_DISPLAY_CLEAR();
	OLED_DISPLAY_8x16_BUFFER(0,"TALOS LABORATORY");


	for (i = 0;i<17;i++)//�������
						{
						ip_buffer[i] = 0;
						}
	OLED_DISPLAY_8x16_BUFFER(6,"waiting..."); //��ʾ�ַ���
	while(1){
		if (USART3_RX_BUF[0]=='C')
		{
				delay_ms(20);//�ô��ڽ�����ʣ������
				for (i = 0;i<17;i++)
				{
				ip_buffer[i]=USART3_RX_BUF[i+22];//��IP��ַ����������
				}
				for(i = 0;i<17;i++)
				{
					if (0x29 < ip_buffer[i]&&ip_buffer[i]< 0x40)
					{
						OLED_DISPLAY_8x16(6,i*8,ip_buffer[i]);//ip��ַ����.��λ��
					}	
					else if (ip_buffer[i] == '.')
					{
						OLED_DISPLAY_8x16(6,i*8,'.');//ip��ַ����.��λ��
					}	
					else
					{
						i = 20;//����ipλ�����ˣ�����ѭ��
						for (j = 0;j<201;j++){
							USART3_RX_BUF[j] = 0;}
							USART3_RX_STA = 0;
					}
				}
		}
		
		if(USART3_RX_BUF[0]=='R')
		{
			Res = 1;//��ֹ��������ж�
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
		
		delay_ms(200); //��ʱ
	}
}
/*

���������塿
u32     a; //����32λ�޷��ű���a
u16     a; //����16λ�޷��ű���a
u8     a; //����8λ�޷��ű���a
vu32     a; //�����ױ��32λ�޷��ű���a
vu16     a; //�����ױ�� 16λ�޷��ű���a
vu8     a; //�����ױ�� 8λ�޷��ű���a
uc32     a; //����ֻ����32λ�޷��ű���a
uc16     a; //����ֻ�� ��16λ�޷��ű���a
uc8     a; //����ֻ�� ��8λ�޷��ű���a

#define ONE  1   //�궨��

delay_us(1); //��ʱ1΢��
delay_ms(1); //��ʱ1����
delay_s(1); //��ʱ1��

GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1)); //LED����

*/



