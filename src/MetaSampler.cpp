
#include "MetaSampler.hpp"

bool MetaSampler::switchTo(int sample) {
  bool switched = false;
  if (sample < 0) {
    sample = 0;
  } else if (sample > getNbSamples()-1) {
    sample = getNbSamples()-1;
  }
  if (sample != selectedSample) {
      selectedSample = sample;
      initProc();
      switched = true;
   }
  return switched;
}

void MetaSampler::setSamplerate(float sr) {
   switch(selectedSample) {
   case 1:
      synthSamplerCello_Processor_setSamplerate(processorCello, float_to_fix(sr));
      break;
   case 2:
      synthSamplerClarinet_Processor_setSamplerate(processorClarinet, float_to_fix(sr));
      break;
   case 3:
      synthSamplerPiano_Processor_setSamplerate(processorPiano, float_to_fix(sr));
      break;
   case 4:
      synthSamplerAmbientLead_Processor_setSamplerate(processorAmbientLead, float_to_fix(sr));
      break;
   case 5:
      synthSamplerAuthenticStrings_Processor_setSamplerate(processorAuthenticStrings, float_to_fix(sr));
      break;
   case 6:
      synthSamplerBoesendorferGrandPiano_Processor_setSamplerate(processorBoesendorferGrandPiano, float_to_fix(sr));
      break;
   case 7:
      synthSamplerCelesta_Processor_setSamplerate(processorCelesta, float_to_fix(sr));
      break;
   case 8:
      synthSamplerClarinets_Processor_setSamplerate(processorClarinets, float_to_fix(sr));
      break;
   case 9:
      synthSamplerClassicSuitcaseMk1_Processor_setSamplerate(processorClassicSuitcaseMk1, float_to_fix(sr));
      break;
   case 10:
      synthSamplerCosmos_Processor_setSamplerate(processorCosmos, float_to_fix(sr));
      break;
   case 11:
      synthSamplerDreamVoice_Processor_setSamplerate(processorDreamVoice, float_to_fix(sr));
      break;
   case 12:
      synthSamplerDrivenSynthLead_Processor_setSamplerate(processorDrivenSynthLead, float_to_fix(sr));
      break;
   case 13:
      synthSamplerGlassMarimbaSoft_Processor_setSamplerate(processorGlassMarimbaSoft, float_to_fix(sr));
      break;
   case 14:
      synthSamplerIndianSitar_Processor_setSamplerate(processorIndianSitar, float_to_fix(sr));
      break;
   case 15:
      synthSamplerJapaneseShakuhachiFlute_Processor_setSamplerate(processorJapaneseShakuhachiFlute, float_to_fix(sr));
      break;
   case 16:
      synthSamplerKoto_Processor_setSamplerate(processorKoto, float_to_fix(sr));
      break;
   case 17:
      synthSamplerMagnificentDrone_Processor_setSamplerate(processorMagnificentDrone, float_to_fix(sr));
      break;
   case 18:
      synthSamplerMysticVibes_Processor_setSamplerate(processorMysticVibes, float_to_fix(sr));
      break;
   case 19:
      synthSamplerPowerFifths_Processor_setSamplerate(processorPowerFifths, float_to_fix(sr));
      break;
   case 20:
      synthSamplerPulsingPatterns_Processor_setSamplerate(processorPulsingPatterns, float_to_fix(sr));
      break;
   case 21:
      synthSamplerShootingStar_Processor_setSamplerate(processorShootingStar, float_to_fix(sr));
      break;
   case 22:
      synthSamplerTimeWarp_Processor_setSamplerate(processorTimeWarp, float_to_fix(sr));
      break;
   case 23:
      synthSamplerTranquility_Processor_setSamplerate(processorTranquility, float_to_fix(sr));
      break;
   case 24:
      synthSamplerVocalCluster_Processor_setSamplerate(processorVocalCluster, float_to_fix(sr));
      break;
   case 25:
      synthSamplerZenGarden_Processor_setSamplerate(processorZenGarden, float_to_fix(sr));
      break;
   case 0:
   default:
      synthSampler_Processor_setSamplerate(processorOcarina, float_to_fix(sr));
      break;
   }
}

