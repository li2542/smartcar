#include "reg52.h"

sbit RightConlA = P3^7;//控制右轮
sbit RightConlB = P3^3;

sbit LeftConlA = P3^4;//控制左轮
sbit LeftConlB = P3^5;

void goForwordLeft(){//前进右转
	LeftConlA = 0;
	LeftConlB = 1;
}

void stopLeft(){//停止右转
	LeftConlA = 0;
	LeftConlB = 0;
}

void goForwordRight(){//前进左转
	RightConlA = 0;
	RightConlB = 1;
}

void stopRight(){//停止左转
	RightConlA = 0;
	RightConlB = 0;
}





void goBack(){//小车后退代码封装
	LeftConlA = 1;
	LeftConlB = 0;
	
	RightConlA = 1;
	RightConlB = 0;
}

void goForword(){//小车前进代码封装
	LeftConlA = 0;
	LeftConlB = 1;
	
	RightConlA = 0;
	RightConlB = 1;
}

void goLeft(){//左转
	LeftConlA = 0;
	LeftConlB = 0;
	
	RightConlA = 0;
	RightConlB = 1;
}

void goRight(){//右转
	LeftConlA = 0;
	LeftConlB = 1;
	
	RightConlA = 0;
	RightConlB = 0;
}

void stop(){//停止
	LeftConlA = 0;
	LeftConlB = 0;
	
	RightConlA = 0;
	RightConlB = 0;
}