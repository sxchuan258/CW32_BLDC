#include "main.h"
#include "global.h"
#include "sensorlessP.h"
#include "sensorless.h"
#include "motor.h"
#include "init.h"
#include "StateMachine.h"

extern System_Type System;
void ADCS_chuli(void);

void ADC_IRQHandler(void)
{
    /* USER CODE BEGIN */
  if (CW_ADC->ISR_f.EOS)
  {
    ADC_ClearITPendingAll();//清除AD所有中断标志
		
	  ADC_GetSqr0Result(&SampleData[0]); //母线电压
		ADC_GetSqr1Result(&SampleData[1]); //U/A相
		ADC_GetSqr2Result(&SampleData[2]); //V/B相
		ADC_GetSqr3Result(&SampleData[3]); //W/C相
	  //ADC_GetSqr4Result(&SampleData[4]); //母线电流 
		
		if(System.OverTurn_Flag == 0)
		{
			System.OverTurn_Flag = 1;
			LEDON;
		}
		else
		{
			System.OverTurn_Flag = 0;
			LEDOFF;
		}

		MotorControl_StateMachine();
	}
}
