// main42.cc is a part of the PYTHIA event generator.
// Copyright (C) 2015 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// Author: Mikhail Kirsanov, Mikhail.Kirsanov@cern.ch.
// This program illustrates how a file with HepMC events
// can be generated by Pythia8.
// Input and output files are specified on the command line, e.g. like
// ./main42.exe main42.cmnd hepmcout42.dat > out
// The main program contains no analysis; this is intended to happen later.
// It therefore "never" has to be recompiled to handle different tasks.

// Set the polarization type:
// 1.0 = + (trans)
// 0.0 = 0 (long)
// -1.0 = - (trans)
// 9.0 = scalar

// 4900023 for Zd
// 34 for W'
// 25 for higgs
#define myspinningparticle 25

// WARNING: typically one needs 25 MB/100 events at the LHC.
// Therefore large event samples may be impractical.
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



  // Interface for conversion from Pythia8::Event to HepMC event.
  HepMC::Pythia8ToHepMC ToHepMC;
  // Specify file where HepMC events will be stored.
  HepMC::IO_GenEvent ascii_io("../OutputRawData/hepmc.dat", std::ios::out);
  
  // Create an LHAup object that can access relevant information in pythia.
  LHAupFromPYTHIA8 myLHA(&pythia.process, &pythia.info);
  // Open a file on which LHEF events should be stored, and write header.
  //myLHA.openLHEF("../OutputRawData/hardprocess.lhe");
  // Setup TFile to store root hist and root tree
  TFile *file = new TFile;
  //TFile *file = TFile::Open("../OutputRawData/KinematicsHist.root","recreate");


  //TApplication theApp();
  //TApplication theApp("hist",1,"");
  // Check that correct number of command-line arguments
  if (argc !=3) {
    cerr << " Unexpected number of command-line arguments. \n You are"
         << " expected to provide one input file name. \n"
         << " Program stopped! " << endl;
    return 1;
  }
  // Check that the provided input name corresponds to an existing file.
  ifstream is(argv[1]);
  if (!is) {
    cerr << " Command-line file " << argv[1] << " was not found. \n" << " Program stopped! " << endl;
    return 1;
  }

  // Confirm that external files will be used for input and output.
  cout << "\n >>> PYTHIA settings will be read from file " << argv[1] << " <<< \n" << endl;
  
  double mypolarization;
  if(atoi(argv[2])==0) 
    { mypolarization = 0.0; TFile *file = TFile::Open("../OutputRawData/long.root","recreate"); myLHA.openLHEF("../OutputRawData/long.lhe");}
  else if (atoi(argv[2])==1) 
    { mypolarization = 1.0; TFile *file = TFile::Open("../OutputRawData/tran.root","recreate"); myLHA.openLHEF("../OutputRawData/tran.lhe");}
  else
    { mypolarization = 9.0; TFile *file = TFile::Open("../OutputRawData/scal.root","recreate"); myLHA.openLHEF("../OutputRawData/scal.lhe");}



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
    // Store initialization info in the LHAup object.
    myLHA.setInit();
    // Write out this initialization info on the file.
    myLHA.initLHEF();

    
