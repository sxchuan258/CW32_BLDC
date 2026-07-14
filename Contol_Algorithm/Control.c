#include "Control.h"
#include "global.h"

extern Motor_Type Motor;

unsigned int PID_Control(unsigned int FeedBack_Value)
{
	unsigned int 				OutPut_Value;
	double 				Error;
	static double ErrorSum = 0;
	
	Error 	 		 = 3000 - FeedBack_Value*1.0;
	ErrorSum 		 = ErrorSum + Error;
	OutPut_Value = 0.015*Error + 0.01*ErrorSum;
	
	if(OutPut_Value < DUTY_MIN)
	{
		OutPut_Value = DUTY_MIN;
	}
	else if(OutPut_Value > 1000)
	{
		OutPut_Value = 1000;
	}
	
	return OutPut_Value;
}
