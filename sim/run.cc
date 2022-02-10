// This was included when wanting to read info to ROOT file.

#include "run.hh"

MyRunAction::MyRunAction()
{
	auto analysisManager = G4AnalysisManager::Instance();
 	analysisManager->SetDefaultFileType("root");
     // If the filename extension is not provided, the default file type (root)
     // will be used for all files specified without extension.
 	analysisManager->SetVerboseLevel(1);

  // Default settings
  	analysisManager->SetNtupleMerging(true);
     // Note: merging ntuples is available only with Root output
  	analysisManager->SetFileName("simmm");
	
	analysisManager->CreateNtuple("Hits", "Hits");
	analysisManager->CreateNtupleIColumn("fEvent");
	analysisManager->CreateNtupleIColumn("fX");
	analysisManager->CreateNtupleIColumn("fY");
	analysisManager->CreateNtupleIColumn("fZ");	
	analysisManager->FinishNtuple();
	
	analysisManager->SetNtupleFileName(0, "simNtuple");
}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
	auto analysisManager = G4AnalysisManager::Instance();
	analysisManager->Reset();	
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
	auto analysisManager = G4AnalysisManager::Instance();
  	analysisManager->Write();
  	analysisManager->CloseFile(false);
}