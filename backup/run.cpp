#include "sm.h"
struct Ranq2
{
	unsigned long long v, w;
	Ranq2(unsigned long long j) : v(4101842887655102017LL), w(1) {
		v ^= j;
		w = int64();
		v = int64();
	}
	inline unsigned long long int64() {
		v ^= v >> 17; v ^= v << 31; v ^= v >> 8;
		w = 4294957665U * (w & 0xffffffff) + (w >> 32);
		return v ^ w;
	}
	inline double doub() { return 5.42101086242752217E-20 * int64(); }
	inline unsigned int int32() { return (unsigned int)int64(); }
};

struct Normaldev : Ranq2 {
	double mu, sig;
	Normaldev(double mmu, double ssig, unsigned long long i) : Ranq2(i), mu(mmu), sig(ssig) {}
	double dev();	//	Return a normal deviate.
};

using namespace std;
double n = 50000;
int main() 
{
	srand((unsigned)time(NULL));
	Ranq2 Rand((unsigned int)(time(NULL)));
	
	double ave = 0;
	
	for (int i = 0; i < n; i++)
	{
		//inter[0] = rand()/double(RAND_MAX);
		/*inter[0] = Rand.doub();
		inter[1] = inter[0] + 0.25;
		//inter[2] = rand()/double(RAND_MAX);
		inter[2] = Rand.doub();
		inter[3] = inter[2] + 0.5;
		x = unwrap(inter[1] - inter[2]);
		y = unwrap(inter[3] - inter[0]);

		inter[4] = cut(min(x, y));
		inter[3] = unwrap(inter[3]);
		inter[1] = unwrap(inter[1]);
		//cout << inter << endl;
		ave += inter[4];*/
		chromo a(4);
		chromo b(12);
		ave += a.compare(b);
	}
	cout << "P: " << ave/n << endl;
}

