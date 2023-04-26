
#pragma once

#include <string>

#include "engine_synthSampler.h"
#include "engine_synthSamplerCello.h"
#include "engine_synthSamplerClarinet.h"
#include "engine_synthSamplerPiano.h"
#include "engine_synthSamplerAmbientLead.h"
#include "engine_synthSamplerAuthenticStrings.h"
#include "engine_synthSamplerBoesendorferGrandPiano.h"
#include "engine_synthSamplerCelesta.h"
#include "engine_synthSamplerClarinets.h"
#include "engine_synthSamplerClassicSuitcaseMk1.h"
#include "engine_synthSamplerCosmos.h"
#include "engine_synthSamplerDreamVoice.h"
#include "engine_synthSamplerDrivenSynthLead.h"
#include "engine_synthSamplerGlassMarimbaSoft.h"
#include "engine_synthSamplerIndianSitar.h"
#include "engine_synthSamplerJapaneseShakuhachiFlute.h"
#include "engine_synthSamplerKoto.h"
#include "engine_synthSamplerMagnificentDrone.h"
#include "engine_synthSamplerMysticVibes.h"
#include "engine_synthSamplerPowerFifths.h"
#include "engine_synthSamplerPulsingPatterns.h"
#include "engine_synthSamplerShootingStar.h"
#include "engine_synthSamplerTimeWarp.h"
#include "engine_synthSamplerTranquility.h"
#include "engine_synthSamplerVocalCluster.h"
#include "engine_synthSamplerZenGarden.h"

// handle the various sampler
struct MetaSampler {
   
   // to sync with the actual number of samples...
   static int getNbSamples() { return 26;};
   // to sync with biggest wave file
   static int getMaxLoopSize() { return 100000;};
   static std::string getSampleName(int sample) {
      switch(sample) {
      case 1:
         return "Cello";
      case 2:
         return "Clarinet";
      case 3:
         return "Piano";
      case 4:
         return "AmbientLead";
      case 5:
         return "AuthenticStrings";
      case 6:
         return "BoesendorferGrandPiano";
      case 7:
         return "Celesta";
      case 8:
         return "Clarinets";
      case 9:
         return "ClassicSuitcaseMk1";
      case 10:
         return "Cosmos";
      case 11:
         return "DreamVoice";
      case 12:
         return "DrivenSynthLead";
      case 13:
         return "GlassMarimbaSoft";
      case 14:
         return "IndianSitar";
      case 15:
         return "JapaneseShakuhachiFlute";
      case 16:
         return "Koto";
      case 17:
         return "MagnificentDrone";
      case 18:
         return "MysticVibes";
      case 19:
         return "PowerFifths";
      case 20:
         return "PulsingPatterns";
      case 21:
         return "ShootingStar";
      case 22:
         return "TimeWarp";
      case 23:
         return "Tranquility";
      case 24:
         return "VocalCluster";
      case 25:
         return "ZenGarden";
      case 0:
      default:
         return "Ocarina";
      }
   };

   // will (re)init corresponding processor upon change. return true if actually swiched
   bool switchTo(int sample);
   // wrapping functions
   void setSamplerate(float sr);
   void nbCables(int cables);
   void setNote(float gate, float voct, float vel, int c);
   bool getLoop();
   int getLoopStart();
   int getLoopEnd();
   void setLoop(bool loop, bool force = false);
   void setLoopStart(int loopS, bool force = false);
   void setLoopEnd(int loopE, bool folse = false);
   float process();

private:
   // all variants of the processor
   synthSampler_Processor_process_type processorOcarina;
   synthSamplerCello_Processor_process_type processorCello;
   synthSamplerClarinet_Processor_process_type processorClarinet;
   synthSamplerPiano_Processor_process_type processorPiano;
   synthSamplerAmbientLead_Processor_process_type processorAmbientLead;
   synthSamplerAuthenticStrings_Processor_process_type processorAuthenticStrings;
   synthSamplerBoesendorferGrandPiano_Processor_process_type processorBoesendorferGrandPiano;
   synthSamplerCelesta_Processor_process_type processorCelesta;
   synthSamplerClarinets_Processor_process_type processorClarinets;
   synthSamplerClassicSuitcaseMk1_Processor_process_type processorClassicSuitcaseMk1;
   synthSamplerCosmos_Processor_process_type processorCosmos;
   synthSamplerDreamVoice_Processor_process_type processorDreamVoice;
   synthSamplerDrivenSynthLead_Processor_process_type processorDrivenSynthLead;
   synthSamplerGlassMarimbaSoft_Processor_process_type processorGlassMarimbaSoft;
   synthSamplerIndianSitar_Processor_process_type processorIndianSitar;
   synthSamplerJapaneseShakuhachiFlute_Processor_process_type processorJapaneseShakuhachiFlute;
   synthSamplerKoto_Processor_process_type processorKoto;
   synthSamplerMagnificentDrone_Processor_process_type processorMagnificentDrone;
   synthSamplerMysticVibes_Processor_process_type processorMysticVibes;
   synthSamplerPowerFifths_Processor_process_type processorPowerFifths;
   synthSamplerPulsingPatterns_Processor_process_type processorPulsingPatterns;
   synthSamplerShootingStar_Processor_process_type processorShootingStar;
   synthSamplerTimeWarp_Processor_process_type processorTimeWarp;
   synthSamplerTranquility_Processor_process_type processorTranquility;
   synthSamplerVocalCluster_Processor_process_type processorVocalCluster;
   synthSamplerZenGarden_Processor_process_type processorZenGarden;
   // currently selected sample
   int selectedSample = -1;

   // initialize current processor
   void initProc();
};
