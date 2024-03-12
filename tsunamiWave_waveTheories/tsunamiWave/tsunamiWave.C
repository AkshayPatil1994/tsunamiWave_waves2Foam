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

\*---------------------------------------------------------------------------*/

#include "tsunamiWave.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace waveTheories
{

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(tsunamiWave, 0);
addToRunTimeSelectionTable(waveTheory, tsunamiWave, dictionary);

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //


tsunamiWave::tsunamiWave
(
    const word& subDictName,
    const fvMesh& mesh_
)
:
    waveTheory(subDictName, mesh_),
    H_(readScalar(coeffDict_.lookup("height"))),
    h_(readScalar(coeffDict_.lookup("depth"))),
    A1_(readScalar(coeffDict_.lookup("A1coeff"))),
    omega1_(readScalar(coeffDict_.lookup("omega1coeff"))),
    propagationDirection_(vector(coeffDict_.lookup("direction"))),
    x0_( vector(coeffDict_.lookup("x0"))),
    t0_( readScalar(coeffDict_.lookup("t0")))
{
    G_ = Foam::mag(g_);				// Gravitational acceleration in m/s^2
    c_     = Foam::sqrt( G_*(H_ + h_) );	// Wave celerity in m/s

    propagationDirection_ /= Foam::mag( propagationDirection_ );

    checkWaveDirection(propagationDirection_);
}


void tsunamiWave::printCoeffs()
{
    Info << "Loading wave theory: " << typeName << endl;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


scalar tsunamiWave::factor( const scalar& time) const
{
    // Dummy, as it does not make sense to ramp up a solitary wave

    return 0.0;
}


scalar tsunamiWave::eta
(
    const point& x,
    const scalar& time
) const
{
//    scalar eta = A1_*1.0/(Foam::cosh(Foam::pow(omega1_*((time - t0_) - (x - x0_)/(Foam::sqrt(G_*(H_ + h_))))),2)) + seaLevel_;
//    scalar denominatorFac = Foam::pow(omega1_*(time - t0_) - ((x-x0_) & propagationDirection_)/c_,2);
//    scalar eta = (A1_*1.0)/(Foam::cosh(Foam::pow(omega1_*(time - t0_) - ((x-x0_) & propagationDirection_)/c_,2))) + seaLevel_;
   scalar eta = (A1_*1.0)/(Foam::cosh(Foam::pow(omega1_*((time-t0_) - ((x-x0_) & propagationDirection_)/c_),2))) + seaLevel_; 
    return eta;
}

scalar tsunamiWave::pExcess
(
    const point& x,
    const scalar& time
) const
{
    scalar Z(returnZ(x));

    scalar result( G_*H_*rhoWater_ );

    result += referencePressure();

    return result;
}


vector tsunamiWave::U
(
    const point& x,
    const scalar& time
) const
{
    scalar Z(returnZ(x));

    scalar Uhorz(0.0);

    Uhorz = Foam::sqrt(G_/h_)*((A1_*1.0)/(Foam::cosh(Foam::pow(omega1_*((time-t0_) - ((x-x0_) & propagationDirection_)/c_),2))) + seaLevel_);

    scalar Uvert(0.0);

    return Uhorz*propagationDirection_ - Uvert*direction_;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace waveTheories
} // End namespace Foam

// ************************************************************************* //
