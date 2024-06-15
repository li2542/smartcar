#include "reg52.h"
#include "delay.h"

sbit sg90_con = P1^1;
int jd;//角度;
int cnt = 0;//记录爆表次数


void Time0Init(){
	TMOD &= 0xF0; //设置定时器模式
	TMOD |= 0x01;
	//给初值，定义一个0.5ms来
	TL0 = 0x33;
	TH0 = 0xFE;
	//开始计时
	TR0 = 1;
	TF0 = 0;
	
	//打开定时器0中断
	ET0 = 1;
	//打开总中断EA
	EA = 1;
}

/*
十进制2左移1位，变成20。相当于乘以10
二禁止1左移1位，变成10（2）。相当于乘以2，左移8位，乘以2的8次方=256；*/



void sgMiddle(){
	
			jd = 3;//90度
			cnt = 0;
			
}

void sgRight(){
				jd = 1;//0度
			cnt = 0;
}

void sgLeft(){
			jd = 5;//135度
			cnt = 0;
}


void Time0Handler() interrupt 1{
	
			cnt++;//统计爆表次数
			//重新给初值
			TL0 = 0x33;
			TH0 = 0xFE;
	
			//控制PWM波
			if(cnt < jd){
				sg90_con = 1;
			}else{
				sg90_con = 0;
			}
			
			if(cnt == 40){//爆表40次，经过了20ms
				cnt = 0; //
				sg90_con = 1;
			}
		
}