/*

---------- file information -----------------------------------------------
file name: 
define   : <�ļ�˵��>
version  : ���ļ�β��
---------------------------------------------------------------------------
*/

//ȫ�ֱ�������
#define  KAKA_Led_GB

#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else
//#include "LB_hc89f003_IO.h"
#include "..\include\HC89F0541.h"
#include "..\include\PJ_TypeRedefine.h"
#include "LB_Led.h"
#include "LB_Motor.h"
#include "LB_Run.h"

#endif

void InitT1(void)
{
	TCON1 = 0x00;						//T1��ʱ��ʱ��ΪFosc
	TMOD = 0x00;						//16λ��װ�ض�ʱ��/������

	//Tim1����ʱ�� 	= (65536 - 0xFACB) * (1 / (Fosc /Timer��Ƶϵ��))
	//				= 1333 / (16000000 / 12)
	//				= 1 ms

	//��ʱ0.1ms
	//���Ƴ�ֵ 	= 65536 - ((1/10000) / (1/(Fosc / Timer��Ƶϵ��)))
	//		   	= 65536 - ((1/10000) / (1/(16000000 / 12)))
	//			= 65536 - 133
	//			= 0xFf78
	TH1 = 0xFf;
	TL1 = 0x78;
	IE |= 0x08;							//��T1�ж�
	TCON |= 0x40;						//ʹ��T1
    
	EA = 1;	

}
/************************************************
	*
	*Function Name:void InitLed(void)
	*Function :LED GPIO initial 
	*
	*
************************************************/
void InitLed(void)
{
  P3M2=0XC2;
  P3M1=0XC2;
  P3_2=1;
  P3_1=1;
}
/************************************************
	*
	*Function Name:void LedBlueON()
	*Function :LED GPIO initial 
	*
	*
************************************************/
void LedBlueON()
{
  P3_2=0;
}


void LedBlueOff()
{
  P3_2=1;
}

void LedRedON()
{
  P3_1=0;
}


void LedRedOff()
{
  P3_1=1;
}

/************************************************
	*
	*Function Name:void InitKey(void)
	*Function : key initial
	*Input Ref:NO
	*Return Ref:NO
	*
************************************************/
void InitKey(void)
{
  P0M0 = 0x68;                        //P00����Ϊʩ�������ִ���������
  P0_0=1;

}
/************************************************
	*
	*Function Name:void InitKey(void)
	*Function : key initial
	*Input Ref:NO
	*Return Ref:NO
	*
************************************************/
INT8U ReadKey(void)
{

  static INT16U  poweron,abc;


  if(PowerSavingFlag ==1){
  	     PowerSavingFlag=0;
  	     AgainInitial();
  	}
   
   if(poweron ==0){
   	 
     poweron ++ ;
	 Delay_ms(1000);//Delay_ms(2000);
     
	 if(P0_0==0)
	 {
		LedBlueON();
		LedRedON();
		return(2); //itself check flag =2
			 
			 
     }
	 abc=0;//WT.EDIT 
   }
   else{
		 if(P0_0==0)
		  {
		    // LedBlueON();
		    if(abc<200)
		   	 abc++;
		  }
	      else	
		  {	  
		    //LedBlueOff();
		   	abc=0;
		  }

		  if((abc>190)&&(abc<200))
		  {
		    //
		    abc=201;
			//LedBlueON();
		    return(1);

		  }
		  else 
		  {
			 return(0);
		  }
		}
}  
			
/************************************************
	*
	*Function Name:void InitKey(void)
	*Function : key initial
	*Input Ref:NO
	*Return Ref:NO
	*
************************************************/
void InitPowerIn(void)
{
  P1M0 = 0x58;                        //P10����Ϊʩ�������ִ���������
  P1_0=1; //��ص�ѹ��飬�Ƿ��ص�ѹ����5V

}
void InitPowerStatus(void)
{
  P1M7 = 0x58;                        //P10����Ϊʩ�������ִ���������
  P1_7=1;  //��س�������GPIO ,�ж��Ƿ���Ҫ���?

  	PITS3 = 0xc0;						

    PINTE1 = 0x80;						//ʹ��INT15
	IE2 |= 0x01;						//��INT8-17�ж�
	EA=1;


}
 INT8U ReadPowerDCIn(void)
{
  return(P1_0); // ����ص��磬��ص�������5V.
}
 /************************************************
	*
	*Function Name: INT8U ReadPowerStatus(void)
	*Function : ��������P1_7=1,���ʱ��P1_7 = 0 
	*Input Ref:NO
	*Return Ref:NO
	*
************************************************/
 INT8U ReadPowerStatus(void)
{
  return(P1_7); //��س���ж�,�Ƿ���Ҫ���?
}