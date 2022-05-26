#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <erfa.h>
#include <psrcat.h>

int str2rad( char *str, double *rad, int is_ra )
{
    // if is_ra, parse as HH:MM:SS, otherwise DD:MM:SS
    // Return 1 if success, 0 if fail
    int dd, mm;
    double ss;
    char s;

    // Parse raw strings
    if (sscanf( str, "%d:%d:%lf", &dd, &mm, &ss ) != 3)
    {
        fprintf( stderr, "ERROR: Cannot parse %s\n", str );
        return 0;
    }

    if (dd < 0)
    {
        s = '-';
        dd = -dd;
    }
    else
        s = '+';

    // Convert hours, minutes, seconds to radians
    // OR
    // Convert degrees, arcminutes, arcseconds to radians
    int status;
    if (is_ra)
        status = eraTf2a( s, dd, mm, ss, rad );
    else
        status = eraAf2a( s, dd, mm, ss, rad );

    if (status != 0)
    {
        fprintf( stderr, "ERROR: couldn't convert \"%c%d:%d:%lf\" to radians\n",
                s, dd, mm, ss );
        return 0;
    }

    return 1;
}

int radec2rad( char *ra, char *dec, double *rarad, double *decrad )
{
    int status = 1;
    status &= str2rad( ra,  rarad,  1 );
    status &= str2rad( dec, decrad, 0 );
    return status;
}

void angsep_usage( char *argv[] )
{
    fprintf( stderr, "Find pulsars near to given coordinates\n"
                     "usage: %s [RA1] [DEC1] [RA2] [DEC2]\n"
                     "  RA        - Right ascension (\"hh:mm:ss.s\")\n"
                     "  Dec       - Declination (\"±dd:mm:ss.s\")\n"
                     "or:    %s [RA] [DEC] [FILE]\n"
                     "  FILE      - File containing many RAs & Decs (whitespace separated)\n",
                     argv[0], argv[0] );
}

int main( int argc, char *argv[] )
{
    // Parse command line arguments
    if (argc < 4)
    {
        fprintf( stderr, "ERROR: incorrect number of arguments\n" );
        angsep_usage( argv );
        exit(EXIT_FAILURE);
    }

    int use_file = 0;
    if (argc == 4)
        use_file = 1;

    double rarad, decrad;

    // Parse the positions
    radec2rad( argv[1], argv[2], &rarad, &decrad );

    double rarad2, decrad2;
    if (!use_file)
    {
        radec2rad( argv[3], argv[4], &rarad2, &decrad2 );

        printf( "%lf\n", eraSeps( rarad, decrad, rarad2, decrad2 ) );
    }
    else
    {
        char str1[64], str2[64];
        FILE *f = fopen( argv[3], "r" );
        if (f == NULL)
        {
            fprintf( stderr, "ERROR: Cannot open file '%s'\n", argv[3] );
            exit(EXIT_FAILURE);
        }

        while (fscanf( f, "%s %s", str1, str2 ) == 2)
        {
            if (radec2rad( str1, str2, &rarad2, &decrad2 ))
                printf( "%lf\n", eraSeps( rarad, decrad, rarad2, decrad2 ) );
            else
                printf( "\n" );
        }
    }

    exit(EXIT_SUCCESS);
}
