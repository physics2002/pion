#include "Run.hh"
#include "G4SystemOfUnits.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"

Run::Run() : G4Run(),
             fNumEvents( 0 ),
             fPrimaryParticleId( 0 ),
             fPrimaryParticleInitialKineticEnergy( 0.0 ),
             fPrimaryParticleInitialTotalEnergy( 0.0 ),
             fPrimaryParticleInitialMomentum( 0.0 ),
             fPrimaryParticleInitial3Momentum( G4ThreeVector() ),
             fPrimaryParticleInitialPosition( G4ThreeVector() ),
             fIsPreassignedDecayEnabled( true ),
             fIsBoostToLabEnabled( true ),
             fNumDecays( 0 ) {}

Run::~Run() {}

void Run::RecordEvent( const G4Event* anEvent ) {
  G4int nEvt = anEvent->GetEventID();
  G4Run::RecordEvent( anEvent );  
}

void Run::Merge( const G4Run* aRun ) {

  const Run* localRun = static_cast< const Run* >( aRun );
  fNumEvents += localRun->GetNumberOfEvent();

  fPrimaryParticleId = localRun->GetPrimaryParticleId();
  fPrimaryParticleInitialKineticEnergy = localRun->GetPrimaryParticleInitialKineticEnergy();
  fPrimaryParticleInitialTotalEnergy = localRun->GetPrimaryParticleInitialTotalEnergy();
  fPrimaryParticleInitialMomentum = localRun->GetPrimaryParticleInitialMomentum();
  fPrimaryParticleInitial3Momentum = localRun->GetPrimaryParticleInitial3Momentum();
  fPrimaryParticleInitialPosition = localRun->GetPrimaryParticleInitialPosition();
  fIsPreassignedDecayEnabled = localRun->GetIsPreassignedDecayEnabled();
  fIsBoostToLabEnabled = localRun->GetIsBoostToLabEnabled();

  fNumDecays += localRun->GetNumberDecays();

  G4Run::Merge( aRun );
}

void Run::PrintInfo() const {

  const G4double femtosecond = 0.001 * CLHEP::picosecond;
  const G4double NN = ( fNumDecays > 0 ? G4double( fNumDecays ) : 1.0 );
  G4cout << std::setprecision(6)
         << G4endl << G4endl
         << " ============ Run::printInfo() =============== \t RunID = " << GetRunID() << G4endl
         << " primary PDG code                     = " << fPrimaryParticleId << G4endl
         << " primary initial kinetic energy [GeV] = "
         << fPrimaryParticleInitialKineticEnergy / CLHEP::GeV << G4endl
         << " primary initial total energy [GeV]   = "
         << fPrimaryParticleInitialTotalEnergy / CLHEP::GeV << G4endl
         << " primary initial momentum [GeV]       = "
         << fPrimaryParticleInitialMomentum / CLHEP::GeV << G4endl
         << " primary initial 3 momentum [GeV]     = "
         << fPrimaryParticleInitial3Momentum / CLHEP::GeV << G4endl
         << " primary initial position [mm]        = "
         << fPrimaryParticleInitialPosition << G4endl
         << ( fNumEvents > 0 ? fNumEvents : GetNumberOfEvent() ) << G4endl
         << " # Decays               = " << fNumDecays << G4endl
         << " ============================================= " << G4endl
         << G4endl;
}

void Run::SetDecayX( const G4double inputValue ) {
  fDecayX = inputValue;
}

void Run::SetDecayY( const G4double inputValue ) {
  fDecayY = inputValue;
}

void Run::SetDecayZ( const G4double inputValue ) {
  fDecayZ = inputValue;
}











