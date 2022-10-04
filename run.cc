#include "run.hh"

MyRunAction::MyRunAction()
{
    G4AnalysisManager *man = G4AnalysisManager ::Instance();


    //don't want to creat new Ntuple whenever run starts
    
    man->CreateNtuple("Hits", "Hits");
    man->CreateNtupleIColumn("fEvent"); // I standards for integer, event number is integer
    man->CreateNtupleDColumn("fX");     // coordinates our detector file, or we add detector number
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    man->FinishNtuple(0); // Nutuple number 0, we can create as many tuple as we want.
}

MyRunAction::~MyRunAction()
{
}

void MyRunAction::BeginOfRunAction(const G4Run *run)
{
    G4AnalysisManager *man = G4AnalysisManager ::Instance();
    // auto analysisManager = G4AnalysisManager ::Instance();
    // analysisManager->FinishNtuple(0);
    G4int runID = run->GetRunID();

    std::stringstream strRunID;
    strRunID << runID;

    man->OpenFile("output" + strRunID.str() + ".root");

    // man->CreateNtuple("Hits","Hits");    
    // man->CreateNtupleIColumn("fEvent");  //I standards for integer, event number is integer
    // man->CreateNtupleDColumn("fX");       //coordinates our detector file, or we add detector number
    // man->CreateNtupleDColumn("fY");
    // man->CreateNtupleDColumn("fZ");
    // man->FinishNtuple(0);                  //Nutuple number 0, we can create as many tuple as we want.
}

void MyRunAction::EndOfRunAction(const G4Run *)
{
    G4AnalysisManager *man = G4AnalysisManager ::Instance();
    // auto analysisManager = G4AnalysisManager ::Instance();

    man->Write();
    man->CloseFile();
}
