#ifndef MyAnalysis_TruthxAODAnalysis_STop_H
#define MyAnalysis_TruthxAODAnalysis_STop_H

#include <xAODBase/IParticleContainer.h>
#include <xAODEgamma/ElectronContainer.h>
#include <xAODEventInfo/EventInfo.h>
#include <xAODJet/JetContainer.h>
#include <xAODMissingET/MissingETAuxContainer.h>
#include <xAODMissingET/MissingETContainer.h>
#include <xAODMuon/MuonContainer.h>
#include "xAODTruth/TruthEventContainer.h"
#include "xAODTruth/TruthParticleContainer.h"
#include "xAODTruth/TruthVertexContainer.h"

#include <xAODRootAccess/TStore.h>
#include <xAODRootAccess/TEvent.h>

#include "xAODRootAccess/Init.h"
#include "xAODRootAccess/TEvent.h"

#include <StopPolarization/PolarizationReweight.h>

#include <EventLoop/Algorithm.h>

#include <TRandom3.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TTree.h>
#include <TF2.h>
#include <TF3.h>
#include <TPostScript.h>
#include <TArrow.h>
#include <TCanvas.h>
#include <TLatex.h>

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

namespace MyAnalysis_STop {

class TruthxAODAnalysis_STop : public EL::Algorithm
{
  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.
public:
  // float cutValue;



  // variables that don't get filled at submission time should be
  // protected from being send from the submission node to the worker
  // node (done by the )
public:

  TRandom3 rand; //!

  StopPolarization::PolarizationReweight *polreweight; //!

  TTree *myTree; //!
  TH1F *h_top_pt; //!
  int m_eventCounter; //!
  int count; //!
  std::string evt_display_name; //!
  TPostScript *ps; //!

  TH2F *h_TrueBoostDeltaMinP_MagVsAng; //!
  TH1F *h_TrueBoostDeltaMinPAng; //!
  TH1F *h_TrueBoostDeltaMinPMag; //!
  TH2F *h_TrueBoostDeltaMaxP_MagVsAng; //!
  TH1F *h_TrueBoostDeltaMaxPAng; //!
  TH1F *h_TrueBoostDeltaMaxPMag; //!

  TH1F *h_TrueTMinP_BW_DeltaAng; //!
  TH1F *h_TrueTMaxP_BW_DeltaAng; //!
  TH1F *h_TrueTMinP_BW_LostOtherW_DeltaAng; //! 
  TH1F *h_TrueTMaxP_BW_LostOtherW_DeltaAng; //! 

  TH1F *h_TrueTMinP_BW_DeltaPhi; //!               
  TH1F *h_TrueTMaxP_BW_DeltaPhi; //!               
  TH1F *h_TrueTMinP_BW_LostOtherW_DeltaPhi; //!    
  TH1F *h_TrueTMaxP_BW_LostOtherW_DeltaPhi; //!

  TH1F *h_TrueTMinP_BW_DeltaEta; //!               
  TH1F *h_TrueTMaxP_BW_DeltaEta; //!               
  TH1F *h_TrueTMinP_BW_LostOtherW_DeltaEta; //!    
  TH1F *h_TrueTMaxP_BW_LostOtherW_DeltaEta; //!

  TH1F *h_TrueTMinP_BW_DeltaTheta; //!               
  TH1F *h_TrueTMaxP_BW_DeltaTheta; //!               
  TH1F *h_TrueTMinP_BW_LostOtherW_DeltaTheta; //!    
  TH1F *h_TrueTMaxP_BW_LostOtherW_DeltaTheta; //!

  TH1F *h_TrueTMinP_BW_DeltaR; //!               
  TH1F *h_TrueTMaxP_BW_DeltaR; //!               
  TH1F *h_TrueTMinP_BW_LostOtherW_DeltaR; //!    
  TH1F *h_TrueTMaxP_BW_LostOtherW_DeltaR; //!

  TH1F *h_True_TTMass; //!

  TH1F *h_true_TMass_MinP; //!
  TH1F *h_true_TMass_MaxP; //!
  TH1F *h_true_WMass_MinP; //!
  TH1F *h_true_WMass_MaxP; //!
  TH1F *h_true_BWjetMass; //!

  TH1F *h_true_nWjetsLost; //!

  TH1F *h_stop1_w_jets_eta[7]; //!
  TH2F *h_stop1_w_jets_pt_eta[7]; //!
  TH2F *h_stop1_w_jets_p_eta[7]; //!

