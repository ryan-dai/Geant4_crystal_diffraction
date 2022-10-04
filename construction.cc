#include "construction.hh"


// //B1DetectorConstruction.cc
//   #include CADMesh.hh

//   //....

//   // CADMesh :: STL
//   auto bunny_mesh = CADMesh::TessellatedMesh::FromSTL("./bunny.stl");
//   auto bunny_logical = new G4LogicalVolume( bunny_mesh->GetSolid() 
//                                            , water
//                                            , "logical"
//                                            , 0, 0, 0
//                                             );
//   new G4PVPlacement( 0
//                    , G4ThreeVector()
//                    , bunny_logical
//                    , "physical"
//                    , logicWorld
//                    , false, 0
//                      );

MyDetectorConstruction::MyDetectorConstruction()
{
    fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");

    fMessenger->DeclareProperty("nCols", nCols, "Number of columns");
    fMessenger->DeclareProperty("nRows", nRows, "Number of rows");

    nCols = 50;
    nRows = 50;

    DefineMaterials();
}

MyDetectorConstruction::~MyDetectorConstruction()
{
}

void MyDetectorConstruction::DefineMaterials()
{
    G4NistManager *nist = G4NistManager::Instance();

    G4double A = 12.01 * g/mole;
    G4double Z = 6;
    G4double density;
    G4double pressure;
    G4double temperature;


    diamond = new G4Material("diamond", Z, A, 3.515*g/cm3);

    // tungsten = new G4Material("tungsten",Z=74., A= 183.85*g/mole, 19.30*g/cm3);
    // materials parameters
    SiO2 = new G4Material("SiO2", 2.201 * g / cm3, 2);
    SiO2->AddElement(nist->FindOrBuildElement("Si"), 1);
    SiO2->AddElement(nist->FindOrBuildElement("O"), 2);

    H2O = new G4Material("H2O", 1.000 * g / cm3, 2);
    H2O->AddElement(nist->FindOrBuildElement("H"), 2);
    H2O->AddElement(nist->FindOrBuildElement("O"), 1);


    elC = nist->FindOrBuildElement("C");


    Aerogel = new G4Material("Aerogel", 0.200 * g / cm3, 3);
    Aerogel->AddMaterial(SiO2, 62.5 * perCent);
    Aerogel->AddMaterial(H2O, 37.4 * perCent);
    Aerogel->AddElement(elC, 0.1 * perCent);

    Lead = nist->FindOrBuildMaterial("G4_Pb");
    tungsten = nist->FindOrBuildMaterial("G4_W");
    worldMat = nist->FindOrBuildMaterial("G4_AIR");
    aluminum = nist->FindOrBuildMaterial("G4_Al");

    density     = universe_mean_density; 
    pressure    = 3.e-18*pascal;
    temperature = 2.73*kelvin;
    vacuum= new G4Material("vacuum", Z=1, A=1.01*g/mole,density,
                 kStateGas,temperature,pressure);


}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{



    // refraction index

    G4double energy[2] = {1.239841939*eV/0.9, 11.239841939*eV/0.2};
    G4double rindexAerogel[2] = {1.1, 1.1};
    G4double rindexWorld[2] = {1.0, 1.0};

    G4MaterialPropertiesTable *mptAerogel = new G4MaterialPropertiesTable();
    mptAerogel->AddProperty("RINDEX", energy, rindexAerogel, 2);

    Aerogel->SetMaterialPropertiesTable(mptAerogel);

    // G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
    mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);

    worldMat->SetMaterialPropertiesTable(mptWorld);

    G4double xWorld =5.*mm;   //half width
    G4double yWorld =5.*mm;
    G4double zWorld =10.*mm;


    solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);   //size

    logicWorld = new G4LogicalVolume(solidWorld, vacuum, "logicWorld"); //material

    physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true); //position

    // solidRadiator = new G4Box("solidRadiator", 1.5 * mm, 1.5 * mm, 1. * mm);
    // logicRadiator = new G4LogicalVolume(solidRadiator, diamond, "logicRadiator");
    // // G4VPhysicalVolume *physRadiator = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.25*m),logicRadiator,"physRadiator",logicWorld,false, 0, true);
    // physRadiator = new G4PVPlacement(0, G4ThreeVector(0., 0., 1.*mm), logicRadiator, "physRadiator", logicWorld, false, 0, true);
    // G4VisAttributes* ScreenVisAtt= new G4VisAttributes(G4Colour(0.0,1.0,1.0));
    // ScreenVisAtt->SetForceSolid(true);
    // logicRadiator -> SetVisAttributes(ScreenVisAtt);

    solidRadiator1 = new G4Box("solidRadiator1", 1.5 * mm, 1.5 *mm, 2.*um);
    logicRadiator1 = new G4LogicalVolume(solidRadiator1, tungsten, "logicRadiator1");
    // G4VPhysicalVolume *physRadiator = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.25*m),logicRadiator,"physRadiator",logicWorld,false, 0, true);
    physRadiator1 = new G4PVPlacement(0, G4ThreeVector(0., 0., -2.*um), logicRadiator1, "physRadiator1", logicWorld, false, 0, true);
    G4VisAttributes* ScreenVisAtt1= new G4VisAttributes(G4Colour(1.0,0.0,1.0));
    ScreenVisAtt1->SetForceSolid(true);
    logicRadiator1 -> SetVisAttributes(ScreenVisAtt1);


    // solidFilter = new G4Box("solidFilter", 5. * mm, 5. *mm, 1.5*mm);
    // logicFilter = new G4LogicalVolume(solidFilter, aluminum, "logicFilter");
    // // G4VPhysicalVolume *physRadiator = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.25*m),logicRadiator,"physRadiator",logicWorld,false, 0, true);
    // physFilter = new G4PVPlacement(0, G4ThreeVector(0., 0., 8.3*mm), logicFilter, "physFilter", logicWorld, false, 0, true);
    // G4VisAttributes* ScreenVisAtt2= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
    // ScreenVisAtt2->SetForceSolid(true);
    // logicFilter -> SetVisAttributes(ScreenVisAtt2);

    solidDetector = new G4Box("solidDetector", xWorld/nRows, yWorld/nCols, 0.1*mm);// it's an array type detector for the X-ray source

    logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");

    for(G4int i = 0; i < nRows; i++)
    {
        for(G4int j = 0; j < nCols; j++)
        {
            physDetector = new G4PVPlacement(0, G4ThreeVector(-0.5*cm+(i+0.5)*cm/nRows, -.5*cm+(j+0.5)*cm/nCols, 9.9*mm), logicDetector, "physDetector", logicWorld, false, j+i*nCols, true);
        }
    }


    fScoringVolume = logicRadiator1;

    return physWorld;
}

void MyDetectorConstruction ::ConstructSDandField()
{
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

    logicDetector->SetSensitiveDetector(sensDet);
}