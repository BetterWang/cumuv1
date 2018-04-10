#include "label.h"
//#include "noff.h"
#include <TFile.h>
#include <TTree.h>
#include <TH1.h>

void bGetError(int s1 = 0, int s3 = 10)
{
	std::cout << "s1 = " << s1 << "\ts3 = " << s3 << std::endl;

	TFile *fr[20];
	for ( int i = 0; i <= s3; i++ ) {
		fr[i] = new TFile(Form("%s/outputC_%i_%i.root", ftxt[s1], i, s3));
	}

	double dC[12][20][50];
	double wC[12][20][50];

	double dC1[12][20][50] = {};
	double dC2[12][20][50] = {};
	double dwC[12][20][50] = {};

	// Get
	for ( int fn = 0; fn <= s3; fn++ ) {
		TFile * f = fr[fn];
		for ( int i = 0; i < 12; i++ ) {
			TH1D * h = (TH1D*) f->Get(Form("hC_%i", i));
			TH1D * hw= (TH1D*) f->Get(Form("hwC_%i", i));
			TH1D * h1 = (TH1D*) f->Get(Form("hV1_%i", i));
			TH1D * h2 = (TH1D*) f->Get(Form("hV2_%i", i));
			TH1D * hwc= (TH1D*) f->Get(Form("hW_%i", i));
			for ( int c = 0; c < 20; c++ ) {
				dC[i][c][fn] = h->GetBinContent(c+1);
				wC[i][c][fn] = hw->GetBinContent(c+1);

				dC1[i][c][fn] = h1->GetBinContent(c+1);
				dC2[i][c][fn] = h2->GetBinContent(c+1);
				dwC[i][c][fn] = hwc->GetBinContent(c+1);
			}
		}
	}

	// Get Error
	double eC[12][20] = {};
	double eV1[12][20] = {};
	double eV2[12][20] = {};
	for ( int i = 0; i < 12; i++ ) {
		for ( int c = 0; c < 20; c++ ) {
			double sum = 0;
			double sum1 = 0;
			double sum2 = 0;
			for ( int fn = 0; fn < s3; fn++ ) {
				sum += (dC[i][c][fn] - dC[i][c][s3]) * (dC[i][c][fn] - dC[i][c][s3]);
				sum1+= (dC1[i][c][fn] - dC1[i][c][s3]) * (dC1[i][c][fn] - dC1[i][c][s3]);
				sum2+= (dC2[i][c][fn] - dC2[i][c][s3]) * (dC2[i][c][fn] - dC2[i][c][s3]);
			}
			eC[i][c] = sqrt( sum ) / s3;
			eV1[i][c] = sqrt( sum1 ) / s3;
			eV2[i][c] = sqrt( sum2 ) / s3;
		}
	}

	// Save
	TH1D * hCR[12] = {};
	TH1D * hwCR[12] = {};

	TH1D * hV1[12] = {};
	TH1D * hV2[12] = {};
	TH1D * hW[12] = {};

	for ( int i = 0; i < 12; i++ ) {
		hCR[i]  = new TH1D(Form("hCR_%i", i), "", 20, 0, 20);
		hwCR[i] = new TH1D(Form("hwCR_%i", i), "", 20, 0, 20);

		hV1[i]  = new TH1D(Form("hV1_%i", i), "", 20, 0, 20);
		hV2[i]  = new TH1D(Form("hV2_%i", i), "", 20, 0, 20);
		hW[i]   = new TH1D(Form("hW_%i", i), "", 20, 0, 20);
	}

	for ( int i = 0; i < 12; i++ ) {
		for ( int c = 0; c < 20; c++ ) {
			hCR[i]->SetBinContent(c+1, dC[i][c][s3]);
			hCR[i]->SetBinError(c+1, eC[i][c]);
			hwCR[i]->SetBinContent(c+1, wC[i][c][s3]);

			hV1[i]->SetBinContent(c+1, dC1[i][c][s3]);
			hV2[i]->SetBinContent(c+1, dC2[i][c][s3]);
			hW[i] ->SetBinContent(c+1, dwC[i][c][s3]);
			hV1[i]->SetBinError(c+1, eV1[i][c]);
			hV2[i]->SetBinError(c+1, eV2[i][c]);
		}
	}

	// Write
	TFile * fwrite = 0;
	fwrite = new TFile(Form("%s/outputE.root", ftxt[s1]), "recreate");
	for ( int i = 0; i < 12; i++ ) {
		hCR[i]->Write();
		hwCR[i]->Write();

		hV1[i]->Write();
		hV2[i]->Write();
		hW[i]->Write();
	}
	fwrite->Close();
}
