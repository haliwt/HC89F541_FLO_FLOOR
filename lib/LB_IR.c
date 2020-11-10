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

#endif

void Init_IR()
{

	P1M5 = 0x68;			        	//P15设置为带SMT上拉输入-读取遥控器的值，此硬件不支持
	P1M6 = 0x68;			        	//P16设置为带SMT上拉输入-速度IR 控制
	P1M7 = 0x68;			        	//P17设置为带SMT上拉输入-电池充电状态控制

	PITS3 |= 0x0C;						//INT13 //外部中断电平选择位,双沿中断
 	PITS3 |= 0x30;						//INT14 //外部中断点电平，双沿
	PITS3 |= 0xC0;						//INT15	
    PINTE1 |= 0xE0;						//使能INT15 14 13

	IE2 |= 0x01;						//打开INT8-17中断
	EA=1;
	Left_ReadIR.ReadIRFlag=0;
	Right_ReadIR.ReadIRFlag=0;
	Mid_ReadIR.ReadIRFlag=0;
}
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

void RightIR_Count(void)
{
	if(Right_ReadIR.ReadIRFlag==1)
	{
		Right_ReadIR.Nowcount++;
		if(Right_ReadIR.Nowcount>200)
		{
			Right_ReadIR.ReadIRFlag=2;
		}
	}
}

void MidIR_Count(void)
{
	if(Mid_ReadIR.ReadIRFlag==1)
	{
		Mid_ReadIR.Nowcount++;
		if(Mid_ReadIR.Nowcount>200)
		{
			Mid_ReadIR.ReadIRFlag=2;
		}
	}
}

void Read_MidIR(void)
{
	Mid_ReadIR.NowVoltage=P1_6; //马达运行速度值，检测值
	if(
	    (Mid_ReadIR.NowVoltage==0)&&(Mid_ReadIR.ReadIRFlag==0) //马达没有
	)
	{
		Mid_ReadIR.ReadIRFlag=1;
		Mid_ReadIR.Nowcount=0;
		Mid_ReadIR.ReadIRBit=0;
	}
	else if(
	    (Mid_ReadIR.NowVoltage==1)&&(Mid_ReadIR.ReadIRFlag==1)
	)
	{
	   //SBUF=Mid_ReadIR.Nowcount;
		Mid_ReadIR.ReadIRData[Mid_ReadIR.ReadIRBit]=Mid_ReadIR.Nowcount;
		Mid_ReadIR.Nowcount=0;
		Mid_ReadIR.ReadIRBit++;
		if(Mid_ReadIR.ReadIRBit>80)
			Mid_ReadIR.ReadIRFlag=2;

	}
	else if(
	    (Mid_ReadIR.NowVoltage==0)&&(Mid_ReadIR.ReadIRFlag==1)
	)
	{
	   //SBUF=Mid_ReadIR.Nowcount;
		Mid_ReadIR.ReadIRData[Mid_ReadIR.ReadIRBit]=Mid_ReadIR.Nowcount;
		Mid_ReadIR.Nowcount=0;
		Mid_ReadIR.ReadIRBit++;
		if(Mid_ReadIR.ReadIRBit>80)
			Mid_ReadIR.ReadIRFlag=2;
	}
}

