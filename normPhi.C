
void normPhi()
{
	std::vector<std::string> strCent{
//		"QWAcc0",
//		"QWAcc10",
//		"QWAcc20",
//		"QWAcc30",
//		"QWAcc40",
//		"QWAcc50",
		"QWAcc60",
		"QWAcc70",
		"QWAcc80",
		"QWAcc100",
		"QWAcc120"
	};

	TFile * f = new TFile("PbPb15_ppReco_PhiAcc.root");

	TH2D * hPhi[20][28] = {};

	for ( int c = 0; c < strCent.size(); c++ ) {
		for ( int i = 0; i < 28; i++ ) {
			hPhi[c][i] = (TH2D*) f->Get(Form("%s/hc_%i", strCent[c].c_str(), i));
		}
	}

	for ( int c = 0; c < strCent.size(); c++ ) {
		for ( int i = 0; i < 28; i++ ) {
			TH2D * hphi = hPhi[c][i];
			for ( int ieta = 0; ieta < 48; ieta++ ) {
				double sum = 0;
				for ( int iphi = 0; iphi < 48; iphi++ ) {
					sum += hphi->GetBinContent(iphi+1, ieta+1);
				}
				sum = sum / 48.;
				for ( int iphi = 0; iphi < 48; iphi++ ) {
					hphi->SetBinContent(iphi+1, ieta+1, hphi->GetBinContent(iphi+1, ieta+1)/sum);
					hphi->SetBinError(iphi+1, ieta+1, hphi->GetBinError(iphi+1, ieta+1)/sum);
				}
				hphi->SetBinError(0, ieta+1, hphi->GetBinError(1, ieta+1)/sum);
				hphi->SetBinError(49, ieta+1, hphi->GetBinError(48, ieta+1)/sum);
			}
		}
	}

	TFile * fout = new TFile("PbPb15_ppReco_normAcc.root", "recreate");
	for ( int c = 0; c < strCent.size(); c++ ) {
		fout->mkdir(strCent[c].c_str());
		fout->cd(strCent[c].c_str());
		for ( int i = 0; i < 28; i++ ) {
			hPhi[c][i]->Write();
		}
		fout->cd("/");
	}
}
