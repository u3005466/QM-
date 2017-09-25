#include "molecule.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cassert>
#include <cmath>

void Molecule::print_geom()
{
    for(int i=0; i < natom; i++)
        printf("%d %8.5f %8.5f %8.5f\n", zvals[i], geom[i][0], geom[i][1], geom[i][2]);
}

void Molecule::translate(double x, double y, double z)
{
    for(int i=0; i < natom; i++) {
        geom[i][0] += x;
        geom[i][1] += y;
        geom[i][2] += z;
    }
}

void Molecule::rotate(double phi)
{
    for(int i=0; i < natom; i++) {
        double x = geom[i][0]; double y = geom[i][1];
        geom[i][0] = x * cos(phi) - y * sin(phi);
        geom[i][1] = x * sin(phi) + y * cos(phi);
    }
}

double Molecule::bond(int a, int b)
{
    return sqrt(pow((geom[a][0] - geom[b][0]), 2) +
                pow((geom[a][1] - geom[b][1]), 2) +
                pow((geom[a][2] - geom[b][2]), 2));
}

double Molecule::unit(int cart, int a, int b)
{
    return -(geom[a][cart] - geom[b][cart])/bond(a,b);
}

double Molecule::angle(int a, int b, int c)
{
    return acos(unit(0,b,a) * unit(0,b,c) + 
                unit(1,b,a) * unit(1,b,c) +
                unit(2,b,a) * unit(2,b,c));
}

Molecule::Molecule(const char *filename, int q)
{
    charge = q;

    /* open filename */
    std::ifstream is(filename);
    assert(is.good());

    /* read the number of atoms from filename */
    is >> natom;

    /* allocate space */
    zvals = new int[natom];
    geom = new double* [natom];
    for(int i=0; i < natom; i++)
        geom[i] = new double[3];

    for(unsigned int i=0; i < natom; i++)
        is >> zvals[i] >> geom[i][0] >> geom[i][1] >> geom[i][2];

    is.close();
}
Molecule::~Molecule()
{
    delete[] zvals;
    for(int i=0; i < natom; i++)
        delete[] geom[i];
    delete[] geom;
}
