/*
 * File: gensig.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 02-Feb-2021 15:41:50
 */

/* Include Files */
#include <math.h>
#include "rt_nonfinite.h"
#include "cacfar.h"
#include "gensig.h"
#include "cacfar_emxutil.h"
#include "awgn.h"

/* Function Definitions */

/*
 * Arguments    : double c
 *                double f0
 *                double T
 *                double B
 *                double L
 *                double N
 *                emxArray_creal_T *sigReceive
 * Return Type  : void
 */
void gensig(double c, double f0, double T, double B, double L, double N,
            emxArray_creal_T *sigReceive)
{
  int l;
  int i12;
  int i13;
  int loop_ub_tmp;
  emxArray_creal_T *b_sigReceive;
  int n;
  double y_im;
  double y_re;
  double r;
  emxArray_creal_T *S2;

  /* target range */
  /* target velocity */
  /*  generate receive signal */
  /* S1 = zeros(L,N); */
  l = sigReceive->size[0] * sigReceive->size[1];
  i12 = (int)L;
  sigReceive->size[0] = i12;
  i13 = (int)N;
  sigReceive->size[1] = i13;
  emxEnsureCapacity_creal_T(sigReceive, l);
  loop_ub_tmp = i12 * i13;
  for (l = 0; l < loop_ub_tmp; l++) {
    sigReceive->data[l].re = 0.0;
    sigReceive->data[l].im = 0.0;
  }

  for (l = 0; l < i12; l++) {
    for (n = 0; n < i13; n++) {
      y_im = 15.0 + -3.0 * T * (1.0 + (double)l);
      y_im = (2.0 * B * y_im / (c * T) + 2.0 * f0 * -3.0 / c) * T / N * (1.0 +
        (double)n) + 2.0 * f0 * y_im / c;
      y_re = y_im * 0.0;
      y_im *= 6.2831853071795862;
      if (y_im == 0.0) {
        y_re = exp(y_re);
        y_im = 0.0;
      } else {
        r = exp(y_re / 2.0);
        y_re = r * (r * cos(y_im));
        y_im = r * (r * sin(y_im));
      }

      sigReceive->data[l + sigReceive->size[0] * n].re = 500.0 * y_re;
      sigReceive->data[l + sigReceive->size[0] * n].im = 500.0 * y_im;
    }
  }

  emxInit_creal_T(&b_sigReceive, 2);
  l = b_sigReceive->size[0] * b_sigReceive->size[1];
  b_sigReceive->size[0] = sigReceive->size[0];
  b_sigReceive->size[1] = sigReceive->size[1];
  emxEnsureCapacity_creal_T(b_sigReceive, l);
  n = sigReceive->size[0] * sigReceive->size[1];
  for (l = 0; l < n; l++) {
    b_sigReceive->data[l] = sigReceive->data[l];
  }

  emxInit_creal_T(&S2, 2);
  awgn(b_sigReceive, sigReceive);

  /* S2 = zeros(L,N); */
  l = S2->size[0] * S2->size[1];
  S2->size[0] = i12;
  S2->size[1] = i13;
  emxEnsureCapacity_creal_T(S2, l);
  for (l = 0; l < loop_ub_tmp; l++) {
    S2->data[l].re = 0.0;
    S2->data[l].im = 0.0;
  }

  for (l = 0; l < i12; l++) {
    for (n = 0; n < i13; n++) {
      y_im = 25.0 + 10.0 * T * (1.0 + (double)l);
      y_im = (2.0 * B * y_im / (c * T) + 2.0 * f0 * 10.0 / c) * T / N * (1.0 +
        (double)n) + 2.0 * f0 * y_im / c;
      y_re = y_im * 0.0;
      y_im *= 6.2831853071795862;
      if (y_im == 0.0) {
        y_re = exp(y_re);
        y_im = 0.0;
      } else {
        r = exp(y_re / 2.0);
        y_re = r * (r * cos(y_im));
        y_im = r * (r * sin(y_im));
      }

      S2->data[l + S2->size[0] * n].re = 500.0 * y_re;
      S2->data[l + S2->size[0] * n].im = 500.0 * y_im;
    }
  }

  l = b_sigReceive->size[0] * b_sigReceive->size[1];
  b_sigReceive->size[0] = S2->size[0];
  b_sigReceive->size[1] = S2->size[1];
  emxEnsureCapacity_creal_T(b_sigReceive, l);
  n = S2->size[0] * S2->size[1];
  for (l = 0; l < n; l++) {
    b_sigReceive->data[l] = S2->data[l];
  }

  awgn(b_sigReceive, S2);
  l = sigReceive->size[0] * sigReceive->size[1];
  i12 = sigReceive->size[0] * sigReceive->size[1];
  emxEnsureCapacity_creal_T(sigReceive, i12);
  n = l - 1;
  emxFree_creal_T(&b_sigReceive);
  for (l = 0; l <= n; l++) {
    sigReceive->data[l].re += S2->data[l].re;
    sigReceive->data[l].im += S2->data[l].im;
  }

  emxFree_creal_T(&S2);
}

/*
 * File trailer for gensig.c
 *
 * [EOF]
 */
