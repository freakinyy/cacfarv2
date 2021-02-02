/*
 * File: cacfar_initialize.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 02-Feb-2021 15:41:50
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "cacfar.h"
#include "gensig.h"
#include "cacfar_initialize.h"
#include "eml_rand_mt19937ar_stateful.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void cacfar_initialize(void)
{
  rt_InitInfAndNaN(8U);
  c_eml_rand_mt19937ar_stateful_i();
}

/*
 * File trailer for cacfar_initialize.c
 *
 * [EOF]
 */
