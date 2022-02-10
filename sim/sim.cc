#include <iostream>

#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "FTFP_BERT.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4OpticalParameters.hh"
#include "G4OpticalPhysics.hh"


#include "construction.hh"
// #include "physics.hh"
#include "action.hh"

int main(int argc, char** argv)
{
	// define runmanager
	G4RunManager *runManager = new G4RunManager();
	
	// load the detector
	runManager->SetUserInitialization(new MyDetectorConstruction());
	
	// Physics List defined here
	G4VModularPhysicsList* physicsList = new FTFP_BERT;
  	physicsList->ReplacePhysics(new G4EmStandardPhysics_option4());

  	G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
  	auto opticalParams               = G4OpticalParameters::Instance();

  	opticalParams->SetWLSTimeProfile("delta");

 	opticalParams->SetScintTrackSecondariesFirst(true);

  	opticalParams->SetCerenkovMaxPhotonsPerStep(100);
  	opticalParams->SetCerenkovMaxBetaChange(10.0);
  	opticalParams->SetCerenkovTrackSecondariesFirst(true);

  	physicsList->RegisterPhysics(opticalPhysics);
  	runManager->SetUserInitialization(physicsList);

	
	// load the action
	runManager->SetUserInitialization(new MyActionInitialization());
	
	runManager->Initialize();
	
	// Interactive mode
	G4UIExecutive *ui = new G4UIExecutive(argc, argv);
 	
	
	// Initilize visualization
	G4VisManager *visManager = new G4VisExecutive();
	visManager->Initialize();
	
	G4UImanager *UImanager = G4UImanager::GetUIpointer();
	
	UImanager->ApplyCommand("/vis/open OGL");
	UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
	UImanager->ApplyCommand("/vis/drawVolume");
	UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
	UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
	// UImanager->ApplyCommand("/tracking/verbose 2");
	UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");

	ui->SessionStart();
	
	return 0;
}