#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <math.h>

#define uchar unsigned char

uchar max7219_1[8];
uchar max7219_2[8];
uchar max7219_3[8];
uchar max7219_4[8];

char num[10][8]={
		{0xF0,0x90,0x90,0x90,0x90,0x90,0xF0,0x00},		//0
		{0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00},		//1
		{0xF0,0x10,0x10,0xF0,0x80,0x80,0xF0,0x00},		//2
		{0xF0,0x10,0x10,0xF0,0x10,0x10,0xF0,0x00},		//3
		{0x90,0x90,0x90,0xF0,0x10,0x10,0x10,0x00},		//4
		{0xF0,0x80,0x80,0xF0,0x10,0x10,0xF0,0x00},		//5
		{0xF0,0x80,0x80,0xF0,0x90,0x90,0xF0,0x00},		//6
		{0xF0,0x10,0x10,0x10,0x10,0x10,0x10,0x00},		//7
		{0xF0,0x90,0x90,0xF0,0x90,0x90,0xF0,0x00},		//8
		{0xF0,0x90,0x90,0xF0,0x10,0x10,0xF0,0x00}};		//9


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

int time_table[8][32];

int hour_1 = 2;
int hour_2 = 2;
int min_1 = 3;
int min_2 = 9;
int sec_1 = 5;
int sec_2 = 8;

void make_table_h1(int h1)
{
	int i,j;
	int n = 0;
	for(i=0;i<7;i++)
	{
		n = 0;
		for(j=1;j<5;j++)
		{
			time_table[i][j] = number1[h1][i][n];
			n = n + 1;
		}
	}
}

void make_table_h2(int h2)
{
	int i,j;
	int n = 0;
	for(i=0;i<7;i++)
	{
		n = 0;
		for(j=6;j<10;j++)
		{
			time_table[i][j] = number1[h2][i][n];
			n = n + 1;
		}
	}
}

void make_table_m1(int m1)
{
	int i,j;
	int n = 0;
	for(i=0;i<7;i++)
	{
		n = 0;
		for(j=13;j<17;j++)
		{
			time_table[i][j] = number1[m1][i][n];
			n = n + 1;
		}
	}
}

void make_table_m2(int m2)
{
	int i,j;
	int n = 0;
	for(i=0;i<7;i++)
	{
		n = 0;
		for(j=18;j<22;j++)
		{
			time_table[i][j] = number1[m2][i][n];
			n = n + 1;
		}
	}
}

void make_table_s1(int s1)
{
	int i,j;
	int m = 0;
	int n = 0;
	for(i=2;i<7;i++)
	{
		n = 0;
		for(j=23;j<26;j++)
		{
			time_table[i][j] = number2[s1][m][n];
			n = n + 1;
		}
		m = m + 1;
	}
}

void make_table_s2(int s2)
{
	int i,j;
	int m = 0;
	int n = 0;
	for(i=2;i<7;i++)
	{
		n = 0;
		for(j=27;j<30;j++)
		{
			time_table[i][j] = number2[s2][m][n];
			n = n + 1;
		}
		m = m + 1;
	}
}

void transform1()
{
	uchar hex1[16]={0x00,0x10,0x20,0x30,0x40,0x50,0x60,0x70,0x80,0x09,0xa0,0xb0,0xc0,0xd0,0xe0,0xf0};
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

void main()
{
	make_table_h1(hour_1);
	make_table_h2(hour_2);
	make_table_m1(min_1);
	make_table_m2(min_2);
	make_table_s1(sec_1);
	make_table_s2(sec_2);
	time_table[11][1] = '1';
	time_table[11][2] = '1';
	time_table[11][4] = '1';
	time_table[11][5] = '1';
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			printf("%d  ", time_table[i][j]);
		}
		printf("\n");
	}
	transform1();
}