#include <SHT1x.h>
#define unsigned char uchar

//#define I2C_SDA A4
//#define I2C_SCL A5
#define dataPin 8
#define clockPin 9
//SHT1x sht1x(dataPin, clockPin);


//I2C传输启动
void I2C_Start()
{
    digitalWrite(I2C_SDA, HIGH);
    digitalWrite(I2C_SCL, HIGH);
    _delay_us(5);
    digitalWrite(I2C_SDA, LOW);
    _delay_us(5);
    digitalWrite(I2C_SCL, LOW);
    _delay_us(5);
}

//I2C传输停止
void I2C_Stop()
{
    digitalWrite(I2C_SDA, LOW);
    _delay_us(5);
    digitalWrite(I2C_SCL, HIGH);
    _delay_us(5);
    digitalWrite(I2C_SDA, HIGH);
    _delay_us(5);
}

//I2C发送一个字节，在SCL时钟高电平器件保持信号SDA稳定
void I2C_sendbyte(uchar dat)
{
    
}

//AHT10初始化：状态使能位Bit[3]是否为1,
void init_AHT10()
{
    I2C_Start();

    I2C_WriteByte(0x70);
    ack_status = Receive_ACK();

    if(ack_status) printf("3");
    else printf("3-n-");    
    
    I2C_WriteByte(0xE1);
    ack_status = Receive_ACK();
    
    if(ack_status) printf("4");
    else printf("4-n-");
    
    I2C_WriteByte(0x08);
    ack_status = Receive_ACK();
    
    if(ack_status) printf("5");
    else printf("5-n-");
    
    I2C_WriteByte(0x00);
    ack_status = Receive_ACK();
    
    if(ack_status) printf("6");
    else printf("6-n-");
    
    I2C_Stop();
}


void setup()
{
    Serial.begin(9600);
	pinMode(I2C_SDA, INPUT);
	pinMode(I2C_SCL, OUTPUT);
}

void loop()
{
	float tempC = sht1x.readTemperatureC();
    float humidity = sht1x.readHumidity();
    Serial.print("摄氏温度: ");
    Serial.println(tempC);
    Serial.print("相对湿度: ");
    Serial.println(humidity);
    delay(3000);
}
