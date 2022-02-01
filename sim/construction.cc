#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    G4NistManager *nist = G4NistManager::Instance();
    
    // Cherenkov
    //G4Material *SiO2 = new G4Material("SiO2", 2.201*g/cm3, 2);
    //SiO2->AddElement(nist->FindOrBuildElement("Si"), 1);
    //SiO2->AddElement(nist->FindOrBuildElement("O"), 2);
    
    //G4Material *H2O = new G4Material("H2O", 1.000*g/cm3, 2);
    //H2O->AddElement(nist->FindOrBuildElement("H"), 2);
    //H2O->AddElement(nist->FindOrBuildElement("O"), 1);
    
    //G4Element *C = nist->FindOrBuildElement("C");
    
    //G4Material *Aerogel = new G4Material("Aerogel", 0.200*g/cm3, 3);
    //Aerogel->AddMaterial(SiO2, 62.5*perCent);
    //Aerogel->AddMaterial(H2O, 37.4*perCent);
    //Aerogel->AddElement(C, 0.1*perCent);
        
    G4double energy[2] = {1.239841939*eV/0.9, 1.239841939*eV/0.2};
    //G4double rindexAerogel[2] = {1.1, 1.1};
    G4double rindexWorld[2] = {1.0, 1.0};
    
    //G4MaterialPropertiesTable *mptAerogel = new G4MaterialPropertiesTable();
    //mptAerogel->AddProperty("RINDEX", energy, rindexAerogel, 2);
    
    //Aerogel->SetMaterialPropertiesTable(mptAerogel);
    
    // BGO
    G4Material *BGO = nist->FindOrBuildMaterial("G4_BGO");
    
    // World
    //G4VisAttributes::SetVisibility
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
    
    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
    mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);
    
    worldMat->SetMaterialPropertiesTable(mptWorld);
    
    G4Box *solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);
    
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
        
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
    
    // Aerogel Placement
    //G4Box *solidRadiator = new G4Box("solidRadiator", 0.4*m, 0.4*m, 0.01*m);
    //G4LogicalVolume *logicRadiator = new G4LogicalVolume(solidRadiator, Aerogel, "logicalRadiator");
    //new G4PVPlacement(0, G4ThreeVector(0., 0., 0.25*m), logicRadiator, "physRadiator", logicWorld, false, 0, true);
    
    // BGO placement
    G4Box *solidBGO1 = new G4Box("solidBGO1", 0.5*m, 0.5*m, 0.05*m);
    G4LogicalVolume *logicBGO1 = new G4LogicalVolume(solidBGO1, BGO, "logicalBGO1");
    new G4PVPlacement(0, G4ThreeVector(0., 0., 0.45*m), logicBGO1, "physBGO1", logicWorld, false, 0, true);
    
    G4Box *solidBGO2 = new G4Box("solidBGO2", 0.5*m, 0.5*m, 0.05*m);
    G4LogicalVolume *logicBGO2 = new G4LogicalVolume(solidBGO2, BGO, "logicalBGO2");
    new G4PVPlacement(0, G4ThreeVector(0., 0., -0.45*m), logicBGO2, "physBGO2", logicWorld, false, 0, true);

    G4Box *solidBGO3 = new G4Box("solidBGO3", 0.5*m, 0.05*m, 0.5*m);
    G4LogicalVolume *logicBGO3 = new G4LogicalVolume(solidBGO3, BGO, "logicalBGO3");
    new G4PVPlacement(0, G4ThreeVector(0., 0.45*m, 0.), logicBGO3, "physBGO3", logicWorld, false, 0, true);

    G4Box *solidBGO4 = new G4Box("solidBGO4", 0.5*m, 0.05*m, 0.5*m);
    G4LogicalVolume *logicBGO4 = new G4LogicalVolume(solidBGO4, BGO, "logicalBGO4");
    new G4PVPlacement(0, G4ThreeVector(0., -0.45*m, 0.), logicBGO4, "physBGO4", logicWorld, false, 0, true);

    G4Box *solidBGO5 = new G4Box("solidBGO5", 0.05*m, 0.5*m, 0.5*m);
    G4LogicalVolume *logicBGO5 = new G4LogicalVolume(solidBGO5, BGO, "logicalBGO5");
    new G4PVPlacement(0, G4ThreeVector(0.45*m, 0., 0.), logicBGO5, "physBGO5", logicWorld, false, 0, true);

    G4Box *solidBGO6 = new G4Box("solidBGO6", 0.05*m, 0.5*m, 0.5*m);
    G4LogicalVolume *logicBGO6 = new G4LogicalVolume(solidBGO6, BGO, "logicalBGO6");
    new G4PVPlacement(0, G4ThreeVector(-0.45*m, 0., 0.), logicBGO6, "physBGO6", logicWorld, false, 0, true);

    
    return physWorld;
}