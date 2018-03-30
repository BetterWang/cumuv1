#include "label.h"
#include "noff.h"

#include <TFile.h>
#include <TH1.h>
using namespace std;
void bGet(int s1 = 0, int s2 = 10, int s3 = 10)
{
	cout << " s1 = " << s1 << " s2 = " << s2 << " s3 = " << s3 << endl;
	TH1::SetDefaultSumw2();
	int NCent = NCentPbPb15;
	const int * pCent = CentBinsPbPb15;

	TFile * f = new TFile(Form("%s/output_%i_%i.root", ftxt[s1], s2, s3));

	TH1D * hNoff = (TH1D*) f->Get("hNoff");
	TH1D * hMult = (TH1D*) f->Get("hMult");

	TH1D * hrQ1Q1_Q2[12] = {};
	TH1D * hwQ1Q1_Q2[12] = {};

	for ( int i = 0; i < 12; i++ ) {
		hrQ1Q1_Q2[i] = (TH1D*) f->Get(Form("hrQ1Q1_Q2_%i", i));
		hwQ1Q1_Q2[i] = (TH1D*) f->Get(Form("hwQ1Q1_Q2_%i", i));
	}

	double dQ[12][200] = {};
	double dwQ[12][200] = {};

	for ( int i = 0; i < 12; i++ ) {
		for ( int c = 0; c < 200; c++ ) {
			dQ[i][c]  = hrQ1Q1_Q2[i]->GetBinContent(c+1);
			dwQ[i][c] = hwQ1Q1_Q2[i]->GetBinContent(c+1);
		}
	}

	//rebin
	double dC[12][20] = {};
	double wC[12][20] = {};

	for ( int c = 0; c < NCent; c++ ) {
		for ( int ieta = 0; ieta < 12; ieta++ ) {
			for ( int cc = pCent[c]; cc < pCent[c+1]; cc++ ) {
				dC[ieta][c] += dQ[ieta][cc]; // dQ[4*ieta][cc] + dQ[4*ieta+1][cc] + dQ[4*ieta+2][cc] + dQ[4*ieta+3][cc];
				wC[ieta][c] += dwQ[ieta][cc]; // dwQ[4*ieta][cc] + dwQ[4*ieta+1][cc] + dwQ[4*ieta+2][cc] + dwQ[4*ieta+3][cc];
			}
			if (dC[ieta][c] != 0.) dC[ieta][c] /= wC[ieta][c];
		}
	}

	TH1D * hNoffR = new TH1D("hNoffR", "hNoffR", 20, 0, 20);
	for ( int c = 0; c < NCent; c++ ) {
		int nevt = 0;
		for ( int m = pCent[c]; m < pCent[c+1]; m++ ) {
			nevt += hNoff->GetBinContent(m+1);
		}
		hNoffR->SetBinContent(c+1, nevt);
	}

	TH1D * hC[12];
	TH1D * hwC[12];
	for ( int i = 0; i < 12; i++ ) {
		hC[i]  = new TH1D(Form("hC_%i", i), "", 20, 0, 20);
		hwC[i] = new TH1D(Form("hwC_%i", i), "", 20, 0, 20);
	}

	for ( int c = 0; c < NCent; c++ ) {
		for ( int ieta = 0; ieta < 12; ieta++ ) {
			hC[ieta] ->SetBinContent(c+1, dC[ieta][c]);
			hwC[ieta]->SetBinContent(c+1, wC[ieta][c]);
		}
	}

	TFile * fwrite = new TFile(Form("%s/outputC_%i_%i.root", ftxt[s1], s2, s3), "recreate");
	for ( int ieta = 0; ieta < 12; ieta++ ) {
		hC[ieta]->Write();
		hwC[ieta]->Write();
	}
	hNoff->Write();
	hMult->Write();
	hNoffR->Write();
}
