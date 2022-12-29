
/* Code automatically generated by Vult https://github.com/modlfo/vult */
#ifndef ENGINE_SYNTHSAMPLER_H
#define ENGINE_SYNTHSAMPLER_H
#include <stdint.h>
#include <math.h>
#include "vultin.h"
#include "engine_synthSampler.tables.h"

typedef struct synthSampler__tuple___real_real_real_real__ {
   fix16_t field_0;
   fix16_t field_1;
   fix16_t field_2;
   fix16_t field_3;
} synthSampler__tuple___real_real_real_real__;

static_inline fix16_t synthSampler_Util_noteToFrequency(int note){
   return fix_mul(0x217 /* 0.008176 */,fix_exp(fix_mul(0xec9 /* 0.057762 */,int_to_fix(note))));
};

typedef struct synthSampler_Util__ctx_type_1 {
   uint8_t pre;
} synthSampler_Util__ctx_type_1;

typedef synthSampler_Util__ctx_type_1 synthSampler_Util_edge_type;

static_inline void synthSampler_Util__ctx_type_1_init(synthSampler_Util__ctx_type_1 &_output_){
   synthSampler_Util__ctx_type_1 _ctx;
   _ctx.pre = false;
   _output_ = _ctx;
   return ;
}

static_inline void synthSampler_Util_edge_init(synthSampler_Util__ctx_type_1 &_output_){
   synthSampler_Util__ctx_type_1_init(_output_);
   return ;
}

static_inline uint8_t synthSampler_Util_edge(synthSampler_Util__ctx_type_1 &_ctx, uint8_t x){
   uint8_t ret;
   ret = (x && bool_not(_ctx.pre));
   _ctx.pre = x;
   return ret;
}

static_inline fix16_t synthSampler_Util_cubic_clipper(fix16_t x){
   if(x <= -0xaaaa /* -0.666667 */){
      return -0xaaaa /* -0.666667 */;
   }
   else
   {
      if(x >= 0xaaaa /* 0.666667 */){
         return 0xaaaa /* 0.666667 */;
      }
      else
      {
         return (x + fix_mul(fix_mul(fix_mul(-0x5555 /* -0.333333 */,x),x),x));
      }
   }
};

typedef struct synthSampler_Util__ctx_type_3 {
   fix16_t pre_x;
} synthSampler_Util__ctx_type_3;

typedef synthSampler_Util__ctx_type_3 synthSampler_Util_change_type;

static_inline void synthSampler_Util__ctx_type_3_init(synthSampler_Util__ctx_type_3 &_output_){
   synthSampler_Util__ctx_type_3 _ctx;
   _ctx.pre_x = 0x0 /* 0.000000 */;
   _output_ = _ctx;
   return ;
}

static_inline void synthSampler_Util_change_init(synthSampler_Util__ctx_type_3 &_output_){
   synthSampler_Util__ctx_type_3_init(_output_);
   return ;
}

static_inline uint8_t synthSampler_Util_change(synthSampler_Util__ctx_type_3 &_ctx, fix16_t x){
   uint8_t v;
   v = (_ctx.pre_x != x);
   _ctx.pre_x = x;
   return v;
}

static_inline void synthSampler_Util_buffer(fix16_t (&_output_)[256]){
   fix16_t buff[256];
   fix_copy_array(256,_output_,buff);
   return ;
}

static_inline void synthSampler_Util_buffer_large(fix16_t (&_output_)[2048]){
   fix16_t buff[2048];
   fix_copy_array(2048,_output_,buff);
   return ;
}

typedef struct synthSampler_Util__ctx_type_6 {
   fix16_t x;
} synthSampler_Util__ctx_type_6;

typedef synthSampler_Util__ctx_type_6 synthSampler_Util_smooth_type;

static_inline void synthSampler_Util__ctx_type_6_init(synthSampler_Util__ctx_type_6 &_output_){
   synthSampler_Util__ctx_type_6 _ctx;
   _ctx.x = 0x0 /* 0.000000 */;
   _output_ = _ctx;
   return ;
}

static_inline void synthSampler_Util_smooth_init(synthSampler_Util__ctx_type_6 &_output_){
   synthSampler_Util__ctx_type_6_init(_output_);
   return ;
}

static_inline fix16_t synthSampler_Util_smooth(synthSampler_Util__ctx_type_6 &_ctx, fix16_t input, fix16_t coeff){
   _ctx.x = (_ctx.x + fix_mul(coeff,(input + (- _ctx.x))));
   return _ctx.x;
}

static_inline fix16_t synthSampler_Util_velocityToLevel(int velocity){
   velocity = int_clip(velocity,0,127);
   return fix_mul(0x204 /* 0.007874 */,int_to_fix(velocity));
}

typedef struct synthSampler_Notes__ctx_type_0 {
   uint8_t poly;
   int notes[128];
   int nb_notes;
   int last_notes[128];
} synthSampler_Notes__ctx_type_0;

typedef synthSampler_Notes__ctx_type_0 synthSampler_Notes_setPoly_type;

void synthSampler_Notes__ctx_type_0_init(synthSampler_Notes__ctx_type_0 &_output_);

