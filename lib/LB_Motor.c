/*

---------- file information -----------------------------------------------
file name: 
define   : <文件说明>
version  : 见文件尾端
---------------------------------------------------------------------------
*/

//全局变量声明
#define  KAKA_Motor_GB

#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else
//#include "LB_hc89f003_IO.h"
#include "..\include\HC89F0541.h"
#include "..\include\PJ_TypeRedefine.h"
#include "LB_Motor.h"

#endif

void Init_MotorSpeed()
{

	P3M4 = 0x68;			        	//P34设置为带SMT上拉输入,检查速度马达
	P3M5 = 0x68;			        	//P35设置为带SMT上拉输入,检测速度马达

							//INT16	17
 	PITS4 = 0x0F;						

    PINTE2 = 0x03;						//使能INT17 16
	IE2 |= 0x01;						//打开INT8-17中断
	EA=1;
	P3_4=1;
	P3_5=1;
	PINTE1=0;
}

void InitMotorIO(void)
{

    P1M1 = 0xC2;                        //P11设置为推挽输出
    P1M2 = 0xC2;                        //P12设置为推挽输出
    P1M3 = 0xC2;                        //P13设置为推挽输出
    P1M4 = 0xC2;                        //P14设置为推挽输出
    P1M6 = 0xC2;                        //P14设置为推挽输出，马达速度控制IO
  P1_1=0;
  P1_2=0;
  P1_3=0;
  P1_4=0;
  P1_6=0;

}

void InitFanEdgeIO(void)
{
    P3M3 = 0xC2;                        //P33设置为推挽输出,喷水马达，
    P3_3=1;
	PWM1_MAP = 0x33;					//PWM1通道映射P33口

    PWM1C = 0x00;						//PWM1高有效，PWM11高有效，时钟8分频 
    PWMM |= 0x10;						//PWM1工作于						

	//独立模式下，PWM0和PWM01共用一个周期寄存器
	//PWM0的占空比调节使用			PWM0组的占空比寄存器
	//PWM01的占空比调节使用			PWM0组的死区寄存器

	//周期计算 	= 0x03ff / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		约1.955kHz

	PWM1PH = 0x01;						//周期高4位设置为0x03
	PWM1PL = 0x0;						//周期低8位设置为0xFF

	//占空比计算= 0x0155 / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   占空比为 170.5/511.5 = 33.3%

	PWM1DH = 0x00;						//PWM1高4位占空比0x01
	PWM1DL = 0x00;						//PWM1低8位占空比0x55													    

	PWMEN |= 0x02;						//使能PWM1以及PWM11

}


