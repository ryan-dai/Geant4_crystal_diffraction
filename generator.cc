#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);     // this part will only run whenever it starts and can be overwritten later if using macro files
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();

    G4String particleName = "e-";
    G4ParticleDefinition *particle = particleTable->FindParticle("e-");

    G4ThreeVector pos(0., 0., 0.);
    G4ThreeVector mom(0., 0., 1.);

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleMomentum(100. * GeV);
    fParticleGun->SetParticleDefinition(particle);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent) // this is method, macra file can override this parameters listed here.
{
    // G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();

    // G4String particleName = "proton";
    // G4ParticleDefinition *particle = particleTable->FindParticle("proton");

    // G4ThreeVector pos(0., 0., 0.);
    // G4ThreeVector mom(0., 0., 1.);

    // fParticleGun->SetParticlePosition(pos);
    // fParticleGun->SetParticleMomentumDirection(mom);
    // fParticleGun->SetParticleMomentum(100. * GeV);
    // fParticleGun->SetParticleDefinition(particle);

    fParticleGun->GeneratePrimaryVertex(anEvent);
}