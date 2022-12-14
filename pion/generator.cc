#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName = "pi-";
    G4ParticleDefinition *particle = particleTable->FindParticle("pi-");

    G4ThreeVector pos(0.,0.,-50.*m);
    G4ThreeVector mom(0.,0.,1.);

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleMomentum(10.*GeV);
    fParticleGun->SetParticleDefinition(particle);

    fParticleGun->GeneratePrimaryVertex(anEvent);
}