void SetEdge(INT8U status)
{
   PWM1DL = status; //PWM占空比寄存器
}
/**************************************************************
	 *
	 *Function Name:void InitMotorRightForward(void)
	 *Function : motor run forward 
	 *
	 *
	 *
**************************************************************/
void InitMotorLeftForward(void)
{

    P1_3=0; //IN2
    P1_4=0; //IN1 
	///*
	PWM0_MAP = 0x14;					//PWM0通道映射P14口
    PWM0C = 0x01 ; //WT.EDIT 11.10//0x00; //motor 快						//PWM0高有效，PWM01高有效，时钟8分频 
    PWMM |= 0x10;						//PWM0工作于互补模式						

	//独立模式下，PWM0和PWM01共用一个周期寄存器
	//PWM0的占空比调节使用			PWM0组的占空比寄存器
	//PWM01的占空比调节使用			PWM0组的死区寄存器

	//周期计算 	= 0x03ff / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		约1.955kHz

	PWM0PH = 0x01;						//周期高4位设置为0x03
	PWM0PL = 0x0;						//周期低8位设置为0xFF

	//占空比计算= 0x0155 / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   占空比为 170.5/511.5 = 33.3%

	PWM0DH = 0x00;						//PWM0高4位占空比0x01
	PWM0DL = 0x60;						//PWM0低8位占空比0x55
	PWMEN |= 0x01;						//使能PWM0以及PWM01
   //*/
   //P1_4=1;
}
/**************************************************************
	*
	*Function Name:void InitMotorRightForward(void)
	*Function : motor run forward 
	*
	*
	*
**************************************************************/
 void InitMotorRightForward(void)
{
    P1_1=0;  //IN2 
    P1_2=0; //IN1 
	///*
	PWM01_MAP = 0x11;					//PWM01通道映射P11口
    PWM0C = 0x01;//WT.EDIT //0x00;						//PWM0高有效，PWM01高有效，时钟8分频 
    PWMM |= 0x10;						//PWM0工作于互补模式						

	//独立模式下，PWM0和PWM01共用一个周期寄存器
	//PWM0的占空比调节使用			PWM0组的占空比寄存器
	//PWM01的占空比调节使用			PWM0组的死区寄存器

	//周期计算 	= 0x03ff / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		约1.955kHz

	PWM0PH = 0x01;						//周期高4位设置为0x03
	PWM0PL = 0x0;						//周期低8位设置为0xFF

	//占空比计算= 0x0155 / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   占空比为 170.5/511.5 = 33.3%


	PWM0DTH = 0x00;						//PWM01高4位占空比0x01
	PWM0DTL = 0x60;						//PWM01低8位占空比0x55
	PWMEN |= 0x10;						//使能PWM0以及PWM01
   	//*/
	//P1_1=1;
}
/**************************************************************
	 *
	 *Function Name:void InitMotorLeftRetreat(void)
	 *Function : motor return run
	 *
	 *
	 *
**************************************************************/
void InitMotorLeftRetreat(void)
{

    P1_3=0; //IN2 --return back
    P1_4=0; //IN1
	///*
	PWM0_MAP = 0x13;					//PWM0通道映射P13口
    PWM0C = 0x01;//WT.EDIT//0x00;						//PWM0高有效，PWM01高有效，时钟8分频 
    PWMM |= 0x10;						//PWM0工作于独立模式			

	//独立模式下，PWM0和PWM01共用一个周期寄存器
	//PWM0的占空比调节使用			PWM0组的占空比寄存器
	//PWM01的占空比调节使用			PWM0组的死区寄存器

	//周期计算 	= 0x03ff / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		约1.955kHz

	PWM0PH = 0x01;						//周期高4位设置为0x03
	PWM0PL = 0x0;						//周期低8位设置为0xFF

	//占空比计算= 0x0155 / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   占空比为 170.5/511.5 = 33.3%

	PWM0DH = 0x00;						//PWM0高4位占空比0x01
	PWM0DL = 0x60;						//PWM0低8位占空比0x55
	PWMEN |= 0x01;						//使能PWM0以及PWM01
	//*/
	//P1_3=1; 
}
 /**************************************************************
	  *
	  *Function Name:void InitMotorRightRetreat(void)
	  *Function : motor return run
	  *
	  *
	  *
**************************************************************/
void InitMotorRightRetreat(void)
{
    P1_1=0;  //IN2 
    P1_2=0; //IN1  ---forward 
	///*
	PWM01_MAP = 0x12;					//PWM01通道映射P12口
    PWM0C = 0x01 ;                      //WT.EDIT 2020.22.20//0x00; //PWM0高有效，PWM01高有效，时钟8分频 
    PWMM |= 0x10;						//PWM0工作于互补模式						

	//独立模式下，PWM0和PWM01共用一个周期寄存器
	//PWM0的占空比调节使用			PWM0组的占空比寄存器
	//PWM01的占空比调节使用			PWM0组的死区寄存器

	//周期计算 	= 0x03ff / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		约1.955kHz

	PWM0PH = 0x01;						//周期高4位设置为0x03
	PWM0PL = 0x0;						//周期低8位设置为0xFF

	//占空比计算= 0x0155 / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   占空比为 170.5/511.5 = 33.3%


	PWM0DTH = 0x00;						//PWM01高4位占空比0x01
	PWM0DTL = 0x60;						//PWM01低8位占空比0x55
	PWMEN |= 0x10;						//使能PWM0以及PWM01
	//*/
	//P1_2=1;
}



void LeftStop()
{

   PWMEN &= 0xfe;

    P1_3=0;
    P1_4=0;
}

void RightStop()
{

   PWMEN &= 0xef;
    P1_1=0;
    P1_2=0;

}

