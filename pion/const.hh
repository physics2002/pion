#ifndef CONST_HH
#define CONST_HH

#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4Tubs.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();

    virtual G4VPhysicalVolume *Construct();

private:
    G4Material* fTargetMaterial;
    G4LogicalVolume* fLogicExperimentalHall;
    G4VPhysicalVolume* fPhysExperimentalHall;
    G4LogicalVolume*  fLogicTargetLayer;
    G4VPhysicalVolume* fPhysTargetLayer;
    G4LogicalVolume*  fLogicTargetLayer1;
    G4VPhysicalVolume* fPhysTargetLayer1;
    G4LogicalVolume*  fLogicTargetLayer2;
    G4VPhysicalVolume* fPhysTargetLayer2;
};
#endif
