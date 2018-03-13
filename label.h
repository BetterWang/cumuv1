
char const * fname[] = {
	"test/",		// 0 test
	"../PbPb2015_cumu/HIMinimumBias2/crab_HIMB2_V1Cumu_pixel_eff_v3/180313_053437/0000/",			// 1 PbPb15 Pixel
	"../PbPb2015_cumu/HIMinimumBias2/crab_HIMB2_V1Cumu_pixel_eta08_eff_v3/180313_053552/0000/",		// 2 PbPb15 Pixel eta08
	"",		// 3 PbPb15 MB5 ppReco
	"../PbPb2015_cumu/HIMinimumBias6/crab_HIMB6_V1Cumu_ppReco_eff_v3/180313_054131/0000/",			// 4 PbPb15 MB6 ppReco
	"../PbPb2015_cumu/HIMinimumBias7/crab_HIMB7_V1Cumu_ppReco_eff_v3/180313_054158/0000/",			// 5 PbPb15 MB7 ppReco
};

char const * ftxt[] = {
	"txt/test/",			// 0
	"txt/PbPb15_HIMB2/",		// 1
	"txt/PbPb15_HIMB2_eta08/",		// 2
	"txt/PbPb15_ppReco5/",			// 3
	"txt/PbPb15_ppReco6/",			// 4
	"txt/PbPb15_ppReco7/",			// 5
};

#include <TChain.h>
#include <iostream>

TChain * chV = new TChain("trV");
void addchain(int s1)
{
        std::cout << fname[s1] << std::endl;
        chV->Add(Form("%s/*.root/V1Cumu/trV", fname[s1]));
}