void MetaSampler::nbCables(int cables) {
   switch(selectedSample) {
   case 1:
      synthSamplerCello_Processor_nbCables(processorCello, cables);
      break;
   case 2:
      synthSamplerClarinet_Processor_nbCables(processorClarinet, cables);
      break;
   case 3:
      synthSamplerPiano_Processor_nbCables(processorPiano, cables);
      break;
   case 4:
      synthSamplerAmbientLead_Processor_nbCables(processorAmbientLead, cables);
      break;
   case 5:
      synthSamplerAuthenticStrings_Processor_nbCables(processorAuthenticStrings, cables);
      break;
   case 6:
      synthSamplerBoesendorferGrandPiano_Processor_nbCables(processorBoesendorferGrandPiano, cables);
      break;
   case 7:
      synthSamplerCelesta_Processor_nbCables(processorCelesta, cables);
      break;
   case 8:
      synthSamplerClarinets_Processor_nbCables(processorClarinets, cables);
      break;
   case 9:
      synthSamplerClassicSuitcaseMk1_Processor_nbCables(processorClassicSuitcaseMk1, cables);
      break;
   case 10:
      synthSamplerCosmos_Processor_nbCables(processorCosmos, cables);
      break;
   case 11:
      synthSamplerDreamVoice_Processor_nbCables(processorDreamVoice, cables);
      break;
   case 12:
      synthSamplerDrivenSynthLead_Processor_nbCables(processorDrivenSynthLead, cables);
      break;
   case 13:
      synthSamplerGlassMarimbaSoft_Processor_nbCables(processorGlassMarimbaSoft, cables);
      break;
   case 14:
      synthSamplerIndianSitar_Processor_nbCables(processorIndianSitar, cables);
      break;
   case 15:
      synthSamplerJapaneseShakuhachiFlute_Processor_nbCables(processorJapaneseShakuhachiFlute, cables);
      break;
   case 16:
      synthSamplerKoto_Processor_nbCables(processorKoto, cables);
      break;
   case 17:
      synthSamplerMagnificentDrone_Processor_nbCables(processorMagnificentDrone, cables);
      break;
   case 18:
      synthSamplerMysticVibes_Processor_nbCables(processorMysticVibes, cables);
      break;
   case 19:
      synthSamplerPowerFifths_Processor_nbCables(processorPowerFifths, cables);
      break;
   case 20:
      synthSamplerPulsingPatterns_Processor_nbCables(processorPulsingPatterns, cables);
      break;
   case 21:
      synthSamplerShootingStar_Processor_nbCables(processorShootingStar, cables);
      break;
   case 22:
      synthSamplerTimeWarp_Processor_nbCables(processorTimeWarp, cables);
      break;
   case 23:
      synthSamplerTranquility_Processor_nbCables(processorTranquility, cables);
      break;
   case 24:
      synthSamplerVocalCluster_Processor_nbCables(processorVocalCluster, cables);
      break;
   case 25:
      synthSamplerZenGarden_Processor_nbCables(processorZenGarden, cables);
      break;
   case 0:
   default:
      synthSampler_Processor_nbCables(processorOcarina, cables);
      break;
   }
}

int MetaSampler::getSize() {
   switch(selectedSample) {
   case 1:
     return synthSamplerCello_Processor_getSize(processorCello);
   case 2:
     return synthSamplerClarinet_Processor_getSize(processorClarinet);
   case 3:
     return synthSamplerPiano_Processor_getSize(processorPiano);
   case 4:
     return synthSamplerAmbientLead_Processor_getSize(processorAmbientLead);
   case 5:
     return synthSamplerAuthenticStrings_Processor_getSize(processorAuthenticStrings);
   case 6:
     return synthSamplerBoesendorferGrandPiano_Processor_getSize(processorBoesendorferGrandPiano);
   case 7:
     return synthSamplerCelesta_Processor_getSize(processorCelesta);
   case 8:
     return synthSamplerClarinets_Processor_getSize(processorClarinets);
   case 9:
     return synthSamplerClassicSuitcaseMk1_Processor_getSize(processorClassicSuitcaseMk1);
   case 10:
     return synthSamplerCosmos_Processor_getSize(processorCosmos);
   case 11:
     return synthSamplerDreamVoice_Processor_getSize(processorDreamVoice);
   case 12:
     return synthSamplerDrivenSynthLead_Processor_getSize(processorDrivenSynthLead);
   case 13:
     return synthSamplerGlassMarimbaSoft_Processor_getSize(processorGlassMarimbaSoft);
   case 14:
     return synthSamplerIndianSitar_Processor_getSize(processorIndianSitar);
   case 15:
     return synthSamplerJapaneseShakuhachiFlute_Processor_getSize(processorJapaneseShakuhachiFlute);
   case 16:
     return synthSamplerKoto_Processor_getSize(processorKoto);
   case 17:
     return synthSamplerMagnificentDrone_Processor_getSize(processorMagnificentDrone);
   case 18:
     return synthSamplerMysticVibes_Processor_getSize(processorMysticVibes);
   case 19:
     return synthSamplerPowerFifths_Processor_getSize(processorPowerFifths);
   case 20:
     return synthSamplerPulsingPatterns_Processor_getSize(processorPulsingPatterns);
   case 21:
     return synthSamplerShootingStar_Processor_getSize(processorShootingStar);
   case 22:
     return synthSamplerTimeWarp_Processor_getSize(processorTimeWarp);
   case 23:
     return synthSamplerTranquility_Processor_getSize(processorTranquility);
   case 24:
     return synthSamplerVocalCluster_Processor_getSize(processorVocalCluster);
   case 25:
     return synthSamplerZenGarden_Processor_getSize(processorZenGarden);
   case 0:
   default:
     return synthSampler_Processor_getSize(processorOcarina);
   }
}

