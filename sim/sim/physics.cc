#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
	RegisterPhysics (new G4EmStandardPhysics());
    RegisterPhysics (new G4OpticalPhysics());
    //RegisterPhysics(new FTFP_BERT());
}

MyPhysicsList::~MyPhysicsList()
{}