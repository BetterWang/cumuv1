
char const * fname[] = {
	"test/",		// 0 test
	"../PbPb2015_cumu/HIMinimumBias2/crab_HIMB2_V1Cumu_pixel_eff_v1/180310_171720/0000/",		// 1 PbPb15 Pixel
};

char const * ftxt[] = {
	"txt/test/",			// 0
	"txt/PbPb15_HIMB2/",		// 1
};

#include <TChain.h>
#include <iostream>

TChain * chV = new TChain("trV");
void addchain(int s1)
{
        std::cout << fname[s1] << std::endl;
        chV->Add(Form("%s/*.root/V1Cumu/trV", fname[s1]));
}
