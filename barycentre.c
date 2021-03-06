#include <stdlib.h>
#include <stdio.h>

#include <SpiceUsr.h>

#include "vec.h"
#include "barycentre.h"

void get_earth_state( double mjd, char *ephemfile, vec *r_earth, vec *v_earth )
/* Extracts the Earth's position (km) and velocity (km/s) in J2000 coordinates
 * from the supplied planetary ephemeris.
 */
{
    // Open ephemeris file
    double jd = mjd + 2400000.5;
    SpiceDouble et = (jd - j2000_c() ) * spd_c();
    SpiceDouble state[6];
    SpiceDouble lt;
    furnsh_c( ephemfile );
    spkezr_c( "earth", et, "j2000", "NONE", "solar system barycenter",
              state, &lt );
    unload_c( ephemfile );

    // Put answer into "output" variables
    if (r_earth != NULL)
    {
        r_earth->x = state[0];
        r_earth->y = state[1];
        r_earth->z = state[2];
    }

    if (v_earth != NULL)
    {
        v_earth->x = state[3];
        v_earth->y = state[4];
        v_earth->z = state[5];
    }
}

void calc_unit_direction_vector( double ra_hrs, double dec_deg, vec *dir )
{
    if (dir == NULL)
        return;

    double ra_rad  = HRS2RAD(ra_hrs);
    double dec_rad = DEG2RAD(dec_deg);

    dir->x = cos(ra_rad)*cos(dec_rad);
    dir->y = sin(ra_rad)*cos(dec_rad);
    dir->z = sin(dec_rad);
}

double get_bc_correction( double ra_hrs, double dec_deg, double mjd, char *ephemfile )
{
    // Get Earth's position
    vec r_earth;
    get_earth_state( mjd, ephemfile, &r_earth, NULL );

    // Get unit vector in direction of source
    vec rn_src;
    calc_unit_direction_vector( ra_hrs, dec_deg, &rn_src );

    vec rn_earth;
    normalise( &r_earth, &rn_earth );

    // Get the barycentric correction
    double proj = proj_length( &r_earth, &rn_src ) * 1.0e3; // km * 1000 = metres
    //fprintf( stderr, "proj_length = %e m\n", proj );

    // Convert the projected length into seconds of light travel time
    return proj/LIGHTSPEED; // In seconds
}

double calc_doppler_factor( double ra_hrs, double dec_degs, double mjd, char *ephemfile )
{
    // Get unit vector representing Earth's motion (in barycentric frame)
    vec rn_src;
    calc_unit_direction_vector( ra_hrs, dec_degs, &rn_src );

    // Get Earth's velocity
    vec v_earth;
    get_earth_state( mjd, ephemfile, NULL, &v_earth ); // km/sec

    // Get component of Earth's velocity in the direction of the source
    double v = dot( &v_earth, &rn_src );

    // Calculate the doppler shift
    double beta = v / clight_c(); // Both v and clight() are in km/sec

    return sqrt((1.0 + beta)/(1.0 - beta));
}
