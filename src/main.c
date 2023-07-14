#include <stdio.h>
#include <assert.h>

#include "system.h"
#include "pid.h"
#include "plant.h"

#include "new.h"

int main (int argc, char ** argv)
{
	void * c, * p;

	double sp[1] = {9.0}; // setpoint
	double e[1]  = {0.0}; // error
	double u[1]	 = {0.0}; // control signal
	double y[1]  = {0.0}; // output

	
	PID_t pid_param = {.Kp=0.4, .Ki=0.2, .Kd=0, .minI=0.0, .maxI=3.0, .Ts=0.3, .tau=0};
	system_desctor_t pid_sys = {.ninputs=1, .nstates=4, .noutputs=1};
	c = new(PID, pid_sys, pid_param); 
	
	system_desctor_t sys_p = {.ninputs=1, .nstates=1, .noutputs=1};
	p = new(Plant, sys_p);

	for (int i = 0; i < 100; i++)
	{
		/* compute error:  e = sp - y */
		e[0] = sp[0] - y[0];

		/* compute control signal: u = f(e); */
		update(c, u, e[0]); // TODO: might need to change e[0] to e only
		
		/* update plant: y = f(u); */
		update(p, y, u[0]);

	}

	delete(c);
	delete(p);
	return 0; 
}
