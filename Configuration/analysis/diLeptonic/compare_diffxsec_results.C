#include <iostream>
#include <TH1.h>
#include <TFile.h>
#include <vector>
#include <Rtypes.h>
#include <TCanvas.h>
#include <TLegend.h>

struct Result {
    TFile *file;
    const char *label;
    EColor color;
    Result(TFile *File, const char *Label, EColor Color);
};

Result::Result ( TFile* File, const char* Label, const EColor Color ) :
    file(File), label(Label), color(Color)
{
}


void compare_diffxsec_results() {
    std::vector<Result> results;
    results.push_back(Result(TFile::Open("/afs/naf.desy.de/user/w/wbehrenh/scratch/final/standard/plots/DiffXS_Histograms.root"), "EPS (1/fb)", kBlack));
    results.push_back(Result(TFile::Open("/afs/naf.desy.de/user/w/wbehrenh/scratch/final/standard/plots_2fb/DiffXS_Histograms.root"), "2011A (2.2/fb)", kRed));
    results.push_back(Result(TFile::Open("/afs/naf.desy.de/user/w/wbehrenh/scratch/final/standard/plots_5fb/DiffXS_Histograms.root"), "All 4.7/fb", kBlue));
    results.push_back(Result(TFile::Open("/afs/naf.desy.de/user/w/wbehrenh/scratch/final/standard/plots_2011b/DiffXS_Histograms.root"), "2011B (2.2/fb)", kMagenta));

    TFile outFile("compare2011periods.root", "recreate");
    
    TList *keys = results.at(0).file->GetListOfKeys();
    for (int i = 0; i < keys->GetEntries(); ++i) {
        TObject *cross_o;
        results[0].file->GetObject(keys->At(i)->GetName(), cross_o);
        TH1 *cross = dynamic_cast<TH1 *>(cross_o);
        if (cross && strstr(cross->GetName(), "Cross")) {
            TCanvas *canvas = new TCanvas(cross->GetName(), cross->GetName(), 800, 800);
            TLegend *leg = new TLegend(0.75, 0.8, 1, 0.65);
            for (size_t file = 0; file < results.size(); ++file) {
                results.at(file).file->GetObject(cross->GetName(), cross);
                cross->SetLineColor(results[file].color);
                cross->SetMarkerColor(results[file].color);
                if (file)
                    cross->Draw("same");
                else
                    cross->Draw();
                leg->AddEntry(cross, results[file].label);
            }
            leg->Draw();
            canvas->Write();
        }
    }
    outFile.Write();
}