void AllStop()
{
   PWMEN &= 0xee;
    P1_1=0;
    P1_2=0;
    P1_3=0;
    P1_4=0;
}

/**************************************************************
	  *
	  *Function Name:void ReadLeftPulsed(void)
	  *Function : motor return run
	  *
	  *
	  *
**************************************************************/
void ReadLeftPulsed(void)
{

	if((LeftMoveMotorData.MotorMode&0x03)==1)
	{
		LeftMoveMotorData.NowPulsed++;
		/*
		if(LeftMoveMotorData.NowPulsed>=(LeftMoveMotorData.MovePulsed+19))
		{
			LeftMoveMotorData.MovePulsed+=19;
			LeftMoveMotorData.RunCm++;
			if(LeftMoveMotorData.SetCm<=LeftMoveMotorData.RunCm)
			{
				LeftMoveMotorData.Flag=1;
				LeftMoveMotorData.MotorMode=0;
				LeftStop();
			}
		}
	   */
	}
	else if((LeftMoveMotorData.MotorMode&0x03)==2)
	{
		LeftMoveMotorData.NowPulsed--;
		/*
		if(LeftMoveMotorData.NowPulsed<=(LeftMoveMotorData.MovePulsed-19))
		{
			LeftMoveMotorData.MovePulsed-=19;
			LeftMoveMotorData.RunCm--;
			if(LeftMoveMotorData.SetCm>=LeftMoveMotorData.RunCm)
			{
				LeftMoveMotorData.Flag=1;
				LeftMoveMotorData.MotorMode=0;
				LeftStop();
			}	
				
		}
		*/
	}
}
/********************************************************************
	*
	*
	*
	*
	*
	*
********************************************************************/
void ReadRightPulsed(void)
{
	if((RightMoveMotorData.MotorMode&0x03)==1)
	{
		RightMoveMotorData.NowPulsed++;
		/*
		if(RightMoveMotorData.NowPulsed>=(RightMoveMotorData.MovePulsed+19))
		{

			RightMoveMotorData.RunCm++;
			RightMoveMotorData.MovePulsed+=19;
			if(RightMoveMotorData.SetCm<=RightMoveMotorData.RunCm)
			{
				RightMoveMotorData.Flag=1;
				RightMoveMotorData.MotorMode=0;
				RightStop();
			}
		}
		*/
	}
	else 
	{
		RightMoveMotorData.NowPulsed--;
		/*
		if(RightMoveMotorData.NowPulsed<=(RightMoveMotorData.MovePulsed-19))
		{

			RightMoveMotorData.RunCm--;
			RightMoveMotorData.MovePulsed-=19;

			if(RightMoveMotorData.SetCm>=RightMoveMotorData.RunCm)
			{
				RightMoveMotorData.Flag=1;
				RightMoveMotorData.MotorMode=0;
				RightStop();
			}
		}
		*/
	}
}
/**************************************************************
	  *
	  *Function Name:void ReadLeftPulsed(void)
	  *Function : motor return run
	  *Input Ref: NO
	  *Retrun Ref: NO
	  *
**************************************************************/
void CheckLeftMotorSpeed(void)
{

	static INT8U i;

	if(LeftMoveMotorData.MotorMode==1)
	{
		if(LeftMoveMotorData.NowPulsed>=LeftMoveMotorData.LastPulsed)
			LeftMoveMotorData.NowSpeed[i]=LeftMoveMotorData.NowPulsed-LeftMoveMotorData.LastPulsed;
	}
	else if(LeftMoveMotorData.MotorMode==2)
	{
		if(LeftMoveMotorData.LastPulsed>=LeftMoveMotorData.NowPulsed)
			LeftMoveMotorData.NowSpeed[i]=LeftMoveMotorData.LastPulsed-LeftMoveMotorData.NowPulsed;
	}

	i++;
	///if(i>1)
	//i=0;
	LeftMoveMotorData.LastPulsed=LeftMoveMotorData.NowPulsed;
	if(i>1)
	{
		i=0;
		LeftMoveMotorData.AvgSpeedLast=LeftMoveMotorData.AvgSpeed;
		LeftMoveMotorData.AvgSpeed=(LeftMoveMotorData.NowSpeed[0]+LeftMoveMotorData.NowSpeed[1])/2;

		//SBUF=LeftMoveMotorData.AvgSpeed;
   	  	
		if(LeftMoveMotorData.MotorMode<0x80)
		{
			if(0==LeftMoveMotorData.RunSpeed)
			{
				LeftMoveMotorData.OutPWM=0;
				LeftMoveMotorData.MotorMode|=0x80;
			}
 
			else if(LeftMoveMotorData.AvgSpeed>LeftMoveMotorData.RunSpeed)
			{

				 //if(LeftMoveMotorData.AvgSpeedLast<=LeftMoveMotorData.AvgSpeed)
				//	LeftMoveMotorData.OutPWM-=2;
				//	if(LeftMoveMotorData.OutPWM<0X20)
				//		LeftMoveMotorData.OutPWM=0X20;
			   ///*
				{

          if((LeftMoveMotorData.AvgSpeed-LeftMoveMotorData.RunSpeed)>3)
					{
             LeftMoveMotorData.OutPWM-=4;
					if(LeftMoveMotorData.OutPWM<0X20)
						LeftMoveMotorData.OutPWM=0X20;
					}					
					else 
					if((LeftMoveMotorData.AvgSpeed-LeftMoveMotorData.RunSpeed)>2)
					{
             LeftMoveMotorData.OutPWM-=3;
					if(LeftMoveMotorData.OutPWM<0X20)
						LeftMoveMotorData.OutPWM=0X20;						
					}					
					else if((LeftMoveMotorData.AvgSpeed-LeftMoveMotorData.RunSpeed)>1)
					{

						LeftMoveMotorData.OutPWM-=2;
					if(LeftMoveMotorData.OutPWM<0X20)
						LeftMoveMotorData.OutPWM=0X20;						
					}
					else
					{

						{

							LeftMoveMotorData.OutPWM--;
							if(LeftMoveMotorData.OutPWM<0X20)
								LeftMoveMotorData.OutPWM=0X20;								
					
						}

					}
         
				}
			  //*/
			}
			else if(LeftMoveMotorData.AvgSpeed<LeftMoveMotorData.RunSpeed)
			{
	
			//		   LeftMoveMotorData.OutPWM+=2;
			//		if(LeftMoveMotorData.OutPWM>0xfE)
			//			LeftMoveMotorData.OutPWM=0xfE;	
			  
				if((LeftMoveMotorData.RunSpeed-LeftMoveMotorData.AvgSpeed)>3)
				{
         
			
					if(LeftMoveMotorData.OutPWM>0xfb)
						LeftMoveMotorData.OutPWM=0xfb;
					else 
                    LeftMoveMotorData.OutPWM+=4;	 					
				}
				else
				if((LeftMoveMotorData.RunSpeed-LeftMoveMotorData.AvgSpeed)>2)
				{

				
					if(LeftMoveMotorData.OutPWM>0xfb)
						LeftMoveMotorData.OutPWM=0xfb;
					else 
            LeftMoveMotorData.OutPWM+=3;							
				}
				else
				if((LeftMoveMotorData.RunSpeed-LeftMoveMotorData.AvgSpeed)>1)
				{

					if(LeftMoveMotorData.OutPWM>0xfb)
						LeftMoveMotorData.OutPWM=0xfb;
					else 
            LeftMoveMotorData.OutPWM+=2;						
				}
				else
				{
					   LeftMoveMotorData.OutPWM++;
					if(LeftMoveMotorData.OutPWM>0xfb)
						LeftMoveMotorData.OutPWM=0xfb;	
					

				}
		   
    


			}

		}
		else
			LeftMoveMotorData.OutPWM=0;
    
	   if(LeftMoveMotorData.MotorMode>0)
		 PWM0DL=LeftMoveMotorData.OutPWM;
	   else
		 LeftStop();
	 	 
	}

}


