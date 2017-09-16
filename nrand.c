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