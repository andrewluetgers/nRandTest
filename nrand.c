#include <math.h>
#include <stdint.h>

static double seed = 75277.0;

double setSeed(double s) {
	return seed = s;
}

double sRand() {
	static double max = 1.0;
	static double min = 0.0;
	seed = (int64_t) (seed * 9301.0 + 49297.0) % 233280;
	return min + ((double)seed / 233280.0) * (max - min);
}

//Box muller method
// https://stackoverflow.com/questions/19944111/creating-a-gaussian-random-generator-with-a-mean-and-standard-deviation
double nRand(double mean, double stddev) {
	static double n2 = 0.0;
	static int n2_cached = 0;
	if (!n2_cached) {
		double x, y, r;
		do {
			x = 2.0*sRand() - 1;
			y = 2.0*sRand() - 1;
			r = x*x + y*y;
		} while (r == 0.0 || r > 1.0);

		double d = (sqrt(-2.0*log(r)/r) * stddev) + mean;
		double n1 = x*d;
		n2 = y*d;
		n2_cached = 1;
		return n1;

	} else {
		n2_cached = 0;
		return n2;
	}
}




/* rand31-park-miller-carta-int.c          Version 1.00  2005 September 21
 *
 * Robin Whittle  rw@firstpr.com.au
 *
 * For a full explanation, latest updates and the history of these
 * algorithms, see:
 *
 *    http://www.firstpr.com.au/dsp/rand31/
 */
long unsigned int rand31pmc_next(void);
void              rand31pmc_seedi(long unsigned int);
long unsigned int rand31pmc_ranlui(void);
float             pmc(void);
long unsigned int seed31pmc = 1;

#define constapmc 16807

long unsigned int rand31pmc_next() {
    long unsigned int hi, lo;
    lo = constapmc * (seed31pmc & 0xFFFF);
    hi = constapmc * (seed31pmc >> 16);
    lo += (hi & 0x7FFF) << 16;
    lo += hi >> 15;
    if (lo > 0x7FFFFFFF) lo -= 0x7FFFFFFF;
    return ( seed31pmc = (long)lo );
}

void pmcSetSeed(long unsigned int seedin) {
    if (seedin == 0) seedin = 1;
    seed31pmc = seedin;
}

float pmcRand(void) {
    return (rand31pmc_next() / 2147483647.0 );
}



inline float fastLog2 (float val)
{
   int *	     exp_ptr = (int)&val;
   int            x = *exp_ptr;
   const int      log_2 = ((x  23) & 255) - 128;
   x &= ~(255 << 23);
   x += 127 << 23;
   *exp_ptr = x;

   val = ((-1.0f/3) * val + 2) * val - 2.0f/3;   // (1)

   return (val + log_2);
}

inline float fastLog(float val)
{
   return (fastLog2(val) * 0.69314718f);
}


//
//#include <stdint.h>
//
///* The state must be seeded so that it is not zero */
//uint64_t s[2];
//
//uint64_t xorshift128plus(void) {
//	uint64_t x = s[0];
//	uint64_t const y = s[1];
//	s[0] = y;
//	x ^= x << 23; // a
//	s[1] = x ^ y ^ (x >> 17) ^ (y >> 26); // b, c
//	return s[1] + y;
//}