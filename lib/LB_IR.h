/*

---------- file information -----------------------------------------------
file name: 
define   : <文件说明>
version  : 见文件尾端
---------------------------------------------------------------------------
*/
#ifndef  LB_IR_h
#define  LB_IR_h



#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else

#include "..\include\PJ_TypeRedefine.h"


#endif


//全局变量声明
#ifdef  KAKA_IR_GB
#define KAKA_IR_EXT
#else
#define  KAKA_IR_EXT extern
#endif

 typedef struct
{
	INT8U  NowVoltage;
	INT8U  Nowcount;
	INT8U  ReadIRBit;
	INT8U  ReadIRFlag;
	INT8U  ReadIRByte;
	INT8U  AABit;
	INT8U  ReadIR[4];
	INT8U  ReadIRData[80];
} ReadIRByte ;
typedef struct
{
	INT8U  Left;
	INT8U  Right;
	INT8U  Mid;
 	INT8U  Top;
	INT8U  Err;
} ReadIRTcount ;

KAKA_IR_EXT	 xdata ReadIRByte Left_ReadIR;
KAKA_IR_EXT	 xdata ReadIRByte Mid_ReadIR;
KAKA_IR_EXT	 xdata ReadIRByte Right_ReadIR;

KAKA_IR_EXT  ReadIRTcount  LeftIR;
KAKA_IR_EXT  ReadIRTcount  RightIR;

KAKA_IR_EXT  ReadIRTcount  MidIR;

KAKA_IR_EXT void Init_IR();

KAKA_IR_EXT void LeftIR_Count(void);
KAKA_IR_EXT void RightIR_Count(void);
KAKA_IR_EXT void MidIR_Count(void);
KAKA_IR_EXT void CheckHandsetIR();
KAKA_IR_EXT void CheckRechargeIR();
KAKA_IR_EXT void ClearAllIR();
KAKA_IR_EXT void Read_RightIR();
KAKA_IR_EXT void Read_MidIR();
KAKA_IR_EXT void Read_LeftIR();	

#endif