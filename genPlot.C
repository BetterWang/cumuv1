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

	double dV1[12][20] = {};
	double dV2[12][20] = {};
	double eV1[12][20] = {};
	double eV2[12][20] = {};

	double dQ3[12][20] = {};
	double eQ3[12][20] = {};

	for ( int i = 0; i < 12; i++ ) {
		TH1D * h = (TH1D*) f->Get(Form("hCR_%i", i));
		TH1D * hv1 = (TH1D*) f->Get(Form("hV1_%i", i));
		TH1D * hv2 = (TH1D*) f->Get(Form("hV2_%i", i));
		TH1D * h3 = (TH1D*) f->Get(Form("hrQ3r_%i", i));
		for ( int c = 0; c < NCent; c++ ) {
			dC[i][c] = h->GetBinContent(c+1);
			eC[i][c] = h->GetBinError(c+1);

			dV1[i][c] = hv1->GetBinContent(c+1);
			eV1[i][c] = hv1->GetBinError(c+1);

			dV2[i][c] = hv2->GetBinContent(c+1);
			eV2[i][c] = hv2->GetBinError(c+1);

			dQ3[i][c] = h3->GetBinContent(c+1);
			eQ3[i][c] = h3->GetBinError(c+1);
		}
	}

	TGraphErrors * grC[20] = {};
	TGraphErrors * grV1[20] = {};
	TGraphErrors * grV2[20] = {};

	TGraphErrors * grQ3[20] = {};

	for ( int c = 0; c < NCent; c++ ) {
		grC[c] = new TGraphErrors(12);
		grV1[c] = new TGraphErrors(12);
		grV2[c] = new TGraphErrors(12);
		for ( int i = 0; i < 12; i++ ) {
			grC[c]->GetX()[i] = Xeta[i];
			grC[c]->GetY()[i] = dC[i][c] / v2[c];
			grC[c]->GetEY()[i] = sqrt( e2[c]*e2[c]/v2[c]/v2[c] + eC[i][c]*eC[i][c] / dC[i][c] / dC[i][c] ) * grC[c]->GetY()[i];

			grV1[c]->GetX()[i] = Xeta[i];
			grV1[c]->GetY()[i] = dV1[i][c];
			grV1[c]->GetEY()[i]= eV1[i][c];

			grV2[c]->GetX()[i] = Xeta[i];
			grV2[c]->GetY()[i] = dV2[i][c];
			grV2[c]->GetEY()[i]= eV2[i][c];

			grQ3[c]->GetX()[i] = Xeta[i];
			grQ3[c]->GetY()[i] = dQ3[i];
			grQ3[c]->GetEY()[i]= eQ3[i];
		}
		grC[c]->SetMarkerStyle(kOpenSquare);
		grC[c]->SetMarkerColor(kBlue);
		grC[c]->SetLineColor(kBlue);

		grV1[c]->SetMarkerStyle(kOpenSquare);
		grV1[c]->SetMarkerColor(kBlue);
		grV1[c]->SetLineColor(kBlue);

		grV2[c]->SetMarkerStyle(kOpenSquare);
		grV2[c]->SetMarkerColor(kBlue);
		grV2[c]->SetLineColor(kBlue);
	}


	TCanvas * cT = MakeCanvas("cT", "cT", 600, 500);
	cT->SetGridy();
	TH2D * hframe_eta = new TH2D("hframe_eta", "", 1, -2.5, 2.5, 1, -0.0010, 0.0010);
	InitHist(hframe_eta, "#eta", "<Q_{1}^{2}Q_{2}^{*}>/v_{2}");

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

	/// V1
	TCanvas * cV1 = MakeCanvas("cV1", "cV1", 600, 500);
	cV1->SetGridy();
	TH2D * hframe_v1 = new TH2D("hframe_v1", "", 1, -2.5, 2.5, 1, -0.03, 0.03);
	InitHist(hframe_v1, "#eta", "v_{1}{RP}");
	for ( int c = 0; c < NCent; c++ ) {
		hframe_v1->Draw();
		grV1[c]->Draw("psame");
		latexS.DrawLatexNDC(0.68, 0.9, Form("%i-%i%%", CentBinsPbPb15[c]/2, CentBinsPbPb15[c+1]/2));
		cV1->SaveAs(Form("%s/grV1_%i.pdf", ftxt[s1], c));
	}

	/// V2
	TCanvas * cV2 = MakeCanvas("cV2", "cV2", 600, 500);
	cV1->SetGridy();
	TH2D * hframe_v2 = new TH2D("hframe_v2", "", 1, -2.5, 2.5, 1, 0.001, 0.15);
	InitHist(hframe_v2, "#eta", "v_{2}{RP}");
	for ( int c = 0; c < NCent; c++ ) {
		hframe_v2->Draw();
		grV2[c]->Draw("psame");
		latexS.DrawLatexNDC(0.68, 0.9, Form("%i-%i%%", CentBinsPbPb15[c]/2, CentBinsPbPb15[c+1]/2));
		cV2->SaveAs(Form("%s/grV2_%i.pdf", ftxt[s1], c));
	}

	/// 3point
	TCanvas * cT3 = MakeCanvas("cT3", "cT3", 600, 500);
	cT3->SetGridy();
	TH2D * hframe3_eta = new TH2D("hframe3_eta", "", 1, -2.5, 2.5, 1, -0.0010, 0.0010);
	InitHist(hframe3_eta, "#eta", "<cos[#phi+#Psi_{1}-#Phi_{2}]>");

	for ( int c = 0; c < NCent; c++ ) {
		hframe3_eta->Draw();
		grQ3[c]->Draw("psame");
		latexS.DrawLatexNDC(0.68, 0.9, Form("%i-%i%%", CentBinsPbPb15[c]/2, CentBinsPbPb15[c+1]/2));
		cT->SaveAs(Form("%s/grQ3_%i.pdf", ftxt[s1], c));
	}


	TFile * fwrite = new TFile(Form("%s/outGraph.root", ftxt[s1]), "recreate");
	for ( int c = 0; c < NCent; c++ ) {
		grC[c]->Write(Form("grC%i", c));
		grV1[c]->Write(Form("grV1%i", c));
		grV2[c]->Write(Form("grV2%i", c));
		grQ3[c]->Write(Form("grQ3%i", c));
	}
}
