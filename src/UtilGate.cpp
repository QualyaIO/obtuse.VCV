#include "plugin.hpp"
#include "engine_utils.h"

// Gate module. Note that inputs could be discarded if there is not enough leg room to process all gates, as internally use MIDI notes

struct UtilGate : Module {

   enum ParamIds {
      DURATION,
      DURATION_AV,
      NUM_PARAMS
   };
   enum InputIds {
      DURATION_IN,
      VOCT,
      TRIGGER,
      NUM_INPUTS
   };
   enum OutputIds {
      GATE_OUT,
      VOCT_OUT,
      NUM_OUTPUTS
   };
   enum LightIds {
      NUM_LIGHTS
   };

   Processor_gate_process_type processor;

   UtilGate();
   void process(const ProcessArgs &args) override;
   // pass all parameters to engine. force: engine will pass params even if not changed, use upon init
   void sendParams(bool force=false);
   // ease reading parameters with modulation
   float readParamCV(int PARAM, int CV_IN, int CV_AV);

   // tmp arrays for inputs
   fix16_t voct[16];
   fix16_t triggs[16];
   // tmp arrays for outputs
   fix16_t voct_out[16];
   fix16_t gates_out[16];

   // time passing by, seconds and fract part of remainder
   int timeS = 0;
   float timeFract = 0.0;
};

UtilGate::UtilGate() {
   config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

   // same range than base VCV gate, 1ms to 10s
   configParam(UtilGate::DURATION, 0.001, 10.0, 0.2, "Duration", " ms", 0.0f, 1000.0f);

   // init engine and apply default parameter
   Processor_gate_process_init(processor);
   sendParams(true);
}

// Reads the CV input values, if any, normalize and apply modulator (was attenuverter before)
// the higher the modulator, the greater the modulation
float UtilGate::readParamCV(int PARAM, int CV_IN, int CV_AV) {
   float val = params[PARAM].getValue();
   float in_val = 1.0;
   if (inputs[CV_IN].getChannels() > 0) {
      // input range should be 0..10v
      in_val = inputs[CV_IN].getVoltage() / 10.0f;
      // values on 0..1
      in_val = clamp(in_val, 0.0, 1.0);
      // by how much we can modulate
      float mod_range = (val - paramQuantities[PARAM]->getMinValue()) *  params[CV_AV].getValue();
      val = val - mod_range * (1 - in_val);
   }
   return val;
}

void UtilGate::sendParams(bool force) {
   Processor_gate_setDuration(processor, float_to_fix(readParamCV(DURATION, DURATION_IN, DURATION_AV)), force);
}

void UtilGate::process(const ProcessArgs &args) {
   
   // update parameters
   sendParams();

   int channels = std::max(inputs[TRIGGER].getChannels(), inputs[VOCT].getChannels());

   int i = 0;
   // retrieve connected cables
   for(; i < channels; i++) {
      // norm and convert in place
      voct[i] = float_to_fix(inputs[VOCT].getPolyVoltage(i)/10.0f);
      triggs[i] = float_to_fix(inputs[TRIGGER].getPolyVoltage(i)/10.0f);
   }
   // nullify remaining
   for(; i < 16; i++) {
      voct[i] = float_to_fix(0.0);
      triggs[i] = float_to_fix(0.0);
   }

   // update time
   timeFract += 1./args.sampleRate;
   while (timeFract >= 1.0) {
      timeS += 1;
      timeFract -= 1.0;
   }
   // let it run
   Processor_gate_process(processor, timeS, float_to_fix(timeFract), triggs, voct, channels);
  // retrieve output
   int channels_out = Processor_gate_getOutputs(processor, gates_out, voct_out);
   i = 0;
   // retrieve connected cables
   for(; i < channels_out; i++) {
      outputs[VOCT_OUT].setVoltage(fix_to_float(voct_out[i]) * 10.0, i);
      outputs[GATE_OUT].setVoltage(fix_to_float(gates_out[i]) * 10.0, i);
   }
   // nullify remaining, just in case
   for(; i < 16; i++) {
      voct[i] = 0.0;
      triggs[i] = 0.0;
   }
   outputs[VOCT_OUT].setChannels(channels_out);
   outputs[GATE_OUT].setChannels(channels_out);

}

struct UtilGateWidget : ModuleWidget {
   UtilGateWidget(UtilGate *module) {
      setModule(module);
      setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Gate.svg")));

      float big_knob_x = 10.160;
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(big_knob_x, 128.5-81.229)), module, UtilGate::DURATION));

      float av_in_x = 4.928;
      float av_knob_x = 15.509;
      float av_duration_y = 128.5-70.092;

      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, av_duration_y)), module, UtilGate::DURATION_IN));
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(av_knob_x, av_duration_y)), module, UtilGate::DURATION_AV));

      float ports_row1_y = 128.5-27.625;
      float ports_row2_y = 128.5-13.609;
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, ports_row1_y)), module, UtilGate::VOCT));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_knob_x, ports_row1_y)), module, UtilGate::TRIGGER));
      addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(av_in_x, ports_row2_y)), module, UtilGate::VOCT_OUT));
      addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(av_knob_x, ports_row2_y)), module, UtilGate::GATE_OUT));

   }
};

Model *utilGate = createModel<UtilGate, UtilGateWidget>("BotaniaGate");
