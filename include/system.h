#ifndef SYSTEM_H 
#define SYSTEM_H 

typedef double * state_t;
typedef struct system_desctor_tag 
{
	int ninputs;
	int nstates;
	int noutputs;
} system_desctor_t;

extern const void * System;


#endif

