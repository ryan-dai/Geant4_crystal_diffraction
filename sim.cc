#include <iostream>


#include "G4Types.hh"

#include "G4RunManagerFactory.hh"

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4VisManager.hh"
#include "G4UImanager.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "construction.hh"
#include "physics.hh"
// #include "action.hh"
#include "ActionInitialization.hh"


int main(int argc, char **argv)
{
	
	G4UIExecutive *ui = 0;

	#ifdef G4MULTITHREADED
		G4MTRunManager *runManager= new G4MTRunManager();
	#else
		G4RunManager *runManager = new G4RunManager();
	#endif

 
	// G4RunManager *runManager = new G4RunManager();

	runManager->SetUserInitialization(new MyDetectorConstruction());
	runManager->SetUserInitialization(new MyPhysicsList());
	// runManager->SetUserInitialization(new MyActionInitialization());
	runManager->SetUserInitialization(new ActionInitialization());




	// runManager->Initialize();  
	//when using mutlithread function, this part should be done in the command file to aviod abruption and crash,
	//it's moved to the .mac file


	// G4UIExecutive *ui = new G4UIExecutive(argc,argv);


	if (argc == 1)
	{
		ui = new G4UIExecutive(argc, argv);
	}
	G4VisManager *visManager = new G4VisExecutive();

	visManager->Initialize();
	G4UImanager *UImanager = G4UImanager::GetUIpointer();

	if (ui)
	{
		UImanager->ApplyCommand("/control/execute vis.mac"); //tell the G4 to execute the vis.mac file

		// UImanager->ApplyCommand("/vis/open OGL");
		// UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
		// UImanager->ApplyCommand("/vis/drawVolume");
		// UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
		// UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
		// UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");

		ui->SessionStart();
	}
	else
	{
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command + fileName);    //run the command .mac file.

	}
	return 0;
}