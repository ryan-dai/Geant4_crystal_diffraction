#ifndef RUN_HH
#define RUN_HH

// #include "g4root.hh"


#include "G4Run.hh"   //G4run as the title file
#include "G4AnalysisManager.hh"
// #include "G4VNtupleManager.hh"
// using G4AnalysisReader = G4Root AnalysisReader

#include "G4UserRunAction.hh"



class MyRunAction : public G4UserRunAction
{
    public:
        MyRunAction();
        ~MyRunAction();

        virtual void BeginOfRunAction(const G4Run*);
        virtual void EndOfRunAction(const G4Run*);
};

#endif