/*
 * TRexRunAction.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRexRunAction.hh"
#include "TRexSettings.hh"

#include "G4Threading.hh"

TRexRunAction::TRexRunAction() {
}

TRexRunAction::TRexRunAction(TRexData* data, TRexPrimaryGeneratorAction* generator, TRexEventAction* eventAction) :
	fData(data), fGenerator(generator), fEventAction(eventAction) {
}

TRexRunAction::~TRexRunAction() {
	// TODO Auto-generated destructor stub
}

void TRexRunAction::BeginOfRunAction(const G4Run*) {
        //if (!IsMaster()){
		// open result Root file
		std::string fName = "t" + std::to_string(G4Threading::G4GetThreadId()) + "_" + fData->GetOutputFileName();
		//std::string fName = "out.root";
		fOutputFile = new TFile(fName.c_str(), "recreate");
		fOutputFile->cd();

		// create trees
		fGeneratorTree = new TTree("treeGen", "Primary generator tree");
		fDetectorTree = new TTree("treeDet", "Detector tree");

		// set the trees
		fGenerator->SetTree(fGeneratorTree);
		fEventAction->SetTree(fDetectorTree);
		fEventAction->CreateBranches();

		// write the settings
		TRexSettings::Get()->Write("settings",TObject::kOverwrite);
        //}
}


void TRexRunAction::EndOfRunAction(const G4Run*) {
    //if (!IsMaster()){
	G4cout << std::to_string(G4Threading::G4GetThreadId()) << " a" << G4endl;
 	fOutputFile->cd();
	G4cout << std::to_string(G4Threading::G4GetThreadId()) << " b" << G4endl;
	fGeneratorTree->Write();
	G4cout << std::to_string(G4Threading::G4GetThreadId()) << " c" << G4endl;
	fDetectorTree->Write();
	G4cout << std::to_string(G4Threading::G4GetThreadId()) << " d" << G4endl;

	fOutputFile->Close();
	G4cout << std::to_string(G4Threading::G4GetThreadId()) << " e" << G4endl;
    //}
}
