/*
 * File: main.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 02-Feb-2021 15:41:50
 */

 /*************************************************************************/
 /* This automatically generated example C main file shows how to call    */
 /* entry-point functions that MATLAB Coder generated. You must customize */
 /* this file for your application. Do not modify this file directly.     */
 /* Instead, make a copy of this file, modify it, and integrate it into   */
 /* your development environment.                                         */
 /*                                                                       */
 /* This file initializes entry-point function arguments to a default     */
 /* size and value before calling the entry-point functions. It does      */
 /* not store or use any values returned from the entry-point functions.  */
 /* If necessary, it does pre-allocate memory for returned values.        */
 /* You can use this file as a starting point for a main function that    */
 /* you can deploy in your application.                                   */
 /*                                                                       */
 /* After you copy the file, and before you deploy it, you must make the  */
 /* following changes:                                                    */
 /* * For variable-size function arguments, change the example sizes to   */
 /* the sizes that your application requires.                             */
 /* * Change the example values of function arguments to the values that  */
 /* your application requires.                                            */
 /* * If the entry-point functions return values, store these values or   */
 /* otherwise use them as required by your application.                   */
 /*                                                                       */
 /*************************************************************************/
 /* Include Files */
#include "rt_nonfinite.h"
#include "cacfar.h"
#include "gensig.h"
#include "main.h"
#include "cacfar_terminate.h"
#include "cacfar_emxAPI.h"
#include "cacfar_initialize.h"

#include <Windows.h>
#include <stdio.h>

/* Function Declarations */
static void argInit_256x2048_creal_T(creal_T result[524288]);
static creal_T argInit_creal_T(void);
static double argInit_real_T(void);
static void main_cacfar(double c, double T, double B, double L, double N, double Npad,
	double Lpad, emxArray_creal_T* sigReceive, emxArray_real_T
	* Range_Dopple_Map, emxArray_real_T* CFAR_Map, emxArray_real_T
	* CFAR_MapRange_Dim, emxArray_real_T* CFAR_MapVelocity_Dim,
	emxArray_real_T* CRange_Dopple_Map,
	LONGLONG* ll);
static void main_gensig(double c, double f0, double T, double B, double L, double N, emxArray_creal_T* sigReceive);

/* Function Definitions */

/*
 * Arguments    : creal_T result[524288]
 * Return Type  : void
 */
static void argInit_256x2048_creal_T(creal_T result[524288])
{
	int idx0;
	int idx1;

	/* Loop over the array to initialize each element. */
	for (idx0 = 0; idx0 < 256; idx0++) {
		for (idx1 = 0; idx1 < 2048; idx1++) {
			/* Set the value of the array element.
			   Change this value to the value that the application requires. */
			result[idx0 + (idx1 << 8)] = argInit_creal_T();
		}
	}
}

/*
 * Arguments    : void
 * Return Type  : creal_T
 */
static creal_T argInit_creal_T(void)
{
	creal_T result;
	double result_tmp;

	/* Set the value of the complex variable.
	   Change this value to the value that the application requires. */
	result_tmp = argInit_real_T();
	result.re = result_tmp;
	result.im = result_tmp;
	return result;
}

/*
 * Arguments    : void
 * Return Type  : double
 */
