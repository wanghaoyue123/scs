#ifndef CONES_H_GUARD
#define CONES_H_GUARD

#ifdef __cplusplus
extern "C" {
#endif

#include "glbopts.h"
#include "scs.h"
#include "scs_blas.h"

/* private data to help cone projection step */
struct SCS_CONE_WORK {
/*
 * cone_boundaries will contain array of indices of rows of A corresponding to
 * cone boundaries, boundaries[0] is starting index for cones of size larger
 * than 1
 */
  scs_float *s; /* used for Moreau decomposition in projection */
  scs_int cone_len;
  /* box cone quantities */
  scs_float *bl, *bu, box_t_warm_start;
#ifdef USE_LAPACK
  /* workspace for eigenvector decompositions: */
  scs_float *Xs, *Z, *e, *work;
  blas_int *iwork, lwork, liwork;
#endif
};

ScsConeWork *SCS(init_cone)(const ScsCone *k, const ScsScaling *scal, scs_int cone_len);
char *SCS(get_cone_header)(const ScsCone *k);
scs_int SCS(validate_cones)(const ScsData *d, const ScsCone *k);
scs_int SCS(set_cone_boundaries)(const ScsCone *k, scs_int **cone_boundaries);

/* pass in iter to control how accurate the cone projection
 with iteration, set iter < 0 for exact projection, warm_start contains guess
 of solution, can be SCS_NULL*/
scs_int SCS(proj_dual_cone)(scs_float *x, const ScsCone *k, ScsConeWork *c,
                            const scs_float *warm_start, scs_int iter);
void SCS(finish_cone)(ScsConeWork *c);

void SCS(set_rho_y_vec)(const ScsCone *k, scs_float scale, scs_float *rho_y_vec,
                        scs_int m);

#ifdef __cplusplus
}
#endif
#endif
