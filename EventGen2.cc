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

// WARNING: typically one needs 25 MB/100 events at the LHC.
// Therefore large event samples may be impractical.
#include <iostream>
#include <cmath>
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

// ROOT, for interactive graphics.
#include "TVirtualPad.h"
#include "TApplication.h"


// Set the polarization type:
// 1.0 = + (trans)
// 0.0 = 0 (long)
// -1.0 = - (trans)
// 9.0 = scalar
#define mypolarization 9.0
// 4900023 for Zd
// 34 for W'
#define myspinningparticle 34


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
  myLHA.openLHEF("../OutputRawData/hardprocess.lhe");
  // Setup TFile to store root hist and root tree
  TFile *file = TFile::Open("../OutputRawData/KinematicsHist.root","recreate");


  //TApplication theApp();
  //TApplication theApp("hist",1,"");
  // Check that correct number of command-line arguments
  if (argc !=2) {
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





  // Extract settings to be used in the main program.
  int    nEvent    = pythia.mode("Main:numberOfEvents");
  int    nAbort    = pythia.mode("Main:timesAllowErrors");



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
    TH1F *InvariantMass = new TH1F("InvariantMass", "InvariantMass", 100, 0., 120.);
    TH1F *leadingMuonPt = new TH1F("leadingMuonPt", "leadingMuonPT", 100, 0., 120.);
    TH1F *trailingMuonPt = new TH1F("trailingMuonPt", "trailingMuonPT", 100, 0., 100.);
    TH1F *XPt = new TH1F("XPt", "XPt", 50, 0., 200.);
    
    // Some other useful hist
    TH1F *MuonCount = new TH1F("MuonCount","Muon count", 20, 0, 15);
    TH1F *bCount = new TH1F("bCount","b count", 10, -0.5, 9.5);
    TH1F *bcutCount = new TH1F("bcutCount","b cut count", 10, -0.5, 9.5);
    TH1F *MuonMotherDistribution = new TH1F("MuonMotherDistribution","Muon mother", 250, 0, 250);
    
    TH1F *Muon1pT = new TH1F("Muon1pT","Muon1 pT", 100, 0, 120);
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
    TH1F *bpTcut = new TH1F("bpTcut","cut b pT", 100, 20, 200);
    TH1F *betacut = new TH1F("betacut","cut b eta", 100, -5, 5);
    TH2F *betapTcut = new TH2F("betapTcut", "cut b eta:pT", 100,-5,5,100, 20, 200);
    
    
    TH1F *IMass = new TH1F("IMass","Invariant mass of 2 leading Muons", 100, 0, 100);
    TH1F *DeltaR = new TH1F("DeltaR","Delt R between muons", 65, 0, 6.5);
    TH1F *DeltaPhi = new TH1F("DeltaPhi","Delt phi between muons", 65, 0, 6.5);
    TH2F *RpT = new TH2F("RpT", "pT:dR", 100,0,100, 65, 0, 6.5);
    
    
    TH1F *JetpT = new TH1F("JetpT","Jet pT", 200, 0, 200);
    TH1F *Jeteta = new TH1F("Jeteta","Jet eta", 100, -5, 5);
    TH1F *bJetpT = new TH1F("bJetpT","bJet pT", 200, 0, 200);
    TH1F *bJeteta = new TH1F("bJeteta","bJet eta", 100, -5, 5);
    
    TH1F *pdgid = new TH1F("pdgid","Final particle PDG ID", 30, 0, 30);
    
    // Root Tree initiated
    TTree *T = new TTree("T","ev1 Tree");
    Event *thisevent = &pythia.event;
    T->Branch("event", &thisevent);

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
    double MuonpTtemp1 = -1;
    double MuonpTtemp2 = -1;
    Particle Muon1, Muon2;
    
    double InvirantMass = -1;
    double iMuon = 0;
    int ib = 0;
    int ibcut =0;
    double Deltaeta = -1;
    double Deltaphi =-1;

    // Generate event.
    if (!pythia.next()) {
      // If failure because reached end of file then exit event loop.
      if (pythia.info.atEndOfFile()) {
        cout << " Aborted since reached end of Les Houches Event File \n";
        break;
      }
      // First few failures write off as "acceptable" errors, then quit.
      if (++iAbort < nAbort) continue;
        cout << " Event generation aborted prematurely, owing to error! \n";
      break;
    }

    
    //---------------------------particle Loop-------------------------------------------
    //...................................................................................
    //...................................................................................  

    for (int i = 0; i < pythia.event.size();  i++) {
        // 1. All Final state particles
        if (pythia.event[i].isFinal() && pythia.event[i].idAbs() !=22) {
            if (pythia.event[i].idAbs()<30) pdgid->Fill(pythia.event[i].idAbs());
            else pdgid->Fill(29);
        }
        // 2. b quarks
        if(pythia.event[i].idAbs() == 5 && pythia.event[pythia.event[i].mother1()].idAbs()!=2212 && pythia.event[pythia.event[i].mother1()].idAbs()!= 5){
            bpT -> Fill(pythia.event[i].pT());
            beta -> Fill (pythia.event[i].eta());
            betapT -> Fill (pythia.event[i].eta(),pythia.event[i].pT());
            ib ++;
            if (pythia.event[i].pT() > 30 && std::abs(pythia.event[i].eta()) < 2.4) {
                bpTcut -> Fill(pythia.event[i].pT());
                betacut -> Fill (pythia.event[i].eta());
                betapTcut -> Fill (pythia.event[i].eta(),pythia.event[i].pT());
                ibcut ++;
            }
        }
        
        // use place of Polar to store spinning particle
        if(pythia.event[i].idAbs() == myspinningparticle){
            PolarpT -> Fill(pythia.event[i].pT());
            Polareta -> Fill (pythia.event[i].eta());
            PolaretapT -> Fill (pythia.event[i].eta(),pythia.event[i].pT());
        }

        // 3. Muons
        if (pythia.event[i].idAbs()==13) {
            //3.1. count Muons
            if(pythia.event[pythia.event[i].mother1()].idAbs() !=13  && pythia.event[pythia.event[i].mother2()].idAbs() !=13) iMuon ++;
            //3.2. Count Muon Mothers
            int MuonMother1 = pythia.event[i].mother1();
            int MuonMother2 = pythia.event[i].mother2();
            if (pythia.event[MuonMother1].idAbs() !=13) {
                if (pythia.event[MuonMother1].idAbs() >250 ) MuonMotherDistribution -> Fill (249);
                else MuonMotherDistribution -> Fill (pythia.event[MuonMother1].idAbs());
            }
            if (pythia.event[MuonMother2].idAbs() !=13) {
                if (pythia.event[MuonMother2].idAbs() >250 ) MuonMotherDistribution -> Fill (249);
                else MuonMotherDistribution -> Fill (pythia.event[MuonMother2].idAbs());
            }
            //3.3. Find Muon from W
            if(pythia.event[MuonMother1].idAbs() == 24 || pythia.event[MuonMother2].idAbs() ==24){
                MuonWpT -> Fill(pythia.event[i].pT());
                MuonWeta -> Fill (pythia.event[i].eta());
                MuonWetapT -> Fill (pythia.event[i].eta(),pythia.event[i].pT());
            }
            //3.4. Find first two leading muons
            if (pythia.event[i].isFinal() && pythia.event[i].pT() > 0 && std::abs(pythia.event[i].eta()) < 5 ) {
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
                Vec4 p_i1 = pythia.event[i1].p();
                Vec4 p_i2 = pythia.event[i2].p();
                Vec4 p_i  = p_i1 + p_i2;
                InvariantMass->Fill( p1.mCalc() );
                
                
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
    bcutCount -> Fill(ibcut);
    if(ib!=0) bevent++;
    if (ibcut!=0) beventcut++;
    
    
    if (MuonIndex1 >0 && MuonIndex2 > 0 ){
    // 5. Fill pT and eta for two leading muons
    Muon1 = pythia.event[MuonIndex1];
    Muon2 = pythia.event[MuonIndex2];
    
    Muon1pT -> Fill(Muon1.pT());
    Muon1eta -> Fill (Muon1.eta());
    Muon1etapT -> Fill (Muon1.eta(),Muon1.pT());
    
    Muon2pT -> Fill(Muon2.pT());
    Muon2eta -> Fill (Muon2.eta());
    Muon2etapT -> Fill (Muon2.eta(),Muon2.pT());
    
    // 6. invirant mass of muon pairs
    InvirantMass =  sqrt( - pow((Muon1.px()+Muon2.px()),2.0) - pow((Muon1.py()+Muon2.py()),2.0) - pow((Muon1.pz()+Muon2.pz()),2.0) + pow((Muon1.e()+Muon2.e()),2.0) );
    IMass -> Fill(InvirantMass);
    // 7. Delta R for muon pairs
    Deltaeta = std::abs(Muon1.eta() - Muon2.eta());
    Deltaphi = std::abs(Muon1.phi() - Muon2.phi());
    if (Deltaphi > 3.1415926) Deltaphi = 2*3.1415926 - Deltaphi;
    DeltaPhi -> Fill(Deltaphi);
    DeltaR -> Fill( sqrt( Deltaeta * Deltaeta + Deltaphi * Deltaphi ) );
    RpT -> Fill (InvirantMass, sqrt( Deltaeta * Deltaeta + Deltaphi * Deltaphi ));
    }
	
    // 8. Fill root tree
    T->Fill();

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
    
//------------------Event Loop ends-------------------------------------------
    
    cout<< "The b event count is " << bevent << " , the cut the b event count is " << beventcut << endl;
    pythia.stat();
    // -------------------------------------------------------------
    // Write tree.
    T->Print();
    T->Write();
    T->Show(1);
    
    MuonCount ->Write();
    MuonMotherDistribution ->Write();
    Muon1pT ->Write();
    Muon1eta ->Write();
    Muon1etapT ->Write();
    Muon2pT ->Write();
    Muon2eta -> Write();
    Muon2etapT ->Write();
    MuonWpT ->Write();
    MuonWeta ->Write();
    MuonWetapT ->Write();
    PolarpT ->Write();
    Polareta -> Write();
    PolaretapT ->Write();
    
    bpT->Write();
    beta->Write();
    betapT->Write();
    bpTcut->Write();
    betacut->Write();
    betapTcut->Write();
    bCount -> Write();
    bcutCount -> Write();
    
    IMass -> Write();
    DeltaPhi->Write();
    DeltaR ->Write();
    RpT ->Write();
    
    pdgid -> Write();

    cosDist->Write();
    XPt->Write();
    leadingMuonPt->Write();
    trailingMuonPt->Write();
    InvariantMass->Write();
    
    delete file;
    // Write endtag. Overwrite initialization info with new cross sections.
    myLHA.closeLHEF(true);
    delete myUserHooks;

    //----------------------------------------------------------

  // Done.
  return 0;
}









/*
 MuonSpectrum -> Fill(pythia.event[i].e());
 MuonMass -> Fill(pythia.event[i].m());
 if(pythia.event[i].pT()>3) MuonpT -> Fill(pythia.event[i].pT());
 Muoneta -> Fill(pythia.event[i].eta());
 
 ThisIsHiggs= (pythia.event[i].idAbs() == 25);
 if (ThisIsHiggs) {
 ThisHiggs2muons = ThisIsHiggs && ( pythia.event[i].daughter1() != pythia.event[i].daughter2());
 if (ThisHiggs2muons) {
 
 MuonIndex1 = pythia.event[i].daughter1();
 MuonIndex2 = pythia.event[i].daughter2();
 
 Muon1 = pythia.event[MuonIndex1];
 Muon2 = pythia.event[MuonIndex2];
 InvirantMass =  sqrt( - pow((Muon1.px()+Muon2.px()),2.0) - pow((Muon1.py()+Muon2.py()),2.0) - pow((Muon1.pz()+Muon2.pz()),2.0) + pow((Muon1.e()+Muon2.e()),2.0) );
 
 cout << "A higgs -> muons found !!!  Higgs# = " << i << " m0="<<pythia.event[i].m()<< " ,muon# ="<< MuonIndex1 <<" "<<MuonIndex2 << " ,Invirant mass is "<< InvirantMass <<endl;
 
 //mult->Fill(InvirantMass);
 eta.fill(InvirantMass);
 }
 }
 
 
 
 if (pythia.event[i].idAbs() == 25){
 cout << "This particle " << i << " is Higgs " ;
 cout << " and its m=" << pythia.event[i].m() << " ,e=" << pythia.event[i].e() << " ,dot1=" << pythia.event[i].daughter1()<< " ,dot2=" << pythia.event[i].daughter2()<< endl;
 iTop = i;}
 
 if (pythia.event[i].isFinal() && pythia.event[i].isCharged()) ++nCharged;
 
 if (pythia.event[i].idAbs() == 13){
 cout << "This particle " << i << " is muon " ;
 cout << " and its pT=" << pythia.event[i].pT() << " ,e=" << pythia.event[i].e() << " ,mother1=" << pythia.event[i].mother1()<< " ,mother2=" << pythia.event[i].mother2()<< endl;}
 
 if (pythia.event[i].idAbs() == 6){
 cout << "This particle " << i << " is top " ;
 cout << " and its m=" << pythia.event[i].m() << " ,e=" << pythia.event[i].e() << " ,daughter1=" << pythia.event[i].daughter1()<< " ,daughter2=" << pythia.event[i].daughter2()<< endl;}
 */




//pT.fill( pythia.event[iTop].pT() );
//eta.fill( pythia.event[iTop].eta() );
//-------------------------------------------------------------
//End of event loop. Statistics.





//cout << pT << eta;