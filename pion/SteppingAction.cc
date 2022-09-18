#include "SteppingAction.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4StepPoint.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4LossTableManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4DecayProducts.hh"
#include "G4DecayTable.hh"
#include "G4VDecayChannel.hh"
#include "Run.hh"

SteppingAction::SteppingAction() : G4UserSteppingAction() {
  Initialize();
}

SteppingAction::~SteppingAction() {}

void SteppingAction::Initialize() {
  fRunPtr = nullptr;
  fPrimaryParticleInitialKineticEnergy = 0.0;
  fPrimaryParticleInitialTotalEnergy = 0.0;
  fPrimaryParticleInitialMomentum = 0.0;
  fPrimaryParticleInitial3Momentum = G4ThreeVector( 0.0, 0.0, 0.0 );
  fPrimaryParticleInitialPosition = G4ThreeVector( 0.0, 0.0, 0.0 );
}

void SteppingAction::UserSteppingAction( const G4Step* theStep ) {

  if ( theStep->GetTrack()->GetParentID() == 0  &&
       theStep->GetTrack()->GetCurrentStepNumber() == 1 ) {
    fPrimaryParticleId = theStep->GetTrack()->GetDefinition()->GetPDGEncoding();
    fPrimaryParticleInitialKineticEnergy = theStep->GetPreStepPoint()->GetKineticEnergy();
    fPrimaryParticleInitialTotalEnergy   = theStep->GetPreStepPoint()->GetTotalEnergy();
    fPrimaryParticleInitial3Momentum     = theStep->GetPreStepPoint()->GetMomentum();
    fPrimaryParticleInitialMomentum      = fPrimaryParticleInitial3Momentum.mag();
    fPrimaryParticleInitialPosition      = theStep->GetPreStepPoint()->GetPosition();

    if ( fRunPtr ) {
      fRunPtr->SetPrimaryParticleId( fPrimaryParticleId );
      fRunPtr->SetPrimaryParticleInitialKineticEnergy( fPrimaryParticleInitialKineticEnergy );
      fRunPtr->SetPrimaryParticleInitialTotalEnergy( fPrimaryParticleInitialTotalEnergy );
      fRunPtr->SetPrimaryParticleInitialMomentum( fPrimaryParticleInitialMomentum );
      fRunPtr->SetPrimaryParticleInitial3Momentum( fPrimaryParticleInitial3Momentum );
      fRunPtr->SetPrimaryParticleInitialPosition( fPrimaryParticleInitialPosition );
      fRunPtr->SetIsPreassignedDecayEnabled( IsPreassignedDecayEnabled() );  
      fRunPtr->SetIsBoostToLabEnabled( IsBoostToLabEnabled() );

    if ( IsPreassignedDecayEnabled()  &&
         ( ! theStep->GetTrack()->GetDefinition()->GetPDGStable() ) ) {
      G4DynamicParticle* dynamicParent =
        const_cast< G4DynamicParticle* >( theStep->GetTrack()->GetDynamicParticle() );
      if ( dynamicParent != nullptr ) {
        G4DecayProducts* decayProducts =
          (G4DecayProducts*)( dynamicParent->GetPreAssignedDecayProducts() );
        if ( decayProducts == nullptr ) {
          G4ParticleDefinition* parentDef = theStep->GetTrack()->GetDefinition();
          G4DecayTable* decayTable =
            ( parentDef == nullptr ? nullptr : parentDef->GetDecayTable() );
          if ( decayTable != nullptr ) {
            G4double parentMass = dynamicParent->GetMass();
            G4VDecayChannel* decayChannel = decayTable->SelectADecayChannel( parentMass );
            if ( decayChannel != nullptr ) {
              decayProducts = decayChannel->DecayIt( parentMass );
              if ( ! decayProducts->IsChecked() ) decayProducts->DumpInfo();
              if ( IsBoostToLabEnabled() ) {

                decayProducts->Boost( dynamicParent->GetTotalEnergy(),
                                      dynamicParent->GetMomentumDirection() );
              }
            } else {
              decayProducts = new G4DecayProducts( *dynamicParent );
            }
            dynamicParent->SetPreAssignedDecayProducts( decayProducts );
          }
        } else {
          G4cout << "WARNING : already present preassign decay !" << G4endl;
        }
      }
    }
  }


  if ( theStep->GetTrack()->GetParentID() == 0  &&
       theStep->GetPostStepPoint()->GetProcessDefinedStep() != nullptr  &&
       theStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName().find( "Decay" )
       != std::string::npos ) {

    const G4double ekin_dynamicParticle =
      theStep->GetTrack()->GetDynamicParticle()->GetKineticEnergy();
    const G4double ekin_val = ekin_dynamicParticle;

    const G4double etot_dynamicParticle =
      theStep->GetTrack()->GetDynamicParticle()->GetTotalEnergy();
    const G4double etot_val = etot_dynamicParticle;

    const G4double p_dynamicParticle =
      theStep->GetTrack()->GetDynamicParticle()->GetMomentum().mag();
    const G4double p_val = p_dynamicParticle;

    const G4ThreeVector pdir_dynamicParticle =
      theStep->GetTrack()->GetDynamicParticle()->GetMomentumDirection();

    const G4double mass_dynamicParticle = theStep->GetTrack()->GetDynamicParticle()->GetMass();
    const G4double mass_val = mass_dynamicParticle;

    const G4double xPos = theStep->GetPostStepPoint()->GetPosition().x();
    const G4double yPos = theStep->GetPostStepPoint()->GetPosition().y();
    const G4double zPos = theStep->GetPostStepPoint()->GetPosition().z();

    std::size_t nSec = theStep->GetNumberOfSecondariesInCurrentStep();
    const std::vector< const G4Track* >* ptrVecSecondaries = theStep->GetSecondaryInCurrentStep();

    G4double deltaE = 0.0, deltaPx = 0.0, deltaPy = 0.0, deltaPz = 0.0;
    if ( nSec > 0  &&  ptrVecSecondaries != nullptr ) {
      G4double sumEsecondaries = 0.0;
      G4ThreeVector sumPsecondaries( 0.0, 0.0, 0.0 );
      for ( std::size_t i = 0; i < nSec; ++i ) {
        if ( (*ptrVecSecondaries)[i] ) {
          sumEsecondaries += (*ptrVecSecondaries)[i]->GetTotalEnergy();
          sumPsecondaries += (*ptrVecSecondaries)[i]->GetMomentum();
        }
      }
      deltaE = sumEsecondaries - theStep->GetPostStepPoint()->GetTotalEnergy();
      
    if ( fRunPtr ) {
      fRunPtr->IncrementNumberDecays();
      fRunPtr->SetDecayX( xPos );
      fRunPtr->SetDecayY( yPos );
      fRunPtr->SetDecayZ( zPos );

    }

  }
}
}
}