static double argInit_real_T(void)
{
	return 0.0;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_cacfar(double c, double T, double B, double L, double N, double Npad,
	double Lpad, emxArray_creal_T* sigReceive, emxArray_real_T
	* Range_Dopple_Map, emxArray_real_T* CFAR_Map, emxArray_real_T
	* CFAR_MapRange_Dim, emxArray_real_T* CFAR_MapVelocity_Dim,
	emxArray_real_T* CRange_Dopple_Map,
	LONGLONG* ll)
{
	//emxArray_real_T* Range_Dopple_Map;
	//emxArray_real_T* CFAR_Map;
	//emxArray_real_T* CFAR_MapRange_Dim;
	//emxArray_real_T* CFAR_MapVelocity_Dim;
	//emxArray_real_T* CRange_Dopple_Map;
	////static creal_T dcv0[524288];
	//emxInitArray_real_T(&Range_Dopple_Map, 2);
	//emxInitArray_real_T(&CFAR_Map, 2);
	//emxInitArray_real_T(&CFAR_MapRange_Dim, 2);
	//emxInitArray_real_T(&CFAR_MapVelocity_Dim, 2);
	//emxInitArray_real_T(&CRange_Dopple_Map, 2);

	/* Initialize function 'cacfar' input arguments. */
	/* Initialize function input argument 'sigReceive'. */
	/* Call the entry-point 'cacfar'. */
	//argInit_256x2048_creal_T(dcv0);
	creal_T* sigReceive0 = sigReceive->data;
	cacfar(c, T, B, L, N, Npad, Lpad, sigReceive0, Range_Dopple_Map, CFAR_Map, CFAR_MapRange_Dim, CFAR_MapVelocity_Dim, CRange_Dopple_Map, ll);
	//emxDestroyArray_real_T(CRange_Dopple_Map);
	//emxDestroyArray_real_T(CFAR_MapVelocity_Dim);
	//emxDestroyArray_real_T(CFAR_MapRange_Dim);
	//emxDestroyArray_real_T(CFAR_Map);
	//emxDestroyArray_real_T(Range_Dopple_Map);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_gensig(double c, double f0, double T, double B, double L, double N, emxArray_creal_T* sigReceive)
{
	//emxArray_creal_T* sigReceive;
	//emxInitArray_creal_T(&sigReceive, 2);

	/* Initialize function 'gensig' input arguments. */
	/* Call the entry-point 'gensig'. */
	gensig(c, f0, T, B, L, N, sigReceive);
	//emxDestroyArray_creal_T(sigReceive);
}

/*
 * Arguments    : int argc
 *                const char * const argv[]
 * Return Type  : int
 */
int main(int argc, const char* const argv[])
{
	(void)argc;
	(void)argv;

	int runtimes = 256;
	int showdebug = 0;
	LARGE_INTEGER pf;
	QueryPerformanceFrequency(&pf);
	LONGLONG ll[3];
	ZeroMemory(ll, 3 * sizeof(LONGLONG));

	/* Initialize the application.
	   You do not need to do this more than one time. */
	cacfar_initialize();

	/* Invoke the entry-point functions.
	   You can call entry-point functions multiple times. */
	for (int ri = 0; ri != runtimes; ++ri)
	{
		printf("%d\n", ri);
		double c = 3e8;
		double f0 = 24.25e9;
		double T = 0.0002;
		double B = 400e6;
		double L = 256;
		double N = 2048;
		double Npad = 1;
		double Lpad = 1;
		emxArray_creal_T* sigReceive;
		emxArray_real_T* Range_Dopple_Map;
		emxArray_real_T* CFAR_Map;
		emxArray_real_T* CFAR_MapRange_Dim;
		emxArray_real_T* CFAR_MapVelocity_Dim;
		emxArray_real_T* CRange_Dopple_Map;
		emxInitArray_creal_T(&sigReceive, 2);
		emxInitArray_real_T(&Range_Dopple_Map, 2);
		emxInitArray_real_T(&CFAR_Map, 2);
		emxInitArray_real_T(&CFAR_MapRange_Dim, 2);
		emxInitArray_real_T(&CFAR_MapVelocity_Dim, 2);
		emxInitArray_real_T(&CRange_Dopple_Map, 2);

		main_gensig(c, f0, T, B, L, N, sigReceive);
		main_cacfar(c, T, B, L, N, Npad, Lpad, sigReceive, Range_Dopple_Map, CFAR_Map, CFAR_MapRange_Dim, CFAR_MapVelocity_Dim, CRange_Dopple_Map, ll);

		for (int i = 0; i != (L - 8) * (N - 8); ++i)
			if (CRange_Dopple_Map->data[i] != 0)
				if (showdebug != 0)
					printf("(%d, %d): %.5e\n", i / ((int)L - 8), i % ((int)L - 8), CRange_Dopple_Map->data[i]);
		if (showdebug != 0)
			printf("\n");

		emxDestroyArray_creal_T(sigReceive);
		emxDestroyArray_real_T(CRange_Dopple_Map);
		emxDestroyArray_real_T(CFAR_MapVelocity_Dim);
		emxDestroyArray_real_T(CFAR_MapRange_Dim);
		emxDestroyArray_real_T(CFAR_Map);
		emxDestroyArray_real_T(Range_Dopple_Map);
	}

	printf("%fe-3 s\n", (float)ll[0] * (float)1e3 / (float)pf.QuadPart / (float)runtimes);
	printf("%fe-3 s\n", (float)ll[1] * (float)1e3 / (float)pf.QuadPart / (float)runtimes);
	printf("%fe-3 s\n", (float)ll[2] * (float)1e3 / (float)pf.QuadPart / (float)runtimes);

	/* Terminate the application.
	   You do not need to do this more than one time. */
	cacfar_terminate();
	return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
