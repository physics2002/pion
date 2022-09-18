#include "const.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
      G4bool checkOverlaps = true;


  const G4double halfLength = 100.0*m;
  const G4double expHall_x = 1.01*halfLength;  // half dimension along x
  const G4double expHall_y = 1.01*halfLength;  // half dimension along y
  const G4double expHall_z = 1.01*halfLength;  // half dimension along z
fTargetMaterial = G4NistManager::Instance()->FindOrBuildMaterial( "G4_Galactic" );

  G4Material* vacuum = G4NistManager::Instance()->FindOrBuildMaterial( "G4_Galactic" );
  G4Box* experimentalHallBox = new G4Box( "expHallBox", expHall_x, expHall_y, expHall_z );
  fLogicExperimentalHall = new G4LogicalVolume( experimentalHallBox,  // solid
                                                vacuum,               // material
                                                "logicExpHall",       // name
                                                0,                    // field manager
                                                0,                    // sensitive detector
                                                0 );                  // user limits
  fPhysExperimentalHall = new G4PVPlacement( 0,                       // rotation
                                             G4ThreeVector(),         // translation
                                             "expHall",               // name
                                             fLogicExperimentalHall,  // logical volume
                                             0,                       // mother physical volume
                                             false,                   // boolean operation
                                             0 );                     // copy number
  G4Tubs* solidTargetLayer = new G4Tubs( "solidTargetLayer",
                                         1.*m,          // inner radius
                                         1.01*m,          // outer radius
                                         50.*m,                  // half cylinder length in z
                                         0.0 *degree,                         // starting phi angle in rad
                                         360 *degree );                    // final phi angle in rad
  fLogicTargetLayer = new G4LogicalVolume( solidTargetLayer,          // solid
                                           fTargetMaterial,           // material
                                           "logicTargetLayer",        // name
                                           0,                         // field manager
                                           0,                         // sensitive detector
                                           0 );                       // user limits
fPhysTargetLayer = new G4PVPlacement( 0,                            // rotation
                                        G4ThreeVector(),              // translation
                                        "physTargetLayer",            // name
                                        fLogicTargetLayer,            // logical volume
                                        fPhysExperimentalHall,        // mother physical volume
                                        false,                        // boolean operation
                                        0,
                                        checkOverlaps);                          // copy number
    G4Material *tubeMatFe = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");

  G4Tubs* solidTargetLayer1 = new G4Tubs( "solidTargetLayer1",
                                         0.*m,          // inner radius
                                         1.*m,          // outer radius
                                         25.*m,                  // half cylinder length in z
                                         0 *degree,                         // starting phi angle in rad
                                         360* degree );                    // final phi angle in rad
  fLogicTargetLayer1 = new G4LogicalVolume( solidTargetLayer1,          // solid
                                           tubeMatFe,           // material
                                           "fLogicTargetLayer1",        // name
                                           0,                         // field manager
                                           0,                         // sensitive detector
                                           0 );                       // user limits
fPhysTargetLayer1 = new G4PVPlacement( 0,                            // rotation
                                        G4ThreeVector(0,0,75*m),              // translation
                                        "physTargetLayer1",            // name
                                        fLogicTargetLayer1,            // logical volume
                                        fPhysExperimentalHall,        // mother physical volume
                                        false,                        // boolean operation
                                        0,
                                        checkOverlaps);                          // copy number    

    G4Material *det_mat = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");

  G4Tubs* solidTargetLayer2 = new G4Tubs( "solidTargetLayer2",
                                         0.*m,          // inner radius
                                         1.*m,          // outer radius
                                         0.5*m,                  // half cylinder length in z
                                         0 *degree,                         // starting phi angle in rad
                                         360 *degree );                    // final phi angle in rad
  fLogicTargetLayer2 = new G4LogicalVolume( solidTargetLayer2,          // solid
                                           det_mat,           // material
                                           "logicTargetLayer2",        // name
                                           0,                         // field manager
                                           0,                         // sensitive detector
                                           0 );                       // user limits
fPhysTargetLayer2 = new G4PVPlacement( 0,                            // rotation
                                        G4ThreeVector(0,0,100.5*m),              // translation
                                        "physTargetLayer2",            // name
                                        fLogicTargetLayer2,            // logical volume
                                        fPhysExperimentalHall,        // mother physical volume
                                        false,                        // boolean operation
                                        0,
                                        checkOverlaps);                          // copy number    





  return fPhysExperimentalHall;
}

//void ExG4DetectprConstr
