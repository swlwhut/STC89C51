
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

 

unsigned char HighRH = 0;  //�ߵ�ƽ����ֵ�ĸ��ֽ�

unsigned char HighRL = 0;  //�ߵ�ƽ����ֵ�ĵ��ֽ�

unsigned char LowRH  = 0;  //�͵�ƽ����ֵ�ĸ��ֽ�

unsigned char LowRL  = 0;  //�͵�ƽ����ֵ�ĵ��ֽ�

 

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

	bit keybuf1 = 1;  //����ֵ�ݴ棬��ʱ���水����ɨ��ֵ

    bit keybuf2 = 1;  //����ֵ�ݴ棬��ʱ���水����ɨ��ֵ

	bit keybuf3 = 1;  //����ֵ�ݴ棬��ʱ���水����ɨ��ֵ

    bit keybuf4 = 1;  //����ֵ�ݴ棬��ʱ���水����ɨ��ֵ

	unsigned int a=100;

    

    EA=1;

 

    while (1)

    {

		  

		keybuf1 = KEY1;            //�ѵ�ǰɨ��ֵ�ݴ�

        if (keybuf1 != backup1)     //��ǰֵ��ǰ��ֵ�����˵����ʱ�����ж���

        {

            delay();              //��ʱ��Լ10ms

            if (keybuf1 == KEY1)   //�ж�ɨ��ֵ��û�з����ı䣬����������

            {

               if (backup1 == 0)  //���ǰ��ֵΪ0����˵����ǰ�ǵ�����

                  {

                    a = a-1000;      

                }

                backup1 = keybuf1;  //���±���Ϊ��ǰֵ���Ա������´αȽ�

            }

        }

		keybuf2 = KEY2;            //�ѵ�ǰɨ��ֵ�ݴ�

        if (keybuf2 != backup2)     //��ǰֵ��ǰ��ֵ�����˵����ʱ�����ж���

        {

            delay();              //��ʱ��Լ10ms

            if (keybuf2 == KEY2)   //�ж�ɨ��ֵ��û�з����ı䣬����������

            {

                if (backup2 == 0)  //���ǰ��ֵΪ0����˵����ǰ�ǵ�����

                {

                    a = a+1000;      

                }

                backup2 = keybuf2;  //���±���Ϊ��ǰֵ���Ա������´αȽ�

            }

        }

		keybuf3 = KEY3;            //�ѵ�ǰɨ��ֵ�ݴ�

        if (keybuf3 != backup3)     //��ǰֵ��ǰ��ֵ�����˵����ʱ�����ж���

        {

            delay();              //��ʱ��Լ10ms

            if (keybuf3 == KEY3)   //�ж�ɨ��ֵ��û�з����ı䣬����������

            {

               if (backup3 == 0)  //���ǰ��ֵΪ0����˵����ǰ�ǵ�����

                  {

                    a = a-100;      

                }

                backup3 = keybuf3;  //���±���Ϊ��ǰֵ���Ա������´αȽ�

            }

        }
		keybuf4 = KEY4;            //�ѵ�ǰɨ��ֵ�ݴ�

        if (keybuf4 != backup4)     //��ǰֵ��ǰ��ֵ�����˵����ʱ�����ж���

        {

            delay();              //��ʱ��Լ10ms

            if (keybuf4 == KEY4)   //�ж�ɨ��ֵ��û�з����ı䣬����������

            {

               if (backup4 == 0)  //���ǰ��ֵΪ0����˵����ǰ�ǵ�����

                  {

                    a = a+100;      

                }

                backup4 = keybuf4;  //���±���Ϊ��ǰֵ���Ա������´αȽ�

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

/* ���ò�����PWM��fr-Ƶ�ʣ�dc-ռ�ձ� */

void ConfigPWM(unsigned int fr, unsigned char dc)

{

    unsigned int  high, low;

    unsigned long tmp;

    

    tmp  = ((11059200/12) / fr) ;  //����һ����������ļ���ֵ

    high = (tmp*dc) / 100;      //����ߵ�ƽ����ļ���ֵ

    low  = tmp - high;          //����͵�ƽ����ļ���ֵ

    high = 65536 - high + 12;   //����ߵ�ƽ������ֵ�������ж���ʱ

    low  = 65536 - low  + 12;   //����͵�ƽ������ֵ�������ж���ʱ

    HighRH = (unsigned char)(high>>8); //�ߵ�ƽ����ֵ���Ϊ�ߵ��ֽ�

    HighRL = (unsigned char)high;

    LowRH  = (unsigned char)(low>>8);  //�͵�ƽ����ֵ���Ϊ�ߵ��ֽ�

    LowRL  = (unsigned char)low;

    TMOD &= 0xF0;   //����T0�Ŀ���λ

    TMOD |= 0x01;   //����T0Ϊģʽ1

    TH0 = HighRH;   //����T0����ֵ

    TL0 = HighRL;

    ET0 = 1;        //ʹ��T0�ж�

    TR0 = 1;        //����T0

    PWMOUT = 1;     //����ߵ�ƽ

}

/* �ر�PWM */

void ClosePWM()

{

    TR0 = 0;     //ֹͣ��ʱ��

    ET0 = 0;     //��ֹ�ж�

    PWMOUT = 1;  //����ߵ�ƽ

}

/* T0�жϷ�����������PWM��� */

void InterruptTimer0() interrupt 1

{

    if (PWMOUT == 1)  //��ǰ���Ϊ�ߵ�ƽʱ��װ�ص͵�ƽֵ������͵�ƽ

    {

        TH0 = LowRH;

        TL0 = LowRL;

        PWMOUT = 0;

    }

    else              //��ǰ���Ϊ�͵�ƽʱ��װ�ظߵ�ƽֵ������ߵ�ƽ

    {

        TH0 = HighRH;

        TL0 = HighRL;

        PWMOUT = 1;

    }

}

/* �����ʱ��������ʱԼ10ms */

void delay()

{

    unsigned int j = 1000;

	

    while (j--);

}
