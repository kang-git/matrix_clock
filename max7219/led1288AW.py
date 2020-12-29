# -*-coding:UTF-8 -*-
import RPi.GPIO as GPIO
import time

row = [17,18,27,22,23,24,25,4]
col = [5,6,13,19,26,12,16,20]



GPIO.setmode(GPIO.BCM)
for i in range(8):
    GPIO.setup(row[i], GPIO.OUT)
    GPIO.setup(col[i], GPIO.OUT)


# 所有点亮
def allighton():
    for i in range(8):
        GPIO.output(row[i],GPIO.LOW)
        GPIO.output(col[i],GPIO.HIGH)

# 所有点灭
def allightoff():
    for i in range(8):
        GPIO.output(row[i],GPIO.HIGH)
        GPIO.output(col[i],GPIO.LOW)

# 瀑布亮
def lightonbyline():
    allightoff()
    for i in range(8):
        GPIO.output(col[i],GPIO.HIGH)
    for j in range(8):
        GPIO.output(row[j],GPIO.LOW)
        time.sleep(0.03)


# 瀑布灭
def lightoffbyline():
    for i in range(8):
        GPIO.output(row[i],GPIO.HIGH)
        time.sleep(0.03)
    for j in range(8):
        GPIO.output(col[j],GPIO.LOW)

# 单独一个点
def singlepoint():
    r = int(input("请输入行号："))
    c = int(input("请输入列号："))
    GPIO.output(row[r-1], GPIO.LOW)
    GPIO.output(col[c-1], GPIO.HIGH)
    time.sleep(2) 


# 流水灯效果
def deliver():
    for i in range(8):
        for j in range(8):
            GPIO.output(row[i], GPIO.LOW)
            GPIO.output(col[j], GPIO.HIGH)
            time.sleep(0.05)
            GPIO.output(col[j], GPIO.LOW)
            GPIO.output(row[i], GPIO.HIGH)



if __name__ == "__main__":
    while True:
        allighton()
        time.sleep(1)
        allightoff()
        time.sleep(2)
        deliver()
        singlepoint()
        allightoff()
        time.sleep(0.5)
        lightonbyline()
        time.sleep(1)
        lightoffbyline()
