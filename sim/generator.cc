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

//void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
//{
//	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
//	G4String particleName="proton";
//	G4ParticleDefinition *particle = particleTable->FindParticle("proton");
//	
//	G4ThreeVector pos(0., 0., 0.);
//	G4ThreeVector mom(0., 0., 1.);
//	
//	fParticleGun->SetParticlePosition(pos);
//	fParticleGun->SetParticleMomentumDirection(mom);
//	fParticleGun->SetParticleMomentum(100.*GeV);
//	fParticleGun->SetParticleDefinition(particle);
//	
//	fParticleGun->GeneratePrimaryVertex(anEvent);
//}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
  //particle type
  if (fParticleGun->GetParticleDefinition() == G4Geantino::Geantino()) {
    G4int Z = 95, A = 241;
    G4double ionCharge   = 0.*eplus;
    G4double excitEnergy = 0.*keV;

    G4ParticleDefinition* ion
       = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
    fParticleGun->SetParticleDefinition(ion);
    fParticleGun->SetParticleCharge(ionCharge);
  }
  
  	fParticleGun->GeneratePrimaryVertex(anEvent);
  }
  
