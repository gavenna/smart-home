#ifndef __SENSOR_H__
#define __SENSOR_H__

void Sensor_Run();

int serial_init(char *file, int speed);

/*
       发送的信息：
           开发板发送给传感器的指令格式：帧头+指令+校验和(8bit)
           帧头和校验和是用来“验证身份”的
           指令才是用来表达此次通信的目的
           各占一个字节，共三个字节
           帧头：0xa5
           指令：
                   只请求光照： 10000001 -> 0x81
                   只请求温湿度气压海拔：10000010 -> 0x82
                   两种都请求：10000011 -> 0x83
           检验和：
                   等于帧头加上指令，只保存低8位
               0xa5 + 0x81  -> 0x26
*/
void *gy_39(void *arg);

#endif