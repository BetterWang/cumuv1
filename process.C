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

	double r3point[12];
	double w3point[12];

	double r3pointPtP[8];
	double r3pointPtM[8];
	double w3pointPtP[8];
	double w3pointPtM[8];

        chV->SetBranchAddress("Noff", &gNoff);
        chV->SetBranchAddress("Mult", &gMult);

        chV->SetBranchAddress("rQ1Q1_Q2", rQ1Q1_Q2);
        chV->SetBranchAddress("wQ1Q1_Q2", wQ1Q1_Q2);


        chV->SetBranchAddress("rV1", rV1);
        chV->SetBranchAddress("rV2", rV2);
        chV->SetBranchAddress("wV",  wV);

        chV->SetBranchAddress("r3point", r3point);
        chV->SetBranchAddress("w3point", w3point);

        chV->SetBranchAddress("r3pointPtP", r3pointPtP);
        chV->SetBranchAddress("r3pointPtM", r3pointPtM);
        chV->SetBranchAddress("w3pointPtP", w3pointPtP);
        chV->SetBranchAddress("w3pointPtM", w3pointPtM);

	TH1D * hMult = new TH1D("hMult", "hMult", 2000, 0, 2000);
	TH1D * hNoff = new TH1D("hNoff", "hNoff", 1000, 0, 2000);

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
		hrQ1Q1_Q2[i] = new TH1D(Form("hrQ1Q1_Q2_%i", i), "", 200, 0, 200);
		hwQ1Q1_Q2[i] = new TH1D(Form("hwQ1Q1_Q2_%i", i), "", 200, 0, 200);

		hrV1[i] = new TH1D(Form("hrV1_%i", i), "", 200, 0, 200);
		hrV2[i] = new TH1D(Form("hrV2_%i", i), "", 200, 0, 200);
		hwV[i] = new TH1D(Form("hwV_%i", i), "", 200, 0, 200);

		hr3point[i] = new TH1D(Form("hr3point_%i", i), "", 200, 0, 200);
		hw3point[i] = new TH1D(Form("hw3point_%i", i), "", 200, 0, 200);
	}

	for ( int i = 0; i < 8; i++ ) {
		hr3pPtP[i] = new TH1D(Form("hr3pPtP_%i", i), "", 200, 0, 200);
		hr3pPtM[i] = new TH1D(Form("hr3pPtM_%i", i), "", 200, 0, 200);
		hw3pPtP[i] = new TH1D(Form("hw3pPtP_%i", i), "", 200, 0, 200);
		hw3pPtM[i] = new TH1D(Form("hw3pPtM_%i", i), "", 200, 0, 200);
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

			drQ3[i][gNoff] += r3point[i];
			dwQ3[i][gNoff] += w3point[i];
		}
		for ( int i = 0; i < 8; i++ ) {
			drQ3PtP[i][gNoff] += r3pointPtP[i];
			dwQ3PtP[i][gNoff] += w3pointPtP[i];
			drQ3PtM[i][gNoff] += r3pointPtM[i];
			dwQ3PtM[i][gNoff] += w3pointPtM[i];
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

			hr3point[i]->SetBinContent(c+1, drQ3[i][c]);
			hw3point[i]->SetBinContent(c+1, dwQ3[i][c]);
		}
	}

	for ( int i = 0; i < 8; i++ ) {
		for ( int c = 0; c < 200; c++ ) {
			hr3pPtP[i]->SetBinContent(c+1, drQ3PtP[i][c]);
			hw3pPtP[i]->SetBinContent(c+1, dwQ3PtP[i][c]);
			hr3pPtM[i]->SetBinContent(c+1, drQ3PtM[i][c]);
			hw3pPtM[i]->SetBinContent(c+1, dwQ3PtM[i][c]);
		}
	}

	TFile * fwrite = new TFile(Form("%s/output_%i_%i.root", ftxt[s1], s2, s3), "recreate");
	for ( int i = 0; i < 12; i++ ) {
		hrQ1Q1_Q2[i]->Write();
		hwQ1Q1_Q2[i]->Write();

		hrV1[i]->Write();
		hrV2[i]->Write();
		hwV[i]->Write();

		hr3point[i]->Write();
		hw3point[i]->Write();
	}
	for ( int i = 0; i < 8; i++ ) {
		hr3pPtP[i]->Write();
		hw3pPtP[i]->Write();
		hr3pPtM[i]->Write();
		hw3pPtM[i]->Write();
	}
	hNoff->Write();
	hMult->Write();
}
