#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "dm.h"

int main()
{
    // Calculate the DM delay
    assert(abs(dmdiff( 10.0, 20.0, 30.0 ) - 5.762233333333e+04) < 1e-6);

    // Exit gracefully
    return 0;
}
