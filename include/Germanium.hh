#ifndef __GERMANIUM_HH
#define __GERMANIUM_HH

#include <iostream>
#include <vector>
#include "TObject.h"

#include "Time.hh"

class Crystal : public TObject {
	public:
		Crystal(){
			ClearCrystal();
		}
		Crystal(int crystal, double energy, MyTime_t time);
		Crystal(int crystal, int segment, double energy, MyTime_t time);

		~Crystal(){
			ClearCrystal();
		}

		void ClearCrystal() {
			fTime = 0.0;
			fCryID = -1;
			fCoreEnergy = -1.;
			fSegEnergy.clear();
			fSegID.clear(); 
		}

		//set
		void SetCryID(int cry) { fCryID = cry; }
		void SetCore(double energy, MyTime_t time);
		void AddSegment(int segment, double energy, MyTime_t time);
		void SetTime(double time) { fTime = time; }
		//get
		int GetCryID() { return fCryID; }
		double GetTime() { return fTime; }
		double GetCore() { return fCoreEnergy;	}
		std::vector<double> GetSeg() { return fSegEnergy; }
		std::vector<int> GetSegID() { return fSegID; }
		//get size
		long long SizeOf() {
			long long result = sizeof(fCoreEnergy);
			result += fSegID.size()*sizeof(int);
			result += fSegEnergy.size()*sizeof(double);
			return result;
		};

	protected:
		int fCryID;
		double fCoreEnergy;
		std::vector<double> fSegEnergy;
		std::vector<int> fSegID;
		MyTime_t fTime;

		ClassDef(Crystal, 1)
};


class Germanium : public TObject {
	public:
		Germanium() {
			ClearGermanium();
		}

		~Germanium() {
			ClearGermanium();
		}

		void ClearGermanium() {
			fClusterID = -1;

			for(unsigned int i = 0; i < fCrystal.size(); ++i) {
				fCrystal[i].ClearCrystal();
			}
			fCrystal.clear();
		}

		//set
		void SetCore(int crystal, double energy, MyTime_t time);
		void SetSegment(int crystal, int segment, double energy, MyTime_t time);
		void PrintCluster();
		void SetCluID(int clu) {
			fClusterID = clu;
		}

		//get
		int NrOfCrystals() {
			return fCrystal.size();
		}

		std::vector<Crystal> GetCrystal() {
			return fCrystal;
		}
		
		double* GetPosition() {
                        return positionWorld;
                }
                
        void SetPosition(double TRX, double TRY, double TRZ) {
                        positionWorld[0] = TRX;
                        positionWorld[1] = TRY;
                        positionWorld[2] = TRZ;
                }
                
        double GetTheta() {
                        return theta;
                }
                
        void SetTheta(double thetaIn) {
                        theta = thetaIn;
                }
                
//      double GetnoComptE() {
//                      return noComptE;
//            }
//      void SetnoComptE(double energy) {
//                      noComptE = energy;
//              }
                
		int GetCluID() {
			return fClusterID;
		}

		long long SizeOf() {
			if(fCrystal.size() == 0) return 0;
			return (fCrystal.size()*fCrystal[0].SizeOf());
		}

	protected:
		std::vector<Crystal> fCrystal;
		double positionWorld [3];
		double theta;
//      double noComptE;
		int fClusterID;
		int fStrange;
		double thetaIn;
		//double fCoreEnergy;
		std::vector<double> fSegEnergy;
		int fCryID;
		MyTime_t fTime;

		ClassDef(Germanium, 2)
};

#endif