//===================================================================================
//===================================================================================
//===================================================================================
// Start booking root hist and root tree 
//...................................................................................
//...................................................................................

    // Book hist for Polarization
    TH1F *cosDist = new TH1F( "cos(theta)_Z", "cos(theta)_Z", 50, -1.0, 1.0);
    // Angular distribution for W+
    TH1F *leadingMuonPt = new TH1F("leadingMuonPt", "leadingMuonPT", 100, 0., 160.);
    TH1F *trailingMuonPt = new TH1F("trailingMuonPt", "trailingMuonPT", 100, 0., 100.);
    TH1F *XPt = new TH1F("XPt", "XPt", 50, 0., 200.);
    
    // Some other useful hist
    TH1F *MuonCount = new TH1F("MuonCount","Muon count", 20, 0, 15);
    TH1F *bCount = new TH1F("bCount","b count", 10, -0.5, 9.5);
    TH1F *bcutCount = new TH1F("bcutCount","b cut count", 10, -0.5, 9.5);
    TH1F *MuonMotherDistribution = new TH1F("MuonMotherDistribution","Muon mother", 250, 0, 250);
    TH1F *pdgid = new TH1F("pdgid","Final particle PDG ID", 30, 0, 30);
    
    TH1F *Muon1pT = new TH1F("Muon1pT","Muon1 pT", 100, 0, 160);
    TH1F *Muon1eta = new TH1F("Muon1eta","Muon1 eta", 100, -5, 5);
    TH2F *Muon1etapT = new TH2F("Muon1etapT", "Muon1 eta:pT", 100,-5,5,100,0,120);
    TH1F *Muon2pT = new TH1F("Muon2pT","Muon2 pT", 100, 0, 120);
    TH1F *Muon2eta = new TH1F("Muon2eta","Muon2 eta", 100, -5, 5);
    TH2F *Muon2etapT = new TH2F("Muon2etapT", "Muon2 eta:pT", 100,-5,5,100,0,120);
    
    TH1F *MuonWpT = new TH1F("MuonWpT","MuonW pT", 100, 0, 120);
    TH1F *MuonWeta = new TH1F("MuonWeta","MuonW eta", 100, -5, 5);
    TH2F *MuonWetapT = new TH2F("MuonWetapT", "MuonW eta:pT", 100,-5,5,100,0,120);
    TH1F *PolarpT = new TH1F("PolarpT","Polar pT", 100, 0, 200);
    TH1F *Polareta = new TH1F("Polareta","Polar eta", 100, -5, 5);
    TH2F *PolaretapT = new TH2F("PolaretapT", "Polar eta:pT", 100,-5,5,100,0,200);
    
    TH1F *bpT = new TH1F("bpT","b pT", 100, 0, 200);
    TH1F *beta = new TH1F("beta","b eta", 100, -5, 5);
    TH2F *betapT = new TH2F("betapT", "b eta:pT", 100,-5,5,100, 0, 200);
    TH1F *heavyBpT = new TH1F("heavyBpT","heavy b pT", 100, 0, 200);
    TH1F *heavyBeta = new TH1F("heavyBeta","heavy b eta", 100, -5, 5);
    TH2F *heavyBetapT = new TH2F("heavyBetapT", "heavy b eta:pT", 100,-5,5,100, 0, 200);
    
    
    TH1F *IMass = new TH1F("IMass","Invariant mass of 2 leading Muons", 100, 0, 100);
    TH1F *DeltaR = new TH1F("DeltaR","Delt R between muons", 65, 0, 6.5);
    TH1F *Deltaeta = new TH1F("Deltaeta","Delt eta between muons", 100, -5, 5);
    TH1F *DeltaPhi = new TH1F("DeltaPhi","Delt phi between muons", 65, 0, 6.5);
    TH1F *MuMupT = new TH1F("MuMupT","pT of mumu system", 100, 0, 200);
    TH1F *MuMupTratio = new TH1F("MuMupTratio","pT/mass of mumu system", 50, 0, 8);
    TH2F *RpT = new TH2F("RpT", "pT:dR", 100,0,200, 65, 0, 6.5);
    
    TH1F *IMass2 = new TH1F("IMass2","Invariant mass of mu mu b", 100, 0, 300);


    //...................................................................................
    //...................................................................................    
    // Finishing booking root hist and root tree 
    //===================================================================================
    //===================================================================================
//===================================================================================


    int iTop = 0;
    int iAbort = 0;
    bool ThisIsPolar;
    int bevent=0;
    int beventcut=0;
    
