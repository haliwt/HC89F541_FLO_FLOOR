/**
*   ************************************************************************************
*								上海芯圣电子股份有限公司
*								    www.holychip.cn
*	************************************************************************************
*	@Examle Version		V1.0.0.0
*	@Demo Version		V1.0.1.0
*	@Date				2017.09.18
*	************************************************************************************
*									 模块性能介绍
*	1、输入（无SMT）模式下VDD=5V时，低电平即输入低电压（VIL1）范围为0~1.5V、高电平即输入
*	   高电压（VIH1）范围为3.5~5V。
*	2、输入（SMT）模式下VDD=5V时，低电平即输入低电压（VIL1）范围为0~1V、高电平即输入高电
*	   压（VIH1）范围为4~5V。
*	3、P0xDBCT [5:0]配置的消抖时间是一个范围，分频系数*Tosc*P0xDBCT[5:0]-Tosc<消抖时间<
*	   分频系数*Tosc*(P0xDBCT[5:0]+1)-Tosc。
	4、HC89F003上电复位以及其它复位功能的复位，所有的IO相关寄存器都会恢复为默认值。
*	************************************************************************************
*									 应用注意事项
*	1、在使用仿真器时，与JTAG复用的IO口会有读取或写入数据异常，因此建议使用仿真器时不要
*	   操作这几个IO口。断开仿真器使用电源供电即可以正常操作。
*	2、分配到P0.0/P0.1/P0.2这三个管脚上的功能脚、外部中断输入、故障检测引脚都受消抖控制。
*   3、HC89F003自B版及其以后版本，IO口P23、P24、P25、P27口增加了上下拉输入同时使能的功能，
       但是不可以使用带上拉输入以及带下拉输入，但是可以使用带施密特上拉输入以及带施密特
       下拉输入，具体详见DateSheet。（关于芯片版本问题可以询问代理商以及原厂业务）
*	************************************************************************************
*  								       客户服务
*	感谢您使用我们的单片机，若发现错误或对函数的使用存在疑问。请添加上海芯圣电子官方QQ群
*	****************************技术支持群：201030494***********************************
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

	/************************************系统初始化****************************************/
	WDTCCR = 0x00;						//关闭看门狗

	while((CLKCON&0x20)!=0x20);			//等待内部高频晶振起振
	CLKSWR = 0x51;						//选择内部高频时钟为主时钟，内部高频RC2分频，Fosc=16MHz
	while((CLKSWR&0xC0)!=0x40);			//等待内部高频切换完成
	CLKDIV = SYS;						//Fosc1分频得到Fcpu，Fcpu=16MHz
}



/***************************************************************************************
  * @实现效果	将P02端口的上拉电阻设置为100K
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
	InitFanEdgeIO(); //喷水马达
	InitLed();
	InitKey();
	InitPowerIn();
	InitPowerStatus();

	ADCtl=1;
	LedBlueON();
	RunMode=0;  //运行模式
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
		 if(BatterCharge ==1){
		 	if(BatterTime >1 && BatterTime <3){
			 //BatterTime =0;
		 	 LedBlueOff();
             LedRedON();
		 	}
            if(BatterTime >=3 && BatterTime < 5){
		       BatterTime =0;
		       LedRedOff();
			   LedBlueOff();
             }
		 }
		 if(CurrentValue==0){
		      CheckRun();
			
		 }
		 else AllStop();
	     kk=ReadKey();
	     CheckMode(kk);
	}

}
/***********************************************************
	**
	*TIMER 1 中断程序:每0.1ms ，进入中断一次
	*
	**
***********************************************************/
void TIMER1_Rpt(void) interrupt TIMER1_VECTOR
{
  static INT8U idata t_10ms;
  static INT8U idata t_100ms;
  static INT8U idata t_1s;
  t_10ms++;
  ReadAD5ms();//检测IR 障碍物, IR pmw power


  if(t_10ms>99) //100 * 0.1ms = 10ms
  {
  	t_10ms=0;
	t_100ms++;
	t_1s++;
	
	 RunMs++;
 	 CheckLeftMotorSpeed(); //控制一定速度
	 CheckRightMotorSpeed(); //
	 AdjustSpeed(); //调节速度
	if(t_100ms>9)//10 *10ms =100ms
	{
	  if(ReadPowerStatus()) //P1_7 ==1(charge batter is over) OK 电池管理芯片，
	    PowerCountOK++; //charge batter is over flag.
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
	  BatterTime++;
	  PumpTime++;
      RunSecond++;
	  ///*
	  
	  Usart1Send[0]=15; //printf 15 number output
	  Usart1Send[1]=Voltage/100;
	  Usart1Send[2]=Voltage%100;
	  Usart1Send[3]=GroundDp[0]; //ir_L
	  Usart1Send[4]=GroundDp[1]; //ir_M
	  Usart1Send[5]=GroundDp[2]; //ir_R 
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

	  if(Usart1Send[6] > 0xC1 || Usart1Send[7]> 0xC1)
	  	 CurrentValue =1;
	  else CurrentValue =0;
	  if(Usart1Send[1] ==0x09){
	  	if(Usart1Send[2]>0x40)
			BatterCharge =1;
		else BatterCharge =0;
		
	  }
	  else BatterCharge =0;
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
	WDTC &=~ 0x20;						//清除WDT中断标志位
}
/***************************************************************************************
  * @说明  	INT8-17中断服务函数
  *	@参数	无
  * @返回值 无
  * @注		无
***************************************************************************************/
void INT8_17_Rpt() interrupt INT8_17_VECTOR 
{
	if(PINTF2&0x01)						//判断INT16中断标志位----L MOTOR SPEED
	{
	  LmotorSpeedNum ++ ;
	  PINTF2 &=0XFE;				//清除INT16中断标志位	--motor L speed 检测	
	  ReadLeftPulsed();
	  
	}
	else if(PINTF2&0x02)			//判断INT17中断标志位 -----R motor SPEED
	{
	  RmotorSpeedNum ++ ;
	  PINTF2 &=0XFD;				//清除INT17中断标志位	--马达 R speed 检测	
	  ReadRightPulsed();
	  
	}
	else if(PINTF1&0x80)			 //判断INT15中断标志位--P1_7 电池充电
	{
	  PINTF1 &=0X7f;				//清除INT15中断标志位---电池充电状态值		
	  PowerCountErr++;
	  PowerCountOK=0;
	}
	else
    {
	  //PINTF1 =0;
	  //PINTF2 =0;
	}
	

}