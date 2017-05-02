/*!
 *  \file	    RunGenFit.C	
 *  \brief		Example macro to run PHG4TrackKalmanFitter
 *  \detail		http://www.phenix.bnl.gov/WWW/offline/doxygen_sPHENIX/html/da/d6e/classPHG4TrackKalmanFitter.html
 *  \author		Haiwang Yu <yuhw@nmsu.edu>
 */
void RunKalmanPatRec(
		const int nevents = 0,
		const char* input = "SvtxClusters.root",
		const char* output = "SvtxTracks.root",
		const char* g4svtx_eval_out_name = "g4svtx_eval.root") {

	gSystem->Load("libphool.so");
	gSystem->Load("libfun4all.so");
	gSystem->Load("libg4dst.so");
	gSystem->Load("libg4hough.so");

	Fun4AllServer *se = Fun4AllServer::instance();
	se->Verbosity(0);

#define _USE_KALMAN_PAT_REC_

#ifdef _USE_KALMAN_PAT_REC_
	//---------------------
	// PHG4KalmanPatRec
	//---------------------
//  const int seeding_nlayer = 10;
//  const int min_seeding_nlayer = 10;
//  int seeding_layer[] = {0, 1, 2, 3, 4, 5, 6, 7, 30, 60};

	const int seeding_nlayer = 8;
	const int min_seeding_nlayer = 8;
	int seeding_layer[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

//  const int seeding_nlayer = 7;
//  const int min_seeding_nlayer = 6;
//  int seeding_layer[] = {0, 1, 2, 3, 4, 5, 6};

	PHG4KalmanPatRec* kalman_pat_rec = new PHG4KalmanPatRec(seeding_nlayer,
			min_seeding_nlayer);
	kalman_pat_rec->set_seeding_layer(seeding_layer, seeding_nlayer);

	kalman_pat_rec->set_mag_field(1.4);
	kalman_pat_rec->Verbosity(10);
	// ALICE ITS upgrade values for total thickness in X_0
	kalman_pat_rec->set_material(0, 0.003);
	kalman_pat_rec->set_material(1, 0.003);
	kalman_pat_rec->set_material(2, 0.003);
	kalman_pat_rec->set_material(3, 0.008);
	kalman_pat_rec->set_material(4, 0.008);
	kalman_pat_rec->set_material(5, 0.008);
	kalman_pat_rec->set_material(6, 0.008);
	kalman_pat_rec->setPtRescaleFactor(0.9972 / 1.00117);
	kalman_pat_rec->set_chi2_cut_init(5.0);  // 5.0
	kalman_pat_rec->set_chi2_cut_fast(10.0, 50.0, 75.0); // 10.0, 50.0, 75.0
	kalman_pat_rec->set_chi2_cut_full(5.0); //5.0
	kalman_pat_rec->set_ca_chi2_cut(5.0); //5.0
	kalman_pat_rec->setMaxClusterError(3.0); //3.0
	kalman_pat_rec->setRejectGhosts(true);
	kalman_pat_rec->setRemoveHits(false);
	kalman_pat_rec->setCutOnDCA(true);

	kalman_pat_rec->set_seeding_only_mode(false);
	kalman_pat_rec->set_do_evt_display(false);

	//loose
//	kalman_pat_rec->set_search_win_rphi(100.);
//	kalman_pat_rec->set_search_win_z(5.);
//	kalman_pat_rec->set_max_incr_chi2(100.);
//	kalman_pat_rec->set_max_consecutive_missing_layer(60);

	//realistic for ana.49
	kalman_pat_rec->set_search_win_rphi(5.);
	kalman_pat_rec->set_search_win_z(5.);
	kalman_pat_rec->set_max_incr_chi2(10.);
	kalman_pat_rec->set_max_consecutive_missing_layer(10);

	kalman_pat_rec->set_min_good_track_hits(30);

	kalman_pat_rec->set_max_merging_dphi(0.0020);
	kalman_pat_rec->set_max_merging_deta(0.0010);
	kalman_pat_rec->set_max_merging_dr(  0.0050);
	kalman_pat_rec->set_max_merging_dz(  0.0050);

	//KalmanFitter, KalmanFitterRefTrack, DafSimple, DafRef
	kalman_pat_rec->set_track_fitting_alg_name("DafSimple");

	se->registerSubsystem(kalman_pat_rec);

#else
	//---------------------
	// Truth Pattern Recognition
	//---------------------
	PHG4TruthPatRec* pat_rec = new PHG4TruthPatRec();
	se->registerSubsystem(pat_rec);

#endif

	//---------------------
	// Kalman Filter
	//---------------------
	PHG4TrackKalmanFitter* kalman = new PHG4TrackKalmanFitter();
	kalman->set_over_write_svtxtrackmap(true);
	kalman->set_over_write_svtxvertexmap(true);
	kalman->set_do_eval(false);
	kalman->set_eval_filename("PHG4TrackKalmanFitter_eval.root");
	se->registerSubsystem(kalman);


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

	SvtxEvaluator* eval = new SvtxEvaluator("SVTXEVALUATOR",
			g4svtx_eval_out_name);
	eval->do_cluster_eval(true);
	eval->do_g4hit_eval(true);
	eval->do_hit_eval(false);
	eval->do_gpoint_eval(false);
	eval->scan_for_embedded(true); // take all tracks if false - take only embedded tracks if true (will not record decay particles!! - loses Upsilon electrons)
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

}