static_inline void synthSampler_Notes_setPoly_init(synthSampler_Notes__ctx_type_0 &_output_){
   synthSampler_Notes__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthSampler_Notes_setPoly(synthSampler_Notes__ctx_type_0 &_ctx, uint8_t flag){
   _ctx.poly = flag;
};

typedef synthSampler_Notes__ctx_type_0 synthSampler_Notes_default_type;

static_inline void synthSampler_Notes_default_init(synthSampler_Notes__ctx_type_0 &_output_){
   synthSampler_Notes__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthSampler_Notes_default(synthSampler_Notes__ctx_type_0 &_ctx){
   synthSampler_Notes_setPoly(_ctx,false);
};

typedef synthSampler_Notes__ctx_type_0 synthSampler_Notes_nbNotes_type;

static_inline void synthSampler_Notes_nbNotes_init(synthSampler_Notes__ctx_type_0 &_output_){
   synthSampler_Notes__ctx_type_0_init(_output_);
   return ;
}

static_inline int synthSampler_Notes_nbNotes(synthSampler_Notes__ctx_type_0 &_ctx){
   return _ctx.nb_notes;
};

typedef synthSampler_Notes__ctx_type_0 synthSampler_Notes_firstNote_type;

static_inline void synthSampler_Notes_firstNote_init(synthSampler_Notes__ctx_type_0 &_output_){
   synthSampler_Notes__ctx_type_0_init(_output_);
   return ;
}

int synthSampler_Notes_firstNote(synthSampler_Notes__ctx_type_0 &_ctx);

typedef synthSampler_Notes__ctx_type_0 synthSampler_Notes_lastNote_type;

static_inline void synthSampler_Notes_lastNote_init(synthSampler_Notes__ctx_type_0 &_output_){
   synthSampler_Notes__ctx_type_0_init(_output_);
   return ;
}

int synthSampler_Notes_lastNote(synthSampler_Notes__ctx_type_0 &_ctx);

typedef synthSampler_Notes__ctx_type_0 synthSampler_Notes_noteOn_type;

static_inline void synthSampler_Notes_noteOn_init(synthSampler_Notes__ctx_type_0 &_output_){
   synthSampler_Notes__ctx_type_0_init(_output_);
   return ;
}

uint8_t synthSampler_Notes_noteOn(synthSampler_Notes__ctx_type_0 &_ctx, int note, int velocity, int channel);

typedef synthSampler_Notes__ctx_type_0 synthSampler_Notes_noteOff_type;

static_inline void synthSampler_Notes_noteOff_init(synthSampler_Notes__ctx_type_0 &_output_){
   synthSampler_Notes__ctx_type_0_init(_output_);
   return ;
}

uint8_t synthSampler_Notes_noteOff(synthSampler_Notes__ctx_type_0 &_ctx, int note, int channel);

static_inline int synthSampler_Sampler_ocarina_samples(){
   return 38836;
};

static_inline fix16_t synthSampler_Sampler_ocarina(int channel, int index){
   if(channel == 0){
      return fix_wrap_array(synthSampler_Sampler_ocarina_chan_0)[(index % 38836)];
   }
   return 0x0 /* 0.000000 */;
}

typedef struct synthSampler_Sampler__ctx_type_2 {
   fix16_t step;
   int state;
   int size;
   int sampleNote;
   fix16_t sampleFs;
   int posBase;
   fix16_t pos;
   synthSampler_Notes__ctx_type_0 playingnotes;
   fix16_t noteRatio;
   uint8_t loopy;
   int loopS;
   int loopE;
   fix16_t level;
   uint8_t gate;
   fix16_t fsRatio;
   fix16_t fs;
   uint8_t crossfade;
   fix16_t buffer_o[256];
   fix16_t buffer_cross[256];
} synthSampler_Sampler__ctx_type_2;

typedef synthSampler_Sampler__ctx_type_2 synthSampler_Sampler_getSample_type;

void synthSampler_Sampler__ctx_type_2_init(synthSampler_Sampler__ctx_type_2 &_output_);

static_inline void synthSampler_Sampler_getSample_init(synthSampler_Sampler__ctx_type_2 &_output_){
   synthSampler_Sampler__ctx_type_2_init(_output_);
   return ;
}

static_inline fix16_t synthSampler_Sampler_getSample(synthSampler_Sampler__ctx_type_2 &_ctx, int index){
   return synthSampler_Sampler_ocarina(0,index);
};

typedef synthSampler_Sampler__ctx_type_2 synthSampler_Sampler_process_type;

static_inline void synthSampler_Sampler_process_init(synthSampler_Sampler__ctx_type_2 &_output_){
   synthSampler_Sampler__ctx_type_2_init(_output_);
   return ;
}

fix16_t synthSampler_Sampler_process(synthSampler_Sampler__ctx_type_2 &_ctx);

typedef synthSampler_Sampler__ctx_type_2 synthSampler_Sampler_process_bufferTo_type;

static_inline void synthSampler_Sampler_process_bufferTo_init(synthSampler_Sampler__ctx_type_2 &_output_){
   synthSampler_Sampler__ctx_type_2_init(_output_);
   return ;
}

void synthSampler_Sampler_process_bufferTo(synthSampler_Sampler__ctx_type_2 &_ctx, int nb, fix16_t (&oBuffer)[256]);

typedef synthSampler_Sampler__ctx_type_2 synthSampler_Sampler_process_buffer_type;

static_inline void synthSampler_Sampler_process_buffer_init(synthSampler_Sampler__ctx_type_2 &_output_){
   synthSampler_Sampler__ctx_type_2_init(_output_);
   return ;
}

static_inline void synthSampler_Sampler_process_buffer(synthSampler_Sampler__ctx_type_2 &_ctx, int nb){
   synthSampler_Sampler_process_bufferTo(_ctx,nb,_ctx.buffer_o);
};

typedef synthSampler_Sampler__ctx_type_2 synthSampler_Sampler_updateStep_type;

static_inline void synthSampler_Sampler_updateStep_init(synthSampler_Sampler__ctx_type_2 &_output_){
   synthSampler_Sampler__ctx_type_2_init(_output_);
   return ;
}

static_inline void synthSampler_Sampler_updateStep(synthSampler_Sampler__ctx_type_2 &_ctx){
   _ctx.step = fix_mul(_ctx.fsRatio,_ctx.noteRatio);
};

typedef synthSampler_Sampler__ctx_type_2 synthSampler_Sampler_setSamplerate_type;

static_inline void synthSampler_Sampler_setSamplerate_init(synthSampler_Sampler__ctx_type_2 &_output_){
   synthSampler_Sampler__ctx_type_2_init(_output_);
   return ;
}

void synthSampler_Sampler_setSamplerate(synthSampler_Sampler__ctx_type_2 &_ctx, fix16_t newFs);

typedef synthSampler_Sampler__ctx_type_2 synthSampler_Sampler_updateCrossFade_type;

static_inline void synthSampler_Sampler_updateCrossFade_init(synthSampler_Sampler__ctx_type_2 &_output_){
   synthSampler_Sampler__ctx_type_2_init(_output_);
   return ;
}

void synthSampler_Sampler_updateCrossFade(synthSampler_Sampler__ctx_type_2 &_ctx);

typedef synthSampler_Sampler__ctx_type_2 synthSampler_Sampler_setLoop_type;

static_inline void synthSampler_Sampler_setLoop_init(synthSampler_Sampler__ctx_type_2 &_output_){
   synthSampler_Sampler__ctx_type_2_init(_output_);
   return ;
}

static_inline void synthSampler_Sampler_setLoop(synthSampler_Sampler__ctx_type_2 &_ctx, uint8_t loop){
   _ctx.loopy = loop;
};

typedef synthSampler_Sampler__ctx_type_2 synthSampler_Sampler_setLoopStart_type;

static_inline void synthSampler_Sampler_setLoopStart_init(synthSampler_Sampler__ctx_type_2 &_output_){
   synthSampler_Sampler__ctx_type_2_init(_output_);
   return ;
}

static_inline void synthSampler_Sampler_setLoopStart(synthSampler_Sampler__ctx_type_2 &_ctx, int newLoopS){
   _ctx.loopS = int_clip(newLoopS,0,_ctx.size);
   synthSampler_Sampler_updateCrossFade(_ctx);
}

typedef synthSampler_Sampler__ctx_type_2 synthSampler_Sampler_setLoopEnd_type;

static_inline void synthSampler_Sampler_setLoopEnd_init(synthSampler_Sampler__ctx_type_2 &_output_){
   synthSampler_Sampler__ctx_type_2_init(_output_);
   return ;
}

static_inline void synthSampler_Sampler_setLoopEnd(synthSampler_Sampler__ctx_type_2 &_ctx, int newLoopE){
   _ctx.loopE = int_clip(newLoopE,0,_ctx.size);
   synthSampler_Sampler_updateCrossFade(_ctx);
}

typedef synthSampler_Sampler__ctx_type_2 synthSampler_Sampler_getSampleSize_type;

static_inline void synthSampler_Sampler_getSampleSize_init(synthSampler_Sampler__ctx_type_2 &_output_){
   synthSampler_Sampler__ctx_type_2_init(_output_);
   return ;
}

static_inline int synthSampler_Sampler_getSampleSize(synthSampler_Sampler__ctx_type_2 &_ctx){
   return _ctx.size;
};

typedef synthSampler_Sampler__ctx_type_2 synthSampler_Sampler_setNote_type;

static_inline void synthSampler_Sampler_setNote_init(synthSampler_Sampler__ctx_type_2 &_output_){
   synthSampler_Sampler__ctx_type_2_init(_output_);
   return ;
}

void synthSampler_Sampler_setNote(synthSampler_Sampler__ctx_type_2 &_ctx, int note);

typedef synthSampler_Sampler__ctx_type_2 synthSampler_Sampler_setLevel_type;

static_inline void synthSampler_Sampler_setLevel_init(synthSampler_Sampler__ctx_type_2 &_output_){
   synthSampler_Sampler__ctx_type_2_init(_output_);
   return ;
}

static_inline void synthSampler_Sampler_setLevel(synthSampler_Sampler__ctx_type_2 &_ctx, fix16_t newLevel){
   _ctx.level = newLevel;
};

typedef synthSampler_Sampler__ctx_type_2 synthSampler_Sampler_noteOn_type;

static_inline void synthSampler_Sampler_noteOn_init(synthSampler_Sampler__ctx_type_2 &_output_){
   synthSampler_Sampler__ctx_type_2_init(_output_);
   return ;
}

void synthSampler_Sampler_noteOn(synthSampler_Sampler__ctx_type_2 &_ctx, int note, int velocity, int channel);

typedef synthSampler_Sampler__ctx_type_2 synthSampler_Sampler_setPoly_type;

static_inline void synthSampler_Sampler_setPoly_init(synthSampler_Sampler__ctx_type_2 &_output_){
   synthSampler_Sampler__ctx_type_2_init(_output_);
   return ;
}

static_inline void synthSampler_Sampler_setPoly(synthSampler_Sampler__ctx_type_2 &_ctx, uint8_t flag){
   synthSampler_Notes_setPoly(_ctx.playingnotes,flag);
};

typedef synthSampler_Sampler__ctx_type_2 synthSampler_Sampler_noteOff_type;

static_inline void synthSampler_Sampler_noteOff_init(synthSampler_Sampler__ctx_type_2 &_output_){
   synthSampler_Sampler__ctx_type_2_init(_output_);
   return ;
}

void synthSampler_Sampler_noteOff(synthSampler_Sampler__ctx_type_2 &_ctx, int note, int channel);

typedef synthSampler_Sampler__ctx_type_2 synthSampler_Sampler_default_type;

static_inline void synthSampler_Sampler_default_init(synthSampler_Sampler__ctx_type_2 &_output_){
   synthSampler_Sampler__ctx_type_2_init(_output_);
   return ;
}

void synthSampler_Sampler_default(synthSampler_Sampler__ctx_type_2 &_ctx);

typedef struct synthSampler_Poly__ctx_type_0 {
   synthSampler_Sampler__ctx_type_2 voice3;
   synthSampler_Sampler__ctx_type_2 voice2;
   synthSampler_Sampler__ctx_type_2 voice1;
   synthSampler_Sampler__ctx_type_2 voice0;
   uint8_t should_leftovers;
} synthSampler_Poly__ctx_type_0;

typedef synthSampler_Poly__ctx_type_0 synthSampler_Poly_getSample_type;

void synthSampler_Poly__ctx_type_0_init(synthSampler_Poly__ctx_type_0 &_output_);

static_inline void synthSampler_Poly_getSample_init(synthSampler_Poly__ctx_type_0 &_output_){
   synthSampler_Poly__ctx_type_0_init(_output_);
   return ;
}

fix16_t synthSampler_Poly_getSample(synthSampler_Poly__ctx_type_0 &_ctx, int voice);

typedef synthSampler_Poly__ctx_type_0 synthSampler_Poly_runVoice_type;

static_inline void synthSampler_Poly_runVoice_init(synthSampler_Poly__ctx_type_0 &_output_){
   synthSampler_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthSampler_Poly_runVoice(synthSampler_Poly__ctx_type_0 &_ctx, int voice, int nb, fix16_t (&buff)[256]){
   switch(voice) {
      case 0:
         synthSampler_Sampler_process_bufferTo(_ctx.voice0,nb,buff);
      break;
      case 1:
         synthSampler_Sampler_process_bufferTo(_ctx.voice1,nb,buff);
      break;
      case 2:
         synthSampler_Sampler_process_bufferTo(_ctx.voice2,nb,buff);
      break;
      case 3:
         synthSampler_Sampler_process_bufferTo(_ctx.voice3,nb,buff);
      break;
    
   }
};

typedef synthSampler_Poly__ctx_type_0 synthSampler_Poly_sendNoteOn_type;

static_inline void synthSampler_Poly_sendNoteOn_init(synthSampler_Poly__ctx_type_0 &_output_){
   synthSampler_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthSampler_Poly_sendNoteOn(synthSampler_Poly__ctx_type_0 &_ctx, int voice, int note, int velocity, int channel){
   switch(voice) {
      case 0:
         synthSampler_Sampler_noteOn(_ctx.voice0,note,velocity,channel);
      break;
      case 1:
         synthSampler_Sampler_noteOn(_ctx.voice1,note,velocity,channel);
      break;
      case 2:
         synthSampler_Sampler_noteOn(_ctx.voice2,note,velocity,channel);
      break;
      case 3:
         synthSampler_Sampler_noteOn(_ctx.voice3,note,velocity,channel);
      break;
    
   }
};

typedef synthSampler_Poly__ctx_type_0 synthSampler_Poly_sendNoteOff_type;

static_inline void synthSampler_Poly_sendNoteOff_init(synthSampler_Poly__ctx_type_0 &_output_){
   synthSampler_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthSampler_Poly_sendNoteOff(synthSampler_Poly__ctx_type_0 &_ctx, int voice, int note, int channel){
   switch(voice) {
      case 0:
         synthSampler_Sampler_noteOff(_ctx.voice0,note,channel);
      break;
      case 1:
         synthSampler_Sampler_noteOff(_ctx.voice1,note,channel);
      break;
      case 2:
         synthSampler_Sampler_noteOff(_ctx.voice2,note,channel);
      break;
      case 3:
         synthSampler_Sampler_noteOff(_ctx.voice3,note,channel);
      break;
    
   }
};

typedef synthSampler_Poly__ctx_type_0 synthSampler_Poly_setSamplerate_type;

static_inline void synthSampler_Poly_setSamplerate_init(synthSampler_Poly__ctx_type_0 &_output_){
   synthSampler_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthSampler_Poly_setSamplerate(synthSampler_Poly__ctx_type_0 &_ctx, fix16_t fs){
   synthSampler_Sampler_setSamplerate(_ctx.voice0,fs);
   synthSampler_Sampler_setSamplerate(_ctx.voice1,fs);
   synthSampler_Sampler_setSamplerate(_ctx.voice2,fs);
   synthSampler_Sampler_setSamplerate(_ctx.voice3,fs);
}

typedef synthSampler_Poly__ctx_type_0 synthSampler_Poly_synthSetLoop_type;

static_inline void synthSampler_Poly_synthSetLoop_init(synthSampler_Poly__ctx_type_0 &_output_){
   synthSampler_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthSampler_Poly_synthSetLoop(synthSampler_Poly__ctx_type_0 &_ctx, uint8_t flag){
   synthSampler_Sampler_setLoop(_ctx.voice0,flag);
   synthSampler_Sampler_setLoop(_ctx.voice1,flag);
   synthSampler_Sampler_setLoop(_ctx.voice2,flag);
   synthSampler_Sampler_setLoop(_ctx.voice3,flag);
}

typedef synthSampler_Poly__ctx_type_0 synthSampler_Poly_synthSetLoopStart_type;

static_inline void synthSampler_Poly_synthSetLoopStart_init(synthSampler_Poly__ctx_type_0 &_output_){
   synthSampler_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthSampler_Poly_synthSetLoopStart(synthSampler_Poly__ctx_type_0 &_ctx, int value){
   synthSampler_Sampler_setLoopStart(_ctx.voice0,value);
   synthSampler_Sampler_setLoopStart(_ctx.voice1,value);
   synthSampler_Sampler_setLoopStart(_ctx.voice2,value);
   synthSampler_Sampler_setLoopStart(_ctx.voice3,value);
}

typedef synthSampler_Poly__ctx_type_0 synthSampler_Poly_synthSetLoopEnd_type;

static_inline void synthSampler_Poly_synthSetLoopEnd_init(synthSampler_Poly__ctx_type_0 &_output_){
   synthSampler_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthSampler_Poly_synthSetLoopEnd(synthSampler_Poly__ctx_type_0 &_ctx, int value){
   synthSampler_Sampler_setLoopEnd(_ctx.voice0,value);
   synthSampler_Sampler_setLoopEnd(_ctx.voice1,value);
   synthSampler_Sampler_setLoopEnd(_ctx.voice2,value);
   synthSampler_Sampler_setLoopEnd(_ctx.voice3,value);
}

typedef synthSampler_Poly__ctx_type_0 synthSampler_Poly_synthGetSize_type;

static_inline void synthSampler_Poly_synthGetSize_init(synthSampler_Poly__ctx_type_0 &_output_){
   synthSampler_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline int synthSampler_Poly_synthGetSize(synthSampler_Poly__ctx_type_0 &_ctx){
   return synthSampler_Sampler_getSampleSize(_ctx.voice0);
};

typedef synthSampler_Poly__ctx_type_0 synthSampler_Poly_synthGetNbWavetables_type;

static_inline void synthSampler_Poly_synthGetNbWavetables_init(synthSampler_Poly__ctx_type_0 &_output_){
   synthSampler_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline int synthSampler_Poly_synthGetNbWavetables(synthSampler_Poly__ctx_type_0 &_ctx){
   return 0;
};

typedef synthSampler_Poly__ctx_type_0 synthSampler_Poly_synthSetModulatorWavetable_type;

static_inline void synthSampler_Poly_synthSetModulatorWavetable_init(synthSampler_Poly__ctx_type_0 &_output_){
   synthSampler_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthSampler_Poly_synthSetModulatorWavetable(synthSampler_Poly__ctx_type_0 &_ctx, fix16_t wavetableIdx){
}

typedef synthSampler_Poly__ctx_type_0 synthSampler_Poly_synthSetCarrierWavetable_type;

static_inline void synthSampler_Poly_synthSetCarrierWavetable_init(synthSampler_Poly__ctx_type_0 &_output_){
   synthSampler_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthSampler_Poly_synthSetCarrierWavetable(synthSampler_Poly__ctx_type_0 &_ctx, fix16_t wavetableIdx){
}

typedef synthSampler_Poly__ctx_type_0 synthSampler_Poly_synthSetModulatorRatio_type;

static_inline void synthSampler_Poly_synthSetModulatorRatio_init(synthSampler_Poly__ctx_type_0 &_output_){
   synthSampler_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthSampler_Poly_synthSetModulatorRatio(synthSampler_Poly__ctx_type_0 &_ctx, fix16_t ratio){
}

typedef synthSampler_Poly__ctx_type_0 synthSampler_Poly_synthSetCarrierRatio_type;

static_inline void synthSampler_Poly_synthSetCarrierRatio_init(synthSampler_Poly__ctx_type_0 &_output_){
   synthSampler_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthSampler_Poly_synthSetCarrierRatio(synthSampler_Poly__ctx_type_0 &_ctx, fix16_t ratio){
}

typedef synthSampler_Poly__ctx_type_0 synthSampler_Poly_synthSetModulatorLevel_type;

static_inline void synthSampler_Poly_synthSetModulatorLevel_init(synthSampler_Poly__ctx_type_0 &_output_){
   synthSampler_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthSampler_Poly_synthSetModulatorLevel(synthSampler_Poly__ctx_type_0 &_ctx, fix16_t level){
}

typedef synthSampler_Poly__ctx_type_0 synthSampler_Poly_synthSetModulatorADSR_type;

static_inline void synthSampler_Poly_synthSetModulatorADSR_init(synthSampler_Poly__ctx_type_0 &_output_){
   synthSampler_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthSampler_Poly_synthSetModulatorADSR(synthSampler_Poly__ctx_type_0 &_ctx, fix16_t a, fix16_t d, fix16_t s, fix16_t r){
}

typedef synthSampler_Poly__ctx_type_0 synthSampler_Poly_synthSetCarrierADSR_type;

static_inline void synthSampler_Poly_synthSetCarrierADSR_init(synthSampler_Poly__ctx_type_0 &_output_){
   synthSampler_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthSampler_Poly_synthSetCarrierADSR(synthSampler_Poly__ctx_type_0 &_ctx, fix16_t a, fix16_t d, fix16_t s, fix16_t r){
}

typedef synthSampler_Poly__ctx_type_0 synthSampler_Poly_shouldLeftOvers_type;

static_inline void synthSampler_Poly_shouldLeftOvers_init(synthSampler_Poly__ctx_type_0 &_output_){
   synthSampler_Poly__ctx_type_0_init(_output_);
   return ;
}

static_inline uint8_t synthSampler_Poly_shouldLeftOvers(synthSampler_Poly__ctx_type_0 &_ctx){
   return _ctx.should_leftovers;
};

typedef synthSampler_Poly__ctx_type_0 synthSampler_Poly_default_type;

static_inline void synthSampler_Poly_default_init(synthSampler_Poly__ctx_type_0 &_output_){
   synthSampler_Poly__ctx_type_0_init(_output_);
   return ;
}

void synthSampler_Poly_default(synthSampler_Poly__ctx_type_0 &_ctx);

typedef struct synthSampler_Voice__ctx_type_0 {
   synthSampler_Notes__ctx_type_0 voicesinactive;
   synthSampler_Notes__ctx_type_0 voicesactive;
   fix16_t voices_ratio;
   int voices[4];
   synthSampler_Poly__ctx_type_0 poly;
   int number_voices;
   int notes[128];
   uint8_t normalize;
   fix16_t leftovers_decay;
   fix16_t leftovers;
   int last_velocities[4];
   fix16_t last_values[4];
   fix16_t fs;
   fix16_t buffer_v3[256];
   fix16_t buffer_v2[256];
   fix16_t buffer_v1[256];
   fix16_t buffer_v0[256];
} synthSampler_Voice__ctx_type_0;

typedef synthSampler_Voice__ctx_type_0 synthSampler_Voice_process_type;

void synthSampler_Voice__ctx_type_0_init(synthSampler_Voice__ctx_type_0 &_output_);

static_inline void synthSampler_Voice_process_init(synthSampler_Voice__ctx_type_0 &_output_){
   synthSampler_Voice__ctx_type_0_init(_output_);
   return ;
}

fix16_t synthSampler_Voice_process(synthSampler_Voice__ctx_type_0 &_ctx);

typedef synthSampler_Voice__ctx_type_0 synthSampler_Voice_process_bufferTo_type;

static_inline void synthSampler_Voice_process_bufferTo_init(synthSampler_Voice__ctx_type_0 &_output_){
   synthSampler_Voice__ctx_type_0_init(_output_);
   return ;
}

void synthSampler_Voice_process_bufferTo(synthSampler_Voice__ctx_type_0 &_ctx, int nb, fix16_t (&oBuffer)[256]);

typedef synthSampler_Voice__ctx_type_0 synthSampler_Voice_process_bufferTo_alt_type;

static_inline void synthSampler_Voice_process_bufferTo_alt_init(synthSampler_Voice__ctx_type_0 &_output_){
   synthSampler_Voice__ctx_type_0_init(_output_);
   return ;
}

void synthSampler_Voice_process_bufferTo_alt(synthSampler_Voice__ctx_type_0 &_ctx, int nb, fix16_t (&oBuffer)[256]);

typedef synthSampler_Voice__ctx_type_0 synthSampler_Voice_noteOff_type;

static_inline void synthSampler_Voice_noteOff_init(synthSampler_Voice__ctx_type_0 &_output_){
   synthSampler_Voice__ctx_type_0_init(_output_);
   return ;
}

void synthSampler_Voice_noteOff(synthSampler_Voice__ctx_type_0 &_ctx, int note, int channel);

typedef synthSampler_Voice__ctx_type_0 synthSampler_Voice_noteOn_type;

static_inline void synthSampler_Voice_noteOn_init(synthSampler_Voice__ctx_type_0 &_output_){
   synthSampler_Voice__ctx_type_0_init(_output_);
   return ;
}

void synthSampler_Voice_noteOn(synthSampler_Voice__ctx_type_0 &_ctx, int note, int velocity, int channel);

typedef synthSampler_Voice__ctx_type_0 synthSampler_Voice_setNbVoices_type;

static_inline void synthSampler_Voice_setNbVoices_init(synthSampler_Voice__ctx_type_0 &_output_){
   synthSampler_Voice__ctx_type_0_init(_output_);
   return ;
}

void synthSampler_Voice_setNbVoices(synthSampler_Voice__ctx_type_0 &_ctx, int nbvoices);

typedef synthSampler_Voice__ctx_type_0 synthSampler_Voice_setNormalize_type;

static_inline void synthSampler_Voice_setNormalize_init(synthSampler_Voice__ctx_type_0 &_output_){
   synthSampler_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthSampler_Voice_setNormalize(synthSampler_Voice__ctx_type_0 &_ctx, uint8_t flag){
   _ctx.normalize = flag;
};

typedef synthSampler_Voice__ctx_type_0 synthSampler_Voice_setSamplerate_type;

static_inline void synthSampler_Voice_setSamplerate_init(synthSampler_Voice__ctx_type_0 &_output_){
   synthSampler_Voice__ctx_type_0_init(_output_);
   return ;
}

void synthSampler_Voice_setSamplerate(synthSampler_Voice__ctx_type_0 &_ctx, fix16_t newFs);

typedef synthSampler_Voice__ctx_type_0 synthSampler_Voice_synthSetLoop_type;

static_inline void synthSampler_Voice_synthSetLoop_init(synthSampler_Voice__ctx_type_0 &_output_){
   synthSampler_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthSampler_Voice_synthSetLoop(synthSampler_Voice__ctx_type_0 &_ctx, uint8_t flag){
   synthSampler_Poly_synthSetLoop(_ctx.poly,flag);
};

typedef synthSampler_Voice__ctx_type_0 synthSampler_Voice_synthSetLoopStart_type;

static_inline void synthSampler_Voice_synthSetLoopStart_init(synthSampler_Voice__ctx_type_0 &_output_){
   synthSampler_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthSampler_Voice_synthSetLoopStart(synthSampler_Voice__ctx_type_0 &_ctx, int value){
   synthSampler_Poly_synthSetLoopStart(_ctx.poly,value);
};

typedef synthSampler_Voice__ctx_type_0 synthSampler_Voice_synthSetLoopEnd_type;

static_inline void synthSampler_Voice_synthSetLoopEnd_init(synthSampler_Voice__ctx_type_0 &_output_){
   synthSampler_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthSampler_Voice_synthSetLoopEnd(synthSampler_Voice__ctx_type_0 &_ctx, int value){
   synthSampler_Poly_synthSetLoopEnd(_ctx.poly,value);
};

typedef synthSampler_Voice__ctx_type_0 synthSampler_Voice_synthGetSize_type;

static_inline void synthSampler_Voice_synthGetSize_init(synthSampler_Voice__ctx_type_0 &_output_){
   synthSampler_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline int synthSampler_Voice_synthGetSize(synthSampler_Voice__ctx_type_0 &_ctx){
   return synthSampler_Poly_synthGetSize(_ctx.poly);
};

typedef synthSampler_Voice__ctx_type_0 synthSampler_Voice_synthGetNbWavetables_type;

static_inline void synthSampler_Voice_synthGetNbWavetables_init(synthSampler_Voice__ctx_type_0 &_output_){
   synthSampler_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline int synthSampler_Voice_synthGetNbWavetables(synthSampler_Voice__ctx_type_0 &_ctx){
   return synthSampler_Poly_synthGetNbWavetables(_ctx.poly);
};

typedef synthSampler_Voice__ctx_type_0 synthSampler_Voice_synthSetModulatorWavetable_type;

static_inline void synthSampler_Voice_synthSetModulatorWavetable_init(synthSampler_Voice__ctx_type_0 &_output_){
   synthSampler_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthSampler_Voice_synthSetModulatorWavetable(synthSampler_Voice__ctx_type_0 &_ctx, fix16_t wavetableIdx){
   synthSampler_Poly_synthSetModulatorWavetable(_ctx.poly,wavetableIdx);
};

typedef synthSampler_Voice__ctx_type_0 synthSampler_Voice_synthSetCarrierWavetable_type;

static_inline void synthSampler_Voice_synthSetCarrierWavetable_init(synthSampler_Voice__ctx_type_0 &_output_){
   synthSampler_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthSampler_Voice_synthSetCarrierWavetable(synthSampler_Voice__ctx_type_0 &_ctx, fix16_t wavetableIdx){
   synthSampler_Poly_synthSetCarrierWavetable(_ctx.poly,wavetableIdx);
};

typedef synthSampler_Voice__ctx_type_0 synthSampler_Voice_synthSetModulatorRatio_type;

static_inline void synthSampler_Voice_synthSetModulatorRatio_init(synthSampler_Voice__ctx_type_0 &_output_){
   synthSampler_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthSampler_Voice_synthSetModulatorRatio(synthSampler_Voice__ctx_type_0 &_ctx, fix16_t ratio){
   synthSampler_Poly_synthSetModulatorRatio(_ctx.poly,ratio);
};

typedef synthSampler_Voice__ctx_type_0 synthSampler_Voice_synthSetCarrierRatio_type;

static_inline void synthSampler_Voice_synthSetCarrierRatio_init(synthSampler_Voice__ctx_type_0 &_output_){
   synthSampler_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthSampler_Voice_synthSetCarrierRatio(synthSampler_Voice__ctx_type_0 &_ctx, fix16_t ratio){
   synthSampler_Poly_synthSetCarrierRatio(_ctx.poly,ratio);
};

typedef synthSampler_Voice__ctx_type_0 synthSampler_Voice_synthSetModulatorLevel_type;

static_inline void synthSampler_Voice_synthSetModulatorLevel_init(synthSampler_Voice__ctx_type_0 &_output_){
   synthSampler_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthSampler_Voice_synthSetModulatorLevel(synthSampler_Voice__ctx_type_0 &_ctx, fix16_t level){
   synthSampler_Poly_synthSetModulatorLevel(_ctx.poly,level);
};

typedef synthSampler_Voice__ctx_type_0 synthSampler_Voice_synthSetModulatorADSR_type;

static_inline void synthSampler_Voice_synthSetModulatorADSR_init(synthSampler_Voice__ctx_type_0 &_output_){
   synthSampler_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthSampler_Voice_synthSetModulatorADSR(synthSampler_Voice__ctx_type_0 &_ctx, fix16_t a, fix16_t d, fix16_t s, fix16_t r){
   synthSampler_Poly_synthSetModulatorADSR(_ctx.poly,a,d,s,r);
};

typedef synthSampler_Voice__ctx_type_0 synthSampler_Voice_synthSetCarrierADSR_type;

static_inline void synthSampler_Voice_synthSetCarrierADSR_init(synthSampler_Voice__ctx_type_0 &_output_){
   synthSampler_Voice__ctx_type_0_init(_output_);
   return ;
}

static_inline void synthSampler_Voice_synthSetCarrierADSR(synthSampler_Voice__ctx_type_0 &_ctx, fix16_t a, fix16_t d, fix16_t s, fix16_t r){
   synthSampler_Poly_synthSetCarrierADSR(_ctx.poly,a,d,s,r);
};

typedef synthSampler_Voice__ctx_type_0 synthSampler_Voice_default_type;

static_inline void synthSampler_Voice_default_init(synthSampler_Voice__ctx_type_0 &_output_){
   synthSampler_Voice__ctx_type_0_init(_output_);
   return ;
}

void synthSampler_Voice_default(synthSampler_Voice__ctx_type_0 &_ctx);

int synthSampler_Processor_cvToPitch(fix16_t cv);

typedef struct synthSampler_Processor__ctx_type_1 {
   synthSampler_Voice__ctx_type_0 voice;
   fix16_t process_ret_3;
   fix16_t process_ret_2;
   fix16_t process_ret_1;
   fix16_t process_ret_0;
   fix16_t param4;
   fix16_t param3;
   fix16_t param2;
   fix16_t param1;
   int last_pitches[16];
   int last_nbcables;
   uint8_t last_gates[16];
   fix16_t fs;
} synthSampler_Processor__ctx_type_1;

typedef synthSampler_Processor__ctx_type_1 synthSampler_Processor_process_type;

void synthSampler_Processor__ctx_type_1_init(synthSampler_Processor__ctx_type_1 &_output_);

static_inline void synthSampler_Processor_process_init(synthSampler_Processor__ctx_type_1 &_output_){
   synthSampler_Processor__ctx_type_1_init(_output_);
   return ;
}

void synthSampler_Processor_process(synthSampler_Processor__ctx_type_1 &_ctx, fix16_t in4, fix16_t fs);

typedef synthSampler_Processor__ctx_type_1 synthSampler_Processor_process_ret_0_type;

static_inline void synthSampler_Processor_process_ret_0_init(synthSampler_Processor__ctx_type_1 &_output_){
   synthSampler_Processor__ctx_type_1_init(_output_);
   return ;
}

static_inline fix16_t synthSampler_Processor_process_ret_0(synthSampler_Processor__ctx_type_1 &_ctx){
   return _ctx.process_ret_0;
};

typedef synthSampler_Processor__ctx_type_1 synthSampler_Processor_process_ret_1_type;

static_inline void synthSampler_Processor_process_ret_1_init(synthSampler_Processor__ctx_type_1 &_output_){
   synthSampler_Processor__ctx_type_1_init(_output_);
   return ;
}

static_inline fix16_t synthSampler_Processor_process_ret_1(synthSampler_Processor__ctx_type_1 &_ctx){
   return _ctx.process_ret_1;
};

typedef synthSampler_Processor__ctx_type_1 synthSampler_Processor_process_ret_2_type;

static_inline void synthSampler_Processor_process_ret_2_init(synthSampler_Processor__ctx_type_1 &_output_){
   synthSampler_Processor__ctx_type_1_init(_output_);
   return ;
}

static_inline fix16_t synthSampler_Processor_process_ret_2(synthSampler_Processor__ctx_type_1 &_ctx){
   return _ctx.process_ret_2;
};

typedef synthSampler_Processor__ctx_type_1 synthSampler_Processor_process_ret_3_type;

static_inline void synthSampler_Processor_process_ret_3_init(synthSampler_Processor__ctx_type_1 &_output_){
   synthSampler_Processor__ctx_type_1_init(_output_);
   return ;
}

static_inline fix16_t synthSampler_Processor_process_ret_3(synthSampler_Processor__ctx_type_1 &_ctx){
   return _ctx.process_ret_3;
};

typedef synthSampler_Processor__ctx_type_1 synthSampler_Processor_setNote_type;

static_inline void synthSampler_Processor_setNote_init(synthSampler_Processor__ctx_type_1 &_output_){
   synthSampler_Processor__ctx_type_1_init(_output_);
   return ;
}

void synthSampler_Processor_setNote(synthSampler_Processor__ctx_type_1 &_ctx, fix16_t gate, fix16_t voct, fix16_t vel, int cable);

typedef synthSampler_Processor__ctx_type_1 synthSampler_Processor_nbCables_type;

static_inline void synthSampler_Processor_nbCables_init(synthSampler_Processor__ctx_type_1 &_output_){
   synthSampler_Processor__ctx_type_1_init(_output_);
   return ;
}

void synthSampler_Processor_nbCables(synthSampler_Processor__ctx_type_1 &_ctx, int nbcables);

typedef synthSampler_Processor__ctx_type_1 synthSampler_Processor_setParam1_type;

static_inline void synthSampler_Processor_setParam1_init(synthSampler_Processor__ctx_type_1 &_output_){
   synthSampler_Processor__ctx_type_1_init(_output_);
   return ;
}

static_inline void synthSampler_Processor_setParam1(synthSampler_Processor__ctx_type_1 &_ctx, fix16_t knob, fix16_t mod, fix16_t input){
   _ctx.param1 = fix_clip((knob + fix_mul(input,mod)),0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
};

typedef synthSampler_Processor__ctx_type_1 synthSampler_Processor_setParam2_type;

static_inline void synthSampler_Processor_setParam2_init(synthSampler_Processor__ctx_type_1 &_output_){
   synthSampler_Processor__ctx_type_1_init(_output_);
   return ;
}

static_inline void synthSampler_Processor_setParam2(synthSampler_Processor__ctx_type_1 &_ctx, fix16_t knob, fix16_t mod, fix16_t input){
   _ctx.param2 = fix_clip((knob + fix_mul(input,mod)),0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
};

typedef synthSampler_Processor__ctx_type_1 synthSampler_Processor_setParam3_type;

static_inline void synthSampler_Processor_setParam3_init(synthSampler_Processor__ctx_type_1 &_output_){
   synthSampler_Processor__ctx_type_1_init(_output_);
   return ;
}

static_inline void synthSampler_Processor_setParam3(synthSampler_Processor__ctx_type_1 &_ctx, fix16_t knob, fix16_t mod, fix16_t input){
   _ctx.param3 = fix_clip((knob + fix_mul(input,mod)),0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
};

typedef synthSampler_Processor__ctx_type_1 synthSampler_Processor_setParam4_type;

static_inline void synthSampler_Processor_setParam4_init(synthSampler_Processor__ctx_type_1 &_output_){
   synthSampler_Processor__ctx_type_1_init(_output_);
   return ;
}

static_inline void synthSampler_Processor_setParam4(synthSampler_Processor__ctx_type_1 &_ctx, fix16_t knob, fix16_t mod, fix16_t input){
   _ctx.param4 = fix_clip((knob + fix_mul(input,mod)),0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
};

typedef synthSampler_Processor__ctx_type_1 synthSampler_Processor_setSamplerate_type;

static_inline void synthSampler_Processor_setSamplerate_init(synthSampler_Processor__ctx_type_1 &_output_){
   synthSampler_Processor__ctx_type_1_init(_output_);
   return ;
}

static_inline void synthSampler_Processor_setSamplerate(synthSampler_Processor__ctx_type_1 &_ctx, fix16_t newFs){
   if(newFs > 0x0 /* 0.000000 */){
      _ctx.fs = newFs;
      synthSampler_Voice_setSamplerate(_ctx.voice,_ctx.fs);
   }
};

typedef synthSampler_Processor__ctx_type_1 synthSampler_Processor_default_type;

static_inline void synthSampler_Processor_default_init(synthSampler_Processor__ctx_type_1 &_output_){
   synthSampler_Processor__ctx_type_1_init(_output_);
   return ;
}

void synthSampler_Processor_default(synthSampler_Processor__ctx_type_1 &_ctx);



#endif // ENGINE_SYNTHSAMPLER_H