  TH1F *h_distop_mass[7]; //!
  TH1F *h_distop_pt[7]; //!
  TH1F *h_dixi_mass[7]; //!
  TH1F *h_stop1_b_w_mass[7]; //!
  TH1F *h_stop2_b_w_mass[7]; //!
  TH1F *h_stop1_pt[7]; //!
  TH1F *h_stop1_b_pt[7]; //!
  TH1F *h_stop1_wj1_pt[7]; //!
  TH1F *h_stop1_wj2_pt[7]; //!
  TH1F *h_stop1_pthrust[7]; //!
  TH1F *h_stop1_b_pthrust[7]; //!
  TH1F *h_stop1_wj1_pthrust[7]; //!
  TH1F *h_stop1_wj2_pthrust[7]; //!
  TH1F *h_stop1_wj_b_MinMass[7]; //!
  TH1F *h_stop1_wj_b_MaxMass[7]; //!
  TH1F *h_stop1_jets_pthrust[7]; //!
  TH1F *h_stop2_pt[7]; //!
  TH1F *h_stop2_b_pt[7]; //!
  TH1F *h_stop2_wj1_pt[7]; //!
  TH1F *h_stop2_wj2_pt[7]; //!
  TH1F *h_stop2_pthrust[7]; //!
  TH1F *h_stop2_b_pthrust[7]; //!
  TH1F *h_stop2_wj1_pthrust[7]; //!
  TH1F *h_stop2_wj2_pthrust[7]; //!
  TH1F *h_stop2_wj_b_MinMass[7]; //!
  TH1F *h_stop2_wj_b_MaxMass[7]; //!
  TH1F *h_stop2_jets_pthrust[7]; //!
  TH1F *h_dixi_pthrust[7]; //!
  TH1F *h_stop1_jets_pt_thrust[7]; //!
  TH1F *h_stop1_b_pt_thrust[7]; //!
  TH1F *h_stop2_jets_pt_thrust[7]; //!
  TH1F *h_stop2_b_pt_thrust[7]; //!
  TH2F *h_stop1_w_thrust2D[7]; //!
  TH2F *h_stop1_b_thrust2D[7]; //!
  TH2F *h_stop2_w_thrust2D[7]; //!
  TH2F *h_stop2_b_thrust2D[7]; //!
  TH1F *h_dixi_pt[7]; //!
  TH1F *h_ISR_MET_delphi[7]; //!

  TH1F *h_nISR[7]; //!

  TH1F *h_noISR_dixi_pt[7]; //!
  TH1F *h_noISR_tt_pt[7]; //!
  TH1F *h_noISR_distop_pt[7]; //!

  TH1F *h_1ISR_totalPt[7]; //!

  TH1F *h_1ISR_jetPt[7]; //!
  TH1F *h_1ISR_jetEta[7]; //!
  TH1F *h_1ISR_jet_b_MinMass[7]; //!
  TH1F *h_1ISR_jet_b_MaxMass[7]; //!
  TH1F *h_1ISR_PAlongThrust[7]; //!

  TH2F *h_1ISR_pt_distop_pt[7]; //!
  TH2F *h_1ISR_pt_Met[7]; //!
  TH2F *h_1ISR_PAlongThrust_Met[7]; //!
  TH2F *h_1ISR_pt_tt_pt[7]; //!
  TH2F *h_1ISR_pt_ISR_b_MinMass[7]; //!
  TH2F *h_1ISR_pt_ISR_b_MaxMass[7]; //!
  TH2F *h_1ISR_Met_ISR_b_MinMass[7]; //!
  TH2F *h_1ISR_Met_ISR_b_MaxMass[7]; //!

  TH1F *h_2ISR_totalPt[7]; //!

  TH1F *h_2ISR_jetPt[7]; //!
  TH1F *h_2ISR_jetEta[7]; //!
  TH1F *h_2ISR_jet_b_MinMass[7]; //!
  TH1F *h_2ISR_jet_b_MaxMass[7]; //!
  TH1F *h_2ISR_PAlongThrust[7]; //!

  TH2F *h_2ISR_pt_distop_pt[7]; //!      
  TH2F *h_2ISR_pt_Met[7]; //!            
  TH2F *h_2ISR_PAlongThrust_Met[7]; //!  
  TH2F *h_2ISR_pt_tt_pt[7]; //!          
  TH2F *h_2ISR_pt_ISR_b_MinMass[7]; //!  
  TH2F *h_2ISR_pt_ISR_b_MaxMass[7]; //!  
  TH2F *h_2ISR_Met_ISR_b_MinMass[7]; //! 
  TH2F *h_2ISR_Met_ISR_b_MaxMass[7]; //! 

