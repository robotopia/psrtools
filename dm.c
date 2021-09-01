#include <stdlib.h>
#include <stdio.h>

#include "dm.h"

double dmdelay( double DM, double freq_MHz )
{
    return DISPERSION_CONSTANT * DM / (freq_MHz * freq_MHz);
}

double dmdiff( double DM, double freq_MHz_lo, double freq_MHz_hi )
{
    return dmdelay( DM, freq_MHz_lo ) - dmdelay( DM, freq_MHz_hi );
}

