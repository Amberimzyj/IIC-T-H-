#include "stm32f10x.h"
#include "sys.h"
#include "usart.h"
#include "led.h"
#include "delay.h"
#include "myiic.h"
#include "AM2320.h"


int main(void)
{
//    u16 t;
//    u16 len;
    u16 times = 0;
    u16 temp;
    u16 humid;
    u32  data;
    float temp1;     //温度数据
    float humid1;    //湿度数据
    delay_init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //设置NVIC中断分组2
    usart_init(115200);    //串口初始化波特率
    LED_Init();       //LED端口初始化
    AM2320_Init();    //初始化IIC





    while (1)
    {

        //唤醒传感器并发送读指令
        AM2320_Wakeup();
        AM2320_Send_Read();
        delay_ms(3);
        //将读取的数据转换为百进制温湿度
        data = AM2320_Read() ;
        humid = data >> 16;
        humid1 = humid / 10.0; //((humid / 256) * 256 + ((humid % 256) / 16) * 16 + ((humid % 256) % 16)) * 1.0 / 10;
        temp = data;
        temp1 = temp / 10.0; //(temp / 256) * 256 + ((temp % 256) / 16) * 16 + ((temp % 256) % 16)) * 1.0 / 10;

        times++;
        if (times % 1 == 0)
        {
            LED0 = !LED0;
            times = 0;
        }

        printf("\r\n当前温度为：%g℃\r\n", temp1);
        printf("\r\n当前湿度为：%g%%RH\r\n\r\n", humid1);

        delay_ms(1000);
        delay_ms(1000);
    }

}

