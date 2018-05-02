#include "/phenix/u/yuhw/RootMacros/sPHENIXStyle/sPhenixStyle.C"

void set_hito_style(TH1* h, const int istyle) {

	const int color1 = kBlack;
	const int color2 = kGreen+2;

	if(istyle == 1) {
		h->SetMarkerStyle(20);
		h->SetMarkerColor(color1);
		h->SetLineColor(color1);
	}
	if(istyle == 2) {
		h->SetMarkerStyle(20);
		h->SetMarkerColor(color2);
		h->SetLineColor(color2);
	}
	if(istyle == 3) {
		h->SetMarkerStyle(4);
		h->SetMarkerColor(color1);
		h->SetLineColor(color1);
	}
	if(istyle == 4) {
		h->SetMarkerStyle(4);
		h->SetMarkerColor(color2);
		h->SetLineColor(color2);
	}
}


void plot_ntp_cluster_dist (
		const char* input = "g4svtx_eval.root",
		const char* cut = "mygr > 0"
		) {

	//gROOT->LoadMacro("SetOKStyle.C");

	SetsPhenixStyle();

	int max_entry = 1000000;

	gStyle->SetOptFit();

	TFile *_file0 = TFile::Open(input);
	TNtuple *ntp_cluster = (TNtuple*) _file0->Get("ntp_cluster");

	ntp_cluster->SetAlias("r","sqrt(x*x+y*y)");
	ntp_cluster->SetAlias("mygr","sqrt(gx*gx+gy*gy)");
	ntp_cluster->SetAlias("gpt","sqrt(gpx*gpx+gpy*gpy)");
	ntp_cluster->SetAlias("drphi","mygr*TMath::ATan2(y,x) - mygr*TMath::ATan2(gy,gx)");
	ntp_cluster->SetAlias("dz","z - gz");

	ntp_cluster->SetAlias("phi","1.*TMath::ATan2(y,x)");
	ntp_cluster->SetAlias("gphi","1.*TMath::ATan2(gy,gx)");
	ntp_cluster->SetAlias("theta","1.*atan2(r,z)");
	ntp_cluster->SetAlias("gtheta","1.*atan2(mygr,gz)");

	//ntp_cluster->Scan("ephi*sqrt(12.):phisize");


	const char* grcut1 = "(layer <= 2)";
	const char* grcut2 = "(layer >= 3 && layer <= 6)";
	const char* grcut3 = "(layer >= 7 && layer <= 66)";

	TCanvas *c0 = new TCanvas("c0","c0");
	c0->Divide(4,2);

	int ipad = 1;

	float range = 5;

	c0->cd(ipad++)->SetGrid();
	range = 20e-4;
	ntp_cluster->Draw(
			"drphi>>h1",
			Form("abs(drphi)<%f&&%s",range,grcut1)
			,"",max_entry);
	h1->SetMarkerStyle(20);
	h1->Fit("gaus");
	h1->SetTitle(";drphi [cm];");

	c0->cd(ipad++)->SetGrid();
	range = 100e-4;
	ntp_cluster->Draw(
			"drphi>>h2",
			Form("abs(drphi)<%f&&%s",range,grcut2)
			,"",max_entry);
	h2->SetMarkerStyle(20);
	//h2->Fit("gaus");
	h2->SetTitle(";drphi [cm];");

	c0->cd(ipad++)->SetGrid();
	range = 1000e-4;
	ntp_cluster->Draw(
			"drphi>>h3",
			Form("abs(drphi)<%f&&%s&&gz>0",range,grcut3)
			,"",max_entry);
	h3->SetMarkerStyle(20);
	h3->Fit("gaus");
	h3->SetTitle(";drphi [cm];");

	c0->cd(ipad++)->SetGrid();
	int n_layer = 80;
	double inner_radius = 0.0;
	double outer_radius = 80.;
	double thickness = (outer_radius-inner_radius)/n_layer;

	range = 5;

	TH2D* _h2d_Delta_rphi_vs_gr = new TH2D("_h2d_Delta_rphi_vs_gr","_h2d_Delta_rphi_vs_gr",
			n_layer, inner_radius, outer_radius,
			100, -range, range);
	ntp_cluster->Project("_h2d_Delta_rphi_vs_gr",
			"drphi/ephi:mygr",
			Form("abs(drphi/ephi)<%f&&%s",range,cut)
			,"",max_entry);

	_h2d_Delta_rphi_vs_gr->FitSlicesY();

	set_hito_style(_h2d_Delta_rphi_vs_gr_1, 3);
	set_hito_style(_h2d_Delta_rphi_vs_gr_2, 1);
	_h2d_Delta_rphi_vs_gr_1->SetTitle("; mygr [cm]; rphi pull");
	_h2d_Delta_rphi_vs_gr_1->GetYaxis()->SetRangeUser(-0.5, 1.5);
	_h2d_Delta_rphi_vs_gr_1->SetStats(0);
	_h2d_Delta_rphi_vs_gr_1->Draw("e");
	_h2d_Delta_rphi_vs_gr_2->Draw("esame");
	//_h2d_Delta_rphi_vs_gr->Draw();


	c0->cd(ipad++)->SetGrid();
	range = 20e-4;
	ntp_cluster->Draw(
			"dz>>h4",
			Form("abs(dz)<%f&&%s",range,grcut1)
			,"",max_entry);
	h4->SetMarkerStyle(20);
	h4->Fit("gaus");
	h4->SetTitle(";dz [cm]; ");

	c0->cd(ipad++)->SetGrid();
	range = 1.5;
	ntp_cluster->Draw(
			"dz>>h5(100,-1.5,1.5)",
			Form("abs(dz)<%f&&%s",range,grcut2)
			,"",max_entry);
	h5->SetMarkerStyle(20);
	h5->GetXaxis()->SetRangeUser(-1.5,1.5);
	//h5->Fit("gaus");
	h5->SetTitle(";dz [cm]; ");

	c0->cd(ipad++)->SetGrid();
	range = 3000e-4;
	ntp_cluster->Draw(
			"dz>>h6",
			Form("abs(dz)<%f&&%s",range,grcut3)
			,"",max_entry);
	h6->SetMarkerStyle(20);
	h6->Fit("gaus");
	h6->SetTitle(";dz [cm]; ");







	c0->cd(ipad++)->SetGrid();
	range = 5;
	TH2D* _h2d_Delta_z_vs_gr = new TH2D("_h2d_Delta_z_vs_gr","_h2d_Delta_z_vs_gr",
			n_layer, inner_radius, outer_radius,
			100, -range, range);
	ntp_cluster->Project("_h2d_Delta_z_vs_gr",
			"dz/ez:mygr",
			Form("abs(dz/ez)<%f&&%s",range,cut)
			,"",max_entry);
	_h2d_Delta_z_vs_gr->FitSlicesY();

	set_hito_style(_h2d_Delta_z_vs_gr_1, 3);
	set_hito_style(_h2d_Delta_z_vs_gr_2, 1);
	_h2d_Delta_z_vs_gr_1->SetTitle("; mygr [cm]; z pull");
	_h2d_Delta_z_vs_gr_1->GetYaxis()->SetRangeUser(-0.3, 1.4);
	_h2d_Delta_z_vs_gr_1->SetStats(0);
	_h2d_Delta_z_vs_gr_1->Draw("e");
	_h2d_Delta_z_vs_gr_2->Draw("esame");

	//c0->cd(ipad++)->SetGrid();
	//ntp_cluster->Draw("zsize/(2.*ez*sqrt(12))");
	//ntp_cluster->Draw("(r*TMath::ATan2(x,y) - r*TMath::ATan2(gx,gy))/phisize", Form("abs((r*TMath::ATan2(x,y) - r*TMath::ATan2(gx,gy))/phisize)<10&&%s",cut));
	//ntp_cluster->Draw("((1.)*TMath::ATan2(gx,gy))", Form("%s",cut));

	c0->Update();
}
