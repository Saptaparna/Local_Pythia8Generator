//  Root histgram combiner
//  combiner.cc
//  Orignially composed by Ziheng on Jun/27/2016
//  @ Northwestern University
//
//  Put three .root files in the same directory
//  and run command root -x combiner.cc
//
//

#define TransverseFILE      "BeforeCut/B2bX4l_8TeV_misgroup/tran.root"
#define LongitudinalFILE    "BeforeCut/B2bX4l_8TeV_misgroup/long.root"
#define ScalarFILE          "BeforeCut/B2bX4l_8TeV_misgroup/scal.root"

#define TransverseFILE2      "AfterbMuCut/B2bX4l_8TeV_misgroup/tran.root"
#define LongitudinalFILE2    "AfterbMuCut/B2bX4l_8TeV_misgroup/long.root"
#define ScalarFILE2          "AfterbMuCut/B2bX4l_8TeV_misgroup/scal.root"


{
    gStyle->SetTitleFontSize(0.07);
    gStyle->SetPalette(1);
    gStyle->SetOptStat(0);
    //gStyle->SetLabelSize(0.8,"X");
    //gStyle->SetTitleXSize(5);
    
    
    TCanvas *playground1 = new TCanvas("playground1","playground1",800,900);
    TCanvas *playground2 = new TCanvas("playground2","playground2",400,900);
    TCanvas *playground3 = new TCanvas("playground3","playground3",400,900);
    TCanvas *playground4 = new TCanvas("playground4","playground4",800,900);

    //-----------------------Start IO Files-----------------------
    TFile *TransverseRootFile = new TFile(TransverseFILE);
    if (TransverseRootFile->IsZombie()) {
        cout << "Error opening file " << TransverseFILE  << endl;
        exit(-1);
    }
    else cout << "open file " << TransverseFILE  << endl;
    
    TFile *LongitudinalRootFile = new TFile(LongitudinalFILE);
    if (LongitudinalRootFile->IsZombie()) {
        cout << "Error opening file " << LongitudinalFILE << endl;
        exit(-1);
    }
    else cout << "open file " << LongitudinalFILE << endl;
    
    TFile *ScalarRootFile = new TFile(ScalarFILE);
    if (ScalarRootFile->IsZombie()) {
        cout << "Error opening file " << ScalarFILE << endl;
        exit(-1);
    }
    else cout << "open file " << ScalarFILE << endl;
        
        
    TFile *TransverseRootFile2 = new TFile(TransverseFILE2);
    if (TransverseRootFile2->IsZombie()) {
        cout << "Error opening file " << TransverseFILE2  << endl;
        exit(-1);
    }
    else cout << "open file " << TransverseFILE2  << endl;
    
    TFile *LongitudinalRootFile2 = new TFile(LongitudinalFILE2);
    if (LongitudinalRootFile2->IsZombie()) {
        cout << "Error opening file " << LongitudinalFILE2 << endl;
        exit(-1);
    }
    else cout << "open file " << LongitudinalFILE2 << endl;
    
    TFile *ScalarRootFile2 = new TFile(ScalarFILE2);
    if (ScalarRootFile2->IsZombie()) {
        cout << "Error opening file " << ScalarFILE2 << endl;
        exit(-1);
    }
    else cout << "open file " << ScalarFILE2 << endl;
        
        
        

    //-------------------------End IO Files-----------------------
    // muons
    playground1->Divide(2,3);
      playground1->cd(1);
        
        TH1F *Tran = (TH1F*)TransverseRootFile.Get("Muon1pT");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("Muon1pT");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("Muon1pT");
        
        TH1F *Tran2 = (TH1F*)TransverseRootFile2.Get("Muon1pT");
        TH1F *Long2 = (TH1F*)LongitudinalRootFile2.Get("Muon1pT");
        TH1F *Scal2 = (TH1F*)ScalarRootFile2.Get("Muon1pT");
        
        
        Long -> SetLineColor(2);
        Long -> SetLineStyle(3);
        Long -> GetXaxis() ->SetTitle("pT_mu1");
        Long -> GetYaxis() ->SetTitle("Count");
        Long->GetXaxis()->SetLabelSize(0.055);
        Long->GetXaxis()->SetTitleSize(0.055);
        Long->GetXaxis()->SetTitleOffset(0.9);
        Long->GetYaxis()->SetLabelSize(0.05);
        Long->GetYaxis()->SetTitleSize(0.05);
        Long -> Draw();
        Tran -> SetLineColor(4);
        Tran -> SetLineStyle(3);
        Tran -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> SetLineStyle(3);
        Scal -> Draw("same");

        
        Long2 -> SetLineColor(2);
        Long2 -> SetLineWidth(2);
        Long2 -> Draw("same");
        Tran2 -> SetLineColor(4);
        Tran2 -> SetLineWidth(2);
        Tran2 -> Draw("same");
        Scal2 -> SetLineColor(1);
        Scal2 -> SetLineWidth(2);
        Scal2 -> Draw("same");
        
        
      playground1->cd(5);
  
        TH1F *Tran = (TH1F*)TransverseRootFile.Get("Muon2pT");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("Muon2pT");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("Muon2pT");
        
        TH1F *Tran2 = (TH1F*)TransverseRootFile2.Get("Muon2pT");
        TH1F *Long2 = (TH1F*)LongitudinalRootFile2.Get("Muon2pT");
        TH1F *Scal2 = (TH1F*)ScalarRootFile2.Get("Muon2pT");
        
        
        Tran -> SetLineColor(4);
        Tran -> SetLineStyle(3);
        Tran -> GetXaxis() ->SetTitle("pT_mu2");
        Tran -> GetYaxis() ->SetTitle("Count");
        Tran->GetXaxis()->SetLabelSize(0.055);
        Tran->GetXaxis()->SetTitleSize(0.055);
        Tran->GetXaxis()->SetTitleOffset(0.9);
        Tran->GetYaxis()->SetLabelSize(0.05);
        Tran->GetYaxis()->SetTitleSize(0.05);
        Tran -> Draw();
        Long -> SetLineColor(2);
        Long -> SetLineStyle(3);
        Long -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> SetLineStyle(3);
        Scal -> Draw("same");
        
        
        Long2 -> SetLineColor(2);
        Long2 -> SetLineWidth(2);
        Long2 -> Draw("same");
        Tran2 -> SetLineColor(4);
        Tran2 -> SetLineWidth(2);
        Tran2 -> Draw("same");
        Scal2 -> SetLineColor(1);
        Scal2 -> SetLineWidth(2);
        Scal2 -> Draw("same");
        
        
      playground1->cd(4);
        
        TH1F *Tran = (TH1F*)TransverseRootFile.Get("MuMupT");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("MuMupT");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("MuMupT");
        
        TH1F *Tran2 = (TH1F*)TransverseRootFile2.Get("MuMupT");
        TH1F *Long2 = (TH1F*)LongitudinalRootFile2.Get("MuMupT");
        TH1F *Scal2 = (TH1F*)ScalarRootFile2.Get("MuMupT");
        
        
        Long -> SetLineColor(2);
        Long -> SetLineStyle(3);
        Long -> GetXaxis() ->SetTitle("pT_mumu");
        Long -> GetYaxis() ->SetTitle("Count");
        Long->GetXaxis()->SetLabelSize(0.055);
        Long->GetXaxis()->SetTitleSize(0.055);
        Long->GetXaxis()->SetTitleOffset(0.9);
        Long->GetYaxis()->SetLabelSize(0.05);
        Long->GetYaxis()->SetTitleSize(0.05);
        Long -> Draw();
        Tran -> SetLineColor(4);
        Tran -> SetLineStyle(3);
        Tran -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> SetLineStyle(3);
        Scal -> Draw("same");
        
        
        Long2 -> SetLineColor(2);
        Long2 -> SetLineWidth(2);
        Long2 -> Draw("same");
        Tran2 -> SetLineColor(4);
        Tran2 -> SetLineWidth(2);
        Tran2 -> Draw("same");
        Scal2 -> SetLineColor(1);
        Scal2 -> SetLineWidth(2);
        Scal2 -> Draw("same");
        

      playground1->cd(3);
        
        TH1F *Tran = (TH1F*)TransverseRootFile.Get("Muon1eta");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("Muon1eta");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("Muon1eta");
        
        TH1F *Tran2 = (TH1F*)TransverseRootFile2.Get("Muon1eta");
        TH1F *Long2 = (TH1F*)LongitudinalRootFile2.Get("Muon1eta");
        TH1F *Scal2 = (TH1F*)ScalarRootFile2.Get("Muon1eta");
        
        
        Long -> SetLineColor(2);
        Long -> SetLineStyle(3);
        Long -> GetXaxis() ->SetTitle("eta_mu1");
        Long -> GetYaxis() ->SetTitle("Count");
        Long->GetXaxis()->SetLabelSize(0.055);
        Long->GetXaxis()->SetTitleSize(0.055);
        Long->GetXaxis()->SetTitleOffset(0.9);
        Long->GetYaxis()->SetLabelSize(0.05);
        Long->GetYaxis()->SetTitleSize(0.05);
        Long -> Draw();
        Tran -> SetLineColor(4);
        Tran -> SetLineStyle(3);
        Tran -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> SetLineStyle(3);
        Scal -> Draw("same");
        
        
        Long2 -> SetLineColor(2);
        Long2 -> SetLineWidth(2);
        Long2 -> Draw("same");
        Tran2 -> SetLineColor(4);
        Tran2 -> SetLineWidth(2);
        Tran2 -> Draw("same");
        Scal2 -> SetLineColor(1);
        Scal2 -> SetLineWidth(2);
        Scal2 -> Draw("same");
        


      playground1->cd(2);
  
        TH1F *Tran = (TH1F*)TransverseRootFile.Get("Muon2eta");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("Muon2eta");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("Muon2eta");
        
        TH1F *Tran2 = (TH1F*)TransverseRootFile2.Get("Muon2eta");
        TH1F *Long2 = (TH1F*)LongitudinalRootFile2.Get("Muon2eta");
        TH1F *Scal2 = (TH1F*)ScalarRootFile2.Get("Muon2eta");
        
        
        Long -> SetLineColor(2);
        Long -> SetLineStyle(3);
        Long -> GetXaxis() ->SetTitle("eta_mu2");
        Long -> GetYaxis() ->SetTitle("Count");
        Long->GetXaxis()->SetLabelSize(0.055);
        Long->GetXaxis()->SetTitleSize(0.055);
        Long->GetXaxis()->SetTitleOffset(0.9);
        Long->GetYaxis()->SetLabelSize(0.05);
        Long->GetYaxis()->SetTitleSize(0.05);
        Long -> Draw();
        Tran -> SetLineColor(4);
        Tran -> SetLineStyle(3);
        Tran -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> SetLineStyle(3);
        Scal -> Draw("same");
        
        
        Long2 -> SetLineColor(2);
        Long2 -> SetLineWidth(2);
        Long2 -> Draw("same");
        Tran2 -> SetLineColor(4);
        Tran2 -> SetLineWidth(2);
        Tran2 -> Draw("same");
        Scal2 -> SetLineColor(1);
        Scal2 -> SetLineWidth(2);
        Scal2 -> Draw("same");


    playground1->cd(6);
        
        TH1F *Tran = (TH1F*)TransverseRootFile.Get("IMass");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("IMass");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("IMass");
        
        TH1F *Tran2 = (TH1F*)TransverseRootFile2.Get("IMass");
        TH1F *Long2 = (TH1F*)LongitudinalRootFile2.Get("IMass");
        TH1F *Scal2 = (TH1F*)ScalarRootFile2.Get("IMass");
        
        
        Long -> SetLineColor(2);
        Long -> SetLineStyle(3);
        Long -> GetXaxis() ->SetTitle("Mass_mumu");
        Long -> GetYaxis() ->SetTitle("Count");
        Long->GetXaxis()->SetLabelSize(0.055);
        Long->GetXaxis()->SetTitleSize(0.055);
        Long->GetXaxis()->SetTitleOffset(0.9);
        Long->GetYaxis()->SetLabelSize(0.05);
        Long->GetYaxis()->SetTitleSize(0.05);
        Long -> Draw();
        Tran -> SetLineColor(4);
        Tran -> SetLineStyle(3);
        Tran -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> SetLineStyle(3);
        Scal -> Draw("same");
        
        
        Long2 -> SetLineColor(2);
        Long2 -> SetLineWidth(2);
        Long2 -> Draw("same");
        Tran2 -> SetLineColor(4);
        Tran2 -> SetLineWidth(2);
        Tran2 -> Draw("same");
        Scal2 -> SetLineColor(1);
        Scal2 -> SetLineWidth(2);
        Scal2 -> Draw("same");
        
    
    
    // separation
    playground2->Divide(1,3);
        
      playground2->cd(1);
        
        TH1F *Tran = (TH1F*)TransverseRootFile.Get("MuMupTratio");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("MuMupTratio");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("MuMupTratio");
        
        TH1F *Tran2 = (TH1F*)TransverseRootFile2.Get("MuMupTratio");
        TH1F *Long2 = (TH1F*)LongitudinalRootFile2.Get("MuMupTratio");
        TH1F *Scal2 = (TH1F*)ScalarRootFile2.Get("MuMupTratio");
        
        
        Long -> SetLineColor(2);
        Long -> SetLineStyle(3);
        Long -> GetXaxis() ->SetTitle("(pT/M)_mumu");
        Long -> GetYaxis() ->SetTitle("Count");
        Long->GetXaxis()->SetLabelSize(0.055);
        Long->GetXaxis()->SetTitleSize(0.055);
        Long->GetXaxis()->SetTitleOffset(0.9);
        Long->GetYaxis()->SetLabelSize(0.05);
        Long->GetYaxis()->SetTitleSize(0.05);
        Long -> Draw();
        Tran -> SetLineColor(4);
        Tran -> SetLineStyle(3);
        Tran -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> SetLineStyle(3);
        Scal -> Draw("same");
        
        
        Long2 -> SetLineColor(2);
        Long2 -> SetLineWidth(2);
        Long2 -> Draw("same");
        Tran2 -> SetLineColor(4);
        Tran2 -> SetLineWidth(2);
        Tran2 -> Draw("same");
        Scal2 -> SetLineColor(1);
        Scal2 -> SetLineWidth(2);
        Scal2 -> Draw("same");
        
        
      playground2->cd(2);
        
        TH1F *Tran = (TH1F*)TransverseRootFile.Get("Deltaeta");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("Deltaeta");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("Deltaeta");
        
        TH1F *Tran2 = (TH1F*)TransverseRootFile2.Get("Deltaeta");
        TH1F *Long2 = (TH1F*)LongitudinalRootFile2.Get("Deltaeta");
        TH1F *Scal2 = (TH1F*)ScalarRootFile2.Get("Deltaeta");
        
        
        Long -> SetLineColor(2);
        Long -> SetLineStyle(3);
        Long -> GetXaxis() ->SetTitle("DeltaEta_mumu");
        Long -> GetYaxis() ->SetTitle("Count");
        Long->GetXaxis()->SetLabelSize(0.055);
        Long->GetXaxis()->SetTitleSize(0.055);
        Long->GetXaxis()->SetTitleOffset(0.9);
        Long->GetYaxis()->SetLabelSize(0.05);
        Long->GetYaxis()->SetTitleSize(0.05);
        Long -> Draw();
        Tran -> SetLineColor(4);
        Tran -> SetLineStyle(3);
        Tran -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> SetLineStyle(3);
        Scal -> Draw("same");
        
        
        Long2 -> SetLineColor(2);
        Long2 -> SetLineWidth(2);
        Long2 -> Draw("same");
        Tran2 -> SetLineColor(4);
        Tran2 -> SetLineWidth(2);
        Tran2 -> Draw("same");
        Scal2 -> SetLineColor(1);
        Scal2 -> SetLineWidth(2);
        Scal2 -> Draw("same");

      playground2->cd(3);
  
        TH1F *Tran = (TH1F*)TransverseRootFile.Get("DeltaR2");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("DeltaR2");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("DeltaR2");
        
        TH1F *Tran2 = (TH1F*)TransverseRootFile2.Get("DeltaR2");
        TH1F *Long2 = (TH1F*)LongitudinalRootFile2.Get("DeltaR2");
        TH1F *Scal2 = (TH1F*)ScalarRootFile2.Get("DeltaR2");
        
        
        Long -> SetLineColor(2);
        Long -> SetLineStyle(3);
        Long -> GetXaxis() ->SetTitle("DeltaPhi_dimuomb");
        Long -> GetYaxis() ->SetTitle("Count");
        Long->GetXaxis()->SetLabelSize(0.055);
        Long->GetXaxis()->SetTitleSize(0.055);
        Long->GetXaxis()->SetTitleOffset(0.9);
        Long->GetYaxis()->SetLabelSize(0.05);
        Long->GetYaxis()->SetTitleSize(0.05);
        Long -> Draw();
        Tran -> SetLineColor(4);
        Tran -> SetLineStyle(3);
        Tran -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> SetLineStyle(3);
        Scal -> Draw("same");
        
        
        Long2 -> SetLineColor(2);
        Long2 -> SetLineWidth(2);
        Long2 -> Draw("same");
        Tran2 -> SetLineColor(4);
        Tran2 -> SetLineWidth(2);
        Tran2 -> Draw("same");
        Scal2 -> SetLineColor(1);
        Scal2 -> SetLineWidth(2);
        Scal2 -> Draw("same");
        
      playground2->cd(2);
        
        TH1F *Tran = (TH1F*)TransverseRootFile.Get("DeltaR");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("DeltaR");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("DeltaR");
        
        TH1F *Tran2 = (TH1F*)TransverseRootFile2.Get("DeltaR");
        TH1F *Long2 = (TH1F*)LongitudinalRootFile2.Get("DeltaR");
        TH1F *Scal2 = (TH1F*)ScalarRootFile2.Get("DeltaR");
        
        
        Long -> SetLineColor(2);
        Long -> SetLineStyle(3);
        Long -> GetXaxis() ->SetTitle("DeltaR_mumu");
        Long -> GetYaxis() ->SetTitle("Count");
        Long->GetXaxis()->SetLabelSize(0.055);
        Long->GetXaxis()->SetTitleSize(0.055);
        Long->GetXaxis()->SetTitleOffset(0.9);
        Long->GetYaxis()->SetLabelSize(0.05);
        Long->GetYaxis()->SetTitleSize(0.05);
        Long -> Draw();
        Tran -> SetLineColor(4);
        Tran -> SetLineStyle(3);
        Tran -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> SetLineStyle(3);
        Scal -> Draw("same");
        
        
        Long2 -> SetLineColor(2);
        Long2 -> SetLineWidth(2);
        Long2 -> Draw("same");
        Tran2 -> SetLineColor(4);
        Tran2 -> SetLineWidth(2);
        Tran2 -> Draw("same");
        Scal2 -> SetLineColor(1);
        Scal2 -> SetLineWidth(2);
        Scal2 -> Draw("same");

      
    playground3->Divide(1,3);
        playground3->cd(1);
        
        
        TH1F *Tran = (TH1F*)TransverseRootFile.Get("bpT");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("bpT");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("bpT");
        
        TH1F *Tran2 = (TH1F*)TransverseRootFile2.Get("bpT");
        TH1F *Long2 = (TH1F*)LongitudinalRootFile2.Get("bpT");
        TH1F *Scal2 = (TH1F*)ScalarRootFile2.Get("bpT");
        
        
        Long -> SetLineColor(2);
        Long -> SetLineStyle(3);
        Long -> GetXaxis() ->SetTitle("pT_b");
        Long -> GetYaxis() ->SetTitle("Count");
        Long->GetXaxis()->SetLabelSize(0.055);
        Long->GetXaxis()->SetTitleSize(0.055);
        Long->GetXaxis()->SetTitleOffset(0.9);
        Long->GetYaxis()->SetLabelSize(0.05);
        Long->GetYaxis()->SetTitleSize(0.05);
        Long -> Draw();
        Tran -> SetLineColor(4);
        Tran -> SetLineStyle(3);
        Tran -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> SetLineStyle(3);
        Scal -> Draw("same");
        
        
        Long2 -> SetLineColor(2);
        Long2 -> SetLineWidth(2);
        Long2 -> Draw("same");
        Tran2 -> SetLineColor(4);
        Tran2 -> SetLineWidth(2);
        Tran2 -> Draw("same");
        Scal2 -> SetLineColor(1);
        Scal2 -> SetLineWidth(2);
        Scal2 -> Draw("same");
        


        playground3->cd(2);
        
        
        TH1F *Tran = (TH1F*)TransverseRootFile.Get("beta");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("beta");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("beta");
        
        TH1F *Tran2 = (TH1F*)TransverseRootFile2.Get("beta");
        TH1F *Long2 = (TH1F*)LongitudinalRootFile2.Get("beta");
        TH1F *Scal2 = (TH1F*)ScalarRootFile2.Get("beta");
        
        
        Long -> SetLineColor(2);
        Long -> SetLineStyle(3);
        Long -> GetXaxis() ->SetTitle("eta_b");
        Long -> GetYaxis() ->SetTitle("Count");
        Long->GetXaxis()->SetLabelSize(0.055);
        Long->GetXaxis()->SetTitleSize(0.055);
        Long->GetXaxis()->SetTitleOffset(0.9);
        Long->GetYaxis()->SetLabelSize(0.05);
        Long->GetYaxis()->SetTitleSize(0.05);
        Long -> Draw();
        Tran -> SetLineColor(4);
        Tran -> SetLineStyle(3);
        Tran -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> SetLineStyle(3);
        Scal -> Draw("same");
        
        
        Long2 -> SetLineColor(2);
        Long2 -> SetLineWidth(2);
        Long2 -> Draw("same");
        Tran2 -> SetLineColor(4);
        Tran2 -> SetLineWidth(2);
        Tran2 -> Draw("same");
        Scal2 -> SetLineColor(1);
        Scal2 -> SetLineWidth(2);
        Scal2 -> Draw("same");

        
        
        playground3->cd(3);
        
        
        TH1F *Tran = (TH1F*)TransverseRootFile.Get("IMassbmumu");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("IMassbmumu");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("IMassbmumu");
        
        TH1F *Tran2 = (TH1F*)TransverseRootFile2.Get("IMassbmumu");
        TH1F *Long2 = (TH1F*)LongitudinalRootFile2.Get("IMassbmumu");
        TH1F *Scal2 = (TH1F*)ScalarRootFile2.Get("IMassbmumu");
        
        
        Long -> SetLineColor(2);
        Long -> SetLineStyle(3);
        Long -> GetXaxis() ->SetTitle("m_bmumu");
        Long -> GetYaxis() ->SetTitle("Count");
        Long->GetXaxis()->SetLabelSize(0.055);
        Long->GetXaxis()->SetTitleSize(0.055);
        Long->GetXaxis()->SetTitleOffset(0.9);
        Long->GetYaxis()->SetLabelSize(0.05);
        Long->GetYaxis()->SetTitleSize(0.05);
        Long -> Draw();
        Tran -> SetLineColor(4);
        Tran -> SetLineStyle(3);
        Tran -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> SetLineStyle(3);
        Scal -> Draw("same");
        
        
        Long2 -> SetLineColor(2);
        Long2 -> SetLineWidth(2);
        Long2 -> Draw("same");
        Tran2 -> SetLineColor(4);
        Tran2 -> SetLineWidth(2);
        Tran2 -> Draw("same");
        Scal2 -> SetLineColor(1);
        Scal2 -> SetLineWidth(2);
        Scal2 -> Draw("same");

    
        
        
    //invariant mass
    /*playground3->Divide(3);
      playground3->cd(1);
        TH1F *Tran = (TH1F*)TransverseRootFile.Get("IMass");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("IMass");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("IMass");
        
        Tran -> SetLineColor(4);
        Tran -> GetXaxis() ->SetTitle("m_mumu");
        Tran -> GetYaxis() ->SetTitle("Count");
        Tran -> Draw();
        Long -> SetLineColor(2);
        Long -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> Draw("same");



      playground3->cd(2);
        TH1F *Tran = (TH1F*)TransverseRootFile.Get("IMass2");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("IMass2");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("IMass2");
        
        Tran -> SetLineColor(4);
        Tran -> GetXaxis() ->SetTitle("m_bmumu");
        Tran -> GetYaxis() ->SetTitle("Count");
        Tran -> Draw();
        Long -> SetLineColor(2);
        Long -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> Draw("same");
     
     playground3->Divide(3,2);
     playground3->cd(1);
     
     TH1F *Tran = (TH1F*)TransverseRootFile.Get("MuMupTratio");
     TH1F *Long = (TH1F*)LongitudinalRootFile.Get("MuMupTratio");
     TH1F *Scal = (TH1F*)ScalarRootFile.Get("MuMupTratio");
     
     Long -> SetLineColor(2);
     Long -> GetXaxis() ->SetTitle("(pT/M)_mumu");
     Long -> GetYaxis() ->SetTitle("Count");
     Long->GetXaxis()->SetLabelSize(0.055);
     Long->GetXaxis()->SetTitleSize(0.055);
     Long->GetXaxis()->SetTitleOffset(0.9);
     Long->GetYaxis()->SetLabelSize(0.05);
     Long->GetYaxis()->SetTitleSize(0.05);
     Long -> Draw();
     Tran -> SetLineColor(4);
     Tran -> Draw("same");
     Scal -> SetLineColor(1);
     Scal -> Draw("same");

    */
    playground4->Divide(2,3);
        playground4->cd(1);
        
        
        TH1F *Tran = (TH1F*)TransverseRootFile.Get("DeltaRPolars");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("DeltaRPolars");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("DeltaRPolars");
        
        TH1F *Tran2 = (TH1F*)TransverseRootFile2.Get("DeltaRPolars");
        TH1F *Long2 = (TH1F*)LongitudinalRootFile2.Get("DeltaRPolars");
        TH1F *Scal2 = (TH1F*)ScalarRootFile2.Get("DeltaRPolars");
        
        
        Long -> SetLineColor(2);
        Long -> SetLineStyle(3);
        Long -> GetXaxis() ->SetTitle("DeltaR_dimuons");
        Long -> GetYaxis() ->SetTitle("Count");
        Long->GetXaxis()->SetLabelSize(0.055);
        Long->GetXaxis()->SetTitleSize(0.055);
        Long->GetXaxis()->SetTitleOffset(0.9);
        Long->GetYaxis()->SetLabelSize(0.05);
        Long->GetYaxis()->SetTitleSize(0.05);
        Long -> Draw();
        Tran -> SetLineColor(4);
        Tran -> SetLineStyle(3);
        Tran -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> SetLineStyle(3);
        Scal -> Draw("same");
        
        
        Long2 -> SetLineColor(2);
        Long2 -> SetLineWidth(2);
        Long2 -> Draw("same");
        Tran2 -> SetLineColor(4);
        Tran2 -> SetLineWidth(2);
        Tran2 -> Draw("same");
        Scal2 -> SetLineColor(1);
        Scal2 -> SetLineWidth(2);
        Scal2 -> Draw("same");
        
  
        playground4->cd(3);
        
        
        TH1F *Tran = (TH1F*)TransverseRootFile.Get("MuonFirstpT");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("MuonFirstpT");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("MuonFirstpT");
        
        TH1F *Tran2 = (TH1F*)TransverseRootFile2.Get("MuonFirstpT");
        TH1F *Long2 = (TH1F*)LongitudinalRootFile2.Get("MuonFirstpT");
        TH1F *Scal2 = (TH1F*)ScalarRootFile2.Get("MuonFirstpT");
        
        
        Long -> SetLineColor(2);
        Long -> SetLineStyle(3);
        Long -> GetXaxis() ->SetTitle("pT_mu_1st");
        Long -> GetYaxis() ->SetTitle("Count");
        Long->GetXaxis()->SetLabelSize(0.055);
        Long->GetXaxis()->SetTitleSize(0.055);
        Long->GetXaxis()->SetTitleOffset(0.9);
        Long->GetYaxis()->SetLabelSize(0.05);
        Long->GetYaxis()->SetTitleSize(0.05);
        Long -> Draw();
        Tran -> SetLineColor(4);
        Tran -> SetLineStyle(3);
        Tran -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> SetLineStyle(3);
        Scal -> Draw("same");
        
        
        Long2 -> SetLineColor(2);
        Long2 -> SetLineWidth(2);
        Long2 -> Draw("same");
        Tran2 -> SetLineColor(4);
        Tran2 -> SetLineWidth(2);
        Tran2 -> Draw("same");
        Scal2 -> SetLineColor(1);
        Scal2 -> SetLineWidth(2);
        Scal2 -> Draw("same");
        
        
        

        
        playground4->cd(4);
        
        
        TH1F *Tran = (TH1F*)TransverseRootFile.Get("MuonThirdpT");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("MuonThirdpT");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("MuonThirdpT");
        
        TH1F *Tran2 = (TH1F*)TransverseRootFile2.Get("MuonThirdpT");
        TH1F *Long2 = (TH1F*)LongitudinalRootFile2.Get("MuonThirdpT");
        TH1F *Scal2 = (TH1F*)ScalarRootFile2.Get("MuonThirdpT");
        
        
        Long -> SetLineColor(2);
        Long -> SetLineStyle(3);
        Long -> GetXaxis() ->SetTitle("pT_mu_3rd");
        Long -> GetYaxis() ->SetTitle("Count");
        Long->GetXaxis()->SetLabelSize(0.055);
        Long->GetXaxis()->SetTitleSize(0.055);
        Long->GetXaxis()->SetTitleOffset(0.9);
        Long->GetYaxis()->SetLabelSize(0.05);
        Long->GetYaxis()->SetTitleSize(0.05);
        Long -> Draw();
        Tran -> SetLineColor(4);
        Tran -> SetLineStyle(3);
        Tran -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> SetLineStyle(3);
        Scal -> Draw("same");
        
        
        Long2 -> SetLineColor(2);
        Long2 -> SetLineWidth(2);
        Long2 -> Draw("same");
        Tran2 -> SetLineColor(4);
        Tran2 -> SetLineWidth(2);
        Tran2 -> Draw("same");
        Scal2 -> SetLineColor(1);
        Scal2 -> SetLineWidth(2);
        Scal2 -> Draw("same");
        
        
        playground4->cd(5);
        
        
        TH1F *Tran = (TH1F*)TransverseRootFile.Get("MuonSecondpT");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("MuonSecondpT");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("MuonSecondpT");
        
        TH1F *Tran2 = (TH1F*)TransverseRootFile2.Get("MuonSecondpT");
        TH1F *Long2 = (TH1F*)LongitudinalRootFile2.Get("MuonSecondpT");
        TH1F *Scal2 = (TH1F*)ScalarRootFile2.Get("MuonSecondpT");
        
        
        Long -> SetLineColor(2);
        Long -> SetLineStyle(3);
        Long -> GetXaxis() ->SetTitle("pT_mu_2nd");
        Long -> GetYaxis() ->SetTitle("Count");
        Long->GetXaxis()->SetLabelSize(0.055);
        Long->GetXaxis()->SetTitleSize(0.055);
        Long->GetXaxis()->SetTitleOffset(0.9);
        Long->GetYaxis()->SetLabelSize(0.05);
        Long->GetYaxis()->SetTitleSize(0.05);
        Long -> Draw();
        Tran -> SetLineColor(4);
        Tran -> SetLineStyle(3);
        Tran -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> SetLineStyle(3);
        Scal -> Draw("same");
        
        
        Long2 -> SetLineColor(2);
        Long2 -> SetLineWidth(2);
        Long2 -> Draw("same");
        Tran2 -> SetLineColor(4);
        Tran2 -> SetLineWidth(2);
        Tran2 -> Draw("same");
        Scal2 -> SetLineColor(1);
        Scal2 -> SetLineWidth(2);
        Scal2 -> Draw("same");
        
        
        playground4->cd(6);
        
        
        TH1F *Tran = (TH1F*)TransverseRootFile.Get("MuonForthpT");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("MuonForthpT");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("MuonForthpT");
        
        TH1F *Tran2 = (TH1F*)TransverseRootFile2.Get("MuonForthpT");
        TH1F *Long2 = (TH1F*)LongitudinalRootFile2.Get("MuonForthpT");
        TH1F *Scal2 = (TH1F*)ScalarRootFile2.Get("MuonForthpT");
        
        
        Long -> SetLineColor(2);
        Long -> SetLineStyle(3);
        Long -> GetXaxis() ->SetTitle("pT_mu_4th");
        Long -> GetYaxis() ->SetTitle("Count");
        Long->GetXaxis()->SetLabelSize(0.055);
        Long->GetXaxis()->SetTitleSize(0.055);
        Long->GetXaxis()->SetTitleOffset(0.9);
        Long->GetYaxis()->SetLabelSize(0.05);
        Long->GetYaxis()->SetTitleSize(0.05);
        Long -> Draw();
        Tran -> SetLineColor(4);
        Tran -> SetLineStyle(3);
        Tran -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> SetLineStyle(3);
        Scal -> Draw("same");
        
        
        Long2 -> SetLineColor(2);
        Long2 -> SetLineWidth(2);
        Long2 -> Draw("same");
        Tran2 -> SetLineColor(4);
        Tran2 -> SetLineWidth(2);
        Tran2 -> Draw("same");
        Scal2 -> SetLineColor(1);
        Scal2 -> SetLineWidth(2);
        Scal2 -> Draw("same");
        

        
        
        
    playground1->SaveAs("1muons.pdf");
    playground2->SaveAs("2separation.pdf");
    playground3->SaveAs("3mass.pdf");
    playground4->SaveAs("4fourlepton.pdf");
}
