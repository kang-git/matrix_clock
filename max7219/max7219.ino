
#define uchar unsigned char
#define uint  unsigned int


//定义Max7219端口
#define Max7219_pinCLK 2
#define Max7219_pinCS  0
#define Max7219_pinDIN 4


uchar disp1[38][8]={
{0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C},//0
{0x10,0x18,0x14,0x10,0x10,0x10,0x10,0x10},//1
{0x7E,0x2,0x2,0x7E,0x40,0x40,0x40,0x7E},//2
{0x3E,0x2,0x2,0x3E,0x2,0x2,0x3E,0x0},//3
{0x8,0x18,0x28,0x48,0xFE,0x8,0x8,0x8},//4
{0x3C,0x20,0x20,0x3C,0x4,0x4,0x3C,0x0},//5
{0x3C,0x20,0x20,0x3C,0x24,0x24,0x3C,0x0},//6
{0x3E,0x22,0x4,0x8,0x8,0x8,0x8,0x8},//7
{0x0,0x3E,0x22,0x22,0x3E,0x22,0x22,0x3E},//8
{0x3E,0x22,0x22,0x3E,0x2,0x2,0x2,0x3E},//9
{0x8,0x14,0x22,0x3E,0x22,0x22,0x22,0x22},//A
{0x3C,0x22,0x22,0x3E,0x22,0x22,0x3C,0x0},//B
{0x3C,0x40,0x40,0x40,0x40,0x40,0x3C,0x0},//C
{0x7C,0x42,0x42,0x42,0x42,0x42,0x7C,0x0},//D
{0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x7C},//E
{0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x40},//F
{0x3C,0x40,0x40,0x40,0x40,0x44,0x44,0x3C},//G
{0x44,0x44,0x44,0x7C,0x44,0x44,0x44,0x44},//H
{0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x7C},//I
{0x3C,0x8,0x8,0x8,0x8,0x8,0x48,0x30},//J
{0x0,0x24,0x28,0x30,0x20,0x30,0x28,0x24},//K
{0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7C},//L
{0x81,0xC3,0xA5,0x99,0x81,0x81,0x81,0x81},//M
{0x0,0x42,0x62,0x52,0x4A,0x46,0x42,0x0},//N
{0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C},//O
{0x3C,0x22,0x22,0x22,0x3C,0x20,0x20,0x20},//P
{0x1C,0x22,0x22,0x22,0x22,0x26,0x22,0x1D},//Q
{0x3C,0x22,0x22,0x22,0x3C,0x24,0x22,0x21},//R
{0x0,0x1E,0x20,0x20,0x3E,0x2,0x2,0x3C},//S
{0x0,0x3E,0x8,0x8,0x8,0x8,0x8,0x8},//T
{0x42,0x42,0x42,0x42,0x42,0x42,0x22,0x1C},//U
{0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18},//V
{0x0,0x49,0x49,0x49,0x49,0x2A,0x1C,0x0},//W
{0x0,0x41,0x22,0x14,0x8,0x14,0x22,0x41},//X
{0x41,0x22,0x14,0x8,0x8,0x8,0x8,0x8},//Y
{0x0,0x7F,0x2,0x4,0x8,0x10,0x20,0x7F},//Z
{0x8,0x7F,0x49,0x49,0x7F,0x8,0x8,0x8},//中
{0xFE,0xBA,0x92,0xBA,0x92,0x9A,0xBA,0xFE},//国
};



//--------------------------------------------
//向MAX7219(U3)写入字节
void Write_Max7219_byte(uchar DATA)         
{
      uchar i,temp;    
      digitalWrite(Max7219_pinCS, LOW);        //CS=0有效,CS=1锁存 
      for(i=8;i>=1;i--)
      {     
            digitalWrite(Max7219_pinCLK, LOW);
            temp=DATA&0x80; //&10000000, 编译器对位操作的理解:非0即为1
            if(temp)
                digitalWrite(Max7219_pinDIN, HIGH);
            else
                digitalWrite(Max7219_pinDIN, LOW);
            DATA=DATA<<1;
            digitalWrite(Max7219_pinCLK, HIGH);   //上升沿把数据送出去
      }                                 
}


