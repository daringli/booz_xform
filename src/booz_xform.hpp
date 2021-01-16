#ifndef BOOZ_XFORM_H
#define BOOZ_XFORM_H

#include <string>
#include <valarray>
#include "vector_matrix.hpp"

namespace booz_xform {  

  const boozfloat pi = 3.141592653589793;
  const boozfloat twopi = 2.0 * pi;
  const boozfloat mu0 = (4.0e-7) * pi;
  
  int driver(int, char**);
  
  class Booz_xform {
  private:
    int nu2_b; //!< Not sure
    int nu3_b; //!< Not sure
    int nu, nv; //!< Number of real-space grid points in the VMEC poloidal and toroidal angles
    boozfloat d_theta, d_zeta; //!< Spacing between grid points in the VMEC poloidal and toroidal angles
    int n_theta_zeta; //!< Number of grid points in the combined theta-zeta grid
    boozfloat hs; //!< Spacing in s between adjacent flux surfaces
    bool completed;
    Vector theta_grid; //!< Theta values of the (theta, zeta) grid, reshaped from 2D -> 1D.
    Vector zeta_grid; //!< Theta values of the (theta, zeta) grid, reshaped from 2D -> 1D.
    Matrix cosm; //!< Stores cos(m*theta) for xm
    Matrix cosn; //!< Stores cos(n*zeta) for xn
    Matrix sinm; //!< Stores sin(m*theta) for xm
    Matrix sinn; //!< Stores sin(n*zeta) for xn
    Matrix cosm_nyq; //!< Stores cos(m*theta) for xm_nyq
    Matrix cosn_nyq; //!< Stores cos(n*zeta) for xn_nyq
    Matrix sinm_nyq; //!< Stores sin(m*theta) for xm_nyq
    Matrix sinn_nyq; //!< Stores sin(n*zeta) for xn_nyq
    Matrix cosm_b; //!< Stores cos(m*theta_Boozer) for xmb
    Matrix cosn_b; //!< Stores cos(n*zeta_Boozer) for xnb
    Matrix sinm_b; //!< Stores sin(m*theta_Boozer) for xmb
    Matrix sinn_b; //!< Stores sin(n*zeta_Boozer) for xnb
    Vector r, z, lambda, d_lambda_d_theta, d_lambda_d_zeta;
    Vector w, d_w_d_theta, d_w_d_zeta, bmod, theta_diff;
    Vector p, d_p_d_theta, d_p_d_zeta;
    Vector theta_Boozer_grid, zeta_Boozer_grid;
    Matrix wmns, wmnc; //!< Right-hand side of eq (10) in Fourier space
    Vector d_Boozer_d_vmec; //!< The Jacobian in eq (12)
    Vector boozer_jacobian; //!< (G + iota * I) / B^2 on the (theta, zeta) grid.
    
    void defaults();
    
  public:
    int verbose;
    int mboz, nboz;
    bool asym;
    int mpol, ntor, mnmax, mpol_nyq, ntor_nyq, mnmax_nyq, ns, nfp, mnboz;
    Matrix rmnc, rmns, zmnc, zmns, lmnc, lmns, bmnc, bmns;
    Matrix bsubumnc, bsubumns, bsubvmnc, bsubvmns;
    Vector iotas, xm, xn, xm_nyq, xn_nyq;
    std::valarray<int> jlist;
    Vector xmb, xnb;
    int ns_b; //!< Number of surfaces on which the transformation is calculated
    Matrix bmnc_b, rmnc_b, zmns_b, pmns_b, gmnc_b;
    Matrix bmns_b, rmns_b, zmnc_b, pmnc_b, gmns_b;
    Vector Boozer_I, Boozer_G; //!< The covariant components of B in Boozer coordinates.
    
    Booz_xform();
    void read_boozmn(std::string);
    void read_wout(std::string);
    void run();
    void init();
    void surface_solve(int);
    void check_accuracy(int, int);
    void write_boozmn(std::string);
    void testfunc1();
    void testfunc2(int);
  };
  
}

/* Translating between fortran and C++ variable names:

   nu_b, nv_b -> nu, nv
   nunv -> n_theta_zeta
   dth, dzt -> d_theta, d_zeta
   scl -> fourier_factor
   thgrd -> theta_grid
   ztgrd -> zeta_grid
   jsize -> ns_b
   wp -> w
   wt -> d_w_d_theta
   wz -> d_w_d_zeta
   lam -> lambda
   lt -> d_lambda_d_theta
   lz -> d_lambda_d_zeta
   xjac -> d_Boozer_d_vmec
 */
#endif

