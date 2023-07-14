#include <stdio.h>

#include "plant.h"
#include "plant.r"
#include "new.h"
#include "new.r"

static void * Plant_ctor (void * _self, va_list * app)
{
	struct Plant * self = 
		(( const struct Class *) System) -> ctor(_self,app);
	return self;
}

static void * Plant_dtor (void * _self)
{
	struct Plant * self = _self;
	((const struct Class *) System) -> dtor(self);
	return 0;
}

static void Plant_update(void * _self, double * y, va_list * app)
{
	struct Plant * self = _self;
	double u = va_arg(* app, double);

	double y_prev = self->_.state[0];

	printf("y_prev = %lf - ", y_prev);
	printf("u = %lf - ", u);
	y[0] = 0.8276*u+0.9661*y_prev;

	printf("y_new = %lf\n", y[0]);

	/* 0.8276*u + 0.9661*Temp */

	self->_.state[0] = y[0];
}


static const struct Class _Plant = 
{
	sizeof(struct Plant), Plant_ctor, Plant_dtor, Plant_update
};

const void * Plant = &_Plant;
