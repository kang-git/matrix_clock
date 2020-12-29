
//变量类型名简化
#define uchar unsigned char
#define uint  unsigned int

//定义Max7219接口
#define Max7219_pinCLK 4
#define Max7219_pinCS  3
#define Max7219_pinDIN 2
//定义ds1302接口
#define ce 5
#define io 7
#define clk 6
//定义温湿度传感器
int pinDHT22 = 8;
//SimpleDHT22 dht22(pinDHT22);

//ds1302相关变量定义
unsigned char add_write[] = {0x8C,0x8A,0x88,0x86,0x84,0x82,0x80};//年星月日时分秒
unsigned char add_read[] = {0x8D,0x8B,0x89,0x87,0x85,0x83,0x81};
unsigned char tim0[] = {20,1,12,28,16,25,0};
unsigned char tim_bcd[7];
unsigned char tim[14];

//max7219相关变量定义
int time_table[8][32];
uchar disp1[38][8]={
{0x3C,0x24,0x24,0x24,0x24,0x24,0x3C,0x00},//0
{0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00},//1
{0x3C,0x04,0x04,0x3C,0x20,0x20,0x3C,0x00},//2
{0x3C,0x04,0x04,0x3C,0x04,0x04,0x3C,0x00},//3
{0x24,0x24,0x24,0x3C,0x04,0x04,0x04,0x00},//4
{0x3C,0x20,0x20,0x3C,0x04,0x04,0x3C,0x00},//5
{0x3C,0x20,0x20,0x3C,0x24,0x24,0x3C,0x00},//6
{0x3C,0x04,0x04,0x04,0x04,0x04,0x04,0x00},//7
{0x3C,0x24,0x24,0x3C,0x24,0x24,0x3C,0x00},//8
{0x3C,0x24,0x24,0x3C,0x04,0x04,0x3C,0x00},//9
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
//大号数字
int number1[10][7][5] = {
	{{1,1,1,1},{1,0,0,1},{1,0,0,1},{1,0,0,1},{1,0,0,1},{1,0,0,1},{1,1,1,1}},	//0
	{{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}},	//1
	{{1,1,1,1},{0,0,0,1},{0,0,0,1},{1,1,1,1},{1,0,0,0},{1,0,0,0},{1,1,1,1}},	//2
	{{1,1,1,1},{0,0,0,1},{0,0,0,1},{1,1,1,1},{0,0,0,1},{0,0,0,1},{1,1,1,1}},	//3
	{{1,0,0,1},{1,0,0,1},{1,0,0,1},{1,1,1,1},{0,0,0,1},{0,0,0,1},{0,0,0,1}},	//4
	{{1,1,1,1},{1,0,0,0},{1,0,0,0},{1,1,1,1},{0,0,0,1},{0,0,0,1},{1,1,1,1}},	//5
	{{1,1,1,1},{1,0,0,0},{1,0,0,0},{1,1,1,1},{1,0,0,1},{1,0,0,1},{1,1,1,1}},	//6
	{{1,1,1,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1}},	//7
	{{1,1,1,1},{1,0,0,1},{1,0,0,1},{1,1,1,1},{1,0,0,1},{1,0,0,1},{1,1,1,1}},	//8
	{{1,1,1,1},{1,0,0,1},{1,0,0,1},{1,1,1,1},{0,0,0,1},{0,0,0,1},{1,1,1,1}}		//9
};
//小号数字
int number2[10][5][3] = {
	{{1,1,1},{1,0,1},{1,0,1},{1,0,1},{1,1,1}},	//0
	{{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0}},	//1
	{{1,1,1},{0,0,1},{1,1,1},{1,0,0},{1,1,1}},	//2
	{{1,1,1},{0,0,1},{1,1,1},{0,0,1},{1,1,1}},	//3
	{{1,0,1},{1,0,1},{1,1,1},{0,0,1},{0,0,1}},	//4
	{{1,1,1},{1,0,0},{1,1,1},{0,0,1},{1,1,1}},	//5
	{{1,1,1},{1,0,0},{1,1,1},{1,0,1},{1,1,1}},	//6
	{{1,1,1},{0,0,1},{0,0,1},{0,0,1},{0,0,1}},	//7
	{{1,1,1},{1,0,1},{1,1,1},{1,0,1},{1,1,1}},	//8
	{{1,1,1},{1,0,1},{1,1,1},{0,0,1},{1,1,1}},	//9	
};
//点阵码表
uchar max7219_1[8];
uchar max7219_2[8];
uchar max7219_3[8];
uchar max7219_4[8];


//--------------------------------------------7219子程序-------------------------------------//
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
/*向M第一片MAX7219写入数据*/
void Write_Max7219_1(uchar add1,uchar dat1)
{ 
    digitalWrite(Max7219_pinCS, LOW);
    Write_Max7219_byte(add1);           //写入地址，即数码管编号
    Write_Max7219_byte(dat1);               //写入数据，即数码管显示数字 
    digitalWrite(Max7219_pinCS, HIGH);                      
}
/*第二片MAX7219的写入数据*/
void Write_Max7219_2(uchar add2,uchar dat2)
{
    digitalWrite(Max7219_pinCS, LOW);
    Write_Max7219_byte(add2);
    Write_Max7219_byte(dat2);
    digitalWrite(Max7219_pinCLK, HIGH);
    Write_Max7219_byte(0x00);  //片1写入空
    Write_Max7219_byte(0x00);
    digitalWrite(Max7219_pinCLK, HIGH);
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
//清屏
void clear_max()
{
    for (uchar i = 1; i < 9; i++)
    {
        Write_Max7219_1(i, 0x00);
        Write_Max7219_2(i, 0x00);
        Write_Max7219_3(i, 0x00);
        Write_Max7219_4(i, 0x00);
    }    
}
//单个点阵上字符下滑
void down(uchar data)
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
            for(i=1;i<9;i++)
            {
                Write_Max7219_1(i,disp1[j][i-1]);
                Write_Max7219_2(i,disp1[j][i-1]);
                Write_Max7219_3(i,disp1[j][i-1]);
                Write_Max7219_4(i,disp1[j][i-1]);
            }
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
//-------------------------------------------7219程序段---------------------------------------//

//-----------------------------------------数据变换程序段--------------------------------------//
//向二进制码表写入时的十位
void make_table_h1(uchar h1)
{
	int i,j;
	int n = 0;
	for(i=0;i<7;i++)
	{
		n = 0;
		for(j=0;j<4;j++)
		{
			time_table[i][j] = number1[h1][i][n];
			n = n + 1;
		}
	}
}
//向二进制码表写入时的各位
void make_table_h2(uchar h2)
{
	int i,j;
	int n = 0;
	for(i=0;i<7;i++)
	{
		n = 0;
		for(j=5;j<9;j++)
		{
			time_table[i][j] = number1[h2][i][n];
			n = n + 1;
		}
	}
}
//向二进制码表写入分的十位
void make_table_m1(uchar m1)
{
	int i,j;
	int n = 0;
	for(i=0;i<7;i++)
	{
		n = 0;
		for(j=14;j<18;j++)
		{
			time_table[i][j] = number1[m1][i][n];
			n = n + 1;
		}
	}
}
//向二进制码表写入分的个位
void make_table_m2(uchar m2)
{
	int i,j;
	int n = 0;
	for(i=0;i<7;i++)
	{
		n = 0;
		for(j=19;j<23;j++)
		{
			time_table[i][j] = number1[m2][i][n];
			n = n + 1;
		}
	}
}
//向二进制码表写入秒的十位
void make_table_s1(uchar s1)
{
	int i,j;
	int m = 0;
	int n = 0;
	for(i=2;i<7;i++)
	{
		n = 0;
		for(j=25;j<28;j++)
		{
			time_table[i][j] = number2[s1][m][n];
			n = n + 1;
		}
		m = m + 1;
	}
}
//向二进制时间码表写入秒数的个位
void make_table_s2(uchar s2)
{
	int i,j;
	int m = 0;
	int n = 0;
	for(i=2;i<7;i++)
	{
		n = 0;
		for(j=29;j<32;j++)
		{
			time_table[i][j] = number2[s2][m][n];
			n = n + 1;
		}
		m = m + 1;
	}
}
//将二进制点阵码表转换为写入max7219点阵的16进制值
void transform()
{
	uchar hex1[16]={0x00,0x10,0x20,0x30,0x40,0x50,0x60,0x70,0x80,0x90,0xa0,0xb0,0xc0,0xd0,0xe0,0xf0};
	uchar hex2[16]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};
	int max1_l,max1_r,max2_l,max2_r,max3_l,max3_r,max4_l,max4_r;
	uchar left1,right1,left2,right2,left3,right3,left4,right4;
	for (int i = 0; i < 8; i++)
	{	
		max1_l = time_table[i][0]*pow(2,3)+time_table[i][1]*pow(2,2)+time_table[i][2]*pow(2,1)+time_table[i][3]*pow(2,0);
		max1_r = time_table[i][4]*pow(2,3)+time_table[i][5]*pow(2,2)+time_table[i][6]*pow(2,1)+time_table[i][7]*pow(2,0);
		max2_l = time_table[i][8]*pow(2,3)+time_table[i][9]*pow(2,2)+time_table[i][10]*pow(2,1)+time_table[i][11]*pow(2,0);
		max2_r = time_table[i][12]*pow(2,3)+time_table[i][13]*pow(2,2)+time_table[i][14]*pow(2,1)+time_table[i][15]*pow(2,0);
		max3_l = time_table[i][16]*pow(2,3)+time_table[i][17]*pow(2,2)+time_table[i][18]*pow(2,1)+time_table[i][19]*pow(2,0);
		max3_r = time_table[i][20]*pow(2,3)+time_table[i][21]*pow(2,2)+time_table[i][22]*pow(2,1)+time_table[i][23]*pow(2,0);
		max4_l = time_table[i][24]*pow(2,3)+time_table[i][25]*pow(2,2)+time_table[i][26]*pow(2,1)+time_table[i][27]*pow(2,0);
		max4_r = time_table[i][28]*pow(2,3)+time_table[i][29]*pow(2,2)+time_table[i][30]*pow(2,1)+time_table[i][31]*pow(2,0);
		left1 = hex1[max1_l%16];
		right1 = hex2[max1_r%16];
		left2 = hex1[max2_l%16];
		right2 = hex2[max2_r%16];
		left3 = hex1[max3_l%16];
		right3 = hex2[max3_r%16];
		left4 = hex1[max4_l%16];
		right4 = hex2[max4_r%16];
		max7219_1[i] = left1|right1;
		max7219_2[i] = left2|right2;
		max7219_3[i] = left3|right3;
		max7219_4[i] = left4|right4;
	}	
}
//-----------------------------------------数据变换程序段--------------------------------------//

//-------------------------------------------DS1302程序段------------------------------------//
//上升沿写入8位数据函数
void write_1302_8(unsigned char dat)
{
    unsigned char i,temp;
    for(i = 0;i < 8;i++)
    {
        digitalWrite(clk, LOW);//时钟信号低时数据才能改变，同时为上升沿做准备
        temp = dat & 0x01;//取出最低位
        if(temp)
            digitalWrite(io, HIGH);
        else
            digitalWrite(io, LOW);
        digitalWrite(clk, HIGH);//时钟上升沿，1302读入数据
        dat = dat >> 1;//数据右移一位，为写入下一位做准备
    }
}
//写操作（写地址写数据）函数
void write_1302_data(unsigned char add, unsigned char dat)
{
    digitalWrite(ce, LOW);//不写入数据时片选信号拉低
    digitalWrite(clk, LOW);//时钟线开始为低
    digitalWrite(ce, HIGH);//拉高片选启动一次数据写入
    write_1302_8(add);//送地址字节
    write_1302_8(dat);//送数据字节
    digitalWrite(ce, LOW);//拉低片选信号结束写入
}
//读操作（写地址+读数据）函数
unsigned char read_1302_data(unsigned char add)
{
    unsigned char i,value;
    digitalWrite(ce, LOW);//准备
    digitalWrite(clk, LOW);//准备
    digitalWrite(ce, HIGH);//拉高片选开始一次读操作
    write_1302_8(add);//送出地址字节
    for(i = 0;i < 8;i++)
    {
        digitalWrite(clk, LOW);
        value = value >> 1;
        if(digitalRead(io))
            value = value | 0x80;
        digitalWrite(clk, HIGH);
    }
    digitalWrite(ce, LOW);//拉低片选结束一次读操作
    //Serial.println("当前寄存器值为:");
    //Serial.println(value);
    return value;
}
//初始化操作（设置时间日期初始值）
void ds1302_initial()
{
    unsigned char i,temp;
    for(i=0;i<7;i++)
    {
        temp = tim0[i]/10;
        tim0[i]= temp*16 + tim0[i]%10;
    }

    write_1302_data(0x8e,0x00);
    for(i=0;i<7;i++)
    {
        write_1302_data(add_write[i],tim0[i]);
    }
    write_1302_data(0x8e,0x80);
    Serial.println("初始化完成");
}
//读取时间并转换
void read_1302_time()
{
    unsigned char i;
    for(i=0;i<7;i++)//每次循环读取一个寄存器的内容，保持到tim_bcd[]数组中
    {
        tim_bcd[i] = read_1302_data(add_read[i]);
    }

    for(i=0;i<7;i++)//将读出的时间、日期分解为十位和个位
    {
        tim[2*i] = tim_bcd[i]/16;
        tim[2*i+1] = tim_bcd[i]%16;
    }
}
//串口显示时间函数
void display_ds1302time()
{
    Serial.print("20");
    Serial.print(tim[0]);
    Serial.print(tim[1]);
    Serial.print("年");
    Serial.print(tim[4]);
    Serial.print(tim[5]);
    Serial.print("月");
    Serial.print(tim[6]);
    Serial.print(tim[7]);
    Serial.print("日  ");
    Serial.print(tim[8]);
    Serial.print(tim[9]);
    Serial.print("时");
    Serial.print(tim[10]);
    Serial.print(tim[11]);
    Serial.print("分");
    Serial.print(tim[12]);
    Serial.print(tim[13]);
    Serial.print("秒");
    Serial.print("  星期");
    switch (tim[3])
    {
    case 1:
        Serial.print("一");
        break;
    case 2:
        Serial.print("二");
        break;
    case 3:
        Serial.print("三");
        break;
    case 4:
        Serial.print("四");
        break;
    case 5:
        Serial.print("五");
        break;
    case 6:
        Serial.print("六");
        break;
    case 7:
        Serial.print("日");
        break;
    default:
        break;
    }
    //Serial.print(tim[3]);
    Serial.println(" ");
}
//----------------------------------------DS1302程序段---------------------------------------//

 //硬件初始化
void setup()
{
    //max7219初始化
    pinMode(Max7219_pinCS, OUTPUT);
    pinMode(Max7219_pinCLK, OUTPUT);
    pinMode(Max7219_pinDIN, OUTPUT);
    pinMode(clk,OUTPUT);
    pinMode(ce,OUTPUT);  
    pinMode(io, INPUT);
    delay(50);
    Init_MAX7219();
    //DS1302及时间map初始化
    //ds1302_initial();
}

/******************************************主程序******************************************/
void loop()
{
    int n = 0;
    uchar hour_1, hour_2, min_1, min_2, sec_1, sec_2;
    uchar old_hour_1, old_hour_2, old_min_1, old_min_2, old_sec_1, old_sec_2; 
    read_1302_time();
    old_hour_1 = tim[8];
    old_hour_2 = tim[9];
    old_min_1 = tim[10];
    old_min_2 = tim[11];
    old_sec_1 = tim[12];
    old_sec_2 = tim[13];
    make_table_h1(old_hour_1);
    make_table_h2(old_hour_2);
    make_table_m1(old_min_1);
    make_table_m2(old_min_2);
    make_table_s1(old_sec_1);
    make_table_s2(old_sec_2);
    time_table[1][11] = 1;
    time_table[2][11] = 1;
    time_table[4][11] = 1;
    time_table[5][11] = 1;
    transform();
    for (size_t i = 1; i < 9; i++)
    {
        Write_Max7219_1(i, max7219_4[i-1]);
        Write_Max7219_2(i, max7219_3[i-1]);
        Write_Max7219_3(i, max7219_2[i-1]);
        Write_Max7219_4(i, max7219_1[i-1]);
    }
    /*while(1)
    {   
        n = n + 1;
        Write_Max7219_1(0x01, 0x00);
        uchar i;
        read_1302_time();
        hour_1 = tim[8];
        hour_2 = tim[9];
        min_1 = tim[10];
        min_2 = tim[11];
        sec_1 = tim[12];
        sec_2 = tim[13];
        if(old_hour_1 != hour_1)
        {
            old_hour_1 = hour_1;
            make_table_h1(old_hour_1);
        }
        if(old_hour_2 != hour_2)
        {
            old_hour_2 = hour_2;
            make_table_h2(hour_2);
        }
        if(old_min_1 != min_1)
        {
            old_min_1 = min_1;
            make_table_m1(min_1);
        }
        if(old_min_2 != min_2)
        {
            old_min_2 = min_2;
            make_table_m2(min_2);
        }
        if(old_sec_1 != sec_1)
        {
            old_sec_1 = sec_1;
            make_table_s1(old_sec_1);
        }
        if(old_sec_2 != sec_2)
        {
            old_sec_2 = sec_2;
            make_table_s2(old_sec_2);
        }
        transform();
        for (size_t i = 1; i < 9; i++)
        {
            Write_Max7219_1(i, max7219_1[i-1]);
            Write_Max7219_2(i, max7219_2[i-1]);
            Write_Max7219_3(i, max7219_3[i-1]);
            Write_Max7219_4(i, max7219_4[i-1]);
        }
        if (n == 50)
        {
            clear_max();
            delay(500);
            n = 0;
        }
    }*/
}
