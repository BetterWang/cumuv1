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

	TH1D * hrV1[12] = {};
	TH1D * hrV2[12] = {};
	TH1D * hwV[12] = {};

	TH1D * hr3point[12] = {};
	TH1D * hw3point[12] = {};

	TH1D * hr3pPtP[8] = {};
	TH1D * hr3pPtM[8] = {};
	TH1D * hw3pPtP[8] = {};
	TH1D * hw3pPtM[8] = {};

	for ( int i = 0; i < 12; i++ ) {
		hrQ1Q1_Q2[i] = (TH1D*) f->Get(Form("hrQ1Q1_Q2_%i", i));
		hwQ1Q1_Q2[i] = (TH1D*) f->Get(Form("hwQ1Q1_Q2_%i", i));

		hrV1[i] = (TH1D*) f->Get(Form("hrV1_%i", i));
		hrV2[i] = (TH1D*) f->Get(Form("hrV2_%i", i));
		hwV[i]  = (TH1D*) f->Get(Form("hwV_%i", i));

		hr3point[i] = (TH1D*) f->Get(Form("hr3point_%i", i));
		hw3point[i] = (TH1D*) f->Get(Form("hw3point_%i", i));
	}

	for ( int i = 0; i < 8; i++ ) {
		hr3pPtP[i] = (TH1D*) f->Get(Form("hr3pPtP_%i", i));
		hw3pPtP[i] = (TH1D*) f->Get(Form("hw3pPtP_%i", i));
		hr3pPtM[i] = (TH1D*) f->Get(Form("hr3pPtM_%i", i));
		hw3pPtM[i] = (TH1D*) f->Get(Form("hw3pPtM_%i", i));
	}

	double dQ[12][200] = {};
	double dwQ[12][200] = {};

	double dV1[12][200] = {};
	double dV2[12][200] = {};
	double dwV[12][200] = {};

	double drQ3[12][200] = {};
	double dwQ3[12][200] = {};

	double drQ3PtP[8][200] = {};
	double dwQ3PtP[8][200] = {};
	double drQ3PtM[8][200] = {};
	double dwQ3PtM[8][200] = {};

	for ( int i = 0; i < 12; i++ ) {
		for ( int c = 0; c < 200; c++ ) {
			dQ[i][c]  = hrQ1Q1_Q2[i]->GetBinContent(c+1);
			dwQ[i][c] = hwQ1Q1_Q2[i]->GetBinContent(c+1);

			dV1[i][c] = hrV1[i]->GetBinContent(c+1);
			dV2[i][c] = hrV2[i]->GetBinContent(c+1);
			dwV[i][c] = hwV[i]->GetBinContent(c+1);

			drQ3[i][c] = hr3point[i]->GetBinContent(c+1);
			dwQ3[i][c] = hw3point[i]->GetBinContent(c+1);
		}
	}
	for ( int i = 0; i < 8; i++ ) {
		for ( int c = 0; c < 200; c++ ) {
			drQ3PtP[i][c] = hr3pPtP[i]->GetBinContent(c+1);
			dwQ3PtP[i][c] = hw3pPtP[i]->GetBinContent(c+1);
			drQ3PtM[i][c] = hr3pPtM[i]->GetBinContent(c+1);
			dwQ3PtM[i][c] = hw3pPtM[i]->GetBinContent(c+1);
		}
	}

	//rebin
	double dC[12][20] = {};
	double wC[12][20] = {};

	double dC1[12][20] = {};
	double dC2[12][20] = {};
	double dwC[12][20] = {};

	double drQ3r[12][20] = {};
	double dwQ3r[12][20] = {};

	double drQ3PtPr[8][20] = {};
	double dwQ3PtPr[8][20] = {};
	double drQ3PtMr[8][20] = {};
	double dwQ3PtMr[8][20] = {};

	for ( int c = 0; c < NCent; c++ ) {
		for ( int ieta = 0; ieta < 12; ieta++ ) {
			for ( int cc = pCent[c]; cc < pCent[c+1]; cc++ ) {
				dC[ieta][c] += dQ[ieta][cc]; // dQ[4*ieta][cc] + dQ[4*ieta+1][cc] + dQ[4*ieta+2][cc] + dQ[4*ieta+3][cc];
				wC[ieta][c] += dwQ[ieta][cc]; // dwQ[4*ieta][cc] + dwQ[4*ieta+1][cc] + dwQ[4*ieta+2][cc] + dwQ[4*ieta+3][cc];
				dC1[ieta][c] += dV1[ieta][cc];
				dC2[ieta][c] += dV2[ieta][cc];
				dwC[ieta][c] += dwV[ieta][cc];

				drQ3r[ieta][c] += drQ3[ieta][cc];
				dwQ3r[ieta][c] += dwQ3[ieta][cc];
			}
			if (dC[ieta][c] != 0.) dC[ieta][c] /= wC[ieta][c];
			if (dwC[ieta][c] != 0.) {
				dC1[ieta][c] /= dwC[ieta][c];
				dC2[ieta][c] /= dwC[ieta][c];
			}
			if ( dwQ3r[ieta][c] != 0. ) drQ3r[ieta][c] /= dwQ3r[ieta][c];
		}
	}
	for ( int c = 0; c < NCent; c++ ) {
		for ( int ipt = 0; ipt < 8; ieta++ ) {
			for ( int cc = pCent[c]; cc < pCent[c+1]; cc++ ) {
				drQ3PtPr[ipt][c] += drQ3PtP[ipt][cc];
				dwQ3PtPr[ipt][c] += dwQ3PtP[ipt][cc];
				drQ3PtMr[ipt][c] += drQ3PtM[ipt][cc];
				dwQ3PtMr[ipt][c] += dwQ3PtM[ipt][cc];
			}
			if ( dwQ3PtPr[ipt][c] != 0 ) drQ3PtPr[ipt][c] /= dwQ3PtPr[ipt][c];
			if ( dwQ3PtMr[ipt][c] != 0 ) drQ3PtMr[ipt][c] /= dwQ3PtMr[ipt][c];
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

	TH1D * hV1[12];
	TH1D * hV2[12];
	TH1D * hW[12];

	TH1D * hrQ3[12];
	TH1D * hwQ3[12];

	TH1D * hrQ3PtP[8];
	TH1D * hwQ3PtP[8];
	TH1D * hrQ3PtM[8];
	TH1D * hwQ3PtM[8];

	for ( int i = 0; i < 12; i++ ) {
		hC[i]  = new TH1D(Form("hC_%i", i), "", 20, 0, 20);
		hwC[i] = new TH1D(Form("hwC_%i", i), "", 20, 0, 20);

		hV1[i] = new TH1D(Form("hV1_%i", i), "", 20, 0, 20);
		hV2[i] = new TH1D(Form("hV2_%i", i), "", 20, 0, 20);
		hW[i]  = new TH1D(Form("hW_%i", i), "", 20, 0, 20);

		hrQ3[i] = new TH1D(Form("hrQ3_%i", i), "", 20, 0, 20);
		hwQ3[i] = new TH1D(Form("hwQ3_%i", i), "", 20, 0, 20);
	}
	for ( int i = 0; i < 8; i++ ) {
		hrQ3PtP[i] = new TH1D(Form("hrQ3PtP_%i", i), "", 20, 0, 20);
		hwQ3PtP[i] = new TH1D(Form("hwQ3PtP_%i", i), "", 20, 0, 20);
		hrQ3PtM[i] = new TH1D(Form("hrQ3PtM_%i", i), "", 20, 0, 20);
		hwQ3PtM[i] = new TH1D(Form("hwQ3PtM_%i", i), "", 20, 0, 20);
	}

	for ( int c = 0; c < NCent; c++ ) {
		for ( int ieta = 0; ieta < 12; ieta++ ) {
			hC[ieta] ->SetBinContent(c+1, dC[ieta][c]);
			hwC[ieta]->SetBinContent(c+1, wC[ieta][c]);

			hV1[ieta]->SetBinContent(c+1, dC1[ieta][c]);
			hV2[ieta]->SetBinContent(c+1, dC2[ieta][c]);
			hW[ieta] ->SetBinContent(c+1, dwC[ieta][c]);

			hrQ3[ieta]->SetBinContent(c+1, drQ3r[ieta][c]);
			hwQ3[ieta]->SetBinContent(c+1, dwQ3r[ieta][c]);
		}
		for ( int ipt = 0; ipt < 8; ipt++ ) {
			hrQ3PtP[ipt]->SetBinContent(c+1, drQ3PtPr[ipt][c]);
			hwQ3PtP[ipt]->SetBinContent(c+1, dwQ3PtPr[ipt][c]);
			hrQ3PtM[ipt]->SetBinContent(c+1, drQ3PtMr[ipt][c]);
			hwQ3PtM[ipt]->SetBinContent(c+1, dwQ3PtMr[ipt][c]);
		}
	}

	TFile * fwrite = new TFile(Form("%s/outputC_%i_%i.root", ftxt[s1], s2, s3), "recreate");
	for ( int ieta = 0; ieta < 12; ieta++ ) {
		hC[ieta]->Write();
		hwC[ieta]->Write();

		hV1[ieta]->Write();
		hV2[ieta]->Write();
		hW[ieta]->Write();

		hrQ3[ieta]->Write();
		hwQ3[ieta]->Write();
	}

	for ( int ipt = 0; ipt < 8; ipt++ ) {
		hrQ3PtP[ipt]->Write();
		hwQ3PtP[ipt]->Write();
		hrQ3PtM[ipt]->Write();
		hwQ3PtM[ipt]->Write();
	}

	hNoff->Write();
	hMult->Write();
	hNoffR->Write();
}
