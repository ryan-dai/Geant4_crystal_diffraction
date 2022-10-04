#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
    RegisterPhysics (new G4EmStandardPhysics()); //more physics implicated more time consumption
    RegisterPhysics (new G4OpticalPhysics());

}

MyPhysicsList::~MyPhysicsList()
{}