bool MetaSampler::getLoop() {
   switch(selectedSample) {
   case 1:
     return synthSamplerCello_Processor_getLoop(processorCello);
   case 2:
     return synthSamplerClarinet_Processor_getLoop(processorClarinet);
   case 3:
     return synthSamplerPiano_Processor_getLoop(processorPiano);
   case 4:
     return synthSamplerAmbientLead_Processor_getLoop(processorAmbientLead);
   case 5:
     return synthSamplerAuthenticStrings_Processor_getLoop(processorAuthenticStrings);
   case 6:
     return synthSamplerBoesendorferGrandPiano_Processor_getLoop(processorBoesendorferGrandPiano);
   case 7:
     return synthSamplerCelesta_Processor_getLoop(processorCelesta);
   case 8:
     return synthSamplerClarinets_Processor_getLoop(processorClarinets);
   case 9:
     return synthSamplerClassicSuitcaseMk1_Processor_getLoop(processorClassicSuitcaseMk1);
   case 10:
     return synthSamplerCosmos_Processor_getLoop(processorCosmos);
   case 11:
     return synthSamplerDreamVoice_Processor_getLoop(processorDreamVoice);
   case 12:
     return synthSamplerDrivenSynthLead_Processor_getLoop(processorDrivenSynthLead);
   case 13:
     return synthSamplerGlassMarimbaSoft_Processor_getLoop(processorGlassMarimbaSoft);
   case 14:
     return synthSamplerIndianSitar_Processor_getLoop(processorIndianSitar);
   case 15:
     return synthSamplerJapaneseShakuhachiFlute_Processor_getLoop(processorJapaneseShakuhachiFlute);
   case 16:
     return synthSamplerKoto_Processor_getLoop(processorKoto);
   case 17:
     return synthSamplerMagnificentDrone_Processor_getLoop(processorMagnificentDrone);
   case 18:
     return synthSamplerMysticVibes_Processor_getLoop(processorMysticVibes);
   case 19:
     return synthSamplerPowerFifths_Processor_getLoop(processorPowerFifths);
   case 20:
     return synthSamplerPulsingPatterns_Processor_getLoop(processorPulsingPatterns);
   case 21:
     return synthSamplerShootingStar_Processor_getLoop(processorShootingStar);
   case 22:
     return synthSamplerTimeWarp_Processor_getLoop(processorTimeWarp);
   case 23:
     return synthSamplerTranquility_Processor_getLoop(processorTranquility);
   case 24:
     return synthSamplerVocalCluster_Processor_getLoop(processorVocalCluster);
   case 25:
     return synthSamplerZenGarden_Processor_getLoop(processorZenGarden);
   case 0:
   default:
     return synthSampler_Processor_getLoop(processorOcarina);
   }
}

