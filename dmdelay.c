#include <stdlib.h>
#include <stdio.h>

void usage( char *argv[] )
{
    fprintf( stderr, "Calculate the delay due to ISM dispersion between two "
                     "given frequencies, according to the formula\n\n" );
    fprintf( stderr, "                         ⎛  DM  ⎞   ⎡ ⎛ fₗₒ ⎞⁻²   ⎛ fₕᵢ ⎞⁻²⎤\n" );
    fprintf( stderr, "    Δt = 4.15 × 10⁶ ms × ⎜——————⎟ × ⎢ ⎜ ——— ⎟   - ⎜ ——— ⎟  ⎥\n" );
    fprintf( stderr, "                         ⎝pc/cm³⎠   ⎣ ⎝ MHz ⎠     ⎝ MHz ⎠  ⎦\n\n" );
    fprintf( stderr, "usage: %s [DM] [freq_lo] [freq_hi]\n", argv[0] );
    fprintf( stderr, "  DM      - dispersion measure (pc/cm³)\n" );
    fprintf( stderr, "  freq_lo - lower frequency (MHz)\n" );
    fprintf( stderr, "  freq_hi - higher frequency (MHz)\n" );
    fprintf( stderr, "The result is written to stdout and given in ms\n" );
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
    double dmdelay = 4.148808e6 * DM * (1.0/(flo*flo) - 1.0/(fhi*fhi));

    // Print the output to stdout
    printf( "%.5f\n", dmdelay );

    // Exit gracefully
    return 0;
}
