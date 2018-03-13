#include "label.h"
#include "noff.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"
#include "TGraphErrors.h"
#include "../../style.h"

void genPlot(int s1 =0)
{
	int NCent = NCentPbPb15;
//	const double * CentX = CentBinsPbPb15;

	TFile *f = new TFile(Form("%s/outputE.root", ftxt[s1]));

	SetStyle();

	double dC[12][20] = {};
	double eC[12][20] = {};

	for ( int i = 0; i < 12; i++ ) {
		TH1D * h = (TH1D*) f->Get(Form("hCR_%i", i));
		for ( int c = 0; c < NCent; c++ ) {
			dC[i][c] = h->GetBinContent(c+1);
			eC[i][c] = h->GetBinError(c+1);
		}
	}

	TGraphErrors * grC[20] = {};

	for ( int c = 0; c < NCent; c++ ) {
		grC[c] = new TGraphErrors(12);
		for ( int i = 0; i < 12; i++ ) {
			grC[c]->GetX()[i] = Xeta[i];
			grC[c]->GetY()[i] = dC[i][c] / v2[c];
			grC[c]->GetEY()[i] = sqrt( e2[c]*e2[c]/v2[c]/v2[c] + eC[i][c]*eC[i][c] / dC[i][c] / dC[i][c] ) * grC[c]->GetY()[i];
		}
		grC[c]->SetMarkerStyle(kOpenSquare);
		grC[c]->SetMarkerColor(kBlue);
		grC[c]->SetLineColor(kBlue);
	}


	TCanvas * cT = MakeCanvas("cT", "cT", 600, 500);
	cT->SetGridy();
	TH2D * hframe_eta = new TH2D("hframe_eta", "", 1, -2.5, 2.5, 1, -0.01, 0.01);
	InitHist(hframe_eta, "#eta", "<Q_{1}^{2}Q_{2}^{*}>");

	TLatex latexS;
	latexS.SetTextFont(43);
	latexS.SetTextSize(22);
	latexS.SetTextAlign(13);

	for ( int c = 0; c < NCent; c++ ) {
		hframe_eta->Draw();
		grC[c]->Draw("psame");
		latexS.DrawLatexNDC(0.68, 0.9, Form("%i-%i%%", CentBinsPbPb15[c]/2, CentBinsPbPb15[c+1]/2));
		cT->SaveAs(Form("%s/grC%i.pdf", ftxt[s1], c));
	}

	TFile * fwrite = new TFile(Form("%s/outGraph.root", ftxt[s1]), "recreate");
	for ( int c = 0; c < NCent; c++ ) {
		grC[c]->Write(Form("grC%i", c));
	}
}
