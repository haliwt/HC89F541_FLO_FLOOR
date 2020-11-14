/*

---------- file information -----------------------------------------------
file name: 
define   : <�ļ�˵��>
version  : ���ļ�β��
---------------------------------------------------------------------------
*/

//ȫ�ֱ�������
#define  KAKA_Motor_GB

#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else
//#include "LB_hc89f003_IO.h"
#include "..\include\HC89F0541.h"
#include "..\include\PJ_TypeRedefine.h"
#include "LB_Motor.h"
#include "LB_Run.h"
#endif

#define abs(x)  (x >0 ? x ��-x)

void Init_MotorSpeed()
{

	P3M4 = 0x68;			        	//P34����Ϊ��SMT��������,����ٶ����
	P3M5 = 0x68;			        	//P35����Ϊ��SMT��������,����ٶ����

							//INT16	17
 	PITS4 = 0x0F;	       //�ⲿ�Ĵ������жϵ�ƽѡ��Ĵ�����˫�ش����ж�					

    PINTE2 = 0x03;						//ʹ��INT17 16
	IE2 |= 0x01;						//��INT8-17�ж�
	EA=1;
	P3_4=1;  //motor Light speed dected
	P3_5=1; //motor Right speed dected
	PINTE1=0;
}
/**************************************************************
	 *
	 *Function Name:void InitMotorIO(void)
	 *Function : �������GPIO ��ʼ������ 
	 *Input Ref:NO
	 *Retrun Ref:NO
	 *
**************************************************************/
void InitMotorIO(void)
{

    P1M1 = 0xC2;                        //P11����Ϊ�������
    P1M2 = 0xC2;                        //P12����Ϊ�������
    P1M3 = 0xC2;                        //P13����Ϊ�������
    P1M4 = 0xC2;                        //P14����Ϊ�������
    P1M6 = 0xC2;                        //P14����Ϊ�������������ٶȿ���IO
  P1_1=0;
  P1_2=0;
  P1_3=0;
  P1_4=0;
  P1_6=0;

}
/**************************************************************
	 *
	 *Function Name:void InitFanEdgeIO(void)
	 *Function : ��ˮ���GPIO ��ʼ������ 
	 *Input Ref:NO
	 *Retrun Ref:NO
	 *
**************************************************************/
void InitFanEdgeIO(void)
{
    P3M3 = 0xC2;                        //P33����Ϊ�������,��ˮ��
    P3_3 =0;
}


