
#define myspinningparticle 25
// 25 higgs
#define myheavyparticle 7
#define MUONPTCUT 25
#define MUONETACUT 2.1 
//25GeV,2.1 for dimuon ana 
#define BPTCUT 30
#define BETACUT 2.5
//30GeV 2.5 for dimuon ana 

// WARNING: typically one needs 25 MB/100 events at the LHC.
// Therefore large event samples may be impractical.
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include "MyUserHooks.hpp"
#include "Pythia8/Pythia.h"
#include "Pythia8Plugins/HepMC2.h"

// ROOT, for saving Pythia events as trees in a file.
#include "TFile.h"
// ROOT, for interactive graphics.
#include "TVirtualPad.h"
#include "TApplication.h"
// ROOT, for histogramming.
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TClonesArray.h"


// ROOT, for interactive graphics.
#include "TVirtualPad.h"
#include "TApplication.h"


using namespace Pythia8;

int main(int argc, char* argv[]) {

  // Generator.
  Pythia pythia;  
  // Read in commands from external file.
  pythia.readFile(argv[1]);

    ofstream eventsfeatures; 
    TFile *file = new TFile;
    cout << "\n >>> PYTHIA settings will be read from file " << argv[1] << " <<< \n" << endl;
    double mypolarization;
    if(atoi(argv[2])==0) 
      { mypolarization = 0.0; TFile *file = TFile::Open("../OutputRawData/long.root","recreate"); eventsfeatures.open("../OutputRawData/long.txt");}
    else if (atoi(argv[2])==1) 
      { mypolarization = 1.0; TFile *file = TFile::Open("../OutputRawData/tran.root","recreate"); eventsfeatures.open("../OutputRawData/tran.txt");}
    else
      { mypolarization = 9.0; TFile *file = TFile::Open("../OutputRawData/scal.root","recreate"); eventsfeatures.open("../OutputRawData/scal.txt");}
    eventsfeatures << "index,pT_mu1,eta_mu1,pT_mu2,eta_mu2,pT_X,eta_X,pT_b,eta_b,DeltaR_mumu,M_dimuon,DeltaR_bdimuon,M_bdimuon,pT_dimuon,(pT/M)_dimuon" << endl;


    // Extract settings to be used in the main program.
    int    nEvent    = pythia.mode("Main:numberOfEvents");
    int    nAbort    = pythia.mode("Main:timesAllowErrors");

    // Root Tree initiated
    Event *event = &pythia.event;
    //TClonesArray* particles = (TClonesArray*)pythia.GetListOfParticles();
    TTree *T = new TTree("T","ev1 Tree");
    T->Branch("event",&event);
    //T->Branch("particles",&particles);

    // Initialize UserHooks class in helicity_user_hook.cc & helicity_user_hook.h
    MyUserHooks* myUserHooks = new MyUserHooks(&pythia.info, true, mypolarization, myspinningparticle);
    // bool argument to switch on and off process level veto
    pythia.setUserHooksPtr(myUserHooks);
    // Connect Pythia user hooks to the derived class

    // Initialization.
    pythia.init();

    
//===================================================================================
// Start booking root hist and root tree 
    TH1F *NumberTMuon = new TH1F("NumberTMuon","NumberTMuon", 4, -0.5, 3.5);

    TH1F *Muon1pT = new TH1F("Muon1pT","Muon1 pT", 80, 0, 160);
    TH1F *Muon1eta = new TH1F("Muon1eta","Muon1 eta", 100, -5, 5);
    TH2F *Muon1etapT = new TH2F("Muon1etapT", "Muon1 eta:pT", 100,-5,5,80,0,160);
    TH1F *Muon2pT = new TH1F("Muon2pT","Muon2 pT", 80, 0, 160);
    TH1F *Muon2eta = new TH1F("Muon2eta","Muon2 eta", 100, -5, 5);
    TH2F *Muon2etapT = new TH2F("Muon2etapT", "Muon2 eta:pT", 100,-5,5,80,0,160);
    
    TH1F *PolarpT = new TH1F("PolarpT","Polar pT", 100, 0, 200);
    TH1F *Polareta = new TH1F("Polareta","Polar eta", 100, -5, 5);
    TH2F *PolaretapT = new TH2F("PolaretapT", "Polar eta:pT", 100,-5,5,100,0,200);    
    TH1F *bpT = new TH1F("bpT","b pT", 100, 0, 200);
    TH1F *beta = new TH1F("beta","b eta", 100, -5, 5);
    TH2F *betapT = new TH2F("betapT", "b eta:pT", 100,-5,5,100, 0, 200);
    TH1F *heavyBpT = new TH1F("heavyBpT","heavy b pT", 100, 0, 200);
    TH1F *heavyBeta = new TH1F("heavyBeta","heavy b eta", 100, -5, 5);
    TH2F *heavyBetapT = new TH2F("heavyBetapT", "heavy b eta:pT", 100,-5,5,100, 0, 200);
    TH1F *IMassbmumu = new TH1F("IMassbmumu","Invariant mass of mu mu b", 60, 0, 300);
    TH1F *DeltaR2 = new TH1F("DeltaR2","Delt R between b-dimuon", 65, 0, 6.5);
    TH1F *Deltaeta2 = new TH1F("Deltaeta2","Delt eta between b-dimuon", 100, -5, 5);
    TH1F *DeltaPhi2 = new TH1F("DeltaPhi2","Delt phi between b-dimuon", 65, 0, 6.5);
        
    TH1F *IMass = new TH1F("IMass","Invariant mass of 2 leading Muons", 70, 10, 80);
    TH1F *DeltaR = new TH1F("DeltaR","Delt R between muons", 65, 0, 6.5);
    TH1F *Deltaeta = new TH1F("Deltaeta","Delt eta between muons", 100, -5, 5);
    TH1F *DeltaPhi = new TH1F("DeltaPhi","Delt phi between muons", 65, 0, 6.5);
    TH1F *MuMupT = new TH1F("MuMupT","pT of mumu system", 100, 0, 200);
    TH1F *MuMupTratio = new TH1F("MuMupTratio","pT/mass of mumu system", 40, 0, 8);
    TH2F *RpT = new TH2F("RpT", "pT:dR", 100,0,200,65,0,6.5);    


// Finishing booking root hist and root tree 
//===================================================================================


    int iTop = 0;
    int iAbort = 0;
    int iPassPhaseCutEvent=0;
    //int beventcut=0;
    
////////////////////////////////////////////////////////////////////////
// Begin event loop.
for (int iEvent = 0; iEvent < nEvent; ++iEvent) {

    int imuon=0,ipolar=0,ib=0,iheavyb=0;
    Particle muon[2]; 
    Particle bjet[1];
    Particle polar[1];
    Particle heavyb[1];
    Particle temp;

    double invariantmass[1],deltaeta[1],deltaphi[1],deltar[1];
    double invariantmass2[1],deltaeta2[1],deltaphi2[1],deltar2[1];

    // Generate event.
    if (!pythia.next()) continue;
    for (int i = 0; i < pythia.event.size();  i++) { 
            if(pythia.event[i].idAbs() == myspinningparticle && pythia.event[i].mother1()!=pythia.event[i].mother2()){
                polar[ipolar]=pythia.event[i];
                heavyb[iheavyb]=pythia.event[pythia.event[i].mother1()];
                ipolar++; 
                iheavyb++;
            }

            if(pythia.event[i].idAbs() == myspinningparticle && pythia.event[pythia.event[i].daughter1()].idAbs() ==13 ){
                if (pythia.event[pythia.event[i].daughter1()].pT() > pythia.event[pythia.event[i].daughter2()].pT()){
                    muon[imuon]= pythia.event[pythia.event[i].daughter1()]; imuon++;
                    muon[imuon]= pythia.event[pythia.event[i].daughter2()]; imuon++;
                    }
                else{
                    muon[imuon]= pythia.event[pythia.event[i].daughter2()]; imuon++;
                    muon[imuon]= pythia.event[pythia.event[i].daughter1()]; imuon++;
                }
            }

            if(pythia.event[i].idAbs() == 5 && pythia.event[pythia.event[i].mother1()].idAbs()!=5 ){
                bjet[ib]=pythia.event[i];
                ib++;
            }
        }

    bool PassPhaseCutb = 1;
    bool PassPhaseCutMuon =1;

    PassPhaseCutMuon = muon[0].pT()>MUONPTCUT && muon[1].pT()>MUONPTCUT && abs(muon[0].eta())<MUONETACUT && abs(muon[1].eta())<MUONETACUT;
    PassPhaseCutb = bjet[0].pT()> BPTCUT && abs(bjet[0].eta()) < BETACUT;

    //for (int i=0; i<4 ; i++) { PassPhaseCutMuon = PassPhaseCutMuon && abs(muon[i].eta()) < MUONETACUT;}
    //for (int i=0; i<2 ; i++) { PassPhaseCutb = PassPhaseCutb && (bjet[i].pT()> BPTCUT && abs(bjet[i].eta()) < BETACUT);}
    // cout<< " number of muons is " << imuon << ", pT_mu1=" <<muon[0].pT()<< ", pT_mu2=" <<muon[1].pT() <<endl;
    // cout<< " number of b is " << ib <<endl;
    
    //if( PassPhaseCutMuon && PassPhaseCutb ){
    if( 1 ){

            iPassPhaseCutEvent++;
            int iSideMuon=0;
            if(abs(muon[0].eta())>0.9)  iSideMuon++;
            if(abs(muon[1].eta())>0.9)  iSideMuon++;
            NumberTMuon -> Fill(iSideMuon);


            //T->Fill();

            heavyBpT -> Fill(heavyb[0].pT());
            heavyBeta -> Fill (heavyb[0].eta());
            heavyBetapT -> Fill (heavyb[0].eta(),heavyb[0].pT());
            bpT -> Fill(bjet[0].pT());
            beta -> Fill (bjet[0].eta());
            betapT -> Fill (bjet[0].eta(),bjet[0].pT());
            PolarpT -> Fill(polar[0].pT());
            Polareta -> Fill (polar[0].eta());
            PolaretapT -> Fill (polar[0].eta(),polar[0].pT());
            Muon1pT -> Fill(muon[0].pT());
            Muon1eta -> Fill (muon[0].eta());
            Muon1etapT -> Fill (muon[0].eta(),muon[0].pT());
            Muon2pT -> Fill(muon[1].pT());
            Muon2eta -> Fill (muon[1].eta());
            Muon2etapT -> Fill (muon[1].eta(),muon[1].pT());
            
            
            deltaeta[0] = std::abs(muon[0].eta() - muon[1].eta());
            deltaphi[0] = std::abs(muon[0].phi() - muon[1].phi());
            if (deltaphi[0] > 3.1415926) deltaphi[0] = 2*3.1415926 - deltaphi[0];
            deltar[0] = sqrt( deltaeta[0] * deltaeta[0] + deltaphi[0] * deltaphi[0] );
            invariantmass[0]=(muon[0].p()+muon[1].p()).mCalc();
            IMass -> Fill(invariantmass[0]);
            Deltaeta -> Fill(deltaeta[0]);
            DeltaPhi -> Fill(deltaphi[0]);
            DeltaR -> Fill(deltar[0]);

            MuMupT -> Fill(  (muon[0].p()+ muon[1].p()).pT()  ); 
            MuMupTratio -> Fill ( (muon[0].p()+ muon[1].p()).pT() /invariantmass[0]);
            RpT -> Fill ( (muon[0].p()+ muon[1].p()).pT(), deltar[0]);


            deltaeta2[0] = std::abs(polar[0].eta() - bjet[0].eta());
            deltaphi2[0] = std::abs(polar[0].phi() - bjet[0].phi());
            if (deltaphi2[0] > 3.1415926) deltaphi2[0] = 2*3.1415926 - deltaphi2[0];
            deltar2[0] = sqrt( deltaeta2[0] * deltaeta2[0] + deltaphi2[0] * deltaphi2[0] );
            invariantmass2[0]=(polar[0].p()+bjet[0].p()).mCalc();
            IMassbmumu -> Fill(invariantmass2[0]);
            Deltaeta2 -> Fill(deltaeta2[0]);
            DeltaPhi2 -> Fill(deltaphi2[0]);
            DeltaR2 -> Fill(deltar2[0]);

            //-- fill txt file
            eventsfeatures << iPassPhaseCutEvent<<", ";
            eventsfeatures << muon[0].pT()<<", "<<muon[0].eta()<<", ";
            eventsfeatures << muon[1].pT()<<", "<<muon[1].eta()<<", ";
            eventsfeatures << polar[0].pT()<<", "<<polar[0].eta()<<", ";
            eventsfeatures << bjet[0].pT()<<", "<<bjet[0].eta()<<", ";
            eventsfeatures << deltar[0] << ", " << invariantmass[0] << ", ";
            eventsfeatures << deltar2[0] << ", " << invariantmass2[0] << ", ";
            eventsfeatures << (muon[0].p()+ muon[1].p()).pT() <<", "<< (muon[0].p()+ muon[1].p()).pT() /invariantmass[0]  <<endl; 
            // done with fill txt file

        }    
    }    
//------------------Event Loop ends-------------------------------------------
    
    pythia.stat();

    //T->Print();
    //T->Write();
    NumberTMuon -> Write(); delete NumberTMuon;
    
    Muon1pT ->Write();    delete Muon1pT;
    Muon1eta ->Write();    delete Muon1eta;
    Muon1etapT ->Write();    delete Muon1etapT;
    Muon2pT ->Write();    delete Muon2pT;
    Muon2eta -> Write();    delete Muon2eta;
    Muon2etapT ->Write();    delete Muon2etapT;
    PolarpT ->Write();    delete PolarpT;
    Polareta -> Write();    delete Polareta;
    PolaretapT ->Write();  delete PolaretapT;
    bpT->Write();    delete bpT;
    beta->Write();    delete beta;
    betapT->Write();    delete betapT;
    heavyBpT->Write();    delete heavyBpT;
    heavyBeta->Write();    delete heavyBeta;
    heavyBetapT->Write();    delete heavyBetapT;

    IMass -> Write();    delete IMass;
    DeltaPhi->Write();    delete DeltaPhi;
    Deltaeta->Write();    delete Deltaeta;
    DeltaR ->Write();    delete DeltaR;
    MuMupT ->Write();    delete MuMupT;
    MuMupTratio -> Write(); delete MuMupTratio;
    RpT ->Write();    delete RpT;

    IMassbmumu -> Write();    delete IMassbmumu;
    DeltaPhi2->Write();    delete DeltaPhi2;
    Deltaeta2->Write();    delete Deltaeta2;
    DeltaR2 ->Write();    delete DeltaR2;


    delete file;
    delete myUserHooks;
    eventsfeatures.close();
    cout<< "number of event pass phase cut is " << iPassPhaseCutEvent <<endl;
//----------------------------------------------------------

  // Done.
  return 0;
}