////////////////////////////////////////////////////////////////////////
// Begin event loop.
for (int iEvent = 0; iEvent < nEvent; ++iEvent) {

    int MuonIndex1 =0;
    int MuonIndex2 =0;
    int bIndex =0;
    double MuonpTtemp1 = -1;
    double MuonpTtemp2 = -1;
    Particle Muon1, Muon2, bjet;
    
    double InvariantMass = -1;
    double iMuon = 0;
    int ib = 0;
    int ibprime =0;
    int ipolar=0;
    double deltaeta = -1;
    double deltaphi =-1;

    // Generate event.
    if (!pythia.next()) continue;
    for (int i = 0; i < pythia.event.size();  i++) 
        { if(pythia.event[i].idAbs() == myspinningparticle && pythia.event[i].mother1()!=pythia.event[i].mother2()) 
            ipolar++;
        }
    //std::cout<<"ipolar="<<ipolar<<std::endl;
  if(ipolar==1){  
    T->Fill();
    //---------------------------particle Loop-------------------------------------------
    //...................................................................................
    //...................................................................................  


    for (int i = 0; i < pythia.event.size();  i++) {
        // 1. All Final state particles
        if (pythia.event[i].isFinal() && pythia.event[i].idAbs() !=22) {
            if (pythia.event[i].idAbs()<30) pdgid->Fill(pythia.event[i].idAbs());
            else pdgid->Fill(29);
        }
        // 2. B->b+polar

        if (pythia.event[i].idAbs() == 7) {
                heavyBpT -> Fill(pythia.event[i].pT());
                heavyBeta -> Fill (pythia.event[i].eta());
                heavyBetapT -> Fill (pythia.event[i].eta(),pythia.event[i].pT());
                ibprime ++;
            }

        if(pythia.event[i].idAbs() == 5 && pythia.event[pythia.event[i].mother1()].idAbs()!=5 ){
            bpT -> Fill(pythia.event[i].pT());
            beta -> Fill (pythia.event[i].eta());
            betapT -> Fill (pythia.event[i].eta(),pythia.event[i].pT());
            ib ++;
            bIndex =i;
        }

        // use place of Polar to store spinning particle
        if(pythia.event[i].idAbs() == myspinningparticle){
            PolarpT -> Fill(pythia.event[i].pT());
            Polareta -> Fill (pythia.event[i].eta());
            PolaretapT -> Fill (pythia.event[i].eta(),pythia.event[i].pT());
        }




        // 3. Muons
        if (pythia.event[i].idAbs()==13 && pythia.event[pythia.event[i].mother1()].idAbs() !=13  && pythia.event[pythia.event[i].mother2()].idAbs() !=13) {
            int MuonMother1 = pythia.event[i].mother1();
            int MuonMother2 = pythia.event[i].mother2();
            
            //3.1. count Muons
            iMuon ++;
            //3.2. Count Muon Mothers
            if (pythia.event[MuonMother1].idAbs() >250 ) MuonMotherDistribution -> Fill (249);
            else MuonMotherDistribution -> Fill (pythia.event[MuonMother1].idAbs());
        
            if (pythia.event[MuonMother2].idAbs() >250 ) MuonMotherDistribution -> Fill (249);
            else MuonMotherDistribution -> Fill (pythia.event[MuonMother2].idAbs());

            //3.3. Find Muon from W
            if(pythia.event[MuonMother1].idAbs() == 24 || pythia.event[MuonMother2].idAbs() ==24){
                MuonWpT -> Fill(pythia.event[i].pT());
                MuonWeta -> Fill (pythia.event[i].eta());
                MuonWetapT -> Fill (pythia.event[i].eta(),pythia.event[i].pT());
            }

            //3.4. Find first two leading muons
            if (pythia.event[i].pT()>0 && pythia.event[i].eta()<10 ) {
                if (pythia.event[i].pT() > MuonpTtemp1 ) {
                    MuonpTtemp2 = MuonpTtemp1;
                    MuonIndex2 = MuonIndex1;
                    MuonpTtemp1 = pythia.event[i].pT();
                    MuonIndex1 = i;
                }
                else if (pythia.event[i].pT() > MuonpTtemp2) {
                    MuonpTtemp2 = pythia.event[i].pT();
                    MuonIndex2 = i;
                }
            }
        }

        // 4. Poloarztion
        // DO NOT TOUCH
        // Select W+/- and veto final state radiation
        if (pythia.event[i].idAbs() == myspinningparticle )
        {
            // identify daughters of the W
            int i1 = pythia.event[i].daughter1();
            int i2 = pythia.event[i].daughter2();
            
            // Angular distribution is defined with respect to the decay product
            // with the same sign charge as the W boson.
            if (pythia.event[i1].id() * pythia.event[i].id() > 0)
            {
                i1 = pythia.event[i].daughter2();  // Specify i1 as daughter with same sign as W
                i2 = pythia.event[i].daughter1();
            }
            
            // Reconstruct W+- decay angle by boosting daughter and mother to W
            // rest frame. W direction in mother rest frame opposite to mother now.
            
            RotBstMatrix Mrotbst;
            Mrotbst.bstback( pythia.event[i].p() ); // Assign boost matrix to boost to W frame
            Vec4 p1 = pythia.event[i1].p();
            p1.rotbst( Mrotbst );		// boost the daughter to W frame
            Vec4 pM = pythia.event[pythia.event[i].mother1()].p();
            pM.rotbst( Mrotbst );		// boost the mother to W frame
            pM.flip3();
            double costhe = costheta( p1, pM );
            //printf("costhe = %e\n", costhe);
            
            // fill histograms
            
            if (pythia.event[i1].idAbs() == 13)
            {   
                XPt->Fill(pythia.event[i].pT());
                
                double Pt_muon_i1 = pythia.event[i1].pT();
                double Pt_muon_i2 = pythia.event[i2].pT();
                if (Pt_muon_i1 > Pt_muon_i2)
                {
                    leadingMuonPt->Fill( Pt_muon_i1 );
                    trailingMuonPt->Fill( Pt_muon_i2 );
                }
                else
                {
                    leadingMuonPt->Fill( Pt_muon_i2 );
                    trailingMuonPt->Fill( Pt_muon_i1 );
                }
                
            }
            
            cosDist->Fill( costhe );

            
        } //4. End of Poloarztion
        

        
    }
    //...................................................................................
    //...................................................................................  
    //----------------------particle Loop ends-------------------------------------------
    
    
    MuonCount -> Fill(iMuon);
    bCount -> Fill(ib);
    bcutCount -> Fill(ibprime);
    if(ib!=0) bevent++;
    
    
    if (MuonIndex1 >0 && MuonIndex2 > 0 ){
    // 5. Fill pT and eta for two leading muons
    Muon1 = pythia.event[MuonIndex1];
    Muon2 = pythia.event[MuonIndex2];
    bjet = pythia.event[bIndex];
    
    Muon1pT -> Fill(Muon1.pT());
    Muon1eta -> Fill (Muon1.eta());
    Muon1etapT -> Fill (Muon1.eta(),Muon1.pT());
    
    Muon2pT -> Fill(Muon2.pT());
    Muon2eta -> Fill (Muon2.eta());
    Muon2etapT -> Fill (Muon2.eta(),Muon2.pT());

    
    // 6. invirant mass of muon pairs
    Vec4 MuMu = Muon1.p() + Muon2.p();
    InvariantMass = MuMu.mCalc();
    //InvirantMass =  sqrt( - pow((Muon1.px()+Muon2.px()),2.0) - pow((Muon1.py()+Muon2.py()),2.0) - pow((Muon1.pz()+Muon2.pz()),2.0) + pow((Muon1.e()+Muon2.e()),2.0) );
    IMass -> Fill(InvariantMass);
    IMass2 -> Fill((Muon1.p()+Muon2.p()+bjet.p()).mCalc());
    // 7. Delta R for muon pairs
    deltaeta = std::abs(Muon1.eta() - Muon2.eta());
    deltaphi = std::abs(Muon1.phi() - Muon2.phi());
    if (deltaphi > 3.1415926) deltaphi = 2*3.1415926 - deltaphi;
    Deltaeta -> Fill(deltaeta);
    DeltaPhi -> Fill(deltaphi);
    DeltaR -> Fill( sqrt( deltaeta * deltaeta + deltaphi * deltaphi ) );
    MuMupT -> Fill(Muon1.pT()+ Muon2.pT()); 
    MuMupTratio -> Fill ((Muon1.pT()+ Muon2.pT())/InvariantMass);
    RpT -> Fill (Muon1.pT()+ Muon2.pT(), sqrt( deltaeta * deltaeta + deltaphi * deltaphi ));
    }
	


    // 9. Store event info in the LHAup object.
    myLHA.setEvent();
    //  Write out this event info on the file.
    // With optional argument (verbose =) false the file is smaller.
    myLHA.eventLHEF();

    // 10. Construct new empty HepMC event and fill it.
    // Units will be as chosen for HepMC build; but can be changed
    // by arguments, e.g. GenEvt( HepMC::Units::GEV, HepMC::Units::MM)
    //HepMC::GenEvent* hepmcevt = new HepMC::GenEvent();
    //ToHepMC.fill_next_event( pythia, hepmcevt );
    // Write the HepMC event to file. Done with it.
    //ascii_io << hepmcevt;
    //delete hepmcevt;
  }

    
}
//------------------Event Loop ends-------------------------------------------
    
    pythia.stat();
