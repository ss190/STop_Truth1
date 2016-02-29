#include "xAODRootAccess/Init.h"
#include "SampleHandler/SampleHandler.h"
#include "SampleHandler/ScanDir.h"
#include "SampleHandler/ToolsDiscovery.h"
#include "EventLoop/Job.h"
#include "EventLoop/DirectDriver.h"
#include "SampleHandler/DiskListLocal.h"
#include <TSystem.h>


#include "MyAnalysis/TruthxAODAnalysis_STop.h"

using namespace MyAnalysis_STop;

int main( int argc, char* argv[] ) {
        
  int nEvt = -1;
  std::string input;
  std::string output="output";
  std::string event_display = "event_display.eps";
  int verbose = 0;

  /** Read inputs to program */
  for(int i = 1; i < argc; i++) {
    if      (strcmp(argv[i], "-n") == 0) nEvt   = atoi(argv[++i]);
    else if (strcmp(argv[i], "-i") == 0) input  = argv[++i];
    else if (strcmp(argv[i], "-o") == 0) output = argv[++i];
    else if (strcmp(argv[i], "-v") == 0) verbose = atoi(argv[++i]);
    else if (strcmp(argv[i], "-e") == 0) event_display = argv[++i];
    else {
      return 0;
    }
  }

  // Take the submit directory from the input if provided:
  std::string submitDir = output;

  // Set up the job for xAOD access:
  xAOD::Init().ignore();

  // Construct the samples to run on:
  SH::SampleHandler sh;

  // use SampleHandler to scan all of the subdirectories of a directory for particular MC single file:
  const char* inputFilePath = gSystem->ExpandPathName (input.c_str());
  SH::ScanDir().filePattern("*.root*").scan(sh, inputFilePath);

  // Set the name of the input TTree. It's always "CollectionTree"
  // for xAOD files.
  sh.setMetaString( "nc_tree", "CollectionTree" );

  // Print what we found:
  sh.print();

  // Create an EventLoop job:
  EL::Job job;
  job.sampleHandler( sh );
  if ( nEvt > 0 ) {
    job.options()->setDouble (EL::Job::optMaxEvents, nEvt);
  }
 
  // Add our analysis to the job:
  TruthxAODAnalysis_STop* alg = new TruthxAODAnalysis_STop();
  alg->SetVerbose(verbose);
  alg->setEvtDisplay(event_display);
  job.algsAdd( alg );

  // Run the job using the local/direct driver:
  EL::DirectDriver driver;
  driver.submit( job, submitDir );

  return 0;
}