/*************************************************************
	*
	*Function Name :void Read_LeftIR(void)
	*Function : 
	*Iinput Ref:NO
	*Return Ref:NO
	*
*************************************************************/
void Read_LeftIR(void)
{
	Left_ReadIR.NowVoltage=P1_5; //读取遥控器的值，此硬件不支持

	if(
	    (Left_ReadIR.NowVoltage==0)&&(Left_ReadIR.ReadIRFlag==0)
	)
	{
		Left_ReadIR.ReadIRFlag=1;
		Left_ReadIR.Nowcount=0;
		Left_ReadIR.ReadIRBit=0;
	}
	else if(
	    (Left_ReadIR.NowVoltage==1)&&(Left_ReadIR.ReadIRFlag==1)
	)
	{
		Left_ReadIR.ReadIRData[Left_ReadIR.ReadIRBit]=Left_ReadIR.Nowcount;
		Left_ReadIR.Nowcount=0;
		Left_ReadIR.ReadIRBit++;
		if(Left_ReadIR.ReadIRBit>80)
			Left_ReadIR.ReadIRFlag=2;
	}
	else if(
	    (Left_ReadIR.NowVoltage==0)&&(Left_ReadIR.ReadIRFlag==1)
	)
	{
		Left_ReadIR.ReadIRData[Left_ReadIR.ReadIRBit]=Left_ReadIR.Nowcount;
		Left_ReadIR.Nowcount=0;
		Left_ReadIR.ReadIRBit++;
		if(Left_ReadIR.ReadIRBit>80)
			Left_ReadIR.ReadIRFlag=2;
	}
}
/*************************************************************
	*
	*Function Name :void Read_RightIR(void)
	*Function : 
	*Iinput Ref:NO
	*Return Ref:NO
	*
*************************************************************/
void Read_RightIR(void)
{
	Right_ReadIR.NowVoltage=P1_7; //电池充电电压状态值 

	if(
	    (Right_ReadIR.NowVoltage==0)&&(Right_ReadIR.ReadIRFlag==0)
	)
	{
		Right_ReadIR.ReadIRFlag=1;
		Right_ReadIR.Nowcount=0;
		Right_ReadIR.ReadIRBit=0;
	}
	else if(
	    (Right_ReadIR.NowVoltage==1)&&(Right_ReadIR.ReadIRFlag==1)
	)
	{
		Right_ReadIR.ReadIRData[Right_ReadIR.ReadIRBit]=Right_ReadIR.Nowcount;
		Right_ReadIR.Nowcount=0;
		Right_ReadIR.ReadIRBit++;
		if(Right_ReadIR.ReadIRBit>80)
			Right_ReadIR.ReadIRFlag=2;
	}
	else if(
	    (Right_ReadIR.NowVoltage==0)&&(Right_ReadIR.ReadIRFlag==1)
	)
	{
		Right_ReadIR.ReadIRData[Right_ReadIR.ReadIRBit]=Right_ReadIR.Nowcount;
		Right_ReadIR.Nowcount=0;
		Right_ReadIR.ReadIRBit++;
		if(Right_ReadIR.ReadIRBit>80)
			Right_ReadIR.ReadIRFlag=2;
	}
}

void CheckXReadIR2(ReadIRByte *P)
{
	INT8U k,m;

	if(P->ReadIRFlag==2)
	{
		{
			m=0;
			for(m=0; m<4; m++)
				P->ReadIR[m]=0;
			m=0;
			k=0;
			P->ReadIRByte=0;
			for(P->AABit=0; P->AABit<P->ReadIRBit;)
			{
				if(
				    P->ReadIRData[P->AABit]>20
				)
				{
					if(k>2)
					{
						P->ReadIR[m]=P->ReadIRByte;
						m++;
					}
					else
						P->AABit++;
					k=0;
					P->ReadIRByte=0;
					//
				}
				else if(
				    (P->ReadIRData[P->AABit]>0)&&(P->ReadIRData[P->AABit]<8)&&(P->ReadIRData[P->AABit+1]>12)&&((P->ReadIRData[P->AABit+1]<35) )
				)
				{
					P->ReadIRByte<<=1;
					P->ReadIRByte|=1;
					P->AABit+=2;

					k++;
					if(k>7)
					{

						P->ReadIR[m]=P->ReadIRByte;
						k=0;
						m++;
						P->ReadIRByte=0;
						P->AABit++;
					}
				}
				else  if(
				    (P->ReadIRData[P->AABit]>0)&&(P->ReadIRData[P->AABit]<8)&&(P->ReadIRData[P->AABit+1]>0)&&((P->ReadIRData[P->AABit+1]<35) )
				)
				{
					P->AABit+=2;
					P->ReadIRByte<<=1;
					k++;
					if(k>7)
					{

						P->ReadIR[m]=P->ReadIRByte;
						k=0;
						m++;
						P->ReadIRByte=0;
						P->AABit++;
					}
				}
				else  if(
				    (P->ReadIRData[P->AABit]>0)&&(P->ReadIRData[P->AABit]<8)&&(P->ReadIRData[P->AABit+1]==0)
				)
				{
					P->ReadIRByte<<=1;
					P->ReadIR[m]=P->ReadIRByte;
					k=0;
					P->ReadIRByte=0;
					P->AABit++;
				}

				else
				{
					P->AABit++;
				}

			}
			for(P->AABit=0; P->AABit<80; P->AABit++)
				P->ReadIRData[P->AABit]=0;
		}

		P->ReadIRFlag=3;
	}
 

}
void CheckXReadIR(ReadIRByte *P)
{
	INT8U k;

	{
		if(P->ReadIRFlag==2)
		{
			{

				P->ReadIR[0]=0;

				k=0;
				P->ReadIRByte=0;
				for(P->AABit=0; P->AABit<16;)
				{
					if(
					    (P->ReadIRData[P->AABit]>10)&&(P->ReadIRData[P->AABit]<40)
					)
					{
						P->ReadIRByte<<=1;
						P->ReadIRByte|=1;
						P->AABit+=2;

						k++;
						if(k>7)
						{

							P->ReadIR[0]=P->ReadIRByte;
							k=0;

							P->ReadIRByte=0;

						}
					}
					else
					{
						P->AABit+=2;
						P->ReadIRByte<<=1;
						k++;
						if(k>7)
						{

							P->ReadIR[0]=P->ReadIRByte;
							k=0;

							P->ReadIRByte=0;
							//P->AABit++;
						}
					}

				}
				for(P->AABit=0; P->AABit<20; P->AABit++)
					P->ReadIRData[P->AABit]=0;
			}

			P->ReadIRFlag=3;
		}
	}
}


