# psrtools
Suite of random pulsar-related utilities

## `angsep`

Calculates the angular separation between two sets of RA/Dec positions.
It can be used in conjunction with psrcat to generate a list of pulsars closest to a given position.
For example, to get a reverse-order list of pulsars closest to 10:31:36 18:42:0,
```
paste -d' ' <(psrcat -x -c "jname" | awk '{print $1}') \
            <(./angsep 10:31:36 18:42:0 <(psrcat -x -c "raj decj" | awk '{print $1,$4}')) | \
awk '$2 {print $1, $2*180/3.141592654}' | \
sort -n -r -k2
```
