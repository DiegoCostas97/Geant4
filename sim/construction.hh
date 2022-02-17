#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "G4PhysicalConstants.hh"

#include "detector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
	MyDetectorConstruction();
	~MyDetectorConstruction();
	
	virtual G4VPhysicalVolume *Construct();

private:
	G4LogicalVolume *logicDetector1;
	G4LogicalVolume *logicDetector2;
	G4LogicalVolume *logicDetector3;
	G4LogicalVolume *logicDetector4;
	G4LogicalVolume *logicDetector5;
	G4LogicalVolume *logicDetector6;
	virtual void ConstructSDandField();
};

#endif