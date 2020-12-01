/*

---------- file information -----------------------------------------------
file name: 
define   : <�ļ�˵��>
version  : ���ļ�β��
---------------------------------------------------------------------------
*/

//ȫ�ֱ�������
#define  KAKA_AD_GB

#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else
//#include "LB_hc89f003_IO.h"
#include "..\include\PJ_TypeRedefine.h"
#include "..\lib\LB_Led.h"
#include "LB_AD.h"
#include "LB_Motor.h"

#endif
/**
  * @˵��  	��ʱ����
  * @����  	fui_i : ��ʱʱ��
  * @����ֵ ��
  * @ע 	Fcpu = 16MHz,fui_i = 1ʱ,��ʱʱ��ԼΪ2us
  */
void Delay_2us(unsigned int fui_i)
{
	while(fui_i--);	
}

/*************************************************************
	*
	*Function Name:void CheckEdgeCurrent()
	*Function :

	*Input Ref: NO
	*Return Ref: NO
	*
*************************************************************/
void InitADIO(void)
{
	P0M2 = 0x02;				        //P02����Ϊģ������---��ص�ѹ��⣨��ر��壩

	P0M3 = 0x02;				        //P03����Ϊģ������---IR_MID_WALL �м�IR
	P0M4 = 0x02;				        //P04����Ϊģ������---IR_L_WALL
	P0M5 = 0x02;				        //P05����Ϊģ������---IR_R_WALL

	P0M6 = 0x02;				        //P06����Ϊģ������---MOTOR_L_CURRENT_
	P0M7 = 0x02;				        //P07����Ϊģ������---MOTOR_R_CURRENT
	P2M5 = 0x02;				        //P25����Ϊģ������---��ˮMOTOR_CURRENT

	P0M1 = 0X80;                        //IR_WALL_PW ���GPIO 
}
/*************************************************************
	*
	*Function Name:void SeleADChanel(INT8U ADChanel)
	*Function :

	*Input Ref: ADChannel
	*Return Ref: NO
	*
*************************************************************/
void SeleADChanel(INT8U ADChanel)
{
	ADCC0 = 0x81;						//��ADCת����Դ
	ADCC1 = (ADChanel&0X0F);			//ѡ���ⲿͨ��0
	ADCC2 = 0x4f;						//ת�����12λ���ݣ������Ҷ��룬ADCʱ��16��Ƶ

}
/*************************************************************
	*
	*Function Name:void CheckEdgeCurrent()
	*Function :

	*Input Ref: NO
	*Return Ref: NO
	*
*************************************************************/
void StartAD()
{
	ADCC0&=0XDF;
	ADCC0 |= 0x40;					//����ADCת��
}
/*************************************************************
	*
	*Function Name:void SetADINT(void)
	*Function :

	*Input Ref: NO
	*Return Ref: NO
	*
*************************************************************/
void SetADINT(void)
{
    EADC = 1;                                   //ʹ��ADC�ж�
    EA = 1;
}

