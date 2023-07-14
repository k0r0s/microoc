#ifndef PID_R
#define PID_R 

#include "pid.h"

struct PID
{ 
	struct System _; 
	double Kp;
	double Ki;
	double Kd;
	double minI;
	double maxI;
	double Ts;
	double tau;
};
	
#endif

