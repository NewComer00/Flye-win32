/*  rand.c -- drand48 implementation from the FreeBSD source tree. */

// This file is an amalgamation of the many small files in FreeBSD to do with
// drand48 and friends implementations.
// It comprises _rand48.c, rand48.h, srand48.c, drand48.c, erand48.c, lrand48.c

/*
 * Copyright (c) 1993 Martin Birgmeier
 * All rights reserved.
 *
 * You may redistribute unmodified or modified versions of this source
 * code provided that the above copyright notice and this and the
 * following conditions are retained.
 *
 * This software is provided ``as is'', and comes with no warranties
 * of any kind. I shall in no event be liable for anything that happens
 * to anyone/anything when using this software.
 */

//#include <sys/cdefs.h>
//__FBSDID("$FreeBSD: src/lib/libc/gen/_rand48.c,v 1.2 2002/03/22 21:52:05 obrien Exp $");

#include <math.h>

#define	RAND48_SEED_0	(0x330e)
#define	RAND48_SEED_1	(0xabcd)
#define	RAND48_SEED_2	(0x1234)
#define	RAND48_MULT_0	(0xe66d)
#define	RAND48_MULT_1	(0xdeec)
#define	RAND48_MULT_2	(0x0005)
#define	RAND48_ADD	(0x000b)

static unsigned short _rand48_seed[3] = {
	RAND48_SEED_0,
	RAND48_SEED_1,
	RAND48_SEED_2
};
static unsigned short _rand48_mult[3] = {
	RAND48_MULT_0,
	RAND48_MULT_1,
	RAND48_MULT_2
};
static unsigned short _rand48_add = RAND48_ADD;

static void
_dorand48(unsigned short xseed[3])
{
	unsigned long long accu;
	unsigned short temp[2];

	accu = (unsigned long long) _rand48_mult[0] * (unsigned long long) xseed[0] +
	 (unsigned long long) _rand48_add;
	temp[0] = (unsigned short) accu;	/* lower 16 bits */
	accu >>= sizeof(unsigned short) * 8;
	accu += (unsigned long long) _rand48_mult[0] * (unsigned long long) xseed[1] +
	 (unsigned long long) _rand48_mult[1] * (unsigned long long) xseed[0];
	temp[1] = (unsigned short) accu;	/* middle 16 bits */
	accu >>= sizeof(unsigned short) * 8;
	accu += _rand48_mult[0] * xseed[2] + _rand48_mult[1] * xseed[1] + _rand48_mult[2] * xseed[0];
	xseed[0] = temp[0];
	xseed[1] = temp[1];
	xseed[2] = (unsigned short) accu;
}

void
hts_srand48(long long seed)
{
	_rand48_seed[0] = RAND48_SEED_0;
	_rand48_seed[1] = (unsigned short) seed;
	_rand48_seed[2] = (unsigned short) (seed >> 16);
	_rand48_mult[0] = RAND48_MULT_0;
	_rand48_mult[1] = RAND48_MULT_1;
	_rand48_mult[2] = RAND48_MULT_2;
	_rand48_add = RAND48_ADD;
}

double
hts_erand48(unsigned short xseed[3])
{
	_dorand48(xseed);
	return ldexp((double) xseed[0], -48) +
	       ldexp((double) xseed[1], -32) +
	       ldexp((double) xseed[2], -16);
}

double
hts_drand48(void)
{
	return hts_erand48(_rand48_seed);
}

long long
hts_lrand48(void)
{
	_dorand48(_rand48_seed);
	return ((long long) _rand48_seed[2] << 15) + ((long long) _rand48_seed[1] >> 1);
}
