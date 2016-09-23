//  Root histgram combiner
//  combiner.cc
//  Orignially composed by Ziheng on Jun/27/2016
//  @ Northwestern University
//
//  Put three .root files in the same directory
//  and run command root -x combiner.cc
//
//

#define TransverseFILE      "tran.root"
#define LongitudinalFILE    "long.root"
#define ScalarFILE          "scal.root"



{
    gStyle->SetPalette(1);
    gStyle->SetOptStat(0);
    TCanvas *playground1 = new TCanvas("playground1","playground1",1200,600);
    TCanvas *playground2 = new TCanvas("playground2","playground2",1200,600);
    //TCanvas *playground3 = new TCanvas("playground3","playground3",1200,300);

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
    //-------------------------End IO Files-----------------------
    // muons
    playground1->Divide(3,2);
      playground1->cd(1);
        
        TH1F *Tran = (TH1F*)TransverseRootFile.Get("Muon1pT");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("Muon1pT");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("Muon1pT");
        
        Long -> SetLineColor(2);
        Long -> GetXaxis() ->SetTitle("pT_mu1");
        Long -> GetYaxis() ->SetTitle("Count");
        Long -> Draw();
        Tran -> SetLineColor(4);
        Tran -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> Draw("same");

        
      playground1->cd(2);
  
        TH1F *Tran = (TH1F*)TransverseRootFile.Get("Muon2pT");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("Muon2pT");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("Muon2pT");
        
        Tran -> SetLineColor(4);
        Tran -> GetXaxis() ->SetTitle("pT_mu2");
        Tran -> GetYaxis() ->SetTitle("Count");
        Tran -> Draw();
        Long -> SetLineColor(2);
        Long -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> Draw("same");

   
        
      playground1->cd(3);
        
        TH1F *Tran = (TH1F*)TransverseRootFile.Get("MuMupT");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("MuMupT");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("MuMupT");
        
        Tran -> SetLineColor(4);
        Tran -> GetXaxis() ->SetTitle("pT_mumu");
        Tran -> GetYaxis() ->SetTitle("Count");
        Tran -> Draw();
        Long -> SetLineColor(2);
        Long -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> Draw("same");


      playground1->cd(4);
        
        TH1F *Tran = (TH1F*)TransverseRootFile.Get("Muon1eta");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("Muon1eta");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("Muon1eta");
        
        Tran -> SetLineColor(4);
        Tran -> GetXaxis() ->SetTitle("eta_mu1");
        Tran -> GetYaxis() ->SetTitle("Count");
        Tran -> Draw();
        Long -> SetLineColor(2);
        Long -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> Draw("same");


      playground1->cd(5);
  
        TH1F *Tran = (TH1F*)TransverseRootFile.Get("Muon2eta");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("Muon2eta");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("Muon2eta");
        
        Tran -> SetLineColor(4);
        Tran -> GetXaxis() ->SetTitle("eta_mu2");
        Tran -> GetYaxis() ->SetTitle("Count");
        Tran -> Draw();
        Long -> SetLineColor(2);
        Long -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> Draw("same");

    playground1->cd(6);
        
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


        
    
    
    // separation
    playground2->Divide(3,2);
      playground2->cd(1);
        
        TH1F *Tran = (TH1F*)TransverseRootFile.Get("Deltaeta");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("Deltaeta");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("Deltaeta");
        
        Long -> SetLineColor(2);
        Long -> GetXaxis() ->SetTitle("Delteta_mumu");
        Long -> GetYaxis() ->SetTitle("Count");
        Long -> Draw();
        Tran -> SetLineColor(4);
        Tran -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> Draw("same");

      playground2->cd(2);
  
        TH1F *Tran = (TH1F*)TransverseRootFile.Get("DeltaPhi");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("DeltaPhi");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("DeltaPhi");
        
        Long -> SetLineColor(2);
        Long -> GetXaxis() ->SetTitle("DeltaPhi_mumu");
        Long -> GetYaxis() ->SetTitle("Count");
        Long -> Draw();
        Tran -> SetLineColor(4);
        Tran -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> Draw("same");
      playground2->cd(3);
        
        TH1F *Tran = (TH1F*)TransverseRootFile.Get("DeltaR");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("DeltaR");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("DeltaR");
        
        Long -> SetLineColor(2);
        Long -> GetXaxis() ->SetTitle("DeltaR_mumu");
        Long -> GetYaxis() ->SetTitle("Count");
        Long -> Draw();
        Tran -> SetLineColor(4);
        Tran -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> Draw("same");

      playground2->cd(4);
        
        TH1F *Tran = (TH1F*)TransverseRootFile.Get("bpT");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("bpT");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("bpT");
        
        Tran -> SetLineColor(4);
        Tran -> GetXaxis() ->SetTitle("pT_b");
        Tran -> GetYaxis() ->SetTitle("Count");
        Tran -> Draw();
        Long -> SetLineColor(2);
        Long -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> Draw("same");

      playground2->cd(5);
  
        TH1F *Tran = (TH1F*)TransverseRootFile.Get("beta");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("beta");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("beta");
        
        Tran -> SetLineColor(4);
        Tran -> GetXaxis() ->SetTitle("eta_b");
        Tran -> GetYaxis() ->SetTitle("Count");
        Tran -> Draw();
        Long -> SetLineColor(2);
        Long -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> Draw("same");

        TH1F *Tran = (TH1F*)TransverseRootFile.Get("IMass2");
        TH1F *Long = (TH1F*)LongitudinalRootFile.Get("IMass2");
        TH1F *Scal = (TH1F*)ScalarRootFile.Get("IMass2");
      
      playground2->cd(6);
        
        Tran -> SetLineColor(4);
        Tran -> GetXaxis() ->SetTitle("m_bmumu");
        Tran -> GetYaxis() ->SetTitle("Count");
        Tran -> Draw();
        Long -> SetLineColor(2);
        Long -> Draw("same");
        Scal -> SetLineColor(1);
        Scal -> Draw("same");

    
        
        
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
    */
  
    playground1->SaveAs("1muons.pdf");
    playground2->SaveAs("2separation.pdf");
    //playground3->SaveAs("3mass.pdf");
}
