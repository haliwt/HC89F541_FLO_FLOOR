/*

---------- file information -----------------------------------------------
file name: 
define   : <�1�7�0�4�1�7�0�5�1�7�1�7>
version  : �1�7�1�7�1�7�0�4�1�7�1�7�1�7
---------------------------------------------------------------------------
*/
#ifndef  LB_IR_h
#define  LB_IR_h



#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else

#include "..\include\PJ_TypeRedefine.h"


#endif


//�0�0�1�7�0�1�1�7�1�7�1�7�1�7�1�7�1�7�1�7
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
	INT8U  Runcontrol;
} ReadIRByte ;

KAKA_IR_EXT	 xdata ReadIRByte Remote1_ReadIR;



KAKA_IR_EXT void Init_IR();

KAKA_IR_EXT void Remote1_Count(void);
KAKA_IR_EXT void Read_Remote1IR();

KAKA_IR_EXT INT8U CheckHandsetIR();
KAKA_IR_EXT  void  CheckXReadIR(ReadIRByte *P);

#endif