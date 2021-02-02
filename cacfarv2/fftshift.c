/*
 * File: fftshift.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 02-Feb-2021 15:41:50
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "cacfar.h"
#include "gensig.h"
#include "fftshift.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_creal_T *x
 * Return Type  : void
 */
void fftshift(emxArray_creal_T *x)
{
  int i2;
  int vlend2;
  int vspread;
  int i;
  int i1;
  int j;
  int ia;
  int ib;
  double xtmp_re;
  int k;
  double xtmp_im;
  int ic;
  i2 = x->size[0];
  if (i2 > 1) {
    vlend2 = i2 / 2;
    vspread = i2 - 1;
    if (vlend2 << 1 == i2) {
      i2 = 0;
      for (i = 0; i < 1; i++) {
        i1 = i2 - 1;
        i2 += vspread;
        for (j = 0; j < 1; j++) {
          i1++;
          i2++;
          ia = i1;
          ib = i1 + vlend2;
          for (k = 0; k < vlend2; k++) {
            xtmp_re = x->data[ia].re;
            xtmp_im = x->data[ia].im;
            x->data[ia] = x->data[ib];
            x->data[ib].re = xtmp_re;
            x->data[ib].im = xtmp_im;
            ia++;
            ib++;
          }
        }
      }
    } else {
      i2 = 0;
      for (i = 0; i < 1; i++) {
        i1 = i2;
        i2 += vspread;
        for (j = 0; j < 1; j++) {
          i1++;
          i2++;
          ia = i1 - 1;
          ib = i1 + vlend2;
          xtmp_re = x->data[ib - 1].re;
          xtmp_im = x->data[ib - 1].im;
          for (k = 0; k < vlend2; k++) {
            ic = ib + 1;
            x->data[ib - 1] = x->data[ia];
            x->data[ia] = x->data[ic - 1];
            ia++;
            ib = ic;
          }

          x->data[ib - 1].re = xtmp_re;
          x->data[ib - 1].im = xtmp_im;
        }
      }
    }
  }
}

/*
 * File trailer for fftshift.c
 *
 * [EOF]
 */
