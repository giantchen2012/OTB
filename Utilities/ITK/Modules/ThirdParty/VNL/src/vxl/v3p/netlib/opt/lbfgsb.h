extern int v3p_netlib_setulb_(
  v3p_netlib_integer v3p_netlib_const *n, /* dimension of the problem */
  v3p_netlib_integer v3p_netlib_const *m, /* max num of metric corrections */
  v3p_netlib_doublereal *x, /* IN: old approximation, OUT: new approximation */
  v3p_netlib_doublereal v3p_netlib_const *l, /* lower bound on x */
  v3p_netlib_doublereal v3p_netlib_const *u, /* upper bound on x */
  v3p_netlib_integer v3p_netlib_const *nbd, /* type of bounds, see below */
  v3p_netlib_doublereal *f, /* OUT: value of function at x */
  v3p_netlib_doublereal *g, /* OUT: value of gradient at x */
  v3p_netlib_doublereal v3p_netlib_const *factr, /* accruacy, see below */
  v3p_netlib_doublereal v3p_netlib_const *pgtol, /* tolerance, see below */
  v3p_netlib_doublereal *wa, /* working space (2m + 4)n + 12m^2 + 12m */
  v3p_netlib_integer *iwa, /* working space 3n */
  char *task, /* working space 60 chars, init to START */
  v3p_netlib_integer v3p_netlib_const *iprint, /* output level, see below */
  char *csave, /* working space 60 chars */
  v3p_netlib_logical *lsave, /* working space 4 */
  v3p_netlib_integer *isave, /* working space 44 */
  v3p_netlib_doublereal *dsave /* working space 29 */
  );
/*
 *    nbd is an integer array of dimension n.
 *      On entry nbd represents the type of bounds imposed on the
 *        variables, and must be specified as follows:
 *        nbd(i)=0 if x(i) is unbounded,
 *               1 if x(i) has only a lower bound,
 *               2 if x(i) has both lower and upper bounds, and
 *               3 if x(i) has only an upper bound.
 *      On exit nbd is unchanged.
 *
 *    factr is a double precision variable.
 *      On entry factr >= 0 is specified by the user.  The iteration
 *        will stop when
 *
 *        (f^k - f^{k+1})/max{|f^k|,|f^{k+1}|,1} <= factr*epsmch
 *
 *        where epsmch is the machine precision, which is automatically
 *        generated by the code. Typical values for factr: 1.d+12 for
 *        low accuracy; 1.d+7 for moderate accuracy; 1.d+1 for extremely
 *        high accuracy.
 *      On exit factr is unchanged.
 *
 *    pgtol is a double precision variable.
 *      On entry pgtol >= 0 is specified by the user.  The iteration
 *        will stop when
 *
 *                max{|proj g_i | i = 1, ..., n} <= pgtol
 *
 *        where pg_i is the ith component of the projected gradient.
 *      On exit pgtol is unchanged.
 *
 *    iprint is an integer variable that must be set by the user.
 *      It controls the frequency and type of output generated:
 *       iprint<0    no output is generated;
 *       iprint=0    print only one line at the last iteration;
 *       0<iprint<99 print also f and |proj g| every iprint iterations;
 *       iprint=99   print details of every iteration except n-vectors;
 *       iprint=100  print also the changes of active set and final x;
 *       iprint>100  print details of every iteration including x and g;
 *      When iprint > 0, the file iterate.dat will be created to
 *                       summarize the iteration.
 *
*/
extern int v3p_netlib_mainlb_(
  v3p_netlib_integer *n,
  v3p_netlib_integer *m,
  v3p_netlib_doublereal *x,
  v3p_netlib_doublereal *l,
  v3p_netlib_doublereal *u,
  v3p_netlib_integer *nbd,
  v3p_netlib_doublereal *f,
  v3p_netlib_doublereal *g,
  v3p_netlib_doublereal *factr,
  v3p_netlib_doublereal *pgtol,
  v3p_netlib_doublereal *ws,
  v3p_netlib_doublereal *wy,
  v3p_netlib_doublereal *sy,
  v3p_netlib_doublereal *ss,
  v3p_netlib_doublereal *wt,
  v3p_netlib_doublereal *wn,
  v3p_netlib_doublereal *snd,
  v3p_netlib_doublereal *z__,
  v3p_netlib_doublereal *r__,
  v3p_netlib_doublereal *d__,
  v3p_netlib_doublereal *t,
  v3p_netlib_doublereal *xp,
  v3p_netlib_doublereal *wa,
  v3p_netlib_integer *index,
  v3p_netlib_integer *iwhere,
  v3p_netlib_integer *indx2,
  char *task,
  v3p_netlib_integer *iprint,
  char *csave,
  v3p_netlib_logical *lsave,
  v3p_netlib_integer *isave,
  v3p_netlib_doublereal *dsave,
  v3p_netlib_ftnlen task_len,
  v3p_netlib_ftnlen csave_len
  );
