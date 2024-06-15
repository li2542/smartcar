#include "reg52.h"
#include "intrins.h"
#include "motor.h"
#include "delay.h"
#include "uart.h"
#include "hc04.h"
#include "sg90.h"
#include "Oled.h"


#define BZ 1
#define XJ 2
#define GS 3
 
//extern char speedLeft;

//extern char speedRight;

sbit A25 = P1^5;
sbit A26 = P1^6;
sbit A27 = P1^7;


sbit leftSensorX = P2^7;
sbit rightSensorX = P2^6;

sbit leftSensorG = P2^5;
sbit rightSensorG = P2^4;


//sbit led = P3^7;

char MIDDLE=0;
char LEFT=1;
char RIGHT=2;

char dir;
	
double disMiddle;
double disLeft;
double disRight;

void xunjiMode()
{
		if(leftSensorX == 0 && rightSensorX == 0){
		goForword();
		}
		if(leftSensorX == 1 && rightSensorX == 0){
		goLeft();
		}
		if(leftSensorX == 0 && rightSensorX == 1){
		goRight();
		}
		if(leftSensorX == 1 && rightSensorX == 1){
		//停
		stop();
	  }
}


void gensuiMode(){
	if(leftSensorG == 0 && rightSensorG ==0){//前进
		goForword();
		//speedLeft = 40;
		//speedRight = 40;
	}
	if(leftSensorG == 1 && rightSensorG ==0){//左转
		goLeft();
		//speedLeft = 10;
		//speedRight = 40;
	}
	if(leftSensorG == 0 && rightSensorG ==1){//右转
		goRight();
		//speedLeft = 40;
		//speedRight = 10;
	}
	if(leftSensorG == 1 && rightSensorG ==1){//停止
		stop();
		//speedLeft = 0;
		//speedRight = 0;
	}
}


void bizhangMode(){
	if(dir > 0){
			sgMiddle();
			dir = MIDDLE;
			Delay300ms();
		}
		Delay50ms();//这里有Bug,要延时50ms
		disMiddle = get_distance();
		if(disMiddle > 35){ 
			//前进
			goForword();
			//led = 0;
		}else{
			stop();
			//led = 1;
			//停止，测左边右边距离
			sgLeft();
			Delay300ms();
			disLeft = get_distance();
			
			sgMiddle();
			Delay300ms();
			
			sgRight();
			Delay300ms();
			dir = RIGHT;
			disRight = get_distance();
			
			if(disLeft < disRight){
				goRight();
				Delay150ms();
				stop();
			}
			if(disLeft > disRight){
				goLeft();
				Delay150ms();
				stop();
			}
		}
}

void main()
{
	int mark = 0;
	Time0Init();
	Time1Init();
		
	sgMiddle();
	Delay300ms();
	dir = MIDDLE;
	
	Oled_Init();
	Oled_Clear();
	Oled_Show_Str(2,2,"------Ready------");
	
	while(1){
		//满足寻迹模式的条件
		if(A25 == 0 && A26 == 1 && A27 == 1){
			if(mark != XJ){
				Oled_Clear();
				Oled_Show_Str(2,2,"-----XunJi----");
			}
			mark = XJ;
			xunjiMode();
		}
		//满足跟随模式的条件
		if(A25 == 1 && A26 == 0 && A27 == 1){
			if(mark != GS){
				Oled_Clear();
				Oled_Show_Str(2,2,"-----GenSui----");
			}
			mark = GS;
			gensuiMode();
		}
		//满足避障模式的条件
		if(A25 == 1 && A26 == 1 && A27 == 0){
			if(mark != BZ){
				Oled_Clear();
				Oled_Show_Str(2,2,"-----BiZhang----");
			}
			mark = BZ;
			bizhangMode();
		}
	}
}
