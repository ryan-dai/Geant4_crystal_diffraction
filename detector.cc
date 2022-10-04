#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{
}

MySensitiveDetector::~MySensitiveDetector()
{
}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    G4Track *track = aStep->GetTrack();

    track->SetTrackStatus(fStopAndKill);

    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();



    G4ThreeVector posPhoton = preStepPoint->GetPosition();

    G4ThreeVector momPhoton = preStepPoint->GetMomentum(); //calculate the photon wavelength
    G4double kinePhoton = preStepPoint->GetKineticEnergy();

    G4double wlen =(1.239841939*eV/momPhoton.mag())*1E+03;
    
    // G4cout << "Photon position: " << posPhoton << G4endl;

    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();

    G4int copyNo = touchable->GetCopyNumber();

    // G4cout << "Copy number: " << copyNo << G4endl;
    G4VPhysicalVolume *physVol = touchable->GetVolume();

    G4ThreeVector posDetector = physVol->GetTranslation();

    #ifndef G4MULTITHREADED
        G4cout << "Detector position: " << posDetector << G4endl;
    #endif


    G4int evt =G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

        G4AnalysisManager *man = G4AnalysisManager ::Instance();
    man->FillNtupleIColumn(0, evt);
    man->FillNtupleDColumn(1, posDetector[0]);
    man->FillNtupleDColumn(2, posDetector[1]);
    man->FillNtupleDColumn(3, posDetector[2]);
    man->FillNtupleDColumn(4, kinePhoton);
    man->AddNtupleRow(0);     //it's 0 Ntuple

    // G4AnalysisManager *man = G4AnalysisManager ::Instance();
    // man->FillNtupleIColumn(0, evt);
    // man->FillNtupleDColumn(1, posDetector[0]);
    // man->FillNtupleDColumn(2, posDetector[1]);
    // man->FillNtupleDColumn(3, posDetector[2]);
    // man->AddNtupleRow(0);     //it's 0 Ntuple

//       analysisManager->FillH1(1,ekin);
//   if (dv > 0.) analysisManager->FillH1(2, r, 1./dv);  
//   analysisManager->FillH1(3,cost);  
//   analysisManager->FillH1(4,phi);    
//   analysisManager->FillH2(1,x,y);
//   analysisManager->FillH2(2,y,z);
//   analysisManager->FillH2(3,z,x);      
//   analysisManager->FillH2(4,phi,cost);
//   analysisManager->FillH2(5,phi,theta);
  


    if (!fScoringVolume) 
    { 
     const B1DetectorConstruction* detectorConstruction
         = static_cast<const B1DetectorConstruction>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
        fScoringVolume = detectorConstruction->GetScoringVolume();
     }

    G4LogicalVolume* preStepPointVolume = preStepPoint->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
    G4LogicalVolume* postStepPointVolume = postStepPoint->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
    if(preStepPointVolume != fScoringVolume && postStepPointVolume == fScoringVolume){
        G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
        analysisManager->FillH1(1, preStepPoint->GetTotalEnergy() / keV);
        analysisManager->FillH1(2, preStepPoint->GetKineticEnergy() / keV);


//     void B1SteppingAction::UserSteppingAction(const G4Step* step)
// {
//   if (!fScoringVolume) { 
//     const B1DetectorConstruction* detectorConstruction
//       = static_cast<const B1DetectorConstruction>
//         (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
//     fScoringVolume = detectorConstruction->GetScoringVolume();
//   }

//   G4StepPoint preStepPoint = step->GetPreStepPoint();
//   G4StepPoint* postStepPoint = step->GetPostStepPoint();


//  if(postStepPoint->GetStepStatus() == fGeomBoundary){
//     G4LogicalVolume* preStepPointVolume = preStepPoint->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
//     G4LogicalVolume* postStepPointVolume = postStepPoint->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
//     if(preStepPointVolume != fScoringVolume && postStepPointVolume == fScoringVolume){
//         G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
//         analysisManager->FillH1(1, preStepPoint->GetTotalEnergy() / keV);
//         analysisManager->FillH1(2, preStepPoint->GetKineticEnergy() / keV);
//     }
//  }


}