extern int v3p_netlib_active_(
  v3p_netlib_integer *n,
  v3p_netlib_doublereal *l,
  v3p_netlib_doublereal *u,
  v3p_netlib_integer *nbd,
  v3p_netlib_doublereal *x,
  v3p_netlib_integer *iwhere,
  v3p_netlib_integer *iprint,
  v3p_netlib_logical *prjctd,
  v3p_netlib_logical *cnstnd,
  v3p_netlib_logical *boxed
  );
extern int v3p_netlib_bmv_(
  v3p_netlib_integer *m,
  v3p_netlib_doublereal *sy,
  v3p_netlib_doublereal *wt,
  v3p_netlib_integer *col,
  v3p_netlib_doublereal *v,
  v3p_netlib_doublereal *p,
  v3p_netlib_integer *info
  );
extern int v3p_netlib_cauchy_(
  v3p_netlib_integer *n,
  v3p_netlib_doublereal *x,
  v3p_netlib_doublereal *l,
  v3p_netlib_doublereal *u,
  v3p_netlib_integer *nbd,
  v3p_netlib_doublereal *g,
  v3p_netlib_integer *iorder,
  v3p_netlib_integer *iwhere,
  v3p_netlib_doublereal *t,
  v3p_netlib_doublereal *d__,
  v3p_netlib_doublereal *xcp,
  v3p_netlib_integer *m,
  v3p_netlib_doublereal *wy,
  v3p_netlib_doublereal *ws,
  v3p_netlib_doublereal *sy,
  v3p_netlib_doublereal *wt,
  v3p_netlib_doublereal *theta,
  v3p_netlib_integer *col,
  v3p_netlib_integer *head,
  v3p_netlib_doublereal *p,
  v3p_netlib_doublereal *c__,
  v3p_netlib_doublereal *wbp,
  v3p_netlib_doublereal *v,
  v3p_netlib_integer *nseg,
  v3p_netlib_integer *iprint,
  v3p_netlib_doublereal *sbgnrm,
  v3p_netlib_integer *info,
  v3p_netlib_doublereal *epsmch
  );
extern int v3p_netlib_cmprlb_(
  v3p_netlib_integer *n,
  v3p_netlib_integer *m,
  v3p_netlib_doublereal *x,
  v3p_netlib_doublereal *g,
  v3p_netlib_doublereal *ws,
  v3p_netlib_doublereal *wy,
  v3p_netlib_doublereal *sy,
  v3p_netlib_doublereal *wt,
  v3p_netlib_doublereal *z__,
  v3p_netlib_doublereal *r__,
  v3p_netlib_doublereal *wa,
  v3p_netlib_integer *index,
  v3p_netlib_doublereal *theta,
  v3p_netlib_integer *col,
  v3p_netlib_integer *head,
  v3p_netlib_integer *nfree,
  v3p_netlib_logical *cnstnd,
  v3p_netlib_integer *info
  );
extern int v3p_netlib_errclb_(
  v3p_netlib_integer *n,
  v3p_netlib_integer *m,
  v3p_netlib_doublereal *factr,
  v3p_netlib_doublereal *l,
  v3p_netlib_doublereal *u,
  v3p_netlib_integer *nbd,
  char *task,
  v3p_netlib_integer *info,
  v3p_netlib_integer *k,
  v3p_netlib_ftnlen task_len
  );
extern int v3p_netlib_formk_(
  v3p_netlib_integer *n,
  v3p_netlib_integer *nsub,
  v3p_netlib_integer *ind,
  v3p_netlib_integer *nenter,
  v3p_netlib_integer *ileave,
  v3p_netlib_integer *indx2,
  v3p_netlib_integer *iupdat,
  v3p_netlib_logical *updatd,
  v3p_netlib_doublereal *wn,
  v3p_netlib_doublereal *wn1,
  v3p_netlib_integer *m,
  v3p_netlib_doublereal *ws,
  v3p_netlib_doublereal *wy,
  v3p_netlib_doublereal *sy,
  v3p_netlib_doublereal *theta,
  v3p_netlib_integer *col,
  v3p_netlib_integer *head,
  v3p_netlib_integer *info
  );
extern int v3p_netlib_formt_(
  v3p_netlib_integer *m,
  v3p_netlib_doublereal *wt,
  v3p_netlib_doublereal *sy,
  v3p_netlib_doublereal *ss,
  v3p_netlib_integer *col,
  v3p_netlib_doublereal *theta,
  v3p_netlib_integer *info
  );
extern int v3p_netlib_freev_(
  v3p_netlib_integer *n,
  v3p_netlib_integer *nfree,
  v3p_netlib_integer *index,
  v3p_netlib_integer *nenter,
  v3p_netlib_integer *ileave,
  v3p_netlib_integer *indx2,
  v3p_netlib_integer *iwhere,
  v3p_netlib_logical *wrk,
  v3p_netlib_logical *updatd,
  v3p_netlib_logical *cnstnd,
  v3p_netlib_integer *iprint,
  v3p_netlib_integer *iter
  );
extern int v3p_netlib_hpsolb_(
  v3p_netlib_integer *n,
  v3p_netlib_doublereal *t,
  v3p_netlib_integer *iorder,
  v3p_netlib_integer *iheap
  );
