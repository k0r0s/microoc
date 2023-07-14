#ifndef SYSTEM_R
#define SYSTEM_R 

struct System
{
	const void * class;
	int ninputs;
	int nstates;
	int noutputs;
	state_t state;
};

#endif