int MetaSampler::getLoopStart() {
   switch(selectedSample) {
   case 1:
     return synthSamplerCello_Processor_getLoopStart(processorCello);
   case 2:
     return synthSamplerClarinet_Processor_getLoopStart(processorClarinet);
   case 3:
     return synthSamplerPiano_Processor_getLoopStart(processorPiano);
   case 4:
     return synthSamplerAmbientLead_Processor_getLoopStart(processorAmbientLead);
   case 5:
     return synthSamplerAuthenticStrings_Processor_getLoopStart(processorAuthenticStrings);
   case 6:
     return synthSamplerBoesendorferGrandPiano_Processor_getLoopStart(processorBoesendorferGrandPiano);
   case 7:
     return synthSamplerCelesta_Processor_getLoopStart(processorCelesta);
   case 8:
     return synthSamplerClarinets_Processor_getLoopStart(processorClarinets);
   case 9:
     return synthSamplerClassicSuitcaseMk1_Processor_getLoopStart(processorClassicSuitcaseMk1);
   case 10:
     return synthSamplerCosmos_Processor_getLoopStart(processorCosmos);
   case 11:
     return synthSamplerDreamVoice_Processor_getLoopStart(processorDreamVoice);
   case 12:
     return synthSamplerDrivenSynthLead_Processor_getLoopStart(processorDrivenSynthLead);
   case 13:
     return synthSamplerGlassMarimbaSoft_Processor_getLoopStart(processorGlassMarimbaSoft);
   case 14:
     return synthSamplerIndianSitar_Processor_getLoopStart(processorIndianSitar);
   case 15:
     return synthSamplerJapaneseShakuhachiFlute_Processor_getLoopStart(processorJapaneseShakuhachiFlute);
   case 16:
     return synthSamplerKoto_Processor_getLoopStart(processorKoto);
   case 17:
     return synthSamplerMagnificentDrone_Processor_getLoopStart(processorMagnificentDrone);
   case 18:
     return synthSamplerMysticVibes_Processor_getLoopStart(processorMysticVibes);
   case 19:
     return synthSamplerPowerFifths_Processor_getLoopStart(processorPowerFifths);
   case 20:
     return synthSamplerPulsingPatterns_Processor_getLoopStart(processorPulsingPatterns);
   case 21:
     return synthSamplerShootingStar_Processor_getLoopStart(processorShootingStar);
   case 22:
     return synthSamplerTimeWarp_Processor_getLoopStart(processorTimeWarp);
   case 23:
     return synthSamplerTranquility_Processor_getLoopStart(processorTranquility);
   case 24:
     return synthSamplerVocalCluster_Processor_getLoopStart(processorVocalCluster);
   case 25:
     return synthSamplerZenGarden_Processor_getLoopStart(processorZenGarden);
   case 0:
   default:
     return synthSampler_Processor_getLoopStart(processorOcarina);
   }
}

int MetaSampler::getLoopEnd() {
   switch(selectedSample) {
   case 1:
     return synthSamplerCello_Processor_getLoopEnd(processorCello);
   case 2:
     return synthSamplerClarinet_Processor_getLoopEnd(processorClarinet);
   case 3:
     return synthSamplerPiano_Processor_getLoopEnd(processorPiano);
   case 4:
     return synthSamplerAmbientLead_Processor_getLoopEnd(processorAmbientLead);
   case 5:
     return synthSamplerAuthenticStrings_Processor_getLoopEnd(processorAuthenticStrings);
   case 6:
     return synthSamplerBoesendorferGrandPiano_Processor_getLoopEnd(processorBoesendorferGrandPiano);
   case 7:
     return synthSamplerCelesta_Processor_getLoopEnd(processorCelesta);
   case 8:
     return synthSamplerClarinets_Processor_getLoopEnd(processorClarinets);
   case 9:
     return synthSamplerClassicSuitcaseMk1_Processor_getLoopEnd(processorClassicSuitcaseMk1);
   case 10:
     return synthSamplerCosmos_Processor_getLoopEnd(processorCosmos);
   case 11:
     return synthSamplerDreamVoice_Processor_getLoopEnd(processorDreamVoice);
   case 12:
     return synthSamplerDrivenSynthLead_Processor_getLoopEnd(processorDrivenSynthLead);
   case 13:
     return synthSamplerGlassMarimbaSoft_Processor_getLoopEnd(processorGlassMarimbaSoft);
   case 14:
     return synthSamplerIndianSitar_Processor_getLoopEnd(processorIndianSitar);
   case 15:
     return synthSamplerJapaneseShakuhachiFlute_Processor_getLoopEnd(processorJapaneseShakuhachiFlute);
   case 16:
     return synthSamplerKoto_Processor_getLoopEnd(processorKoto);
   case 17:
     return synthSamplerMagnificentDrone_Processor_getLoopEnd(processorMagnificentDrone);
   case 18:
     return synthSamplerMysticVibes_Processor_getLoopEnd(processorMysticVibes);
   case 19:
     return synthSamplerPowerFifths_Processor_getLoopEnd(processorPowerFifths);
   case 20:
     return synthSamplerPulsingPatterns_Processor_getLoopEnd(processorPulsingPatterns);
   case 21:
     return synthSamplerShootingStar_Processor_getLoopEnd(processorShootingStar);
   case 22:
     return synthSamplerTimeWarp_Processor_getLoopEnd(processorTimeWarp);
   case 23:
     return synthSamplerTranquility_Processor_getLoopEnd(processorTranquility);
   case 24:
     return synthSamplerVocalCluster_Processor_getLoopEnd(processorVocalCluster);
   case 25:
     return synthSamplerZenGarden_Processor_getLoopEnd(processorZenGarden);
   case 0:
   default:
     return synthSampler_Processor_getLoopEnd(processorOcarina);
   }
}

