#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *R0Hist)
{
	G4Track *track = aStep->GetTrack();
	
	track->SetTrackStatus(fStopAndKill);
	
	G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
	G4StepPoint *postStepPoint = aStep->GetPostStepPoint();
	
	G4ThreeVector posPhoton = preStepPoint->GetPosition();
	
	// G4cout << "Photon Position: " << posPhoton << G4endl;
	
	const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
	
	G4int copyNo = touchable->GetCopyNumber(); // This will give the label of the detector the photon is entering.
	
	// G4cout << "Copy Number: " << copyNo << G4endl;
	
	G4VPhysicalVolume *physVol = touchable->GetVolume();
	G4ThreeVector posDetector = physVol->GetTranslation();
	
	G4cout << "Detector Position: " << posDetector << G4endl;
}