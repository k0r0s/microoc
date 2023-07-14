#include <stdio.h>
#include <stdlib.h>

#include "system.h" // extern const void * Controller 
#include "system.r" // Controller struct

#include "new.h" // new, delete, update
#include "new.r" // Class struct with ctor,dtor,...

static void * System_ctor (void * _self, va_list * app) 
{
	struct System * self = _self; 
	system_desctor_t sys = va_arg(* app, system_desctor_t);

	self->ninputs 	= sys.ninputs;
	self->nstates 	= sys.nstates;
	self->state 	= (double *) malloc(sizeof(double)*self->nstates);
	self->noutputs 	= sys.noutputs;

	for (int i = 0; i < self->nstates; i++)
	{
		self->state[i] = 0.0;
	}
	return self;
}

static void * System_dtor (void * _self)
{
	struct System * self = _self;
	free(self->state);
	return 0;
}

static const struct Class _System = 
{
	/* where we to malloc a dtor would be needed to free */
	sizeof(struct System), System_ctor, System_dtor, 0
};

const void * System = &_System;

