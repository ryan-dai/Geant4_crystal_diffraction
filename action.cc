#include "action.hh"

MyActionInitialization::MyActionInitialization()
{
}

MyActionInitialization::~MyActionInitialization()
{
}


//using Multithread, we then will need the buildformaster function inside our folder
void MyActionInitialization::BuildForMaster() const
{
    MyRunAction *runAction = new MyRunAction();
    SetUserAction(runAction);  //make sure the runAction is started in this thread
}


void MyActionInitialization::Build() const
{
    PrimaryGeneratorAction *generator = new PrimaryGeneratorAction();
    SetUserAction(generator);

    MyRunAction *runAction = new MyRunAction();

    SetUserAction(runAction);
}
