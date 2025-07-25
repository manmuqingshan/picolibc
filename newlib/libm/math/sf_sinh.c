/* ef_sinh.c -- float version of e_sinh.c.
 * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
 */

/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

#include "fdlibm.h"

static const float one = 1.0;

float
sinhf(float x)
{
    float t, w, h;
    __int32_t ix, jx;

    GET_FLOAT_WORD(jx, x);
    ix = jx & 0x7fffffff;

    /* x is INF or NaN */
    if (!FLT_UWORD_IS_FINITE(ix))
        return x + x;

    h = 0.5;
    if (jx < 0)
        h = -h;
    /* |x| in [0,22], return sign(x)*0.5*(E+E/(E+1))) */
    if (ix < 0x41b00000) { /* |x|<22 */
        if (ix < 0x31800000) /* |x|<2**-28 */
            return __math_inexactf(x); /* sinh(tiny) = tiny with inexact */
        t = expm1f(fabsf(x));
        if (ix < 0x3f800000)
            return h * ((float)2.0 * t - t * t / (t + one));
        return h * (t + t / (t + one));
    }

    /* |x| in [22, log(maxdouble)] return 0.5*exp(|x|) */
    if (ix <= FLT_UWORD_LOG_MAX)
        return h * expf(fabsf(x));

    /* |x| in [log(maxdouble), overflowthresold] */
    if (ix <= FLT_UWORD_LOG_2MAX) {
        w = expf((float)0.5 * fabsf(x));
        t = h * w;
        return t * w;
    }

    /* |x| > overflowthresold, sinh(x) overflow */
    return __math_oflowf(x < 0);
}

_MATH_ALIAS_f_f(sinh)
