#include "Control.h"
#include "global.h"

PI_Type	SpeedCtrl_PI;
PI_Type	Phase1RunTime_PI;
PI_Type	Phase2RunTime_PI;
PI_Type	Phase3RunTime_PI;
PI_Type	Phase4RunTime_PI;
PI_Type	Phase5RunTime_PI;
PI_Type	Phase6RunTime_PI;

extern Motor_Type Motor;

int PID_Control(unsigned int FeedBack_Value ,unsigned int Ref ,PI_Type *PI)
{
	int Error;
	
	Error 	 			= Ref - FeedBack_Value;
	PI->IntegPart = PI->IntegPart + Error;
	PI->Out  			= PI->Kp*Error + PI->Ki*PI->IntegPart;
	PI->Out	 			= PI->Out >> 15;
	
	if(PI->Out < PI->PIMin)
	{
		PI->Out = PI->PIMin;
	}
	else if(PI->Out > PI->PIMax)
	{
		PI->Out = PI->PIMax;
	}
	
	return PI->Out;
}
