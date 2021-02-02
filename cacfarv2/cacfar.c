/*
 * File: cacfar.c
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
#include "sum.h"
#include "abs.h"
#include "fftshift.h"
#include "fft.h"
#include "blackman.h"

#include <Windows.h>

/* Function Definitions */

/*
 * range fft processing
 * Arguments    : double c
 *                double T
 *                double B
 *                double L
 *                double N
 *                double Npad
 *                double Lpad
 *                const creal_T sigReceive[524288]
 *                emxArray_real_T *Range_Dopple_Map
 *                emxArray_real_T *CFAR_Map
 *                emxArray_real_T *CFAR_MapRange_Dim
 *                emxArray_real_T *CFAR_MapVelocity_Dim
 *                emxArray_real_T *CRange_Dopple_Map
 * Return Type  : void
 */
void cacfar(double c, double T, double B, double L, double N, double Npad,
	double Lpad, const creal_T sigReceive[524288], emxArray_real_T
	* Range_Dopple_Map, emxArray_real_T* CFAR_Map, emxArray_real_T
	* CFAR_MapRange_Dim, emxArray_real_T* CFAR_MapVelocity_Dim,
	emxArray_real_T* CRange_Dopple_Map, LONGLONG* ll)
{
	LARGE_INTEGER li[2];

	QueryPerformanceCounter(&li[0]);

	emxArray_real_T* hanning1;
	emxArray_creal_T* sigRWin;
	int i0;
	int i1;
	int i2;
	int loop_ub;
	emxArray_int32_T* i;
	emxArray_real_T* b_hanning1;
	int ii;
	emxArray_real_T* sigRfft_tmp;
	double a;
	int jj;
	emxArray_creal_T* sigRfft;
	creal_T c_hanning1[2048];
	emxArray_creal_T* b_sigRWin;
	emxArray_creal_T* r0;
	emxArray_creal_T* sigDWin;
	emxArray_creal_T* r1;
	emxArray_creal_T* b_sigDWin;
	emxArray_real_T* Range_Dim;
	double b_a;
	emxArray_real_T* Velocity_Dim;
	int i3;
	int nx;
	int i4;
	int idx;
	int b_loop_ub;
	double b_sigRfft_tmp[25];
	double dv0[5];
	emxArray_boolean_T* x;
	emxArray_int32_T* j;
	boolean_T exitg1;
	boolean_T guard1 = false;
	emxInit_real_T(&hanning1, 1);
	emxInit_creal_T(&sigRWin, 2);
	blackman(N, hanning1);

	/* sigRWin = zeros(L,N); */
	i0 = sigRWin->size[0] * sigRWin->size[1];
	i1 = (int)L;
	sigRWin->size[0] = i1;
	i2 = (int)N;
	sigRWin->size[1] = i2;
	emxEnsureCapacity_creal_T(sigRWin, i0);
	loop_ub = i1 * i2;
	for (i0 = 0; i0 < loop_ub; i0++) {
		sigRWin->data[i0].re = 0.0;
		sigRWin->data[i0].im = 0.0;
	}

	emxInit_int32_T(&i, 1);
	emxInit_real_T(&b_hanning1, 2);
	for (ii = 0; ii < i1; ii++) {
		loop_ub = sigRWin->size[1];
		i0 = i->size[0];
		i->size[0] = loop_ub;
		emxEnsureCapacity_int32_T(i, i0);
		for (i0 = 0; i0 < loop_ub; i0++) {
			i->data[i0] = i0;
		}

		i0 = b_hanning1->size[0] * b_hanning1->size[1];
		b_hanning1->size[0] = 1;
		b_hanning1->size[1] = hanning1->size[0];
		emxEnsureCapacity_real_T(b_hanning1, i0);
		loop_ub = hanning1->size[0];
		for (i0 = 0; i0 < loop_ub; i0++) {
			b_hanning1->data[i0] = hanning1->data[i0];
		}

		for (i0 = 0; i0 < 2048; i0++) {
			c_hanning1[i0].re = b_hanning1->data[i0] * sigReceive[ii + (i0 << 8)].re;
			c_hanning1[i0].im = b_hanning1->data[i0] * sigReceive[ii + (i0 << 8)].im;
		}

		jj = i->size[0];
		for (i0 = 0; i0 < jj; i0++) {
			sigRWin->data[ii + sigRWin->size[0] * i->data[i0]] = c_hanning1[i0];
		}

		/*  " .* "即矩阵对应元素相乘，两个矩阵必须满足规格相同。A.'是对矩阵A一般转置，A’是共轭转置，即对矩阵中每个元素先求共轭再转置，因为这是实数矩阵所以二者结果一致 */
	}

	emxInit_real_T(&sigRfft_tmp, 2);

	/* sigRfft = zeros(L,N*Npad); */
	i0 = sigRfft_tmp->size[0] * sigRfft_tmp->size[1];
	sigRfft_tmp->size[0] = i1;
	a = N * Npad;
	i2 = (int)a;
	sigRfft_tmp->size[1] = i2;
	emxEnsureCapacity_real_T(sigRfft_tmp, i0);
	jj = i1 * i2;
	for (i0 = 0; i0 < jj; i0++) {
		sigRfft_tmp->data[i0] = 0.0;
	}

	emxInit_creal_T(&sigRfft, 2);
	i0 = sigRfft->size[0] * sigRfft->size[1];
	sigRfft->size[0] = sigRfft_tmp->size[0];
	sigRfft->size[1] = sigRfft_tmp->size[1];
	emxEnsureCapacity_creal_T(sigRfft, i0);
	loop_ub = sigRfft_tmp->size[0] * sigRfft_tmp->size[1];
	for (i0 = 0; i0 < loop_ub; i0++) {
		sigRfft->data[i0].re = sigRfft_tmp->data[i0];
		sigRfft->data[i0].im = 0.0;
	}

	emxInit_creal_T(&b_sigRWin, 2);
	emxInit_creal_T(&r0, 2);
	for (ii = 0; ii < i1; ii++) {
		loop_ub = sigRWin->size[1];
		i0 = b_sigRWin->size[0] * b_sigRWin->size[1];
		b_sigRWin->size[0] = 1;
		b_sigRWin->size[1] = loop_ub;
		emxEnsureCapacity_creal_T(b_sigRWin, i0);
		for (i0 = 0; i0 < loop_ub; i0++) {
			b_sigRWin->data[i0] = sigRWin->data[ii + sigRWin->size[0] * i0];
		}

		fft(b_sigRWin, a, r0);
		loop_ub = r0->size[1];
		for (i0 = 0; i0 < loop_ub; i0++) {
			sigRfft->data[ii + sigRfft->size[0] * i0] = r0->data[i0];
		}
	}

	emxFree_creal_T(&r0);
	emxFree_creal_T(&b_sigRWin);

	QueryPerformanceCounter(&li[1]);
	ll[0] += (li[1].QuadPart - li[0].QuadPart);

	/*  doppler fft processing */
	QueryPerformanceCounter(&li[0]);
	blackman(L, hanning1);

	/* sigDWin = zeros(L,N*Npad); */
	i0 = sigRfft_tmp->size[0] * sigRfft_tmp->size[1];
	sigRfft_tmp->size[0] = i1;
	sigRfft_tmp->size[1] = i2;
	emxEnsureCapacity_real_T(sigRfft_tmp, i0);
	for (i0 = 0; i0 < jj; i0++) {
		sigRfft_tmp->data[i0] = 0.0;
	}

	emxInit_creal_T(&sigDWin, 2);
	i0 = sigDWin->size[0] * sigDWin->size[1];
	sigDWin->size[0] = sigRfft_tmp->size[0];
	sigDWin->size[1] = sigRfft_tmp->size[1];
	emxEnsureCapacity_creal_T(sigDWin, i0);
	loop_ub = sigRfft_tmp->size[0] * sigRfft_tmp->size[1];
	for (i0 = 0; i0 < loop_ub; i0++) {
		sigDWin->data[i0].re = sigRfft_tmp->data[i0];
		sigDWin->data[i0].im = 0.0;
	}

	for (ii = 0; ii < i2; ii++) {
		loop_ub = hanning1->size[0];
		for (i0 = 0; i0 < loop_ub; i0++) {
			sigDWin->data[i0 + sigDWin->size[0] * ii].re = hanning1->data[i0] *
				sigRfft->data[i0 + sigRfft->size[0] * ii].re;
			sigDWin->data[i0 + sigDWin->size[0] * ii].im = hanning1->data[i0] *
				sigRfft->data[i0 + sigRfft->size[0] * ii].im;
		}
	}

	emxFree_creal_T(&sigRfft);

	/* sigDfft = zeros(L*Lpad,N*Npad); */
	i0 = sigRfft_tmp->size[0] * sigRfft_tmp->size[1];
	a = L * Lpad;
	i1 = (int)a;
	sigRfft_tmp->size[0] = i1;
	sigRfft_tmp->size[1] = i2;
	emxEnsureCapacity_real_T(sigRfft_tmp, i0);
	loop_ub = i1 * i2;
	for (i0 = 0; i0 < loop_ub; i0++) {
		sigRfft_tmp->data[i0] = 0.0;
	}

	i0 = sigRWin->size[0] * sigRWin->size[1];
	sigRWin->size[0] = sigRfft_tmp->size[0];
	sigRWin->size[1] = sigRfft_tmp->size[1];
	emxEnsureCapacity_creal_T(sigRWin, i0);
	loop_ub = sigRfft_tmp->size[0] * sigRfft_tmp->size[1];
	for (i0 = 0; i0 < loop_ub; i0++) {
		sigRWin->data[i0].re = sigRfft_tmp->data[i0];
		sigRWin->data[i0].im = 0.0;
	}

	emxInit_creal_T(&r1, 1);
	emxInit_creal_T(&b_sigDWin, 1);
	for (ii = 0; ii < i2; ii++) {
		loop_ub = sigDWin->size[0];
		i0 = b_sigDWin->size[0];
		b_sigDWin->size[0] = loop_ub;
		emxEnsureCapacity_creal_T(b_sigDWin, i0);
		for (i0 = 0; i0 < loop_ub; i0++) {
			b_sigDWin->data[i0] = sigDWin->data[i0 + sigDWin->size[0] * ii];
		}

		b_fft(b_sigDWin, a, r1);
		fftshift(r1);
		loop_ub = r1->size[0];
		for (i0 = 0; i0 < loop_ub; i0++) {
			sigRWin->data[i0 + sigRWin->size[0] * ii] = r1->data[i0];
		}
	}

	emxFree_creal_T(&b_sigDWin);
	emxFree_creal_T(&r1);
	emxFree_creal_T(&sigDWin);
	emxInit_real_T(&Range_Dim, 2);

	QueryPerformanceCounter(&li[1]);
	ll[1] += (li[1].QuadPart - li[0].QuadPart);

	/* Rres = c/(2*B*Npad); */
	/* Vres = c/(2*24.25*10^9*T*L*Lpad); */
	/*  2D CA-CFAR */
	QueryPerformanceCounter(&li[0]);
	/* 要求的恒虚警率 */
	a = c / (2.0 * B);

	/* 距离维精度 */
	b_a = c / (4.85E+10 * T * L);

	/* 多普勒维（速度）精度 */
	if (N < 1.0) {
		Range_Dim->size[0] = 1;
		Range_Dim->size[1] = 0;
	}
	else if (rtIsInf(N) && (1.0 == N)) {
		i0 = Range_Dim->size[0] * Range_Dim->size[1];
		Range_Dim->size[0] = 1;
		Range_Dim->size[1] = 1;
		emxEnsureCapacity_real_T(Range_Dim, i0);
		Range_Dim->data[0] = rtNaN;
	}
	else {
		i0 = Range_Dim->size[0] * Range_Dim->size[1];
		Range_Dim->size[0] = 1;
		loop_ub = (int)floor(N - 1.0);
		Range_Dim->size[1] = loop_ub + 1;
		emxEnsureCapacity_real_T(Range_Dim, i0);
		for (i0 = 0; i0 <= loop_ub; i0++) {
			Range_Dim->data[i0] = 1.0 + (double)i0;
		}
	}

	i0 = Range_Dim->size[0] * Range_Dim->size[1];
	i1 = Range_Dim->size[0] * Range_Dim->size[1];
	Range_Dim->size[0] = 1;
	emxEnsureCapacity_real_T(Range_Dim, i1);
	loop_ub = i0 - 1;
	for (i0 = 0; i0 <= loop_ub; i0++) {
		Range_Dim->data[i0] *= a;
	}

	emxInit_real_T(&Velocity_Dim, 2);

	/* 实际距离坐标 */
	if (L < 1.0) {
		Velocity_Dim->size[0] = 1;
		Velocity_Dim->size[1] = 0;
	}
	else if (rtIsInf(L) && (1.0 == L)) {
		i0 = Velocity_Dim->size[0] * Velocity_Dim->size[1];
		Velocity_Dim->size[0] = 1;
		Velocity_Dim->size[1] = 1;
		emxEnsureCapacity_real_T(Velocity_Dim, i0);
		Velocity_Dim->data[0] = rtNaN;
	}
	else {
		i0 = Velocity_Dim->size[0] * Velocity_Dim->size[1];
		Velocity_Dim->size[0] = 1;
		loop_ub = (int)floor(L - 1.0);
		Velocity_Dim->size[1] = loop_ub + 1;
		emxEnsureCapacity_real_T(Velocity_Dim, i0);
		for (i0 = 0; i0 <= loop_ub; i0++) {
			Velocity_Dim->data[i0] = 1.0 + (double)i0;
		}
	}

	i0 = Velocity_Dim->size[0] * Velocity_Dim->size[1];
	i1 = Velocity_Dim->size[0] * Velocity_Dim->size[1];
	Velocity_Dim->size[0] = 1;
	emxEnsureCapacity_real_T(Velocity_Dim, i1);
	a = L / 2.0;
	loop_ub = i0 - 1;
	for (i0 = 0; i0 <= loop_ub; i0++) {
		Velocity_Dim->data[i0] = b_a * (Velocity_Dim->data[i0] - a);
	}

	/* 实际多普勒维（速度）坐标 */
	b_abs(sigRWin, Range_Dopple_Map);

	/* RDM（数值是两次fft后信号的幅值，信号是复数，所以也就是绝对值） */
	/* 窗口大小9*9 */
	/* handleWindow = zeros(handleWindow_r,handleWindow_c); */
	/* 保护窗口大小5*5 */
	/* proCell = zeros(proCell_r,proCell_c); */
	/* 提取RDM的行数和列数，这里其实还是刚开始设定的信号的矩阵大小 */
	/* RDM经过CFAR滑窗处理后的点阵的行数，也就相当于裁掉了边 */
	/* RDM经过CFAR滑窗处理后的点阵的列数(=一行的点数) */
	/* 2D-CFAR检测判决门限 */
	i0 = Range_Dopple_Map->size[0];
	i1 = CFAR_Map->size[0] * CFAR_Map->size[1];
	CFAR_Map->size[0] = Range_Dopple_Map->size[0] - 8;
	CFAR_Map->size[1] = Range_Dopple_Map->size[1] - 8;
	emxEnsureCapacity_real_T(CFAR_Map, i1);
	emxFree_creal_T(&sigRWin);
	for (jj = 0; jj <= i0 - 9; jj++) {
		i1 = Range_Dopple_Map->size[1];
		if (0 <= i1 - 9) {
			i3 = (int)(jj + 9U);
			if (1 + jj > i3) {
				i2 = 1;
				i3 = 0;
			}
			else {
				i2 = jj + 1;
			}

			i4 = i2 - 1;
		}

		for (nx = 0; nx <= i1 - 9; nx++) {
			i2 = (int)(nx + 9U);
			if (1 + nx > i2) {
				idx = 1;
				i2 = 0;
			}
			else {
				idx = nx + 1;
			}

			ii = sigRfft_tmp->size[0] * sigRfft_tmp->size[1];
			loop_ub = i3 - i4;
			sigRfft_tmp->size[0] = loop_ub;
			b_loop_ub = (i2 - idx) + 1;
			sigRfft_tmp->size[1] = b_loop_ub;
			emxEnsureCapacity_real_T(sigRfft_tmp, ii);
			for (i2 = 0; i2 < b_loop_ub; i2++) {
				for (ii = 0; ii < loop_ub; ii++) {
					sigRfft_tmp->data[ii + sigRfft_tmp->size[0] * i2] =
						Range_Dopple_Map->data[(i4 + ii) + Range_Dopple_Map->size[0] * ((idx
							+ i2) - 1)];
				}
			}

			/* 处理窗口内的数据是根据位置对应关系从RDM中抠的数据 */
			/* 保护窗口内的数据是根据位置对应关系从上一行得到的处理窗口中抠的数据 */
			/* 参考窗均值 */
			sum(sigRfft_tmp, b_hanning1);
			for (i2 = 0; i2 < 5; i2++) {
				for (idx = 0; idx < 5; idx++) {
					b_sigRfft_tmp[idx + 5 * i2] = sigRfft_tmp->data[(idx +
						sigRfft_tmp->size[0] * (2 + i2)) + 2];
				}
			}

			c_sum(b_sigRfft_tmp, dv0);
			CFAR_Map->data[jj + CFAR_Map->size[0] * nx] = 15.668923983885406 * ((b_sum
			(b_hanning1) -d_sum(dv0)) / 56.0);

			/* 门限值 */
		}
	}

	emxFree_real_T(&b_hanning1);
	emxFree_real_T(&sigRfft_tmp);
	if (5.0 > (N - 5.0) + 1.0) {
		i0 = 0;
		i1 = 0;
	}
	else {
		i0 = 4;
		i1 = (int)((N - 5.0) + 1.0);
	}

	i2 = CFAR_MapRange_Dim->size[0] * CFAR_MapRange_Dim->size[1];
	CFAR_MapRange_Dim->size[0] = 1;
	loop_ub = i1 - i0;
	CFAR_MapRange_Dim->size[1] = loop_ub;
	emxEnsureCapacity_real_T(CFAR_MapRange_Dim, i2);
	for (i1 = 0; i1 < loop_ub; i1++) {
		CFAR_MapRange_Dim->data[i1] = Range_Dim->data[i0 + i1];
	}

	emxFree_real_T(&Range_Dim);

	/* CFAR后距离维的点对应的实际距离值（因为滑窗损失的几个点，所以不是从0开始了） */
	if (5.0 > (L - 5.0) + 1.0) {
		i0 = 0;
		i1 = 0;
	}
	else {
		i0 = 4;
		i1 = (int)((L - 5.0) + 1.0);
	}

	i2 = CFAR_MapVelocity_Dim->size[0] * CFAR_MapVelocity_Dim->size[1];
	CFAR_MapVelocity_Dim->size[0] = 1;
	loop_ub = i1 - i0;
	CFAR_MapVelocity_Dim->size[1] = loop_ub;
	emxEnsureCapacity_real_T(CFAR_MapVelocity_Dim, i2);
	for (i1 = 0; i1 < loop_ub; i1++) {
		CFAR_MapVelocity_Dim->data[i1] = Velocity_Dim->data[i0 + i1];
	}

	emxFree_real_T(&Velocity_Dim);
	if (5.0 > (L - 5.0) + 1.0) {
		i0 = 0;
		i1 = 0;
	}
	else {
		i0 = 4;
		i1 = (int)((L - 5.0) + 1.0);
	}

	if (5.0 > (N - 5.0) + 1.0) {
		i2 = 0;
		i3 = 0;
	}
	else {
		i2 = 4;
		i3 = (int)((N - 5.0) + 1.0);
	}

	i4 = CRange_Dopple_Map->size[0] * CRange_Dopple_Map->size[1];
	loop_ub = i1 - i0;
	CRange_Dopple_Map->size[0] = loop_ub;
	b_loop_ub = i3 - i2;
	CRange_Dopple_Map->size[1] = b_loop_ub;
	emxEnsureCapacity_real_T(CRange_Dopple_Map, i4);
	for (i1 = 0; i1 < b_loop_ub; i1++) {
		for (i3 = 0; i3 < loop_ub; i3++) {
			CRange_Dopple_Map->data[i3 + CRange_Dopple_Map->size[0] * i1] =
				Range_Dopple_Map->data[(i0 + i3) + Range_Dopple_Map->size[0] * (i2 + i1)];
		}
	}

	emxInit_boolean_T(&x, 2);
	i0 = x->size[0] * x->size[1];
	x->size[0] = CRange_Dopple_Map->size[0];
	x->size[1] = CRange_Dopple_Map->size[1];
	emxEnsureCapacity_boolean_T(x, i0);
	loop_ub = CRange_Dopple_Map->size[0] * CRange_Dopple_Map->size[1];
	for (i0 = 0; i0 < loop_ub; i0++) {
		x->data[i0] = (CRange_Dopple_Map->data[i0] < CFAR_Map->data[i0]);
	}

	nx = x->size[0] * x->size[1];
	emxInit_int32_T(&j, 1);
	if (nx == 0) {
		i->size[0] = 0;
		j->size[0] = 0;
	}
	else {
		idx = 0;
		i0 = i->size[0];
		i->size[0] = nx;
		emxEnsureCapacity_int32_T(i, i0);
		i0 = j->size[0];
		j->size[0] = nx;
		emxEnsureCapacity_int32_T(j, i0);
		ii = 1;
		jj = 1;
		exitg1 = false;
		while ((!exitg1) && (jj <= x->size[1])) {
			guard1 = false;
			if (x->data[(ii + x->size[0] * (jj - 1)) - 1]) {
				idx++;
				i->data[idx - 1] = ii;
				j->data[idx - 1] = jj;
				if (idx >= nx) {
					exitg1 = true;
				}
				else {
					guard1 = true;
				}
			}
			else {
				guard1 = true;
			}

			if (guard1) {
				ii++;
				if (ii > x->size[0]) {
					ii = 1;
					jj++;
				}
			}
		}

		if (nx == 1) {
			if (idx == 0) {
				i->size[0] = 0;
				j->size[0] = 0;
			}
		}
		else if (1 > idx) {
			i->size[0] = 0;
			j->size[0] = 0;
		}
		else {
			i0 = i->size[0];
			i->size[0] = idx;
			emxEnsureCapacity_int32_T(i, i0);
			i0 = j->size[0];
			j->size[0] = idx;
			emxEnsureCapacity_int32_T(j, i0);
		}
	}

	emxFree_boolean_T(&x);
	i0 = hanning1->size[0];
	hanning1->size[0] = i->size[0];
	emxEnsureCapacity_real_T(hanning1, i0);
	loop_ub = i->size[0];
	for (i0 = 0; i0 < loop_ub; i0++) {
		hanning1->data[i0] = i->data[i0];
	}

	emxFree_int32_T(&i);
	i0 = hanning1->size[0];
	for (jj = 0; jj < i0; jj++) {
		CRange_Dopple_Map->data[((int)hanning1->data[jj] + CRange_Dopple_Map->size[0]
			* (j->data[jj] - 1)) - 1] = 0.0;
	}

	emxFree_int32_T(&j);
	emxFree_real_T(&hanning1);

	QueryPerformanceCounter(&li[1]);
	ll[2] += (li[1].QuadPart - li[0].QuadPart);
}

/*
 * File trailer for cacfar.c
 *
 * [EOF]
 */
