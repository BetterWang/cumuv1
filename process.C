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

	double rQ1Q1_Q2[48];
	double wQ1Q1_Q2[48];

        chV->SetBranchAddress("Noff", &gNoff);
        chV->SetBranchAddress("Mult", &gMult);

        chV->SetBranchAddress("rQ1Q1_Q2", rQ1Q1_Q2);
        chV->SetBranchAddress("wQ1Q1_Q2", wQ1Q1_Q2);

	TH1D * hMult = new TH1D("hMult", "hMult", 2000, 0, 2000);
	TH1D * hNoff = new TH1D("hNoff", "hNoff", 1000, 0, 2000);

	TH1D * hrQ1Q1_Q2[48] = {};
	TH1D * hwQ1Q1_Q2[48] = {};

	for ( int i = 0; i < 48; i++ ) {
		hrQ1Q1_Q2[i] = new TH1D(Form("hrQ1Q1_Q2_%i", i), "", 200, 0, 200);
		hwQ1Q1_Q2[i] = new TH1D(Form("hwQ1Q1_Q2_%i", i), "", 200, 0, 200);
	}

	double dQ[48][200] = {};
	double dwQ[48][200] = {};

	unsigned int ievt = 0;
	if ( s2 != s3 ) ievt = s2;
	while ( chV->GetEntry(ievt) ) {
		if ( !((ievt-s2)%100000) ) cout << "!! ievt = " << ievt << endl;
		if ( s2 == s3 ) ievt++;
		else ievt+= s3;

		if ( (gNoff>=200) ) {
			continue;
		}

		for ( int i = 0; i < 48; i++ ) {
			dQ[i][gNoff] += rQ1Q1_Q2[i];
			dwQ[i][gNoff] += wQ1Q1_Q2[i];
		}
		hNoff->Fill(gNoff);
		hMult->Fill(gMult);
	}

	for ( int i = 0; i < 48; i++ ) {
		for ( int c = 0; c < 200; c++ ) {
			hrQ1Q1_Q2[i]->SetBinContent(c+1, dQ[i][c]);
			hwQ1Q1_Q2[i]->SetBinContent(c+1, dwQ[i][c]);
		}
	}

	TFile * fwrite = new TFile(Form("%s/output_%i_%i.root", ftxt[s1], s2, s3), "recreate");
	for ( int i = 0; i < 48; i++ ) {
		hrQ1Q1_Q2[i]->Write();
		hwQ1Q1_Q2[i]->Write();
	}
	hNoff->Write();
	hMult->Write();
}
