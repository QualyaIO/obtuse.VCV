#include "plugin.hpp"
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

   // all varients of the processor
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

   int selectedSample = -1;

   MetaSampler();
   // to sync with the actual number of samples...
   static int getNbSamples() { return 26;};
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

   // will (re)init corresponding processor upon change
   void switchTo(int sample);
   // wrapping functions
   void setSamplerate(float sr);
   void nbCables(int cables);
   void setNote(float gate, float voct, float vel, int c);
   float process();

private:
   // initialize current processor
   void initProc();
};

MetaSampler::MetaSampler() {
}

void MetaSampler::switchTo(int sample) {
   sample = clamp(sample, 0, getNbSamples());
   if (sample != selectedSample) {
      selectedSample = sample;
      initProc();
   }
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


// naming the samples
struct SampleQuantity : ParamQuantity {
	std::string getDisplayValueString() override {
           return std::to_string(int(getValue())) + " - " + MetaSampler::getSampleName(int(getValue()));
	}
};

struct SynthSampler : Module {

   enum ParamIds {
      SAMPLE,
      LOOP_TOGGLE,
      LOOP_START,
      LOOP_END,
      NUM_PARAMS
   };
   enum InputIds {
      VOCT,
      GATE,
      VEL,
      NUM_INPUTS
   };
   enum OutputIds {
      OUT,
      NUM_OUTPUTS
   };
   enum LightIds {
      LOOP_LIGHT,
      NUM_LIGHTS
   };

   MetaSampler sampler;

   SynthSampler();
   // pass all parameters to engine. force: engine will pass params even if not changed, use upon init
   void sendParams(bool force=false);
   void process(const ProcessArgs &args) override;
};

SynthSampler::SynthSampler() {
   config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

   //configParam(SynthSampler::SAMPLE, 0, MetaSampler::getNbSamples(), 0, "BPM", " BPM");
   configParam<SampleQuantity>(SynthSampler::SAMPLE, 0, MetaSampler::getNbSamples()-1, 0, "Sample", "");
   paramQuantities[SAMPLE]->snapEnabled = true;
   
   sendParams(true);
}

void SynthSampler::sendParams(bool force) {
   // update light for loop toggle
   bool press = params[LOOP_TOGGLE].getValue() > 0.0;
   lights[LOOP_LIGHT].setBrightnessSmooth(press, 10.0f);

   // sync current processor
   sampler.switchTo(int(params[SAMPLE].getValue()));
}

void SynthSampler::process(const ProcessArgs &args) {
   // update parameters
   sampler.setSamplerate(args.sampleRate/1000.0);
   sendParams();

   // retrieve current max number of channels for gate and v/oct
   int channels =
      std::max(
               std::max(inputs[GATE].getChannels(), inputs[VOCT].getChannels()),
               inputs[VEL].getChannels());
   sampler.nbCables(channels);
   // pass each note to the synth
   for (int c = 0; c < channels; c++) {
      // Reads all the input values and normalizes the values
      float gate = inputs[GATE].getPolyVoltage(c) / 10.0f;
      float voct = inputs[VOCT].getPolyVoltage(c) / 10.0f;
      float vel = inputs[VEL].getPolyVoltage(c) / 10.0f;
      sampler.setNote(gate, voct, vel, c);
   }

   // out is audio, set to audio range (-5..5)
   outputs[OUT].setVoltage(sampler.process() * 5.0f);
}

struct SynthSamplerWidget : ModuleWidget {
   SynthSamplerWidget(SynthSampler *module) {
      setModule(module);

      setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SynthSampler.svg")));


      addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(10.16, 128.5-92.937)), module, SynthSampler::SAMPLE));

      // this time we got a a latch light button
      addParam(createLightParamCentered<VCVLightLatch<LargeSimpleLight<GreenLight>>>(mm2px(Vec(10.16, 128.5-69.287)), module, SynthSampler::LOOP_TOGGLE, SynthSampler::LOOP_LIGHT));

      float port_1_x = 5.435;
      float port_2_x = 14.885;
      float knobs_y = 128.5-59.486;

      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(port_1_x, knobs_y)), module, SynthSampler::LOOP_START));
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(port_2_x, knobs_y)), module, SynthSampler::LOOP_END));

      float port_a_y = 128.5-33.845;
      float port_b_y = 128.5-18.745;
      
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(port_1_x, port_a_y)), module, SynthSampler::VOCT));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(port_2_x, port_a_y)), module, SynthSampler::GATE));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(port_1_x, port_b_y)), module, SynthSampler::VEL));

      addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(port_2_x, port_b_y)), module, SynthSampler::OUT));
   }
};

Model *synthSampler = createModel<SynthSampler, SynthSamplerWidget>("BotaniaSynthSampler");
