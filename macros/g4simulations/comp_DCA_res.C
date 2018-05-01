//#include "sPhenixStyle.C"
#include "/phenix/u/yuhw/RootMacros/sPHENIXStyle/sPhenixStyle.C"

float BinorminalError(const float pass, const float all){
	if(pass < 0) return 0;
	if(all <= 0) return 0;
	if(pass > all) return 0;
	float r = pass/all;
	return sqrt(r*(1-r)/all);
}

TH1D* GetpTRes(
		const char* input = "g4svtx_eval.root"
		){

	TFile*f=TFile::Open(input);
	TNtuple*ntp_track=(TNtuple*)f->Get("ntp_track");

	ntp_cluster->SetAlias("r","sqrt(x*x+y*y)");
	ntp_cluster->SetAlias("rphi","r*atan2(y,x)");
	ntp_cluster->SetAlias("gpt","sqrt(gpx*gpx+gpy*gpy)");

	ntp_gtrack->SetAlias("gpt","sqrt(gpx*gpx+gpy*gpy)");
	ntp_gtrack->SetAlias("pt","sqrt(px*px+py*py)");
	ntp_gtrack->SetAlias("gp","sqrt(gpt*gpt+gpz*gpz)");
	ntp_gtrack->SetAlias("p","sqrt(pt*pt+pz*pz)");
	ntp_gtrack->SetAlias("geta","0.5*log((gp+gpz)/(gp-gpz))");
	ntp_gtrack->SetAlias("eta","0.5*log((p+pz)/(p-pz))");
	ntp_gtrack->SetAlias("dpt","(pt-gpt)/gpt");

	ntp_track->SetAlias("gpt","sqrt(gpx*gpx+gpy*gpy)");
	ntp_track->SetAlias("pt","sqrt(px*px+py*py)");
	ntp_track->SetAlias("dpt","(pt-gpt)/gpt");

	//TString good_track_cut = Form("trackID>=0");

	//TString good_track_cut = Form("(gtrackID>=0&&gnhits>20)&&(1.*nfromtruth/nhits>0.8)&&abs(dca2d)<0.1&&quality<3&&(nmaps>-1)");
	TString good_track_cut = Form("(gtrackID>=0&&gnhits>20)&&(1.*nfromtruth/nhits>0.8)&&TMath::Abs(dca2d)<0.1&&quality<5&&(nmaps>0)");
	TString good_gtrack_cut = Form("gtrackID>=0&&gnhits>20&&gpt>1.&&abs(geta)<1.");

	TH2D* h9 = new TH2D("h9","",31,-0.5,30.5,50,-0.02,0.02);

	ntp_track->Project("h9","dca2d:gpt",good_track_cut.Data());
	h9->FitSlicesY();
	TH1D* h9_1 = (TH1D*)gDirectory->Get("h9_1");
	TH1D* h9_2 = (TH1D*)gDirectory->Get("h9_2");

	h9_1->SetMarkerStyle(4);
	h9_1->SetMarkerColor(kBlack);
	h9_1->SetLineColor(kBlack);

	h9_2->SetMarkerStyle(20);
	h9_2->SetMarkerColor(kBlack);
	h9_2->SetLineColor(kBlack);
	h9_2->GetYaxis()->SetRangeUser(-0.002,0.0100);
	//h9_2->GetYaxis()->SetRangeUser(0.0000,0.0100);
	h9_2->GetYaxis()->SetTitleOffset(1.5);
	h9_2->SetStats(0);
	h9_2->SetTitle(";p_{T} [GeV/c];DCA_{r} [cm]");



	return (TH1D*)h9_2->Clone(input);
}


void comp_DCA_res(
		){
	SetsPhenixStyle();

	int colors[] = {1, 2, 4, 6, 8, 9, 40, 41, 42};

	vector<char*> inputs;
	vector<char*> input_names;

	inputs.push_back("tony_MVTX_PU200.root");
	input_names.push_back("w/ MVTX");

	inputs.push_back("tony_no_MVTX_PU200.root");
	input_names.push_back("w/o MVTX");

	TCanvas * c3 = new TCanvas("c3","c3");
	TLegend *leg = new TLegend(0.1,0.7,0.48,0.9);

	for(int i=0;i<inputs.size();++i) {
		TH1D * eff_pt = GetpTRes(inputs[i]);
		eff_pt->SetLineColor(colors[i]);
		eff_pt->SetMarkerColor(colors[i]);
		leg->AddEntry(eff_pt, input_names[i]);
		if(i==0)
			eff_pt->Draw("e");
		else
			eff_pt->Draw("e,same");
	}

	leg->Draw();
}