/**************************************************************
	  *
	  *Function Name:void ReadLeftPulsed(void)
	  *Function : motor return run
	  *
	  *
	  *
**************************************************************/
void CheckRightMotorSpeed(void)
{

	static INT8U i;

	if(RightMoveMotorData.MotorMode==1)
	{
		if(RightMoveMotorData.NowPulsed>=RightMoveMotorData.LastPulsed)
			RightMoveMotorData.NowSpeed[i]=RightMoveMotorData.NowPulsed-RightMoveMotorData.LastPulsed;
	}
	else if(RightMoveMotorData.MotorMode==2)
	{
		if(RightMoveMotorData.LastPulsed>=RightMoveMotorData.NowPulsed)
			RightMoveMotorData.NowSpeed[i]=RightMoveMotorData.LastPulsed-RightMoveMotorData.NowPulsed;
	}

	i++;
    //if(i>4)
	//i=0;
	RightMoveMotorData.LastPulsed=RightMoveMotorData.NowPulsed;
	if(i>1)
	{
		i=0;
		RightMoveMotorData.AvgSpeedLast=RightMoveMotorData.AvgSpeed;
		RightMoveMotorData.AvgSpeed=(RightMoveMotorData.NowSpeed[0]+RightMoveMotorData.NowSpeed[1])/2;

    
		if(RightMoveMotorData.MotorMode<0x80)
		{
			if(0==RightMoveMotorData.RunSpeed)
			{
				RightMoveMotorData.OutPWM=0;
				RightMoveMotorData.MotorMode|=0x80;
			}

			else if(RightMoveMotorData.AvgSpeed>RightMoveMotorData.RunSpeed)
			{

				//	  RightMoveMotorData.OutPWM-=2;
				//	 if(RightMoveMotorData.OutPWM<0X20)
				//		RightMoveMotorData.OutPWM=0X20;	
			
				{
					
          if((RightMoveMotorData.AvgSpeed-RightMoveMotorData.RunSpeed)>3)
					{
             RightMoveMotorData.OutPWM-=4;
					if(RightMoveMotorData.OutPWM<0X20)
						RightMoveMotorData.OutPWM=0X20;						
					}					
					else 
					if((RightMoveMotorData.AvgSpeed-RightMoveMotorData.RunSpeed)>2)
					{

						RightMoveMotorData.OutPWM-=3;
					if(RightMoveMotorData.OutPWM<0X20)
						RightMoveMotorData.OutPWM=0X20;						
					}					
					else if((RightMoveMotorData.AvgSpeed-RightMoveMotorData.RunSpeed)>1)
					{

						RightMoveMotorData.OutPWM-=2;
					if(RightMoveMotorData.OutPWM<0X20)
						RightMoveMotorData.OutPWM=0X20;						
					}
					else
					{

					  RightMoveMotorData.OutPWM--;
					 if(RightMoveMotorData.OutPWM<0X20)
						RightMoveMotorData.OutPWM=0X20;								

					}

				}
			  
			}
			else if(RightMoveMotorData.AvgSpeed<RightMoveMotorData.RunSpeed)
			{
			
				//	RightMoveMotorData.OutPWM+=2;					
                  //  if(RightMoveMotorData.OutPWM>0xfE)
				//	RightMoveMotorData.OutPWM=0xfE;
			
				if((RightMoveMotorData.RunSpeed-RightMoveMotorData.AvgSpeed)>3)
				{
 					if(RightMoveMotorData.OutPWM>0xfb)
						RightMoveMotorData.OutPWM=0xfb;
					else
						RightMoveMotorData.OutPWM+=4;		          
				}
				else
				if((RightMoveMotorData.RunSpeed-RightMoveMotorData.AvgSpeed)>2)
				{

					if(RightMoveMotorData.OutPWM>0xfb)
						RightMoveMotorData.OutPWM=0xfb;
					else
						RightMoveMotorData.OutPWM+=3;					
				}
				else
				if((RightMoveMotorData.RunSpeed-RightMoveMotorData.AvgSpeed)>1)
				{
					if(RightMoveMotorData.OutPWM>0xfb)
						RightMoveMotorData.OutPWM=0xfb;
					else
						RightMoveMotorData.OutPWM+=2;					
				}
				else
				{
					RightMoveMotorData.OutPWM++;					
                    if(RightMoveMotorData.OutPWM>0xfb)
					RightMoveMotorData.OutPWM=0xfb;

				}
			 
 
			}

		}
		else
			RightMoveMotorData.OutPWM=0;
    
	   if(RightMoveMotorData.MotorMode>0)
		 PWM0DTL=RightMoveMotorData.OutPWM;
	   else
		 RightStop();
		 
	}

}