void MetaSampler::setLoop(bool param, bool force) {
   switch(selectedSample) {
   case 1:
     synthSamplerCello_Processor_setLoop(processorCello, param, force);
     break;
   case 2:
     synthSamplerClarinet_Processor_setLoop(processorClarinet, param, force);
      break;
   case 3:
     synthSamplerPiano_Processor_setLoop(processorPiano, param, force);
      break;
   case 4:
     synthSamplerAmbientLead_Processor_setLoop(processorAmbientLead, param, force);
      break;
   case 5:
     synthSamplerAuthenticStrings_Processor_setLoop(processorAuthenticStrings, param, force);
      break;
   case 6:
     synthSamplerBoesendorferGrandPiano_Processor_setLoop(processorBoesendorferGrandPiano, param, force);
      break;
   case 7:
     synthSamplerCelesta_Processor_setLoop(processorCelesta, param, force);
      break;
   case 8:
     synthSamplerClarinets_Processor_setLoop(processorClarinets, param, force);
      break;
   case 9:
     synthSamplerClassicSuitcaseMk1_Processor_setLoop(processorClassicSuitcaseMk1, param, force);
      break;
   case 10:
     synthSamplerCosmos_Processor_setLoop(processorCosmos, param, force);
      break;
   case 11:
     synthSamplerDreamVoice_Processor_setLoop(processorDreamVoice, param, force);
      break;
   case 12:
     synthSamplerDrivenSynthLead_Processor_setLoop(processorDrivenSynthLead, param, force);
      break;
   case 13:
     synthSamplerGlassMarimbaSoft_Processor_setLoop(processorGlassMarimbaSoft, param, force);
      break;
   case 14:
     synthSamplerIndianSitar_Processor_setLoop(processorIndianSitar, param, force);
      break;
   case 15:
     synthSamplerJapaneseShakuhachiFlute_Processor_setLoop(processorJapaneseShakuhachiFlute, param, force);
      break;
   case 16:
     synthSamplerKoto_Processor_setLoop(processorKoto, param, force);
      break;
   case 17:
     synthSamplerMagnificentDrone_Processor_setLoop(processorMagnificentDrone, param, force);
      break;
   case 18:
     synthSamplerMysticVibes_Processor_setLoop(processorMysticVibes, param, force);
      break;
   case 19:
     synthSamplerPowerFifths_Processor_setLoop(processorPowerFifths, param, force);
      break;
   case 20:
     synthSamplerPulsingPatterns_Processor_setLoop(processorPulsingPatterns, param, force);
      break;
   case 21:
     synthSamplerShootingStar_Processor_setLoop(processorShootingStar, param, force);
      break;
   case 22:
     synthSamplerTimeWarp_Processor_setLoop(processorTimeWarp, param, force);
      break;
   case 23:
     synthSamplerTranquility_Processor_setLoop(processorTranquility, param, force);
      break;
   case 24:
     synthSamplerVocalCluster_Processor_setLoop(processorVocalCluster, param, force);
      break;
   case 25:
     synthSamplerZenGarden_Processor_setLoop(processorZenGarden, param, force);
      break;
   case 0:
   default:
     synthSampler_Processor_setLoop(processorOcarina, param, force);
      break;
   }
}

