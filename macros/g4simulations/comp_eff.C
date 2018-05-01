//#include "sPhenixStyle.C"
#include <vector>
#include "/phenix/u/yuhw/RootMacros/sPHENIXStyle/sPhenixStyle.C"

float BinorminalError(const float pass, const float all){
	if(pass < 0) return 0;
	if(all <= 0) return 0;
	if(pass > all) return 0;
	float r = pass/all;
	return sqrt(r*(1-r)/all);
}

TH1D *GetEffpT(const char* input){

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

	TString gpt_cut = Form("abs(gpt-30)<0.5");
	//TString gpt_cut = Form("(gpt<2.&&gpt>0.5)");

	//TH1D* h3_den = new TH1D("h3_den","; p_{T}; eff.",81, -0.25, 40.25);
	//TH1D* h3_den = new TH1D("h3_den","; p_{T}; eff.",41, -0.5, 40.5);
	//TH1D* h3_den = new TH1D("h3_den","; p_{T}; eff.",21, -1, 41);
	TH1D* h3_den = new TH1D("h3_den","; p_{T}; eff.",11, -2, 42.);
	TH1D* h3_num = (TH1D*)h3_den->Clone("h3_num");;
	TH1D* h3_eff = (TH1D*)h3_den->Clone("h3_eff");;

	cout<<__LINE__<<": "<< good_track_cut <<endl;
	ntp_gtrack->Project("h3_den","gpt",good_gtrack_cut);
	ntp_track->Project("h3_num","gpt",(good_gtrack_cut+"&&"+good_track_cut).Data());
	//ntp_track->Draw( "gpt>>h3_num",(good_gtrack_cut+"&&"+good_track_cut).Data());

	//look at maps matching eff
	//ntp_gtrack->Draw("gpt>>h3_den",good_track_cut);
	//ntp_gtrack->Draw("gpt>>h3_num",Form("(%s)&&nmaps>0",good_track_cut));

	for(int i=1;i<=h3_den->GetNbinsX();++i){
		double pass = h3_num->GetBinContent(i);
		double all = h3_den->GetBinContent(i);
		double eff = 0;
		if(all > pass)
			eff = pass/all;
		else if(all > 0)
			eff = 1.;

		double err = BinorminalError(pass, all); 
		h3_eff->SetBinContent(i, eff);
		h3_eff->SetBinError(i, err);
	}

	h3_eff->SetStats(0);
	h3_eff->SetTitle("; p_{T} [GeV/c]; eff.");
	h3_eff->SetMarkerStyle(20);
	h3_eff->SetMarkerColor(kBlack);
	h3_eff->SetLineColor(kBlack);
	h3_eff->GetYaxis()->SetRangeUser(0.0, 1.);


	return h3_eff;

}

void comp_eff(
		){
	SetsPhenixStyle();

	int colors[] = {1, 2, 4, 6, 8, 9, 40, 41, 42};

	vector<char*> inputs;
	vector<char*> input_names;

	inputs.push_back("eval_v3_1.root");
	input_names.push_back("Central, 1#mum");

	inputs.push_back("eval_v3_100.root");
	input_names.push_back("Central, 100#mum");

	inputs.push_back("eval_v3_5000.root");
	input_names.push_back("Central, 5mm");

	inputs.push_back("eval_v3_pu200_100.root");
	input_names.push_back("Central+PU200, 100#mum");

	inputs.push_back("eval_v3_pu200_5000.root");
	input_names.push_back("Central+PU200, 5mm");

	TCanvas * c3 = new TCanvas("c3","c3");
	TLegend *leg = new TLegend(0.1,0.7,0.48,0.9);

	for(int i=0;i<inputs.size();++i) {
		TH1D * eff_pt = GetEffpT(inputs[i]);
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
