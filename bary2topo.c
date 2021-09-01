#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <SpiceUsr.h>

#include "barycentre.h"
#include "vec.h"

void usage( FILE *f );
void fprintf_header( FILE *f, int argc, char *argv[] );

int main( int argc, char *argv[] )
{
    // Set the default output to stdout
    FILE *out = stdout;

    // Parse the command line arguments
    if (argc < 6)
    {
        usage( stderr );
        exit(EXIT_FAILURE);
    }

    double  ra_hrs    = atof(argv[1]);   // Right Ascension in decimal hours
    double  dec_degs  = atof(argv[2]);   // Declination in decimal degrees
    double  period    = atof(argv[3]);   // Declination in decimal degrees
    char   *ephemfile = argv[4];         // Path to the NASA planetary
                                         // ephemeris file
    double mjd;

    // Print out the header
    fprintf_header( out, argc, argv );

    int i;
    for (i = 5; i < argc; i++)
    {
        mjd = atof(argv[i]);   // The epoch in question (MJD)
        fprintf( out, "  %10.6f  %.15f\n", mjd, period / calc_doppler_factor( ra_hrs, dec_degs, mjd, ephemfile ) );
    }

    return EXIT_SUCCESS;
}

void usage( FILE *f )
{
    fprintf( f, "usage: bary2topo RA DEC PERIOD SPK MJD [MJD ...]\n"
            "  RA in J2000 decimal hours\n"
            "  DEC in J2000 decimal degrees\n"
            "  PERIOD in seconds\n"
            "  SPK path to NASA planetary ephemeris file\n"
            "    (e.g. from http://naif.jpl.nasa.gov/pub/naif/"
            "generic_kernels/spk/planets/de430.bsp)\n"
            "  MJD in decimal days\n" );
}

void fprintf_header( FILE *f, int argc, char *argv[] )
{
    fprintf( f, "# PSRTOOLS %s\n", PSRTOOLS_VERSION );
    fprintf( f, "# Creating command:\n#    " );
    int i;
    for (i = 0; i < argc; i++)
        fprintf( f, " %s", argv[i] );
    fprintf( f, "\n#\n"
            "# (1)           (2)                     \n"
            "# MJD           Topocentric_period_(sec)\n"
            "# --------------------------------------\n" );
}
