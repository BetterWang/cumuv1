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

	// Get
	for ( int fn = 0; fn <= s3; fn++ ) {
		TFile * f = fr[fn];
		for ( int i = 0; i < 12; i++ ) {
			TH1D * h = (TH1D*) f->Get(Form("hC_%i", i));
			TH1D * hw= (TH1D*) f->Get(Form("hwC_%i", i));
			for ( int c = 0; c < 20; c++ ) {
				dC[i][c][fn] = h->GetBinContent(c+1);
				wC[i][c][fn] = hw->GetBinContent(c+1);
			}
		}
	}

	// Get Error
	double eC[12][20] = {};
	for ( int i = 0; i < 12; i++ ) {
		for ( int c = 0; c < 20; c++ ) {
			double sum = 0;
			for ( int fn = 0; fn < s3; fn++ ) {
				sum += (dC[i][c][fn] - dC[i][c][s3]) * (dC[i][c][fn] - dC[i][c][s3]);
			}
			eC[i][c] = sqrt( sum ) / s3;
		}
	}

	// Save
	TH1D * hCR[12] = {};
	TH1D * hwCR[12] = {};

	for ( int i = 0; i < 12; i++ ) {
		hCR[i]  = new TH1D(Form("hCR_%i", i), "", 20, 0, 20);
		hwCR[i] = new TH1D(Form("hwCR_%i", i), "", 20, 0, 20);
	}

	for ( int i = 0; i < 12; i++ ) {
		for ( int c = 0; c < 20; c++ ) {
			hCR[i]->SetBinContent(c+1, dC[i][c][s3]);
			hCR[i]->SetBinError(c+1, eC[i][c]);
			hwCR[i]->SetBinContent(c+1, wC[i][c][s3]);
		}
	}

	// Write
	TFile * fwrite = 0;
	fwrite = new TFile(Form("%s/outputE.root", ftxt[s1]), "recreate");
	for ( int i = 0; i < 12; i++ ) {
		hCR[i]->Write();
		hwCR[i]->Write();
	}
	fwrite->Close();
}
