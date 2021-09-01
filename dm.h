#ifndef __DM_H__
#define __DM_H__

#define DISPERSION_CONSTANT  4.148808e6  /* MHz^2 pc^-1 cm^3 ms */

double dmdelay( double DM, double freq_MHz );
double dmdiff( double DM, double freq_MHz_lo, double freq_MHz_hi );

#endif
