/**
*   ************************************************************************************
*								�Ϻ�оʥ���ӹɷ����޹�˾
*								    www.holychip.cn
*	************************************************************************************
*	@Examle Version		V1.0.0.0
*	@Demo Version		V1.0.1.0
*	@Date				2017.09.18
*	************************************************************************************
*									 ģ�����ܽ���
*	1�����루��SMT��ģʽ��VDD=5Vʱ���͵�ƽ������͵�ѹ��VIL1����ΧΪ0~1.5V���ߵ�ƽ������
*	   �ߵ�ѹ��VIH1����ΧΪ3.5~5V��
*	2�����루SMT��ģʽ��VDD=5Vʱ���͵�ƽ������͵�ѹ��VIL1����ΧΪ0~1V���ߵ�ƽ������ߵ�
*	   ѹ��VIH1����ΧΪ4~5V��
*	3��P0xDBCT [5:0]���õ�����ʱ����һ����Χ����Ƶϵ��*Tosc*P0xDBCT[5:0]-Tosc<����ʱ��<
*	   ��Ƶϵ��*Tosc*(P0xDBCT[5:0]+1)-Tosc��
	4��HC89F003�ϵ縴λ�Լ�������λ���ܵĸ�λ�����е�IO��ؼĴ�������ָ�ΪĬ��ֵ��
*	************************************************************************************
*									 Ӧ��ע������
*	1����ʹ�÷�����ʱ����JTAG���õ�IO�ڻ��ж�ȡ��д�������쳣����˽���ʹ�÷�����ʱ��Ҫ
*	   �����⼸��IO�ڡ��Ͽ�������ʹ�õ�Դ���缴��������������
*	2�����䵽P0.0/P0.1/P0.2�������ܽ��ϵĹ��ܽš��ⲿ�ж����롢���ϼ�����Ŷ����������ơ�
*   3��HC89F003��B�漰���Ժ�汾��IO��P23��P24��P25��P27������������������ͬʱʹ�ܵĹ��ܣ�
       ���ǲ�����ʹ�ô����������Լ����������룬���ǿ���ʹ�ô�ʩ�������������Լ���ʩ����
       �������룬�������DateSheet��������оƬ�汾�������ѯ�ʴ������Լ�ԭ��ҵ��
*	************************************************************************************
*  								       �ͻ�����
*	��л��ʹ�����ǵĵ�Ƭ���������ִ����Ժ�����ʹ�ô������ʡ��������Ϻ�оʥ���ӹٷ�QQȺ
*	****************************����֧��Ⱥ��201030494***********************************
*   ************************************************************************************
**/
#define	ALLOCATE_EXTERN
#define	ver 5

#include "HC89F0541.h"

#include "..\lib\LB_Led.h"
#include "..\lib\LB_AD.h"
#include "..\lib\LB_Usart.h"
#include "..\lib\LB_eeprom.h"
#include "..\lib\LB_Motor.h"

#include "..\lib\LB_Run.h"

void InitSysclk(INT8U SYS)
{

	/************************************ϵͳ��ʼ��****************************************/
	WDTCCR = 0x00;						//�رտ��Ź�

	while((CLKCON&0x20)!=0x20);			//�ȴ��ڲ���Ƶ��������
	CLKSWR = 0x51;						//ѡ���ڲ���Ƶʱ��Ϊ��ʱ�ӣ��ڲ���ƵRC2��Ƶ��Fosc=16MHz
	while((CLKSWR&0xC0)!=0x40);			//�ȴ��ڲ���Ƶ�л����
	CLKDIV = SYS;						//Fosc1��Ƶ�õ�Fcpu��Fcpu=16MHz
}