void CheckRechargeIR()
{
   CheckXReadIR(&Left_ReadIR);
   CheckXReadIR(&Right_ReadIR);
   CheckXReadIR(&Mid_ReadIR);
	
	if(Right_ReadIR.ReadIRFlag==3)
	{

			if((Right_ReadIR.ReadIR[0]&0XF4)==0XF4)
				RightIR.Right++;
			else if((Right_ReadIR.ReadIR[0]&0XF2)==0XF2)
				RightIR.Mid++;			
			else if((Right_ReadIR.ReadIR[0]&0XF8)==0XF8)
				RightIR.Left++;
			else if((Right_ReadIR.ReadIR[0]&0XF1)==0XF1)
				RightIR.Top++;
			else if(Right_ReadIR.ReadIR[0]!=0)
				RightIR.Err++;

			Right_ReadIR.ReadIR[0]=0;
			Right_ReadIR.ReadIRFlag=0;

	}	
	
	if(Left_ReadIR.ReadIRFlag==3)
	{

			if((Left_ReadIR.ReadIR[0]&0XF4)==0XF4)
				LeftIR.Right++;
			else if((Left_ReadIR.ReadIR[0]&0XF2)==0XF2)
				LeftIR.Mid++;			
			else if((Left_ReadIR.ReadIR[0]&0XF8)==0XF8)
				LeftIR.Left++;
			else if((Left_ReadIR.ReadIR[0]&0XF1)==0XF1)
				LeftIR.Top++;
			else if(Left_ReadIR.ReadIR[0]!=0)
				LeftIR.Err++;

			Left_ReadIR.ReadIR[0]=0;
			Left_ReadIR.ReadIRFlag=0;

	}	
	
	
	if(Mid_ReadIR.ReadIRFlag==3)
	{
			//SBUF=Mid_ReadIR.ReadIR[0];
			if((Mid_ReadIR.ReadIR[0]&0XF4)==0XF4)
				MidIR.Right++;
			else if((Mid_ReadIR.ReadIR[0]&0XF2)==0XF2)
				MidIR.Mid++;			
			else if((Mid_ReadIR.ReadIR[0]&0XF8)==0XF8)
				MidIR.Left++;
			else if((Mid_ReadIR.ReadIR[0]&0XF1)==0XF1)
				MidIR.Top++;

			else if(Mid_ReadIR.ReadIR[0]!=0)
				MidIR.Err++;

			Mid_ReadIR.ReadIR[0]=0;
			Mid_ReadIR.ReadIRFlag=0;

	}



	
	
}

void ClearAllIR()
{
	  LeftIR.Left=0;
	  LeftIR.Right=0;
	  LeftIR.Mid=0;
	  LeftIR.Top=0;
	  LeftIR.Err=0;

	  MidIR.Left=0;
	  MidIR.Right=0;
	  MidIR.Mid=0;
	  MidIR.Top=0;
	  MidIR.Err=0;

	  RightIR.Left=0;
	  RightIR.Right=0;
	  RightIR.Mid=0;
	  RightIR.Top=0;
	  RightIR.Err=0;
}

void CheckHandsetIR()
{
   CheckXReadIR(&Left_ReadIR);
   CheckXReadIR(&Right_ReadIR);
   CheckXReadIR(&Mid_ReadIR);
   if(Mid_ReadIR.ReadIRFlag==3)
   {
      Mid_ReadIR.ReadIRFlag=0;
	  if(Mid_ReadIR.ReadIR[0]==0X44)
   	    SBUF=Mid_ReadIR.ReadIR[2];
   }
   if(Left_ReadIR.ReadIRFlag==3)
   {
      Left_ReadIR.ReadIRFlag=0;
   	  //SBUF=Mid_ReadIR.ReadIR[0];
   }
   if(Right_ReadIR.ReadIRFlag==3)
   {
      Right_ReadIR.ReadIRFlag=0;
   	  //SBUF=Mid_ReadIR.ReadIR[0];
   }
}


