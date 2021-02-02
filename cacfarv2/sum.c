/*
 * File: sum.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 02-Feb-2021 15:41:50
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "cacfar.h"
#include "gensig.h"
#include "sum.h"
#include "cacfar_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 * Return Type  : double
 */
double b_sum(const emxArray_real_T *x)
{
  double y;
  int vlen;
  int k;
  vlen = x->size[1];
  if (x->size[1] == 0) {
    y = 0.0;
  } else {
    y = x->data[0];
    for (k = 2; k <= vlen; k++) {
      y += x->data[k - 1];
    }
  }

  return y;
}

/*
 * Arguments    : const double x[25]
 *                double y[5]
 * Return Type  : void
 */
void c_sum(const double x[25], double y[5])
{
  int i;
  int xpageoffset;
  for (i = 0; i < 5; i++) {
    xpageoffset = i * 5;
    y[i] = x[xpageoffset];
    y[i] += x[xpageoffset + 1];
    y[i] += x[xpageoffset + 2];
    y[i] += x[xpageoffset + 3];
    y[i] += x[xpageoffset + 4];
  }
}

/*
 * Arguments    : const double x[5]
 * Return Type  : double
 */
double d_sum(const double x[5])
{
  return (((x[0] + x[1]) + x[2]) + x[3]) + x[4];
}

/*
 * Arguments    : const emxArray_real_T *x
 *                emxArray_real_T *y
 * Return Type  : void
 */
void sum(const emxArray_real_T *x, emxArray_real_T *y)
{
  int vlen;
  int npages;
  unsigned int sz_idx_1;
  int xpageoffset;
  int i;
  int k;
  vlen = x->size[0];
  if ((x->size[0] == 0) || (x->size[1] == 0)) {
    sz_idx_1 = (unsigned int)x->size[1];
    xpageoffset = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = (int)sz_idx_1;
    emxEnsureCapacity_real_T(y, xpageoffset);
    i = (int)sz_idx_1;
    for (xpageoffset = 0; xpageoffset < i; xpageoffset++) {
      y->data[xpageoffset] = 0.0;
    }
  } else {
    npages = x->size[1];
    xpageoffset = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = x->size[1];
    emxEnsureCapacity_real_T(y, xpageoffset);
    for (i = 0; i < npages; i++) {
      xpageoffset = i * x->size[0];
      y->data[i] = x->data[xpageoffset];
      for (k = 2; k <= vlen; k++) {
        y->data[i] += x->data[(xpageoffset + k) - 1];
      }
    }
  }
}

/*
 * File trailer for sum.c
 *
 * [EOF]
 */