void SetEdge(INT8U status)
{
   PWM1DL = status; //PWMռ�ձȼĴ�������8λ
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
    P1_4=0; //IN1 //Left motor
	///*
	PWM0_MAP = 0x14;					//PWM0ͨ��ӳ��P14��
    PWM0C = 0x00;   //motor ��			//PWM0����Ч��PWM01����Ч��00: 1��Ƶ 01��ʱ��8��Ƶ 
    PWMM |= 0x10;						//PWM0�����ڻ���ģʽ						

	//����ģʽ�£�PWM0��PWM01����һ�����ڼĴ���
	//PWM0��ռ�ձȵ���ʹ��			PWM0���ռ�ձȼĴ���
	//PWM01��ռ�ձȵ���ʹ��			PWM0��������Ĵ���

	//���ڼ��� 	= 0x03ff / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		Լ1.955kHz
	//      0x100 / 16000000 /1 = 1.6 * 10^(-5)us 6.25Mhz

	PWM0PH = 0x01;						//���ڸ�4λ����Ϊ0x03 //������256
	PWM0PL = 0x0;						//���ڵ�8λ����Ϊ0xFF

	//ռ�ձȼ���= 0x0155 / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   ռ�ձ�Ϊ 170.5/511.5 = 33.3%

	PWM0DH = 0x00;		//left				//PWM0��4λռ�ձ�0x01
	PWM0DL = 0x60;						//PWM0��8λռ�ձ�0x55
	PWMEN |= 0x01;						//ʹ��PWM0�Լ�PWM01
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
	PWM01_MAP = 0x11;					//PWM01ͨ��ӳ��P11��
    PWM0C = 0x00;						//PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
    PWMM |= 0x10;						//PWM0�����ڻ���ģʽ						

	//����ģʽ�£�PWM0��PWM01����һ�����ڼĴ���
	//PWM0��ռ�ձȵ���ʹ��			PWM0���ռ�ձȼĴ���
	//PWM01��ռ�ձȵ���ʹ��			PWM0��������Ĵ���

	//���ڼ��� 	= 0x03ff / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		Լ1.955kHz

	PWM0PH = 0x01;						//���ڸ�4λ����Ϊ0x03
	PWM0PL = 0x0;						//���ڵ�8λ����Ϊ0xFF

	//ռ�ձȼ���= 0x0155 / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   ռ�ձ�Ϊ 170.5/511.5 = 33.3%


	PWM0DTH = 0x00;						//PWM01��4λռ�ձ�0x01
	PWM0DTL = 0x60;						//PWM01��8λռ�ձ�0x55
	PWMEN |= 0x10;						//ʹ��PWM0�Լ�PWM01
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
	PWM0_MAP = 0x13;					//PWM0ͨ��ӳ��P13��
    PWM0C = 0x00;						//PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
    PWMM |= 0x10;						//PWM0�����ڶ���ģʽ			

	//����ģʽ�£�PWM0��PWM01����һ�����ڼĴ���
	//PWM0��ռ�ձȵ���ʹ��			PWM0���ռ�ձȼĴ���
	//PWM01��ռ�ձȵ���ʹ��			PWM0��������Ĵ���

	//���ڼ��� 	= 0x03ff / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		Լ1.955kHz

	PWM0PH = 0x01;						//���ڸ�4λ����Ϊ0x03
	PWM0PL = 0x0;						//���ڵ�8λ����Ϊ0xFF

	//ռ�ձȼ���= 0x0155 / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   ռ�ձ�Ϊ 170.5/511.5 = 33.3%

	PWM0DH = 0x00;						//PWM0��4λռ�ձ�0x01
	PWM0DL = 0x60;						//PWM0��8λռ�ձ�0x55
	PWMEN |= 0x01;						//ʹ��PWM0�Լ�PWM01
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
	PWM01_MAP = 0x12;					//PWM01ͨ��ӳ��P12��
    PWM0C = 0x00;                      //WT.EDIT 2020.22.20//0x00; //PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
    PWMM |= 0x10;						//PWM0�����ڻ���ģʽ						

	//����ģʽ�£�PWM0��PWM01����һ�����ڼĴ���
	//PWM0��ռ�ձȵ���ʹ��			PWM0���ռ�ձȼĴ���
	//PWM01��ռ�ձȵ���ʹ��			PWM0��������Ĵ���

	//���ڼ��� 	= 0x03ff / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		Լ1.955kHz

	PWM0PH = 0x01;						//���ڸ�4λ����Ϊ0x03
	PWM0PL = 0x0;						//���ڵ�8λ����Ϊ0xFF

	//ռ�ձȼ���= 0x0155 / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   ռ�ձ�Ϊ 170.5/511.5 = 33.3%


	PWM0DTH = 0x00;						//PWM01��4λռ�ձ�0x01
	PWM0DTL = 0x60;						//PWM01��8λռ�ձ�0x55
	PWMEN |= 0x10;						//ʹ��PWM0�Լ�PWM01
	//*/
	//P1_2=1;
}



void LeftStop()
{

   PWMEN &= 0xfE;

    P1_3=0;
    P1_4=0;
}

void RightStop()
{

   PWMEN &= 0xeF;
    P1_1=0;
    P1_2=0;

}
/**************************************************************
	  *
	  *Function Name:void WaterPumpStop(void)
	  *Function : motor return run
	  *
	  *
	  *
**************************************************************/
void WaterPumpStop(void)
{
   //PWMEN &= 0xe5;
   P3_3 =0;
}
/**************************************************************
	  *
	  *Function Name:void WaterPumpStop(void)
	  *Function : motor return run
	  *
	  *
	  *
**************************************************************/
void AllStop()
{
   PWMEN &= 0xEE;
    P1_1=0;
    P1_2=0;
    P1_3=0;
    P1_4=0;
}

