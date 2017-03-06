/*!
 *  \file	    RunGenFit.C	
 *  \brief		Example macro to run PHG4TrackKalmanFitter
 *  \detail		http://www.phenix.bnl.gov/WWW/offline/doxygen_sPHENIX/html/da/d6e/classPHG4TrackKalmanFitter.html
 *  \author		Haiwang Yu <yuhw@nmsu.edu>
 */
void RunGenFit(
		const int nevents = 0,
		const char* input = "SvtxTracks.root",
		const char* output = "SvtxTracksRefit.root"
		) {

	gSystem->Load("libphool.so");
	gSystem->Load("libfun4all.so");
	gSystem->Load("libg4dst.so");
	gSystem->Load("libg4hough.so");

	Fun4AllServer *se = Fun4AllServer::instance();
	se->Verbosity(0); 

	PHG4TrackKalmanFitter *kalman = new PHG4TrackKalmanFitter();

	kalman->Verbosity(10);

	//kalman->set_cut_min_p_T(-0.1);

	//MIE, MAPS_TPC, MAPS_IT_TPC, LADDER_MAPS_TPC, LADDER_MAPS_IT_TPC, LADDER_MAPS_LADDER_IT_TPC, MAPS_LADDER_IT_TPC
	//kalman->set_detector_type(PHG4TrackKalmanFitter::LADDER_MAPS_LADDER_IT_TPC);

	kalman->set_output_mode(PHG4TrackKalmanFitter::OverwriteOriginalNode);//MakeNewNode, OverwriteOriginalNode, DebugMode
	//kalman->set_fit_primary_tracks(false);

	//kalman->set_track_fitting_alg_name("DafRef");// KalmanFitterRefTrack, KalmanFitter, DafSimple, DafRef
	//kalman->set_primary_pid_guess(211);
	//kalman->set_vertexing_method("avf-smoothing:1");//https://rave.hepforge.org/trac/wiki/RaveMethods

	kalman->set_do_eval(true);
	kalman->set_eval_filename("PHG4TrackKalmanFitter_eval.root");

	//kalman->set_do_evt_display(true);

	se->registerSubsystem(kalman);

	Fun4AllInputManager *in = new Fun4AllDstInputManager("DSTin");

	TString tstr_input(input);
	if (tstr_input.EndsWith(".root"))
		in->AddFile( input );
	else 
		in->AddListFile( input );

	se->registerInputManager(in);

	Fun4AllDstOutputManager *out = new Fun4AllDstOutputManager("DSTOUT", output);
	se->registerOutputManager(out);


	se->run( nevents );

	se->End();

}
