#ifndef Run_h
#define Run_h 1

#include "G4Run.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"

class Run : public G4Run {

  public:

    Run();
    ~Run();

    virtual void RecordEvent( const G4Event* anEvent ) override;
    virtual void Merge( const G4Run* aRun ) override;

    void PrintInfo() const;

    void SetPrimaryParticleId( const G4int inputValue ) { fPrimaryParticleId = inputValue; }
    void SetPrimaryParticleInitialKineticEnergy( const G4double inputValue )
      { fPrimaryParticleInitialKineticEnergy = inputValue; }
    void SetPrimaryParticleInitialTotalEnergy( const G4double inputValue )
      { fPrimaryParticleInitialTotalEnergy = inputValue; }
    void SetPrimaryParticleInitialMomentum( const G4double inputValue )
      { fPrimaryParticleInitialMomentum = inputValue; }
    void SetPrimaryParticleInitial3Momentum( const G4ThreeVector& inputValue )
      { fPrimaryParticleInitial3Momentum = inputValue; }
    void SetPrimaryParticleInitialPosition( const G4ThreeVector& inputValue )
      { fPrimaryParticleInitialPosition = inputValue; }
    void SetIsPreassignedDecayEnabled( const G4bool inputValue )
      { fIsPreassignedDecayEnabled = inputValue; }
    void SetIsBoostToLabEnabled( const G4bool inputValue ) { fIsBoostToLabEnabled = inputValue; }

    G4int    GetPrimaryParticleId() const { return fPrimaryParticleId; }
    G4double GetPrimaryParticleInitialKineticEnergy() const
      { return fPrimaryParticleInitialKineticEnergy; }
    G4double GetPrimaryParticleInitialTotalEnergy() const
      { return fPrimaryParticleInitialTotalEnergy; }
    G4double GetPrimaryParticleInitialMomentum() const
      { return fPrimaryParticleInitialMomentum; }
    G4ThreeVector GetPrimaryParticleInitial3Momentum() const
      { return fPrimaryParticleInitial3Momentum; }
    G4ThreeVector GetPrimaryParticleInitialPosition() const
      { return fPrimaryParticleInitialPosition; }
    G4bool   GetIsPreassignedDecayEnabled() const { return fIsPreassignedDecayEnabled; }
    G4bool   GetIsBoostToLabEnabled() const { return fIsBoostToLabEnabled; }

    void IncrementNumberDecays() { ++fNumDecays; }
    G4int GetNumberDecays() const { return fNumDecays; };

    void SetDecayX( const G4double inputValue );
    void SetDecayY( const G4double inputValue );
    void SetDecayZ( const G4double inputValue );

  private:

    G4int fNumEvents;

    G4int fPrimaryParticleId;
    G4double fPrimaryParticleInitialKineticEnergy;
    G4double fPrimaryParticleInitialTotalEnergy;
    G4double fPrimaryParticleInitialMomentum;
    G4ThreeVector fPrimaryParticleInitial3Momentum;
    G4ThreeVector fPrimaryParticleInitialPosition;
    G4bool fIsPreassignedDecayEnabled;
    G4bool fIsBoostToLabEnabled;

    G4int fNumDecays;
    G4double fDecayX;
    G4double fDecayY;
    G4double fDecayZ;
};

#endif