/**************************************************************
	   *
	   *Function Name:void SetXMotor()
	   *Function : motor return run
	   *Input Ref:NO
	   *Retrn Ref: NO
	   *
**************************************************************/
void SetXMotor(
    INT8U Leftmotor,
    INT8U LeftStartSpeed,
    INT8U LeftEndSpeed,
	INT8U LeftSlope,
    INT8U Rightmotor,
    INT8U RightStartSpeed,
    INT8U RightEndSpeed,
	INT8U RightSlope
)
{


	RightMoveMotorData.LastPulsed=0;
	LeftMoveMotorData.LastPulsed=0;
	RightMoveMotorData.NowPulsed=0;
	LeftMoveMotorData.NowPulsed=0;

	RightMoveMotorData.MovePulsed=0;
	LeftMoveMotorData.MovePulsed=0;
	LeftMoveMotorData.Slope=LeftSlope;
	RightMoveMotorData.Slope=RightSlope;
	LeftMoveMotorData.Flag=0;
	RightMoveMotorData.Flag=0;
	//LeftMoveMotorData.MotorMode=Leftmotor;
	//RightMoveMotorData.MotorMode=Rightmotor;
	if(LeftStartSpeed==0XFF)
	{

	}
	else if(LeftStartSpeed==0XF8)
	{
		if(LeftMoveMotorData.EndSpeed<20)
			LeftMoveMotorData.EndSpeed++;
	}
	else if(LeftStartSpeed==0XF0)
	{
		if(LeftMoveMotorData.EndSpeed>2)
			LeftMoveMotorData.EndSpeed--;
	}
	else 
	{

		if(Leftmotor==1)
		{
			//if(LeftMoveMotorData.MotorMode!=Leftmotor)
			{
				InitMotorLeftForward();
				LeftMoveMotorData.OutPWM=0Xa0;
				PWM0DL=LeftMoveMotorData.OutPWM;


			}
			LeftMoveMotorData.MotorMode=Leftmotor;
			LeftMoveMotorData.LastPulsed=0;
			LeftMoveMotorData.NowPulsed=0;

		}
		else if(Leftmotor==2)
		{
			//if(LeftMoveMotorData.MotorMode!=Leftmotor)
			{
				InitMotorLeftRetreat();
				LeftMoveMotorData.OutPWM=0Xa0;
				PWM0DL=LeftMoveMotorData.OutPWM;
			}
			LeftMoveMotorData.MotorMode=Leftmotor;
			LeftMoveMotorData.LastPulsed=0;
			LeftMoveMotorData.NowPulsed=0;	

		}
		else
		{
			LeftStop();
		}
		LeftMoveMotorData.RunSpeed=LeftStartSpeed;
		LeftMoveMotorData.EndSpeed=LeftEndSpeed;

	}


	if(RightStartSpeed==0XFF)
	{

	}
	else if(RightStartSpeed==0XF8)
	{
		if(RightMoveMotorData.EndSpeed<20)
			RightMoveMotorData.EndSpeed++;
	}
	else if(RightStartSpeed==0XF0)
	{
		if(RightMoveMotorData.EndSpeed>2)
			RightMoveMotorData.EndSpeed--;
	}
	else 
	{

		if(Rightmotor==1)
		{
			//if(RightMoveMotorData.MotorMode!=Rightmotor)
			{
				InitMotorRightForward();
				RightMoveMotorData.OutPWM=0Xa0;
				PWM0DTL=RightMoveMotorData.OutPWM;

			}
		
			RightMoveMotorData.MotorMode=Rightmotor;
			RightMoveMotorData.LastPulsed=0;
			RightMoveMotorData.NowPulsed=0;
			RightMoveMotorData.MovePulsed=0;
		}
		else if(Rightmotor==2)
		{
			//if(RightMoveMotorData.MotorMode!=Rightmotor)
			{
				InitMotorRightRetreat();
				RightMoveMotorData.OutPWM=0Xa0;
				PWM0DTL=RightMoveMotorData.OutPWM;

			}
		
			RightMoveMotorData.MotorMode=Rightmotor;
			RightMoveMotorData.LastPulsed=0;
			RightMoveMotorData.NowPulsed=0;
			RightMoveMotorData.MovePulsed=0;
		}
		else
			RightStop();

		RightMoveMotorData.RunSpeed=RightStartSpeed;
		RightMoveMotorData.EndSpeed=RightEndSpeed;

	}

}