/*************************************************************
	*
	*Function Name:void  SetAD(INT8U ADChanel)
	*Function :

	*Input Ref: ADChanel
	*Return Ref: NO
	*
*************************************************************/
void  SetAD(INT8U ADChanel)
{
  code INT8U ADCC[7]={2,3,4,5,6,7,13};//batter,M_IR,L_IR,R_IR,L_curretn,R_cu,Pump_cuuretn
  SeleADChanel(ADCC[ADChanel]);
  SetADINT();
  StartAD();
}
/*************************************************************
	*
	*Function Name:void ReadAD5ms()
	*Function :
��ȡ����IR��ֵ
	*Input Ref: NO
	*Return Ref: NO
	*
*************************************************************/
void ReadAD5ms()
{
  static INT8U i=0;
  static INT8U chanel=5;
  static INT16U ADtemp[5];                        
  ADtemp[i]=ADCR; //ADC ת������Ĵ���,ADCC[7]={2,3,4,5,6,7,13};
  i++;
  if(i>2)
  {
     i=0;
	 AD5ms[chanel]= (ADtemp[1]+ADtemp[2])/2; // (IR_MID_WALL + IR_L_WALL)
	 chanel++;
	 if(chanel>6) //AN3 ,AN4, AN5 rIR input 
	 {
	
	   if(ADCtl) // power on initial value ADCtl = 1;
	   {
		   if(ADFlag) //IR turn on _ turn off 
		   {
			 P0_1 = 1; //IR ����GPIO  ,IR_POWER output +5V IR works
			 ADFlag=0; //IR_WorksFlag =1
			 ADFlashFlag=1;
		   }
		  else //turn off //T = 0.2ms
		  {
			 P0_1 = 0; // IR don't works
			 ADFlag=1;  //IR_WorksFlag =1
			 ADFlashFlag=1;
		  }
	  }
	  else{
	  	 P0_1 = 0;// IR don't works
	  }
		//SBUF=(AD5ms[1]>>4);
	    chanel=0;
	}
  }
  else
  {
  	 SetAD(chanel); //ADCת��
  }
}
/*************************************************************
	*
	*Function Name:INT8U ReadGroundDp(INT8U *p)
	*Function :

	*Input Ref: *P
	*Return Ref: NO
	*
*************************************************************/
INT8U ReadGroundDp(INT8U *p)
{
  INT8U i;
  INT16U temp,tempMin,tempMax;
  temp=0;


  tempMin=*p;
  tempMax=*p;
  for(i=1;i<10;i++)
  {
    
	if(tempMin>*(p+i))
	{
	   tempMin=*(p+i);
	}
	else if(tempMax<*(p+i))
	{
	   tempMax=*(p+i);
	}
	else
	 temp+=*(p+i);
  }
  
  return(temp/8);
}
/*************************************************************
	*
	*Function Name:void CheckGround()
	*Function :

	*Input Ref: NO
	*Return Ref: NO
	*
*************************************************************/
void CheckGround()
{
 if(ADFlashFlag)//IR of works flag bit.
 {
   if(ADFlag)
   {
   	   GroundAD[0][0]=(AD5ms[2]>>4); // L_WALL //ADtemp[i]=ADCR; //ADC ת������Ĵ���,ADCC[7]={2,3,4,5,6,7,13};
	   GroundAD[1][0]=(AD5ms[1]>>4); //M_WALL IR_WALL �ж�ֵ
	   GroundAD[2][0]=(AD5ms[3]>>4); //R_WALL 
	   ADFlashFlag=0;
	 //SBUF=GroundAD[0][0];
    if(GroundAD[0][1]>GroundAD[0][0]) // IR_M_WALL 
	{
       GroundAD100Ms[0][ADTime]=GroundAD[0][1]-GroundAD[0][0];
	}
	else
       GroundAD100Ms[0][ADTime]=GroundAD[0][0]-GroundAD[0][1];

    if(GroundAD[1][1]>GroundAD[1][0]) //IR_L_WALL
	{
       GroundAD100Ms[1][ADTime]=GroundAD[1][1]-GroundAD[1][0];
	}
	else
	  GroundAD100Ms[1][ADTime]=GroundAD[1][0]-GroundAD[1][1];

    if(GroundAD[2][1]>GroundAD[2][0]) 
	{

       GroundAD100Ms[2][ADTime]=GroundAD[2][1]-GroundAD[2][0];
	}
	else
	  GroundAD100Ms[2][ADTime]=GroundAD[2][0]-GroundAD[2][1];

	 ADTime++;
   if(ADTime>7)
   {
   	  ADTime=0;
	  GroundDp[0]=(GroundAD100Ms[0][0]+GroundAD100Ms[0][2]+GroundAD100Ms[0][4]+GroundAD100Ms[0][6])/4; //ir_L_wall
      //ir_M_wall
	  GroundDp[1]=(GroundAD100Ms[1][0]+GroundAD100Ms[1][2]+GroundAD100Ms[1][4]+GroundAD100Ms[1][6])/4; //ir_M_wall
	  //ir_R_wall
	  GroundDp[2]=(GroundAD100Ms[2][0]+GroundAD100Ms[2][2]+GroundAD100Ms[2][4]+GroundAD100Ms[2][6])/4; //ir_R_wall

   }
   //SBUF=AD5ms[5]/16;//ADC ת������Ĵ���,ADCC[7]={2,3,4,5,6,7,13};
   	LCurrentAD[ADTime]=AD5ms[4]; //L_speed current value 
	RCurrentAD[ADTime]=AD5ms[5]; //R_speed
	  
   }
   else
   {

	   GroundAD[0][1]=(AD5ms[3]>>4); 
	   GroundAD[1][1]=(AD5ms[2]>>4);
	   GroundAD[2][1]=(AD5ms[1]>>4);
	   ADFlashFlag=0;
   }

 }
}
/*************************************************************
	*
	*Function Name:void CheckEdgeCurrent()
	*Function :

	*Input Ref: NO
	*Return Ref: NO
	*
*************************************************************/
void CheckEdgeCurrent()
{

 EdgeCurrent=(EdgeCurrent*9+((AD5ms[6]*13)/5))/10;//ADCC[7]={2,3,4,5,6,7,13};
 if(EdgeCurrent>0x80)
 EdgeCurrentOverCount++;
 else 
 {
   if(EdgeCurrentOverCount>1)
     EdgeCurrentOverCount--;
 }
  if(EdgeCurrent<30)
   EdgeCurrentLessCount++;
  else
 {
   if(EdgeCurrentLessCount>1)
     EdgeCurrentLessCount--;
 }
}

/*************************************************************
	*
	*Function Name:void CheckLCurrent()
	*Function :
	*Input Ref: NO
	*Return Ref: NO
	*
*************************************************************/
void CheckLCurrent()
{
 INT16U	LCurrentADAvg;
 LCurrentADAvg=(LCurrentAD[0]+LCurrentAD[2]+LCurrentAD[4]+LCurrentAD[6])/4;
 //SBUF= (INT8U)LCurrentADAvg;////ADC ת������Ĵ���,ADCC[7]={2,3,4,5,6,7,13};
 LCurrent=(LCurrent*9+(LCurrentADAvg*9.6))/10;
				
}
void CheckRCurrent()
{
 INT16U	RCurrentADAvg;
 RCurrentADAvg=(RCurrentAD[0]+RCurrentAD[2]+RCurrentAD[4]+RCurrentAD[6])/4;

 RCurrent=(RCurrent*9+(RCurrentADAvg*9.6))/10;
 //5000/4096/0.1
 
}
/*************************************************************
	*
	*Function Name:void CheckEdgeCurrent()
	*Function :batter of voltage 
	*Input Ref: NO
	*Return Ref: NO
	*
*************************************************************/
void CheckVoltage()
{
   Voltage=(Voltage*19+(AD5ms[0]/2.56))/20; //��ر����������
   //4000*4/4096/10

}

/***************************************************************************************
  * @˵��  	ADC�жϷ�����
  *	@����	��
  * @����ֵ ��
  * @ע		��
***************************************************************************************/
void ADC_Rpt() interrupt ADC_VECTOR
{

    IE1 &=~ 0x40;                       //�ر�ADC�ж�
    ADCC0 &=~ 0x20;						//���ADC�жϱ�־λ

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

	   LedBlueOff();
	   LedRedOff();

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