#include <SHT1x.h>
#define unsigned char uchar

//#define I2C_SDA A4
//#define I2C_SCL A5
#define dataPin A4
#define clockPin A5
SHT1x sht1x(dataPin, clockPin);

void setup()
{
    Serial.begin(9600);
	//pinMode(I2C_SDA, INPUT);
	//pinMode(I2C_SCL, OUTPUT);
}

/*
void I2C_Start()
{
    digitalWrite(I2C_SDA, HIGH);
    _delay_us(5);
    digitalWrite(I2C_SCL, HIGH);
    _delay_us(5);
    digitalWrite(I2C_SDA, LOW);
    _delay_us(5);
    digitalWrite(I2C_SDA, LOW);
    _delay_us(5);
}

void I2C_Stop()
{
    digitalWrite(I2C_SDA, LOW);
    _delay_us(5);
    digitalWrite(I2C_SCL, HIGH);
    _delay_us(5);
    digitalWrite(I2C_SDA, HIGH);
    _delay_us(5);
}
*/

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
