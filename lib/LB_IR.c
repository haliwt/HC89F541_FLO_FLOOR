/*

---------- file information -----------------------------------------------
file name: 
define   : <文件说明>
version  : 见文件尾端
---------------------------------------------------------------------------
*/

//全局变量声明
#define  KAKA_IR_GB

#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else
//#include "LB_hc89f003_IO.h"
#include "..\include\HC89F0541.h"
#include "..\include\PJ_TypeRedefine.h"
#include "LB_IR.h"
#include "LB_Usart.h"

#endif

void Init_IR()
{

	P1M5 = 0x68;	//P1M6 = 0x68;			        	//P16璁剧疆涓哄甫SMT涓婃媺杈撳叆

 	PITS3 |=0x04;//PITS3 |= 0x10;						//14 
    PINTE1 |= 0x20;//PINTE1 |= 0x40;						//浣胯兘INT14

	IE2 |= 0x01;						//鎵撳紑INT8-17涓柇
	EA=1;
	Left_ReadIR.ReadIRFlag=0;
	
}
/*************************************************************
	*
	*Function Name :void LeftIR_Count(void)
	*Function : This is that in Timer1 interrupt 0.1ms program
	*Iinput Ref:NO
	*Return Ref:NO
	*
*************************************************************/
void LeftIR_Count(void)
{
	if(Left_ReadIR.ReadIRFlag==1)
	{
		Left_ReadIR.Nowcount++;
		if(Left_ReadIR.Nowcount>200)
		{
			Left_ReadIR.ReadIRFlag=2;
		}
	}
}
/*************************************************************
	*
	*Function Name :void Read_LeftIR(void)
	*Function : That in interrupt extend GPIO carry out
	*Iinput Ref:NO
	*Return Ref:NO
	*
*************************************************************/
void Read_LeftIR(void)
{
     TCON |= 0x40;						//浣胯兘T1
	Left_ReadIR.NowVoltage=P1_5; //GPIO 

	if((P1_5==0)&&(Left_ReadIR.ReadIRFlag==0)) 
	{
		//The first interrupt carry out 
		Left_ReadIR.ReadIRFlag=1;
		Left_ReadIR.Nowcount=0;
		Left_ReadIR.ReadIRBit=0;
	}
	else if((P1_5==1)&&(Left_ReadIR.ReadIRFlag==1))// The second in interrupt 
	{
		//recode high level continue time 
		Left_ReadIR.ReadIRData[Left_ReadIR.ReadIRBit]=Left_ReadIR.Nowcount;
		Left_ReadIR.Nowcount=0;
		Left_ReadIR.ReadIRBit++; //recode high level 
		if(Left_ReadIR.ReadIRBit>80)
			Left_ReadIR.ReadIRFlag=2;
	}
	else if((P1_5==0)&&(Left_ReadIR.ReadIRFlag==1))
	{
		//recode continue low level time
		Left_ReadIR.ReadIRData[Left_ReadIR.ReadIRBit]=Left_ReadIR.Nowcount;
		Left_ReadIR.Nowcount=0;
		Left_ReadIR.ReadIRBit++; //recode low level
		if(Left_ReadIR.ReadIRBit>80)
			Left_ReadIR.ReadIRFlag=2;
	}
}
/***********************************************************************
	*
	*Function Name:void DecoderIR(ReadIRByte *P)
	*Fcuntion: decode IR be receive data for carrier 38KHz 
	*          NEC specification index codes low 9ms + high 4.5ms
	*          client codes 16bit high 8bit and low 8bit 
	*          data codes 16bit  high 8bit and low 8bit 
	*
	*
	*
***********************************************************************/
void DecoderIR(ReadIRByte *P)//void CheckXReadIR(ReadIRByte *P)
{
	INT8U k,ReadIR_cnt,FristCodeflag;
	FristCodeflag=0;
	ReadIR_cnt=0;
	P->AABit=0;

	if(P->ReadIRFlag==2)
	{		
		P->ReadIRByte=0;
		k=0;
		if(P->ReadIRData[P->AABit]>120) //index head codes times 9+4.5=13.5ms 
		{
		  for(P->AABit=1; P->AABit<P->ReadIRBit;P->AABit++)//cilent codes 16 bit
			{				     
					 //high continue 0.56ms + low level continue 0.56ms = 1.125ms
					 if((P->ReadIRData[P->AABit]>0)&&(P->ReadIRData[P->AABit]<=14))//14 * 0.1ms =1.4ms
					 {
					 	P->ReadIRByte= 0x00 | (P->ReadIRByte<<1);// P->ReadIRByte =0; //low level Read ReadIRByte = 0x0A
					    k++;
						if(k>7)
					    {
						    P->ReadIR[ReadIR_cnt++]=P->ReadIRByte; //8 bit 
						    k=0;
						    P->ReadIRByte=0;
//							P->ReadIRFlag=3;

					    }
					 }
					 if((P->ReadIRData[P->AABit]>14)&&(P->ReadIRData[P->AABit]<28))// 28 * 0.1=2.8ms
					 {
						//low level 0.56ms + high level 1.69ms =2.25ms 
						P->ReadIRByte = 0x01 |(P->ReadIRByte<<1);//P->ReadIRByte =1;
					    k++;
						if(k>7)
					    {
						    P->ReadIR[ReadIR_cnt++]=P->ReadIRByte; //
						    k=0;
						    P->ReadIRByte=0;
							P->ReadIRFlag=3;
					    }
					 }
					 if(ReadIR_cnt==4)
					 {
			    	    Usart1Send[0]=4;
	                    Usart1Send[1]=P->ReadIR[0];
						Usart1Send[2]=P->ReadIR[1];
						Usart1Send[3]=P->ReadIR[2];
						Usart1Send[4]=P->ReadIR[3];
	                    SendCount=1;
	                    SBUF=Usart1Send[SendCount];
						ReadIR_cnt=0;
						FristCodeflag=0;
						P->ReadIRFlag=3;


					 }
			}
			for(P->AABit=0; P->AABit<80; P->AABit++)
			{
			    P->ReadIRData[P->AABit]=0; //That receive IR data is error 
			}
		}
		else if((P->ReadIRData[P->AABit]>105)&&(P->ReadIRData[P->AABit]<115))
		{
			P->ReadIRFlag=3;//continue key of codes
		}
		else
		{
			Left_ReadIR.ReadIRFlag=0;
			for(P->AABit=0; P->AABit<80; P->AABit++)
			{
			     P->ReadIRData[P->AABit]=0;
			}
		}		
	}
}

/*************************************************************
	*
	*Function Name :void Read_LeftIR(void)
	*Function : That in interrupt extend GPIO carry out
	*Iinput Ref:NO
	*Return Ref:NO
	*
*************************************************************/
INT8U CheckHandsetIR(void)
{
  
   INT8U KK=0;
	
   DecoderIR(&Left_ReadIR);// CheckXReadIR(&Left_ReadIR);

   if(Left_ReadIR.ReadIRFlag==3)
   {
     
	  Left_ReadIR.ReadIRFlag=0;
	   Usart1Send[0]=4;
		Usart1Send[1]=Left_ReadIR.ReadIR[0];
		Usart1Send[2]=Left_ReadIR.ReadIR[1];
		Usart1Send[3]=Left_ReadIR.ReadIR[2];
		Usart1Send[4]=Left_ReadIR.ReadIR[3];
		SendCount=1;
		SBUF=Usart1Send[SendCount];

	  }
   

  
  return(KK);
	
	
}

void ClearAllIR()
{
	  LeftIR.Left=0;
	  LeftIR.Right=0;
	  LeftIR.Mid=0;
	  LeftIR.Top=0;
	  LeftIR.Err=0;


	  
}



