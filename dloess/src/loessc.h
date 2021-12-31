#ifndef DLOESS_LOESSC_H_
#define DLOESS_LOESSC_H_

#include "loess.h"

#define GAUSSIAN    1
#define SYMMETRIC   0

void
loess_raw(double *y, double *x, double *weights, double *robust, int32_t *d,
          int32_t *n, double *span, int32_t *degree, int32_t *nonparametric,
          int32_t *drop_square, int32_t *sum_drop_sqr, double *cell,
          char **surf_stat, double *surface, int32_t *parameter, int32_t *a,
          double *xi, double *vert, double *vval, double *diagonal, double *trL,
          double *one_delta, double *two_delta, int32_t *setLf);

void
loess_dfit(double *y, double *x, double *x_evaluate, double *weights,
           double *span, int32_t *degree, int32_t *nonparametric,
           int32_t *drop_square, int32_t *sum_drop_sqr, int32_t *d, int32_t *n,
           int32_t *m, double *fit);

void
loess_dfitse(double *y, double *x, double *x_evaluate, double *weights,
             double *robust, int32_t *family, double *span, int32_t *degree,
             int32_t *nonparametric, int32_t *drop_square,
             int32_t *sum_drop_sqr, int32_t *d, int32_t *n, int32_t *m,
             double *fit, double *L);

void
loess_ifit(int32_t *parameter, int32_t *a, double *xi, double *vert,
           double *vval, int32_t *m, double *x_evaluate, double *fit);

void
loess_ise(double *y, double *x, double *x_evaluate, double *weights,
          double *span, int32_t *degree, int32_t *nonparametric,
          int32_t *drop_square, int32_t *sum_drop_sqr, double *cell, int32_t *d,
          int32_t *n, int32_t *m, double *fit, double *L);

void
loess_workspace(int32_t *d, int32_t *n, double *span, int32_t *degree,
                int32_t *nonparametric, int32_t *drop_square,
                int32_t *sum_drop_sqr, int32_t *setLf);

void
loess_prune(int32_t *parameter, int32_t *a, double *xi, double *vert,
            double *vval);

void
loess_grow(int32_t *parameter, int32_t *a, double *xi, double *vert,
           double *vval);

void
loess_free();

void F77_SUB(ehg182)(int *i);

void F77_SUB(ehg183)(char *s, int *i, int *n, int *inc);

void F77_SUB(ehg184)(char *s, double *x, int *n, int *inc);

#endif // __DLOESS_LOESSC_H__
