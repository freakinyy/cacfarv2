/*
 * File: awgn.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 02-Feb-2021 15:41:50
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "cacfar.h"
#include "gensig.h"
#include "awgn.h"
#include "cacfar_emxutil.h"
#include "randn.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_creal_T *varargin_1
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void awgn(const emxArray_creal_T *varargin_1, emxArray_creal_T *y)
{
  double b_varargin_1[2];
  emxArray_real_T *r2;
  emxArray_real_T *b;
  int i14;
  int loop_ub;
  double re;
  double im;
  b_varargin_1[0] = varargin_1->size[0];
  b_varargin_1[1] = varargin_1->size[1];
  emxInit_real_T(&r2, 2);
  randn(b_varargin_1, r2);
  b_varargin_1[0] = varargin_1->size[0];
  b_varargin_1[1] = varargin_1->size[1];
  emxInit_real_T(&b, 2);
  randn(b_varargin_1, b);
  i14 = y->size[0] * y->size[1];
  y->size[0] = varargin_1->size[0];
  y->size[1] = varargin_1->size[1];
  emxEnsureCapacity_creal_T(y, i14);
  loop_ub = varargin_1->size[0] * varargin_1->size[1];
  for (i14 = 0; i14 < loop_ub; i14++) {
    re = r2->data[i14] + 0.0 * b->data[i14];
    im = b->data[i14];
    y->data[i14].re = varargin_1->data[i14].re + 0.070710678118654752 * re;
    y->data[i14].im = varargin_1->data[i14].im + 0.070710678118654752 * im;
  }

  emxFree_real_T(&b);
  emxFree_real_T(&r2);
}

/*
 * File trailer for awgn.c
 *
 * [EOF]
 */
