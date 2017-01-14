// Copyright (c) 2017 Daniel Pedersen. Subject to the GNU GPLv3.

#include "random.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

void kmcrand_init()
{
	srand((int)time(NULL));
}

double urand()
{
	return (double)(rand() + 1l) / (RAND_MAX + 1l);
}

double kmcrand(double k)
{
	return -log(urand()) / k;
}
