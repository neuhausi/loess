#ifndef DLOESS_LOESSF_H_
#define DLOESS_LOESSF_H_

#include "loess.h"

void F77_SUB(lowesa)(double *trl, int32_t *n, int32_t *d, int32_t *tau,
                     int32_t *nsing, double *delta1, double *delta2);

void F77_SUB(lowesb)(double *xx, double *yy, double *ww, double *diagl,
                     int32_t *infl, int32_t *iv, void *liv, void *lv,
                     double *wv);

void F77_SUB(lowesc)(int32_t *n, double *l, double *ll, double *trl,
                     double *delta1, double *delta2);

void F77_SUB(lowesd)(int32_t *versio, int32_t *iv, int32_t *liv, int32_t *lv,
                     double *v, int32_t *d, int32_t *n, double *f,
                     int32_t *ideg, int32_t *nvmax, int32_t *setlf);

void F77_SUB(lowese)(int32_t *iv, void *liv, void *lv, double *wv, int32_t *m,
                     double *x, double *surface);

void F77_SUB(lowesf)(double *xx, double *yy, double *ww, int32_t *iv, void *liv,
                     void *lv, double *wv, int32_t *m, double *z, double *l,
                     int32_t *ihat, double *s);

void F77_SUB(lowesl)(int *iv, void *liv, void *lv, double *wv, int32_t *m,
                     double *z, double *l);

void F77_SUB(lowesp)(int32_t *n, double *y, double *yhat, double *pwgts,
                     double *rwgts, int32_t *pi, double *ytilde);

void F77_SUB(lowesw)(double *res, int32_t *n, double *rw,
                     int32_t *pi);

void F77_SUB(ehg169)(int32_t *d, int32_t *vc, int32_t *nc, int32_t *ncmax,
                     int32_t *nv, int32_t *nvmax, double *v, int32_t *a,
                     double *xi, int32_t *c, int32_t *hi, int32_t *lo);

void F77_SUB(ehg196)(int32_t *tau, int32_t *d, double *f, double *trl);

#endif // DLOESS_LOESSF_H_
