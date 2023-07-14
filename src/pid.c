#include <stdio.h>

#include "pid.h"
#include "pid.r"
#include "new.h"
#include "new.r"

static void * PID_ctor (void * _self, va_list * app)
{
	struct PID * self = 
		(( const struct Class *) System) -> ctor(_self,app);

	PID_t  pid_param = va_arg(* app, PID_t);
	self->Kp 		 = pid_param.Kp;
	self->Ki 		 = pid_param.Ki;
	self->Kd 		 = pid_param.Kd;

	self->minI		 = pid_param.minI;
	self->maxI 		 = pid_param.maxI;

	self->Ts		 = pid_param.Ts;
	self->tau	 	 = pid_param.tau;

	/* TODO: check that the controller is feasible 
	 * Additional logic for maxI, minI, maxD,... */
	return self;
}

static void * PID_dtor (void * _self)
{
	struct PID * self = _self;
	((const struct Class *) System) -> dtor(self);
	return 0;
}

static void PID_update(void * _self, double * u, va_list * app)
{
	struct PID * self = _self;
	double inputs = va_arg(* app, double);

	double e = self->_.state[0];
	double p = self->_.state[1];
	double i = self->_.state[2];
	double d = self->_.state[3];
	
	/* TODO: Clean this */
	/* current error */
	e = inputs;
	/* proportional */
	p = self->Kp * e; // 
	/* integral */
	i = i + 0.5 * self->Ki * self->Ts * (e + self->_.state[0]);
	/* anti-wind up via integrator clamping */
	if ( i > self->maxI)
	{
		i = self->maxI;
	}
	else if ( i < self->minI)
	{
		i = self->minI;
	}
	/* filtered derivative */
	d = (2.0 * self->Kd * ( e - self->_.state[0])
		+ (2.0 * self->tau - self->Ts) * self->_.state[3]) / (2.0 * self->tau + self->Ts);
	
	self->_.state[0] = e;
	self->_.state[1] = p;
	self->_.state[2] = i;
	self->_.state[3] = d;

	*u = p+i+d;	
}

static const struct Class _PID = 
{
	sizeof(struct PID), PID_ctor, PID_dtor, PID_update
};

const void * PID = &_PID;
