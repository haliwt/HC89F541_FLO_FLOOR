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
#include "LB_Motor.h"
#include "LB_Run.h"

#endif

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

  static INT16U  poweron=0,abc,key=0,cba;
   
   if(poweron ==0){
   	 
    
	 Delay_ms(3000);
    
	 if(P0_0==0)
	 {
		
			 Delay_ms(20);
			 if(P0_0==0){
			 	LedBlueON();
				LedRedON();
			    return(2); //itself check flag =2
			 }
			 
     }
     poweron ++ ;
       

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
  P1M0 = 0x58;                        //P10设置为施密特数字带上拉输入
  P1_0=1; //电池电压检查，是否电池电压低于5V

}
void InitPowerStatus(void)
{
  P1M7 = 0x58;                        //P10设置为施密特数字带上拉输入
  P1_7=1;  //电池充电管理，GPIO ,判断是否需要充电 

  	PITS3 = 0xc0;						

    PINTE1 = 0x80;						//使能INT15
	IE2 |= 0x01;						//打开INT8-17中断
	EA=1;


}
 INT8U ReadPowerDCIn(void)
{
  return(P1_0); // 检查电池掉电，电池电量低于5V.
}
 /************************************************
	*
	*Function Name: INT8U ReadPowerStatus(void)
	*Function : 充电结束，P1_7=1,充电时：P1_7 = 0 
	*Input Ref:NO
	*Return Ref:NO
	*
************************************************/
 INT8U ReadPowerStatus(void)
{
  return(P1_7); //电池充电判断,是否需要充电
}