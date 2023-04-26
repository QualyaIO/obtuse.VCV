#include "plugin.hpp"
#include "MetaSampler.hpp"

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
      OVERRIDE_TOGGLE,
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
      OVERRIDE_LIGHT,
      NUM_LIGHTS
   };

   MetaSampler sampler;

   SynthSampler();
   // pass all parameters to engine. force: engine will pass params even if not changed, use upon init
   void syncParams(bool force=false);
   void process(const ProcessArgs &args) override;
};

SynthSampler::SynthSampler() {
   config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

   configParam<SampleQuantity>(SynthSampler::SAMPLE, 0, MetaSampler::getNbSamples()-1, 0, "Sample", "");
   paramQuantities[SAMPLE]->snapEnabled = true;

   configParam(SynthSampler::LOOP_START, 0, MetaSampler::getMaxLoopSize(), 0, "Loop start", " sample");
   paramQuantities[LOOP_START]->snapEnabled = true;
   configParam(SynthSampler::LOOP_END, 0, MetaSampler::getMaxLoopSize(), 0, "Loop end", " sample");
   paramQuantities[LOOP_END]->snapEnabled = true;
   
   configSwitch(SynthSampler::LOOP_TOGGLE, 0, 1, 0, "Loop", {"Disable looping", "Enable looping"});
   configSwitch(SynthSampler::OVERRIDE_TOGGLE, 0, 1, 0, "Loop override", {"Fetch default loop state upon change", "Override default loop state"});

   syncParams(true);
}

void SynthSampler::syncParams(bool force) {
   bool loop_press = params[LOOP_TOGGLE].getValue() > 0.0;
   bool override_press = params[OVERRIDE_TOGGLE].getValue() > 0.0;

   // sync current processor
   if (sampler.switchTo(int(params[SAMPLE].getValue()))) {
      // we did switch, force current state to sampler if override is set, otherwise force sampler default state to VCV
      if (override_press) {
         sampler.setLoop(loop_press, true);
         sampler.setLoopStart(int(params[LOOP_START].getValue()), true);
         sampler.setLoopEnd(int(params[LOOP_END].getValue()), true);
      } else {
         params[LOOP_TOGGLE].setValue(sampler.getLoop());
         params[LOOP_START].setValue(sampler.getLoopStart());
         params[LOOP_END].setValue(sampler.getLoopEnd());
      }
   } else {
         sampler.setLoop(loop_press, force);
         sampler.setLoopStart(int(params[LOOP_START].getValue()), force);
         sampler.setLoopEnd(int(params[LOOP_END].getValue()), force);
   }

   // enforcing range of loop within size
   // FIXME: getting too close to the end will disable crossfading and then loop altogether
   // TODO: also enforce start pos compared to end?
   if (params[LOOP_END].getValue() > sampler.getSize()) {
      params[LOOP_END].setValue(sampler.getSize());
   }
   if (params[LOOP_START].getValue() > sampler.getSize()) {
      params[LOOP_START].setValue(sampler.getSize());
   }

   // update lights
   lights[LOOP_LIGHT].setBrightnessSmooth(loop_press, 10.0f);
   lights[OVERRIDE_LIGHT].setBrightnessSmooth(override_press, 10.0f);
}

void SynthSampler::process(const ProcessArgs &args) {
   // update parameters
   sampler.setSamplerate(args.sampleRate/1000.0);
   syncParams();

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

      float port_1_x = 5.435;
      float port_2_x = 14.885;
      float knobs_y = 128.5-59.486;
      float buttons_y = 128.5-69.287;

      // this time we got a a latch light button
      addParam(createLightParamCentered<VCVLightLatch<LargeSimpleLight<GreenLight>>>(mm2px(Vec(port_1_x, buttons_y)), module, SynthSampler::LOOP_TOGGLE, SynthSampler::LOOP_LIGHT));
      addParam(createLightParamCentered<VCVLightLatch<LargeSimpleLight<PinkLight>>>(mm2px(Vec(port_2_x, buttons_y)), module, SynthSampler::OVERRIDE_TOGGLE, SynthSampler::OVERRIDE_LIGHT));

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
