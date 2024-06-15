void IIC_Send_Byte(char dataSend);

void Oled_Write_Cmd(char dataCmd);

void Oled_Write_Data(char dataData);

void Oled_Init(void);

void Oled_Clear();

void Oled_Show_Char(char row,char col,char oledChar);

void Oled_Show_Str(char row,char col,char *str);