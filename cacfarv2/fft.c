/*
 * File: fft.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 02-Feb-2021 15:41:50
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "cacfar.h"
#include "gensig.h"
#include "fft.h"
#include "cacfar_emxutil.h"
#include "fft1.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_creal_T *x
 *                double varargin_1
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void b_fft(const emxArray_creal_T *x, double varargin_1, emxArray_creal_T *y)
{
  emxArray_real_T *costab;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  boolean_T guard1 = false;
  int i11;
  boolean_T useRadix2;
  int N2blue;
  int nRows;
  emxInit_real_T(&costab, 2);
  emxInit_real_T(&sintab, 2);
  emxInit_real_T(&sintabinv, 2);
  guard1 = false;
  if (x->size[0] == 0) {
    guard1 = true;
  } else {
    i11 = (int)varargin_1;
    if (i11 == 0) {
      guard1 = true;
    } else {
      useRadix2 = ((i11 > 0) && ((i11 & (i11 - 1)) == 0));
      get_algo_sizes((int)varargin_1, useRadix2, &N2blue, &nRows);
      generate_twiddle_tables(nRows, useRadix2, costab, sintab, sintabinv);
      if (useRadix2) {
        r2br_r2dit_trig_impl(x, i11, costab, sintab, y);
      } else {
        dobluesteinfft(x, N2blue, i11, costab, sintab, sintabinv, y);
      }
    }
  }

  if (guard1) {
    i11 = y->size[0];
    y->size[0] = (int)varargin_1;
    emxEnsureCapacity_creal_T(y, i11);
    if ((int)varargin_1 > x->size[0]) {
      N2blue = y->size[0];
      i11 = y->size[0];
      y->size[0] = N2blue;
      emxEnsureCapacity_creal_T(y, i11);
      for (i11 = 0; i11 < N2blue; i11++) {
        y->data[i11].re = 0.0;
        y->data[i11].im = 0.0;
      }
    }
  }

  emxFree_real_T(&sintabinv);
  emxFree_real_T(&sintab);
  emxFree_real_T(&costab);
}

/*
 * Arguments    : const emxArray_creal_T *x
 *                double varargin_1
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void fft(const emxArray_creal_T *x, double varargin_1, emxArray_creal_T *y)
{
  emxArray_creal_T *b_y1;
  emxArray_real_T *costab;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  boolean_T guard1 = false;
  int i9;
  boolean_T useRadix2;
  int N2blue;
  int nRows;
  emxArray_creal_T b_x;
  int c_x[1];
  int d_x[1];
  emxInit_creal_T(&b_y1, 1);
  emxInit_real_T(&costab, 2);
  emxInit_real_T(&sintab, 2);
  emxInit_real_T(&sintabinv, 2);
  guard1 = false;
  if (x->size[1] == 0) {
    guard1 = true;
  } else {
    i9 = (int)varargin_1;
    if (i9 == 0) {
      guard1 = true;
    } else {
      useRadix2 = ((i9 > 0) && ((i9 & (i9 - 1)) == 0));
      get_algo_sizes((int)varargin_1, useRadix2, &N2blue, &nRows);
      generate_twiddle_tables(nRows, useRadix2, costab, sintab, sintabinv);
      if (useRadix2) {
        nRows = x->size[1];
        b_x = *x;
        d_x[0] = nRows;
        b_x.size = &d_x[0];
        b_x.numDimensions = 1;
        r2br_r2dit_trig_impl(&b_x, i9, costab, sintab, b_y1);
      } else {
        nRows = x->size[1];
        b_x = *x;
        c_x[0] = nRows;
        b_x.size = &c_x[0];
        b_x.numDimensions = 1;
        dobluesteinfft(&b_x, N2blue, i9, costab, sintab, sintabinv, b_y1);
      }
    }
  }

  if (guard1) {
    i9 = b_y1->size[0];
    b_y1->size[0] = (int)varargin_1;
    emxEnsureCapacity_creal_T(b_y1, i9);
    if ((int)varargin_1 > x->size[1]) {
      nRows = b_y1->size[0];
      i9 = b_y1->size[0];
      b_y1->size[0] = nRows;
      emxEnsureCapacity_creal_T(b_y1, i9);
      for (i9 = 0; i9 < nRows; i9++) {
        b_y1->data[i9].re = 0.0;
        b_y1->data[i9].im = 0.0;
      }
    }
  }

  emxFree_real_T(&sintabinv);
  emxFree_real_T(&sintab);
  emxFree_real_T(&costab);
  i9 = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = (int)varargin_1;
  emxEnsureCapacity_creal_T(y, i9);
  nRows = (int)varargin_1;
  for (i9 = 0; i9 < nRows; i9++) {
    y->data[i9] = b_y1->data[i9];
  }

  emxFree_creal_T(&b_y1);
}

/*
 * File trailer for fft.c
 *
 * [EOF]
 */
