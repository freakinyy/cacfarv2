/*
 * File: eml_rand_mt19937ar_stateful.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 02-Feb-2021 15:41:50
 */

/* Include Files */
#include <string.h>
#include "rt_nonfinite.h"
#include "cacfar.h"
#include "gensig.h"
#include "eml_rand_mt19937ar_stateful.h"
#include "cacfar_data.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void c_eml_rand_mt19937ar_stateful_i(void)
{
  unsigned int r;
  int mti;
  memset(&state[0], 0, 625U * sizeof(unsigned int));
  r = 5489U;
  state[0] = 5489U;
  for (mti = 0; mti < 623; mti++) {
    r = ((r ^ r >> 30U) * 1812433253U + mti) + 1U;
    state[mti + 1] = r;
  }

  state[624] = 624U;
}

/*
 * File trailer for eml_rand_mt19937ar_stateful.c
 *
 * [EOF]
 */