void MetaSampler::setLoopStart(int param, bool force) {
   switch(selectedSample) {
   case 1:
     synthSamplerCello_Processor_setLoopStart(processorCello, param, force);
      break;
   case 2:
     synthSamplerClarinet_Processor_setLoopStart(processorClarinet, param, force);
      break;
   case 3:
     synthSamplerPiano_Processor_setLoopStart(processorPiano, param, force);
      break;
   case 4:
     synthSamplerAmbientLead_Processor_setLoopStart(processorAmbientLead, param, force);
      break;
   case 5:
     synthSamplerAuthenticStrings_Processor_setLoopStart(processorAuthenticStrings, param, force);
      break;
   case 6:
     synthSamplerBoesendorferGrandPiano_Processor_setLoopStart(processorBoesendorferGrandPiano, param, force);
      break;
   case 7:
     synthSamplerCelesta_Processor_setLoopStart(processorCelesta, param, force);
      break;
   case 8:
     synthSamplerClarinets_Processor_setLoopStart(processorClarinets, param, force);
      break;
   case 9:
     synthSamplerClassicSuitcaseMk1_Processor_setLoopStart(processorClassicSuitcaseMk1, param, force);
      break;
   case 10:
     synthSamplerCosmos_Processor_setLoopStart(processorCosmos, param, force);
      break;
   case 11:
     synthSamplerDreamVoice_Processor_setLoopStart(processorDreamVoice, param, force);
      break;
   case 12:
     synthSamplerDrivenSynthLead_Processor_setLoopStart(processorDrivenSynthLead, param, force);
      break;
   case 13:
     synthSamplerGlassMarimbaSoft_Processor_setLoopStart(processorGlassMarimbaSoft, param, force);
      break;
   case 14:
     synthSamplerIndianSitar_Processor_setLoopStart(processorIndianSitar, param, force);
      break;
   case 15:
     synthSamplerJapaneseShakuhachiFlute_Processor_setLoopStart(processorJapaneseShakuhachiFlute, param, force);
      break;
   case 16:
     synthSamplerKoto_Processor_setLoopStart(processorKoto, param, force);
      break;
   case 17:
     synthSamplerMagnificentDrone_Processor_setLoopStart(processorMagnificentDrone, param, force);
      break;
   case 18:
     synthSamplerMysticVibes_Processor_setLoopStart(processorMysticVibes, param, force);
      break;
   case 19:
     synthSamplerPowerFifths_Processor_setLoopStart(processorPowerFifths, param, force);
      break;
   case 20:
     synthSamplerPulsingPatterns_Processor_setLoopStart(processorPulsingPatterns, param, force);
      break;
   case 21:
     synthSamplerShootingStar_Processor_setLoopStart(processorShootingStar, param, force);
      break;
   case 22:
     synthSamplerTimeWarp_Processor_setLoopStart(processorTimeWarp, param, force);
      break;
   case 23:
     synthSamplerTranquility_Processor_setLoopStart(processorTranquility, param, force);
      break;
   case 24:
     synthSamplerVocalCluster_Processor_setLoopStart(processorVocalCluster, param, force);
      break;
   case 25:
     synthSamplerZenGarden_Processor_setLoopStart(processorZenGarden, param, force);
      break;
   case 0:
   default:
     synthSampler_Processor_setLoopStart(processorOcarina, param, force);
      break;
   }
}

void MetaSampler::setLoopEnd(int param, bool force) {
   switch(selectedSample) {
   case 1:
     synthSamplerCello_Processor_setLoopEnd(processorCello, param, force);
      break;
   case 2:
     synthSamplerClarinet_Processor_setLoopEnd(processorClarinet, param, force);
      break;
   case 3:
     synthSamplerPiano_Processor_setLoopEnd(processorPiano, param, force);
      break;
   case 4:
     synthSamplerAmbientLead_Processor_setLoopEnd(processorAmbientLead, param, force);
      break;
   case 5:
     synthSamplerAuthenticStrings_Processor_setLoopEnd(processorAuthenticStrings, param, force);
      break;
   case 6:
     synthSamplerBoesendorferGrandPiano_Processor_setLoopEnd(processorBoesendorferGrandPiano, param, force);
      break;
   case 7:
     synthSamplerCelesta_Processor_setLoopEnd(processorCelesta, param, force);
      break;
   case 8:
     synthSamplerClarinets_Processor_setLoopEnd(processorClarinets, param, force);
      break;
   case 9:
     synthSamplerClassicSuitcaseMk1_Processor_setLoopEnd(processorClassicSuitcaseMk1, param, force);
      break;
   case 10:
     synthSamplerCosmos_Processor_setLoopEnd(processorCosmos, param, force);
      break;
   case 11:
     synthSamplerDreamVoice_Processor_setLoopEnd(processorDreamVoice, param, force);
      break;
   case 12:
     synthSamplerDrivenSynthLead_Processor_setLoopEnd(processorDrivenSynthLead, param, force);
      break;
   case 13:
     synthSamplerGlassMarimbaSoft_Processor_setLoopEnd(processorGlassMarimbaSoft, param, force);
      break;
   case 14:
     synthSamplerIndianSitar_Processor_setLoopEnd(processorIndianSitar, param, force);
      break;
   case 15:
     synthSamplerJapaneseShakuhachiFlute_Processor_setLoopEnd(processorJapaneseShakuhachiFlute, param, force);
      break;
   case 16:
     synthSamplerKoto_Processor_setLoopEnd(processorKoto, param, force);
      break;
   case 17:
     synthSamplerMagnificentDrone_Processor_setLoopEnd(processorMagnificentDrone, param, force);
      break;
   case 18:
     synthSamplerMysticVibes_Processor_setLoopEnd(processorMysticVibes, param, force);
      break;
   case 19:
     synthSamplerPowerFifths_Processor_setLoopEnd(processorPowerFifths, param, force);
      break;
   case 20:
     synthSamplerPulsingPatterns_Processor_setLoopEnd(processorPulsingPatterns, param, force);
      break;
   case 21:
     synthSamplerShootingStar_Processor_setLoopEnd(processorShootingStar, param, force);
      break;
   case 22:
     synthSamplerTimeWarp_Processor_setLoopEnd(processorTimeWarp, param, force);
      break;
   case 23:
     synthSamplerTranquility_Processor_setLoopEnd(processorTranquility, param, force);
      break;
   case 24:
     synthSamplerVocalCluster_Processor_setLoopEnd(processorVocalCluster, param, force);
      break;
   case 25:
     synthSamplerZenGarden_Processor_setLoopEnd(processorZenGarden, param, force);
      break;
   case 0:
   default:
     synthSampler_Processor_setLoopEnd(processorOcarina, param, force);
      break;
   }
}

