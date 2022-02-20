/**
 * \file signtest.c
 * \brief Test treatment of +/-0 and +/-180
 *
 * Copyright (c) Charles Karney (2022) <charles@karney.com> and licensed
 * under the MIT/X11 License.  For more information, see
 * https://geographiclib.sourceforge.io/
 **********************************************************************/

#define GEODESIC_TESTING 1
#include "geodesic.h"
#include <stdio.h>
#include <math.h>
#include <float.h>

typedef double T;

int equiv(T x, T y) {
  return (isnan(x) && isnan(y)) ||
    (x == y && signbit(x) == signbit(y));
}

// use "do { } while (false)" idiom so it can be punctuated like a statement.

#define check(expr, r) do {             \
    T s = (T)(r),  t = expr;            \
    if (!equiv(s, t)) {                 \
    printf("Line %d : %s != %s (%g)\n", \
           __LINE__, #expr, #r, t);     \
      ++n;                              \
    }                                   \
  } while (0)

#define checksincosd(x, s, c) do {            \
    T sx, cx;                                 \
    geod_sincosd(x, &sx, &cx);                \
    if (!equiv(s, sx)) {                      \
      printf("Line %d: sin(%g) != %g (%g)\n", \
             __LINE__, x, s, sx);             \
      ++n;                                    \
    }                                         \
    if (!equiv(c, cx)) {                      \
      printf("Line %d: cos(%g) != %g (%g)\n", \
             __LINE__, x, c, cx);             \
      ++n;                                    \
    }                                         \
  } while (0)