/**************************************************************
	  *
	  *Function Name:void ReadLeftPulsed(void)
	  *Function : ��������-���� ǰ���ͺ���
	  *
	  *
	  *
**************************************************************/
void ReadLeftPulsed(void)
{

	if((LeftMoveMotorData.MotorMode&0x03)==1) //forword
	{
		LeftMoveMotorData.NowPulsed++;
		LmotorSpeedNum ++ ; //WT.EDIT

		
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
	else if((LeftMoveMotorData.MotorMode&0x03)==2) //retreat
	{
		LeftMoveMotorData.NowPulsed--;
		LmotorSpeedNum -- ; //WT.EDIT 
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
	*Function Name:void ReadRightPulsed(void)
	*Function : �����������壬ǰ���ͺ���
	*
	*
	*
********************************************************************/
void ReadRightPulsed(void)
{
	if((RightMoveMotorData.MotorMode&0x03)==1) //right motor RunMode =3
	{
		RightMoveMotorData.NowPulsed++;
		RmotorSpeedNum ++; //WT.EDIT 
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
	else if((RightMoveMotorData.MotorMode&0x03)==2) //WT.EDIT //retreat//else 
	{
		RightMoveMotorData.NowPulsed--;
		RmotorSpeedNum --; //WT.EDIT
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
	  *Function : 
	  *Input Ref: NO
	  *Retrun Ref: NO
	  *
**************************************************************/
void CheckLeftMotorSpeed(void)
{

	static INT8U i;

	if(LeftMoveMotorData.MotorMode==1) // forword CW
	{
		if(LeftMoveMotorData.NowPulsed>=LeftMoveMotorData.LastPulsed)
			LeftMoveMotorData.NowSpeed[i]=LeftMoveMotorData.NowPulsed-LeftMoveMotorData.LastPulsed;
		
	}
	else if(LeftMoveMotorData.MotorMode==2) //retreat CCW
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
			if(0==LeftMoveMotorData.RunSpeed) //ɲ��
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
						LeftMoveMotorData.OutPWM=0X20;	//32					
					}
					else
					{

						{

							LeftMoveMotorData.OutPWM--;
							if(LeftMoveMotorData.OutPWM<0X20) //��Сֵ����
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
         
			
					if(LeftMoveMotorData.OutPWM>0xfb) //PWM_T =256 ;
						LeftMoveMotorData.OutPWM=0xfb; //
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
						if(LeftMoveMotorData.OutPWM>0xfb)//PWM_T =256 ;
							LeftMoveMotorData.OutPWM=0xfb;	 //
					

				}
		   }

		}
		else
			LeftMoveMotorData.OutPWM=0;
    
	   if(LeftMoveMotorData.MotorMode>0)
		   PWM0DL=LeftMoveMotorData.OutPWM; //L motor duty = OutPWM= 0xfb(251)
	   else
		 LeftStop();
	 	 
	}

}


/**************************************************************
	  *
	  *Function Name:void CheckRightMotorSpeed(void)
	  *Function : motor return run
	  *Input Ref: NO
	  *Return Ref: NO
	  *
**************************************************************/
void CheckRightMotorSpeed(void)
{

	static INT8U i;

	if(RightMoveMotorData.MotorMode==1) //ǰ��
	{
		if(RightMoveMotorData.NowPulsed>=RightMoveMotorData.LastPulsed)
			RightMoveMotorData.NowSpeed[i]=RightMoveMotorData.NowPulsed-RightMoveMotorData.LastPulsed;
			
	}
	else if(RightMoveMotorData.MotorMode==2) //����
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
						RightMoveMotorData.OutPWM=0xfb; //251 
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
		    PWM0DTL=RightMoveMotorData.OutPWM;   //R motor puty = outPWM.
	   else
		 RightStop();
		 
	}

	

}

/**************************************************************
	   *
	   *Function Name:void SetXMotor()
	   *Function : ����L,R motor puty of value 
	   *Input Ref:1.leftmotor =1 ���� ,2.leftStartSpeed,3leftEndSpeed,4.left slope
	   *            leftmotor =2 ��ת
	   *Retrn Ref: NO
	   *
**************************************************************/
void SetXMotor(
    INT8U Leftmotor,   /* ����� ����*/
    INT8U LeftStartSpeed,
    INT8U LeftEndSpeed,
	INT8U LeftSlope,
    INT8U Rightmotor,   /* �����   ���� */
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
	else if(LeftStartSpeed==0XF8) // 248 //PWM_T = 0x100 =256
	{
		if(LeftMoveMotorData.EndSpeed<20) //��Сֵ
			LeftMoveMotorData.EndSpeed++;
	}
	else if(LeftStartSpeed==0XF0) //240 //PWM_T = 0x100 =256
	{
		if(LeftMoveMotorData.EndSpeed>2) //
			LeftMoveMotorData.EndSpeed--;
	}
	else 
	{

		if(Leftmotor==1)  //CW �������
		{
			//if(LeftMoveMotorData.MotorMode!=Leftmotor)
			{
				InitMotorLeftForward();
				LeftMoveMotorData.OutPWM=0Xa0; // 160 
				PWM0DH = 0x00; 
				PWM0DL=LeftMoveMotorData.OutPWM; // L motor puty = 0xa0/0x10=62.5%;


			}
			LeftMoveMotorData.MotorMode=Leftmotor;
			LeftMoveMotorData.LastPulsed=0;
			LeftMoveMotorData.NowPulsed=0;

		}
		else if(Leftmotor==2) //CCW ��﷽��
		{
			//if(LeftMoveMotorData.MotorMode!=Leftmotor)
			{
				InitMotorLeftRetreat();
				LeftMoveMotorData.OutPWM=0Xa0;
				PWM0DL=LeftMoveMotorData.OutPWM;//L motor puty = 0xa0/0x10 =62.5%;
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

    //Right motor run state value
	if(RightStartSpeed==0XFF)
	{

	}
	else if(RightStartSpeed==0XF8)//248
	{
		if(RightMoveMotorData.EndSpeed<20)
			RightMoveMotorData.EndSpeed++;
	}
	else if(RightStartSpeed==0XF0)//240
	{
		if(RightMoveMotorData.EndSpeed>2)
			RightMoveMotorData.EndSpeed--;
	}
	else 
	{

		if(Rightmotor==1) //motor CW 
		{
			//if(RightMoveMotorData.MotorMode!=Rightmotor)
			{
				InitMotorRightForward();
				RightMoveMotorData.OutPWM=0Xa0; //160  /motor PWM_T = 0x100 =256
				PWM0DTL=RightMoveMotorData.OutPWM; //R motor puty = 0xa0/0x100 =62.5%;

			}
		
			RightMoveMotorData.MotorMode=Rightmotor;
			RightMoveMotorData.LastPulsed=0;
			RightMoveMotorData.NowPulsed=0;
			RightMoveMotorData.MovePulsed=0;
		}
		else if(Rightmotor==2) //motor CCW 
		{
			//if(RightMoveMotorData.MotorMode!=Rightmotor)
			{
				InitMotorRightRetreat();
				RightMoveMotorData.OutPWM=0Xa0;
				PWM0DTL=RightMoveMotorData.OutPWM; //R motor puty = 0xa0/0x10 = 62.5%;

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
	   *Function : �����ٵ���
	   *Input Ref:NO
	   *Retrn Ref: NO
	   *
**************************************************************/
#if 1
void AdjustSpeed(void)
{
  if(RightMoveMotorData.RunSpeed==40 && LeftMoveMotorData.RunSpeed==40){ 
	  if((RmotorSpeedNum - LmotorSpeedNum) > 10 ){
	      
	      return ;
	  }
	  else{
	  
	       //���� �ƶ�������� �����ƶ�����
	        PWM0DTH = 0x00; //right motor
	        PWM0DTL=RightMoveMotorData.OutPWM ++    ;
		   
		    PWM0DH = 0x00;		//left motor
	  		PWM0DL=LeftMoveMotorData.OutPWM--;
	  		if((RmotorSpeedNum - LmotorSpeedNum)  > 10 ){
	          return ;
			 
	        }


	  }
  }
}

 #endif 
/**********************DEFAULT***************************************/
#if 0
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
#endif 
/**************************************************************
	   *
	   *Function Name:void SetMotorcm(INT8U mode,INT16U Setcm)
	   *Function : ����ƶ��ľ�������
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
/**************************************************************
	   *
	   *Function Name:void WaterPump()
	   *Function : ˮ�õ������
	   *Input Ref: NO
	   *Retrn Ref: NO
	   *
**************************************************************/
void WaterPump(void)
{
   P3M3 = 0xC2;                        //P33����Ϊ�������,��ˮ��	
   P3_3=1; //��ˮ
	/*
   P3M3 = 0xC2;                        //P33����Ϊ�������,��ˮ��
  // P3_3=1; //��ˮ
  
   PWM1_MAP = 0x33;					//PWM1ͨ��ӳ��P33��

    PWM1C = 0x01;//WT.EDIT	//0x00					//PWM1����Ч��PWM11����Ч��ʱ��8��Ƶ 
    PWMM |= 0x10;						//PWM1������						

	//����ģʽ�£�PWM0��PWM01����һ�����ڼĴ���
	//PWM0��ռ�ձȵ���ʹ��			PWM0���ռ�ձȼĴ���
	//PWM01��ռ�ձȵ���ʹ��			PWM0��������Ĵ���

	//���ڼ��� 	= 0x03ff / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		Լ1.955kHz

	PWM1PH = 0x03;						//���ڸ�4λ����Ϊ0x03
	PWM1PL = 0xff;						//���ڵ�8λ����Ϊ0xFF

	//ռ�ձȼ���= 0x0155 / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   ռ�ձ�Ϊ 170.5/511.5 = 33.3%

	PWM1DH = 0x01;						//PWM1��4λռ�ձ�0x01
	PWM1DL = 0xff;	//WT.EDIT					//PWM1��8λռ�ձ�0x55													    

	PWMEN |= 0x02;						//ʹ��PWM1�Լ�PWM11
*/
    

}
/**
  * @?��?��  	?������o����y
  * @2?��y  	fui_i : ?����������??
  * @����???�� ?T
  * @���� 	Fcpu = 16MHz��?fui_i = 1������??����������?????a1Ms
  */
void Delay_ms(unsigned int fui_i)
{
	unsigned int fui_j;
	for(;fui_i > 0;fui_i --)
	for(fui_j = 1596;fui_j > 0;fui_j --)
	{
		;
	}
}



