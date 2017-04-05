void RunBJetModule(
		const char* input = "SvtxTracks.root",
		const char* output = "HFtag.root",
		const bool use_refit_track_vertex = false
		) {

	gSystem->Load("libfun4all.so");
	gSystem->Load("libg4eval.so");

	gSystem->Load("libg4bbc_io.so");

	gSystem->Load("libBJetModule.so");

	Fun4AllServer *se = Fun4AllServer::instance();
	se->Verbosity(0); 

	BJetModule *tm;

	tm = new BJetModule( output );

	if(use_refit_track_vertex) {
		gSystem->Load("libg4hough.so");

		PHG4TrackKalmanFitter *kalman = new PHG4TrackKalmanFitter();

		//kalman->set_output_mode(PHG4TrackKalmanFitter::MakeNewNode);//MakeNewNode, OverwriteOriginalNode, DebugMode
		//kalman->set_fit_primary_tracks(false);

		//kalman->set_track_fitting_alg_name("DafRef");// KalmanFitterRefTrack, KalmanFitter, DafSimple, DafRef
		//kalman->set_primary_pid_guess(211);
		//kalman->set_vertexing_method("avf-smoothing:1");//https://rave.hepforge.org/trac/wiki/RaveMethods

		//kalman->set_do_eval(true);
		//kalman->set_eval_filename("PHG4TrackKalmanFitter_eval.root");
		se->registerSubsystem(kalman);

		//tm->set_trackmap_name("SvtxTrackMapRefit");
		//tm->set_vertexmap_name("SvtxVertexMapRefit");
	}

	se->registerSubsystem( tm );

	Fun4AllInputManager *in = new Fun4AllDstInputManager("DSTin");

	TString tstr_input(input);
	if (tstr_input.EndsWith(".root"))
		in->AddFile( input );
	else 
		in->AddListFile( input );

	se->registerInputManager(in);

	se->run( 0 );

	se->End();

}