int main() {
  T inf = INFINITY,
    nan = NAN,
    eps = DBL_EPSILON;
  int n = 0;
  geod_Init();

  check( geod_AngRound(-eps/32), -eps/32);
  check( geod_AngRound(-eps/64), -0.0   );
  check( geod_AngRound(-  0.0 ), -0.0   );
  check( geod_AngRound(   0.0 ), +0.0   );
  check( geod_AngRound( eps/64), +0.0   );
  check( geod_AngRound( eps/32), +eps/32);
  check( geod_AngRound((1-2*eps)/64), (1-2*eps)/64);
  check( geod_AngRound((1-eps  )/64),  1.0     /64);
  check( geod_AngRound((1-eps/2)/64),  1.0     /64);
  check( geod_AngRound((1-eps/4)/64),  1.0     /64);
  check( geod_AngRound( 1.0     /64),  1.0     /64);
  check( geod_AngRound((1+eps/2)/64),  1.0     /64);
  check( geod_AngRound((1+eps  )/64),  1.0     /64);
  check( geod_AngRound((1+2*eps)/64), (1+2*eps)/64);
  check( geod_AngRound((1-eps  )/32), (1-eps  )/32);
  check( geod_AngRound((1-eps/2)/32),  1.0     /32);
  check( geod_AngRound((1-eps/4)/32),  1.0     /32);
  check( geod_AngRound( 1.0     /32),  1.0     /32);
  check( geod_AngRound((1+eps/2)/32),  1.0     /32);
  check( geod_AngRound((1+eps  )/32), (1+eps  )/32);
  check( geod_AngRound((1-eps  )/16), (1-eps  )/16);
  check( geod_AngRound((1-eps/2)/16), (1-eps/2)/16);
  check( geod_AngRound((1-eps/4)/16),  1.0     /16);
  check( geod_AngRound( 1.0     /16),  1.0     /16);
  check( geod_AngRound((1+eps/4)/16),  1.0     /16);
  check( geod_AngRound((1+eps/2)/16),  1.0     /16);
  check( geod_AngRound((1+eps  )/16), (1+eps  )/16);
  check( geod_AngRound((1-eps  )/ 8), (1-eps  )/ 8);
  check( geod_AngRound((1-eps/2)/ 8), (1-eps/2)/ 8);
  check( geod_AngRound((1-eps/4)/ 8),  1.0     / 8);
  check( geod_AngRound((1+eps/2)/ 8),  1.0     / 8);
  check( geod_AngRound((1+eps  )/ 8), (1+eps  )/ 8);
  check( geod_AngRound( 1-eps      ),  1-eps      );
  check( geod_AngRound( 1-eps/2    ),  1-eps/2    );
  check( geod_AngRound( 1-eps/4    ),  1          );
  check( geod_AngRound( 1.0        ),  1          );
  check( geod_AngRound( 1+eps/4    ),  1          );
  check( geod_AngRound( 1+eps/2    ),  1          );
  check( geod_AngRound( 1+eps      ),  1+  eps    );
  check( geod_AngRound( 90.0-64*eps),  90-64*eps  );
  check( geod_AngRound( 90.0-32*eps),  90         );
  check( geod_AngRound( 90.0       ),  90         );

  checksincosd(-  inf,  nan,  nan);
  checksincosd(-810.0, -1.0, +0.0);
  checksincosd(-720.0, -0.0, +1.0);
  checksincosd(-630.0, +1.0, +0.0);
  checksincosd(-540.0, -0.0, -1.0);
  checksincosd(-450.0, -1.0, +0.0);
  checksincosd(-360.0, -0.0, +1.0);
  checksincosd(-270.0, +1.0, +0.0);
  checksincosd(-180.0, -0.0, -1.0);
  checksincosd(- 90.0, -1.0, +0.0);
  checksincosd(-  0.0, -0.0, +1.0);
  checksincosd(+  0.0, +0.0, +1.0);
  checksincosd(+ 90.0, +1.0, +0.0);
  checksincosd(+180.0, +0.0, -1.0);
  checksincosd(+270.0, -1.0, +0.0);
  checksincosd(+360.0, +0.0, +1.0);
  checksincosd(+450.0, +1.0, +0.0);
  checksincosd(+540.0, +0.0, -1.0);
  checksincosd(+630.0, -1.0, +0.0);
  checksincosd(+720.0, +0.0, +1.0);
  checksincosd(+810.0, +1.0, +0.0);
  checksincosd(+  inf,  nan,  nan);
  checksincosd(   nan,  nan,  nan);

  check( geod_atan2d(+0.0 , -0.0 ), +180 );
  check( geod_atan2d(-0.0 , -0.0 ), -180 );
  check( geod_atan2d(+0.0 , +0.0 ), +0.0 );
  check( geod_atan2d(-0.0 , +0.0 ), -0.0 );
  check( geod_atan2d(+0.0 , -1.0 ), +180 );
  check( geod_atan2d(-0.0 , -1.0 ), -180 );
  check( geod_atan2d(+0.0 , +1.0 ), +0.0 );
  check( geod_atan2d(-0.0 , +1.0 ), -0.0 );
  check( geod_atan2d(-1.0 , +0.0 ),  -90 );
  check( geod_atan2d(-1.0 , -0.0 ),  -90 );
  check( geod_atan2d(+1.0 , +0.0 ),  +90 );
  check( geod_atan2d(+1.0 , -0.0 ),  +90 );
  check( geod_atan2d(+1.0 ,  -inf), +180 );
  check( geod_atan2d(-1.0 ,  -inf), -180 );
  check( geod_atan2d(+1.0 ,  +inf), +0.0 );
  check( geod_atan2d(-1.0 ,  +inf), -0.0 );
  check( geod_atan2d( +inf, +1.0 ),  +90 );
  check( geod_atan2d( +inf, -1.0 ),  +90 );
  check( geod_atan2d( -inf, +1.0 ),  -90 );
  check( geod_atan2d( -inf, -1.0 ),  -90 );
  check( geod_atan2d( +inf,  -inf), +135 );
  check( geod_atan2d( -inf,  -inf), -135 );
  check( geod_atan2d( +inf,  +inf),  +45 );
  check( geod_atan2d( -inf,  +inf),  -45 );
  check( geod_atan2d(  nan, +1.0 ),  nan );
  check( geod_atan2d(+1.0 ,   nan),  nan );

  double e;
  check( geod_sum(+9.0, -9.0, &e), +0.0 );
  check( geod_sum(-9.0, +9.0, &e), +0.0 );
  check( geod_sum(-0.0, +0.0, &e), +0.0 );
  check( geod_sum(+0.0, -0.0, &e), +0.0 );
  check( geod_sum(-0.0, -0.0, &e), -0.0 );
  check( geod_sum(+0.0, +0.0, &e), +0.0 );

  check( geod_AngNormalize(-900.0), -180 );
  check( geod_AngNormalize(-720.0), -0.0 );
  check( geod_AngNormalize(-540.0), -180 );
  check( geod_AngNormalize(-360.0), -0.0 );
  check( geod_AngNormalize(-180.0), -180 );
  check( geod_AngNormalize(  -0.0), -0.0 );
  check( geod_AngNormalize(  +0.0), +0.0 );
  check( geod_AngNormalize( 180.0), +180 );
  check( geod_AngNormalize( 360.0), +0.0 );
  check( geod_AngNormalize( 540.0), +180 );
  check( geod_AngNormalize( 720.0), +0.0 );
  check( geod_AngNormalize( 900.0), +180 );

  check( geod_AngDiff(+  0.0, +  0.0, &e), +0.0 );
  check( geod_AngDiff(+  0.0, -  0.0, &e), -0.0 );
  check( geod_AngDiff(-  0.0, +  0.0, &e), +0.0 );
  check( geod_AngDiff(-  0.0, -  0.0, &e), +0.0 );
  check( geod_AngDiff(+  5.0, +365.0, &e), +0.0 );
  check( geod_AngDiff(+365.0, +  5.0, &e), -0.0 );
  check( geod_AngDiff(+  5.0, +185.0, &e), +180.0 );
  check( geod_AngDiff(+185.0, +  5.0, &e), -180.0 );
  check( geod_AngDiff( +eps , +180.0, &e), +180.0 );
  check( geod_AngDiff( -eps , +180.0, &e), -180.0 );
  check( geod_AngDiff( +eps , -180.0, &e), +180.0 );
  check( geod_AngDiff( -eps , -180.0, &e), -180.0 );

  if (n) {
    printf("%d %s%s\n", n, "failure", (n > 1 ? "s" : ""));
    return 1;
  }
}
