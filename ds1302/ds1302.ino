unsigned char add_write[] = {0x8C,0x8A,0x88,0x86,0x84,0x82,0x80};//年星月日时分秒
unsigned char add_read[] = {0x8D,0x8B,0x89,0x87,0x85,0x83,0x81};
unsigned char tim0[] = {20,6,12,31,14,30,0};
unsigned char tim_bcd[7];
unsigned char tim[14];


#define ce 2
#define io 0
#define clk 4


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

//显示时间函数
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

void setup()
{
    pinMode(clk,OUTPUT);
    pinMode(ce,OUTPUT);
    pinMode(io,INPUT);
    Serial.begin(9600);
    ds1302_initial();
}

void loop()
{
    read_1302_time();
    display_ds1302time();
    delay(2000);
}