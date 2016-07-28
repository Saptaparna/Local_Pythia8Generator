//  Root histgram combiner
//  combiner.cc
//  Orignially composed by Ziheng on Jun/27/2016
//  @ Northwestern University
//
//  Put three .root files in the same directory
//  and run command root -x combiner.cc
//
//

#define TransverseFILE      "1.root"
#define LongitudinalFILE    "0.root"
#define ScalarFILE          "9.root"



{
    gStyle->SetPalette(1);
    gStyle->SetOptStat(0);
    TCanvas *playground1 = new TCanvas("playground1","playground1",800,600);
    TCanvas *playground2 = new TCanvas("playground2","playground2",800,600);
    TCanvas *playground3 = new TCanvas("playground3","playground3",800,600);

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
        
        playground1->cd();
        
        TH1F *TransTrailingMuPt = (TH1F*)TransverseRootFile.Get("trailingMuonPt");
        TH1F *LongiTrailingMuPt = (TH1F*)LongitudinalRootFile.Get("trailingMuonPt");
        TH1F *ScalaTrailingMuPt = (TH1F*)ScalarRootFile.Get("trailingMuonPt");
        
        TransTrailingMuPt -> SetLineColor(4);
        TransTrailingMuPt -> GetXaxis() ->SetTitle("pT[GeV]");
        TransTrailingMuPt -> GetYaxis() ->SetTitle("Count");
        TransTrailingMuPt -> Draw();
        
        LongiTrailingMuPt -> SetLineColor(2);
        LongiTrailingMuPt -> Draw("same");
        ScalaTrailingMuPt -> SetLineColor(1);
        ScalaTrailingMuPt -> Draw("same");


        TPaveText *pt = new TPaveText(1,1,100,100);
        pt->AddText("Black -- Scalar");
        pt->AddText("Red -- Longitudinal");
        pt->AddText("Blue -- Transerver");
        pt->Draw();
        
        
        
        
        
        
        playground2->cd();
        
        TH1F *TransLeadingMuPt = (TH1F*)TransverseRootFile.Get("leadingMuonPt");
        TH1F *LongiLeadingMuPt = (TH1F*)LongitudinalRootFile.Get("leadingMuonPt");
        TH1F *ScalaLeadingMuPt = (TH1F*)ScalarRootFile.Get("leadingMuonPt");
        
        TransLeadingMuPt -> SetLineColor(4);
        TransLeadingMuPt -> GetXaxis() ->SetTitle("pT[GeV]");
        TransLeadingMuPt -> GetYaxis() ->SetTitle("Count");

        
        LongiLeadingMuPt -> SetLineColor(2);
        LongiLeadingMuPt -> Draw();
        ScalaLeadingMuPt -> SetLineColor(1);
        ScalaLeadingMuPt -> Draw("same");
        TransLeadingMuPt -> Draw("same");
        
        TPaveText *pt2 = new TPaveText(1,1,100,100);
        pt2->AddText("Black -- Scalar");
        pt2->AddText("Red -- Longitudinal");
        pt2->AddText("Blue -- Transerver");
        pt2->Draw();
        
        
        
        
        
        playground3->cd();
        
        TH1F *TransCos = (TH1F*)TransverseRootFile.Get("cos(theta)_Z");
        TH1F *LongiCos = (TH1F*)LongitudinalRootFile.Get("cos(theta)_Z");
        TH1F *ScalaCos = (TH1F*)ScalarRootFile.Get("cos(theta)_Z");
        
        TransCos -> SetLineColor(4);
        TransCos -> GetXaxis() ->SetTitle("pT[GeV]");
        TransCos -> GetYaxis() ->SetTitle("Count");
        
        LongiCos -> SetLineColor(2);
        LongiCos -> Draw();
        ScalaCos -> SetLineColor(1);
        ScalaCos -> Draw("same");
        TransCos -> Draw("same");
        
        TPaveText *pt2 = new TPaveText(0,0,1,100);
        pt2->AddText("Black -- Scalar");
        pt2->AddText("Red -- Longitudinal");
        pt2->AddText("Blue -- Transerver");
        pt2->Draw();
        
        
}
