#ifndef __CONTROL_H
#define __CONTROL_H

#include"global.h"

extern PI_Type	SpeedCtrl_PI;
extern PI_Type	Phase1RunTime_PI;
extern PI_Type	Phase2RunTime_PI;
extern PI_Type	Phase3RunTime_PI;
extern PI_Type	Phase4RunTime_PI;
extern PI_Type	Phase5RunTime_PI;
extern PI_Type	Phase6RunTime_PI;

int PID_Control(unsigned int FeedBack_Value ,unsigned int Ref ,PI_Type *PI);

#endif
