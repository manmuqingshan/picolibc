/* sf_log1p.c -- float version of s_log1p.c.
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
#include "math_config.h"

static const float
ln2_hi =   6.9313812256e-01,	/* 0x3f317180 */
ln2_lo =   9.0580006145e-06,	/* 0x3717f7d1 */
Lp1 = 6.6666668653e-01,	/* 3F2AAAAB */
Lp2 = 4.0000000596e-01,	/* 3ECCCCCD */
Lp3 = 2.8571429849e-01, /* 3E924925 */
Lp4 = 2.2222198546e-01, /* 3E638E29 */
Lp5 = 1.8183572590e-01, /* 3E3A3325 */
Lp6 = 1.5313838422e-01, /* 3E1CD04F */
Lp7 = 1.4798198640e-01; /* 3E178897 */

static const float zero = 0.0;

float
log1pf(float x)
{
	float hfsq,f,c=0,s,z,R,u;
	__int32_t k,hx,hu,ax;

	GET_FLOAT_WORD(hx,x);
	ax = hx&0x7fffffff;

	k = 1;
	if (!FLT_UWORD_IS_FINITE(hx)) return x+x;
	if (hx < 0x3ed413d7) {			/* x < 0.41422  */
	    if(ax>=0x3f800000) {		/* x <= -1.0 */
		if(x==(float)-1.0)
		    return __math_divzerof (1); /* log1p(-1)=-inf */
		else
		    return __math_invalidf (x);	/* log1p(x<-1)=NaN */
	    }
	    if(ax<0x39000000) {			/* |x| < 2**-13 */
		if(ax<0x32800000) 		/* |x| < 2**-26 */
		    return __math_inexactf(x);
		else
		    return __math_inexactf(x - x*x*(float)0.5);
	    }
	    if(hx>0||hx<=((__int32_t)0xbe95f61f)) {
		k=0;f=x;hu=1;}	/* -0.2929<x<0.41422 */
	}
	if(k!=0) {
	    if(hx<0x5a000000) {
		u  = (float)1.0+x; 
		GET_FLOAT_WORD(hu,u);
	        k  = (hu>>23)-127;
		/* correction term */
	        c  = (k>0)? (float)1.0-(u-x):x-(u-(float)1.0);
		c /= u;
	    } else {
		u  = x;
		GET_FLOAT_WORD(hu,u);
	        k  = (hu>>23)-127;
		c  = 0;
	    }
	    hu &= 0x007fffff;
	    if(hu<0x3504f7) {
	        SET_FLOAT_WORD(u,hu|0x3f800000);/* normalize u */
	    } else {
	        k += 1; 
		SET_FLOAT_WORD(u,hu|0x3f000000);	/* normalize u/2 */
	        hu = (0x00800000-hu)>>2;
	    }
	    f = u-(float)1.0;
	}
	hfsq=(float)0.5*f*f;
	if(hu==0) {	/* |f| < 2**-20 */
           if(f==zero) { if(k==0) return zero;  
                       else {c += k*ln2_lo; return k*ln2_hi+c;}}
	    R = hfsq*((float)1.0-(float)0.66666666666666666*f);
	    if(k==0) return f-R; else
	    	     return k*ln2_hi-((R-(k*ln2_lo+c))-f);
	}
 	s = f/((float)2.0+f); 
	z = s*s;
	R = z*(Lp1+z*(Lp2+z*(Lp3+z*(Lp4+z*(Lp5+z*(Lp6+z*Lp7))))));
	if(k==0) return f-(hfsq-s*(hfsq+R)); else
		 return k*ln2_hi-((hfsq-(s*(hfsq+R)+(k*ln2_lo+c)))-f);
}

_MATH_ALIAS_f_f(log1p)
