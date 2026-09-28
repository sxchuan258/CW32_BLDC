#include "StateMachine.h"
#include "global.h"
#include "motor.h"
#include "sw_init.h"

extern System_Type System;

void MotorControl_StateMachine(void)
{
	if(SampleData[0] < 700)
	{
		ControlParameter_Init();
		SW_Init();
	}
	
	switch(Motor.RunState)
	{
		case STOP_STATE:
			/* 进入初始停止状态 */
			Motor.RunState = SELF_CHECK_STATE;
			Motor.Phase		 = 0;
			Motor.Duty		 = DUTY_MIN;
		break;
		
		case SELF_CHECK_STATE:
			if(SampleData[0] > 800) Motor.RunState = PRE_CHARGE_STATE;
		break;
		
		case PRE_CHARGE_STATE:
//			PWM_AL_ON;
//			PWM_BL_ON;
//			PWM_CL_ON;
			System.PreCharge_Time++;
			if(System.PreCharge_Time > 1000)
			{
				//Motor.RunState = ORIENT_INIT_STATE;
			}
		break;
		
		case ORIENT_INIT_STATE:
			/* 进入预定位初始化状态，定位到AB相 */
			Motor.Phase = Motor_NewPhaseValueGet(Motor.Phase);
			Motor_ChangePhase(Motor.Phase);
			Motor.RunState = ORIENT_END_STATE;
		break;
		
		case ORIENT_END_STATE:	//进入预定位结束状态
			System.Orient_Time++;
		
			if(System.Orient_Time > 500)
			{
				/* 进行强拖参数初始化 */
				Motor.Phase		 							 = 2;
				Motor.ForceState 						 = 1;
				Motor.DemagnetizationTimeCnt = 3;
				Motor.ForceRunTimeBase 			 = TIME_MAX;
				Motor.Duty 									 = DUTY_MIN;
				Motor.TerminalVoltageMax 		 = 0;
        Motor.TerminalVoltageMin 		 = 3708;

				Motor.RunState = FORCE_RUN_STATE;
			}
		break;
		
		case FORCE_RUN_STATE:		//进入强拖运行状态
			Motor.ForceRunTimeCnt++;
			switch(Motor.ForceState)
			{
				case 1:
					if(Motor.DemagnetizationTimeCnt > 0)
					{
						Motor.DemagnetizationTimeCnt--;
					}
					else
					{
						Motor.DemagnetizationTimeCnt = 3;
						Motor.ForceState = 2;
					}
				break;
				
				case 2:
					Motor.Phase = Motor_NewPhaseValueGet(Motor.Phase);
					Motor_ChangePhase(Motor.Phase);
					Motor.ForceRunTimeCnt = 0;
					Motor.ForceState = 3;
				break;
					
				case 3:
					TerminalVoltageGet();
				
					if(Motor.ForceRunTimeCnt > Motor.ForceRunTimeBase)
					{
						Motor.ForceState = 4;
					}
					
					if(Motor.TerminalVoltage > 500)
					{
						Motor.DetectBEMF_Times++;
						if(Motor.DetectBEMF_Times > 30000)
						{
							Motor.ForceState = 5;
						}
					}
				break;
				
				case 4:
					Motor.Duty++;
					if(Motor.Duty > DUTY_MAX)
					{
						Motor.Duty = DUTY_MAX;
					}
					Motor.ForceRunTimeBase--;
					if(Motor.ForceRunTimeBase < TIME_MIN)
					{
						Motor.ForceRunTimeBase = TIME_MIN;
					}
					Motor.ForceState = 1;
				break;
					
				case 5:
					Motor.Phase = Motor_NewPhaseValueGet(Motor.Phase);
					Motor_ChangePhase(Motor.Phase);
					Motor.DemagnetizationTimeCnt = 3;
					Motor.SensorlessState = 1;
					
					CW_BTIM2->CNT = 0;
					Motor.RunState = SENSORLESS_STATE;
				break;
			}
		break;
		
		case SENSORLESS_STATE: //进入无感方波运行状态
			switch(Motor.SensorlessState)
			{
				case 1:
					if(Motor.DemagnetizationTimeCnt > 0)
					{
						Motor.DemagnetizationTimeCnt--;
					}
					else
					{
//						if(Motor.Slope == 0)
//						{
							Motor.DemagnetizationTimeCnt = 3;
//						}
//						else
//						{
//							Motor.DemagnetizationTimeCnt = 7;
//						}
						//Motor.DemagnetizationTimeCnt = DemagnetizationTimeSet(Motor.Speed);
						Motor.SensorlessState = 2;
					}
				break;
					
				case 2:
					TerminalVoltageGet();
					Motor.Vbus = SampleData[0]*1;
					Motor.VbusZcp = Motor.Vbus >> 1; //1/2Vbus
				
					if(Motor.Slope)
					{
						if(Motor.TerminalVoltage >= Motor.VbusZcp)
						{
							BTIM_Cmd(CW_BTIM2, DISABLE);
//							if(Motor.Speed < 2500)
//							{
								Motor.CeventTime = (CW_BTIM2->CNT)>>1;
//							}
//							else
//							{
//								Motor_ConventTimeClc(Motor.Phase ,(CW_BTIM2->CNT)>>1);
//							}
							CW_BTIM2->CNT = 0;
							BTIM_Cmd(CW_BTIM2, ENABLE);
							
							CW_BTIM3->CNT = 0;
							CW_BTIM3->ARR = Motor.CeventTime;
							BTIM_ClearITPendingBit(CW_BTIM3, BTIM_IT_UPDATE);
							BTIM_Cmd(CW_BTIM3, ENABLE);
						}
					}
					else
					{
						if(Motor.TerminalVoltage <= Motor.VbusZcp)
						{
							BTIM_Cmd(CW_BTIM2, DISABLE);
//							if(Motor.Speed < 2500)
//							{
								Motor.CeventTime = (CW_BTIM2->CNT)>>1;
//							}
//							else
//							{
//								Motor_ConventTimeClc(Motor.Phase ,(CW_BTIM2->CNT)>>1);
//							}
							CW_BTIM2->CNT = 0;
							BTIM_Cmd(CW_BTIM2, ENABLE);
							
							CW_BTIM3->CNT = 0;
							CW_BTIM3->ARR = Motor.CeventTime;
							BTIM_ClearITPendingBit(CW_BTIM3, BTIM_IT_UPDATE);
							BTIM_Cmd(CW_BTIM3, ENABLE);
						}
					}
					
					/* 满足第一轮六个换相时间与转速的计算，进入速度闭环 */
					if(System.SpeedClcDown_FirstFlag == 1) ATIM_Cmd(ENABLE);
				break;
			}
		break;
		
		default:
			//电机停转
		break;
	}
}
