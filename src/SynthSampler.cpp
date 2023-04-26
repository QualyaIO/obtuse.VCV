#include "plugin.hpp"
#include "engine_synthSampler.h"
#include "engine_synthSamplerCello.h"
#include "engine_synthSamplerClarinet.h"
#include "engine_synthSamplerPiano.h"

// handle the various sampler
struct MetaSampler {

   // all varients of the processor
   synthSampler_Processor_process_type processorOcarina;
   synthSamplerCello_Processor_process_type processorCello;
   synthSamplerClarinet_Processor_process_type processorClarinet;
   synthSamplerPiano_Processor_process_type processorPiano;

   int selectedSample = -1;

   MetaSampler();
   // to sync with the actual number of samples...
   static int getNbSamples() { return 3;};
   static std::string getSampleName(int sample) {
      switch(sample) {
      case 1:
         return "Cello";
      case 2:
         return "Clarinet";
      case 3:
         return "Piano";
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
   configParam<SampleQuantity>(SynthSampler::SAMPLE, 0, MetaSampler::getNbSamples(), 0, "Sample", "");
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
