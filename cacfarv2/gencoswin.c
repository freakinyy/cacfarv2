/*
 * File: gencoswin.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 02-Feb-2021 15:41:50
 */

/* Include Files */
#include <math.h>
#include "rt_nonfinite.h"
#include "cacfar.h"
#include "gensig.h"
#include "gencoswin.h"
#include "cacfar_emxutil.h"
#include "cos.h"

/* Function Definitions */

/*
 * Arguments    : double m
 *                double n
 *                emxArray_real_T *w
 * Return Type  : void
 */
void calc_window(double m, double n, emxArray_real_T *w)
{
  emxArray_real_T *y;
  int i8;
  int loop_ub;
  emxArray_real_T *x;
  emxInit_real_T(&y, 2);
  if (rtIsNaN(m - 1.0)) {
    i8 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 1;
    emxEnsureCapacity_real_T(y, i8);
    y->data[0] = rtNaN;
  } else if (m - 1.0 < 0.0) {
    y->size[0] = 1;
    y->size[1] = 0;
  } else if (rtIsInf(m - 1.0) && (0.0 == m - 1.0)) {
    i8 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 1;
    emxEnsureCapacity_real_T(y, i8);
    y->data[0] = rtNaN;
  } else {
    i8 = y->size[0] * y->size[1];
    y->size[0] = 1;
    loop_ub = (int)floor(m - 1.0);
    y->size[1] = loop_ub + 1;
    emxEnsureCapacity_real_T(y, i8);
    for (i8 = 0; i8 <= loop_ub; i8++) {
      y->data[i8] = i8;
    }
  }

  emxInit_real_T(&x, 1);
  i8 = x->size[0];
  x->size[0] = y->size[1];
  emxEnsureCapacity_real_T(x, i8);
  loop_ub = y->size[1];
  for (i8 = 0; i8 < loop_ub; i8++) {
    x->data[i8] = y->data[i8] / (n - 1.0);
  }

  emxFree_real_T(&y);
  i8 = w->size[0];
  w->size[0] = x->size[0];
  emxEnsureCapacity_real_T(w, i8);
  loop_ub = x->size[0];
  for (i8 = 0; i8 < loop_ub; i8++) {
    w->data[i8] = 6.2831853071795862 * x->data[i8];
  }

  b_cos(w);
  i8 = x->size[0];
  emxEnsureCapacity_real_T(x, i8);
  loop_ub = x->size[0];
  for (i8 = 0; i8 < loop_ub; i8++) {
    x->data[i8] *= 12.566370614359172;
  }

  b_cos(x);
  i8 = w->size[0];
  emxEnsureCapacity_real_T(w, i8);
  loop_ub = w->size[0];
  for (i8 = 0; i8 < loop_ub; i8++) {
    w->data[i8] = (0.42 - 0.5 * w->data[i8]) + 0.08 * x->data[i8];
  }

  emxFree_real_T(&x);
  w->data[0] = 0.0;
}

/*
 * File trailer for gencoswin.c
 *
 * [EOF]
 */