  TH1F *h_delr_b1_w1[7]; //!
  TH1F *h_delr_stop1_b1[7]; //!
  TH1F *h_delr_stop1_w1j1[7]; //!
  TH1F *h_delr_stop1_w1j2[7]; //!
  
  TH1F *h_delr_b2_w2[7]; //!
  TH1F *h_delr_stop2_b2[7]; //!
  TH1F *h_delr_stop2_w2j1[7]; //!
  TH1F *h_delr_stop2_w2j2[7]; //!

  TH1F *h_delr_ISR_stop1[7]; //!
  TH1F *h_delr_ISR_b1[7]; //!
  TH1F *h_delr_ISR_w1[7]; //!
  TH1F *h_delr_ISR_w1j1[7]; //!
  TH1F *h_delr_ISR_w1j2[7]; //!

  TH1F *h_delr_ISR_stop2[7]; //!
  TH1F *h_delr_ISR_b2[7]; //!
  TH1F *h_delr_ISR_w2[7]; //!
  TH1F *h_delr_ISR_w2j1[7]; //!
  TH1F *h_delr_ISR_w2j2[7]; //!

  TH1F *h_delphi_ISR_MET[7]; //!

  TH1F *Ana_AllHad_2b_Thrust_LabFrame2_NegCone_W_minWDeltaM_NMissing[7]; //!

  TH2F *Ana_AllHad_2b_Thrust_LabFrame2_MissingBothW_B_NegCone_W_minWDeltaM_WMet_DPhi_WMet_DEt_2D[7]; //!
  TH1F *Ana_AllHad_2b_Thrust_LabFrame2_MissingBothW_B_NegCone_W_minWDeltaM_WMet_DPhi[7]; //!
  TH1F *Ana_AllHad_2b_Thrust_LabFrame2_MissingBothW_B_NegCone_W_minWDeltaM_WMet_DPt[7]; //!
  TH1F *Ana_AllHad_2b_Thrust_LabFrame2_MissingBothW_B_NegCone_W_minWDeltaM_WMet_PThrust[7]; //!

  TH2F *Ana_AllHad_2b_Thrust_TopFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_BMom_TopMass_2D[7]; //!
  TH2F *Ana_AllHad_2b_Thrust_TopFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMom_TopMass_2D[7]; //!
  TH2F *Ana_AllHad_2b_Thrust_TopFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_BWAngle_TopMass_2D[7]; //!
  TH1F *Ana_AllHad_2b_Thrust_TopFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_BMom[7]; //!
  TH1F *Ana_AllHad_2b_Thrust_TopFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMom[7]; //!
  TH1F *Ana_AllHad_2b_Thrust_TopFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_BWAngle[7]; //!

  TH2F *Ana_AllHad_2b_Thrust_TTFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_TBoost_TopMass_2D[7]; //!
  TH2F *Ana_AllHad_2b_Thrust_TTFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_ThrustAngle_TopMass_2D[7]; //!

  TH1F *Ana_AllHad_2b_Thrust_TTFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_TBoost[7]; //!
  TH1F *Ana_AllHad_2b_Thrust_TTFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_ThrustAngle[7]; //!

  TH2F *Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_TopMass_TopPThrust_2D[7]; //!
  TH2F *Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMass_TopPThrust_2D[7]; //!
  TH1F *Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_B_NegCone_W_minWDeltaM_TTMass[7]; //!

  TH2F *Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMet_DPhi_WMet_DEt_2D[7]; //!
  TH1F *Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMet_DPhi[7]; //!
  TH1F *Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMet_DPt[7]; //!
  TH1F *Ana_AllHad_2b_Thrust_LabFrame2_MissingMaxPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMet_PThrust[7]; //!

  TH2F *Ana_AllHad_2b_Thrust_TopFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_BMom_TopMass_2D[7]; //!
  TH2F *Ana_AllHad_2b_Thrust_TopFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMom_TopMass_2D[7]; //!
  TH2F *Ana_AllHad_2b_Thrust_TopFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_BWAngle_TopMass_2D[7]; //!
  TH1F *Ana_AllHad_2b_Thrust_TopFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_BMom[7]; //!
  TH1F *Ana_AllHad_2b_Thrust_TopFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMom[7]; //!
  TH1F *Ana_AllHad_2b_Thrust_TopFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_BWAngle[7]; //!

