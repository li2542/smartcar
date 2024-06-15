#include "reg52.h"
#include "motor.h"
#include "string.h"
#include "delay.h"

sfr AUXR = 0x8e;
char buffer[12];
void UartInit(void)		//9600bps@11.0592MHz
{
	AUXR = 0x01;
	SCON = 0x50; //配置串口工作方式1，REN使能接收
	TMOD &= 0xF0;
	TMOD |= 0x20;//定时器1工作方式位8位自动重装
	
	TH1 = 0xFD;
	TL1 = 0xFD;//9600波特率的初值
	TR1 = 1;//开启定时器
	EA = 1;//开启总中断
	ES = 1;//开启串口中断
}

//M1 前进  M2 后退  M3 左转  M4 右转
void Uart_Handler() interrupt 4
{
	static int i = 0;
	char tmp;
	if(RI){
		RI = 0;
		tmp = SBUF;
		
		if(tmp == 'M'){
			i = 0;
		}
		buffer[i++] = tmp;
		
		//灯控指令
		if(buffer[0] == 'M'){
			switch(buffer[1]){
				case '1':
					goForword();
				  memset(buffer,'\0',12);
					Delay10ms();
					break;
				case '2':
					goBack();
					memset(buffer,'\0',12);
				Delay10ms();
					break;
				case '3':
					goLeft();
					memset(buffer,'\0',12);
				Delay10ms();
					break;
				case '4':
					goRight();
					memset(buffer,'\0',12);
				Delay10ms();
					break;
				case '5':
					stop();
					memset(buffer,'\0',12);
				Delay10ms();
					break;
			}
			//memset(buffer,'\0',12);
		}
		if(i == 12){
			i = 0;
		}
	}
	
}
