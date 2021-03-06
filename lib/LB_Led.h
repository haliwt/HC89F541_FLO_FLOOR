/*

---------- file information -----------------------------------------------
file name: 
define   : <文件说明>
version  : 见文件尾端
---------------------------------------------------------------------------
*/
#ifndef  LB_Led_h
#define  LB_Led_h



#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else

#include "..\include\PJ_TypeRedefine.h"


#endif


//全局变量声明
#ifdef  KAKA_Led_GB
#define KAKA_Led_EXT
#else
#define  KAKA_Led_EXT extern
#endif

KAKA_Led_EXT INT16U SelfKeyTime;

KAKA_Led_EXT  void InitLed(void);

KAKA_Led_EXT  void LedBlueOff();
KAKA_Led_EXT  void LedBlueON();
KAKA_Led_EXT  void LedRedON();
KAKA_Led_EXT  void LedRedOff();

KAKA_Led_EXT void InitT1(void);
KAKA_Led_EXT void InitKey(void);
KAKA_Led_EXT INT8U ReadKey(void);
KAKA_Led_EXT void InitPowerIn(void);
KAKA_Led_EXT void InitPowerStatus(void);
KAKA_Led_EXT INT8U ReadPowerDCIn(void);
KAKA_Led_EXT INT8U ReadPowerStatus(void);
#endif