#include <stdint.h>
#include <complex>
using namespace std;

#define ARRAY_SIZES (2048)
#define REPEATES (5e5*1)
int int_g[ARRAY_SIZES];

/*! Setup arrays that are done from global memory*/
int8_t  int8_g[ARRAY_SIZES];
int8_t  int8_g2[ARRAY_SIZES];

int16_t int16_g[ARRAY_SIZES];
int16_t int16_g2[ARRAY_SIZES];

int32_t int32_g[ARRAY_SIZES];
int32_t int32_g2[ARRAY_SIZES];

complex<int32_t> cx_int32_g[ARRAY_SIZES];
complex<int32_t> cx_int32_g2[ARRAY_SIZES];


int64_t int64_g[ARRAY_SIZES];
int64_t int64_g2[ARRAY_SIZES];

float   float_g[ARRAY_SIZES];
float   float_g2[ARRAY_SIZES];


double  double_g[ARRAY_SIZES];
double  double_g2[ARRAY_SIZES];

complex<float> cx_float_g[ARRAY_SIZES];
complex<float> cx_float_g2[ARRAY_SIZES];

complex<double> cx_double_g[ARRAY_SIZES];
complex<double> cx_double_g2[ARRAY_SIZES];

#include <iostream>
#include <boost/date_time.hpp>
#include <armadillo>


boost::posix_time::ptime start;
boost::posix_time::ptime end;
boost::posix_time::time_duration dt;

int array_sizes = 0;
template <class RES,class LEFT,class RIGHT>
void BasicTest_2 (RES *a, LEFT* b, RIGHT*c, const char * text) {
	start = boost::posix_time::microsec_clock::universal_time();

	for(int loop=0;loop<REPEATES;loop++)
	{
		for(int x=0;x<array_sizes; x++)
		{
			a[x] = b[x]*c[x];
		}
	}

	end       = boost::posix_time::microsec_clock::universal_time();
	dt = end - start;

	cout << dt << " Template " << text << endl;
}

template <class RES,class LEFT,class RIGHT>
void BasicTest (RES *a, LEFT* b, RIGHT*c, const char * text) {
	start = boost::posix_time::microsec_clock::universal_time();

	for(int loop=0;loop<REPEATES;loop++)
	{
		for(int x=0;x<ARRAY_SIZES; x++)
		{
			a[x] = b[x]*c[x];
		}
	}

	end       = boost::posix_time::microsec_clock::universal_time();
	dt = end - start;

	cout << dt << " Template " << text << endl;
}
template <class TYPE>
void ARMATEST(TYPE *a, TYPE*b, const char * text)
{
	bool copy_aux_mem = false; //Do not copy memory to an auxilery memory location.
	arma::Row<TYPE> left  = arma::Row<TYPE>(a, ARRAY_SIZES,copy_aux_mem);
	arma::Row<TYPE> right  = arma::Row<TYPE>(a, ARRAY_SIZES,copy_aux_mem);

	start = boost::posix_time::microsec_clock::universal_time();
	for(int loop=0;loop<REPEATES;loop++)
	{
		left = left % right;
	}
	end       = boost::posix_time::microsec_clock::universal_time();
	dt = end - start;

	cout << dt << " Template ARMA " << text << endl;
}

void int16_test()
{
	start = boost::posix_time::microsec_clock::universal_time();

		for(int loop=0;loop<REPEATES;loop++)
		{
			for(int x=0;x<ARRAY_SIZES; x++)
			{
				int16_g[x] = int16_g[x]*int16_g2[x];
			}
		}

		end       = boost::posix_time::microsec_clock::universal_time();
		dt = end - start;

		cout << dt << " Function int16_g,int16_g,int16_g" << endl;
}
void float_conversion_test()
{
	start = boost::posix_time::microsec_clock::universal_time();

		for(int loop=0;loop<REPEATES;loop++)
		{
			for(int x=0;x<ARRAY_SIZES; x++)
			{
				float_g[x] = float_g[x]*int8_g[x];
			}
		}

		end       = boost::posix_time::microsec_clock::universal_time();
		dt = end - start;

		cout << dt << " function float_g[x] = float_g[x]*int8_g[x];" << endl;
}

