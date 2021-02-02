/*
 * File: cacfar.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 02-Feb-2021 15:41:50
 */

#ifndef CACFAR_H
#define CACFAR_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "cacfar_types.h"

#include <Windows.h>

/* Function Declarations */
extern void cacfar(double c, double T, double B, double L, double N, double Npad,
                   double Lpad, const creal_T sigReceive[524288],
                   emxArray_real_T *Range_Dopple_Map, emxArray_real_T *CFAR_Map,
                   emxArray_real_T *CFAR_MapRange_Dim, emxArray_real_T
                   *CFAR_MapVelocity_Dim, emxArray_real_T *CRange_Dopple_Map, LONGLONG* ll);

#endif

/*
 * File trailer for cacfar.h
 *
 * [EOF]
 */
