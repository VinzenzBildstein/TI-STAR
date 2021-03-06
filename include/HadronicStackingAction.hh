#ifndef HadronicStackingAction_h
#define HadronicStackingAction_h 1

#include "G4ClassificationOfNewTrack.hh"
#include "G4UserStackingAction.hh"
#include "G4Track.hh"

class HadronicStackingAction : public G4UserStackingAction{
    public:
        HadronicStackingAction();
        ~HadronicStackingAction();
        
        virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track*);
        virtual void NewStage();
        virtual void PrepareNewEvent();

        
    private:
         G4ParticleTable* particleTable;
         G4ParticleDefinition * deuteronDef;
         G4ParticleDefinition * protonDef;
         G4ParticleDefinition * electronDef;
         G4ParticleDefinition * alphaDef;
         std::ofstream outfile;
};

#endif