int main()
{




	array_sizes = ARRAY_SIZES;
	/* -------------------------------------- */
	cout <<" Time to taken to multiply arrays of length " << ARRAY_SIZES << " together " << REPEATES << " times" << endl;
	cout << "Order is RESULT, LEFT, RIGHT ==== RESULT = LEFT * RIGHT" << endl;
	cout << "HEAP TEST " << endl;

	BasicTest(int8_g,int8_g,int8_g2 ,"int8_g,int8_g,int8_g");
	BasicTest(int16_g,int16_g,int16_g2 ,"int16_g,int16_g,int16_g");
	int16_test();
	BasicTest(int32_g,int32_g,int32_g2 ,"int32_g,int32_g,int32_g");
	BasicTest(int64_g,int64_g,int64_g2 ,"int64_g,int64_g,int64_g");
	BasicTest(float_g,float_g,float_g2 ,"float_g,float_g,float_g ");
	BasicTest(double_g,double_g,double_g2 ,"double_g,double_g,double_g ");
	BasicTest(cx_int32_g,cx_int32_g,cx_int32_g2 ,"cx_int32_g,cx_int32_g,cx_int32_g2");
	BasicTest(cx_float_g,cx_float_g,cx_float_g2 ,"cx_float_g,cx_float_g,cx_float_g2");
	BasicTest(cx_double_g,cx_double_g,cx_double_g2 ,"cx_double_g,cx_double_g,cx_double_g2");

	/* -------------------------------------- */
	cout << "Conversions" << endl;

	BasicTest(int16_g,int16_g,int8_g ,"int16_g,int16_g,int8_g");
	BasicTest(int32_g,int32_g,int8_g ,"int32_g,int32_g,int8_g");
	BasicTest(int64_g,int64_g,int8_g ,"int64_g,int64_g,int8_g");
	BasicTest(int32_g,int32_g,int16_g ,"int32_g,int32_g,int16_g");
	BasicTest(int64_g,int64_g,int16_g ,"int64_g,int64_g,int16_g ");
	BasicTest(int64_g,int64_g,int32_g ,"int64_g,int64_g,int32_g ");

	BasicTest(float_g,float_g,int8_g ,"float_g,float_g,int8_g ");
	BasicTest(float_g,float_g,int16_g ,"float_g,float_g,int16_g ");
	float_conversion_test();
	BasicTest(float_g,float_g,int32_g ,"float_g,float_g,int32_g ");
	BasicTest(float_g,float_g,int64_g ,"float_g,float_g,int64_g ");

	BasicTest(double_g,double_g,int8_g ,"double_g,double_g,int8_g ");
	BasicTest(double_g,double_g,int16_g ,"double_g,double_g,int16_g ");
	BasicTest(double_g,double_g,int32_g ,"double_g,double_g,int32_g ");
	BasicTest(double_g,double_g,int64_g ,"double_g,double_g,int64_g ");
	BasicTest(double_g,double_g,float_g ,"double_g,double_g,float_g ");

	BasicTest(cx_float_g,cx_float_g,float_g ,"cx_float_g,cx_float_g,float_g");
	BasicTest(cx_double_g,cx_double_g,double_g ,"cx_double_g,cx_double_g,double_g");

	cout << "ARMADILLO" << endl;
//	ARMATEST(int8_g,int8_g2 ,"int8_g,int8_g,int8_g"); //Not supported
	ARMATEST(int16_g,int16_g2 ,"int16_g,int16_g,int16_g");
	ARMATEST(int32_g,int32_g2 ,"int32_g,int32_g,int32_g");
//	ARMATEST(int64_g,int64_g2 ,"int64_g,int64_g,int64_g"); //Not supported
	ARMATEST(float_g,float_g2 ,"float_g,float_g,float_g ");
	ARMATEST(double_g,double_g2 ,"double_g,double_g,double_g ");
	ARMATEST(cx_float_g,cx_float_g2 ,"cx_float_g,cx_float_g2 ");
	ARMATEST(cx_double_g,cx_double_g ,"cx_double_g,cx_float_g2 ");

//	cout << "STACK TEST " << endl;
//	/*! Setup arrays that are done from stack memory*/
//	int8_t  int8_s[ARRAY_SIZES];
//	int8_t  int8_s2[ARRAY_SIZES];
//
//	int16_t int16_s[ARRAY_SIZES];
//	int16_t int16_s2[ARRAY_SIZES];
//
//	int32_t int32_s[ARRAY_SIZES];
//	int32_t int32_s2[ARRAY_SIZES];
//
//	int64_t int64_s[ARRAY_SIZES];
//	int64_t int64_s2[ARRAY_SIZES];
//
//	float   float_s[ARRAY_SIZES];
//	float   float_s2[ARRAY_SIZES];
//
//	double  double_s[ARRAY_SIZES];
//	double  double_s2[ARRAY_SIZES];
//	BasicTest(int8_s,int8_s,int8_s2 ,"int8_s,int8_s,int8_s");
//	BasicTest(int16_s,int16_s,int16_s2 ,"int16_s,int16_s,int16_s");
//	int16_test();
//	BasicTest(int32_s,int32_s,int32_s2 ,"int32_s,int32_s,int32_s");
//	BasicTest(int64_s,int64_s,int64_s2 ,"int64_s,int64_s,int64_s");
//	BasicTest(float_s,float_s,float_s2 ,"float_s,float_s,float_s ");
//	BasicTest(double_s,double_s,double_s2 ,"double_s,double_s,double_s ");
//	/* -------------------------------------- */
//	cout << "Conversions" << endl;
//
//	BasicTest(int16_s,int16_s,int8_s ,"int16_s,int16_s,int8_s");
//	BasicTest(int32_s,int32_s,int8_s ,"int32_s,int32_s,int8_s");
//	BasicTest(int64_s,int64_s,int8_s ,"int64_s,int64_s,int8_s");
//	BasicTest(int32_s,int32_s,int16_s ,"int32_s,int32_s,int16_s");
//	BasicTest(int64_s,int64_s,int16_s ,"int64_s,int64_s,int16_s ");
//	BasicTest(int64_s,int64_s,int32_s ,"int64_s,int64_s,int32_s ");
//
//	BasicTest(float_s,float_s,int8_s ,"float_s,float_s,int8_s ");
//	BasicTest(float_s,float_s,int16_s ,"float_s,float_s,int16_s ");
//	float_conversion_test();
//	BasicTest(float_s,float_s,int32_s ,"float_s,float_s,int32_s ");
//	BasicTest(float_s,float_s,int64_s ,"float_s,float_s,int64_s ");
//
//	BasicTest(double_s,double_s,int8_s ,"double_s,double_s,int8_s ");
//	BasicTest(double_s,double_s,int16_s ,"double_s,double_s,int16_s ");
//	BasicTest(double_s,double_s,int32_s ,"double_s,double_s,int32_s ");
//	BasicTest(double_s,double_s,int64_s ,"double_s,double_s,int64_s ");
//	BasicTest(double_s,double_s,float_s ,"double_s,double_s,float_s ");

//cout <<"Variable for loop" << endl;
//
//BasicTest_2(int8_g,int8_g,int8_g2 ,"int8_g,int8_g,int8_g");
//BasicTest_2(int16_g,int16_g,int16_g2 ,"int16_g,int16_g,int16_g");
//
//BasicTest_2(int32_g,int32_g,int32_g2 ,"int32_g,int32_g,int32_g");
//BasicTest_2(int64_g,int64_g,int64_g2 ,"int64_g,int64_g,int64_g");
//BasicTest_2(float_g,float_g,float_g2 ,"float_g,float_g,float_g ");
//BasicTest_2(double_g,double_g,double_g2 ,"double_g,double_g,double_g ");
//BasicTest_2(cx_int32_g,cx_int32_g,cx_int32_g2 ,"cx_int32_g,cx_int32_g,cx_int32_g2");
//BasicTest_2(cx_float_g,cx_float_g,cx_float_g2 ,"cx_float_g,cx_float_g,cx_float_g2");
//BasicTest_2(cx_double_g,cx_double_g,cx_double_g2 ,"cx_double_g,cx_double_g,cx_double_g2");
//
///* -------------------------------------- */
//cout << "   Conversions" << endl;
//
//BasicTest_2(int16_g,int16_g,int8_g ,"int16_g,int16_g,int8_g");
//BasicTest_2(int32_g,int32_g,int8_g ,"int32_g,int32_g,int8_g");
//BasicTest_2(int64_g,int64_g,int8_g ,"int64_g,int64_g,int8_g");
//BasicTest_2(int32_g,int32_g,int16_g ,"int32_g,int32_g,int16_g");
//BasicTest_2(int64_g,int64_g,int16_g ,"int64_g,int64_g,int16_g ");
//BasicTest_2(int64_g,int64_g,int32_g ,"int64_g,int64_g,int32_g ");
//
//BasicTest_2(float_g,float_g,int8_g ,"float_g,float_g,int8_g ");
//BasicTest_2(float_g,float_g,int16_g ,"float_g,float_g,int16_g ");
//
//BasicTest_2(float_g,float_g,int32_g ,"float_g,float_g,int32_g ");
//BasicTest_2(float_g,float_g,int64_g ,"float_g,float_g,int64_g ");
//
//BasicTest_2(double_g,double_g,int8_g ,"double_g,double_g,int8_g ");
//BasicTest_2(double_g,double_g,int16_g ,"double_g,double_g,int16_g ");
//BasicTest_2(double_g,double_g,int32_g ,"double_g,double_g,int32_g ");
//BasicTest_2(double_g,double_g,int64_g ,"double_g,double_g,int64_g ");
//BasicTest_2(double_g,double_g,float_g ,"double_g,double_g,float_g ");
//
//BasicTest_2(cx_float_g,cx_float_g,float_g ,"cx_float_g,cx_float_g,float_g");
//BasicTest_2(cx_double_g,cx_double_g,double_g ,"cx_double_g,cx_double_g,double_g");
}