//===================================================================================
//===================================================================================
//===================================================================================
// Write root and LHE
//...................................................................................
    T->Print();
    T->Write();
    
    MuonCount ->Write();    delete MuonCount;
    MuonMotherDistribution ->Write();    delete MuonMotherDistribution;
    Muon1pT ->Write();    delete Muon1pT;
    Muon1eta ->Write();    delete Muon1eta;
    Muon1etapT ->Write();    delete Muon1etapT;
    Muon2pT ->Write();    delete Muon2pT;
    Muon2eta -> Write();    delete Muon2eta;
    Muon2etapT ->Write();    delete Muon2etapT;
    MuonWpT ->Write();    delete MuonWpT;
    MuonWeta ->Write();    delete MuonWeta;
    MuonWetapT ->Write();    delete MuonWetapT;
    PolarpT ->Write();    delete PolarpT;
    Polareta -> Write();    delete Polareta;
    PolaretapT ->Write();  delete PolaretapT;
    
    bpT->Write();    delete bpT;
    beta->Write();    delete beta;
    betapT->Write();    delete betapT;
    heavyBpT->Write();    delete heavyBpT;
    heavyBeta->Write();    delete heavyBeta;
    heavyBetapT->Write();    delete heavyBetapT;
    bCount -> Write();    delete bCount;
    bcutCount -> Write();    delete bcutCount;
    
    IMass -> Write();    delete IMass;
    IMass2 -> Write();    delete IMass2;
    DeltaPhi->Write();    delete DeltaPhi;
    Deltaeta->Write();    delete Deltaeta;
    DeltaR ->Write();    delete DeltaR;
    MuMupT ->Write();    delete MuMupT;
    MuMupTratio -> Write(); delete MuMupTratio;
    RpT ->Write();    delete RpT;
    
    pdgid -> Write();    delete pdgid;

    cosDist->Write();    delete cosDist;
    XPt->Write();   delete XPt;
    leadingMuonPt->Write();    delete leadingMuonPt;
    trailingMuonPt->Write();    delete trailingMuonPt;


    delete file;
    // Write endtag. Overwrite initialization info with new cross sections.
    myLHA.closeLHEF(true);
    delete myUserHooks;
//----------------------------------------------------------

  // Done.
  return 0;
}





