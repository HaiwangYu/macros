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


void plot_ntp_cluster (
		const char* input = "g4svtx_eval.root",
		const char* cut = "gr > 0"
		) {

	SetsPhenixStyle();

	TFile *_file0 = TFile::Open(input);
	TNtuple *ntp_cluster = (TNtuple*) _file0->Get("ntp_cluster");

	ntp_cluster->SetAlias("r","sqrt(x*x+y*y)");
	ntp_cluster->SetAlias("gr","sqrt(gx*gx+gy*gy)");
	ntp_cluster->SetAlias("gpt","sqrt(gpx*gpx+gpy*gpy)");
	ntp_cluster->SetAlias("dphi","gr*TMath::ATan2(y,x) - gr*TMath::ATan2(gy,gx)");
	ntp_cluster->SetAlias("dz","z - gz");

	TCanvas *c1 = new TCanvas("c1","c1");
	c1->Divide(3,2);
	c1->cd(1);
	ntp_cluster->Draw("ephi","layer<=2","",1000);
	c1->cd(2);
	ntp_cluster->Draw("ephi","layer>=3&&layer<=6","",1000);
	c1->cd(3);
	ntp_cluster->Draw("ephi","layer>=7","",1000);

	c1->cd(4);
	ntp_cluster->Draw("ez","layer<=2","",1000);
	c1->cd(5);
	ntp_cluster->Draw("ez","layer>=3&&layer<=6","",1000);
	c1->cd(6);
	ntp_cluster->Draw("ez","layer>=7","",1000);


	TCanvas *c2 = new TCanvas("c2","c2");
	c2->Divide(3,2);
	c2->cd(1);
	ntp_cluster->Draw("phisize","layer<=2","",1000);
	c2->cd(2);
	ntp_cluster->Draw("phisize","layer>=3&&layer<=6","",1000);
	c2->cd(3);
	ntp_cluster->Draw("phisize","layer>=7","",1000);

	c2->cd(4);
	ntp_cluster->Draw("zsize","layer<=2","",1000);
	c2->cd(5);
	ntp_cluster->Draw("zsize","layer>=3&&layer<=6","",1000);
	c2->cd(6);
	ntp_cluster->Draw("zsize","layer>=7","",1000);


	//ntp_cluster->Scan("ephi*sqrt(12.):phisize");


	const char* grcut1 = "(gr < 4)";
	const char* grcut2 = "(gr > 4 && gr < 29)";
	const char* grcut3 = "(gr > 29)";

	TCanvas *c0 = new TCanvas("c0","c0");
	c0->Divide(4,2);

	int ipad = 1;

	float range = 5;

	c0->cd(ipad++)->SetGrid();
	range = 5;
	ntp_cluster->Draw(
			"dphi/ephi>>h1",
			Form("abs(dphi/ephi)<%f&&%s",range,grcut1));
	h1->SetMarkerStyle(20);
	//h1->Fit("gaus");

	c0->cd(ipad++)->SetGrid();
	range = 10;
	ntp_cluster->Draw(
			"dphi/ephi>>h2",
			Form("abs(dphi/ephi)<%f&&%s",range,grcut2));
	h2->SetMarkerStyle(20);
	//h2->Fit("gaus");

	c0->cd(ipad++)->SetGrid();
	range = 5;
	ntp_cluster->Draw(
			"dphi/ephi>>h3",
			Form("abs(dphi/ephi)<%f&&%s",range,grcut3));
	h3->SetMarkerStyle(20);
	h3->Fit("gaus");

	c0->cd(ipad++)->SetGrid();
	int n_layer = 160;
	double inner_radius = 0.0;
	double outer_radius = 80.;
	double thickness = (outer_radius-inner_radius)/n_layer;

	range = 5;

	TH2D* _h2d_Delta_rphi_vs_gr = new TH2D("_h2d_Delta_rphi_vs_gr","_h2d_Delta_rphi_vs_gr",
			n_layer, inner_radius, outer_radius,
			100, -range, range);
	ntp_cluster->Project("_h2d_Delta_rphi_vs_gr",
			"dphi/ephi:gr",
			Form("abs(dphi/ephi)<%f&&%s",range,cut));
	_h2d_Delta_rphi_vs_gr->FitSlicesY();

	set_hito_style(_h2d_Delta_rphi_vs_gr_1, 3);
	set_hito_style(_h2d_Delta_rphi_vs_gr_2, 1);
	_h2d_Delta_rphi_vs_gr_1->SetTitle("r*phi pull; gr [cm]; ");
	_h2d_Delta_rphi_vs_gr_1->GetYaxis()->SetRangeUser(-0.3, 1.4);
	_h2d_Delta_rphi_vs_gr_1->SetStats(0);
	_h2d_Delta_rphi_vs_gr_1->Draw("e");
	_h2d_Delta_rphi_vs_gr_2->Draw("esame");
	//_h2d_Delta_rphi_vs_gr->Draw();


	c0->cd(ipad++)->SetGrid();
	range = 5;
	ntp_cluster->Draw(
			"dz/ez>>h4",
			Form("abs(dz/ez)<%f&&%s",range,grcut1));
	h4->SetMarkerStyle(20);
	//h4->Fit("gaus");

	c0->cd(ipad++)->SetGrid();
	range = 10;
	ntp_cluster->Draw(
			"dz/ez>>h5",
			Form("abs(dz/ez)<%f&&%s",range,grcut2));
	h5->SetMarkerStyle(20);
	//h5->Fit("gaus");

	c0->cd(ipad++)->SetGrid();
	range = 5;
	ntp_cluster->Draw(
			"dz/ez>>h6",
			Form("abs(dz/ez)<%f&&%s",range,grcut3));
	h6->SetMarkerStyle(20);
	h6->Fit("gaus");

	c0->cd(ipad++)->SetGrid();
	range = 5;
	TH2D* _h2d_Delta_z_vs_gr = new TH2D("_h2d_Delta_z_vs_gr","_h2d_Delta_z_vs_gr",
			n_layer, inner_radius, outer_radius,
			100, -range, range);
	ntp_cluster->Project("_h2d_Delta_z_vs_gr",
			"dz/ez:gr",
			Form("abs(dz/ez)<%f&&%s",range,cut));
	_h2d_Delta_z_vs_gr->FitSlicesY();

	set_hito_style(_h2d_Delta_z_vs_gr_1, 3);
	set_hito_style(_h2d_Delta_z_vs_gr_2, 1);
	_h2d_Delta_z_vs_gr_1->SetTitle("z pull; gr [cm]; ");
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
