#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <MyAnalysis/TruthxAODAnalysis_STop.h>
#include <MyAnalysis/Util.h>

#include "xAODRootAccess/tools/Message.h"

using namespace MyAnalysis_STop;

ClassImp(TruthxAODAnalysis_STop)

TruthxAODAnalysis_STop :: TruthxAODAnalysis_STop ()
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // initialize().
 }



EL::StatusCode TruthxAODAnalysis_STop :: setupJob (EL::Job& job)
{
  // Here you put code that sets up the job on the submission object
  // so that it is ready to work with your algorithm, e.g. you can
  // request the D3PDReader service or add output files.  Any code you
  // put here could instead also go into the submission script.  The
  // sole advantage of putting it here is that it gets automatically
  // activated/deactivated when you add/remove the algorithm from your
  // job, which may or may not be of value to you.

  // let's initialize the algorithm to use the xAODRootAccess package
  job.useXAOD ();
  EL_RETURN_CHECK( "setupJob()", xAOD::Init() );

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthxAODAnalysis_STop :: histInitialize ()
{
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.

  if (verbose) std::cout << "In histInitialize " << std::endl;
  h_top_pt = new TH1F("h_top_pt","Top quark pt",200, 0.0, 400.);  // Intialize the top pt histogram
  wk()->addOutput (h_top_pt);

  TString name;

  for ( int i=0; i<3; i++ ) {

    std::stringstream ssi;

    ssi << i;
    std::string istr = ssi.str();
  
    name = "h_stop1_w_jets_eta_"+istr+"cut";
    h_stop1_w_jets_eta[i] = new TH1F(name.Data(),name.Data(),200,-3.0,3.0);
    wk()->addOutput(h_stop1_w_jets_eta[i]);
    name = "h_stop1_w_jets_pt_eta_"+istr+"cut";
    h_stop1_w_jets_pt_eta[i] = new TH2F(name.Data(),name.Data(),40, -3.0,3.0, 40 ,0.0,300.);
    wk()->addOutput(h_stop1_w_jets_pt_eta[i]);
    name = "h_stop1_w_jets_p_eta_"+istr+"cut";
    h_stop1_w_jets_p_eta[i] = new TH2F(name.Data(),name.Data(),40, -3.0,3.0, 40 ,0.0,300.);
    wk()->addOutput(h_stop1_w_jets_p_eta[i]);

    name = "h_distop_mass_"+istr+"cut";    
    h_distop_mass[i] = new TH1F(name.Data(),name.Data(),200,600.0,1500.);
    wk()->addOutput(h_distop_mass[i]);
    name = "h_distop_pt_"+istr+"cut";
    h_distop_pt[i] = new TH1F(name.Data(),name.Data(),400,0.0,1000.);
    wk()->addOutput(h_distop_pt[i]);
    name = "h_dixi_mass_"+istr+"cut";
    h_dixi_mass[i] = new TH1F(name.Data(),name.Data(),200,0.,700.);
    wk()->addOutput(h_dixi_mass[i]);
    name = "h_stop1_b_w_mass_"+istr+"cut";
    h_stop1_b_w_mass[i] = new TH1F(name.Data(),name.Data(),200,150.0,175.);
    wk()->addOutput(h_stop1_b_w_mass[i]);
    name = "h_stop2_b_w_mass_"+istr+"cut";
    h_stop2_b_w_mass[i] = new TH1F(name.Data(),name.Data(),200,150.0,175.);
    wk()->addOutput(h_stop2_b_w_mass[i]);
    name = "h_stop1_pt_"+istr+"cut";
    h_stop1_pt[i] = new TH1F(name.Data(),name.Data(),200,0.0,700.);
    wk()->addOutput(h_stop1_pt[i]);
    name = "h_stop1_b_pt_"+istr+"cut";
    h_stop1_b_pt[i] = new TH1F(name.Data(),name.Data(),200,0.0,700.);
    wk()->addOutput(h_stop1_b_pt[i]);
    name = "h_stop1_wj1_pt_"+istr+"cut";
    h_stop1_wj1_pt[i] = new TH1F(name.Data(),name.Data(),200,0.0,700.);
    wk()->addOutput(h_stop1_wj1_pt[i]);
    name = "h_stop1_wj2_pt_"+istr+"cut";
    h_stop1_wj2_pt[i] = new TH1F(name.Data(),name.Data(),200,0.0,700.);
    wk()->addOutput(h_stop1_wj2_pt[i]);
    name = "h_stop1_pthrust_"+istr+"cut";
    h_stop1_pthrust[i] = new TH1F(name.Data(),name.Data(),200,-700.,700.);
    wk()->addOutput(h_stop1_pthrust[i]);
    name = "h_stop1_b_pthrust_"+istr+"cut";
    h_stop1_b_pthrust[i] = new TH1F(name.Data(),name.Data(),200,-700.,700.);
    wk()->addOutput(h_stop1_b_pthrust[i]);
    name = "h_stop1_wj1_pthrust_"+istr+"cut";
    h_stop1_wj1_pthrust[i] = new TH1F(name.Data(),name.Data(),200,-700.,700.);
    wk()->addOutput(h_stop1_wj1_pthrust[i]);
    name = "h_stop1_wj2_pthrust_"+istr+"cut";
    h_stop1_wj2_pthrust[i] = new TH1F(name.Data(),name.Data(),200,-700.,700.);
    wk()->addOutput(h_stop1_wj2_pthrust[i]);
    name = "h_stop1_wj_b_MinMass_"+istr+"cut";
    h_stop1_wj_b_MinMass[i]  = new TH1F(name.Data(),name.Data(),400,0.0,1000.);
    wk()->addOutput(h_stop1_wj_b_MinMass[i]);
    name = "h_stop1_wj_b_MaxMass_"+istr+"cut";
    h_stop1_wj_b_MaxMass[i] = new TH1F(name.Data(),name.Data(),400,0.0,1000.);
    wk()->addOutput(h_stop1_wj_b_MaxMass[i]);
    name = "h_stop1_jets_pthrust_"+istr+"cut";
    h_stop1_jets_pthrust[i] = new TH1F(name.Data(),name.Data(),200,-700.,500);
    wk()->addOutput(h_stop1_jets_pthrust[i]);
    name = "h_stop2_pt_"+istr+"cut";
    h_stop2_pt[i] = new TH1F(name.Data(),name.Data(),200,0.0,700.);
    wk()->addOutput(h_stop2_pt[i]);
    name = "h_stop2_b_pt_"+istr+"cut";
    h_stop2_b_pt[i] = new TH1F(name.Data(),name.Data(),200,0.0,700.);
    wk()->addOutput(h_stop2_b_pt[i]);
    name = "h_stop2_wj1_pt_"+istr+"cut";
    h_stop2_wj1_pt[i] = new TH1F(name.Data(),name.Data(),200,0.0,700.);
    wk()->addOutput(h_stop2_wj1_pt[i]);
    name = "h_stop2_wj2_pt_"+istr+"cut";
    h_stop2_wj2_pt[i] = new TH1F(name.Data(),name.Data(),200,0.0,700.);
    wk()->addOutput(h_stop2_wj2_pt[i]);
    name = "h_stop2_wj_b_MinMass_"+istr+"cut";
    h_stop2_wj_b_MinMass[i]  = new TH1F(name.Data(),name.Data(),400,0.0,1000.);
    wk()->addOutput(h_stop2_wj_b_MinMass[i]);
    name = "h_stop2_wj_b_MaxMass_"+istr+"cut";
    h_stop2_wj_b_MaxMass[i] = new TH1F(name.Data(),name.Data(),400,0.0,1000.);
    wk()->addOutput(h_stop2_wj_b_MaxMass[i]);
    name = "h_stop2_pthrust_"+istr+"cut";
    h_stop2_pthrust[i] = new TH1F(name.Data(),name.Data(),200,-700.,700.);
    wk()->addOutput(h_stop2_pthrust[i]);
    name = "h_stop2_b_pthrust_"+istr+"cut";
    h_stop2_b_pthrust[i] = new TH1F(name.Data(),name.Data(),200,-700.,700.);
    wk()->addOutput(h_stop2_b_pthrust[i]);
    name = "h_stop2_wj1_pthrust_"+istr+"cut";
    h_stop2_wj1_pthrust[i] = new TH1F(name.Data(),name.Data(),200,-700.,700.);
    wk()->addOutput(h_stop2_wj1_pthrust[i]);
    name = "h_stop2_wj2_pthrust_"+istr+"cut";
    h_stop2_wj2_pthrust[i] = new TH1F(name.Data(),name.Data(),200,-700.,700.);
    wk()->addOutput(h_stop2_wj2_pthrust[i]);
    name = "h_stop2_jets_pthrust_"+istr+"cut";
    h_stop2_jets_pthrust[i] = new TH1F(name.Data(),name.Data(),200,-700.,700.);
    wk()->addOutput(h_stop2_jets_pthrust[i]);
    
    name = "h_dixi_pt_"+istr+"cut";
    h_dixi_pt[i] = new TH1F(name.Data(),name.Data(),200,0.0,700.);
    wk()->addOutput(h_dixi_pt[i]);
    name = "h_dixi_pthrust_"+istr+"cut";
    h_dixi_pthrust[i] = new TH1F(name.Data(),name.Data(),200,-700.,700.);
    wk()->addOutput(h_dixi_pthrust[i]);

    name = "h_stop1_jets_pt_thrust_"+istr+"cut";
    h_stop1_jets_pt_thrust[i] = new TH1F(name.Data(),name.Data(),200,-700.,700.);
    wk()->addOutput(h_stop1_jets_pt_thrust[i]);
    name = "h_stop1_b_pt_thrust_"+istr+"cut";
    h_stop1_b_pt_thrust[i] = new TH1F(name.Data(),name.Data(),200,-700.,700.);
    wk()->addOutput(h_stop1_b_pt_thrust[i]);
    name = "h_stop2_jets_pt_thrust_"+istr+"cut";
    h_stop2_jets_pt_thrust[i] = new TH1F(name.Data(),name.Data(),200,-700.,700.);
    wk()->addOutput(h_stop2_jets_pt_thrust[i]);
    name = "h_stop2_b_pt_thrust_"+istr+"cut";
    h_stop2_b_pt_thrust[i] = new TH1F(name.Data(),name.Data(),200,-700.,700.);
    wk()->addOutput(h_stop2_b_pt_thrust[i]);

    name = "h_stop1_w_thrust2D_"+istr+"cut";
    h_stop1_w_thrust2D[i] = new TH2F(name.Data(),name.Data(),40,-700.,700.,40,-700.,600.);
    wk()->addOutput(h_stop1_w_thrust2D[i]);
    name = "h_stop1_b_thrust2D_"+istr+"cut";
    h_stop1_b_thrust2D[i] = new TH2F(name.Data(),name.Data(),40,-700.,700.,40,-700.,600.);
    wk()->addOutput(h_stop1_b_thrust2D[i]);
    name = "h_stop2_w_thrust2D_"+istr+"cut";
    h_stop2_w_thrust2D[i] = new TH2F(name.Data(),name.Data(),40,-700.,700.,40,-700.,600.);
    wk()->addOutput(h_stop2_w_thrust2D[i]);
    name = "h_stop2_b_thrust2D_"+istr+"cut";
    h_stop2_b_thrust2D[i] = new TH2F(name.Data(),name.Data(),40,-700.,700.,40,-700.,600.);
    wk()->addOutput(h_stop2_b_thrust2D[i]);

    name = "h_ISR_MET_delphi_"+istr+"cut";
    h_ISR_MET_delphi[i] = new TH1F(name.Data(),name.Data(),40,0.0,TMath::Pi());
    wk()->addOutput(h_ISR_MET_delphi[i]);

    name = "h_nISR_"+istr+"cut";
    h_nISR[i] = new TH1F(name.Data(),name.Data(),5,-0.5,4.5);
    wk()->addOutput(h_nISR[i]);

    name = "h_noISR_dixi_pt_"+istr+"cut";
    h_noISR_dixi_pt[i] = new TH1F(name.Data(),name.Data(),400,0.0,1000.);
    wk()->addOutput(h_noISR_dixi_pt[i]);
    name = "h_noISR_tt_pt_"+istr+"cut";
    h_noISR_tt_pt[i] = new TH1F(name.Data(),name.Data(),400,0.0,1000.);
    wk()->addOutput(h_noISR_tt_pt[i]);
    name = "h_noISR_distop_pt_"+istr+"cut";
    h_noISR_distop_pt[i] = new TH1F(name.Data(),name.Data(),400,0.0,1000.);
    wk()->addOutput(h_noISR_distop_pt[i]);

    name = "h_1ISR_totalPt_"+istr+"cut";
    h_1ISR_totalPt[i] = new TH1F(name.Data(),name.Data(),400,0.0,1000.);

    name = "h_1ISR_jetPt_"+istr+"cut";
    h_1ISR_jetPt[i] = new TH1F(name.Data(),name.Data(),400,0.0,1000.);
    name = "h_1ISR_jetEta_"+istr+"cut";
    h_1ISR_jetEta[i] = new TH1F(name.Data(),name.Data(),400,-5.0,5.0);
    name = "h_1ISR_jet_b_MinMass_"+istr+"cut";
    h_1ISR_jet_b_MinMass[i] = new TH1F(name.Data(),name.Data(),400,0.0,1000.);
    name = "h_1ISR_jet_b_MaxMass_"+istr+"cut";
    h_1ISR_jet_b_MaxMass[i] = new TH1F(name.Data(),name.Data(),400,0.0,1000.);
    name = "h_1ISR_PAlongThrust_"+istr+"cut";
    h_1ISR_PAlongThrust[i] = new TH1F(name.Data(),name.Data(),400,-1000.0,1000.0);

    name = "h_1ISR_pt_distop_pt_"+istr+"cut";
    h_1ISR_pt_distop_pt[i] = new TH2F(name.Data(),name.Data(),100,0.0,1000., 100, 0.0, 1000.);
    name = "h_1ISR_pt_Met_"+istr+"cut";
    h_1ISR_pt_Met[i] = new TH2F(name.Data(),name.Data(),100,0.0,1000., 100, 0.0, 1000.);
    name = "h_1ISR_PAlongThrust_Met_"+istr+"cut";
    h_1ISR_PAlongThrust_Met[i] = new TH2F(name.Data(),name.Data(),100,-1000.0,1000., 100, 0.0, 1000.);
    name = "h_1ISR_pt_tt_pt_"+istr+"cut";
    h_1ISR_pt_tt_pt[i] = new TH2F(name.Data(),name.Data(),100,0.0,1000., 100, 0.0, 1000.);
    name = "h_1ISR_b_MinMass_"+istr+"cut";
    h_1ISR_pt_ISR_b_MinMass[i] = new TH2F(name.Data(),name.Data(),100,0.0,1000., 100, 0.0, 1000.);
    name = "h_1ISR_b_MaxMass_"+istr+"cut";
    h_1ISR_pt_ISR_b_MaxMass[i] = new TH2F(name.Data(),name.Data(),100,0.0,1000., 100, 0.0, 1000.);
    name = "h_1ISR_Met_ISR_b_MinMass_"+istr+"cut";
    h_1ISR_Met_ISR_b_MinMass[i] = new TH2F(name.Data(),name.Data(),100,0.0,1000., 100, 0.0, 1000.);
    name = "h_1ISR_Met_ISR_b_MaxMass_"+istr+"cut";
    h_1ISR_Met_ISR_b_MaxMass[i] = new TH2F(name.Data(),name.Data(),100,0.0,1000., 100, 0.0, 1000.);

    name = "h_2ISR_totalPt_"+istr+"cut";
    h_2ISR_totalPt[i] = new TH1F(name.Data(),name.Data(),400,0.0,1000.);
    
    name = "h_2ISR_jetPt_"+istr+"cut";
    h_2ISR_jetPt[i] = new TH1F(name.Data(),name.Data(),400,0.0,1000.);
    name = "h_2ISR_jetEta_"+istr+"cut";
    h_2ISR_jetEta[i] = new TH1F(name.Data(),name.Data(),400,-5.0,5.0);
    name = "h_2ISR_jet_b_MinMass_"+istr+"cut";
    h_2ISR_jet_b_MinMass[i] = new TH1F(name.Data(),name.Data(),400,0.0,1000.);
    name = "h_2ISR_jet_b_MaxMass_"+istr+"cut";
    h_2ISR_jet_b_MaxMass[i] = new TH1F(name.Data(),name.Data(),400,0.0,1000.);
    name = "h_2ISR_PAlongThrust_"+istr+"cut";
    h_2ISR_PAlongThrust[i] = new TH1F(name.Data(),name.Data(),400,-1000.0,1000.0);

    name = "h_2ISR_pt_distop_pt_"+istr+"cut";
    h_2ISR_pt_distop_pt[i] = new TH2F(name.Data(),name.Data(),100,0.0,1000., 100, 0.0, 1000.);
    name = "h_2ISR_pt_Met_"+istr+"cut";
    h_2ISR_pt_Met[i] = new TH2F(name.Data(),name.Data(),100,0.0,1000., 100, 0.0, 1000.);
    name = "h_2ISR_PAlongThrust_Met_"+istr+"cut";
    h_2ISR_PAlongThrust_Met[i] = new TH2F(name.Data(),name.Data(),100,-1000.0,1000., 100, 0.0, 1000.);
    name = "h_2ISR_pt_tt_pt_"+istr+"cut";
    h_2ISR_pt_tt_pt[i] = new TH2F(name.Data(),name.Data(),100,0.0,1000., 100, 0.0, 1000.);
    name = "h_2ISR_b_MinMass_"+istr+"cut";
    h_2ISR_pt_ISR_b_MinMass[i] = new TH2F(name.Data(),name.Data(),100,0.0,1000., 100, 0.0, 1000.);
    name = "h_2ISR_b_MaxMass_"+istr+"cut";
    h_2ISR_pt_ISR_b_MaxMass[i] = new TH2F(name.Data(),name.Data(),100,0.0,1000., 100, 0.0, 1000.);
    name = "h_2ISR_Met_ISR_b_MinMass_"+istr+"cut";
    h_2ISR_Met_ISR_b_MinMass[i] = new TH2F(name.Data(),name.Data(),100,0.0,1000., 100, 0.0, 1000.);
    name = "h_2ISR_Met_ISR_b_MaxMass_"+istr+"cut";
    h_2ISR_Met_ISR_b_MaxMass[i] = new TH2F(name.Data(),name.Data(),100,0.0,1000., 100, 0.0, 1000.);

    wk()->addOutput(h_1ISR_totalPt[i]);

    wk()->addOutput(h_1ISR_jetPt[i]);
    wk()->addOutput(h_1ISR_jetEta[i]);
    wk()->addOutput(h_1ISR_jet_b_MinMass[i]);
    wk()->addOutput(h_1ISR_jet_b_MaxMass[i]);
    wk()->addOutput(h_1ISR_PAlongThrust[i]);
    
    wk()->addOutput(h_1ISR_pt_distop_pt[i]);
    wk()->addOutput(h_1ISR_pt_Met[i]);
    wk()->addOutput(h_1ISR_PAlongThrust_Met[i]);
    wk()->addOutput(h_1ISR_pt_tt_pt[i]);
    wk()->addOutput(h_1ISR_pt_ISR_b_MinMass[i]);
    wk()->addOutput(h_1ISR_pt_ISR_b_MaxMass[i]);
    wk()->addOutput(h_1ISR_Met_ISR_b_MinMass[i]);
    wk()->addOutput(h_1ISR_Met_ISR_b_MaxMass[i]);

    wk()->addOutput(h_2ISR_totalPt[i]);

    wk()->addOutput(h_2ISR_jetPt[i]);
    wk()->addOutput(h_2ISR_jetEta[i]);
    wk()->addOutput(h_2ISR_jet_b_MinMass[i]);
    wk()->addOutput(h_2ISR_jet_b_MaxMass[i]);
    wk()->addOutput(h_2ISR_PAlongThrust[i]);

    wk()->addOutput(h_2ISR_pt_distop_pt[i]);
    wk()->addOutput(h_2ISR_pt_Met[i]);
    wk()->addOutput(h_2ISR_PAlongThrust_Met[i]);
    wk()->addOutput(h_2ISR_pt_tt_pt[i]);
    wk()->addOutput(h_2ISR_pt_ISR_b_MinMass[i]);
    wk()->addOutput(h_2ISR_pt_ISR_b_MaxMass[i]);
    wk()->addOutput(h_2ISR_Met_ISR_b_MinMass[i]);
    wk()->addOutput(h_2ISR_Met_ISR_b_MaxMass[i]);

    name = "h_delr_b1_w1_"+istr+"cut";
    h_delr_b1_w1[i] = new TH1F(name.Data(),name.Data(),400, 0.0, 5.0);
    wk()->addOutput(h_delr_b1_w1[i]);
    name = "h_delr_stop1_b1_"+istr+"cut";
    h_delr_stop1_b1[i] = new TH1F(name.Data(),name.Data(),400, 0.0, 5.0);
    wk()->addOutput(h_delr_stop1_b1[i]);
    name = "h_delr_stop1_w1j1_"+istr+"cut";
    h_delr_stop1_w1j1[i] = new TH1F(name.Data(),name.Data(),400, 0.0, 5.0);
    wk()->addOutput(h_delr_stop1_w1j1[i]);
    name = "h_delr_stop1_w1j2_"+istr+"cut";
    h_delr_stop1_w1j2[i] = new TH1F(name.Data(),name.Data(),400, 0.0, 5.0);
    wk()->addOutput(h_delr_stop1_w1j2[i]);

    name = "h_delr_b2_w2_"+istr+"cut";
    h_delr_b2_w2[i] = new TH1F(name.Data(),name.Data(),400, 0.0, 5.0);
    wk()->addOutput(h_delr_b2_w2[i]);
    name = "h_delr_stop2_b2_"+istr+"cut";
    h_delr_stop2_b2[i] = new TH1F(name.Data(),name.Data(),400, 0.0, 5.0);
    wk()->addOutput(h_delr_stop2_b2[i]);
    name = "h_delr_stop2_w2j1_"+istr+"cut";
    h_delr_stop2_w2j1[i] = new TH1F(name.Data(),name.Data(),400, 0.0, 5.0);
    wk()->addOutput(h_delr_stop2_w2j1[i]);
    name = "h_delr_stop2_w2j2_"+istr+"cut";
    h_delr_stop2_w2j2[i] = new TH1F(name.Data(),name.Data(),400, 0.0, 5.0);
    wk()->addOutput(h_delr_stop2_w2j2[i]);

    name = "h_delr_ISR_stop1_"+istr+"cut";
    h_delr_ISR_stop1[i] = new TH1F(name.Data(),name.Data(),400, 0.0, 5.0);
    wk()->addOutput(h_delr_ISR_stop1[i]);
    name = "h_delr_ISR_b1_"+istr+"cut";
    h_delr_ISR_b1[i] = new TH1F(name.Data(),name.Data(),400, 0.0, 5.0);
    wk()->addOutput(h_delr_ISR_b1[i]);
    name = "h_delr_ISR_w1_"+istr+"cut";
    h_delr_ISR_w1[i] = new TH1F(name.Data(),name.Data(),400, 0.0, 5.0);
    wk()->addOutput(h_delr_ISR_w1[i]);
    name = "h_delr_ISR_w1j1_"+istr+"cut";
    h_delr_ISR_w1j1[i] = new TH1F(name.Data(),name.Data(),400, 0.0, 5.0);
    wk()->addOutput(h_delr_ISR_w1j1[i]);
    name = "h_delr_ISR_w1j2_"+istr+"cut";
    h_delr_ISR_w1j2[i] = new TH1F(name.Data(),name.Data(),400, 0.0, 5.0);
    wk()->addOutput(h_delr_ISR_w1j2[i]);

    name = "h_delr_ISR_stop2_"+istr+"cut";
    h_delr_ISR_stop2[i] = new TH1F(name.Data(),name.Data(),400, 0.0, 5.0);
    wk()->addOutput(h_delr_ISR_stop2[i]);
    name = "h_delr_ISR_b2_"+istr+"cut";
    h_delr_ISR_b2[i] = new TH1F(name.Data(),name.Data(),400, 0.0, 5.0);
    wk()->addOutput(h_delr_ISR_b2[i]);
    name = "h_delr_ISR_w2_"+istr+"cut";
    h_delr_ISR_w2[i] = new TH1F(name.Data(),name.Data(),400, 0.0, 5.0);
    wk()->addOutput(h_delr_ISR_w2[i]);
    name = "h_delr_ISR_w2j1_"+istr+"cut";
    h_delr_ISR_w2j1[i] = new TH1F(name.Data(),name.Data(),400, 0.0, 5.0);
    wk()->addOutput(h_delr_ISR_w2j1[i]);
    name = "h_delr_ISR_w2j2_"+istr+"cut";
    h_delr_ISR_w2j2[i] = new TH1F(name.Data(),name.Data(),400, 0.0, 5.0);
    wk()->addOutput(h_delr_ISR_w2j2[i]);

    name = "h_delphi_ISR_MET_"+istr+"cut";
    h_delphi_ISR_MET[i] = new TH1F(name.Data(),name.Data(),400, 0.0, 5.0);
    wk()->addOutput(h_delphi_ISR_MET[i]);
    
    //-----------------------------------------------//

    name = "Ana_AllHad_2b_Thrust_LabFrame2_NegCone_W_minWDeltaM_NMissing_"+istr+"cut";
    Ana_AllHad_2b_Thrust_LabFrame2_NegCone_W_minWDeltaM_NMissing[i]  = new TH1F(name.Data(),name.Data(), 4, -0.5, 3.5);
    name = "Ana_AllHad_2b_Thrust_LabFrame2_MissingBothW_B_NegCone_W_minWDeltaM_WMet_DPhi_WMet_DEt_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_LabFrame2_MissingBothW_B_NegCone_W_minWDeltaM_WMet_DPhi_WMet_DEt_2D[i] = new TH2F(name.Data(),name.Data(), 40, 0.0, TMath::Pi(), 100, 0.0, 1000.);
    name = "Ana_AllHad_2b_Thrust_LabFrame2_MissingBothW_B_NegCone_W_minWDeltaM_WMet_DPhi_"+istr+"cut";
    Ana_AllHad_2b_Thrust_LabFrame2_MissingBothW_B_NegCone_W_minWDeltaM_WMet_DPhi[i] = new TH1F(name.Data(),name.Data(), 400, 0.0, TMath::Pi());
    name = "Ana_AllHad_2b_Thrust_LabFrame2_MissingBothW_B_NegCone_W_minWDeltaM_WMet_DPt_"+istr+"cut";
    Ana_AllHad_2b_Thrust_LabFrame2_MissingBothW_B_NegCone_W_minWDeltaM_WMet_DPt[i] = new TH1F(name.Data(),name.Data(), 400, 0.0, 1000.);
    name = "Ana_AllHad_2b_Thrust_LabFrame2_MissingBothW_B_NegCone_W_minWDeltaM_WMet_PThrust_"+istr+"cut";
    Ana_AllHad_2b_Thrust_LabFrame2_MissingBothW_B_NegCone_W_minWDeltaM_WMet_PThrust[i] = new TH1F(name.Data(),name.Data(), 400, -700.0, 600.);

    //----------------------------------------------//
        
    name = "Ana_AllHad_2b_Thrust_TopFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_BMom_TopMass_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TopFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_BMom_TopMass_2D[i] = new TH2F(name.Data(),name.Data(), 100, 0.0, 300.0, 100, 0.0, 1000.);
    name = "Ana_AllHad_2b_Thrust_TopFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMom_TopMass_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TopFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMom_TopMass_2D[i] = new TH2F(name.Data(),name.Data(), 100, 0.0, 300.0, 100, 0.0, 1000.);
    name = "Ana_AllHad_2b_Thrust_TopFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_BWAngle_TopMass_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TopFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_BWAngle_TopMass_2D[i] = new TH2F(name.Data(),name.Data(), 100, 0.0, TMath::Pi(), 100, 0.0, 1000.);
    name = "Ana_AllHad_2b_Thrust_TopFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_BMom_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TopFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_BMom[i] = new TH1F(name.Data(),name.Data(), 400, 0.0, 300.0);
    name = "Ana_AllHad_2b_Thrust_TopFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMom_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TopFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMom[i] = new TH1F(name.Data(),name.Data(), 400, 0.0, 300.0);
    name = "Ana_AllHad_2b_Thrust_TopFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_BWAngle_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TopFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_BWAngle[i] = new TH1F(name.Data(),name.Data(), 400, 0.0, TMath::Pi());

    name = "Ana_AllHad_2b_Thrust_TTFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_TBoost_TopMass_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TTFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_TBoost_TopMass_2D[i]= new TH2F(name.Data(),name.Data(), 100, -2.0, 2.0, 100, 0.0, 1000.);
    name = "Ana_AllHad_2b_Thrust_TTFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_ThrustAngle_TopMass_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TTFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_ThrustAngle_TopMass_2D[i]= new TH2F(name.Data(),name.Data(), 100, 0.0, TMath::Pi(), 100, 0.0, 1000.);

    name = "Ana_AllHad_2b_Thrust_TTFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_TBoost_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TTFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_TBoost[i]= new TH1F(name.Data(),name.Data(), 400, -2.0, 2.0);
    name = "Ana_AllHad_2b_Thrust_TTFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_ThrustAngle"+istr+"cut";
    Ana_AllHad_2b_Thrust_TTFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_ThrustAngle[i]= new TH1F(name.Data(),name.Data(), 400, 0.0, TMath::Pi());

    name = "Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_TopMass_TopPThrust_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_TopMass_TopPThrust_2D[i] = new TH2F(name.Data(),name.Data(), 40, -700.0, 600.0, 100, 0.0, 1000.);
    name = "Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMass_TopPThrust_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMass_TopPThrust_2D[i] = new TH2F(name.Data(),name.Data(), 40, -700.0, 600.0, 100, 0.0, 1000.);

    name = "Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_B_NegCone_W_minWDeltaM_TTMass_"+istr+"cut";
    Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_B_NegCone_W_minWDeltaM_TTMass[i] = new TH1F(name.Data(),name.Data(), 500, 0.0, 1200.);

    name = "Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMet_DPhi_WMet_DEt_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMet_DPhi_WMet_DEt_2D[i] = new TH2F(name.Data(),name.Data(), 40, 0.0, TMath::Pi(), 100, 0.0, 1000.);
    name = "Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMet_DPhi_"+istr+"cut";
    Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMet_DPhi[i] = new TH1F(name.Data(),name.Data(), 400, 0.0, TMath::Pi());
    name = "Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMet_DPt_"+istr+"cut";
    Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMet_DPt[i] = new TH1F(name.Data(),name.Data(), 400, 0.0, 1000.);
    name = "Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMet_PThrust_"+istr+"cut";
    Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMet_PThrust[i] = new TH1F(name.Data(),name.Data(), 400, -700.0, 600.);

    //----------------------------------------------------------------//  

    name = "Ana_AllHad_2b_Thrust_TopFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_BMom_TopMass_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TopFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_BMom_TopMass_2D[i] = new TH2F(name.Data(),name.Data(), 100, 0.0, 300.0, 100, 0.0, 1000.);
    name = "Ana_AllHad_2b_Thrust_TopFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMom_TopMass_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TopFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMom_TopMass_2D[i] = new TH2F(name.Data(),name.Data(), 100, 0.0, 300.0, 100, 0.0, 1000.);
    name = "Ana_AllHad_2b_Thrust_TopFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_BWAngle_TopMass_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TopFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_BWAngle_TopMass_2D[i] = new TH2F(name.Data(),name.Data(), 100, 0.0, TMath::Pi(), 100, 0.0, 1000.);
    name = "Ana_AllHad_2b_Thrust_TopFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_BMom_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TopFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_BMom[i] = new TH1F(name.Data(),name.Data(), 400, 0.0, 300.0);
    name = "Ana_AllHad_2b_Thrust_TopFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMom_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TopFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMom[i] = new TH1F(name.Data(),name.Data(), 400, 0.0, 300.0);
    name = "Ana_AllHad_2b_Thrust_TopFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_BWAngle_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TopFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_BWAngle[i] = new TH1F(name.Data(),name.Data(), 400, 0.0, TMath::Pi());

    name = "Ana_AllHad_2b_Thrust_TTFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_TBoost_TopMass_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TTFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_TBoost_TopMass_2D[i]= new TH2F(name.Data(),name.Data(), 100, -2.0, 2.0, 100, 0.0, 1000.);
    name = "Ana_AllHad_2b_Thrust_TTFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_ThrustAngle_TopMass_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TTFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_ThrustAngle_TopMass_2D[i]= new TH2F(name.Data(),name.Data(), 100, 0.0, TMath::Pi(), 100, 0.0, 1000.);

    name = "Ana_AllHad_2b_Thrust_TTFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_TBoost_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TTFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_TBoost[i]= new TH1F(name.Data(),name.Data(), 400, -2.0, 2.0);
    name = "Ana_AllHad_2b_Thrust_TTFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_ThrustAngle"+istr+"cut";
    Ana_AllHad_2b_Thrust_TTFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_ThrustAngle[i]= new TH1F(name.Data(),name.Data(), 400, 0.0, TMath::Pi());

    name = "Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_TopMass_TopPThrust_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_TopMass_TopPThrust_2D[i] = new TH2F(name.Data(),name.Data(), 40, -700.0, 600.0, 100, 0.0, 1000.);
    name = "Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMass_TopPThrust_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMass_TopPThrust_2D[i] = new TH2F(name.Data(),name.Data(), 40, -700.0, 600.0, 100, 0.0, 1000.);

    name = "Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_B_NegCone_W_minWDeltaM_TTMass_"+istr+"cut";
    Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_B_NegCone_W_minWDeltaM_TTMass[i] = new TH1F(name.Data(),name.Data(), 500, 0.0, 1200.);

    name = "Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMet_DPhi_WMet_DEt_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMet_DPhi_WMet_DEt_2D[i] = new TH2F(name.Data(),name.Data(), 40, 0.0, TMath::Pi(), 100, 0.0, 1000.);
    name = "Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMet_DPhi_"+istr+"cut";
    Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMet_DPhi[i] = new TH1F(name.Data(),name.Data(), 400, 0.0, TMath::Pi());
    name = "Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMet_DPt_"+istr+"cut";
    Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMet_DPt[i] = new TH1F(name.Data(),name.Data(), 400, 0.0, 1000.);
    name = "Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMet_PThrust_"+istr+"cut";
    Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMet_PThrust[i] = new TH1F(name.Data(),name.Data(), 400, -700.0, 600.);

    //----------------------------------------------------------------// 
    
    name = "Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_BMom_TopMass_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_BMom_TopMass_2D[i] = new TH2F(name.Data(),name.Data(), 100, 0.0, 300.0, 100, 0.0, 1000.);
    name = "Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_WMom_TopMass_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_WMom_TopMass_2D[i] = new TH2F(name.Data(),name.Data(), 100, 0.0, 300.0, 100, 0.0, 1000.);
    name = "Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_BWAngle_TopMass_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_BWAngle_TopMass_2D[i] = new TH2F(name.Data(),name.Data(), 100, 0.0, TMath::Pi(), 100, 0.0, 1000.);
    name = "Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_BMom_TopMass_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_BMom_TopMass_2D[i] = new TH2F(name.Data(),name.Data(), 100, 0.0, 300.0, 100, 0.0, 1000.);
    name = "Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_WMom_TopMass_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_WMom_TopMass_2D[i] = new TH2F(name.Data(),name.Data(), 100, 0.0, 300.0, 100, 0.0, 1000.);
    name = "Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_BWAngle_TopMass_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_BWAngle_TopMass_2D[i] = new TH2F(name.Data(),name.Data(), 100, 0.0, TMath::Pi(), 100, 0.0, 1000.);
    name = "Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_BMom_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_BMom[i] = new TH1F(name.Data(),name.Data(), 400, 0.0, 300.0);
    name = "Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_WMom_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_WMom[i] = new TH1F(name.Data(),name.Data(), 400, 0.0, 300.0);
    name = "Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_BWAngle_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_BWAngle[i] = new TH1F(name.Data(),name.Data(), 400, 0.0, TMath::Pi());
    name = "Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_BMom_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_BMom[i] = new TH1F(name.Data(),name.Data(), 400, 0.0, 300.0);
    name = "Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_WMom_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_WMom[i] = new TH1F(name.Data(),name.Data(), 400, 0.0, 300.0);
    name = "Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_BWAngle_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_BWAngle[i] = new TH1F(name.Data(),name.Data(), 400, 0.0, TMath::Pi());

    name = "Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_TBoost_TopMass_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_TBoost_TopMass_2D[i]= new TH2F(name.Data(),name.Data(), 100, -2.0, 2.0, 100, 0.0, 1000.);
    name = "Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_ThrustAngle_TopMass_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_ThrustAngle_TopMass_2D[i]= new TH2F(name.Data(),name.Data(), 100, 0.0, TMath::Pi(), 100, 0.0, 1000.);
    name = "Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_TBoost_TopMass_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_TBoost_TopMass_2D[i]= new TH2F(name.Data(),name.Data(), 100, -2.0, 2.0, 100, 0.0, 1000.);
    name = "Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_ThrustAngle_TopMass_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_ThrustAngle_TopMass_2D[i]= new TH2F(name.Data(),name.Data(), 100, 0.0, TMath::Pi(), 100, 0.0, 1000.);

    name = "Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_TBoost_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_TBoost[i]= new TH1F(name.Data(),name.Data(), 400, -2.0, 2.0);
    name = "Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_ThrustAngle_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_ThrustAngle[i]= new TH1F(name.Data(),name.Data(), 400, 0.0, TMath::Pi());
    name = "Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_TBoost_"+istr+"cut";
    Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_TBoost[i]= new TH1F(name.Data(),name.Data(), 400, -2.0, 2.0);
    name = "Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_ThrustAngle"+istr+"cut";
    Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_ThrustAngle[i]= new TH1F(name.Data(),name.Data(), 400, 0.0, TMath::Pi());

    name = "Ana_AllHad_2b_Thrust_LabFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_TopMass_TopPThrust_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_LabFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_TopMass_TopPThrust_2D[i] = new TH2F(name.Data(),name.Data(), 40, -700.0, 600.0, 100, 0.0, 1000.);
    name = "Ana_AllHad_2b_Thrust_LabFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_WMass_TopPThrust_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_LabFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_WMass_TopPThrust_2D[i] = new TH2F(name.Data(),name.Data(), 40, -700.0, 600.0, 100, 0.0, 1000.);
    name = "Ana_AllHad_2b_Thrust_LabFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_TopMass_TopPThrust_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_LabFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_TopMass_TopPThrust_2D[i] = new TH2F(name.Data(),name.Data(), 40, -700.0, 600.0, 100, 0.0, 1000.);
    name = "Ana_AllHad_2b_Thrust_LabFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_WMass_TopPThrust_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_LabFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_WMass_TopPThrust_2D[i] = new TH2F(name.Data(),name.Data(), 40, -700.0, 600.0, 100, 0.0, 1000.);
    name = "Ana_AllHad_2b_Thrust_LabFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_TopMass1_TopMass2_2D_"+istr+"cut";
    Ana_AllHad_2b_Thrust_LabFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_TopMass1_TopMass2_2D[i] = new TH2F(name.Data(),name.Data(), 100, 0.0, 1000.0, 100, 0.0, 1000.);
    name = "Ana_AllHad_2b_Thrust_LabFrame2_FoundBoth_B_NegCone_W_minWDeltaM_TTMass_"+istr+"cut";
    Ana_AllHad_2b_Thrust_LabFrame2_FoundBoth_B_NegCone_W_minWDeltaM_TTMass[i] = new TH1F(name.Data(),name.Data(), 500, 0.0, 1200.);

    //---------------------------------------------------//

    wk()->addOutput(Ana_AllHad_2b_Thrust_LabFrame2_NegCone_W_minWDeltaM_NMissing[i]);

    wk()->addOutput(Ana_AllHad_2b_Thrust_LabFrame2_MissingBothW_B_NegCone_W_minWDeltaM_WMet_DPhi_WMet_DEt_2D[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_LabFrame2_MissingBothW_B_NegCone_W_minWDeltaM_WMet_DPhi[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_LabFrame2_MissingBothW_B_NegCone_W_minWDeltaM_WMet_DPt[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_LabFrame2_MissingBothW_B_NegCone_W_minWDeltaM_WMet_PThrust[i]);

    wk()->addOutput(Ana_AllHad_2b_Thrust_TopFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_BMom_TopMass_2D[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TopFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMom_TopMass_2D[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TopFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_BWAngle_TopMass_2D[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TopFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_BMom[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TopFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMom[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TopFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_BWAngle[i]);

    wk()->addOutput(Ana_AllHad_2b_Thrust_TTFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_TBoost_TopMass_2D[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TTFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_ThrustAngle_TopMass_2D[i]);

    wk()->addOutput(Ana_AllHad_2b_Thrust_TTFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_TBoost[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TTFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_ThrustAngle[i]);

    wk()->addOutput(Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_TopMass_TopPThrust_2D[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMass_TopPThrust_2D[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_B_NegCone_W_minWDeltaM_TTMass[i]);

    wk()->addOutput(Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMet_DPhi_WMet_DEt_2D[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMet_DPhi[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMet_DPt[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMet_PThrust[i]);

    wk()->addOutput(Ana_AllHad_2b_Thrust_TopFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_BMom_TopMass_2D[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TopFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMom_TopMass_2D[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TopFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_BWAngle_TopMass_2D[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TopFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_BMom[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TopFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMom[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TopFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_BWAngle[i]);

    wk()->addOutput(Ana_AllHad_2b_Thrust_TTFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_TBoost_TopMass_2D[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TTFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_ThrustAngle_TopMass_2D[i]);

    wk()->addOutput(Ana_AllHad_2b_Thrust_TTFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_TBoost[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TTFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_ThrustAngle[i]);

    wk()->addOutput(Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_TopMass_TopPThrust_2D[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMass_TopPThrust_2D[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_B_NegCone_W_minWDeltaM_TTMass[i]);

    wk()->addOutput(Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMet_DPhi_WMet_DEt_2D[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMet_DPhi[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMet_DPt[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMet_PThrust[i]);

    wk()->addOutput(Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_BMom_TopMass_2D[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_WMom_TopMass_2D[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_BWAngle_TopMass_2D[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_BMom_TopMass_2D[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_WMom_TopMass_2D[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_BWAngle_TopMass_2D[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_BMom[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_WMom[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_BWAngle[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_BMom[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_WMom[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_BWAngle[i]);

    wk()->addOutput(Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_TBoost_TopMass_2D[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_ThrustAngle_TopMass_2D[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_TBoost_TopMass_2D[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_ThrustAngle_TopMass_2D[i]);

    wk()->addOutput(Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_TBoost[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_ThrustAngle[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_TBoost[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_ThrustAngle[i]);

    wk()->addOutput(Ana_AllHad_2b_Thrust_LabFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_TopMass_TopPThrust_2D[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_LabFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_WMass_TopPThrust_2D[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_LabFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_TopMass_TopPThrust_2D[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_LabFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_WMass_TopPThrust_2D[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_LabFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_TopMass1_TopMass2_2D[i]);
    wk()->addOutput(Ana_AllHad_2b_Thrust_LabFrame2_FoundBoth_B_NegCone_W_minWDeltaM_TTMass[i]);


    if (verbose) std::cout <<"finished making histograms" << std::endl;
   
  }

  name = "h_TrueBoostDeltaMinP_MagVsAng";
  h_TrueBoostDeltaMinP_MagVsAng = new TH2F(name.Data(),name.Data(), 100, -1.0, 1.0, 100, 0.0, TMath::Pi());
  name = "h_TrueBoostDeltaMinPAng";
  h_TrueBoostDeltaMinPAng = new TH1F(name.Data(),name.Data(), 200, 0.0, TMath::Pi());
  name = "h_TrueBoostDeltaMinPMag";
  h_TrueBoostDeltaMinPMag = new TH1F(name.Data(),name.Data(), 200, -1.0, 1.00);
  name = "h_TrueBoostDeltaMaxP_MagVsAng";
  h_TrueBoostDeltaMaxP_MagVsAng = new TH2F(name.Data(),name.Data(), 100, -1.0, 1.0, 100, 0.0, TMath::Pi());
  name = "h_TrueBoostDeltaMaxPAng";
  h_TrueBoostDeltaMaxPAng = new TH1F(name.Data(),name.Data(), 200, 0.0, TMath::Pi());
  name = "h_TrueBoostDeltaMaxPMag";
  h_TrueBoostDeltaMaxPMag = new TH1F(name.Data(),name.Data(), 200, -1.0, 1.00);

  name = "h_TrueTMinP_BW_DeltaAng";
  h_TrueTMinP_BW_DeltaAng = new TH1F(name.Data(),name.Data(), 200, 0.0, TMath::Pi());
  name = "h_TrueTMaxP_BW_DeltaAng";
  h_TrueTMaxP_BW_DeltaAng = new TH1F(name.Data(),name.Data(), 200, 0.0, TMath::Pi());
  name = "h_TrueTMinP_BW_LostOtherW_DeltaAng";
  h_TrueTMinP_BW_LostOtherW_DeltaAng = new TH1F(name.Data(),name.Data(), 200, 0.0, TMath::Pi());
  name = "h_TrueTMaxP_BW_LostOtherW_DeltaAng";
  h_TrueTMaxP_BW_LostOtherW_DeltaAng = new TH1F(name.Data(),name.Data(), 200, 0.0, TMath::Pi());

  name = "h_TrueTMinP_BW_DeltaPhi";
  h_TrueTMinP_BW_DeltaPhi = new TH1F(name.Data(),name.Data(), 200, 0.0, TMath::Pi());
  name = "h_TrueTMaxP_BW_DeltaPhi";
  h_TrueTMaxP_BW_DeltaPhi = new TH1F(name.Data(),name.Data(), 200, 0.0, TMath::Pi());
  name = "h_TrueTMinP_BW_LostOtherW_DeltaPhi";
  h_TrueTMinP_BW_LostOtherW_DeltaPhi = new TH1F(name.Data(),name.Data(), 200, 0.0, TMath::Pi());
  name = "h_TrueTMaxP_BW_LostOtherW_DeltaPhi";
  h_TrueTMaxP_BW_LostOtherW_DeltaPhi = new TH1F(name.Data(),name.Data(), 200, 0.0, TMath::Pi());

  name = "h_TrueTMinP_BW_DeltaEta";
  h_TrueTMinP_BW_DeltaEta = new TH1F(name.Data(),name.Data(), 200, -3.0,3.0);
  name = "h_TrueTMaxP_BW_DeltaEta";
  h_TrueTMaxP_BW_DeltaEta = new TH1F(name.Data(),name.Data(), 200, -3.0,3.0);
  name = "h_TrueTMinP_BW_LostOtherW_DeltaEta";
  h_TrueTMinP_BW_LostOtherW_DeltaEta = new TH1F(name.Data(),name.Data(), 200, -3.0,3.0);
  name = "h_TrueTMaxP_BW_LostOtherW_DeltaEta";
  h_TrueTMaxP_BW_LostOtherW_DeltaEta = new TH1F(name.Data(),name.Data(), 200, -3.0,3.0);

  name = "h_TrueTMinP_BW_DeltaTheta";
  h_TrueTMinP_BW_DeltaTheta = new TH1F(name.Data(),name.Data(), 200, -TMath::Pi(), TMath::Pi());
  name = "h_TrueTMaxP_BW_DeltaTheta";
  h_TrueTMaxP_BW_DeltaTheta = new TH1F(name.Data(),name.Data(), 200, -TMath::Pi(), TMath::Pi());
  name = "h_TrueTMinP_BW_LostOtherW_DeltaTheta";
  h_TrueTMinP_BW_LostOtherW_DeltaTheta = new TH1F(name.Data(),name.Data(), 200, -TMath::Pi(), TMath::Pi());
  name = "h_TrueTMaxP_BW_LostOtherW_DeltaTheta";
  h_TrueTMaxP_BW_LostOtherW_DeltaTheta = new TH1F(name.Data(),name.Data(), 200, -TMath::Pi(), TMath::Pi());

  name = "h_True_TTMass";
  h_True_TTMass = new TH1F(name.Data(),name.Data(), 300, 0.0, 1500.);

  wk()->addOutput(h_TrueBoostDeltaMinP_MagVsAng);
  wk()->addOutput(h_TrueBoostDeltaMinPAng);
  wk()->addOutput(h_TrueBoostDeltaMinPMag);
  wk()->addOutput(h_TrueBoostDeltaMaxP_MagVsAng);
  wk()->addOutput(h_TrueBoostDeltaMaxPAng);
  wk()->addOutput(h_TrueBoostDeltaMaxPMag);

  wk()->addOutput(h_TrueTMinP_BW_DeltaAng);
  wk()->addOutput(h_TrueTMaxP_BW_DeltaAng);
  wk()->addOutput(h_TrueTMinP_BW_LostOtherW_DeltaAng);
  wk()->addOutput(h_TrueTMaxP_BW_LostOtherW_DeltaAng);

  wk()->addOutput(h_TrueTMinP_BW_DeltaPhi);
  wk()->addOutput(h_TrueTMaxP_BW_DeltaPhi);
  wk()->addOutput(h_TrueTMinP_BW_LostOtherW_DeltaPhi);
  wk()->addOutput(h_TrueTMaxP_BW_LostOtherW_DeltaPhi);

  wk()->addOutput(h_TrueTMinP_BW_DeltaEta);
  wk()->addOutput(h_TrueTMaxP_BW_DeltaEta);
  wk()->addOutput(h_TrueTMinP_BW_LostOtherW_DeltaEta);
  wk()->addOutput(h_TrueTMaxP_BW_LostOtherW_DeltaEta);

  wk()->addOutput(h_TrueTMinP_BW_DeltaTheta);
  wk()->addOutput(h_TrueTMaxP_BW_DeltaTheta);
  wk()->addOutput(h_TrueTMinP_BW_LostOtherW_DeltaTheta);
  wk()->addOutput(h_TrueTMaxP_BW_LostOtherW_DeltaTheta);

  wk()->addOutput(h_True_TTMass);

  name = "h_true_TMass_MinP";
  h_true_TMass_MinP= new TH1F(name.Data(),name.Data(), 300, 140.0, 210.);
  name = "h_true_TMass_MaxP";
  h_true_TMass_MaxP= new TH1F(name.Data(),name.Data(), 300, 140.0, 210.);
  name = "h_true_WMass_MinP";
  h_true_WMass_MinP= new TH1F(name.Data(),name.Data(), 300, 40.0, 120.);
  name = "h_true_WMass_MaxP";
  h_true_WMass_MaxP= new TH1F(name.Data(),name.Data(), 300, 40.0, 120.);
  name = "h_true_BWjetMass";
  h_true_BWjetMass = new TH1F(name.Data(),name.Data(), 300, 0.0, 200.);

  wk()->addOutput(h_true_TMass_MinP);
  wk()->addOutput(h_true_TMass_MaxP);
  wk()->addOutput(h_true_WMass_MinP);
  wk()->addOutput(h_true_WMass_MaxP);
  wk()->addOutput(h_true_BWjetMass);

  name = "h_true_nWjetsLost";
  h_true_nWjetsLost = new TH1F(name.Data(),name.Data(), 5, -0.5, 4.5);
  wk()->addOutput(h_true_nWjetsLost);

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthxAODAnalysis_STop :: fileExecute ()
{
  // Here you do everything that needs to be done exactly once for every
  // single file, e.g. collect a list of all lumi-blocks processed
  return EL::StatusCode::SUCCESS;
}



/*EL::StatusCode TruthxAODAnalysis_STop :: changeInput (bool firstFile)
{
  // Here you do everything you need to do when we change input files,
  // e.g. resetting branch addresses on trees.  If you are using
  // D3PDReader or a similar service this method is not needed.
  return EL::StatusCode::SUCCESS;
  }*/



EL::StatusCode TruthxAODAnalysis_STop :: initialize ()
{
  // Here you do everything that you need to do after the first input
  // file has been connected and before the first event is processed,
  // e.g. create additional histograms based on which variables are
  // available in the input files.  You can also create all of your
  // histograms and trees in here, but be aware that this method
  // doesn't get called if no events are processed.  So any objects
  // you create here won't be available in the output if you have no
  // input events.
  xAOD::TEvent* event = wk()->xaodEvent();

  evt_display_name = "event_display.eps";

  ps = new TPostScript(evt_display_name.c_str(), 112);

  Info("initialize()", "Number of events = %lli", event->getEntries() ); // print long long int

  rand = TRandom3( 234234);

  //  if (verbose) std::cout << "in Initialize, about to initialise variables" << std::endl;
  m_eventCounter = 0;

  count = 0;

  thrust_vec = TLorentzVector(0.,0.,0.,0.);
  thrust_perp_vec = TLorentzVector(0.,0.,0.,0.);
  
  stop1 = TLorentzVector(0.,0.,0.,0.);
  stop1_b = TLorentzVector(0.,0.,0.,0.);
  stop1_wj1 = TLorentzVector(0.,0.,0.,0.);
  stop1_wj2 = TLorentzVector(0.,0.,0.,0.);
  stop1_xi =  TLorentzVector(0.,0.,0.,0.);

  stop2 = TLorentzVector(0.,0.,0.,0.);
  stop2_b = TLorentzVector(0.,0.,0.,0.);
  stop2_wj1 = TLorentzVector(0.,0.,0.,0.);
  stop2_wj2 = TLorentzVector(0.,0.,0.,0.);
  stop2_xi = TLorentzVector(0.,0.,0.,0.);

  ISR_total = TLorentzVector(0.,0.,0.,0.);
  verbose = false;

  w_polemass = 80.35;
  b_polemass = 4.65;
  t_polemass = 173.34;

  t_reduced_mass= t_polemass*t_polemass- w_polemass*w_polemass- b_polemass*b_polemass;

  expected_b_momentum = sqrt( t_reduced_mass *t_reduced_mass / 4. / t_polemass / t_polemass -
                              b_polemass*b_polemass*w_polemass*w_polemass/t_polemass/t_polemass );

  GeV = 1000.;

  polreweight = new StopPolarization::PolarizationReweight;

  polreweight->setUnitMeV(); // set unit as MeV                                                                 
  // polreweight->setUnitGeV(); // set unit as GeV                                                              

  // set W, Z mass, width                                                                                       
  polreweight->setMassW(80399.);
  polreweight->setWidthW(2085.);
  polreweight->setMassZ(91187.6);
  polreweight->setWidthZ(2495.2);
  polreweight->setMassTop(172500.);
  polreweight->setWidthTop(1333.13);

  // set mass threshold if it is applied at generator level                                                     
  polreweight->setMassWThreshold(0.);
  polreweight->setMassZThreshold(0.);
  polreweight->setMassTopThreshold(54000.);

  std::string generatorName = "MadGraphPythia8";
  polreweight->setGeneratorName(generatorName);

  // set true if decay of susy particles is done in Pythia(8)                                                   
  polreweight->setDecayPythia(true);

  // set true if 3-body decay is done with phase space calculation only                                         
  polreweight->setPhaseSpaceOnly(true);

  //  if (verbose) std::cout << "Finished intializing variables " << std::endl;
  return EL::StatusCode::SUCCESS;
}

void TruthxAODAnalysis_STop::setEvtDisplay(std::string eps) {
  evt_display_name = eps;
  return;
}

void TruthxAODAnalysis_STop::DrawEvtDisplay(){

  std::cout << "drawing display" << std::endl;

  TCanvas *c2 = new TCanvas("c2");
  c2->Range(0,0,1,1);

  TArrow *metArrow = new TArrow();
  TArrow *arrow = new TArrow();

  TLatex p;
  p.SetTextSize(0.05);
  p.SetTextFont(42);

  metArrow->SetLineColor(kBlack);

  std::vector<float> jetpt_vec;
  jetpt_vec.resize(0);
  jetpt_vec.push_back(stop1_b.Pt());
  jetpt_vec.push_back(stop1_wj1.Pt());
  jetpt_vec.push_back(stop1_wj2.Pt());
  jetpt_vec.push_back(stop2_b.Pt());
  jetpt_vec.push_back(stop2_wj1.Pt());
  jetpt_vec.push_back(stop2_wj2.Pt());
  jetpt_vec.push_back(dixi.Pt());
  for (int i=0;i<nISR;i++){
    jetpt_vec.push_back(ISR_p[i][3]);
  }
  std::sort (jetpt_vec.begin(), jetpt_vec.end());
  double maximum = 2.2*jetpt_vec.back();

  double length  = dixi.Pt()/maximum;
  metArrow->DrawArrow(0.5, 0.5, 0.5-length*cos(dixi.Phi()), 0.5+length*sin(dixi.Phi()),0.01,"|>");

  length = stop1_b.Pt()/maximum;
  double phi = stop1_b.Phi();
  arrow->SetLineColor(kBlue);
  arrow->DrawArrow(0.5, 0.5, 0.5-length*cos(phi), 0.5+length*sin(phi),0.01,"|>");
  p.DrawLatex(0.1,0.6,Form("#color[4]{bjet pt = %3.2f}",stop1_b.Pt()));

  length = stop2_b.Pt()/maximum;
  phi =stop2_b.Phi();
  arrow->SetLineColor(kBlue);
  arrow->DrawArrow(0.5, 0.5, 0.5-length*cos(phi), 0.5+length*sin(phi),0.01,"|>");
  p.DrawLatex(0.1,0.5,Form("#color[4]{bjet pt = %3.2f}",stop2_b.Pt()));

  length = stop1_wj1.Pt()/maximum;
  phi =stop1_wj1.Phi();
  arrow->SetLineColor(kOrange);
  arrow->DrawArrow(0.5, 0.5, 0.5-length*cos(phi), 0.5+length*sin(phi),0.01,"|>");
  length = stop1_wj2.Pt()/maximum;
  phi =stop1_wj2.Phi();
  arrow->SetLineColor(kOrange);
  arrow->DrawArrow(0.5, 0.5, 0.5-length*cos(phi), 0.5+length*sin(phi),0.01,"|>");

  length = stop2_wj1.Pt()/maximum;
  phi =stop2_wj1.Phi();
  arrow->SetLineColor(kOrange);
  arrow->DrawArrow(0.5, 0.5, 0.5-length*cos(phi), 0.5+length*sin(phi),0.01,"|>");
  length = stop2_wj2.Pt()/maximum;
  phi =stop2_wj2.Phi();
  arrow->SetLineColor(kOrange);
  arrow->DrawArrow(0.5, 0.5, 0.5-length*cos(phi), 0.5+length*sin(phi),0.01,"|>");

  double place = 0.4;
  for (int i=0; i<nISR; i ++){
    arrow->SetLineColor(kRed);
    arrow->DrawArrow(0.5, 0.5, 0.5-ISR_p[i][0]/maximum, 0.5+ISR_p[i][1]/maximum,0.01,"|>");
    p.DrawLatex(0.1,place,Form("#color[2]{ISR jet pt = %3.2f}",ISR_p[i][3]));
    place -= 0.1;
  }

  p.DrawLatex(0.1,0.8,Form("#color[1]{MET     = %3.2f}",dixi.Pt()) );
  p.DrawLatex(0.1,0.7,Form("#color[2]{ISR pt  = %3.2f}",ISR_total.Pt()) );

  c2->Update();  ps->NewPage();

  delete c2;
  delete arrow;
  delete metArrow;
}

EL::StatusCode TruthxAODAnalysis_STop :: execute ()
{
  if ( verbose ) std::cout << std::endl;

  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.

  xAOD::TEvent* event = wk()->xaodEvent();

  // print every 100 events, so we know where we are:
  if( (m_eventCounter % 100) ==0 ) Info("execute()", "Event number = %i", m_eventCounter );
  m_eventCounter++;

  //----------------------------
  // Event information
  //--------------------------- 
  const xAOD::EventInfo* eventInfo = 0;
  EL_RETURN_CHECK("execute",event->retrieve( eventInfo, "EventInfo"));  
  
  // check if the event is data or MC
  // (many tools are applied either to data or MC)
  // check if the event is MC
  if(eventInfo->eventType( xAOD::EventInfo::IS_SIMULATION ) ){
    isMC = true; // can do something with this later
  }   

  //--------------------------------------------------------//
  //     Look in the event's truth container                //
  //--------------------------------------------------------//

  //  Full Truth information is not available.
  //  Check here for basic information
  //
  //  https://indico.cern.ch/event/307549/session/7/contribution/31/material/slides/0.pdf

  //-------------------------------------------------------//

  //  Load the list of truth particles in the event
  //  Note not all particles in the truth has been saved:  Only the main decay tree have been saved
  //  If your code dies because you can't find a particle->barcode() for example
  //  it might mean that you are trying to access a particle that was not saved.
  
  const xAOD::TruthParticleContainer* TruthParticleCont = 0;
  EL_RETURN_CHECK("execute()",event->retrieve(TruthParticleCont, "TruthParticles"));

  double reweight1 = polreweight->getReweightTopNeutralino(TruthParticleCont, 1.40639, TMath::Pi()/4.);
  //  double reweight1 = 1.0;

  if ( verbose ) std::cout << "weight " << reweight1 << std::endl;

  //--------------------------------------------------------------//
  //             Loop over all saved truth particles              //
  //--------------------------------------------------------------//

  xAOD::TruthParticleContainer::const_iterator ipart_itr = TruthParticleCont->begin();
  xAOD::TruthParticleContainer::const_iterator ipart_end = TruthParticleCont->end();


  //  if (verbose) std::cout << "in execute, about to set lorent vectors to 0 " << std::endl;
  stop1.SetPxPyPzE(0.,0.,0.,0.);
  stop1_b.SetPxPyPzE(0.,0.,0.,0.);
  stop1_wj1.SetPxPyPzE(0.,0.,0.,0.);
  stop1_wj2.SetPxPyPzE(0.,0.,0.,0.);
  stop1_xi.SetPxPyPzE(0.,0.,0.,0.);

  stop2.SetPxPyPzE(0.,0.,0.,0.);
  stop2_b.SetPxPyPzE(0.,0.,0.,0.);
  stop2_wj1.SetPxPyPzE(0.,0.,0.,0.);
  stop2_wj2.SetPxPyPzE(0.,0.,0.,0.);
  stop2_xi.SetPxPyPzE(0.,0.,0.,0.);
  dixi.SetPxPyPzE(0.,0.,0.,0.);

  nISR = 0;
  ISR_p.resize(0);

  thrust_vec.SetXYZT(0,0,0,0);
  thrust_perp_vec.SetXYZT(0,0,0,0);

  isStop1Had = false;
  isStop2Had = false;
  plotEvent = false;

  //--------------------------------------------------------//
  //           Start to loop over truth here                //
  //--------------------------------------------------------//

  for( ; ipart_itr != ipart_end; ++ipart_itr ) {

    if (verbose) std::cout << "inside particle loop" << std::endl;
    //    Get the particle from the particle container
    const xAOD::TruthParticle* particle = (*ipart_itr);

    //--------------------------------------------------------------------------------------------//
    //  access all the information from the particle
    //  what information can be accessed is documented here
    //  http://hep.uchicago.edu/~kkrizka/rootcoreapis/dd/dc2/classxAOD_1_1TruthParticle__v1.html
    //--------------------------------------------------------------------------------------------//

    //--------------------------------------------------------------------------------------------//
    // This is the unique barcode of the particle.
    // if two particles have with the same barcode then they
    // are the same particle with same pt, pz, m, etc...
    //int barcode = particle->barcode(); 
    //  The PDG "ID" is the physical type of particle
    //  an id of 6 is a top quark, -6 is a anti-top
    //  an id of 11 is an electron, -11 is an positron
    //  a table of pdg ID can be found here
    //  http://pdg.lbl.gov/2005/reviews/montecarlorpp.pdf
    //--------------------------------------------------------------------------------------------//

    int pdgId = particle->pdgId();

    //--------------------------------------------------------------------------------------------//
    //  status of the particle is the stage of the particle in the decay chain
    //  Unfortunately depending on the MC generator, different status code means different things
    //  http://lcgapp.cern.ch/project/simu/HepMC/205/status.html
    //  https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookGenParticleCandidate
    //  a status code of 1 is a final state particle.  It will not decay anymore
    //  a status code of 2 is an intermediate particle. It will decay further
    //  a status code of 3 identifies the "hard part" of the interaction, 
    //  i.e. the partons that are used in the matrix element calculation, including immediate decays of resonances.
    //  Sometimes a mid decay particle is more interesting than a final state particle.
    //  For quarks/gluon, you are not interested in all the final quarks.  You want the initial
    //  quark/gluon with status code 2 that makes all the other quark/gluons in the chain
    //  The original unstable quark/gluon will have the energy of the full jet
    //  ignore particles with all other status codes 
    //  they dont mean anything they are internal book-keeping for 
    //  the MC generation to balance out 4 momenta.  They aren't "real" or part of the simulation
    //--------------------------------------------------------------------------------------------//

    int status = particle->status();

    //--------------------------------------------------------------------------------------------//    
    //  Four momentum values of the particle
    //  Everthing is in MeV so you'll have to convert to GeV manually
    //--------------------------------------------------------------------------------------------//

    //    float px = particle->px();
    //    float py = particle->py();
    //    float pz = particle->pz();
    //    float pt = particle->pt();

    //--------------------------------------------------------------------------------------------//
    //         Charge of the particle
    //--------------------------------------------------------------------------------------------//

    //    float e = particle->e();

    //--------------------------------------------------------------------------------------------//
    //          Mass of the particle
    //--------------------------------------------------------------------------------------------//

    //    float m = particle->m();

    //  if debugging output every particle
    // if ( verbose ) std::if (verbose) std::cout << "pdgId " << pdgId << " status " << status << " pt " << pt << " pz " << pz << std::std::endl;

    //---------------------------------------------------------//
    //           Look for all the s-top/anti stops             //
    //---------------------------------------------------------//

    //  for s-top decay, the pdgId == 100006 is the stop.  
    //  In MC, stops and any paricle can be passed along a chain to tweak its momentum slightly
    //  So the decay chain can be stop -> stop -> stop -> top+neutralino
    //  each stop in the chain will have a different status
    //  the initial pp -> stop stop + ISR is status code 22
    //  the final stop -> b W + neutralino is at status code 62

    //std::vector <std::vector<float>> ISR_p;
    if (verbose) std::cout << "The id of this particle is " << pdgId << std::endl;
    if (verbose) std::cout << "The status of this particle is " << status << std::endl;

    //-------------------------------------------------------//
    //    Find the initial pp -> stop + stop + ISR decay     //
    //-------------------------------------------------------//

    //  The first stop has status 22

    if ((pdgId == 1000006) && status == 22) {

      //---------------------------------------------------------//
      //      Look at pp -> Stop+AntiStop+ISR Decay Vertex       //
      //---------------------------------------------------------//

      bool hasProdVtx = particle->hasProdVtx();
      if (hasProdVtx){

	const xAOD::TruthVertex* prodVtx = particle->prodVtx();
	int npart = prodVtx->nOutgoingParticles();

	if (verbose) std::cout << "npart for prodvtx is  " << npart << std::endl;

	//---------------------------------------------------------------------//
	//     Loop over all products of the pp -> Stop + Stop + ISR Vertex    //
	//---------------------------------------------------------------------//

	for (int j=0; j<npart; j++){
	  const xAOD::TruthParticle* particle = prodVtx->outgoingParticle(j);
	  pdgId = particle->pdgId();
	  status = particle->status();

	  //-------------------------------------------//
	  //      Find Decay Products of STop          //
	  //-------------------------------------------//
	  if (pdgId ==  1000006) {
	    if (verbose) std::cout << "inside stop1 production vertex loop..... " << std::endl;
	    if (verbose) std::cout << "The id of particle " << j << " of stop1 prodvtx is " << pdgId << std::endl;
	    if (verbose) std::cout << "The status of particle "<< j << " of stop1 prodvtx " << status << std::endl;
	    isStop1Had = Find_STopDecayProducts( particle, &stop1_t, &stop1_xi, &stop1_b, &stop1_wj1, &stop1_wj2 );
	  }
          //-------------------------------------------//
          //      Find Decay Products of AntiSTop      //
          //-------------------------------------------//
	  else if (pdgId == -1000006){
	    if (verbose) std::cout << "inside stop1 production vertex loop..... " << std::endl;
	    if (verbose) std::cout << "The id of particle " << j << " of stop2 prodvtx is " << pdgId << std::endl;
	    if (verbose) std::cout << "The status of particle "<< j << " of stop2 prodvtx " << status << std::endl;
            isStop2Had = Find_STopDecayProducts( particle, &stop2_t, &stop2_xi, &stop2_b, &stop2_wj1, &stop2_wj2 );
	  }
          //-------------------------------------------//
          //      Find Decay Products of ISR           //
          //-------------------------------------------//
	  else{

	    nISR++;

	    float temp_px=0.;
	    float temp_py=0.;
	    float temp_pz=0.;
	    float temp_pt=0.;
	    float temp_e=0.;
	    std::vector<float> p;
	    p.resize(0);

	    temp_px = particle->px()/GeV;
	    temp_py = particle->py()/GeV;
	    temp_pz = particle->pz()/GeV;
	    temp_pt = particle->pt()/GeV;
	    temp_e = particle->e()/GeV;

	    p.push_back(temp_px);
	    p.push_back(temp_py);
	    p.push_back(temp_pz);
	    p.push_back(temp_pt);
	    p.push_back(temp_e);
	    ISR_p.push_back(p);

	    if ( verbose ) std::cout << "ISR E " << temp_e << "ISR pt " << sqrt(temp_px*temp_px + temp_py*temp_py) << std::endl;

	  }
	}
      }

      //------------------------------------------------------//
      //      break out of the loop if we found the stop      //
      //------------------------------------------------------//

      break;

    }

    if (verbose) std::cout << "Outside antistop loop" << std::endl;

    //Currently, only draw histograms if both W decays are hadronic

  } // finished loop over all truth particles

  //-------------------------------------------------//
  //           if not all hadronic give up           //
  //-------------------------------------------------//

  //  if (!isStop1Had || !isStop2Had) { return EL::StatusCode::SUCCESS; }

  //-------------------------------------------------//
  //             Find Direction of Thrust            //
  //-------------------------------------------------//

  ditop = stop1_t + stop2_t;

  float temp_px = 0.;
  float temp_py = 0.;
  float temp_pz = 0.;
  float temp_pt = 0.;
  float temp_e = 0.;
  for (int i=0; i<nISR; i ++){
    temp_px += ISR_p[i][0];
    temp_py += ISR_p[i][1];
    temp_pz += ISR_p[i][2];
    temp_pt += ISR_p[i][3];
    temp_e += ISR_p[i][4];
  }
  ISR_total.SetPxPyPzE(temp_px,temp_py,temp_pz,temp_e);

  TLorentzVector total = ditop+ISR_total;

  dixi = stop1_xi + stop2_xi;

  //  if ( dixi.Pt() < 250. ) { return EL::StatusCode::SUCCESS; }

  if ( verbose ) std::cout << "di top P " << ditop.P() << " M " << ditop.M() << std::endl;
  if ( verbose ) std::cout << " +ISR P " <<  total.P() << " M " << total.M() << std::endl;

  if (!isStop1Had || !isStop2Had) { return EL::StatusCode::SUCCESS; }     

  FindThrustDir();

  //------------------------------------------------------------//
  //         Order STops by B Quark P Along Thrust              //
  //------------------------------------------------------------//

  double b1_pthrust = CalculatePAlongThrust( &stop1_b );
  double b2_pthrust = CalculatePAlongThrust( &stop2_b );
  
  if ( b1_pthrust < b2_pthrust ) {
    stopb_tmp   = stop1_b;
    stopwj1_tmp = stop1_wj1;
    stopwj2_tmp = stop1_wj2;
    stopxi_tmp  = stop1_xi;
    stop1_b   = stop2_b;
    stop1_wj1 = stop2_wj1;
    stop1_wj2 = stop2_wj2;
    stop1_xi  = stop2_xi;
    stop2_b   = stopb_tmp;
    stop2_wj1 = stopwj1_tmp;
    stop2_wj2 = stopwj2_tmp;
    stop2_xi  = stopxi_tmp;
  }

  /*
  double randomN = rand.Gaus(1.0,0.005);
  stop1_b.SetPxPyPzE(stop1_b.Px()*randomN, stop1_b.Py()*randomN,
		     stop1_b.Pz()*randomN, stop1_b.E()*randomN);
  randomN = rand.Gaus(1.0,0.005);
  stop1_wj1.SetPxPyPzE(stop1_wj1.Px()*randomN, stop1_wj1.Py()*randomN,
		       stop1_wj1.Pz()*randomN, stop1_wj1.E()*randomN);
  randomN = rand.Gaus(1.0,0.005);
  stop1_wj2.SetPxPyPzE(stop1_wj2.Px()*randomN, stop1_wj2.Py()*randomN,
		       stop1_wj2.Pz()*randomN, stop1_wj2.E()*randomN);
  randomN = rand.Gaus(1.0,0.005);
  stop2_b.SetPxPyPzE(stop2_b.Px()*randomN, stop2_b.Py()*randomN,
                     stop2_b.Pz()*randomN, stop2_b.E()*randomN);
  randomN = rand.Gaus(1.0,0.005);
  stop2_wj1.SetPxPyPzE(stop2_wj1.Px()*randomN, stop2_wj1.Py()*randomN,
		       stop2_wj1.Pz()*randomN, stop2_wj1.E()*randomN);
  randomN = rand.Gaus(1.0,0.005);
  stop2_wj2.SetPxPyPzE(stop2_wj2.Px()*randomN, stop2_wj2.Py()*randomN,
		       stop2_wj2.Pz()*randomN, stop2_wj2.E()*randomN);
  */

  //-----------------------------------------------------//
  //           Construct Combined Objects                //
  //-----------------------------------------------------//

  stop1 = stop1_b + stop1_wj1 + stop1_wj2 + stop1_xi;
  stop2 = stop2_b + stop2_wj1 + stop2_wj2 + stop2_xi;

  distop = stop1 + stop2;
  dixi = stop1_xi + stop2_xi;
  stop1_jets = stop1_b + stop1_wj1 + stop1_wj2;
  stop2_jets = stop2_b + stop2_wj1 + stop2_wj2;
  stop1_w = stop1_wj1 + stop1_wj2;
  stop2_w = stop2_wj1 + stop2_wj2;
  
  AllJets_Vec.resize(0);
  AllJets_Lost.resize(0);
  AllJets_Vec.push_back(stop1_b);
  AllJets_Vec.push_back(stop2_b);
  AllJets_Lost.push_back(0);
  AllJets_Lost.push_back(0);

  int n_jets_lost = 0;

  if ((stop1_wj1+AllJets_Vec.at(0)).M() > 170. &&
      (stop1_wj1+AllJets_Vec.at(1)).M() > 170.) {
    n_jets_lost++;
    AllJets_Lost.push_back(1);
  }
  else {
    AllJets_Lost.push_back(0);
  }
  if ((stop1_wj2+AllJets_Vec.at(0)).M() > 170. &&
      (stop1_wj2+AllJets_Vec.at(1)).M() > 170.) {
    n_jets_lost++;
    AllJets_Lost.push_back(1);
  }
  else {
    AllJets_Lost.push_back(0);
  }
  if ((stop2_wj1+AllJets_Vec.at(0)).M() > 170. &&
      (stop2_wj1+AllJets_Vec.at(1)).M() > 170.) {
    n_jets_lost++;
    AllJets_Lost.push_back(1);
  }
  else {
    AllJets_Lost.push_back(0);
  }
  if ((stop2_wj2+AllJets_Vec.at(0)).M() > 170. &&
      (stop2_wj2+AllJets_Vec.at(1)).M() > 170.) {
    n_jets_lost++;
    AllJets_Lost.push_back(1);
  }
  else {
    AllJets_Lost.push_back(0);
  }

  AllJets_Vec.push_back(stop1_wj1);
  AllJets_Vec.push_back(stop1_wj2);
  AllJets_Vec.push_back(stop2_wj1);
  AllJets_Vec.push_back(stop2_wj2);

  TLorentzVector temp;
  for (int i=0; i<nISR; i ++){
    temp.SetPxPyPzE(ISR_p[i][0],ISR_p[i][1],ISR_p[i][2],ISR_p[i][4]);

    if ((temp+AllJets_Vec.at(0)).M() > 170. &&
	(temp+AllJets_Vec.at(1)).M() > 170.) continue;
    AllJets_Vec.push_back(temp);
    AllJets_Lost.push_back(0);
  }

  //-------------------------------------------------------//
  //              Smear these jets                         //
  //-------------------------------------------------------//
 
  /*
  //  Apply a 15% uncertainty to all jet energies
  for ( int i=0; i<AllJets_Vec.size(); i++ ) {

    double randomN = rand.Gaus(1.0,0.15);
    double Px = AllJets_Vec.at(i).Px() * randomN;
    double Py = AllJets_Vec.at(i).Py() * randomN;
    double Pz = AllJets_Vec.at(i).Pz() * randomN;
    double E  = AllJets_Vec.at(i).E()  * randomN;

    AllJets_Vec.at(i).SetPxPyPzE(Px,Py,Pz,E);

    if ( AllJets_Lost.at(i) == 1 ) continue;

    if ( AllJets_Vec.at(i).Pt() < 20. ) {
      if ( i == 0 || i == 1 )   return EL::StatusCode::SUCCESS;
      n_jets_lost++;
      AllJets_Lost.at(i) = 1;
    }

  }
  */

  h_true_nWjetsLost->Fill(n_jets_lost, reweight1);

  if ( verbose ) std::cout << "lost n w jets " << n_jets_lost << std::endl;

  int njunk = 0; //(int) rand.Uniform(3);
  for (int i=0; i<njunk; i++){
    double E = rand.Gaus(40.,10.);
    double eta = rand.Uniform(0.0,3.0);
    double phi = rand.Gaus(0.0,TMath::Pi());
    temp.SetPtEtaPhiE(E*sin(2*atan(exp(-eta))),eta,phi,E);
    AllJets_Vec.push_back(temp);
    AllJets_Lost.push_back(0);
  }

  if ( AllJets_Vec.size() < 6 ) return EL::StatusCode::SUCCESS;

  for ( int i=0; i<AllJets_Vec.size(); i++ ) {
    //    AllJets_Lost.at(i) = 0  ;
  }

  int nfound = 0;
  for ( int i=0; i<AllJets_Vec.size(); i++ ) {
    if (   AllJets_Lost.at(i) == 0 ) nfound++;
  }



  if ( nfound < 6 ) return EL::StatusCode::SUCCESS;

  //-------------------------------------------------------//
  //         Identified all particles do analysis          //
  //-------------------------------------------------------//

  TTVect.SetPxPyPzE(0,0,0,0);

  if ( verbose ) std::cout << AllJets_Vec.size() << std::endl;

  for ( int i=0; i<AllJets_Vec.size(); i++ ) {
    if (   AllJets_Lost.at(i) == 0 ) TTVect += AllJets_Vec.at(i);
  }

  double TTMass = TTVect.M();

  if ( TTMass < t_polemass*2 ) TTMass = 2*t_polemass+1.0;

  double expected_boost = 2.*sqrt( TTMass*TTMass/4. - t_polemass*t_polemass ) / TTMass;

  double A_const = sqrt(( expected_b_momentum*expected_b_momentum + b_polemass*b_polemass ) * ( 1 - expected_boost*expected_boost ));

  //-----------------------------------------//
  //   Boost everything to the TT CM Frame   //
  //-----------------------------------------//

  for ( int i=0; i<AllJets_Vec.size(); i++ ) {
    AllJets_Vec.at(i).Boost(-TTVect.BoostVector());
  }

  double B1_E = AllJets_Vec.at(0).E();
  //  double B1_P = AllJets_Vec.at(0).P();
  double B2_E = AllJets_Vec.at(1).E();
  //  double B2_P = AllJets_Vec.at(1).P();

  double A1_const = (A_const - B1_E);
  double A2_const = (A_const - B2_E);

  B1_3vec = AllJets_Vec.at(0).Vect();
  B2_3vec = AllJets_Vec.at(1).Vect();

  k_3vec_u = A2_const * B1_3vec + A1_const * B2_3vec;
  k_3vec_u.SetMag(1.0);

  B1_perp_k     = B1_3vec - (B1_3vec.Dot(k_3vec_u))*k_3vec_u;
  double   B1_perp_k_mag = B1_perp_k.Mag();
  B1_perp_k.SetMag(1.0);

  B1_cross_k = B1_perp_k.Cross(k_3vec_u);
  B1_cross_k.SetMag(1.0);

  double C1 = - A1_const / expected_boost / B1_perp_k_mag;
  if ( C1 >= 1.0 ) C1 = 0.99999;
  if ( C1 <= 0.0 ) C1 = 0.00001;
  double D1 = sqrt(1-C1*C1);

  T_Calc_Boost_Vect1 = C1 * B1_perp_k + D1 * B1_cross_k;
  T_Calc_Boost_Vect1.SetMag(expected_boost);

  T_Calc_Boost_Vect2 = C1 * B1_perp_k - D1 * B1_cross_k;
  T_Calc_Boost_Vect2.SetMag(expected_boost);

  if ( verbose ) {
    std::cout << expected_boost << std::endl;
    std::cout << A1_const << " A1_const " << std::endl;
    std::cout << C1 << " " << D1 << std::endl;
    std::cout << expected_boost << " " << B1_perp_k_mag << std::endl;
    std::cout << expected_b_momentum << std::endl;
    std::cout << T_Calc_Boost_Vect2.Mag() << std::endl;
  }

  //--------------------------------------------//

  int truth_boost = PlotTruth_SoftTop(T_Calc_Boost_Vect1,T_Calc_Boost_Vect2, reweight1);

  //--------------------------------------------//

  bool FoundTop1 = false;
  bool FoundTop2 = false;

  //  if ( truth_boost == 1 ) {

    for ( int i=0; i<AllJets_Vec.size(); i++ ) {
      AllJets_Vec.at(i).Boost(-T_Calc_Boost_Vect1);
    }
    FoundTop1 = FindSoftTop(0,1);
    for ( int i=0; i<AllJets_Vec.size(); i++ ) {
      AllJets_Vec.at(i).Boost(T_Calc_Boost_Vect1);
    }
    WCand_TTFrame2_MinPThrust.Boost(T_Calc_Boost_Vect1);
    TCand_TTFrame2_MinPThrust.Boost(T_Calc_Boost_Vect1);
    
    if ( FoundTop1 ) {
    for ( int i=0; i<AllJets_Vec.size(); i++ ) {
      AllJets_Vec.at(i).Boost(T_Calc_Boost_Vect1);
    }
    FoundTop2 = FindSoftTop(1,0);
    for ( int i=0; i<AllJets_Vec.size(); i++ ) {
      AllJets_Vec.at(i).Boost(-T_Calc_Boost_Vect1);
    }
    WCand_TTFrame2_MaxPThrust.Boost(-T_Calc_Boost_Vect1);
    TCand_TTFrame2_MaxPThrust.Boost(-T_Calc_Boost_Vect1);

  }
  else {
    for ( int i=0; i<AllJets_Vec.size(); i++ ) {
      AllJets_Vec.at(i).Boost(-T_Calc_Boost_Vect2);
    }
    FoundTop1 = FindSoftTop(0,1);
    for ( int i=0; i<AllJets_Vec.size(); i++ ) {
      AllJets_Vec.at(i).Boost(T_Calc_Boost_Vect2);
    }
    WCand_TTFrame2_MinPThrust.Boost(T_Calc_Boost_Vect2);
    TCand_TTFrame2_MinPThrust.Boost(T_Calc_Boost_Vect2);

    for ( int i=0; i<AllJets_Vec.size(); i++ ) {
      AllJets_Vec.at(i).Boost(T_Calc_Boost_Vect2);
    }
    FoundTop2 = FindSoftTop(1,0);
    for ( int i=0; i<AllJets_Vec.size(); i++ ) {
      AllJets_Vec.at(i).Boost(-T_Calc_Boost_Vect2);
    }
    WCand_TTFrame2_MaxPThrust.Boost(-T_Calc_Boost_Vect2);
    TCand_TTFrame2_MaxPThrust.Boost(-T_Calc_Boost_Vect2);
  }

  WCand_LabFrame2_MinPThrust.Boost(TTVect.BoostVector());
  TCand_LabFrame2_MinPThrust.Boost(TTVect.BoostVector());
  WCand_LabFrame2_MaxPThrust.Boost(TTVect.BoostVector());
  TCand_LabFrame2_MaxPThrust.Boost(TTVect.BoostVector());

  //--------------------------------------------------//

  //--------------------------------------------------//

  plotEvent = true;
  if (plotEvent){

    if (verbose) std::cout << "Plotting cut 0 plots" << std::endl;
    plot_signal(0, reweight1);

    if (dixi.Pt()>=200.){
      if ( count < 500 ) DrawEvtDisplay();
      count++;
      plot_signal(1, reweight1);
      if (verbose) std::cout << "passed cut 1 criterion" << std::endl;
      std::vector<float> jetpt_vec;
      jetpt_vec.resize(0);
      jetpt_vec.push_back(stop1_b.Pt());
      jetpt_vec.push_back(stop1_wj1.Pt());
      jetpt_vec.push_back(stop1_wj2.Pt());
      jetpt_vec.push_back(stop2_b.Pt());
      jetpt_vec.push_back(stop2_wj1.Pt());
      jetpt_vec.push_back(stop2_wj2.Pt());
      for (int i=0;i<nISR;i++){
	jetpt_vec.push_back(ISR_p[i][3]);
      }
      std::sort (jetpt_vec.begin(), jetpt_vec.end());
      float max_jetpt = jetpt_vec.back();
      jetpt_vec.pop_back();

      float secondmax_jetpt = jetpt_vec.back();
      if (verbose) std::cout << "max_jetpt is: " << max_jetpt << std::endl;
      if (verbose) std::cout << "secondmax is: " << secondmax_jetpt << std::endl;
      if ((max_jetpt >=200.) && (secondmax_jetpt >=60)){
	plot_signal(2, reweight1);
      }
    }
    plotEvent = false;
  }

  //-------------------------------------------------------------//

  return EL::StatusCode::SUCCESS;
}


bool TruthxAODAnalysis_STop::FindSoftTop(int b_top_index, int b_othertop_index) {

  if ( verbose ) std::cout << "Finding Soft Tops 2 " << std::endl;
  if ( verbose ) std::cout << b_top_index << " " << b_othertop_index << std::endl;

  if ( b_top_index < 0 ) return false;
  if ( b_othertop_index < 0 ) return false;

  bool found_WCand = false;
  double deltaThetaCut = TMath::Pi()/3.;

  double minWDeltaM = 10000000.;
  int minWDeltaM_k = -1;
  int minWDeltaM_j = -1;

  TVector3 negB_jet = -(AllJets_Vec.at(b_top_index).Vect()); // Set Direction Negative of B                                                         

  if (verbose) std::cout << "bjet P " << AllJets_Vec.at(b_top_index).P() << std::endl;
  if (verbose) std::cout << "other bjet P " << AllJets_Vec.at(b_othertop_index).P() << std::endl;

  for ( int j=0; j < AllJets_Vec.size(); j++ ) {
    if ( j == b_top_index )      continue;
    if ( j == b_othertop_index ) continue;
    if ( AllJets_Lost.at(j) == 1 ) continue;

    for ( int k=j+1; k < AllJets_Vec.size(); k++ ) {
      if ( k == b_top_index )      continue;
      if ( k == b_othertop_index ) continue;
      if ( AllJets_Lost.at(k) == 1 ) continue;

      double deltaTheta = negB_jet.Angle((AllJets_Vec.at(j)+AllJets_Vec.at(k)).Vect());
      if (verbose) std::cout << "jet pair neg bjet angle " << deltaTheta << std::endl;
      
      if ( fabs(deltaTheta) < deltaThetaCut ) {
        found_WCand = true;
        double jk_mass = (AllJets_Vec.at(j)+AllJets_Vec.at(k)).M();

        if (verbose) std::cout <<"found jet pair neg bjet angle " << deltaTheta << std::endl;
        if (verbose) std::cout <<"found jet pair mass           " << jk_mass << std::endl;

        // find best w candidate that falls into the cone opposite diretion of B
        // for both b's
        if ( minWDeltaM > fabs( jk_mass - w_polemass ) ) {
          minWDeltaM   = fabs( jk_mass - w_polemass );
          minWDeltaM_k = k;
          minWDeltaM_j = j;
        }
      }
    }
  }

  if ( found_WCand ) {
    if ( b_top_index == 0 ) {
      FoundMinPThrustTop = true;
      BCand_TopFrame2_MinPThrust = AllJets_Vec.at( b_top_index );
      WCand_TopFrame2_MinPThrust = AllJets_Vec.at(minWDeltaM_j) + AllJets_Vec.at(minWDeltaM_k);
      WCand_j1_TopFrame2_MinPThrust = AllJets_Vec.at(minWDeltaM_j);
      WCand_j2_TopFrame2_MinPThrust = AllJets_Vec.at(minWDeltaM_k);

      WCand_TTFrame2_MinPThrust = WCand_TopFrame2_MinPThrust;
      TCand_TTFrame2_MinPThrust = WCand_TopFrame2_MinPThrust + BCand_TopFrame2_MinPThrust;

      WCand_LabFrame2_MinPThrust = WCand_TTFrame2_MinPThrust;
      TCand_LabFrame2_MinPThrust = TCand_TTFrame2_MinPThrust;

    }
    if ( b_top_index == 1 ) {
      FoundMaxPThrustTop = true;

      BCand_TopFrame2_MaxPThrust = AllJets_Vec.at( b_top_index );
      WCand_TopFrame2_MaxPThrust = AllJets_Vec.at(minWDeltaM_j) + AllJets_Vec.at(minWDeltaM_k);
      WCand_j1_TopFrame2_MaxPThrust = AllJets_Vec.at(minWDeltaM_j);
      WCand_j2_TopFrame2_MaxPThrust = AllJets_Vec.at(minWDeltaM_k);

      WCand_TTFrame2_MaxPThrust = WCand_TopFrame2_MaxPThrust;
      TCand_TTFrame2_MaxPThrust = WCand_TopFrame2_MaxPThrust + BCand_TopFrame2_MaxPThrust;

      WCand_LabFrame2_MaxPThrust = WCand_TTFrame2_MaxPThrust;
      TCand_LabFrame2_MaxPThrust = TCand_TTFrame2_MaxPThrust;

    }
    return true;
  }
  else {

    if ( b_top_index == 0 ) {
      FoundMinPThrustTop = false;
      BCand_TopFrame2_MinPThrust = AllJets_Vec.at( b_top_index );
      WCand_TopFrame2_MinPThrust = -AllJets_Vec.at(b_top_index );
      WCand_TopFrame2_MinPThrust.SetE( sqrt(AllJets_Vec.at( b_top_index ).P()*
					    AllJets_Vec.at( b_top_index ).P() +
					    w_polemass*w_polemass) );

      WCand_TTFrame2_MinPThrust = WCand_TopFrame2_MinPThrust;
      TCand_TTFrame2_MinPThrust = WCand_TopFrame2_MinPThrust + BCand_TopFrame2_MinPThrust;

      WCand_LabFrame2_MinPThrust = WCand_TTFrame2_MinPThrust;
      TCand_LabFrame2_MinPThrust = TCand_TTFrame2_MinPThrust;
    }
    if ( b_top_index == 1 ) {
      FoundMaxPThrustTop = false;

      BCand_TopFrame2_MaxPThrust = AllJets_Vec.at( b_top_index );
      WCand_TopFrame2_MaxPThrust = -AllJets_Vec.at(b_top_index );
      WCand_TopFrame2_MaxPThrust.SetE( sqrt(AllJets_Vec.at( b_top_index ).P()*
					    AllJets_Vec.at( b_top_index ).P() +
					    w_polemass*w_polemass) );

      WCand_TTFrame2_MaxPThrust = WCand_TopFrame2_MaxPThrust;
      TCand_TTFrame2_MaxPThrust = WCand_TopFrame2_MaxPThrust + BCand_TopFrame2_MaxPThrust;

      WCand_LabFrame2_MaxPThrust = WCand_TTFrame2_MaxPThrust;
      TCand_LabFrame2_MaxPThrust = TCand_TTFrame2_MaxPThrust;
    }
    return false;
  }
}

double TruthxAODAnalysis_STop::CalculatePAlongThrust( TLorentzVector *Vec ) {
  return Vec->Px()*thrust_vec.Px() + Vec->Py()*thrust_vec.Py();
}
double TruthxAODAnalysis_STop::CalculatePAlongThrust( double px, double py ) {
  return px*thrust_vec.Px() + py*thrust_vec.Py();
}

bool TruthxAODAnalysis_STop::Find_STopDecayProducts( const xAOD::TruthParticle* particle, 
						     TLorentzVector *Top_tmp,
						     TLorentzVector *Xi_tmp,  TLorentzVector *B_tmp,
						     TLorentzVector *WJ1_tmp, TLorentzVector *WJ2_tmp ) {

  bool isSTopHad = false;

  if (verbose) std::cout << "inside stop1 loop (prod)" << std::endl;

  const xAOD::TruthVertex* decayVtx = particle->decayVtx();
  const xAOD::TruthParticle* particle_daughter;
  const xAOD::TruthVertex* decayVtx_daughter = decayVtx;

  int npart_daughter = decayVtx_daughter->nOutgoingParticles();

  int pdgId, status;

  //------------------------------------------------------------//
  //       Look at decay vertex see what the stop decays to     //
  //------------------------------------------------------------//

  //---------------------------------------------------------------------------------------//
  //  The stop can decay into another stop in a stop->stop->stop chain
  //  Make sure you reach the end of the chain and the decay product is stop -> W b + Xi
  //  Checking to see if it has more than one decay product (i.e. not a chain of astops).
  //  Doing this recursively until we get astop->W b + xi    
  //---------------------------------------------------------------------------------------//

  if (verbose) std::cout << "npart daughter before while is : " << npart_daughter << std::endl;
  while (npart_daughter <= 1){
    particle_daughter = decayVtx_daughter->outgoingParticle(0);
    decayVtx = decayVtx_daughter;
    decayVtx_daughter = particle_daughter->decayVtx();
    npart_daughter = decayVtx_daughter->nOutgoingParticles();
    particle = particle_daughter;
  }

  status = particle->status();
  if (verbose) std::cout << "npart daughter after while is : " << npart_daughter << std::endl;
  if (verbose) std::cout << "particle's status is: " << status << std::endl;

  //----------------------------------------------------------------//
  //               Found last stop in the chain.                    //
  //  This stop decay vertex should be the stop -> W b + Xi vertex  //
  //----------------------------------------------------------------//

  bool hasDecayVtx = particle->hasDecayVtx();
  if (hasDecayVtx){

    const xAOD::TruthVertex* decayVtx = particle->decayVtx();
    int npart = decayVtx->nOutgoingParticles();

    //----------------------------------------------------------------//
    //             Loop over decay products of the stop               //
    //----------------------------------------------------------------//

    for (int j=0; j<npart; j++){

      const xAOD::TruthParticle* particle = decayVtx->outgoingParticle(j);
      pdgId = particle->pdgId();
      status = particle->status();
      
      double px = particle->px()/GeV;
      double py = particle->py()/GeV;
      double pz = particle->pz()/GeV;
      double e = particle->e()/GeV;

      if (verbose) std::cout << "inside stop1 decay vertex loop..... " << std::endl;
      if (verbose) std::cout << "The id of particle " << j << " of stop1 decayvtx is " << pdgId << std::endl;
      if (verbose) std::cout << "The status of particle "<< j << " of stop1 decayvtx " << status << std::endl;

      //---------------------//
      //      Find the B     //
      //---------------------//

      if (abs(pdgId) == 5){
	B_tmp->SetPxPyPzE(px,py,pz,e);
	if (verbose) std::cout << "stop1_b_px is " << px << std::endl;
      }

      //----------------------------------------------//
      //     Find any susy particles, this is the Xi  //
      //----------------------------------------------//

      if (abs(pdgId) >= 100000){
	Xi_tmp->SetPxPyPzE(px,py,pz,e);
      }

      //-------------------------//
      //     Find the W boson    //
      //-------------------------//

      if (abs(pdgId) == 24){
	isSTopHad = Find_WDecayProducts( particle, WJ1_tmp, WJ2_tmp );          
      }

      if ( abs(pdgId) == 6 ) {
	Top_tmp->SetPxPyPzE(px,py,pz,e);
	if (verbose) std::cout << "stop1_t_p is " << sqrt(px*px+py*py+pz*pz) << std::endl;
	isSTopHad = Find_TopDecayProducts( particle, B_tmp, WJ1_tmp, WJ2_tmp );
      }
    }
  }

  return isSTopHad;
}

bool TruthxAODAnalysis_STop::Find_TopDecayProducts( const xAOD::TruthParticle* particle,
						    TLorentzVector *B_tmp,
						    TLorentzVector *WJ1_tmp, TLorentzVector *WJ2_tmp ) {


  bool isSTopHad = false;

  //---------------------------------------//
  //     Find decay product of Top boson   //
  //---------------------------------------//

  bool hasDecayVtx = particle->hasDecayVtx();
  int pdgId = particle->pdgId();
  int status = particle->status();
  if (hasDecayVtx){
    const xAOD::TruthVertex* decayVtx = particle->decayVtx();

    const xAOD::TruthParticle* particle_daughter;
    const xAOD::TruthVertex* decayVtx_daughter = decayVtx;


    //----------------------------------------------------//
    //   Again the W can decay into other W in a chain    //
    //   Keep looking until you find the final t->b,w     //
    //----------------------------------------------------//

    while (abs(pdgId)==6){
      particle_daughter = decayVtx_daughter->outgoingParticle(0);
      decayVtx = decayVtx_daughter;
      decayVtx_daughter = particle_daughter->decayVtx();
      pdgId = particle_daughter->pdgId();
    }

    //-----------------------------------------//
    //         Finally found T decay           //
    //-----------------------------------------//

    int npart = decayVtx->nOutgoingParticles();

    if (verbose) std::cout << "top npart is " << npart << std::endl;
    status = particle->status();
    if (verbose) std::cout << "(top) status of top that decays to non top is: " << status << std::endl;

    //------------------------------------------//
    //         Assign T decay products          //
    //------------------------------------------//

    bool j1_exists = false;

    for (int k=0; k<npart;k++){
      const xAOD::TruthParticle* particle = decayVtx->outgoingParticle(k);
      pdgId = particle->pdgId();
      status = particle->status();
      if (verbose) std::cout << "inside top decay vertex loop..... " << std::endl;
      if (verbose) std::cout << "The id of particle " << k << " of Wdecayvtx is " << pdgId << std::endl;
      if (verbose) std::cout << "The status of particle "<< k << " of Wdecayvtx " << status << std::endl;

      if (abs(pdgId) ==5) {

        double px = particle->px()/GeV;
        double py = particle->py()/GeV;
        double pz = particle->pz()/GeV;
        double e = particle->e()/GeV;

	B_tmp->SetPxPyPzE(px,py,pz,e);

      }
      
      if (abs(pdgId) == 24) {
        isSTopHad = Find_WDecayProducts( particle, WJ1_tmp, WJ2_tmp );
      }
    }
  }

  return isSTopHad;

}

bool TruthxAODAnalysis_STop::Find_WDecayProducts( const xAOD::TruthParticle* particle, 
						  TLorentzVector *WJ1_tmp, TLorentzVector *WJ2_tmp ) {
  
  //---------------------------------------------------//
  //  I'm passing the address of WJ1_tmp and WJ2_tmp   //
  //  This means that the TLorentzVector sent to WJ1   //
  //  and WJ2 will have its momenta set as those of    //
  //  the WDecay product.                              //
  //  Use pointers to pass objects between methods     //
  //---------------------------------------------------//

  bool isSTopHad = false;
  
  //---------------------------------------//                                                       
  //     Find decay product of W boson     //                                                       
  //---------------------------------------//                                                       
  bool hasDecayVtx = particle->hasDecayVtx();
  int pdgId = particle->pdgId();
  int status = particle->status();
  if (hasDecayVtx){
    const xAOD::TruthVertex* decayVtx = particle->decayVtx();

    const xAOD::TruthParticle* particle_daughter;
    const xAOD::TruthVertex* decayVtx_daughter = decayVtx;


    //----------------------------------------------------//                                        
    //   Again the W can decay into other W in a chain    //                                        
    //   Keep looking until you find the final W->j1,j2   //                                        
    //----------------------------------------------------//                                        

    while (abs(pdgId)==24){
      particle_daughter = decayVtx_daughter->outgoingParticle(0);
      decayVtx = decayVtx_daughter;
      decayVtx_daughter = particle_daughter->decayVtx();
      pdgId = particle_daughter->pdgId();
    }

    //-----------------------------------------//                                                   
    //         Finally found W decay           //                                                   
    //-----------------------------------------//                                                   

    int npart = decayVtx->nOutgoingParticles();

    if (verbose) std::cout << "stop1 npart is " << npart << std::endl;
    status = particle->status();
    if (verbose) std::cout << "(Stop1) status of W that decays to non W is: " << status << std::endl;

    //------------------------------------------//                                                  
    //         Assign W decay products          //                                                  
    //------------------------------------------//                                                  

    bool j1_exists = false;

    for (int k=0; k<npart;k++){
      const xAOD::TruthParticle* particle = decayVtx->outgoingParticle(k);
      pdgId = particle->pdgId();
      status = particle->status();
      if (verbose) std::cout << "inside W decay vertex loop..... " << std::endl;
      if (verbose) std::cout << "The id of particle " << k << " of Wdecayvtx is " << pdgId << std::endl;
      if (verbose) std::cout << "The status of particle "<< k << " of Wdecayvtx " << status << std::endl;

      //-----------------------------------------------------//
      //       If Decay Product is Quarks, W is Hadronic     //
      //-----------------------------------------------------//

      if ((abs(pdgId) >=1) && (abs(pdgId) <=6)) {
	double wj_px = particle->px()/GeV;
	double wj_py = particle->py()/GeV;
	double wj_pz = particle->pz()/GeV;
	double wj_e = particle->e()/GeV;

	if ( !j1_exists ) {
	  if (verbose) std::cout << "inside stop1W first jet loop " << std::endl;
	  j1_exists = true;
	  WJ1_tmp->SetPxPyPzE(wj_px,wj_py,wj_pz,wj_e);
	}
	else {
          if (verbose) std::cout << "inside stop2W first jet loop " << std::endl;
          WJ2_tmp->SetPxPyPzE(wj_px,wj_py,wj_pz,wj_e);
	  isSTopHad = true;
	}
      }
    }
  }
  else {
    std::cout << "WTF, W has no decay product.  MC is broken!!!!" << std::endl;
  }

  return isSTopHad;

}

int TruthxAODAnalysis_STop::PlotTruth_SoftTop(TVector3 boost1, TVector3 boost2, double weight){


  TVector3 TrueBoostMinP = (AllJets_Vec.at(0)+AllJets_Vec.at(2)+AllJets_Vec.at(3)).BoostVector();
  TVector3 TrueBoostMaxP = (AllJets_Vec.at(1)+AllJets_Vec.at(4)+AllJets_Vec.at(5)).BoostVector();

  double TMassMinP = (AllJets_Vec.at(0)+AllJets_Vec.at(2)+AllJets_Vec.at(3)).M();
  double TMassMaxP = (AllJets_Vec.at(1)+AllJets_Vec.at(4)+AllJets_Vec.at(5)).M();

  double WMassMinP = (AllJets_Vec.at(2)+AllJets_Vec.at(3)).M();
  double WMassMaxP = (AllJets_Vec.at(4)+AllJets_Vec.at(5)).M();

  double BW1MassMinP = TMath::Min((AllJets_Vec.at(0)+AllJets_Vec.at(2)).M(), (AllJets_Vec.at(1)+AllJets_Vec.at(2)).M());
  double BW1MassMaxP = TMath::Min((AllJets_Vec.at(1)+AllJets_Vec.at(4)).M(), (AllJets_Vec.at(0)+AllJets_Vec.at(4)).M());
  double BW2MassMinP = TMath::Min((AllJets_Vec.at(0)+AllJets_Vec.at(3)).M(), (AllJets_Vec.at(1)+AllJets_Vec.at(3)).M());
  double BW2MassMaxP = TMath::Min((AllJets_Vec.at(1)+AllJets_Vec.at(5)).M(), (AllJets_Vec.at(0)+AllJets_Vec.at(5)).M());

  h_true_TMass_MinP->Fill(TMassMinP, weight);
  h_true_TMass_MaxP->Fill(TMassMaxP, weight);

  h_true_WMass_MinP->Fill(WMassMinP, weight);
  h_true_WMass_MaxP->Fill(WMassMaxP, weight);

  h_true_BWjetMass->Fill(BW1MassMinP, weight);
  h_true_BWjetMass->Fill(BW1MassMaxP, weight);
  h_true_BWjetMass->Fill(BW2MassMinP, weight);
  h_true_BWjetMass->Fill(BW2MassMaxP, weight);

  double TTMass    = (AllJets_Vec.at(0)+AllJets_Vec.at(2)+AllJets_Vec.at(3) +
                      AllJets_Vec.at(1)+AllJets_Vec.at(4)+AllJets_Vec.at(5)).M();

  int truth_boost_i;

  //-------------------------------------//
  //  Figure out which boost is better   //
  //-------------------------------------//

  //  Min pthrust top
  AllJets_Vec.at(0).Boost(-boost1);
  AllJets_Vec.at(2).Boost(-boost1);
  AllJets_Vec.at(3).Boost(-boost1);

  double deltaAngle1 = AllJets_Vec.at(0).Vect().Angle((AllJets_Vec.at(2)+AllJets_Vec.at(3)).Vect());

  AllJets_Vec.at(0).Boost(boost1);
  AllJets_Vec.at(2).Boost(boost1);
  AllJets_Vec.at(3).Boost(boost1);

  //  Max Pthrust top
  AllJets_Vec.at(1).Boost(boost1);
  AllJets_Vec.at(4).Boost(boost1);
  AllJets_Vec.at(5).Boost(boost1);

  deltaAngle1 += AllJets_Vec.at(1).Vect().Angle((AllJets_Vec.at(4)+AllJets_Vec.at(5)).Vect());

  AllJets_Vec.at(1).Boost(-boost1);
  AllJets_Vec.at(4).Boost(-boost1);
  AllJets_Vec.at(5).Boost(-boost1);

  //  Min pthrust top
  AllJets_Vec.at(0).Boost(-boost2);
  AllJets_Vec.at(2).Boost(-boost2);
  AllJets_Vec.at(3).Boost(-boost2);

  double deltaAngle2 = AllJets_Vec.at(0).Vect().Angle((AllJets_Vec.at(2)+AllJets_Vec.at(3)).Vect());

  AllJets_Vec.at(0).Boost(boost2);
  AllJets_Vec.at(2).Boost(boost2);
  AllJets_Vec.at(3).Boost(boost2);

  //  Max Pthrust top                                                                                                                                                                                      
  AllJets_Vec.at(1).Boost(boost2);
  AllJets_Vec.at(4).Boost(boost2);
  AllJets_Vec.at(5).Boost(boost2);

  deltaAngle2 += AllJets_Vec.at(1).Vect().Angle((AllJets_Vec.at(4)+AllJets_Vec.at(5)).Vect());

  AllJets_Vec.at(1).Boost(-boost2);
  AllJets_Vec.at(4).Boost(-boost2);
  AllJets_Vec.at(5).Boost(-boost2);

  double TrueBoostDeltaAngMinP;
  double TrueBoostDeltaMagMinP;
  double TrueBoostDeltaAngMaxP;
  double TrueBoostDeltaMagMaxP;
  
  if ( deltaAngle1 > deltaAngle2 ) {

    truth_boost_i = 1;

    AllJets_Vec.at(0).Boost(-boost1);
    AllJets_Vec.at(2).Boost(-boost1);
    AllJets_Vec.at(3).Boost(-boost1);
    AllJets_Vec.at(1).Boost(boost1);
    AllJets_Vec.at(4).Boost(boost1);
    AllJets_Vec.at(5).Boost(boost1);

    TrueBoostDeltaAngMinP = TrueBoostMinP.Angle(-boost1);
    TrueBoostDeltaMagMinP = TrueBoostMinP.Mag() - boost1.Mag();
    TrueBoostDeltaAngMaxP = TrueBoostMaxP.Angle( boost1);
    TrueBoostDeltaMagMaxP = TrueBoostMaxP.Mag() - boost1.Mag();
  }
  else {

    truth_boost_i = 2;

    AllJets_Vec.at(0).Boost(-boost2);
    AllJets_Vec.at(2).Boost(-boost2);
    AllJets_Vec.at(3).Boost(-boost2);
    AllJets_Vec.at(1).Boost(boost2);
    AllJets_Vec.at(4).Boost(boost2);
    AllJets_Vec.at(5).Boost(boost2);

    TrueBoostDeltaAngMinP = TrueBoostMinP.Angle(-boost2);
    TrueBoostDeltaMagMinP = TrueBoostMinP.Mag() - boost2.Mag();
    TrueBoostDeltaAngMaxP = TrueBoostMaxP.Angle( boost2);
    TrueBoostDeltaMagMaxP = TrueBoostMaxP.Mag() - boost2.Mag();
  }

  double deltaAngleMinP = AllJets_Vec.at(0).Vect().Angle((AllJets_Vec.at(2)+AllJets_Vec.at(3)).Vect());
  double deltaAngleMaxP = AllJets_Vec.at(1).Vect().Angle((AllJets_Vec.at(4)+AllJets_Vec.at(5)).Vect());

  double deltaPhiMinP = fabs(AllJets_Vec.at(0).DeltaPhi(AllJets_Vec.at(2)+AllJets_Vec.at(3)));
  double deltaPhiMaxP = fabs(AllJets_Vec.at(1).DeltaPhi(AllJets_Vec.at(4)+AllJets_Vec.at(5)));

  double deltaEtaMinP = AllJets_Vec.at(0).Eta() - (AllJets_Vec.at(2)+AllJets_Vec.at(3)).Eta();
  double deltaEtaMaxP = AllJets_Vec.at(1).Eta() - (AllJets_Vec.at(4)+AllJets_Vec.at(5)).Eta();

  double deltaRMinP = AllJets_Vec.at(0).DeltaR(AllJets_Vec.at(2)+AllJets_Vec.at(3));
  double deltaRMaxP = AllJets_Vec.at(1).DeltaR(AllJets_Vec.at(4)+AllJets_Vec.at(5));

  double deltaThetaMinP = AllJets_Vec.at(0).Theta()-(AllJets_Vec.at(2)+AllJets_Vec.at(3)).Theta();
  double deltaThetaMaxP = AllJets_Vec.at(1).Theta()-(AllJets_Vec.at(4)+AllJets_Vec.at(5)).Theta();

  if (verbose) std::cout <<"found MinP jet pair bjet angle " << deltaAngleMinP << std::endl;
  if (verbose) std::cout <<"found MinP jet pair mass       " << (AllJets_Vec.at(2)+AllJets_Vec.at(3)).M() << std::endl;
  if (verbose) std::cout <<"found MaxP jet pair bjet angle " << deltaAngleMaxP << std::endl;
  if (verbose) std::cout <<"found MaxP jet pair mass       " << (AllJets_Vec.at(4)+AllJets_Vec.at(5)).M() << std::endl;

  h_TrueBoostDeltaMinP_MagVsAng->Fill(TrueBoostDeltaMagMinP, TrueBoostDeltaAngMinP, weight);
  h_TrueBoostDeltaMinPAng->Fill(TrueBoostDeltaAngMinP, weight);
  h_TrueBoostDeltaMinPMag->Fill(TrueBoostDeltaMagMinP, weight);
  h_TrueBoostDeltaMaxP_MagVsAng->Fill(TrueBoostDeltaMagMaxP, TrueBoostDeltaAngMaxP, weight);
  h_TrueBoostDeltaMaxPAng->Fill(TrueBoostDeltaAngMaxP, weight);
  h_TrueBoostDeltaMaxPMag->Fill(TrueBoostDeltaMagMaxP, weight);
  
  if ( AllJets_Lost.at(2) == 0 && AllJets_Lost.at(3) == 0 && 
       (AllJets_Lost.at(4) == 1 || AllJets_Lost.at(5) == 1) ) {
    h_TrueTMinP_BW_LostOtherW_DeltaAng->Fill(deltaAngleMinP, weight);
    h_TrueTMinP_BW_LostOtherW_DeltaPhi->Fill(deltaPhiMinP, weight);
    h_TrueTMinP_BW_LostOtherW_DeltaEta->Fill(deltaEtaMinP, weight);
    h_TrueTMinP_BW_LostOtherW_DeltaTheta->Fill(deltaThetaMinP, weight);
  }
  if ( AllJets_Lost.at(4) == 0 && AllJets_Lost.at(5) == 0 &&
       (AllJets_Lost.at(2) == 1 || AllJets_Lost.at(3) == 1) ) {
    h_TrueTMaxP_BW_LostOtherW_DeltaAng->Fill(deltaAngleMaxP, weight);
    h_TrueTMaxP_BW_LostOtherW_DeltaPhi->Fill(deltaPhiMaxP, weight);
    h_TrueTMaxP_BW_LostOtherW_DeltaEta->Fill(deltaEtaMaxP, weight);
    h_TrueTMaxP_BW_LostOtherW_DeltaTheta->Fill(deltaThetaMaxP, weight);
  }
  if ( AllJets_Lost.at(2) == 0 && AllJets_Lost.at(3) == 0 ) {
    h_TrueTMinP_BW_DeltaAng->Fill(deltaAngleMinP, weight);
    h_TrueTMinP_BW_DeltaAng->Fill(deltaAngleMinP, weight);
    h_TrueTMinP_BW_DeltaPhi->Fill(deltaPhiMinP, weight);
    h_TrueTMinP_BW_DeltaEta->Fill(deltaEtaMinP, weight);
    h_TrueTMinP_BW_DeltaTheta->Fill(deltaThetaMinP, weight);
  }
  if ( AllJets_Lost.at(4) == 0 && AllJets_Lost.at(5) == 0 ) {
    h_TrueTMaxP_BW_DeltaAng->Fill(deltaAngleMaxP, weight);
    h_TrueTMaxP_BW_DeltaPhi->Fill(deltaPhiMaxP, weight);
    h_TrueTMaxP_BW_DeltaEta->Fill(deltaEtaMaxP, weight);
    h_TrueTMaxP_BW_DeltaTheta->Fill(deltaThetaMaxP, weight);
  }

  h_True_TTMass->Fill(TTMass, weight);

  if ( deltaAngle1 > deltaAngle2 ) {

    AllJets_Vec.at(0).Boost(boost1);
    AllJets_Vec.at(2).Boost(boost1);
    AllJets_Vec.at(3).Boost(boost1);
    AllJets_Vec.at(1).Boost(-boost1);
    AllJets_Vec.at(4).Boost(-boost1);
    AllJets_Vec.at(5).Boost(-boost1);

  }
  else {

    AllJets_Vec.at(0).Boost(boost2);
    AllJets_Vec.at(2).Boost(boost2);
    AllJets_Vec.at(3).Boost(boost2);
    AllJets_Vec.at(1).Boost(-boost2);
    AllJets_Vec.at(4).Boost(-boost2);
    AllJets_Vec.at(5).Boost(-boost2);

  }
  
  return truth_boost_i;

}

void TruthxAODAnalysis_STop::SetVerbose(int i) {
  if ( i == 0 ) verbose = false;
  else verbose = true;
  return;
}

void TruthxAODAnalysis_STop::plot_signal(int icut, double weight){
  //Plot stop stop2 inv mass
  if (verbose) std::cout << "Inside plot_signal, filling distop mass plot" << std::endl;
  h_distop_mass[icut]->Fill(distop.M(), weight);  
  h_distop_pt[icut]->Fill(distop.Pt(), weight);

  // Plot W, b inv mass
  if (verbose) std::cout << "Filling w b inv mass plot" << std::endl;
  h_stop1_b_w_mass[icut]->Fill(stop1_jets.M(), weight);

  h_stop2_b_w_mass[icut]->Fill(stop2_jets.M(), weight);

  if (verbose) std::cout << "Filling pt plots" << std::endl;
  //pt of jets
  h_stop1_pt[icut]->Fill(stop1.Pt(), weight);
  h_stop2_pt[icut]->Fill(stop2.Pt(), weight);
  h_stop1_b_pt[icut]->Fill(stop1_b.Pt(), weight);
  h_stop2_b_pt[icut]->Fill(stop2_b.Pt(), weight);
  if (verbose) std::cout << "filling stop_wj2 hist" << std::endl;
  /*if (verbose) std::cout << "stop_wj1 px is" << stop_wj1.Px() << std::endl;
  if (verbose) std::cout << "stop_wj1 py is" << stop_wj1.Py() << std::endl;
  if (verbose) std::cout << "stop_wj1 pz is" << stop_wj1.Pz() << std::endl;
  if (verbose) std::cout << "stop_wj1 E is" << stop_wj1.E() << std::endl;
  if (verbose) std::cout << "stop_wj1 pt is" << stop_wj1.Pt() << std::endl;
  */

  h_stop1_w_jets_eta[icut]->Fill(stop1_wj1.Eta(), weight);
  h_stop1_w_jets_eta[icut]->Fill(stop1_wj2.Eta(), weight);

  h_stop1_w_jets_pt_eta[icut]->Fill(stop1_wj1.Eta(), stop1_wj1.Pt(), weight);
  h_stop1_w_jets_pt_eta[icut]->Fill(stop1_wj2.Eta(), stop1_wj2.Pt(), weight);

  h_stop1_w_jets_p_eta[icut]->Fill(stop1_wj1.Eta(), stop1_wj1.P(), weight);
  h_stop1_w_jets_p_eta[icut]->Fill(stop1_wj2.Eta(), stop1_wj2.P(), weight);

  h_stop1_wj_b_MinMass[icut]->Fill(TMath::Min((stop1_wj1+stop1_b).M(),(stop1_wj1+stop2_b).M()));
  h_stop1_wj_b_MinMass[icut]->Fill(TMath::Min((stop1_wj2+stop1_b).M(),(stop1_wj2+stop2_b).M()));
  h_stop1_wj_b_MaxMass[icut]->Fill(TMath::Max((stop1_wj1+stop1_b).M(),(stop1_wj1+stop2_b).M()));
  h_stop1_wj_b_MaxMass[icut]->Fill(TMath::Max((stop1_wj2+stop1_b).M(),(stop1_wj2+stop2_b).M()));

  h_stop1_wj1_pt[icut]->Fill(stop1_wj1.Pt(), weight);
  h_stop1_wj2_pt[icut]->Fill(stop1_wj2.Pt(), weight);
  h_stop2_wj1_pt[icut]->Fill(stop2_wj1.Pt(), weight);
  h_stop2_wj2_pt[icut]->Fill(stop2_wj2.Pt(), weight);
  if (verbose) std::cout << "filling stop_wj2 hist" << std::endl;
  //if (verbose) std::cout << "stop_wj2 px is" << stop_wj2.Px() << std::endl;
  //if (verbose) std::cout << "stop_wj2 py is" << stop_wj2.Py() << std::endl;
  //if (verbose) std::cout << "stop_wj2 pz is" << stop_wj2.Pz() << std::endl;
  //if (verbose) std::cout << "stop_wj2 E is" << stop_wj2.E() << std::endl;
  //if (verbose) std::cout << "stop_wj2 pt is" << stop_wj2.Pt() << std::endl;

  //if (verbose) std::cout << "checking that h_stop_wj2 exists: " << h_stop_wj2_pt[icut]->GetNbinsX() << std::endl;
  //  h_stop_wj2_pt[icut]->Fill(stop_wj2.Pt(), weight);
  h_stop2_pt[icut]->Fill(stop2.Pt(), weight);
  if (verbose) std::cout << "astop_b pt is" << stop2_b.Pt() << std::endl;
  //h_astop_b_pt[icut]->Fill(astop_b.Pt(), weight);
  if (verbose) std::cout << "astop_b_pt is fine" << std::endl;
  //h_astop_wj1_pt[icut]->Fill(astop_wj1.Pt(), weight);
  if (verbose) std::cout << "astop_wj1_pt is fine " << std::endl;
  //h_astop_wj2_pt[icut]->Fill(astop_wj2.Pt(), weight);
  if (verbose) std::cout << "astop_wj2_pt is fine " << std::endl;
  //h_dixi_pt[icut]->Fill(dixi.Pt(), weight);
  if (verbose) std::cout << "dixi_pt is fine " << std::endl;

  
  //PThrust of everything
  if (verbose) std::cout << "Filling Pthrust plots" << std::endl;
  float stop1_pthrust = stop1.Px()*thrust_vec.Px() + stop1.Py()*thrust_vec.Py();
  h_stop1_pthrust[icut]->Fill(stop1_pthrust, weight);

  float stop1_b_pthrust = stop1_b.Px()*thrust_vec.Px() + stop1_b.Py()*thrust_vec.Py();
  h_stop1_b_pthrust[icut]->Fill(stop1_b_pthrust, weight);

  float stop1_wj1_pthrust = stop1_wj1.Px()*thrust_vec.Px() + stop1_wj1.Py()*thrust_vec.Py();
  h_stop1_wj1_pthrust[icut]->Fill(stop1_wj1_pthrust, weight);

  float stop1_wj2_pthrust = stop1_wj2.Px()*thrust_vec.Px() + stop1_wj2.Py()*thrust_vec.Py();
  h_stop1_wj2_pthrust[icut]->Fill(stop1_wj2_pthrust, weight);

  float stop1_jets_pthrust = stop1_jets.Px()*thrust_vec.Px() + stop1_jets.Py()*thrust_vec.Py();
  h_stop1_jets_pthrust[icut]->Fill(stop1_jets_pthrust, weight);

  float stop2_pthrust = stop2.Px()*thrust_vec.Px() + stop2.Py()*thrust_vec.Py();
  h_stop2_pthrust[icut]->Fill(stop2_pthrust, weight);

  float stop2_b_pthrust = stop2_b.Px()*thrust_vec.Px() + stop2_b.Py()*thrust_vec.Py();
  h_stop2_b_pthrust[icut]->Fill(stop2_b_pthrust, weight);

  float stop2_wj1_pthrust = stop2_wj1.Px()*thrust_vec.Px() + stop2_wj1.Py()*thrust_vec.Py();
  h_stop2_wj1_pthrust[icut]->Fill(stop2_wj1_pthrust, weight);

  float stop2_wj2_pthrust = stop2_wj2.Px()*thrust_vec.Px() + stop2_wj2.Py()*thrust_vec.Py();
  h_stop2_wj2_pthrust[icut]->Fill(stop2_wj2_pthrust, weight);

  float stop2_jets_pthrust = stop2_jets.Px()*thrust_vec.Px() + stop2_jets.Py()*thrust_vec.Py();
  h_stop2_jets_pthrust[icut]->Fill(stop2_jets_pthrust, weight);

  float xi_pthrust = dixi.Px()*thrust_vec.Px() + dixi.Py()*thrust_vec.Py();
  h_dixi_pthrust[icut]->Fill(xi_pthrust, weight);

  if (verbose) std::cout << "Filling Pt thrust plots" << std::endl;
  //PtThrust for W, b
  float stop1_jets_pt_thrust = stop1_jets.Px()*thrust_perp_vec.Px() + stop1_jets.Py()*thrust_perp_vec.Py();
  h_stop1_jets_pt_thrust[icut]->Fill(stop1_jets_pt_thrust, weight);

  float stop1_b_pt_thrust = stop1_b.Px()*thrust_perp_vec.Px() + stop1_b.Py()*thrust_perp_vec.Py();
  h_stop1_b_pt_thrust[icut]->Fill(stop1_b_pt_thrust, weight);

  float stop2_jets_pt_thrust = stop2_jets.Px()*thrust_perp_vec.Px() + stop2_jets.Py()*thrust_perp_vec.Py();
  h_stop2_jets_pt_thrust[icut]->Fill(stop2_jets_pt_thrust, weight);

  float stop2_b_pt_thrust = stop2_b.Px()*thrust_perp_vec.Px() + stop2_b.Py()*thrust_perp_vec.Py();
  h_stop2_b_pt_thrust[icut]->Fill(stop2_b_pt_thrust, weight);

  if (verbose) std::cout << "Filling thrust2D plots" << std::endl;
  //Thrust2D
  h_stop1_w_thrust2D[icut]->Fill(stop1_jets_pthrust,stop1_jets_pt_thrust, weight);
  h_stop1_b_thrust2D[icut]->Fill(stop1_b_pthrust,stop1_b_pt_thrust, weight);

  h_stop2_w_thrust2D[icut]->Fill(stop2_jets_pthrust,stop2_jets_pt_thrust, weight);
  h_stop2_b_thrust2D[icut]->Fill(stop2_b_pthrust,stop2_b_pt_thrust, weight);

  h_stop2_wj_b_MinMass[icut]->Fill(TMath::Min((stop2_wj1+stop1_b).M(),(stop2_wj1+stop2_b).M()));
  h_stop2_wj_b_MinMass[icut]->Fill(TMath::Min((stop2_wj2+stop1_b).M(),(stop2_wj2+stop2_b).M()));
  h_stop2_wj_b_MaxMass[icut]->Fill(TMath::Max((stop2_wj1+stop1_b).M(),(stop2_wj1+stop2_b).M()));
  h_stop2_wj_b_MaxMass[icut]->Fill(TMath::Max((stop2_wj2+stop1_b).M(),(stop2_wj2+stop2_b).M()));

  if (verbose) std::cout << "Filling dixi pt plot" << std::endl;
  //Pt of the 2 neutralino system (isn't this MET?)

  if ( verbose ) std::cout << "dixi_mass is " << dixi.M() << std::endl;
  h_dixi_mass[icut]->Fill(dixi.M(), weight);
  h_dixi_pt[icut]->Fill(dixi.Pt(), weight);

  //Delta Phi between ISR and MET

  if (verbose) std::cout << "Doing delphi btwn ISR and MET" << std::endl;
  float temp_px = 0.;
  float temp_py = 0.;
  float temp_pz = 0.;
  float temp_pt = 0.;
  float temp_e = 0.;
  for (int i=0; i<nISR; i ++){
    temp_px += ISR_p[i][0];
    temp_py += ISR_p[i][1];
    temp_pz += ISR_p[i][2];
    temp_pt += ISR_p[i][3];
    temp_e += ISR_p[i][4];
  }
  ISR_total.SetPxPyPzE(temp_px,temp_py,temp_pz,temp_e);

  h_nISR[icut]->Fill(nISR, weight);

  if( nISR == 0 ) {
    h_noISR_dixi_pt[icut]->Fill(dixi.Pt(), weight);
    h_noISR_tt_pt[icut]->Fill((stop1_jets+stop2_jets).Pt(), weight);
    h_noISR_distop_pt[icut]->Fill(distop.Pt(), weight);
  }

  if ( nISR == 1 ) {
    h_1ISR_totalPt[icut]->Fill(ISR_total.Pt(), weight);

    TLorentzVector ISR_tmp;
    for (int i=0; i<nISR; i ++){
      ISR_tmp.SetPxPyPzE(ISR_p[i][0],ISR_p[i][1],
			 ISR_p[i][2],ISR_p[i][4]);
      double ISR_b1_mass = (stop1_b+ISR_tmp).M();
      double ISR_b2_mass = (stop2_b+ISR_tmp).M();
      double ISR_PAlongThrust = CalculatePAlongThrust( &ISR_tmp );
      h_1ISR_jetPt[icut]->Fill(ISR_tmp.Pt(), weight);
      h_1ISR_jetEta[icut]->Fill(ISR_tmp.Eta(), weight);
      h_1ISR_jet_b_MinMass[icut]->Fill( TMath::Min( ISR_b1_mass, ISR_b2_mass ) , weight);
      h_1ISR_jet_b_MaxMass[icut]->Fill( TMath::Max( ISR_b1_mass, ISR_b2_mass ) , weight);
      h_1ISR_PAlongThrust[icut]->Fill(ISR_PAlongThrust, weight);


      h_1ISR_pt_distop_pt[icut]->Fill(ISR_tmp.Pt(), distop.Pt(), weight);
      h_1ISR_pt_Met[icut]->Fill(ISR_tmp.Pt(), dixi.Pt(), weight);
      h_1ISR_PAlongThrust_Met[icut]->Fill(ISR_PAlongThrust, dixi.Pt(), weight);
      h_1ISR_pt_tt_pt[icut]->Fill(ISR_tmp.Pt(), (stop1_jets+stop2_jets).Pt(), weight);
      h_1ISR_pt_ISR_b_MinMass[icut]->Fill(ISR_tmp.Pt(), TMath::Min( ISR_b1_mass, ISR_b2_mass ) , weight);
      h_1ISR_pt_ISR_b_MaxMass[icut]->Fill(ISR_tmp.Pt(), TMath::Max( ISR_b1_mass, ISR_b2_mass ) , weight);
      h_1ISR_Met_ISR_b_MinMass[icut]->Fill(dixi.Pt(), TMath::Min( ISR_b1_mass, ISR_b2_mass ), weight);
      h_1ISR_Met_ISR_b_MaxMass[icut]->Fill(dixi.Pt(), TMath::Max( ISR_b1_mass, ISR_b2_mass ), weight);

    }
  }

  if ( nISR >= 2 ) {
    h_2ISR_totalPt[icut]->Fill(ISR_total.Pt(), weight);

    TLorentzVector ISR_tmp;
    for (int i=0; i<nISR; i ++){
      ISR_tmp.SetPxPyPzE(ISR_p[i][0],ISR_p[i][1],
                         ISR_p[i][2],ISR_p[i][4]);
      double ISR_b1_mass = (stop1_b+ISR_tmp).M();
      double ISR_b2_mass = (stop2_b+ISR_tmp).M();
      double ISR_PAlongThrust =CalculatePAlongThrust( &ISR_tmp);
      h_2ISR_jetPt[icut]->Fill(ISR_tmp.Pt(), weight);
      h_2ISR_jetEta[icut]->Fill(ISR_tmp.Eta(), weight);
      h_2ISR_jet_b_MinMass[icut]->Fill( TMath::Min( ISR_b1_mass, ISR_b2_mass ) , weight);
      h_2ISR_jet_b_MaxMass[icut]->Fill( TMath::Max( ISR_b1_mass, ISR_b2_mass ) , weight);
      h_2ISR_PAlongThrust[icut]->Fill(ISR_PAlongThrust, weight);

      h_2ISR_pt_distop_pt[icut]->Fill(ISR_tmp.Pt(), distop.Pt(), weight);
      h_2ISR_pt_Met[icut]->Fill(ISR_tmp.Pt(), dixi.Pt(), weight);
      h_2ISR_PAlongThrust_Met[icut]->Fill(ISR_PAlongThrust, dixi.Pt(), weight);
      h_2ISR_pt_tt_pt[icut]->Fill(ISR_tmp.Pt(), (stop1_jets+stop2_jets).Pt(), weight);
      h_2ISR_pt_ISR_b_MinMass[icut]->Fill(ISR_tmp.Pt(), TMath::Min( ISR_b1_mass, ISR_b2_mass ) , weight);
      h_2ISR_pt_ISR_b_MaxMass[icut]->Fill(ISR_tmp.Pt(), TMath::Max( ISR_b1_mass, ISR_b2_mass ) , weight);
      h_2ISR_Met_ISR_b_MinMass[icut]->Fill(dixi.Pt(), TMath::Min( ISR_b1_mass, ISR_b2_mass ), weight);
      h_2ISR_Met_ISR_b_MaxMass[icut]->Fill(dixi.Pt(), TMath::Max( ISR_b1_mass, ISR_b2_mass ), weight);

      h_2ISR_pt_distop_pt[icut]->Fill(ISR_tmp.Pt(), distop.Pt(), weight);
      h_2ISR_pt_Met[icut]->Fill(ISR_tmp.Pt(), dixi.Pt(), weight);
      h_2ISR_PAlongThrust_Met[icut]->Fill(ISR_PAlongThrust, dixi.Pt(), weight);
      h_2ISR_pt_tt_pt[icut]->Fill(ISR_tmp.Pt(), (stop1_jets+stop2_jets).Pt(), weight);
      h_2ISR_pt_ISR_b_MinMass[icut]->Fill(ISR_tmp.Pt(), TMath::Min( ISR_b1_mass, ISR_b2_mass ) , weight);
      h_2ISR_pt_ISR_b_MaxMass[icut]->Fill(ISR_tmp.Pt(), TMath::Max( ISR_b1_mass, ISR_b2_mass ) , weight);
      h_2ISR_Met_ISR_b_MinMass[icut]->Fill(dixi.Pt(), TMath::Min( ISR_b1_mass, ISR_b2_mass ), weight);
      h_2ISR_Met_ISR_b_MaxMass[icut]->Fill(dixi.Pt(), TMath::Max( ISR_b1_mass, ISR_b2_mass ), weight);
    }
  }

  if (verbose) std::cout << "Doing Delta phi plot" << std::endl;
  float deltaPhi = dixi.DeltaPhi(ISR_total);
  h_ISR_MET_delphi[icut]->Fill(fabs(deltaPhi), weight);
  if (verbose) std::cout << "Doing Delta R plots" << std::endl;

  float delr_b1_w1 = stop1_b.DeltaR(stop1_w);
  if  (verbose) std::cout << "delr_b1_w1 is " << delr_b1_w1 << std::endl;
  h_delr_b1_w1[icut]->Fill(fabs(delr_b1_w1), weight);
  if (verbose) std::cout << "First one worked" << std::endl;

  float delr_stop1_b1 = stop1.DeltaR(stop1_b);
  h_delr_stop1_b1[icut]->Fill(fabs(delr_stop1_b1), weight);
  float delr_stop1_w1j1 = stop1.DeltaR(stop1_wj1);
  h_delr_stop1_w1j1[icut]->Fill(fabs(delr_stop1_w1j1), weight);
  float delr_stop1_w1j2 = stop1.DeltaR(stop1_wj2);
  h_delr_stop1_w1j2[icut]->Fill(fabs(delr_stop1_w1j2), weight);

  if (verbose) std::cout << "Stop1 jets are fine" << std::endl;

  float delr_b2_w2 = stop2_b.DeltaR(stop2_w);
  h_delr_b2_w2[icut]->Fill(fabs(delr_b2_w2), weight);
  float delr_stop2_b2 = stop2.DeltaR(stop2_b);
  h_delr_stop2_b2[icut]->Fill(fabs(delr_stop2_b2), weight);
  float delr_stop2_w2j1 = stop2.DeltaR(stop2_wj1);
  h_delr_stop2_w2j1[icut]->Fill(fabs(delr_stop2_w2j1), weight);
  float delr_stop2_w2j2 = stop2.DeltaR(stop2_wj2);
  h_delr_stop2_w2j2[icut]->Fill(fabs(delr_stop2_w2j2), weight);


  if (verbose) std::cout << "Stop2 jets are fine" << std::endl;

  float delr_ISR_stop1 = ISR_total.DeltaR(stop1);
  h_delr_ISR_stop1[icut]->Fill(fabs(delr_ISR_stop1), weight);
  float delr_ISR_b1 = ISR_total.DeltaR(stop1_b);
  h_delr_ISR_b1[icut]->Fill(fabs(delr_ISR_b1), weight);
  float delr_ISR_w1 = ISR_total.DeltaR(stop1_w);
  h_delr_ISR_w1[icut]->Fill(fabs(delr_ISR_w1), weight);
  float delr_ISR_w1j1 = ISR_total.DeltaR(stop1_wj1);
  h_delr_ISR_w1j1[icut]->Fill(fabs(delr_ISR_w1j1), weight);
  float delr_ISR_w1j2 = ISR_total.DeltaR(stop1_wj2);
  h_delr_ISR_w1j2[icut]->Fill(fabs(delr_ISR_w1j2), weight);

  if (verbose) std::cout << "Stop1 jets are fine" << std::endl;

  float delr_ISR_stop2 = ISR_total.DeltaR(stop2);
  h_delr_ISR_stop2[icut]->Fill(fabs(delr_ISR_stop2), weight);
  float delr_ISR_b2 = ISR_total.DeltaR(stop2_b);
  h_delr_ISR_b2[icut]->Fill(fabs(delr_ISR_b2), weight);
  float delr_ISR_w2 = ISR_total.DeltaR(stop2_w);
  h_delr_ISR_w2[icut]->Fill(fabs(delr_ISR_w2), weight);
  float delr_ISR_w2j1 = ISR_total.DeltaR(stop2_wj1);
  h_delr_ISR_w2j1[icut]->Fill(fabs(delr_ISR_w2j1), weight);
  float delr_ISR_w2j2 = ISR_total.DeltaR(stop2_wj2);
  h_delr_ISR_w2j2[icut]->Fill(fabs(delr_ISR_w2j2), weight);

  float delphi_ISR_MET = ISR_total.DeltaPhi(dixi);
  h_delphi_ISR_MET[icut]->Fill(fabs(delphi_ISR_MET), weight);

  //-----------------------------------------------------//
  
  if ( !FoundMinPThrustTop && !FoundMaxPThrustTop) {

    Ana_AllHad_2b_Thrust_LabFrame2_NegCone_W_minWDeltaM_NMissing[icut]->Fill(0.0, weight);

    double W_Met_DPhi     = fabs((WCand_LabFrame2_MinPThrust+WCand_LabFrame2_MaxPThrust).DeltaPhi(dixi));
    double W_Met_DPt      = (dixi-WCand_LabFrame2_MaxPThrust-WCand_LabFrame2_MinPThrust).Pt();
    double W_Pt           = (WCand_LabFrame2_MaxPThrust+WCand_LabFrame2_MinPThrust).Pt();

    double W_PThrust = CalculatePAlongThrust( (WCand_LabFrame2_MinPThrust+WCand_LabFrame2_MaxPThrust).Px(),
					      (WCand_LabFrame2_MinPThrust+WCand_LabFrame2_MaxPThrust).Py() );
    double Met_PThrust    = CalculatePAlongThrust( dixi.Pt()*cos(dixi.Phi()),       dixi.Pt()*sin(dixi.Phi()) );

    //    double TT_Mass = (TCand_TTFrame2_MinPThrust+TCand_TTFrame2_MaxPThrust).M();

    double TT_Mass = TTVect.M();


    double T_boost_theoretical = 2.*sqrt( TT_Mass*TT_Mass/4. - t_polemass*t_polemass ) / TT_Mass;

    Ana_AllHad_2b_Thrust_LabFrame2_MissingBothW_B_NegCone_W_minWDeltaM_WMet_DPhi_WMet_DEt_2D[icut]->Fill(W_Met_DPhi,  W_Met_DPt, weight);
    Ana_AllHad_2b_Thrust_LabFrame2_MissingBothW_B_NegCone_W_minWDeltaM_WMet_DPhi[icut]->Fill(            W_Met_DPhi, weight);
    Ana_AllHad_2b_Thrust_LabFrame2_MissingBothW_B_NegCone_W_minWDeltaM_WMet_DPt[icut]->Fill(             W_Met_DPt, weight);
    Ana_AllHad_2b_Thrust_LabFrame2_MissingBothW_B_NegCone_W_minWDeltaM_WMet_PThrust[icut]->Fill(         W_PThrust, weight);

  }
  if (  FoundMinPThrustTop && !FoundMaxPThrustTop ) {

    Ana_AllHad_2b_Thrust_LabFrame2_NegCone_W_minWDeltaM_NMissing[icut]->Fill(1.0);

    double B_MinP_TopF_P = BCand_TopFrame2_MinPThrust.P();
    double W_MinP_TopF_P = WCand_TopFrame2_MinPThrust.P();
    double BW_MinP_TopF_Angle = BCand_TopFrame2_MinPThrust.Vect().Angle( WCand_TopFrame2_MinPThrust.Vect() );

    double TBoost_MinP_TTF_Boost = TCand_TTFrame2_MinPThrust.BoostVector().Mag();
    double TBoost_MaxP_TTF_Boost = TCand_TTFrame2_MaxPThrust.BoostVector().Mag();

    double W_Mass_MinP = WCand_TTFrame2_MinPThrust.M();
    double T_Mass_MinP = TCand_TTFrame2_MinPThrust.M();
    double W_PThrust_MinP = CalculatePAlongThrust( WCand_LabFrame2_MinPThrust.Px(), WCand_LabFrame2_MinPThrust.Py() );
    double T_PThrust_MinP = CalculatePAlongThrust( TCand_LabFrame2_MinPThrust.Px(), TCand_LabFrame2_MinPThrust.Py() );

    // Missing W predicted pt and met value
    double W_Met_DPhi_MaxP     = fabs(WCand_LabFrame2_MaxPThrust.DeltaPhi(dixi));
    double W_Met_DPt_MaxP      = (dixi-WCand_LabFrame2_MaxPThrust).Pt();
    double W_Pt_MaxP           = WCand_LabFrame2_MaxPThrust.Pt();

    double T_PThrust_MaxP = CalculatePAlongThrust( TCand_LabFrame2_MaxPThrust.Px(), TCand_LabFrame2_MaxPThrust.Py() );
    double W_PThrust_MaxP = CalculatePAlongThrust( WCand_LabFrame2_MaxPThrust.Px(), WCand_LabFrame2_MaxPThrust.Py() );
    double Met_PThrust    = CalculatePAlongThrust( dixi.Pt()*cos(dixi.Phi()),       dixi.Pt()*sin(dixi.Phi()) );

    double TT_Mass = (TCand_TTFrame2_MinPThrust+TCand_TTFrame2_MaxPThrust).M();

    double T_boost_theoretical = 2.*sqrt( TT_Mass*TT_Mass/4. - t_polemass*t_polemass ) / TT_Mass;

    Ana_AllHad_2b_Thrust_TopFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_BMom_TopMass_2D[icut]->Fill(    B_MinP_TopF_P,      T_Mass_MinP , weight );
    Ana_AllHad_2b_Thrust_TopFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMom_TopMass_2D[icut]->Fill(    W_MinP_TopF_P,      T_Mass_MinP , weight );
    Ana_AllHad_2b_Thrust_TopFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_BWAngle_TopMass_2D[icut]->Fill( BW_MinP_TopF_Angle, T_Mass_MinP , weight );
    Ana_AllHad_2b_Thrust_TopFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_BMom[icut]->Fill(    B_MinP_TopF_P,      weight );
    Ana_AllHad_2b_Thrust_TopFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMom[icut]->Fill(    W_MinP_TopF_P,      weight );
    Ana_AllHad_2b_Thrust_TopFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_BWAngle[icut]->Fill( BW_MinP_TopF_Angle, weight );

    Ana_AllHad_2b_Thrust_TTFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_TBoost_TopMass_2D[icut]->Fill(      TBoost_MinP_TTF_Boost-T_boost_theoretical, T_Mass_MinP, weight );
    Ana_AllHad_2b_Thrust_TTFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_TBoost[icut]->Fill(      TBoost_MinP_TTF_Boost-T_boost_theoretical,  weight );

    Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_TopMass_TopPThrust_2D[icut]->Fill(T_PThrust_MinP, T_Mass_MinP, weight);
    Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMass_TopPThrust_2D[icut]->Fill(  T_PThrust_MinP, W_Mass_MinP, weight);

    Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_B_NegCone_W_minWDeltaM_TTMass[icut]->Fill(TT_Mass);

    Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMet_DPhi_WMet_DEt_2D[icut]->Fill(W_Met_DPhi_MaxP,  W_Met_DPt_MaxP, weight);
    Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMet_DPhi[icut]->Fill(            W_Met_DPhi_MaxP, weight);
    Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMet_DPt[icut]->Fill(             W_Met_DPt_MaxP, weight);
    Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMet_PThrust[icut]->Fill(         W_PThrust_MaxP, weight);
  }
  if ( !FoundMinPThrustTop &&  FoundMaxPThrustTop ) {

    Ana_AllHad_2b_Thrust_LabFrame2_NegCone_W_minWDeltaM_NMissing[icut]->Fill(2.0);

    double B_MaxP_TopF_P = BCand_TopFrame2_MaxPThrust.P();
    double W_MaxP_TopF_P = WCand_TopFrame2_MaxPThrust.P();
    double BW_MaxP_TopF_Angle = BCand_TopFrame2_MaxPThrust.Vect().Angle( WCand_TopFrame2_MaxPThrust.Vect() );

    double TBoost_MaxP_TTF_Boost = TCand_TTFrame2_MaxPThrust.BoostVector().Mag();
    double TBoost_MinP_TTF_Boost = TCand_TTFrame2_MinPThrust.BoostVector().Mag();

    double W_Mass_MaxP = WCand_TTFrame2_MaxPThrust.M();
    double T_Mass_MaxP = TCand_TTFrame2_MaxPThrust.M();
    double W_PThrust_MaxP = CalculatePAlongThrust( WCand_LabFrame2_MaxPThrust.Px(), WCand_LabFrame2_MaxPThrust.Py() );
    double T_PThrust_MaxP = CalculatePAlongThrust( TCand_LabFrame2_MaxPThrust.Px(), TCand_LabFrame2_MaxPThrust.Py() );

    // Missing W predicted pt and met value
    double W_Met_DPhi_MinP     = fabs(WCand_LabFrame2_MinPThrust.DeltaPhi(dixi));
    double W_Met_DPt_MinP      = (dixi-WCand_LabFrame2_MinPThrust).Pt();
    double W_Pt_MinP           = WCand_LabFrame2_MinPThrust.Pt();

    double T_PThrust_MinP = CalculatePAlongThrust( TCand_LabFrame2_MinPThrust.Px(), TCand_LabFrame2_MinPThrust.Py() );
    double W_PThrust_MinP = CalculatePAlongThrust( WCand_LabFrame2_MinPThrust.Px(), WCand_LabFrame2_MinPThrust.Py() );
    double Met_PThrust    = CalculatePAlongThrust( dixi.Pt()*cos(dixi.Phi()),       dixi.Pt()*sin(dixi.Phi()) );

    double TT_Mass = (TCand_TTFrame2_MaxPThrust+TCand_TTFrame2_MinPThrust).M();

    double T_boost_theoretical = 2.*sqrt( TT_Mass*TT_Mass/4. - t_polemass*t_polemass ) / TT_Mass;

    Ana_AllHad_2b_Thrust_TopFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_BMom_TopMass_2D[icut]->Fill(    B_MaxP_TopF_P,      T_Mass_MaxP , weight );
    Ana_AllHad_2b_Thrust_TopFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMom_TopMass_2D[icut]->Fill(    W_MaxP_TopF_P,      T_Mass_MaxP , weight );
    Ana_AllHad_2b_Thrust_TopFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_BWAngle_TopMass_2D[icut]->Fill( BW_MaxP_TopF_Angle, T_Mass_MaxP , weight );
    Ana_AllHad_2b_Thrust_TopFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_BMom[icut]->Fill(    B_MaxP_TopF_P,      weight );
    Ana_AllHad_2b_Thrust_TopFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMom[icut]->Fill(    W_MaxP_TopF_P,      weight );
    Ana_AllHad_2b_Thrust_TopFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_BWAngle[icut]->Fill( BW_MaxP_TopF_Angle, weight );

    Ana_AllHad_2b_Thrust_TTFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_TBoost_TopMass_2D[icut]->Fill(      TBoost_MaxP_TTF_Boost-T_boost_theoretical, T_Mass_MaxP , weight );
    Ana_AllHad_2b_Thrust_TTFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_TBoost[icut]->Fill(      TBoost_MaxP_TTF_Boost-T_boost_theoretical,  weight );

    Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_TopMass_TopPThrust_2D[icut]->Fill(T_PThrust_MaxP, T_Mass_MaxP, weight);
    Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMass_TopPThrust_2D[icut]->Fill(  T_PThrust_MaxP, W_Mass_MaxP, weight);

    Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_B_NegCone_W_minWDeltaM_TTMass[icut]->Fill(TT_Mass);

    Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMet_DPhi_WMet_DEt_2D[icut]->Fill(W_Met_DPhi_MinP,  W_Met_DPt_MinP, weight);
    Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMet_DPhi[icut]->Fill(            W_Met_DPhi_MinP, weight);
    Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMet_DPt[icut]->Fill(             W_Met_DPt_MinP, weight);
    Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMet_PThrust[icut]->Fill(         W_PThrust_MinP, weight);
  }
  if ( FoundMinPThrustTop && FoundMaxPThrustTop ) {

    Ana_AllHad_2b_Thrust_LabFrame2_NegCone_W_minWDeltaM_NMissing[icut]->Fill(3.0);

    double B_MinP_TopF_P = BCand_TopFrame2_MinPThrust.P();
    double W_MinP_TopF_P = WCand_TopFrame2_MinPThrust.P();
    double BW_MinP_TopF_Angle = BCand_TopFrame2_MinPThrust.Vect().Angle( WCand_TopFrame2_MinPThrust.Vect() );

    double B_MaxP_TopF_P = BCand_TopFrame2_MaxPThrust.P();
    double W_MaxP_TopF_P = WCand_TopFrame2_MaxPThrust.P();
    double BW_MaxP_TopF_Angle = BCand_TopFrame2_MaxPThrust.Vect().Angle( WCand_TopFrame2_MaxPThrust.Vect() );

    double TBoost_MinP_TTF_Boost = TCand_TTFrame2_MinPThrust.BoostVector().Mag();
    double TBoost_MaxP_TTF_Boost = TCand_TTFrame2_MaxPThrust.BoostVector().Mag();

    double W_Mass_MinP = WCand_TTFrame2_MinPThrust.M();
    double T_Mass_MinP = TCand_TTFrame2_MinPThrust.M();
    double W_PThrust_MinP = CalculatePAlongThrust( WCand_LabFrame2_MinPThrust.Px(), WCand_LabFrame2_MinPThrust.Py() );
    double T_PThrust_MinP = CalculatePAlongThrust( TCand_LabFrame2_MinPThrust.Px(), TCand_LabFrame2_MinPThrust.Py() );

    double W_Mass_MaxP = WCand_LabFrame2_MaxPThrust.M();
    double T_Mass_MaxP = TCand_LabFrame2_MaxPThrust.M();
    double W_PThrust_MaxP = CalculatePAlongThrust( WCand_LabFrame2_MaxPThrust.Px(), WCand_LabFrame2_MaxPThrust.Py() );
    double T_PThrust_MaxP = CalculatePAlongThrust( TCand_LabFrame2_MaxPThrust.Px(), TCand_LabFrame2_MaxPThrust.Py() );

    double TT_Mass = (TCand_TTFrame2_MinPThrust+TCand_TTFrame2_MaxPThrust).M();

    double T_boost_theoretical = 2.*sqrt( TT_Mass*TT_Mass/4. - t_polemass*t_polemass ) / TT_Mass;

    Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_BMom_TopMass_2D[icut]->Fill(    B_MinP_TopF_P,      T_Mass_MinP , weight );
    Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_WMom_TopMass_2D[icut]->Fill(    W_MinP_TopF_P,      T_Mass_MinP , weight );
    Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_BWAngle_TopMass_2D[icut]->Fill( BW_MinP_TopF_Angle, T_Mass_MinP , weight );
    Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_BMom_TopMass_2D[icut]->Fill(    B_MaxP_TopF_P,      T_Mass_MaxP , weight );
    Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_WMom_TopMass_2D[icut]->Fill(    W_MaxP_TopF_P,      T_Mass_MaxP , weight );
    Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_BWAngle_TopMass_2D[icut]->Fill( BW_MaxP_TopF_Angle, T_Mass_MaxP , weight );
    Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_BMom[icut]->Fill(    B_MinP_TopF_P,      weight );
    Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_WMom[icut]->Fill(    W_MinP_TopF_P,      weight );
    Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_BWAngle[icut]->Fill( BW_MinP_TopF_Angle, weight );
    Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_BMom[icut]->Fill(    B_MaxP_TopF_P,       weight );
    Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_WMom[icut]->Fill(    W_MaxP_TopF_P,       weight );
    Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_BWAngle[icut]->Fill( BW_MaxP_TopF_Angle,  weight );

    Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_TBoost_TopMass_2D[icut]->Fill(      TBoost_MinP_TTF_Boost-T_boost_theoretical, T_Mass_MinP , weight );
    Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_TBoost_TopMass_2D[icut]->Fill(      TBoost_MaxP_TTF_Boost-T_boost_theoretical, T_Mass_MaxP , weight );

    Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_TBoost[icut]->Fill(      TBoost_MinP_TTF_Boost-T_boost_theoretical,  weight );
    Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_TBoost[icut]->Fill(      TBoost_MaxP_TTF_Boost-T_boost_theoretical,  weight );

    Ana_AllHad_2b_Thrust_LabFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_TopMass_TopPThrust_2D[icut]->Fill(T_PThrust_MinP, T_Mass_MinP, weight);
    Ana_AllHad_2b_Thrust_LabFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_WMass_TopPThrust_2D[icut]->Fill(  T_PThrust_MinP, W_Mass_MinP, weight);
    Ana_AllHad_2b_Thrust_LabFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_TopMass_TopPThrust_2D[icut]->Fill(T_PThrust_MaxP, T_Mass_MaxP, weight);
    Ana_AllHad_2b_Thrust_LabFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_WMass_TopPThrust_2D[icut]->Fill(  T_PThrust_MaxP, W_Mass_MaxP, weight);

    Ana_AllHad_2b_Thrust_LabFrame2_FoundBoth_B_NegCone_W_minWDeltaM_TTMass[icut]->Fill(TT_Mass, weight);
    Ana_AllHad_2b_Thrust_LabFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_TopMass1_TopMass2_2D[icut]->Fill(T_Mass_MinP, T_Mass_MaxP, weight);
  }

  return;
}

void TruthxAODAnalysis_STop::FindThrustDir(){

  if (verbose) if (verbose) std::cout <<"finding thrust"<<std::endl;

  thrust_vec.SetXYZT(0,0,0,0);

  TString Formula("(abs(x*[0]+y*[1])+");
  TString tmp;

  uint nsize = 4+nISR;
  if ( nISR > 3 ) nsize = 7;
  for( uint i=1; i < nsize; i++ ) {
    tmp = TString(Form("abs(x*[%u]+y*[%u])+",2*i,2*i+1));
    Formula = Formula+tmp;
    }

  tmp = TString(Form("abs(x*[%u]+y*[%u]))",2*nsize,2*nsize+1));
  Formula = Formula+tmp;

  TF2 fcn("ThrustFunction",Formula.Data(),-1.,1.,-1.,1.);

  fcn.FixParameter(0, stop1_b.Px());
  fcn.FixParameter(1, stop1_b.Py());
  fcn.FixParameter(2, stop1_wj1.Px());
  fcn.FixParameter(3, stop1_wj1.Py());
  fcn.FixParameter(4, stop1_wj2.Px());
  fcn.FixParameter(5, stop1_wj2.Py());

  fcn.FixParameter(6, stop2_b.Px());
  fcn.FixParameter(7, stop2_b.Py());
  fcn.FixParameter(8, stop2_wj1.Px());
  fcn.FixParameter(9, stop2_wj1.Py());
  fcn.FixParameter(10, stop2_wj2.Px());
  fcn.FixParameter(11, stop2_wj2.Py());

  fcn.FixParameter(12, dixi.Px());
  fcn.FixParameter(13, dixi.Py());

  for (int i = 0; i<nISR; i++) {
    fcn.FixParameter(14+2*i, ISR_p[i][0]);
    fcn.FixParameter(15+2*i, ISR_p[i][1]);
  }
  /*
  if ( nISR > 1 ) {
    fcn.FixParameter(12, ISR_p[;
    fcn.FixParameter(13, ISR2.Py());
  }
  if ( nISR > 2 ) {
    fcn.FixParameter(14, ISR3.Px());
    fcn.FixParameter(15, ISR3.Py());
    }*/

  double bestX, bestY;
  fcn.Eval(0.5,0.5);
  fcn.GetMaximumXY(bestX,bestY);

  double total = sqrt(bestX*bestX+bestY*bestY);
  bestX = bestX/total;
  bestY = bestY/total;

  // point positive in the direction of the met                                                     
  if ( (dixi.Px()*bestX + dixi.Py()*bestY) < 0 ) {
    bestX = -bestX;
    bestY = -bestY;
  }

  thrust_vec.SetXYZT(bestX,bestY,0,0);

  double bestPerpX, bestPerpY;
  bestPerpX = 1.0 - bestX*bestX;
  bestPerpY = 0.0 - bestX*bestY;
  double totPerp = sqrt(bestPerpX*bestPerpX+bestPerpY*bestPerpY);
  bestPerpX = bestPerpX/totPerp;
  bestPerpY = bestPerpY/totPerp;

  //  define positive as cross product with positive result              
  if ( (bestX*bestPerpY - bestPerpX*bestY) < 0 ) {
    bestPerpX = - bestPerpX;
    bestPerpY = - bestPerpY;
  }

  thrust_perp_vec.SetXYZT(bestPerpX,bestPerpY,0,0);

  return;
}







EL::StatusCode TruthxAODAnalysis_STop :: postExecute ()
{
  // Here you do everything that needs to be done after the main event
  // processing.  This is typically very rare, particularly in user
  // code.  It is mainly used in implementing the NTupleSvc.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthxAODAnalysis_STop :: finalize ()
{
  // This method is the mirror image of initialize(), meaning it gets
  // called after the last event has been processed on the worker node
  // and allows you to finish up any objects you created in
  // initialize() before they are written to disk.  This is actually
  // fairly rare, since this happens separately for each worker node.
  // Most of the time you want to do your post-processing on the
  // submission node after all your histogram outputs have been
  // merged.  This is different from histFinalize() in that it only
  // gets called on worker nodes that processed input events.
  ps->Close();

  delete polreweight;

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthxAODAnalysis_STop :: histFinalize ()
{
  // This method is the mirror image of histInitialize(), meaning it
  // gets called after the last event has been processed on the worker
  // node and allows you to finish up any objects you created in
  // histInitialize() before they are written to disk.  This is
  // actually fairly rare, since this happens separately for each
  // worker node.  Most of the time you want to do your
  // post-processing on the submission node after all your histogram
  // outputs have been merged.  This is different from finalize() in
  // that it gets called on all worker nodes regardless of whether
  // they processed input events.

  
  return EL::StatusCode::SUCCESS;
}

//  LocalWords:  DeltaEta