extern int v3p_netlib_lnsrlb_(
  v3p_netlib_integer *n,
  v3p_netlib_doublereal *l,
  v3p_netlib_doublereal *u,
  v3p_netlib_integer *nbd,
  v3p_netlib_doublereal *x,
  v3p_netlib_doublereal *f,
  v3p_netlib_doublereal *fold,
  v3p_netlib_doublereal *gd,
  v3p_netlib_doublereal *gdold,
  v3p_netlib_doublereal *g,
  v3p_netlib_doublereal *d__,
  v3p_netlib_doublereal *r__,
  v3p_netlib_doublereal *t,
  v3p_netlib_doublereal *z__,
  v3p_netlib_doublereal *stp,
  v3p_netlib_doublereal *dnorm,
  v3p_netlib_doublereal *dtd,
  v3p_netlib_doublereal *xstep,
  v3p_netlib_doublereal *stpmx,
  v3p_netlib_integer *iter,
  v3p_netlib_integer *ifun,
  v3p_netlib_integer *iback,
  v3p_netlib_integer *nfgv,
  v3p_netlib_integer *info,
  char *task,
  v3p_netlib_logical *boxed,
  v3p_netlib_logical *cnstnd,
  char *csave,
  v3p_netlib_integer *isave,
  v3p_netlib_doublereal *dsave,
  v3p_netlib_ftnlen task_len,
  v3p_netlib_ftnlen csave_len
  );
extern int v3p_netlib_matupd_(
  v3p_netlib_integer *n,
  v3p_netlib_integer *m,
  v3p_netlib_doublereal *ws,
  v3p_netlib_doublereal *wy,
  v3p_netlib_doublereal *sy,
  v3p_netlib_doublereal *ss,
  v3p_netlib_doublereal *d__,
  v3p_netlib_doublereal *r__,
  v3p_netlib_integer *itail,
  v3p_netlib_integer *iupdat,
  v3p_netlib_integer *col,
  v3p_netlib_integer *head,
  v3p_netlib_doublereal *theta,
  v3p_netlib_doublereal *rr,
  v3p_netlib_doublereal *dr,
  v3p_netlib_doublereal *stp,
  v3p_netlib_doublereal *dtd
  );
extern int v3p_netlib_projgr_(
  v3p_netlib_integer *n,
  v3p_netlib_doublereal *l,
  v3p_netlib_doublereal *u,
  v3p_netlib_integer *nbd,
  v3p_netlib_doublereal *x,
  v3p_netlib_doublereal *g,
  v3p_netlib_doublereal *sbgnrm
  );
extern int v3p_netlib_subsm_(
  v3p_netlib_integer *n,
  v3p_netlib_integer *m,
  v3p_netlib_integer *nsub,
  v3p_netlib_integer *ind,
  v3p_netlib_doublereal *l,
  v3p_netlib_doublereal *u,
  v3p_netlib_integer *nbd,
  v3p_netlib_doublereal *x,
  v3p_netlib_doublereal *d__,
  v3p_netlib_doublereal *xp,
  v3p_netlib_doublereal *ws,
  v3p_netlib_doublereal *wy,
  v3p_netlib_doublereal *theta,
  v3p_netlib_doublereal *xx,
  v3p_netlib_doublereal *gg,
  v3p_netlib_integer *col,
  v3p_netlib_integer *head,
  v3p_netlib_integer *iword,
  v3p_netlib_doublereal *wv,
  v3p_netlib_doublereal *wn,
  v3p_netlib_integer *iprint,
  v3p_netlib_integer *info
  );
extern int v3p_netlib_dcsrch_(
  v3p_netlib_doublereal *f,
  v3p_netlib_doublereal *g,
  v3p_netlib_doublereal *stp,
  v3p_netlib_doublereal *ftol,
  v3p_netlib_doublereal *gtol,
  v3p_netlib_doublereal *xtol,
  v3p_netlib_doublereal *stpmin,
  v3p_netlib_doublereal *stpmax,
  char *task,
  v3p_netlib_integer *isave,
  v3p_netlib_doublereal *dsave,
  v3p_netlib_ftnlen task_len
  );
extern int v3p_netlib_dcstep_(
  v3p_netlib_doublereal *stx,
  v3p_netlib_doublereal *fx,
  v3p_netlib_doublereal *dx,
  v3p_netlib_doublereal *sty,
  v3p_netlib_doublereal *fy,
  v3p_netlib_doublereal *dy,
  v3p_netlib_doublereal *stp,
  v3p_netlib_doublereal *fp,
  v3p_netlib_doublereal *dp,
  v3p_netlib_logical *brackt,
  v3p_netlib_doublereal *stpmin,
  v3p_netlib_doublereal *stpmax
  );
extern v3p_netlib_doublereal v3p_netlib_dpmeps_(
  
  );
extern int v3p_netlib_dtrsl_(
  v3p_netlib_doublereal *t,
  v3p_netlib_integer *ldt,
  v3p_netlib_integer *n,
  v3p_netlib_doublereal *b,
  v3p_netlib_integer *job,
  v3p_netlib_integer *info
  );