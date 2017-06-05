/*!
 *  \file	    RunGenFit.C	
 *  \brief		Example macro to run PHG4KalmanPatRec
 *  \author		Haiwang Yu <yuhw@nmsu.edu>
 */

//#define _ONLY_SEEDING_
void RunKalmanPatRec(const int nevents = 0,
		const bool use_kalman_pat_rec = true, const char* input =
				"SvtxClusters.root", const char* output = "SvtxTracks.root",
		const char* g4svtx_eval_out_name = "g4svtx_eval.root") {

	gSystem->Load("libphool.so");
	gSystem->Load("libfun4all.so");
	gSystem->Load("libg4dst.so");
	gSystem->Load("libg4hough.so");

	Fun4AllServer *se = Fun4AllServer::instance();
//	se->Verbosity(10);

	if (use_kalman_pat_rec) {
		//---------------------
		// PHG4KalmanPatRec
		//---------------------

//		const int seeding_nlayer = 8;
//		const int min_seeding_nlayer = 6;
//		int seeding_layers[] = { 0, 1, 2, 7, 20, 35, 50, 66 };
//
//		const int seeding_nlayer = 10;
//		const int min_seeding_nlayer = 8;
//		int seeding_layers[] = { 0,1,2,3,5,7,20,35,50,66 };
//
//		const int seeding_nlayer = 8;
//		const int min_seeding_nlayer = 8;
//		int seeding_layers[] = { 0,1,2,3,5,7,30,60 };
//
//		const int seeding_nlayer = 8;
//		const int min_seeding_nlayer = 6;
//		int seeding_layers[] = { 0,1,2,3,4,5,6,7 };
//
//		const int seeding_nlayer = 7;
//		const int min_seeding_nlayer = 7;
//		int seeding_layers[] = { 0, 1, 2, 3, 4, 5, 6 };
//
//		const int seeding_nlayer = 3;
//		const int min_seeding_nlayer = 3;
//		int seeding_layers[] = { 0,1,2 };

//		const int seeding_nlayer = 7;
//		const int min_seeding_nlayer = 5;
//		PHG4KalmanPatRec* kalman_pat_rec = new PHG4KalmanPatRec(seeding_nlayer, min_seeding_nlayer);

//		PHG4KalmanPatRec* kalman_pat_rec = new PHG4KalmanPatRec("PHG4KalmanPatRec");
		PHG4KalmanPatRec* kalman_pat_rec = new PHG4KalmanPatRec("PHG4KalmanPatRec", 0, 4, 60);


//		kalman_pat_rec->Verbosity(100);

//		int seeding_layers[] = {7,15,25,35,45,55,66};
//		kalman_pat_rec->set_seeding_layer(seeding_layers, seeding_nlayer);
//
//		kalman_pat_rec->set_nlayers_all(67);
//		int seeding_layers[] = {7,15,25,35,45,55,66};
//		kalman_pat_rec->set_seeding_layer(seeding_layers, 7);
//
//		unsigned int maps_layers[] = {0, 1, 2};
//		unsigned int intt_layers[] = {3, 4, 5, 6};
//
//		kalman_pat_rec->set_maps_layers(maps_layers, 3);
//		kalman_pat_rec->set_intt_layers(intt_layers, 4);

//		kalman_pat_rec->set_nlayers_all(65);
//		int seeding_layers[] = {7,15,25,35,45,55,64};
//		kalman_pat_rec->set_seeding_layer(seeding_layers, 7);
//
//		unsigned int maps_layers[] = {0};
//		kalman_pat_rec->set_maps_layers(maps_layers, 1);
//
//		unsigned int intt_layers[] = {1, 2, 3, 4};
//		kalman_pat_rec->set_intt_layers(intt_layers, 4);

//		kalman_pat_rec->set_mag_field(1.4);
//		kalman_pat_rec->setRejectGhosts(true);
//		kalman_pat_rec->setRemoveHits(false);
//		kalman_pat_rec->setCutOnDCA(true);
//		kalman_pat_rec->setPtRescaleFactor(0.9972 / 1.00117);
//		kalman_pat_rec->set_chi2_cut_init(5.0);  // place holder setter
//		kalman_pat_rec->set_chi2_cut_fast(10.0, 50.0, 75.0);
//		kalman_pat_rec->set_chi2_cut_full(5.0);
//		kalman_pat_rec->set_ca_chi2_cut(5.0);
//		kalman_pat_rec->setMaxClusterError(3.0); //place holder setter

		// ALICE ITS upgrade values for total thickness in X_0
//		kalman_pat_rec->set_material(0, 0.003);
//		kalman_pat_rec->set_material(1, 0.003);
//		kalman_pat_rec->set_material(2, 0.003);
//		kalman_pat_rec->set_material(3, 0.008);
//		kalman_pat_rec->set_material(4, 0.008);
//		kalman_pat_rec->set_material(5, 0.008);
//		kalman_pat_rec->set_material(6, 0.008);

//#ifdef _ONLY_SEEDING_
//		kalman_pat_rec->set_seeding_only_mode(true);
//#else
//		kalman_pat_rec->set_seeding_only_mode(false);
//#endif

//		kalman_pat_rec->set_blowup_factor(1.);
//		kalman_pat_rec->set_init_direction(-1);
//
//		kalman_pat_rec->set_max_search_win_phi_tpc(    0.0040);
//		kalman_pat_rec->set_min_search_win_phi_tpc(    0.0000);
//		kalman_pat_rec->set_max_search_win_theta_tpc(  0.0040);
//		kalman_pat_rec->set_min_search_win_theta_tpc(  0.0000);
//
//		kalman_pat_rec->set_max_search_win_phi_intt(   0.0100);
//		kalman_pat_rec->set_min_search_win_phi_intt(   0.0000);
//		kalman_pat_rec->set_max_search_win_theta_intt( 1.0000);
//		kalman_pat_rec->set_min_search_win_theta_intt( 0.1000);
//
//		kalman_pat_rec->set_max_search_win_phi_maps(   0.0030);
//		kalman_pat_rec->set_min_search_win_phi_maps(   0.0000);
//		kalman_pat_rec->set_max_search_win_theta_maps( 0.0030);
//		kalman_pat_rec->set_min_search_win_theta_maps( 0.0000);
//
//		kalman_pat_rec->set_search_win_phi(5.);
//		kalman_pat_rec->set_search_win_theta(5.);
//		kalman_pat_rec->set_max_incr_chi2(20.);
//		kalman_pat_rec->set_max_consecutive_missing_layer(20);
//
//		kalman_pat_rec->set_max_splitting_chi2(0.);
//		kalman_pat_rec->set_min_good_track_hits(30);
//
//		kalman_pat_rec->set_max_merging_dphi(0.1000);
//		kalman_pat_rec->set_max_merging_deta(0.1000);
//		kalman_pat_rec->set_max_merging_dr(0.1000);
//		kalman_pat_rec->set_max_merging_dz(0.1000);
//		kalman_pat_rec->set_max_share_hits(3);

		//KalmanFitter, KalmanFitterRefTrack, DafSimple, DafRef
//		kalman_pat_rec->set_track_fitting_alg_name("DafRef");

		se->registerSubsystem(kalman_pat_rec);

	} else {
		//---------------------
		// Truth Pattern Recognition
		//---------------------
		PHG4TruthPatRec* pat_rec = new PHG4TruthPatRec();
		se->registerSubsystem(pat_rec);

	}

	//---------------------
	// Kalman Filter
	//---------------------
#ifdef _ONLY_SEEDING_
#else
	PHG4TrackKalmanFitter* kalman = new PHG4TrackKalmanFitter();
//	kalman->Verbosity(100);
	kalman->set_do_evt_display(true);
//	kalman->set_track_fitting_alg_name("DafRef");
//	kalman->set_over_write_svtxtrackmap(true);
//	kalman->set_over_write_svtxvertexmap(true);
//	kalman->set_do_eval(false);
//	kalman->set_eval_filename("PHG4TrackKalmanFitter_eval.root");

	se->registerSubsystem(kalman);
#endif

	//---------------
	// Load libraries
	//---------------

	gSystem->Load("libfun4all.so");
	gSystem->Load("libg4detectors.so");
	gSystem->Load("libg4hough.so");
	gSystem->Load("libg4eval.so");


	//---------------
	// Fun4All server
	//---------------

	Fun4AllServer *se = Fun4AllServer::instance();

	//----------------
	// SVTX evaluation
	//----------------

	//SvtxEvaluator* eval = new SvtxEvaluator("SVTXEVALUATOR",g4svtx_eval_out_name);

	gSystem->Load("libSvtxEvaluatorHaiwang.so");
	SvtxEvaluatorHaiwang* eval = new SvtxEvaluatorHaiwang("SVTXEVALUATOR",g4svtx_eval_out_name);

	eval->do_cluster_eval(true);
	eval->do_g4hit_eval(true);
	eval->do_hit_eval(false);
	eval->do_gpoint_eval(false);
	eval->scan_for_embedded(false); // take all tracks if false - take only embedded tracks if true (will not record decay particles!! - loses Upsilon electrons)
	eval->Verbosity(0);
	se->registerSubsystem(eval);

	Fun4AllInputManager *in = new Fun4AllDstInputManager("DSTin");

	TString tstr_input(input);
	if (tstr_input.EndsWith(".root"))
		in->AddFile(input);
	else
		in->AddListFile(input);
	se->registerInputManager(in);

//	Fun4AllDstOutputManager *out = new Fun4AllDstOutputManager("DSTOUT",
//			output);
//	se->registerOutputManager(out);

	se->run(nevents);

	se->End();

	std::cout << " Success!! " << std::endl;
}