  TH2F *Ana_AllHad_2b_Thrust_TTFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_TBoost_TopMass_2D[7]; //!
  TH2F *Ana_AllHad_2b_Thrust_TTFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_ThrustAngle_TopMass_2D[7]; //!

  TH1F *Ana_AllHad_2b_Thrust_TTFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_TBoost[7]; //!
  TH1F *Ana_AllHad_2b_Thrust_TTFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_ThrustAngle[7]; //!

  TH2F *Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_TopMass_TopPThrust_2D[7]; //!
  TH2F *Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_MaxPThrust_B_NegCone_W_minWDeltaM_WMass_TopPThrust_2D[7]; //!
  TH1F *Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_B_NegCone_W_minWDeltaM_TTMass[7]; //!

  TH2F *Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMet_DPhi_WMet_DEt_2D[7]; //!
  TH1F *Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMet_DPhi[7]; //!
  TH1F *Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMet_DPt[7]; //!
  TH1F *Ana_AllHad_2b_Thrust_LabFrame2_MissingMinPThrust_MinPThrust_B_NegCone_W_minWDeltaM_WMet_PThrust[7]; //!

  TH2F *Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_BMom_TopMass_2D[7]; //!
  TH2F *Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_WMom_TopMass_2D[7]; //!
  TH2F *Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_BWAngle_TopMass_2D[7]; //!
  TH2F *Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_BMom_TopMass_2D[7]; //!
  TH2F *Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_WMom_TopMass_2D[7]; //!
  TH2F *Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_BWAngle_TopMass_2D[7]; //!
  TH1F *Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_BMom[7]; //!
  TH1F *Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_WMom[7]; //!
  TH1F *Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_BWAngle[7]; //!
  TH1F *Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_BMom[7]; //!
  TH1F *Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_WMom[7]; //!
  TH1F *Ana_AllHad_2b_Thrust_TopFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_BWAngle[7]; //!


  TH2F *Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_TBoost_TopMass_2D[7]; //!
  TH2F *Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_ThrustAngle_TopMass_2D[7]; //!
  TH2F *Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_TBoost_TopMass_2D[7]; //!
  TH2F *Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_ThrustAngle_TopMass_2D[7]; //!

  TH1F *Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_TBoost[7]; //!
  TH1F *Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_ThrustAngle[7]; //!
  TH1F *Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_TBoost[7]; //!
  TH1F *Ana_AllHad_2b_Thrust_TTFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_ThrustAngle[7]; //!

  TH2F *Ana_AllHad_2b_Thrust_LabFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_TopMass_TopPThrust_2D[7]; //!
  TH2F *Ana_AllHad_2b_Thrust_LabFrame2_FoundBoth_MinPThrust_B_NegCone_W_minWDeltaM_WMass_TopPThrust_2D[7]; //!
  TH2F *Ana_AllHad_2b_Thrust_LabFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_TopMass_TopPThrust_2D[7]; //!
  TH2F *Ana_AllHad_2b_Thrust_LabFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_WMass_TopPThrust_2D[7]; //!
  TH2F *Ana_AllHad_2b_Thrust_LabFrame2_FoundBoth_MaxPThrust_B_NegCone_W_minWDeltaM_TopMass1_TopMass2_2D[7]; //!
  TH1F *Ana_AllHad_2b_Thrust_LabFrame2_FoundBoth_B_NegCone_W_minWDeltaM_TTMass[7]; //!

  TLorentzVector thrust_vec; //!
  TLorentzVector thrust_perp_vec; //!

  TLorentzVector stopxi_tmp; //!
  TLorentzVector stopb_tmp; //!
  TLorentzVector stopwj1_tmp; //!
  TLorentzVector stopwj2_tmp; //!

  TLorentzVector ditop; //!
  TLorentzVector stop1_t; //!
  TLorentzVector stop2_t; //!

  TLorentzVector stop1; //!
  TLorentzVector stop1_b; //!
  TLorentzVector stop1_wj1; //!
  TLorentzVector stop1_wj2; //!
  TLorentzVector stop1_xi; //!
  TLorentzVector stop2; //!
  TLorentzVector stop2_b; //!
  TLorentzVector stop2_wj1; //!
  TLorentzVector stop2_wj2; //!
  TLorentzVector stop2_xi; //!

