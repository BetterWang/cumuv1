
char const * fname[] = {
	"test/",		// 0 test
	"../PbPb2015_cumu/HIMinimumBias2/crab_HIMB2_V1Cumu_pixel_eff_v3/180313_053437/0000/",			// 1 PbPb15 Pixel
	"../PbPb2015_cumu/HIMinimumBias2/crab_HIMB2_V1Cumu_pixel_eta08_eff_v3/180313_053552/0000/",		// 2 PbPb15 Pixel eta08
	"../PbPb2015_cumu/HIMinimumBias5/crab_HIMB5_V1Cumu_ppReco_eff_v3/180313_054104/0000/",			// 3 PbPb15 MB5 ppReco
	"../PbPb2015_cumu/HIMinimumBias6/crab_HIMB6_V1Cumu_ppReco_eff_v3/180313_054131/0000/",			// 4 PbPb15 MB6 ppReco
	"../PbPb2015_cumu/HIMinimumBias7/crab_HIMB7_V1Cumu_ppReco_eff_v3/180313_054158/0000/",			// 5 PbPb15 MB7 ppReco
	"../PbPb2015_cumu/HIMinimumBias5/crab_HIMB5_V1Cumu_ppReco_eta08_eff_v3/180313_212701/0000/",		// 6 PbPb15 MB5 ppReco eta08
	"../PbPb2015_cumu/HIMinimumBias6/crab_HIMB6_V1Cumu_ppReco_eta08_eff_v3/180313_212723/0000/",		// 7 PbPb15 MB6 ppReco eta08
	"../PbPb2015_cumu/HIMinimumBias7/crab_HIMB7_V1Cumu_ppReco_eta08_eff_v3/180313_212746/0000/",		// 8 PbPb15 MB7 ppReco eta08
	"../PbPb2015_cumu/HIMinimumBias5/crab_HIMB5_V1Cumu_ppReco_effacc_v4/180314_163315/0000/",		// 9 PbPb15 MB5 ppReco acc
	"../PbPb2015_cumu/HIMinimumBias6/crab_HIMB6_V1Cumu_ppReco_effacc_v4/180314_163342/0000/",		// 10 PbPb15 MB6 ppReco acc
	"../PbPb2015_cumu/HIMinimumBias7/crab_HIMB7_V1Cumu_ppReco_effacc_v4/180314_163408/0000/",		// 11 PbPb15 MB7 ppReco acc
	"NA",			// 12 PbPb15 MB567 ppReco
	"NA",			// 13 PbPb15 MB567 ppReco eta08
	"NA",			// 14 PbPb15 MB567 ppReco acc
	"../PbPb2015_cumu/HIMinimumBias5/crab_HIMB5_V1Cumu_ppReco_poseta_effacc_v5/180316_172056/0000/",	// 15 PbPb15 MB5 ppReco acc poseta
	"../PbPb2015_cumu/HIMinimumBias6/crab_HIMB6_V1Cumu_ppReco_poseta_effacc_v5/180316_172115/0000/",	// 16 PbPb15 MB6 ppReco acc poseta
	"../PbPb2015_cumu/HIMinimumBias7/crab_HIMB7_V1Cumu_ppReco_poseta_effacc_v5/180316_172135/0000/",	// 17 PbPb15 MB7 ppReco acc poseta
	"NA",			// 18 PbPb15 MB567 ppReco acc poseta
	"../PbPb2015_cumu/HIMinimumBias5/crab_HIMB5_V1Cumu_ppReco_effacc_b12_v5/180318_011356/0000/",		// 19 PbPb15 MB5 ppReco acc b12
	"../PbPb2015_cumu/HIMinimumBias6/crab_HIMB6_V1Cumu_ppReco_effacc_b12_v5/180318_011412/0000/",		// 20 PbPb15 MB6 ppReco acc b12
	"../PbPb2015_cumu/HIMinimumBias7/crab_HIMB7_V1Cumu_ppReco_effacc_b12_v5/180318_011428/0000/",		// 21 PbPb15 MB7 ppReco acc b12
	"NA",		// 22 PbPb15 MB567 ppReco acc b12
	"../PbPb2015_cumu/HIMinimumBias5/crab_HIMB5_V1Cumu_ppReco_poseta_effacc_b12_v5/180318_203943/0000/",	// 23 PbPb15 MB5 ppReco acc poseta b12
	"../PbPb2015_cumu/HIMinimumBias6/crab_HIMB6_V1Cumu_ppReco_poseta_effacc_b12_v5/180318_204001/0000/",	// 24 PbPb15 MB6 ppReco acc poseta b12
	"../PbPb2015_cumu/HIMinimumBias7/crab_HIMB7_V1Cumu_ppReco_poseta_effacc_b12_v5/180318_204018/0000/",	// 25 PbPb15 MB7 ppReco acc poseta b12
	"NA",		// 26 PbPb15 MB567 ppReco acc poseta b12
	"../PbPb2015_cumu/AMPT_PbPb5TeV_Gen/crab_AMPT1_V1_v3/180405_180525/0000/",				// 27 AMPT b12
	"../PbPb2015_cumu/MC/PionExpoPtV2/",									// 28 ToyMC V2 b12
	"../PbPb2015_cumu/MC/PionExpoPtV1V2/",									// 29 ToyMC V1 V2 b12
	"../PbPb2015_cumu/MC/PionExpoPtV1V2_3p/",								// 30 ToyMC V1 V2 b12 gap
	"../PbPb2015_cumu/AMPT_PbPb5TeV_Gen/crab_AMPT1_V1_v10/180412_232258/0000/",				// 31 AMPT b12 gap
	"../PbPb2015_cumu/HIMinimumBias5/crab_HIMB5_V1Cumu_ppReco_effacc_b12_v8/180410_232232/0000/",		// 32 PbPb15 MB5 ppReco acc b12 gap
	"../PbPb2015_cumu/HIMinimumBias6/crab_HIMB6_V1Cumu_ppReco_effacc_b12_v8/180410_232303/0000/",		// 33 PbPb15 MB6 ppReco acc b12 gap
	"../PbPb2015_cumu/HIMinimumBias7/crab_HIMB7_V1Cumu_ppReco_effacc_b12_v8/180410_232334/0000/",		// 34 PbPb15 MB7 ppReco acc b12 gap
	"NA",	// 35 PbPb15 MB567 ppReco acc b12 gap
	"../PbPb2015_cumu/MC/PionExpoPtV1V2_v2/",								// 36 ToyMC V1 V2 b12 gap v1odd001
	"../PbPb2015_cumu/AMPT_PbPb5TeV_Gen/crab_AMPT1_V1_odd_v1/180411_184616/0000/",				// 37 AMPT b12 gap v1odd001
	"../PbPb2015_cumu/AMPT_PbPb5TeV_Gen/crab_AMPT1_V1_odd_v5/180412_234642/0000/",				// 38 AMPT b12 gap v1odd
	"../PbPb2015_cumu/HIMinimumBias5/crab_HIMB5_V1Cumu_ppReco_effacc_b12_v10/180412_194938/0000/",		// 39 PbPb15 MB5 ppReco acc b12 gap with 3point
	"../PbPb2015_cumu/HIMinimumBias6/crab_HIMB6_V1Cumu_ppReco_effacc_b12_v10/180412_194958/0000/",		// 40 PbPb15 MB6 ppReco acc b12 gap with 3point
	"../PbPb2015_cumu/HIMinimumBias7/crab_HIMB7_V1Cumu_ppReco_effacc_b12_v10/180412_195017/0000/",		// 41 PbPb15 MB7 ppReco acc b12 gap with 3point
	"NA",		// 42 PbPb15 MB567 ppReco acc b12 gap with 3point
	"../PbPb2015_cumu/AMPT_PbPb5TeV_Gen/crab_AMPT1_V1_odd003_v2/180414_230056/0000/",			// 43 AMPT b12 gap v1odd003
};

