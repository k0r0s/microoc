#ifndef PID_H
#define PID_H

#include "system.h"
#include "system.r"

typedef struct PID_tag
{
	double Kp;
	double Ki;
	double Kd;

	double minI;
	double maxI;

	double Ts;
	double tau;
} PID_t;

extern const void * PID;

#endif 
