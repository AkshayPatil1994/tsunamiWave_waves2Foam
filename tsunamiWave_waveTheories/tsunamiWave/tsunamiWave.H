/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by original author
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Class
    Foam::waveTheories::tsunameWave

Description
    First test for a tsunami wave using
	eta = A sech(Omega*( [t-t0] - [x - x0]/sqrt(g*h)))^2
	u = sqrt(g/h)*eta

SourceFiles
    tsunamiWave.C

Author
   Akshay Patil

\*---------------------------------------------------------------------------*/

#ifndef tsunamiWave_H
#define tsunamiWave_H

#include "waveTheory.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace waveTheories
{

/*---------------------------------------------------------------------------*\
                         Class tsunamiWave Declaration
\*---------------------------------------------------------------------------*/

class tsunamiWave
:
    public waveTheory
{

protected:

    // Protected data
        // Read from waveProperties
        scalar H_;
        scalar h_;
        vector propagationDirection_;
        point  x0_;
	scalar A1_;	// This is the coeff in front of the E wave
	scalar omega1_;	// This is the wave period in the sech() argument
	scalar t0_;	// Scalar time t0

        // Computed
        scalar G_;
        scalar c_;

    // Protected member functions

        scalar factor(const scalar& ) const;
public:

    //- Runtime type information
    TypeName("tsunamiWave");

    // Constructors

        //- from components
        tsunamiWave
        (
            const word&,
            const fvMesh& mesh_
        );


    // Destructor

        ~tsunamiWave()
        {}


    // Member Functions
        virtual Switch conflictTSoftInitialise() const
        {
            return false;
        };

        void printCoeffs();

        virtual scalar eta
        (
            const point&,
            const scalar&
        ) const;

//        virtual scalar ddxPd
//        (
//            const point&,
//            const scalar&,
//            const vector&
//        ) const;

        virtual vector U
        (
            const point&,
            const scalar&
        ) const;

        virtual scalar pExcess
        (
            const point&,
            const scalar&
        ) const;

        bool implementPressure() const
        {
            return true; //false;
        };

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace waveTheories
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