char const * ftxt[] = {
	"txt/test/",			// 0
	"txt/PbPb15_HIMB2/",		// 1
	"txt/PbPb15_HIMB2_eta08/",		// 2
	"txt/PbPb15_ppReco5/",			// 3
	"txt/PbPb15_ppReco6/",			// 4
	"txt/PbPb15_ppReco7/",			// 5
	"txt/PbPb15_ppReco5_eta08/",		// 6
	"txt/PbPb15_ppReco6_eta08/",		// 7
	"txt/PbPb15_ppReco7_eta08/",		// 8
	"txt/PbPb15_ppReco5_acc/",		// 9
	"txt/PbPb15_ppReco6_acc/",		// 10
	"txt/PbPb15_ppReco7_acc/",		// 11
	"txt/PbPb15_ppReco567/",		// 12
	"txt/PbPb15_ppReco567_eta08/",		// 13
	"txt/PbPb15_ppReco567_acc/",		// 14
	"txt/PbPb15_ppReco5_poseta_acc/",	// 15
	"txt/PbPb15_ppReco6_poseta_acc/",	// 16
	"txt/PbPb15_ppReco7_poseta_acc/",	// 17
	"txt/PbPb15_ppReco567_poseta_acc/",	// 18
	"txt/PbPb15_ppReco5_b12_acc/",		// 19
	"txt/PbPb15_ppReco6_b12_acc/",		// 20
	"txt/PbPb15_ppReco7_b12_acc/",		// 21
	"txt/PbPb15_ppReco567_b12_acc/",	// 22
	"txt/PbPb15_ppReco5_poseta_b12_acc/",	// 23
	"txt/PbPb15_ppReco6_poseta_b12_acc/",	// 24
	"txt/PbPb15_ppReco7_poseta_b12_acc/",	// 25
	"txt/PbPb15_ppReco567_poseta_b12_acc/",	// 26
	"txt/AMPT_b12/",			// 27
	"txt/ToyMC_b12/",			// 28
	"txt/ToyMC_V1V2_b12/",			// 29
	"txt/ToyMC_V1V2_gap/",			// 30
	"txt/AMPT_gap/",			// 31
	"txt/PbPb15_ppReco5_b12_acc_gap/",	// 32
	"txt/PbPb15_ppReco6_b12_acc_gap/",	// 33
	"txt/PbPb15_ppReco7_b12_acc_gap/",	// 34
	"txt/PbPb15_ppReco567_b12_acc_gap/",	// 35
	"txt/ToyMC_V1V2_b12_v1odd001/",		// 36
	"txt/AMPT_gap_v1odd001/",		// 37
	"txt/AMPT_gap_v1odd/",			// 38
	"txt/PbPb15_ppReco5_b12_acc_gap_3p/",	// 39
	"txt/PbPb15_ppReco6_b12_acc_gap_3p/",	// 40
	"txt/PbPb15_ppReco7_b12_acc_gap_3p/",	// 41
	"txt/PbPb15_ppReco567_b12_acc_gap_3p/",	// 42
	"txt/AMPT_gap_v1odd003/",		// 43
};

#include <TChain.h>
#include <iostream>

TChain * chV = new TChain("trV");
void addchain(int s1)
{
        std::cout << fname[s1] << std::endl;
        chV->Add(Form("%s/*.root/V1Cumu/trV", fname[s1]));
}