/***************************************************************************************
  * @ʵ��Ч��	��P02�˿ڵ�������������Ϊ100K
***************************************************************************************/
void main(void)
{

	INT8U kk;
	INT8U  abc;
	InitSysclk(1);

	InitT1();
	InitADIO();
	Init_MotorSpeed();
    InitMotorIO();
	Init_Usart1();
	InitFanEdgeIO(); //��ˮ����
	InitLed();
	InitKey();
	InitPowerIn();
	InitPowerStatus();

	ADCtl=1;
	LedBlueON();
	RunMode=0;  //����ģʽ
	RunStep=0;
	RunSecond=0;
	LCurrent=0;
	RCurrent=0;
	
    Mode=1;
    Step=0;
	abc=0;
	
while(1)
	{

	   
	   CheckGround();
	   CheckRun();
	   kk=ReadKey();
       CheckMode(kk);
	  
	  }

}
/***********************************************************
	**
	*�жϳ���:ÿ0.1ms �������ж�һ��
	*
	**
***********************************************************/
void TIMER1_Rpt(void) interrupt TIMER1_VECTOR
{
  static INT8U idata t_10ms;
  static INT8U idata t_100ms;
  static INT8U idata t_1s;
  t_10ms++;
  ReadAD5ms();//���IR �ϰ���

  if(t_10ms>99) //10ms
  {
  	t_10ms=0;
	t_100ms++;
	t_1s++;
	RunMs++;
 	 CheckLeftMotorSpeed(); //����һ���ٶ�
	 CheckRightMotorSpeed(); //
	 AdjustSpeed(); //�����ٶ�
	if(t_100ms>9)//10 *10ms =100ms
	{
	  if(ReadPowerStatus()) //P1_7 ==1 OK ��ع���оƬ��
	    PowerCountOK++;
	  t_100ms=0;
	  CheckLCurrent();
	  CheckRCurrent();
	  NoImpSecond++;
	}
	
	CheckEdgeCurrent();
	CheckVoltage();
	if(t_1s>99) //100 * 10ms = 1000ms =1s
	{
	  t_1s=0;
	  PumpTime++;
      PowerSavingTime++ ;
	   RunSecond++;
	  ///*
	  
	  Usart1Send[0]=15; //printf 15 number output
	  Usart1Send[1]=0x0A;//Voltage/100;
	  Usart1Send[2]=0x0B;//Voltage%100;
	  Usart1Send[3]=GroundDp[0];
	  Usart1Send[4]=GroundDp[1];
	  Usart1Send[5]=GroundDp[2];
	  Usart1Send[6]=LCurrent/10;
	  Usart1Send[7]=RCurrent/10;

	  Usart1Send[8]=LeftMoveMotorData.AvgSpeed;
	  Usart1Send[9]=RightMoveMotorData.AvgSpeed;
	  Usart1Send[10]=LeftMoveMotorData.OutPWM;
	  Usart1Send[11]=RightMoveMotorData.OutPWM;
	  Usart1Send[12]=RunMode;
	  Usart1Send[13]=RunStep;
	  Usart1Send[14]=Mode;
	  Usart1Send[15]=Step;
	  SendCount=1;
	  SBUF=Usart1Send[SendCount];
	 //*/
	  /*
	  Usart1Send[0]=13;
	  Usart1Send[1]=LeftIR.Left;
	  Usart1Send[2]=LeftIR.Right;
	  Usart1Send[3]=LeftIR.Mid;
	  Usart1Send[4]=LeftIR.Top;

	  Usart1Send[5]=MidIR.Left;
	  Usart1Send[6]=MidIR.Right;
	  Usart1Send[7]=MidIR.Mid;
	  Usart1Send[8]=MidIR.Top;

	  Usart1Send[9]=RightIR.Left;
	  Usart1Send[10]=RightIR.Right;
	  Usart1Send[11]=RightIR.Mid;
	  Usart1Send[12]=RightIR.Top;

	  Usart1Send[13]=RunStep;
	  SendCount=1;
	  SBUF=Usart1Send[SendCount];
  	  */
	  //SBUF=Usart1Send[SendCount];	
	}
  }
}
void WDT_Rpt() interrupt WDT_VECTOR
{
	WDTC &=~ 0x20;						//���WDT�жϱ�־λ
}
/***************************************************************************************
  * @˵��  	INT8-17�жϷ�����
  *	@����	��
  * @����ֵ ��
  * @ע		��
***************************************************************************************/
void INT8_17_Rpt() interrupt INT8_17_VECTOR 
{
	if(PINTF2&0x01)						//�ж�INT16�жϱ�־λ----L MOTOR SPEED
	{
	 // LmotorSpeedNum ++ ;
	  PINTF2 &=0XFE;				//���INT16�жϱ�־λ	--motor L speed ���	
	  ReadLeftPulsed();
	  
	}
	else if(PINTF2&0x02)			//�ж�INT17�жϱ�־λ -----R motor SPEED
	{
	  RmotorSpeedNum ++ ;
	  PINTF2 &=0XFD;				//���INT17�жϱ�־λ	--���� R speed ���	
	  ReadRightPulsed();
	  
	}
	else if(PINTF1&0x80)			 //�ж�INT15�жϱ�־λ--��س��
	{
	  PINTF1 &=0X7f;				//���INT15�жϱ�־λ---��س��״ֵ̬		
	  PowerCountErr++;
	  PowerCountOK=0;
	}
	else
    {
	  //PINTF1 =0;
	  //PINTF2 =0;
	}
	

}