/*

---------- file information -----------------------------------------------
file name: 
define   : <文件说明>
version  : 见文件尾端
---------------------------------------------------------------------------
*/

//全局变量声明
#define  KAKA_Led_GB

#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else
//#include "LB_hc89f003_IO.h"
#include "..\include\HC89F0541.h"
#include "..\include\PJ_TypeRedefine.h"
#include "LB_Led.h"
#include "LB_AD.h"

#endif

/**
  * @?渭?梅  	?贸锚卤o藟锚y
  * @2?锚y  	fui_i : ?贸锚卤锚卤??
  * @路渭???渭 ?T
  * @脳锟?	Fcpu = 16MHz锟?fui_i = 1锚卤锟??贸锚卤锚卤?????a1Ms
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


void InitT1(void)
{
	TCON1 = 0x00;						//T1定时器时钟为Fosc
	TMOD = 0x00;						//16位重装载定时器/计数器

	//Tim1计算时间 	= (65536 - 0xFACB) * (1 / (Fosc /Timer分频系数))
	//				= 1333 / (16000000 / 12)
	//				= 1 ms

	//定时0.1ms
	//反推初值 	= 65536 - ((1/10000) / (1/(Fosc / Timer分频系数)))
	//		   	= 65536 - ((1/10000) / (1/(16000000 / 12)))
	//			= 65536 - 133
	//			= 0xFf78
	TH1 = 0xFf;
	TL1 = 0x78;
	IE |= 0x08;							//打开T1中断
	TCON |= 0x40;						//使能T1
    
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
  P0M0 = 0x68;                        //P00设置为施密特数字带上拉输入
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

  static INT16U  poweron ,abc;
  if(poweron ==0){
   	 
      poweron ++ ;
	 Delay_ms(1000);//Delay_ms(2000);
    
	 if(P0_0==0)
	 {
		LedBlueON();
		LedRedON();
		return(2); //itself check flag =2
			 
			 
     }
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
   //LedBlueOff();
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
  P1M0 = 0x58;                        //P10设置为施密特数字带上拉输入
  P1_0=1; //电池电压检查，是否电池电压低于5V

}
void InitPowerStatus(void)
{
      P1M7 = 0x58;                        //P10设置为施密特数字带上拉输入
     P1_7=1;                              //电池充电管理，GPIO ,判断是否需要充电 

  	PITS3 = 0xc0;	   // INT15   双沿中断					

    PINTE1 = 0x80;						//使能INT15
	IE2 |= 0x01;						//打开INT8-17中断
	EA=1;


}
 INT8U ReadPowerDCIn(void)
{
  return(P1_0); // 检查电池掉电，电池电量低于5V.
}
 INT8U ReadPowerStatus(void)
{
   return(P1_7); //电池充电判断,是否需要充电
}

/*************************************************************
	*
	*Function Name :void SelfChecking(void)
	*Function : It self check for mass product
	*Iinput Ref:NO
	*Return Ref:NO
	*
*************************************************************/
void SelfChecking(void)
{
      INT8U ir_Left,ir_Mid,ir_Right,i=0;

	  ir_Left =GroundDp[0]; //ir_L
	  ir_Mid = GroundDp[1];  //ir_M
	  ir_Right = GroundDp[2];  //ir_R 

	 //  LedBlueOff();
	 //  LedRedOff();

	  if(ir_Left !=0){

		 GroundDp[0]=0;
		
          LedBlueOff();
		  LedRedOff();
		  LedRedON();
		  Delay_ms(100);
 		  LedRedOff();
		  LedBlueON();
		  Delay_ms(100);
		  if(ir_Left !=0){
		  LedBlueOff();
		  LedRedON();
		  Delay_ms(100);
 		  LedBlueON();
		  LedRedOff();
		  Delay_ms(100);
		  }
		  if(ir_Left !=0){
		  LedBlueOff();
		  LedRedON();
		  Delay_ms(100);
 		  LedBlueOff();
		  LedRedON();
		  Delay_ms(100);
		  }		 

       }
     if(ir_Mid != 0){
	 	GroundDp[1]=0;
     
		   LedBlueOff();
		  LedRedOff();
          LedBlueON();
		 Delay_ms(100);
 		 LedBlueOff();
		   Delay_ms(100);
		if(ir_Mid != 0){
		  LedBlueON();
		 Delay_ms(100);
 		 LedBlueOff();
		   Delay_ms(100);
		}
		if(ir_Mid != 0){
		  LedBlueON();
		   Delay_ms(100);
 		 LedBlueOff();
		   Delay_ms(100);
		}
		if(ir_Mid != 0){
		  LedBlueON();
		  Delay_ms(100);
 		 LedBlueOff();
		 LedRedOff();
		 Delay_ms(100);
		}
	     	
		

     }

	 if(ir_Right != 0){
	 	GroundDp[2]=0;
          
 		    LedBlueON();
		    LedRedOff();
			LedRedON();
			Delay_ms(100);
		
			LedRedOff();
			Delay_ms(100);
			 if(ir_Right != 0){
			LedRedON();
			Delay_ms(100);
			
		    LedRedOff();
			Delay_ms(100);
			 }
			 if(ir_Right != 0){
			LedRedON();
			Delay_ms(100);
			LedRedOff();
		
			Delay_ms(100);
			 }
			 if(ir_Right != 0){
			LedRedON();
			Delay_ms(100);
			LedBlueON();
		    LedRedOff();
			Delay_ms(100);
			 }
		
     }


}


