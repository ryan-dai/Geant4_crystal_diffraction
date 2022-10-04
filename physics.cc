#include "physics.hh"
#include "G4EmPenelopePhysics.hh"
MyPhysicsList::MyPhysicsList()
: G4VUserPhysicsList()
{
    RegisterPhysics (new G4EmPenelopePhysics());
    RegisterPhysics (new G4EmStandardPhysics()); //more physics implicated more time consumption
    RegisterPhysics (new G4OpticalPhysics());

}

MyPhysicsList::~MyPhysicsList()
{}