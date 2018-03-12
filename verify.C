#include "label.h"

void verify(int s1 = 1){
//	int s1 = 1;
	int s3 = 10;

	TFile *f;
	for ( int s2 = 0; s2 <= s3; s2++ ) {
		f = new TFile(Form("%s/output_%i_%i.root", ftxt[s1], s2, s3));

		TH1D * h;
		unsigned int Nevt;
		if (!f->IsZombie()) {
			h= (TH1D*) f->Get("hNoff");
			Nevt = h->GetEntries();
			cout << " s1 = " << s1 << "\ts2 = " << s2 << "\tNevt = " << Nevt;
			if (Nevt==0 ) cout << "\t!!!Empty!!!" << endl;
			else cout << endl;
		} else {
			cout << " s1 = " << s1 << "\ts2 = " << s2 << "\tNot exist!!!" << endl;
		}
	}
}