void MetaSampler::setNote(float gate, float voct, float vel, int c) {
   switch(selectedSample) {
   case 1:
      synthSamplerCello_Processor_setNote(processorCello, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   case 2:
      synthSamplerClarinet_Processor_setNote(processorClarinet, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   case 3:
      synthSamplerPiano_Processor_setNote(processorPiano, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   case 4:
      synthSamplerAmbientLead_Processor_setNote(processorAmbientLead, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   case 5:
      synthSamplerAuthenticStrings_Processor_setNote(processorAuthenticStrings, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   case 6:
      synthSamplerBoesendorferGrandPiano_Processor_setNote(processorBoesendorferGrandPiano, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   case 7:
      synthSamplerCelesta_Processor_setNote(processorCelesta, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   case 8:
      synthSamplerClarinets_Processor_setNote(processorClarinets, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   case 9:
      synthSamplerClassicSuitcaseMk1_Processor_setNote(processorClassicSuitcaseMk1, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   case 10:
      synthSamplerCosmos_Processor_setNote(processorCosmos, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   case 11:
      synthSamplerDreamVoice_Processor_setNote(processorDreamVoice, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   case 12:
      synthSamplerDrivenSynthLead_Processor_setNote(processorDrivenSynthLead, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   case 13:
      synthSamplerGlassMarimbaSoft_Processor_setNote(processorGlassMarimbaSoft, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   case 14:
      synthSamplerIndianSitar_Processor_setNote(processorIndianSitar, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   case 15:
      synthSamplerJapaneseShakuhachiFlute_Processor_setNote(processorJapaneseShakuhachiFlute, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   case 16:
      synthSamplerKoto_Processor_setNote(processorKoto, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   case 17:
      synthSamplerMagnificentDrone_Processor_setNote(processorMagnificentDrone, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   case 18:
      synthSamplerMysticVibes_Processor_setNote(processorMysticVibes, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   case 19:
      synthSamplerPowerFifths_Processor_setNote(processorPowerFifths, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   case 20:
      synthSamplerPulsingPatterns_Processor_setNote(processorPulsingPatterns, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   case 21:
      synthSamplerShootingStar_Processor_setNote(processorShootingStar, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   case 22:
      synthSamplerTimeWarp_Processor_setNote(processorTimeWarp, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   case 23:
      synthSamplerTranquility_Processor_setNote(processorTranquility, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   case 24:
      synthSamplerVocalCluster_Processor_setNote(processorVocalCluster, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   case 25:
      synthSamplerZenGarden_Processor_setNote(processorZenGarden, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   case 0:
   default:
      synthSampler_Processor_setNote(processorOcarina, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   }
}

float MetaSampler::process() {
   switch(selectedSample) {
   case 1:
      return fix_to_float(synthSamplerCello_Processor_process(processorCello));
   case 2:
      return fix_to_float(synthSamplerClarinet_Processor_process(processorClarinet));
   case 3:
      return fix_to_float(synthSamplerPiano_Processor_process(processorPiano));
   case 4:
      return fix_to_float(synthSamplerAmbientLead_Processor_process(processorAmbientLead));
   case 5:
      return fix_to_float(synthSamplerAuthenticStrings_Processor_process(processorAuthenticStrings));
   case 6:
      return fix_to_float(synthSamplerBoesendorferGrandPiano_Processor_process(processorBoesendorferGrandPiano));
   case 7:
      return fix_to_float(synthSamplerCelesta_Processor_process(processorCelesta));
   case 8:
      return fix_to_float(synthSamplerClarinets_Processor_process(processorClarinets));
   case 9:
      return fix_to_float(synthSamplerClassicSuitcaseMk1_Processor_process(processorClassicSuitcaseMk1));
   case 10:
      return fix_to_float(synthSamplerCosmos_Processor_process(processorCosmos));
   case 11:
      return fix_to_float(synthSamplerDreamVoice_Processor_process(processorDreamVoice));
   case 12:
      return fix_to_float(synthSamplerDrivenSynthLead_Processor_process(processorDrivenSynthLead));
   case 13:
      return fix_to_float(synthSamplerGlassMarimbaSoft_Processor_process(processorGlassMarimbaSoft));
   case 14:
      return fix_to_float(synthSamplerIndianSitar_Processor_process(processorIndianSitar));
   case 15:
      return fix_to_float(synthSamplerJapaneseShakuhachiFlute_Processor_process(processorJapaneseShakuhachiFlute));
   case 16:
      return fix_to_float(synthSamplerKoto_Processor_process(processorKoto));
   case 17:
      return fix_to_float(synthSamplerMagnificentDrone_Processor_process(processorMagnificentDrone));
   case 18:
      return fix_to_float(synthSamplerMysticVibes_Processor_process(processorMysticVibes));
   case 19:
      return fix_to_float(synthSamplerPowerFifths_Processor_process(processorPowerFifths));
   case 20:
      return fix_to_float(synthSamplerPulsingPatterns_Processor_process(processorPulsingPatterns));
   case 21:
      return fix_to_float(synthSamplerShootingStar_Processor_process(processorShootingStar));
   case 22:
      return fix_to_float(synthSamplerTimeWarp_Processor_process(processorTimeWarp));
   case 23:
      return fix_to_float(synthSamplerTranquility_Processor_process(processorTranquility));
   case 24:
      return fix_to_float(synthSamplerVocalCluster_Processor_process(processorVocalCluster));
   case 25:
      return fix_to_float(synthSamplerZenGarden_Processor_process(processorZenGarden));
   case 0:
   default:
      return fix_to_float(synthSampler_Processor_process(processorOcarina));
   }
}

void MetaSampler::initProc() {
   switch(selectedSample) {
   case 1:
      synthSamplerCello_Processor_process_init(processorCello);
      break;
   case 2:
      synthSamplerClarinet_Processor_process_init(processorClarinet);
      break;
   case 3:
      synthSamplerPiano_Processor_process_init(processorPiano);
      break;
   case 4:
      synthSamplerAmbientLead_Processor_process_init(processorAmbientLead);
      break;
   case 5:
      synthSamplerAuthenticStrings_Processor_process_init(processorAuthenticStrings);
      break;
   case 6:
      synthSamplerBoesendorferGrandPiano_Processor_process_init(processorBoesendorferGrandPiano);
      break;
   case 7:
      synthSamplerCelesta_Processor_process_init(processorCelesta);
      break;
   case 8:
      synthSamplerClarinets_Processor_process_init(processorClarinets);
      break;
   case 9:
      synthSamplerClassicSuitcaseMk1_Processor_process_init(processorClassicSuitcaseMk1);
      break;
   case 10:
      synthSamplerCosmos_Processor_process_init(processorCosmos);
      break;
   case 11:
      synthSamplerDreamVoice_Processor_process_init(processorDreamVoice);
      break;
   case 12:
      synthSamplerDrivenSynthLead_Processor_process_init(processorDrivenSynthLead);
      break;
   case 13:
      synthSamplerGlassMarimbaSoft_Processor_process_init(processorGlassMarimbaSoft);
      break;
   case 14:
      synthSamplerIndianSitar_Processor_process_init(processorIndianSitar);
      break;
   case 15:
      synthSamplerJapaneseShakuhachiFlute_Processor_process_init(processorJapaneseShakuhachiFlute);
      break;
   case 16:
      synthSamplerKoto_Processor_process_init(processorKoto);
      break;
   case 17:
      synthSamplerMagnificentDrone_Processor_process_init(processorMagnificentDrone);
      break;
   case 18:
      synthSamplerMysticVibes_Processor_process_init(processorMysticVibes);
      break;
   case 19:
      synthSamplerPowerFifths_Processor_process_init(processorPowerFifths);
      break;
   case 20:
      synthSamplerPulsingPatterns_Processor_process_init(processorPulsingPatterns);
      break;
   case 21:
      synthSamplerShootingStar_Processor_process_init(processorShootingStar);
      break;
   case 22:
      synthSamplerTimeWarp_Processor_process_init(processorTimeWarp);
      break;
   case 23:
      synthSamplerTranquility_Processor_process_init(processorTranquility);
      break;
   case 24:
      synthSamplerVocalCluster_Processor_process_init(processorVocalCluster);
      break;
   case 25:
      synthSamplerZenGarden_Processor_process_init(processorZenGarden);
      break;
   case 0:
   default:
      synthSampler_Processor_process_init(processorOcarina);
      break;
   }
}
