#include "reg52.h"
#include "motor.h"

int cntLeft = 0;
char speedLeft;

int cntRight = 0;
char speedRight;


void Time1Init()
{
	//1. 配置定时器1工作模式位16位计时
	TMOD &= 0x0F;
	TMOD |= 0x1 << 4 ;
	//2. 给初值，定一个0.5出来
	TL1=0x33;
	TH1=0xFE;
	//3. 开始计时
	TR1 = 1;
	TF1 = 0;
	//4. 打开定时器1中断
	ET1 = 1;
	//5. 打开总中断EA
	EA = 1;
}

void Time0Init()
{
	//1. 配置定时器0工作模式位16位计时
	TMOD = 0x01;
	//2. 给初值，定一个0.5出来
	TL0=0x33;
	TH0=0xFE;
	//3. 开始计时
	TR0 = 1;
	TF0 = 0;
	//4. 打开定时器0中断
	ET0 = 1;
	//5. 打开总中断EA
	EA = 1;
}
void Time0Handler() interrupt 1
{
	cntLeft++; //统计爆表的次数. cnt=1的时候，报表了1
	//重新给初值
	TL0=0x33;
	TH0=0xFE;
	//控制PWM波
	if(cntLeft < speedLeft){
		//左轮前进
		goForwordLeft();
	}else{
		//停止
		stopLeft();
	}
	if(cntLeft == 40){//爆表40次，经过了20ms
		cntLeft = 0; 
	}
}

void Time1Handler() interrupt 3
{
	cntRight++; //统计爆表的次数. cnt=1的时候，报表了1
	//重新给初值
	TL1=0x33;
	TH1=0xFE;
	//控制PWM波
	if(cntRight < speedRight){
		//右轮 前进
		goForwordRight();
	}else{
		//停止
		stopRight();
	}
	if(cntRight == 40){//爆表40次，经过了20ms
		cntRight = 0; 
	}
}