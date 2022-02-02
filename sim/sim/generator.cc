#include "generator.hh"
#include "G4IonTable.hh"
#include "G4Geantino.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
	fParticleGun = new G4ParticleGun(1);
	fParticleGun->SetParticleEnergy(0*eV);
 	fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
  	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));  

}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName="gamma";
	G4ParticleDefinition *particle = particleTable->FindParticle("gamma");
	
	G4ThreeVector pos(0., 0., 0.);
	G4ThreeVector mom(0., 0., 1.3);
	
	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom);
	fParticleGun->SetParticleMomentum(0.1*MeV);
	fParticleGun->SetParticleDefinition(particle);
	
	fParticleGun->GeneratePrimaryVertex(anEvent);
}


