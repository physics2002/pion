#ifndef SteppingAction_H
#define SteppingAction_H 1

#include "globals.hh"
#include "G4UserSteppingAction.hh"
#include "G4ThreeVector.hh"
#include "CLHEP/Units/SystemOfUnits.h"

class Run;

class SteppingAction : public G4UserSteppingAction {
  public:
    SteppingAction();
    virtual ~SteppingAction();

    virtual void UserSteppingAction( const G4Step* ) override;

    void Initialize();

    void SetRunPointer( Run* inputValue = nullptr ) { fRunPtr = inputValue; }
     
  private:

    G4bool IsPreassignedDecayEnabled() const { return fIsPreassignedDecayEnabled; }
    G4bool IsBoostToLabEnabled() const { return fIsBoostToLabEnabled; }

    const G4bool fIsPreassignedDecayEnabled = true;
    const G4bool fIsBoostToLabEnabled = true;

    Run* fRunPtr;

    G4int    fPrimaryParticleId;
    G4double fPrimaryParticleInitialKineticEnergy;
    G4double fPrimaryParticleInitialTotalEnergy;
    G4double fPrimaryParticleInitialMomentum;
    G4ThreeVector fPrimaryParticleInitial3Momentum;
    G4ThreeVector fPrimaryParticleInitialPosition;
};
#endif