//-------------------------------------------
/*向M第一片MAX7219写入数据*/
void Write_Max7219_1(uchar add1,uchar dat1)
{ 
    digitalWrite(Max7219_pinCS, LOW);
    Write_Max7219_byte(add1);           //写入地址，即数码管编号
    Write_Max7219_byte(dat1);               //写入数据，即数码管显示数字 
    digitalWrite(Max7219_pinCS, HIGH);                        
}

/*
//向下翻页
void down(uchar add1,uchar dat1)
{
    Write_Max7219_1()
  
}
*/

/*第二片MAX7219的写入数据*/
void Write_Max7219_2(uchar add2,uchar dat2)
{
    digitalWrite(Max7219_pinCS, LOW);
    Write_Max7219_byte(add2);
    Write_Max7219_byte(dat2);
    digitalWrite(Max7219_pinCLK, HIGH);
    Write_Max7219_byte(0x00);  //片1写入空
    Write_Max7219_byte(0x00);
    digitalWrite(Max7219_pinCS, HIGH);
}


/*第三片MAX7219的写入数据*/
void Write_Max7219_3(uchar add3,uchar dat3)
{
    digitalWrite(Max7219_pinCS, LOW);
    Write_Max7219_byte(add3);
    Write_Max7219_byte(dat3);
    digitalWrite(Max7219_pinCLK, HIGH);
    Write_Max7219_byte(0x00); //片1写入空
    Write_Max7219_byte(0x00);
    Write_Max7219_byte(0x00); //片2写入空
    Write_Max7219_byte(0x00);
    digitalWrite(Max7219_pinCS, HIGH);
}

/*第四片MAX7219的写入数据*/
void Write_Max7219_4(uchar add4,uchar dat4)
{
    digitalWrite(Max7219_pinCS, LOW);
    Write_Max7219_byte(add4);
    Write_Max7219_byte(dat4);
    digitalWrite(Max7219_pinCLK, HIGH);
    Write_Max7219_byte(0x00); //片1写入空
    Write_Max7219_byte(0x00);
    Write_Max7219_byte(0x00); //片2写入空
    Write_Max7219_byte(0x00);
    Write_Max7219_byte(0x00); //片3写入空
    Write_Max7219_byte(0x00);
    digitalWrite(Max7219_pinCS, HIGH);
}
 
/*初始化芯片*/
void Init_MAX7219(void)
{
    Write_Max7219_1(0x09, 0x00);       //译码方式：BCD码
    Write_Max7219_1(0x0a, 0x0f);       //亮度 
    Write_Max7219_1(0x0b, 0x07);       //扫描界限；8个数码管显示
    Write_Max7219_1(0x0c, 0x01);       //掉电模式：0，普通模式：1
    Write_Max7219_1(0x0f, 0x00);       //显示测试：1；测试结束，正常显示：0

    Write_Max7219_2(0x09, 0x00);       //译码方式：BCD码
    Write_Max7219_2(0x0a, 0x0f);       //亮度 
    Write_Max7219_2(0x0b, 0x07);       //扫描界限；8个数码管显示
    Write_Max7219_2(0x0c, 0x01);       //掉电模式：0，普通模式：1
    Write_Max7219_2(0x0f, 0x00);       //显示测试：1；测试结束，正常显示：0

    Write_Max7219_3(0x09, 0x00);       //译码方式：BCD码
    Write_Max7219_3(0x0a, 0x0f);       //亮度 
    Write_Max7219_3(0x0b, 0x07);       //扫描界限；8个数码管显示
    Write_Max7219_3(0x0c, 0x01);       //掉电模式：0，普通模式：1
    Write_Max7219_3(0x0f, 0x00);       //显示测试：1；测试结束，正常显示：0

    Write_Max7219_4(0x09, 0x00);       //译码方式：BCD码
    Write_Max7219_4(0x0a, 0x0f);       //亮度 
    Write_Max7219_4(0x0b, 0x07);       //扫描界限；8个数码管显示
    Write_Max7219_4(0x0c, 0x01);       //掉电模式：0，普通模式：1
    Write_Max7219_4(0x0f, 0x00);       //显示测试：1；测试结束，正常显示：0
}
 
 
void setup()
{
    pinMode(Max7219_pinCS, OUTPUT);
    pinMode(Max7219_pinCLK, OUTPUT);
    pinMode(Max7219_pinDIN, OUTPUT);   
    delay(50);
    Init_MAX7219();

}