  TLorentzVector distop; //!
  TLorentzVector dixi; //!
  TLorentzVector stop1_jets; //!
  TLorentzVector stop2_jets; //!
  TLorentzVector stop1_w; //!
  TLorentzVector stop2_w; //!

  TLorentzVector ISR_total; //!

  TVector3 B1_3vec; //!
  TVector3 B2_3vec; //!

  TVector3 k_3vec_u; //!
  TVector3 B1_perp_k; //!

  TVector3 B1_cross_k; //!
  TVector3 T_Calc_Boost_Vect1; //!
  TVector3 T_Calc_Boost_Vect2; //!

  TLorentzVector BCand_TopFrame2_MinPThrust; //!
  TLorentzVector WCand_TopFrame2_MinPThrust; //!
  TLorentzVector WCand_j1_TopFrame2_MinPThrust; //!
  TLorentzVector WCand_j2_TopFrame2_MinPThrust; //!

  TLorentzVector BCand_TopFrame2_MaxPThrust; //!
  TLorentzVector WCand_TopFrame2_MaxPThrust; //!
  TLorentzVector WCand_j1_TopFrame2_MaxPThrust; //!
  TLorentzVector WCand_j2_TopFrame2_MaxPThrust; //!

  TLorentzVector WCand_TTFrame2_MinPThrust; //!
  TLorentzVector TCand_TTFrame2_MinPThrust; //!
  TLorentzVector WCand_TTFrame2_MaxPThrust; //!
  TLorentzVector TCand_TTFrame2_MaxPThrust; //!

  TLorentzVector WCand_LabFrame2_MinPThrust; //!
  TLorentzVector TCand_LabFrame2_MinPThrust; //!
  TLorentzVector WCand_LabFrame2_MaxPThrust; //!
  TLorentzVector TCand_LabFrame2_MaxPThrust; //!

  bool FoundMaxPThrustTop; //!
  bool FoundMinPThrustTop; //! 

  double w_polemass; //!
  double b_polemass; //!
  double t_polemass; //!
  double t_reduced_mass; //!
  double expected_b_momentum; //!

  TLorentzVector TTVect; //!
  std::vector<TLorentzVector> AllJets_Vec; //!
  std::vector<int> AllJets_Lost; //!

  std::vector <std::vector<float>> ISR_p; //!

  bool isMC; //!
  bool verbose; //!
  int nISR; //! 
  double GeV; //!
  bool isStop1Had; //!
  bool isStop2Had; //!
  bool plotEvent; //!

  // this is a standard constructor
  TruthxAODAnalysis_STop ();

  // these are the functions inherited from Algorithm
  virtual EL::StatusCode setupJob (EL::Job& job);
  virtual EL::StatusCode fileExecute ();
  virtual EL::StatusCode histInitialize ();
  //  virtual EL::StatusCode changeInput (bool firstFile);
  virtual EL::StatusCode initialize ();
  virtual EL::StatusCode execute ();
  virtual EL::StatusCode postExecute ();
  virtual EL::StatusCode finalize ();
  virtual EL::StatusCode histFinalize ();

  int PlotTruth_SoftTop(TVector3 boost1, TVector3 boost2, double weight);
  void setEvtDisplay(std::string eps);
  void DrawEvtDisplay();
  void plot_signal(int icut, double weight);
  void SetVerbose(int i);
  bool FindSoftTop(int b_top_index, int b_othertop_index);
  void FindThrustDir();
  double CalculatePAlongThrust( double px, double py );
  double CalculatePAlongThrust( TLorentzVector *Vec );
  bool Find_STopDecayProducts( const xAOD::TruthParticle* particle, 
			       TLorentzVector *Top_tmp,
			       TLorentzVector *Xi_tmp, TLorentzVector *B_tmp,
			       TLorentzVector *WJ1_tmp, TLorentzVector *WJ2_tmp );
  bool Find_TopDecayProducts( const xAOD::TruthParticle* particle,
			      TLorentzVector *B_tmp,
			      TLorentzVector *WJ1_tmp, TLorentzVector *WJ2_tmp );

  bool Find_WDecayProducts( const xAOD::TruthParticle* particle, 
			    TLorentzVector *WJ1_tmp, TLorentzVector *WJ2_tmp );

  // this is needed to distribute the algorithm to the workers
  ClassDef(TruthxAODAnalysis_STop, 1);
};

}

#endif
