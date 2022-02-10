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
    
    // BGO Optical Properties (MPT)
    // Declare the MPT 
    G4MaterialPropertiesTable *BGO_mpt = new G4MaterialPropertiesTable();    
    
    // Define the energy region for optical properties
    G4double BGO_energy[3] = {1.9*eV, 2.6*eV, 3.3*eV}; //Not know how it works
    // Relative intensity of scintillation light over specified energy range
    G4double BGO_SCINT[3] = {0.1, 1., 0.1};
    // Refractive index of BGO
    G4double BGO_RINDEX[3] = {2.15, 2.15, 2.15};
    // Absorption length of BGO for optical photons
    G4double BGO_ABSL[3] = {1.118*cm, 1.118*cm, 1.118*cm}; //Not know how it works
    
    // Add properties to the MPT
    BGO_mpt->AddProperty("SCINTILLATIONCOMPONENT1", BGO_energy, BGO_SCINT, 3);
    // BGO_mt->AddProperty("SCINTILLATIONCOMPONENT2", BGO_energy, BGO_SCINT, 3); ???
    BGO_mpt->AddProperty("RINDEX", BGO_energy, BGO_RINDEX, 3);
    BGO_mpt->AddProperty("ABSLENGTH", BGO_energy, BGO_ABSL, 3);
    
    BGO_mpt->AddConstProperty("SCINTILLATIONYIELD", 8/keV);
    BGO_mpt->AddConstProperty("RESOLUTIONSCALE", 1.0);
    BGO_mpt->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 300.*ns);
    // BGO_mt->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 45.*ns); ???
    BGO_mpt->AddConstProperty("SCINTILLATIONYIELD1", 1.0);    
    
    // Attach material porperties table to the material
    BGO->SetMaterialPropertiesTable(BGO_mpt);
    
    
    // World
    //G4VisAttributes::SetVisibility
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
    
    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
    mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);
    
    worldMat->SetMaterialPropertiesTable(mptWorld);
    
    G4Box *solidWorld = new G4Box("solidWorld", 4*m, 4*m, 4*m);
    
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
        
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
    
    
    // Aerogel Placement
    //G4Box *solidRadiator = new G4Box("solidRadiator", 0.4*m, 0.4*m, 0.01*m);
    //G4LogicalVolume *logicRadiator = new G4LogicalVolume(solidRadiator, Aerogel, "logicalRadiator");
    //new G4PVPlacement(0, G4ThreeVector(0., 0., 0.25*m), logicRadiator, "physRadiator", logicWorld, false, 0, true);
    
    // BGO placement
    G4Box *solidBGO1 = new G4Box("solidBGO1", 15.*cm, 15.*cm, 2.5*cm);
    G4LogicalVolume *logicBGO1 = new G4LogicalVolume(solidBGO1, BGO, "logicalBGO1");
    new G4PVPlacement(0, G4ThreeVector(0., 0., 12.5*cm), logicBGO1, "physBGO1", logicWorld, false, 0, true);
    
    G4Box *solidBGO2 = new G4Box("solidBGO2", 15.*cm, 15.*cm, 2.5*cm);
    G4LogicalVolume *logicBGO2 = new G4LogicalVolume(solidBGO2, BGO, "logicalBGO2");
    new G4PVPlacement(0, G4ThreeVector(0., 0., -12.5*cm), logicBGO2, "physBGO2", logicWorld, false, 0, true);

    G4Box *solidBGO3 = new G4Box("solidBGO3", 15.*cm, 2.5*cm, 15.*cm);
    G4LogicalVolume *logicBGO3 = new G4LogicalVolume(solidBGO3, BGO, "logicalBGO3");
    new G4PVPlacement(0, G4ThreeVector(0., 12.5*cm, 0.), logicBGO3, "physBGO3", logicWorld, false, 0, true);

    G4Box *solidBGO4 = new G4Box("solidBGO4", 15.*cm, 2.5*cm, 15.*cm);
    G4LogicalVolume *logicBGO4 = new G4LogicalVolume(solidBGO4, BGO, "logicalBGO4");
    new G4PVPlacement(0, G4ThreeVector(0., -12.5*cm, 0.), logicBGO4, "physBGO4", logicWorld, false, 0, true);

    G4Box *solidBGO5 = new G4Box("solidBGO5", 2.5*cm, 15.*cm, 15.*cm);
    G4LogicalVolume *logicBGO5 = new G4LogicalVolume(solidBGO5, BGO, "logicalBGO5");
    new G4PVPlacement(0, G4ThreeVector(12.5*cm, 0., 0.), logicBGO5, "physBGO5", logicWorld, false, 0, true);

    G4Box *solidBGO6 = new G4Box("solidBGO6", 2.5*cm, 15.*cm, 15.*cm);
    G4LogicalVolume *logicBGO6 = new G4LogicalVolume(solidBGO6, BGO, "logicalBGO6");
    new G4PVPlacement(0, G4ThreeVector(-12.5*cm, 0., 0.), logicBGO6, "physBGO6", logicWorld, false, 0, true);
    
    // Array of photodetectors YouTube tutorial
    G4bool checkOverlaps = true;
    G4Box *solidDetector1 = new G4Box("solidDetector1", 0.05*m, 0.05*m, 0.1*m);
        
    // We had to add the logicDetector to the construction.hh ????????
    logicDetector1 = new G4LogicalVolume(solidDetector1, worldMat, "logicDetector1");
    
    for(G4int i = 0; i < 80; i++)
    {
        for(G4int j = 0; j < 80; j++)
        {
            new G4PVPlacement(0, G4ThreeVector(-3.995*m+(i+0.5)*m/10, -3.995*m+(j+0.5)*m/10, 3.90*m), logicDetector1, "physDetector1", logicWorld, false, j+i*1, checkOverlaps); // Gives some overlaps, maybe check. I could not find them.
        }
    }
    
    
    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField() // This won't work if the logicDetector is not defined in the header file!
{
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
    
    logicDetector1->SetSensitiveDetector(sensDet);
}