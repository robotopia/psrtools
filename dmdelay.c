#include <stdlib.h>
#include <stdio.h>

#include "dm.h"

void usage( char *argv[] )
{
    fprintf( stderr, "Calculate the delay due to ISM dispersion between two "
                     "given frequencies, according to the formula\n\n"
                     "                               ⎛  DM  ⎞   ⎡ ⎛ fₗₒ ⎞⁻²   ⎛ fₕᵢ ⎞⁻²⎤\n"
                     "    Δt = %10.6f × 10⁶ ms × ⎜——————⎟ × ⎢ ⎜ ——— ⎟   - ⎜ ——— ⎟  ⎥\n"
                     "                               ⎝pc/cm³⎠   ⎣ ⎝ MHz ⎠     ⎝ MHz ⎠  ⎦\n\n"
                     "usage: %s [DM] [freq_lo] [freq_hi]\n"
                     "  DM      - dispersion measure (pc/cm³)\n"
                     "  freq_lo - lower frequency (MHz)\n"
                     "  freq_hi - higher frequency (MHz)\n"
                     "The result is written to stdout and given in ms\n",
                     DISPERSION_CONSTANT / 1e6,
                     argv[0]
           );
}

int main( int argc, char *argv[] )
{
    // Parse command line arguments
    if (argc != 4)
    {
        fprintf( stderr, "error: incorrect number of arguments\n" );
        usage( argv );
        exit(EXIT_FAILURE);
    }

    double DM  = atof(argv[1]);
    double flo = atof(argv[2]);
    double fhi = atof(argv[3]);

    // Calculate the DM delay
    double delay_ms = dmdiff( DM, flo, fhi );

    // Print the output to stdout
    printf( "%.5f\n", delay_ms );

    // Exit gracefully
    return 0;
}