/**************************************************************
	   *
	   *Function Name:void AdjustSpeed()
	   *Function : motor return run
	   *Input Ref:NO
	   *Retrn Ref: NO
	   *
**************************************************************/
void AdjustSpeed()
{

	if(LeftMoveMotorData.RunSpeed>LeftMoveMotorData.EndSpeed)
	{
		LeftMoveMotorData.SlopeTime++;
		if(LeftMoveMotorData.SlopeTime>LeftMoveMotorData.Slope)
		{
			LeftMoveMotorData.SlopeTime=0;
			if(LeftMoveMotorData.RunSpeed>0)
				LeftMoveMotorData.RunSpeed--;
		}
	}
	else if(LeftMoveMotorData.RunSpeed<LeftMoveMotorData.EndSpeed)
	{
		LeftMoveMotorData.SlopeTime++;
		if(LeftMoveMotorData.SlopeTime>LeftMoveMotorData.Slope)
		{
			LeftMoveMotorData.SlopeTime=0;
			LeftMoveMotorData.RunSpeed++;
		}
	}
	if(RightMoveMotorData.RunSpeed>RightMoveMotorData.EndSpeed)
	{
		RightMoveMotorData.SlopeTime++;
		if(RightMoveMotorData.SlopeTime>RightMoveMotorData.Slope)
		{
			RightMoveMotorData.SlopeTime=0;
			if(RightMoveMotorData.RunSpeed>0)
				RightMoveMotorData.RunSpeed--;
		}
	}
	else if(RightMoveMotorData.RunSpeed<RightMoveMotorData.EndSpeed)
	{
		RightMoveMotorData.SlopeTime++;
		if(RightMoveMotorData.SlopeTime>RightMoveMotorData.Slope)
		{
			RightMoveMotorData.SlopeTime=0;
			RightMoveMotorData.RunSpeed++;
		}
	}

}

