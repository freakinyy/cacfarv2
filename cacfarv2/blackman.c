/*
 * File: blackman.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 02-Feb-2021 15:41:50
 */

/* Include Files */
#include <float.h>
#include <math.h>
#include "rt_nonfinite.h"
#include "cacfar.h"
#include "gensig.h"
#include "blackman.h"
#include "cacfar_emxutil.h"
#include "gencoswin.h"

/* Function Declarations */
static int div_s32_floor(int numerator, int denominator);
static double rt_remd_snf(double u0, double u1);
static double rt_roundd_snf(double u);

/* Function Definitions */

/*
 * Arguments    : int numerator
 *                int denominator
 * Return Type  : int
 */
static int div_s32_floor(int numerator, int denominator)
{
  int quotient;
  unsigned int absNumerator;
  unsigned int absDenominator;
  boolean_T quotientNeedsNegation;
  unsigned int tempAbsQuotient;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }
  } else {
    if (numerator < 0) {
      absNumerator = ~(unsigned int)numerator + 1U;
    } else {
      absNumerator = (unsigned int)numerator;
    }

    if (denominator < 0) {
      absDenominator = ~(unsigned int)denominator + 1U;
    } else {
      absDenominator = (unsigned int)denominator;
    }

    quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
    tempAbsQuotient = absNumerator / absDenominator;
    if (quotientNeedsNegation) {
      absNumerator %= absDenominator;
      if (absNumerator > 0U) {
        tempAbsQuotient++;
      }

      quotient = -(int)tempAbsQuotient;
    } else {
      quotient = (int)tempAbsQuotient;
    }
  }

  return quotient;
}

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_remd_snf(double u0, double u1)
{
  double y;
  double q;
  if (rtIsNaN(u0) || rtIsInf(u0) || (rtIsNaN(u1) || rtIsInf(u1))) {
    y = rtNaN;
  } else if ((u1 != 0.0) && (u1 != trunc(u1))) {
    q = fabs(u0 / u1);
    if (fabs(q - floor(q + 0.5)) <= DBL_EPSILON * q) {
      y = 0.0 * u0;
    } else {
      y = fmod(u0, u1);
    }
  } else {
    y = fmod(u0, u1);
  }

  return y;
}

/*
 * Arguments    : double u
 * Return Type  : double
 */
static double rt_roundd_snf(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/*
 * Arguments    : double varargin_1
 *                emxArray_real_T *w
 * Return Type  : void
 */
void blackman(double varargin_1, emxArray_real_T *w)
{
  double n_out;
  emxArray_real_T *b_w;
  int i5;
  int i6;
  int i7;
  int loop_ub;
  int b_loop_ub;
  if (varargin_1 == floor(varargin_1)) {
    n_out = varargin_1;
  } else {
    n_out = rt_roundd_snf(varargin_1);
  }

  if (!(n_out < 0.0)) {
    if (n_out == 0.0) {
      w->size[0] = 0;
    } else if (n_out == 1.0) {
      i5 = w->size[0];
      w->size[0] = 1;
      emxEnsureCapacity_real_T(w, i5);
      w->data[0] = 1.0;
    } else {
      emxInit_real_T(&b_w, 1);
      if (!(rt_remd_snf(n_out + 1.0, 2.0) != 0.0)) {
        calc_window((n_out + 1.0) / 2.0, n_out + 1.0, w);
        if (2 > w->size[0]) {
          i5 = 1;
          i6 = 1;
          i7 = 0;
        } else {
          i5 = w->size[0];
          i6 = -1;
          i7 = 2;
        }

        loop_ub = b_w->size[0];
        b_loop_ub = div_s32_floor(i7 - i5, i6);
        b_w->size[0] = (w->size[0] + b_loop_ub) + 1;
        emxEnsureCapacity_real_T(b_w, loop_ub);
        loop_ub = w->size[0];
        for (i7 = 0; i7 < loop_ub; i7++) {
          b_w->data[i7] = w->data[i7];
        }

        for (i7 = 0; i7 <= b_loop_ub; i7++) {
          b_w->data[i7 + w->size[0]] = w->data[(i5 + i6 * i7) - 1];
        }

        i5 = w->size[0];
        w->size[0] = b_w->size[0];
        emxEnsureCapacity_real_T(w, i5);
        b_loop_ub = b_w->size[0];
        for (i5 = 0; i5 < b_loop_ub; i5++) {
          w->data[i5] = b_w->data[i5];
        }
      } else {
        calc_window(((n_out + 1.0) + 1.0) / 2.0, n_out + 1.0, w);
        if (2 > w->size[0] - 1) {
          i5 = 1;
          i6 = 1;
          i7 = 0;
        } else {
          i5 = w->size[0] - 1;
          i6 = -1;
          i7 = 2;
        }

        loop_ub = b_w->size[0];
        b_loop_ub = div_s32_floor(i7 - i5, i6);
        b_w->size[0] = (w->size[0] + b_loop_ub) + 1;
        emxEnsureCapacity_real_T(b_w, loop_ub);
        loop_ub = w->size[0];
        for (i7 = 0; i7 < loop_ub; i7++) {
          b_w->data[i7] = w->data[i7];
        }

        for (i7 = 0; i7 <= b_loop_ub; i7++) {
          b_w->data[i7 + w->size[0]] = w->data[(i5 + i6 * i7) - 1];
        }

        i5 = w->size[0];
        w->size[0] = b_w->size[0];
        emxEnsureCapacity_real_T(w, i5);
        b_loop_ub = b_w->size[0];
        for (i5 = 0; i5 < b_loop_ub; i5++) {
          w->data[i5] = b_w->data[i5];
        }
      }

      emxFree_real_T(&b_w);
    }
  }
}

/*
 * File trailer for blackman.c
 *
 * [EOF]
 */
