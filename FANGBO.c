
#include <reg52.h>

sbit PWMOUT = P2^1;

sbit LED1 = P2^3;

sbit LED2 =	P2^2;

sbit LED3 =	P2^1;

sbit LED4 =	P2^0;

sbit KEY1 = P3^2;

sbit KEY2 = P3^3;

sbit KEY3 = P3^0;

sbit KEY4 = P3^1;

 

unsigned char HighRH = 0;  //高电平重载值的高字节

unsigned char HighRL = 0;  //高电平重载值的低字节

unsigned char LowRH  = 0;  //低电平重载值的高字节

unsigned char LowRL  = 0;  //低电平重载值的低字节

 

void ConfigPWM(unsigned int fr, unsigned char dc);

void ClosePWM();

void delay();

 

void main()

{

    unsigned int i;

	bit backup1 = 1;

	bit backup2 = 1;

	bit backup3 = 1;

	bit backup4 = 1;

	bit keybuf1 = 1;  //按键值暂存，临时保存按键的扫描值

    bit keybuf2 = 1;  //按键值暂存，临时保存按键的扫描值

	bit keybuf3 = 1;  //按键值暂存，临时保存按键的扫描值

    bit keybuf4 = 1;  //按键值暂存，临时保存按键的扫描值

	unsigned int a=100;

    

    EA=1;

 

    while (1)

    {

		  

		keybuf1 = KEY1;            //把当前扫描值暂存

        if (keybuf1 != backup1)     //当前值与前次值不相等说明此时按键有动作

        {

            delay();              //延时大约10ms

            if (keybuf1 == KEY1)   //判断扫描值有没有发生改变，即按键抖动

            {

               if (backup1 == 0)  //如果前次值为0，则说明当前是弹起动作

                  {

                    a = a-1000;      

                }

                backup1 = keybuf1;  //更新备份为当前值，以备进行下次比较

            }

        }

		keybuf2 = KEY2;            //把当前扫描值暂存

        if (keybuf2 != backup2)     //当前值与前次值不相等说明此时按键有动作

        {

            delay();              //延时大约10ms

            if (keybuf2 == KEY2)   //判断扫描值有没有发生改变，即按键抖动

            {

                if (backup2 == 0)  //如果前次值为0，则说明当前是弹起动作

                {

                    a = a+1000;      

                }

                backup2 = keybuf2;  //更新备份为当前值，以备进行下次比较

            }

        }

		keybuf3 = KEY3;            //把当前扫描值暂存

        if (keybuf3 != backup3)     //当前值与前次值不相等说明此时按键有动作

        {

            delay();              //延时大约10ms

            if (keybuf3 == KEY3)   //判断扫描值有没有发生改变，即按键抖动

            {

               if (backup3 == 0)  //如果前次值为0，则说明当前是弹起动作

                  {

                    a = a-100;      

                }

                backup3 = keybuf3;  //更新备份为当前值，以备进行下次比较

            }

        }
		keybuf4 = KEY4;            //把当前扫描值暂存

        if (keybuf4 != backup4)     //当前值与前次值不相等说明此时按键有动作

        {

            delay();              //延时大约10ms

            if (keybuf4 == KEY4)   //判断扫描值有没有发生改变，即按键抖动

            {

               if (backup4 == 0)  //如果前次值为0，则说明当前是弹起动作

                  {

                    a = a+100;      

                }

                backup4 = keybuf4;  //更新备份为当前值，以备进行下次比较

            }

        }

			 ConfigPWM(a, 50);   

             for (i=0; i<40000; i++);

	         ClosePWM();

			  if ((a <= 50)||(a >= 150))

              {             

                    LED1 = 0;

					LED2 = 0;

					LED3 = 0;

					LED4 = 0; 

              }  

		      else 

			  {

			  	    LED1 = 1;

					LED2 = 1;

					LED3 = 1;

					LED4 = 1; 

			  }     

    }

}

/* 配置并启动PWM，fr-频率，dc-占空比 */

void ConfigPWM(unsigned int fr, unsigned char dc)

{

    unsigned int  high, low;

    unsigned long tmp;

    

    tmp  = ((11059200/12) / fr) ;  //计算一个周期所需的计数值

    high = (tmp*dc) / 100;      //计算高电平所需的计数值

    low  = tmp - high;          //计算低电平所需的计数值

    high = 65536 - high + 12;   //计算高电平的重载值并补偿中断延时

    low  = 65536 - low  + 12;   //计算低电平的重载值并补偿中断延时

    HighRH = (unsigned char)(high>>8); //高电平重载值拆分为高低字节

    HighRL = (unsigned char)high;

    LowRH  = (unsigned char)(low>>8);  //低电平重载值拆分为高低字节

    LowRL  = (unsigned char)low;

    TMOD &= 0xF0;   //清零T0的控制位

    TMOD |= 0x01;   //配置T0为模式1

    TH0 = HighRH;   //加载T0重载值

    TL0 = HighRL;

    ET0 = 1;        //使能T0中断

    TR0 = 1;        //启动T0

    PWMOUT = 1;     //输出高电平

}

/* 关闭PWM */

void ClosePWM()

{

    TR0 = 0;     //停止定时器

    ET0 = 0;     //禁止中断

    PWMOUT = 1;  //输出高电平

}

/* T0中断服务函数，产生PWM输出 */

void InterruptTimer0() interrupt 1

{

    if (PWMOUT == 1)  //当前输出为高电平时，装载低电平值并输出低电平

    {

        TH0 = LowRH;

        TL0 = LowRL;

        PWMOUT = 0;

    }

    else              //当前输出为低电平时，装载高电平值并输出高电平

    {

        TH0 = HighRH;

        TL0 = HighRL;

        PWMOUT = 1;

    }

}

/* 软件延时函数，延时约10ms */

void delay()

{

    unsigned int j = 1000;

	

    while (j--);

}
