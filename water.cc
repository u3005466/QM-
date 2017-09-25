#include "molecule.h"
#include <cmath>
#include <cstdio>

using namespace std;

int main(int argc, char *argv[])
{
    Molecule h2o("geom.dat", 0);

    h2o.print_geom();
    h2o.translate(5, 0, 0);
    h2o.print_geom();
    printf("%8.5f\n", h2o.bond(0,1));
    h2o.rotate(0.5 * M_PI);
    h2o.print_geom();
    return 0;
} 
