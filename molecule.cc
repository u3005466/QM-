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

double Molecule::bond(int atom1, int atom2)
{
    return sqrt(pow((geom[atom1][0] - geom[atom2][0]), 2) +
                pow((geom[atom1][1] - geom[atom2][1]), 2) +
                pow((geom[atom1][2] - geom[atom2][2]), 2));
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
