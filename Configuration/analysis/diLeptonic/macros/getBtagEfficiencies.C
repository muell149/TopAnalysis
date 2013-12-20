#include <TString.h>
#include <TStyle.h>
#include <TSystem.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH2.h>
#include <TPaveText.h>
#include <TText.h>
#include <iostream>

TString outDir = "bTagEfficiencies/";



void setStyle(TStyle* myStyle)
{
    myStyle->SetCanvasBorderMode(0);
    myStyle->SetCanvasColor(kWhite);
    myStyle->SetCanvasDefH(600); //Height of canvas
    myStyle->SetCanvasDefW(600); //Width of canvas
    myStyle->SetCanvasDefX(0);   //Position on screen
    myStyle->SetCanvasDefY(0);
    myStyle->SetPadBorderMode(0);
    myStyle->SetPadColor(kWhite);
    myStyle->SetPadGridX(false);
    myStyle->SetPadGridY(false);
    myStyle->SetGridColor(0);
    myStyle->SetGridStyle(3);
    myStyle->SetGridWidth(1);
    myStyle->SetFrameBorderMode(0);
    myStyle->SetFrameBorderSize(1);
    myStyle->SetFrameFillColor(0);
    myStyle->SetFrameFillStyle(0);
    myStyle->SetFrameLineColor(1);
    myStyle->SetFrameLineStyle(1);
    myStyle->SetFrameLineWidth(1);
    myStyle->SetPadTopMargin(0.1);
    myStyle->SetPadBottomMargin(0.1);
    myStyle->SetPadLeftMargin(0.11);
    myStyle->SetPadRightMargin(0.15);
    myStyle->SetPaperSize(20.,20.);
    myStyle->SetOptStat(0);
}

void getEff(TString channel)
{
    TFile *file = new TFile("./BTagEff/Nominal/"+channel+"/"+channel+"_ttbarsignalplustau.root");
    if(!file) {
        std::cout<<"File in channel "<<channel<<" doesn't exist"<<std::endl;
        return;
    }

    setStyle(gStyle);

    TH2D *beff = (TH2D*) file->Get("BEffPerJet");
    TH2D *ceff = (TH2D*) file->Get("CEffPerJet");
    TH2D *leff = (TH2D*) file->Get("LEffPerJet");

    TPaveText *text = new TPaveText(0.55,0.80,0.8, 0.9, "NDC");
    text->SetFillColor(0);
    text->SetFillStyle(0);
    text->SetBorderSize(0);


    TString channelLatex = "";
    if(channel == "mumu"){channelLatex = "#mu#mu channel";}
    else if (channel == "emu"){channelLatex = "e#mu channel";}
    else if (channel == "ee"){channelLatex = "ee channel";}
    text->AddText(channelLatex);

    gSystem->mkdir(outDir);
    TCanvas *c = new TCanvas("", "", 0,0, 1000, 1000);

    TString xtitle = "p_{T}^{b-jets}";
    TString ytitle = "|#eta^{b-jets}|";
    TString title = "Tagging Efficiency (b-jet)";
    beff->GetXaxis()->SetTitle(xtitle);
    beff->GetYaxis()->SetTitle(ytitle);
    beff->GetYaxis()->SetTitleOffset(1.35*beff->GetYaxis()->GetTitleOffset());
    beff->SetTitle(title);
    beff->GetZaxis()->SetRangeUser(0.6,0.9);
    beff->Draw("colz");
    text->Draw("same");
    c->SetLogx();
    c->Print(outDir.Copy()+channel+"_bJetEff.eps");

    xtitle = "p_{T}^{c-jets}";
    ytitle = "|#eta^{c-jets}|";
    title = "Tagging Efficiency (c-jet)";
    ceff->GetXaxis()->SetTitle(xtitle);
    ceff->GetYaxis()->SetTitle(ytitle);
    ceff->GetYaxis()->SetTitleOffset(1.35*ceff->GetYaxis()->GetTitleOffset());
    ceff->SetTitle(title);
    ceff->GetZaxis()->SetRangeUser(0.1, 0.7);
    ceff->Draw("colz");
    text->Draw("same");
    c->Print(outDir.Copy()+channel+"_cJetEff.eps");

    xtitle = "p_{T}^{l-jets}";
    ytitle = "|#eta^{l-jets}|";
    title = "Tagging Efficiency (l-jet)";
    leff->GetXaxis()->SetTitle(xtitle);
    leff->GetYaxis()->SetTitle(ytitle);
    leff->GetYaxis()->SetTitleOffset(1.35*leff->GetYaxis()->GetTitleOffset());
    leff->GetZaxis()->SetRangeUser(0, 0.5);
    leff->SetTitle(title);
    leff->Draw("colz");
    text->Draw("same");
    c->Print(outDir.Copy()+channel+"_lJetEff.eps");

    file->Close();
    delete c;
//     delete text;
//     delete beff;
//     delete ceff;
//     delete leff;
//     delete c;
}




void getBtagEfficiencies()
{
    TString channel[3] = {"ee", "emu", "mumu"};
    for (unsigned int iter =0; iter < 3; iter ++){
        getEff(channel[iter]);
    };
}