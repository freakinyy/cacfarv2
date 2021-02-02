/*
 * File: abs.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 02-Feb-2021 15:41:50
 */

/* Include Files */
#include <math.h>
#include "rt_nonfinite.h"
#include "cacfar.h"
#include "gensig.h"
#include "abs.h"
#include "cacfar_emxutil.h"

/* Function Declarations */
static double rt_hypotd_snf(double u0, double u1);

/* Function Definitions */

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_hypotd_snf(double u0, double u1)
{
  double y;
  double a;
  double b;
  a = fabs(u0);
  b = fabs(u1);
  if (a < b) {
    a /= b;
    y = b * sqrt(a * a + 1.0);
  } else if (a > b) {
    b /= a;
    y = a * sqrt(b * b + 1.0);
  } else if (rtIsNaN(b)) {
    y = b;
  } else {
    y = a * 1.4142135623730951;
  }

  return y;
}

/*
 * Arguments    : const emxArray_creal_T *x
 *                emxArray_real_T *y
 * Return Type  : void
 */
void b_abs(const emxArray_creal_T *x, emxArray_real_T *y)
{
  int nx;
  unsigned int unnamed_idx_0;
  unsigned int unnamed_idx_1;
  int k;
  nx = x->size[0] * x->size[1];
  unnamed_idx_0 = (unsigned int)x->size[0];
  unnamed_idx_1 = (unsigned int)x->size[1];
  k = y->size[0] * y->size[1];
  y->size[0] = (int)unnamed_idx_0;
  y->size[1] = (int)unnamed_idx_1;
  emxEnsureCapacity_real_T(y, k);
  for (k = 0; k < nx; k++) {
    y->data[k] = rt_hypotd_snf(x->data[k].re, x->data[k].im);
  }
}

/*
 * File trailer for abs.c
 *
 * [EOF]
 */
