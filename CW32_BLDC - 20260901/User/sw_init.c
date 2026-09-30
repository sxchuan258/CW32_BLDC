#include "sw_init.h"
#include "global.h" 
#include "Control.h"
#include "sw_init.h"

extern System_Type System;
extern Motor_Type  Motor;

void ControlParameter_Init(void)
{
	SpeedCtrl_PI.Kp  	 		 = 0.05 * (1 << 15);
	SpeedCtrl_PI.Ki  	 		 = 0.00015	* (1 << 15);
	SpeedCtrl_PI.PIMin 		 = PWM_PERIOD * 0.15;
	SpeedCtrl_PI.PIMax 		 = PWM_PERIOD * 0.99;
	SpeedCtrl_PI.IntegPart = 0;
	
	Phase1RunTime_PI.Kp 			 = 0.005 * (1 << 15);
	Phase1RunTime_PI.Ki 			 = 0.01 * (1 << 15);
	Phase1RunTime_PI.PIMin 		 = -200;
	Phase1RunTime_PI.PIMax 		 = 200;
	Phase1RunTime_PI.IntegPart = 0;
	
	Phase2RunTime_PI.Kp 			 = 0.005 * (1 << 15);
	Phase2RunTime_PI.Ki 			 = 0.01 * (1 << 15);
	Phase2RunTime_PI.PIMin 		 = -200;
	Phase2RunTime_PI.PIMax 		 = 200;
	Phase2RunTime_PI.IntegPart = 0;
	
	Phase3RunTime_PI.Kp 			 = 0.005 * (1 << 15);
	Phase3RunTime_PI.Ki 			 = 0.01 * (1 << 15);
	Phase3RunTime_PI.PIMin 		 = -200;
	Phase3RunTime_PI.PIMax 		 = 200;
	Phase3RunTime_PI.IntegPart = 0;
	
	Phase4RunTime_PI.Kp 			 = 0.005 * (1 << 15);
	Phase4RunTime_PI.Ki 			 = 0.01 * (1 << 15);
	Phase4RunTime_PI.PIMin 		 = -200;
	Phase4RunTime_PI.PIMax 		 = 200;
	Phase4RunTime_PI.IntegPart = 0;
	
	Phase5RunTime_PI.Kp 			 = 0.005 * (1 << 15);
	Phase5RunTime_PI.Ki 			 = 0.01 * (1 << 15);
	Phase5RunTime_PI.PIMin 		 = -200;
	Phase5RunTime_PI.PIMax 		 = 200;
	Phase5RunTime_PI.IntegPart = 0;
	
	Phase6RunTime_PI.Kp 			 = 0.005 * (1 << 15);
	Phase6RunTime_PI.Ki 			 = 0.01 * (1 << 15);
	Phase6RunTime_PI.PIMin 		 = -200;
	Phase6RunTime_PI.PIMax 		 = 200;
	Phase6RunTime_PI.IntegPart = 0;
}

void SW_Init(void)
{
	Motor.CeventTime 			 			 = 0;
	Motor.Duty			 			 			 = 0;
	Motor.ForceRunTimeBase 			 = 0;
	Motor.ForceRunTimeCnt	 			 = 0;
	Motor.Phase						 			 = 0;
	Motor.SixTyRunTime[0]	 			 = 0;
	Motor.SixTyRunTime[1]	 			 = 0;
	Motor.SixTyRunTime[2]	 			 = 0;
	Motor.SixTyRunTime[3]	 			 = 0;
	Motor.SixTyRunTime[4]	 			 = 0;
	Motor.SixTyRunTime[5]	 			 = 0;
	Motor.Slope						 		   = 0;
	Motor.Speed						 			 = 0;
	Motor.SpeedRef				 			 = 0;
	Motor.Speed_u32				 			 = 0;
	Motor.Speed_u32_1_6		 			 = 0;
	Motor.SensorlessState				 = 0;
	Motor.TerminalVoltage	 			 = 0;
	Motor.VbusZcp					 			 = 0;
	Motor.RunState				 			 = 0;
	Motor.DemagnetizationTimeCnt = 0;
	
	System.OpenLopp_RunTimes 			= 0;
	System.Orient_Time			 			= 0;
	System.PreCharge_Time		 			= 0;
	System.OverTurn_Flag		 			= 0;
	System.SpeedClcDown_FirstFlag	= 0;
}
