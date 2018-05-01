//#include "sPhenixStyle.C"
#include "/phenix/u/yuhw/RootMacros/sPHENIXStyle/sPhenixStyle.C"

float BinorminalError(const float pass, const float all){
	if(pass < 0) return 0;
	if(all <= 0) return 0;
	if(pass > all) return 0;
	float r = pass/all;
	return sqrt(r*(1-r)/all);
}

void plot_ntp_track(
		const char* input = "g4svtx_eval.root",
		const int min_nfromtruth = 30
		){

	SetsPhenixStyle();

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

	int nbin = 30;
	float range = 0.2;

	TCanvas * c3_1 = new TCanvas("c3_1","c3_1");
	TH1D* h3_1_den = new TH1D("h3_1_den","; #eta; eff.",1000,-2,2);
	//TH1D* h3_1_den = new TH1D("h3_1_den","; p_{T}; eff.",41, -0.5, 40.5);
	TH1D* h3_1_num = (TH1D*)h3_1_den->Clone("h3_1_num");;
	TH1D* h3_1_eff = (TH1D*)h3_1_den->Clone("h3_1_eff");;

	cout<<__LINE__<<": "<< good_track_cut <<endl;
	ntp_gtrack->Draw("geta>>h3_1_den",good_gtrack_cut);
	ntp_track->Draw("geta>>h3_1_num",(good_gtrack_cut+"&&"+good_track_cut).Data());
	//ntp_track->Draw( "gpt>>h3_1_num",(good_gtrack_cut+"&&"+good_track_cut).Data());

	//look at maps matching eff
	//ntp_gtrack->Draw("gpt>>h3_1_den",good_track_cut);
	//ntp_gtrack->Draw("gpt>>h3_1_num",Form("(%s)&&nmaps>0",good_track_cut));

	for(int i=1;i<=h3_1_den->GetNbinsX();++i){
		double pass = h3_1_num->GetBinContent(i);
		double all = h3_1_den->GetBinContent(i);
		double eff = 0;
		if(all > pass)
			eff = pass/all;
		else if(all > 0)
			eff = 1.;

		double err = BinorminalError(pass, all); 
		h3_1_eff->SetBinContent(i, eff);
		h3_1_eff->SetBinError(i, err);
	}

	h3_1_eff->Draw("e,text");
	h3_1_eff->SetStats(0);
	h3_1_eff->SetTitle("; p_{T} [GeV/c]; eff.");
	h3_1_eff->SetMarkerStyle(20);
	h3_1_eff->SetMarkerColor(kBlack);
	h3_1_eff->SetLineColor(kBlack);
	h3_1_eff->GetYaxis()->SetRangeUser(0.0, 1.);

	TCanvas * c3 = new TCanvas("c3","c3");
	TH1D* h3_den = new TH1D("h3_den","; p_{T}; eff.",81, -0.25, 40.25);
	//TH1D* h3_den = new TH1D("h3_den","; p_{T}; eff.",41, -0.5, 40.5);
	TH1D* h3_num = (TH1D*)h3_den->Clone("h3_num");;
	TH1D* h3_eff = (TH1D*)h3_den->Clone("h3_eff");;

	cout<<__LINE__<<": "<< good_track_cut <<endl;
	ntp_gtrack->Draw("gpt>>h3_den",good_gtrack_cut);
	ntp_track->Draw("gpt>>h3_num",(good_gtrack_cut+"&&"+good_track_cut).Data());
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

	h3_eff->Draw("e,text");
	h3_eff->SetStats(0);
	h3_eff->SetTitle("; p_{T} [GeV/c]; eff.");
	h3_eff->SetMarkerStyle(20);
	h3_eff->SetMarkerColor(kBlack);
	h3_eff->SetLineColor(kBlack);
	h3_eff->GetYaxis()->SetRangeUser(0.0, 1.);


	TCanvas * c1 = new TCanvas("c1","c1");
	c1->SetGrid(1,1);
	//TH2D*h1 = new TH2D("h1","h1",10,0,30,100,-0.1,0.1);
	TH2D*h1 = new TH2D("h1","h1",31,-0.5,30.5,nbin,-range,range);
	ntp_track->Draw("dpt:gpt>>h1",good_track_cut.Data());
	//h1->FitSlicesY(0,0,-1,0,"qnrl");
	h1->FitSlicesY();
	TH1D*h1_1 = (TH1D*)gDirectory->Get("h1_1");
	TH1D*h1_2 = (TH1D*)gDirectory->Get("h1_2");
	h1_2->Draw("e");
	h1_1->Draw("same");

	h1_1->SetMarkerStyle(4);
	h1_1->SetMarkerColor(kBlack);
	h1_1->SetLineColor(kBlack);

	h1_2->SetMarkerStyle(20);
	h1_2->SetMarkerColor(kBlack);
	h1_2->SetLineColor(kBlack);
	h1_2->GetYaxis()->SetRangeUser(-0.02,0.06);
	//h1_2->GetYaxis()->SetRangeUser(0.,0.02);
	h1_2->GetYaxis()->SetTitleOffset(1.5);
	h1_2->SetStats(0);
	h1_2->SetTitle(";p_{T} [GeV/c];#frac{#Delta p_{T}}{p_{T}}");

	TCanvas * c9 = new TCanvas("c9","c9");
	ntp_track->Draw("dca2d:gpt>>h9(31,-0.5,30.5,50,-0.02,0.02)",good_track_cut.Data());
	h9->FitSlicesY();
	TH1D* h9_1 = (TH1D*)gDirectory->Get("h9_1");
	TH1D* h9_2 = (TH1D*)gDirectory->Get("h9_2");

	h9_2->Draw("e");
	h9_1->Draw("same");

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

	return;

	TCanvas * c2 = new TCanvas("c2","c2");
	//ntp_track->Draw("dpt>>h2(100,-0.1,0.1)","gpt>4.5&&gpt<5.5","e");
	ntp_track->Draw(Form("dpt>>h2(%d,%f,%f)",nbin,-range,range),
			(good_track_cut+"&&"+gpt_cut).Data()
			,"e");
	h2->Fit("gaus","");
	h2->SetMarkerStyle(20);
	h2->SetMarkerColor(kBlack);
	h2->SetLineColor(kBlack);
	h2->SetTitle(Form("%s;#frac{#Delta p_{T}}{p_{T}};",good_track_cut));
	h2->GetXaxis()->SetTitleOffset(1.5);

	int n_good_trac_in_ntp_gtrack = ntp_gtrack->GetEntries(Form("nfromtruth>=%d",min_nfromtruth));

	TCanvas * c4 = new TCanvas("c4","c4");
	ntp_cluster->Draw("layer>>h4(80,-1.5,78.5)","trackID>=0&&gtrackID>=0");
	h4->Scale(1./ntp_gtrack->GetEntries("trackID>=0&&gtrackID>=0"));
	h4->SetTitle(";layers;eff.");

	TCanvas * c5 = new TCanvas("c5","c5");
	ntp_gtrack->Draw("nhits>>h5(80,-1.5,78.5)","px==px");
	h5->SetTitle(";nhits/track;");
	//ntp_cluster->Draw("layer>>h5(80,-1.5,78.5)","");

	//TCanvas * c6 = new TCanvas("c6","c6");
	//ntp_cluster->Draw("layer>>h6(80,-1.5,78.5)","trackID==trackID","");
	//h6->Scale(1./n_good_trac_in_ntp_gtrack);
	//h6->SetTitle(";layer;");

	TCanvas * c7 = new TCanvas("c7","c7");
	//ntp_gtrack->Draw("nhits:nfromtruth>>h7(20,-0.5,19.5,20,-0.5,19.5)","nfromtruth>0","colz");
	ntp_track->Draw("nhits:nfromtruth>>h7(80,-0.5,79.5,80,-0.5,79.5)","nfromtruth>0","text");
	TLine *line = new TLine();
	line->SetLineWidth(3);
	line->SetLineColor(kRed);
	//line->DrawLine(0,0,70,70);

	h7->SetTitle("nfromtruth>0;nfromtruth;nhits");

	TCanvas * c8 = new TCanvas("c8","c8");
	ntp_gtrack->Draw(Form("nfromtruth>=(%d)",min_nfromtruth),"nfromtruth>0","text");

	nbin = 100;
	range = 0.04;

	TCanvas * c10 = new TCanvas("c10","c10");
	c10->SetLogy();

	cout<<__LINE__<<": " << "good_track_cut: " <<  good_track_cut << endl;
	cout<<__LINE__<<": " << "good_track_cut: " <<  good_track_cut << endl;

	ntp_track->Draw(Form("dca2d>>h10(%d,%f,%f)",nbin,-range,range),
			(good_track_cut+"&&"+gpt_cut).Data()
			,"e");
	h10->SetTitle(";DCA_{r} [cm]");
	h10->Fit("gaus","q");
	h10->SetMarkerStyle(20);
	h10->SetMarkerColor(kBlack);
	h10->SetLineColor(kBlack);
	h10->GetYaxis()->SetRangeUser(0.1,1000);

	cout << "good_track_cut: " <<  good_track_cut << endl;
	cout << "gpt_cut: " << gpt_cut << endl;
	TCanvas * c11 = new TCanvas("c11","c11");
	ntp_track->Draw("nmaps","","bar,text");

	//ntp_track->Draw("dpt:dca2d>>h10(100,-0.1,0.1,100,-0.1,0.1)","","colz");
	//ntp_track->Draw("dpt:quality>>h10(100,0,2,100,-0.1,0.1)","","colz");

}
