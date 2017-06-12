#include "TRexActionInitialization.hh"

#include "MiniBallHistoManager.hh"
#include "MiniBallHistoGenerator.hh"
#include "MiniBallRootGenerator.hh"

#include "TRexPrimaryGeneratorAction.hh"
#include "TRexRunAction.hh"
#include "TRexEventAction.hh"

TRexActionInitialization::TRexActionInitialization(TRexDetectorConstruction* detConst, TRexData* data, MiniBallHistoManager* histoMan) : G4VUserActionInitialization(), fDetConst(detConst), fData(data), fHistoMan(histoMan)
{

}

TRexActionInitialization::~TRexActionInitialization(){

}

void TRexActionInitialization::Build() const{
G4cout << "build for " << std::to_string(G4Threading::G4GetThreadId()) << G4endl;

// initalize Miniball
  std::string fName = "t" + std::to_string(G4Threading::G4GetThreadId()) + "_" + fData->GetOutputFileName();
  MiniBallRootGenerator* miniballHistoGen = new MiniBallRootGenerator(fName.c_str(), 5);
  MiniBallHistoManager* miniballHistoManager = new MiniBallHistoManager(miniballHistoGen);
  miniballHistoManager->SetMBTupleType(EVENT);
  miniballHistoManager->SetEnergyUnit(keV);

    // set mandatory user action class
    TRexPrimaryGeneratorAction* gen_action = new TRexPrimaryGeneratorAction();
    SetUserAction(gen_action);

    TRexEventAction* event_action = new TRexEventAction(fDetConst, miniballHistoManager);
    SetUserAction(event_action);

    TRexRunAction* run_action = new TRexRunAction(fData, gen_action, event_action);
    SetUserAction(run_action);
}

void TRexActionInitialization::BuildForMaster() const{
    TRexPrimaryGeneratorAction* gen_action = new TRexPrimaryGeneratorAction;

    TRexEventAction* event_action = new TRexEventAction(fDetConst, fHistoMan);

    TRexRunAction* run_action = new TRexRunAction(fData, gen_action, event_action);
    SetUserAction(run_action);
}