/**************************************************************
	   *
	   *Function Name:void SetMotorcm(INT8U mode,INT16U Setcm)
	   *Function : motor return run
	   *Input Ref: mode,Setcm
	   *Retrn Ref: NO
	   *
**************************************************************/
void SetMotorcm(INT8U mode,INT16U Setcm)
{
  switch(mode)
  {
     case 1:
	 {
	   LeftMoveMotorData.RunCm=0;
       RightMoveMotorData.RunCm=0;
       LeftMoveMotorData.SetCm=Setcm;
       RightMoveMotorData.SetCm=Setcm;
     }
	 break;
	 case 2:
	 {
	   LeftMoveMotorData.RunCm=0;
       RightMoveMotorData.RunCm=0;
       LeftMoveMotorData.SetCm=LeftMoveMotorData.RunCm-Setcm;
       RightMoveMotorData.SetCm=RightMoveMotorData.RunCm-Setcm;
     }
	 break;
	 case 3:
	 {
	   LeftMoveMotorData.RunCm=0;
       RightMoveMotorData.RunCm=0;
       LeftMoveMotorData.SetCm=LeftMoveMotorData.RunCm-Setcm/6;
       RightMoveMotorData.SetCm=Setcm/6;
     }
	 break;
	 case 4:
	 {
	   LeftMoveMotorData.RunCm=0;
       RightMoveMotorData.RunCm=0;
       LeftMoveMotorData.SetCm=Setcm/6;
       RightMoveMotorData.SetCm=RightMoveMotorData.RunCm-Setcm/6;
     }
	 break;
  }
}

