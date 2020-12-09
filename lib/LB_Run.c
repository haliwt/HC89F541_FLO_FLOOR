/*

---------- file information -----------------------------------------------
file name:
define   : <??????>
version  : ?????β??
---------------------------------------------------------------------------
*/

//??????????
#define  KAKA_Run_GB

#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else
//#include "LB_hc89f003_IO.h"
#include "..\include\PJ_TypeRedefine.h"
#include "LB_Motor.h"
#include "LB_Run.h"
#include "LB_AD.h"
#include "LB_Led.h"
#include "LB_IR.h"
#include "LB_Usart.h"

#endif

/***************************************************************
	*
	*Function Name:void CheckRun()
	*Function : 
	*Input Ref: NO
	*Return Ref: No
	*
***************************************************************/
void  CheckRun()
{
    //开机执行 ,没有按下按键 ，初始化Step =0  Mode=1;Step=0;RunStep=0,RunMode =0 
	//  RunMode=2;  RunStep=1; KEY press 
	switch(RunMode) //initial RunMode =0
	{
		
	//RunMode =1 ,RunMode =0 ,don't run every one program .		
    case 2:
	{
	  switch(RunStep)
	  {
		  	case 0:
			{
			     
				

			}
			break;

		case 1: //KEY press  RunStep =1 
		{

            if(CurrentValue ==0){ //WT.EDIT.2020.11.16
				SetXMotor(2,40,160,2,2,40,160,2);//SetXMotor(2,5,20,2,2,5,20,2);//WT.EDIT //SetXMotor(2,20,40,2,2,20,40,2);//new line SetXMotor(1,20,40,1,1,20,40,1);
				
				SetMotorcm(1,5000);
				RunStep=2;
				RunMs=0;
			//	LedBlueON();
            }
			else
			   AllStop();	

			
		}
		break;
		case 2:
        {
		   // floor Robot to touch to wall 
          if((GroundDp[0]>GroundMin)||(GroundDp[1]>GroundMin)||(GroundDp[2]>GroundMin))
			{
				 AllStop();
				 //SetXMotor(1,20,1,1,1,20,1,1);
				  RunStep=3;
				 RunMs=0;			
			}
			if((RightMoveMotorData.Flag==1)||(LeftMoveMotorData.Flag==1))
			{
 				 if(CurrentValue ==0){ //WT.EDIT.2020.11.16
					SetXMotor(2,40,160,2,2,40,160,2);//SetXMotor(2,5,20,2,2,5,20,2);//WT.EDIT //SetXMotor(2,20,40,2,2,20,40,2);//new line SetXMotor(1,20,40,1,1,20,40,1);  //???
					
					SetMotorcm(1,5000);
 				}
				else  AllStop();
			}
			
			if(RunMs>2000)//if(RunMs>3000)
			{
				 AllStop();
				 //SetXMotor(1,20,1,1,1,20,1,1);
				RunStep=3;
				RunMs=0;	
			}
			
		}
			break;
		case 3:
		{
		   if(RunMs>20)  //Back run 
		   {
			 
			 if(CurrentValue ==0){ //WT.EDIT.2020.11.16
					SetXMotor(1,40,160,2,1,40,160,2);//SetXMotor(1,5,20,2,1,5,20,2);//WT.EDIT //SetXMotor(1,20,40,2,1,20,40,2);//new line //SetXMotor(2,20,40,1,2,20,40,1); //back 
					SetMotorcm(2,1000);
					RunStep=4;
				//	LedBlueON();
				}
			    else AllStop();
		   }
		    
		}
		break;
		case 4:
		{
			if(RunMs>120)
			{
				AllStop();
				//SetXMotor(2,20,1,1,2,20,1,1);
				RunMs=0;
				RunStep=5;
			//	LedBlueON();
			}
			
		}
			break;
	    case 5:
		  {
			if(RunMs>20) //right run  --
			{
				if(CurrentValue ==0){ //WT.EDIT.2020.11.16
					SetXMotor(1,40,160,2,2,40,160,2);//SetXMotor(1,5,20,2,2,5,20,2);//SetXMotor(1,20,40,2,2,20,40,2);//new line SetXMotor(2,20,40,1,1,20,40,1); //right turn 
				    SetMotorcm(3,5000);//SetMotorcm(3,9000);
					RunMs=0;
					RunStep=6;
				//	LedBlueON();
				}
				else{
					AllStop();

				}
			}	
			
		  }
		break;
		case 6:
			if(RunMs > 100)//if(RunMs>100)
			{
				AllStop();
				RunMs=0;
				RunStep=7;
			//	LedBlueON();
			}
			
			break;
		case 7: //water pump
			
			if(RunMs>20) //20 * 10ms =200ms
			{

				if(PumpTime >20){

					
				   RunMs=0;
				   RunStep=8;//??? //RunStep=12;
				   WaterPump(); 
				 //  LedBlueON();
				   if(CurrentValue ==0){ //WT.EDIT.2020.11.16
					    SetXMotor(2,40,160,2,1,40,160,2);//SetXMotor(2,5,20,2,1,5,20,2);//WT.EDIT  //SetXMotor(2,20,40,2,1,20,40,2);//SetXMotor(1,20,40,1,2,20,40,1); //left turn run 转圈
						SetMotorcm(4,4000);//WT.EDIT 2020.11.17//SetMotorcm(4,9000); //??
						SetXMotor(1,40,160,2,2,40,160,2);//SetXMotor(1,5,20,2,2,5,20,2); //WT.EDIT //SetXMotor(1,20,40,2,2,20,40,2); //SetXMotor(2,20,40,1,1,20,40,1); //right turn 
				        SetMotorcm(3,9000);
				   }
				    else AllStop();
		    	}
				else{
					RunMs=0;
					RunStep=2;//??? //RunStep=12;
					if(CurrentValue ==0){ //WT.EDIT.2020.11.16
					  SetXMotor(2,40,160,2,2,40,160,2);//SetXMotor(2,5,20,2,2,5,20,2); //SetXMotor(2,20,40,2,2,20,40,2);//new line //SetXMotor(1,20,40,1,1,20,40,1);//SetXMotor(1,20,25,1,1,20,40,1); //???
	                
					   SetMotorcm(1,5000);	
					}
					else AllStop();
				}

				
			}
		
	
			break;
		 case 8: // water pump

			        if(RunMs > 13){ //9
						WaterPumpStop();
				        RunMs=0;
					    RunStep=9;//??? //RunStep=12;
					   // LedBlueON();
			        }
		 break;
		 case 9:
		 {
		   if(RunMs > 240)
		   {
			//	LedBlueON();
				PumpTime=0;
			    RunMs=0;
			    RunStep=2; 
				if(CurrentValue ==0){ //WT.EDIT.2020.11.16
					SetXMotor(2,40,160,2,2,40,160,2);//SetXMotor(2,5,20,2,2,5,20,2);//WT.EDIT //SetXMotor(2,20,40,2,2,20,40,2);//new line //SetXMotor(1,20,40,1,1,20,40,1);//SetXMotor(1,20,25,1,1,20,40,1);//SetXMotor(1,20,25,1,1,20,40,1); //???
					
					SetMotorcm(1,5000);	
				}
				else AllStop();
		   }
		 }
		 break;
		}
	}
	
  }
	
}
/***************************************************************
	*
	*Function Name:void CheckMode(INT8U Key)
	*Function :
	*Input Ref: Key
	*Return Ref: No
	*
***************************************************************/
void CheckMode(INT8U Key)
{
   //开机执行 ,没有按下按键 ，初始化Step =0  Mode=1;Step=0;RunStep=0,RunMode =0 
  if(Key ==2){

       
	Mode = 40;
	Delay_ms(100);
	LedBlueOff();
	LedRedOff();
	Delay_ms(100);
	LedBlueON();
	LedRedON();
	
  }
  else  if(Key==1)
  {

	
    LedBlueON();
	if(Mode==0)  //初始化Mode =1
	{
	  //????
	  Mode=1;
	  Step=1;
	 
	}
	else { //开机执行 ,没有按下按键 ，初始化Step =0  Mode=1;Step=0;RunStep=0,RunMode =0 
	  if(Step==0)
	  {
	    Step=1; 
	    ADCtl=1;
        RunSecond=0; //第一次，按key Power On
	  }
	  else	if(Step<20)
	  {
		//LedBlueON();
		Mode=1;
		Step=0;
		RunSecond=0;
		AllStop();
		SetEdge(0);
		RunStep=0;
				//SetBuzzerTime(2);
	  }
	}
  }

 //开机执行 ,没有按下按键 ，初始化 Mode=1;Step=0;RunStep=0,RunMode =0 
  switch(Mode)
  {
  	case 0:
	{
	  switch(Step) //Power On step =1; Mode =1
	  {
	     //???????,?????????
	     case 0:
		 {

			AllStop();
			LedBlueOff();

		 }
		 break;
		 //???????,???????1??2?????????4??
		 case 1:
		 {
		    //if(RunSecond==20)
			{
			  RunSecond=0;
		     // LedBlueON();
			  //Step=2;
			}
		 }

		 case 10:
		 {
		   if(RunSecond>0)
		   {
		   	   Step=0;
			   RunSecond=0;
			    
		   }
		 }
		 break;
	  
	  }
	}
	break;
	//开机执行 ,没有按下按键 ，初始化Step =0  Mode=1;Step=0;RunStep=0,RunMode =0 
	case 1:  //Key press   Mode =1,Step =1  
    {
	   switch(Step) //step =1
	   {
	     //?????????1????2??
	   	 case 0:
		 {
		   //ADCtl=1;
		  //
		   if(RunSecond>15) //16 * 1s = 16s---
		   {
		     //Step=0;
			 //Mode=0;
			 RunSecond=0;
			 LedBlueOff();
             ADCtl=0;
		   }
		 // ADCtl=1;

	   		if(ReadPowerDCIn())
			{
				Step=5;

			}
		 } 
		 break;
		 //Step =1 ,key press the first
		 case 1: //The first key press  Step=1; RundSecond =0 
		 {
		   if(RunSecond>0)  //在TIMER 1 中，0.1ms interrupt
		   {
		   	  Step=2; //Next run 2
			  LedBlueON();
			  ADCtl=1;

			  
			  RunMode=2;
			  RunStep=1;
			  ADCtl=1;

				RunMs=0;
			  NoImpSecond=0;

		   }
		 }
		 break;
		 
		 case 2:
		 {

		  
		  if(Voltage<960) //Batter of detected voltage
		  {

			     ADCtl=0;
			     RunStep=0;
			  	 AllStop();

				 SetEdge(0);

				 Step=8;
			 
			} 
			else  if(ReadPowerDCIn())
			  {
			     ADCtl=0;
			     RunStep=0;
			  	 AllStop();

				 SetEdge(0);

				 Step=5;


			  }
			  if(NoImpSecond==40)
			  {
			    SetEdge(50);
				NoImpSecond=41;
			  }
			 if(NoImpSecond==45)
			 {
			    SetEdge(0);
				NoImpSecond=0;		 
			 }
			  
			 }
		 break;
		 //???????????????????2Hz

		 case 3:
		 {

		   if(RunSecond>0)
		   {
			 LedBlueON();
			 	   	 
			 Step=4;
			 RunSecond=0;
		   }

		   
          if(ReadPowerDCIn())
		  {
		     ADCtl=0;
		     RunStep=0;
		  	 AllStop();
			 SetEdge(0);

			 Step=5;


		  }
		  
		 }
		 break;
		 
		 case 4:
		 {

		   if(RunSecond>0)
		   {
			  LedBlueOff();
  	 
			 Step=3;
			 RunSecond=0;
		   }
		   
          if(ReadPowerDCIn()) //?????GPIO ==1 ,??????????
		  {
		     ADCtl=0;
		     RunStep=5;
		  	 AllStop();
			 SetEdge(0);


		  }	

		 }
		 break;
		// ????е????? 0.5Hz
		 case 5:
		 {
		   if(RunSecond>1) //2 * 1s =2s
		   {
			 LedBlueON();  
			 Step=6;
			 RunSecond=0;
		   }

		 }
		 break;
		 
		 case 6:
		 {
		   if(PowerCountErr>29)
		   {
		   	  //LedBlueON();
			  Step=10; 
		   }

		   if(RunSecond>1)
		   {
		   	 LedBlueOff();
			 Step=5;
			 RunSecond=0;
		   }
		   else if(PowerCountOK>20) //batter charge is over 
		   {
		   	  Step=7;
		   }		   
		   else if(0==ReadPowerDCIn())
		   {
		   	 Step=0;
			 Mode=1;
			 //SetBuzzerTime(1);
		   }
		 }
		 break;
		 //???粻??
		 case 7:
		 if(0==ReadPowerDCIn())
		   {
		   	 Step=0;
			 Mode=0;
		   }
		
		   else if(Voltage<970)
		   {
		   	  Step=5;
			  
			  //SetBuzzerTime(3);
		   }
		 break;

		 case 8:
		 {
		   if(RunSecond>0)
		   {
			  LedBlueON();
		   	 
			 Step=9;
			 RunSecond=0;
		   }
        if(ReadPowerDCIn())
		  {
		     RunStep=5;

		  }
		 }
		 break;
		 
		 case 9:
		 {
		   if(RunSecond>0)
		   {

             LedBlueOff();	   	 
			 Step=8;
			 RunSecond=0;
		   }
        if(ReadPowerDCIn())
		  {
		     RunStep=5;

		  }
		 }
		 break;

		 case 10:
		 {
		   if(NoImpSecond>0)//100ms
		   {
			  LedBlueON();
		   	 
			 Step=11;
			 NoImpSecond=0;
		   }

		 }
		 break;
		 
		 case 11:
		 {
		   if(NoImpSecond>0)
		   {

             LedBlueOff();	   	 
			 Step=10;
			 NoImpSecond=0;
		   }

		 }
		 break;
		 case 20:
		 {
		 	if((GroundDp[0]>GroundMin)&&(GroundDp[1]>GroundMin)&&(GroundDp[2]>GroundMin))
			  LedBlueON();
			else
			  LedBlueOff();
		 }
		 break;

	   }
	}
	break;
	
      
	case 40 :
         
		  if(RunMs >10){
			ADFlag=1;
			RunMs =0;
			AllStop();
			RunStep=0;
			LedBlueON();
			LedRedON();
			CheckGround();
			SelfChecking();
		  }
		
		


	break;

  }
}