/**********************主程序**************************/
void loop()
{
    uchar i,j;
    uchar dat[8];
    uchar transfor;
    delay(50);
    Init_MAX7219();  
    while(1)
    {
        
        for(j=0;j<38;j++)
        {
            /*for(i=1;i<9;i++)
            {
                Write_Max7219_1(i,disp1[j][i-1]);
                Write_Max7219_2(i,disp1[j][i-1]);
                Write_Max7219_3(i,disp1[j][i-1]);
                Write_Max7219_4(i,disp1[j][i-1]);
            }*/
            delay(300);
            for(i=1;i<9;i++)
            {
                Write_Max7219_1(i, disp1[j][i-1]);
                Write_Max7219_2(i, disp1[j][i-1]);
                Write_Max7219_3(i, disp1[j][i-1]);
                Write_Max7219_4(i, disp1[j][i-1]);
            }
            delay(760);
            for(i=0;i<8;i++)    
                dat[i] = disp1[j][i];
            for(i=7;i>0;i--)
                dat[i] = dat[i-1];
            dat[0] = 0x00;
            delay(30);
            for(i=1;i<9;i++)
            {
                Write_Max7219_1(i, dat[i-1]);
                Write_Max7219_2(i, dat[i-1]);
                Write_Max7219_3(i, dat[i-1]);
                Write_Max7219_4(i, dat[i-1]);  
            }
            for(i=7;i>0;i--)
                dat[i] = dat[i-1];
            dat[0] = 0x00;
            delay(30);
            for(i=1;i<9;i++)
            {
                Write_Max7219_1(i, dat[i-1]);
                Write_Max7219_2(i, dat[i-1]);
                Write_Max7219_3(i, dat[i-1]);
                Write_Max7219_4(i, dat[i-1]);  
            }
            for(i=7;i>0;i--)
                dat[i] = dat[i-1];
            dat[1] = dat[0];
            dat[0] = 0x00;
            delay(30);
            for(i=1;i<9;i++)
            {
                Write_Max7219_1(i, dat[i-1]);
                Write_Max7219_2(i, dat[i-1]);
                Write_Max7219_3(i, dat[i-1]);
                Write_Max7219_4(i, dat[i-1]);  
            }
            for(i=7;i>0;i--)
                dat[i] = dat[i-1];
            dat[1] = dat[0];
            dat[0] = 0x00;
            delay(30);
            for(i=1;i<9;i++)
            {
                Write_Max7219_1(i, dat[i-1]);
                Write_Max7219_2(i, dat[i-1]);
                Write_Max7219_3(i, dat[i-1]);
                Write_Max7219_4(i, dat[i-1]);  
            }
            for(i=7;i>0;i--)
                dat[i] = dat[i-1];
            dat[1] = dat[0];
            dat[0] = 0x00;
            delay(30);
            for(i=1;i<9;i++)
            {
                Write_Max7219_1(i, dat[i-1]);
                Write_Max7219_2(i, dat[i-1]);
                Write_Max7219_3(i, dat[i-1]);
                Write_Max7219_4(i, dat[i-1]);  
            }
            for(i=7;i>0;i--)
                dat[i] = dat[i-1];
            dat[1] = dat[0];
            dat[0] = 0x00;
            delay(30);
            for(i=1;i<9;i++)
            {
                Write_Max7219_1(i, dat[i-1]);
                Write_Max7219_2(i, dat[i-1]);
                Write_Max7219_3(i, dat[i-1]);
                Write_Max7219_4(i, dat[i-1]);  
            }
            for(i=7;i>0;i--)
                dat[i] = dat[i-1];
            dat[1] = dat[0];
            dat[0] = 0x00;
            delay(30);
            for(i=1;i<9;i++)
            {
                Write_Max7219_1(i, dat[i-1]);
                Write_Max7219_2(i, dat[i-1]);
                Write_Max7219_3(i, dat[i-1]);
                Write_Max7219_4(i, dat[i-1]);  
            }
            for(i=7;i>0;i--)
                dat[i] = dat[i-1];
            dat[1] = dat[0];
            dat[0] = 0x00;
            delay(30);
            for(i=1;i<9;i++)
            {
                Write_Max7219_1(i, dat[i-1]);
                Write_Max7219_2(i, dat[i-1]);
                Write_Max7219_3(i, dat[i-1]);
                Write_Max7219_4(i, dat[i-1]);  
            }
        }
    } 
}
