#include "label.h"
#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TMath.h>
using namespace std;

void process(int s1 = 0, int s2 = 10, int s3 = 10)
{
	cout << " s1 = " << s1 << " s2 = " << s2 << " s3 = " << s3 << endl;
	TH1::SetDefaultSumw2();
	addchain(s1);

	int gNoff;
	int gMult;

	double rQ1Q1_Q2[12];
	double wQ1Q1_Q2[12];

	double rV1[12];
	double rV2[12];
	double wV[12];

        chV->SetBranchAddress("Noff", &gNoff);
        chV->SetBranchAddress("Mult", &gMult);

        chV->SetBranchAddress("rQ1Q1_Q2", rQ1Q1_Q2);
        chV->SetBranchAddress("wQ1Q1_Q2", wQ1Q1_Q2);

        chV->SetBranchAddress("rV1", rV1);
        chV->SetBranchAddress("rV2", rV2);
        chV->SetBranchAddress("wV",  wV);

	TH1D * hMult = new TH1D("hMult", "hMult", 2000, 0, 2000);
	TH1D * hNoff = new TH1D("hNoff", "hNoff", 1000, 0, 2000);

	TH1D * hrQ1Q1_Q2[12] = {};
	TH1D * hwQ1Q1_Q2[12] = {};

	TH1D * hrV1[12] = {};
	TH1D * hrV2[12] = {};
	TH1D * hwV[12] = {};

	for ( int i = 0; i < 12; i++ ) {
		hrQ1Q1_Q2[i] = new TH1D(Form("hrQ1Q1_Q2_%i", i), "", 200, 0, 200);
		hwQ1Q1_Q2[i] = new TH1D(Form("hwQ1Q1_Q2_%i", i), "", 200, 0, 200);

		hrV1[i] = new TH1D(Form("hrV1_%i", i), "", 200, 0, 200);
		hrV2[i] = new TH1D(Form("hrV2_%i", i), "", 200, 0, 200);
		hwV[i] = new TH1D(Form("hwV_%i", i), "", 200, 0, 200);
	}

	double dQ[12][200] = {};
	double dwQ[12][200] = {};

	double dV1[12][200] = {};
	double dV2[12][200] = {};
	double dwV[12][200] = {};

	unsigned int ievt = 0;
	if ( s2 != s3 ) ievt = s2;
	while ( chV->GetEntry(ievt) ) {
		if ( !((ievt-s2)%100000) ) cout << "!! ievt = " << ievt << endl;
		if ( s2 == s3 ) ievt++;
		else ievt+= s3;

		if ( (gNoff>=200) ) {
			continue;
		}

		for ( int i = 0; i < 12; i++ ) {
			dQ[i][gNoff] += rQ1Q1_Q2[i];
			dwQ[i][gNoff] += wQ1Q1_Q2[i];

			dV1[i][gNoff] += rV1[i];
			dV2[i][gNoff] += rV2[i];
			dwV[i][gNoff] += wV[i];
		}
		hNoff->Fill(gNoff);
		hMult->Fill(gMult);
	}

	for ( int i = 0; i < 12; i++ ) {
		for ( int c = 0; c < 200; c++ ) {
			hrQ1Q1_Q2[i]->SetBinContent(c+1, dQ[i][c]);
			hwQ1Q1_Q2[i]->SetBinContent(c+1, dwQ[i][c]);

			hrV1[i]->SetBinContent(c+1, dV1[i][c]);
			hrV2[i]->SetBinContent(c+1, dV2[i][c]);
			hwV[i]->SetBinContent(c+1,  dwV[i][c]);
		}
	}

	TFile * fwrite = new TFile(Form("%s/output_%i_%i.root", ftxt[s1], s2, s3), "recreate");
	for ( int i = 0; i < 12; i++ ) {
		hrQ1Q1_Q2[i]->Write();
		hwQ1Q1_Q2[i]->Write();

		hrV1[i]->Write();
		hrV2[i]->Write();
		hwV[i]->Write();
	}
	hNoff->Write();
	hMult->Write();
}
