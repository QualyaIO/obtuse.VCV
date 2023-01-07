
/* Code automatically generated by Vult https://github.com/modlfo/vult */
#ifndef ENGINE_EFFECTS_H
#define ENGINE_EFFECTS_H
#include <stdint.h>
#include <math.h>
#include "vultin.h"
#include "engine_effects.tables.h"

typedef struct _tuple___real_real_real_real__ {
   fix16_t field_0;
   fix16_t field_1;
   fix16_t field_2;
   fix16_t field_3;
} _tuple___real_real_real_real__;

static_inline fix16_t Util_noteToFrequency(int note){
   return fix_mul(0x217 /* 0.008176 */,fix_exp(fix_mul(0xec9 /* 0.057762 */,int_to_fix(note))));
};

typedef struct Util__ctx_type_1 {
   uint8_t pre;
} Util__ctx_type_1;

typedef Util__ctx_type_1 Util_edge_type;

static_inline void Util__ctx_type_1_init(Util__ctx_type_1 &_output_){
   Util__ctx_type_1 _ctx;
   _ctx.pre = false;
   _output_ = _ctx;
   return ;
}

static_inline void Util_edge_init(Util__ctx_type_1 &_output_){
   Util__ctx_type_1_init(_output_);
   return ;
}

static_inline uint8_t Util_edge(Util__ctx_type_1 &_ctx, uint8_t x){
   uint8_t ret;
   ret = (x && bool_not(_ctx.pre));
   _ctx.pre = x;
   return ret;
}

static_inline fix16_t Util_cubic_clipper(fix16_t x){
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

typedef struct Util__ctx_type_3 {
   fix16_t pre_x;
} Util__ctx_type_3;

typedef Util__ctx_type_3 Util_change_type;

static_inline void Util__ctx_type_3_init(Util__ctx_type_3 &_output_){
   Util__ctx_type_3 _ctx;
   _ctx.pre_x = 0x0 /* 0.000000 */;
   _output_ = _ctx;
   return ;
}

static_inline void Util_change_init(Util__ctx_type_3 &_output_){
   Util__ctx_type_3_init(_output_);
   return ;
}

static_inline uint8_t Util_change(Util__ctx_type_3 &_ctx, fix16_t x){
   uint8_t v;
   v = (_ctx.pre_x != x);
   _ctx.pre_x = x;
   return v;
}

static_inline void Util_buffer(fix16_t (&_output_)[256]){
   fix16_t buff[256];
   fix_copy_array(256,_output_,buff);
   return ;
}

static_inline void Util_buffer_large(fix16_t (&_output_)[2048]){
   fix16_t buff[2048];
   fix_copy_array(2048,_output_,buff);
   return ;
}

typedef struct Util__ctx_type_6 {
   fix16_t x;
} Util__ctx_type_6;

typedef Util__ctx_type_6 Util_smooth_type;

static_inline void Util__ctx_type_6_init(Util__ctx_type_6 &_output_){
   Util__ctx_type_6 _ctx;
   _ctx.x = 0x0 /* 0.000000 */;
   _output_ = _ctx;
   return ;
}

static_inline void Util_smooth_init(Util__ctx_type_6 &_output_){
   Util__ctx_type_6_init(_output_);
   return ;
}

static_inline fix16_t Util_smooth(Util__ctx_type_6 &_ctx, fix16_t input, fix16_t coeff){
   _ctx.x = (_ctx.x + fix_mul(coeff,(input + (- _ctx.x))));
   return _ctx.x;
}

static_inline fix16_t Util_velocityToLevel(int velocity){
   velocity = int_clip(velocity,0,127);
   return fix_mul(0x204 /* 0.007874 */,int_to_fix(velocity));
}

typedef struct CombFB__ctx_type_0 {
   fix16_t scale;
   int pos;
   fix16_t fs;
   int delay;
   fix16_t decay;
   fix16_t buffer[2048];
} CombFB__ctx_type_0;

typedef CombFB__ctx_type_0 CombFB_process_type;

void CombFB__ctx_type_0_init(CombFB__ctx_type_0 &_output_);

static_inline void CombFB_process_init(CombFB__ctx_type_0 &_output_){
   CombFB__ctx_type_0_init(_output_);
   return ;
}

fix16_t CombFB_process(CombFB__ctx_type_0 &_ctx, fix16_t sample);

typedef CombFB__ctx_type_0 CombFB_process_bufferTo_type;

static_inline void CombFB_process_bufferTo_init(CombFB__ctx_type_0 &_output_){
   CombFB__ctx_type_0_init(_output_);
   return ;
}

void CombFB_process_bufferTo(CombFB__ctx_type_0 &_ctx, int nb, fix16_t (&input)[256], fix16_t (&oBuffer)[256]);

typedef CombFB__ctx_type_0 CombFB_setDecay_type;

static_inline void CombFB_setDecay_init(CombFB__ctx_type_0 &_output_){
   CombFB__ctx_type_0_init(_output_);
   return ;
}

static_inline void CombFB_setDecay(CombFB__ctx_type_0 &_ctx, fix16_t newDecay){
   _ctx.decay = fix_clip(newDecay,0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
   _ctx.scale = fix_div(0x10000 /* 1.000000 */,(0x10000 /* 1.000000 */ + _ctx.decay));
}

typedef CombFB__ctx_type_0 CombFB_getMaxDelay_type;

static_inline void CombFB_getMaxDelay_init(CombFB__ctx_type_0 &_output_){
   CombFB__ctx_type_0_init(_output_);
   return ;
}

static_inline int CombFB_getMaxDelay(CombFB__ctx_type_0 &_ctx){
   return 2048;
};

typedef CombFB__ctx_type_0 CombFB_getMaxDelayms_type;

static_inline void CombFB_getMaxDelayms_init(CombFB__ctx_type_0 &_output_){
   CombFB__ctx_type_0_init(_output_);
   return ;
}

static_inline fix16_t CombFB_getMaxDelayms(CombFB__ctx_type_0 &_ctx){
   if(_ctx.fs <= 0x0 /* 0.000000 */){
      return 0x0 /* 0.000000 */;
   }
   return fix_div(0x8000000 /* 2048.000000 */,_ctx.fs);
}

typedef CombFB__ctx_type_0 CombFB_setDelay_type;

static_inline void CombFB_setDelay_init(CombFB__ctx_type_0 &_output_){
   CombFB__ctx_type_0_init(_output_);
   return ;
}

static_inline void CombFB_setDelay(CombFB__ctx_type_0 &_ctx, int newDelay){
   _ctx.delay = int_clip(newDelay,0,CombFB_getMaxDelay(_ctx));
   _ctx.pos = 0;
}

typedef CombFB__ctx_type_0 CombFB_setDelayms_type;

static_inline void CombFB_setDelayms_init(CombFB__ctx_type_0 &_output_){
   CombFB__ctx_type_0_init(_output_);
   return ;
}

static_inline void CombFB_setDelayms(CombFB__ctx_type_0 &_ctx, fix16_t delayms){
   CombFB_setDelay(_ctx,fix_to_int(fix_mul(_ctx.fs,delayms)));
};

typedef CombFB__ctx_type_0 CombFB_setSamplerate_type;

static_inline void CombFB_setSamplerate_init(CombFB__ctx_type_0 &_output_){
   CombFB__ctx_type_0_init(_output_);
   return ;
}

static_inline void CombFB_setSamplerate(CombFB__ctx_type_0 &_ctx, fix16_t newFs){
   if(newFs > 0x0 /* 0.000000 */){
      _ctx.fs = newFs;
   }
};

typedef CombFB__ctx_type_0 CombFB_default_type;

static_inline void CombFB_default_init(CombFB__ctx_type_0 &_output_){
   CombFB__ctx_type_0_init(_output_);
   return ;
}

void CombFB_default(CombFB__ctx_type_0 &_ctx);

typedef struct Allpass__ctx_type_0 {
   fix16_t scale;
   int pos;
   fix16_t fs;
   int delay;
   fix16_t decay;
   fix16_t buffer_allpassed[2048];
   fix16_t buffer[2048];
} Allpass__ctx_type_0;

typedef Allpass__ctx_type_0 Allpass_process_type;

void Allpass__ctx_type_0_init(Allpass__ctx_type_0 &_output_);

static_inline void Allpass_process_init(Allpass__ctx_type_0 &_output_){
   Allpass__ctx_type_0_init(_output_);
   return ;
}

fix16_t Allpass_process(Allpass__ctx_type_0 &_ctx, fix16_t sample);

typedef Allpass__ctx_type_0 Allpass_process_bufferTo_type;

static_inline void Allpass_process_bufferTo_init(Allpass__ctx_type_0 &_output_){
   Allpass__ctx_type_0_init(_output_);
   return ;
}

void Allpass_process_bufferTo(Allpass__ctx_type_0 &_ctx, int nb, fix16_t (&input)[256], fix16_t (&oBuffer)[256]);

typedef Allpass__ctx_type_0 Allpass_setDecay_type;

static_inline void Allpass_setDecay_init(Allpass__ctx_type_0 &_output_){
   Allpass__ctx_type_0_init(_output_);
   return ;
}

static_inline void Allpass_setDecay(Allpass__ctx_type_0 &_ctx, fix16_t newDecay){
   _ctx.decay = fix_clip(newDecay,0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
   _ctx.scale = fix_div(0x10000 /* 1.000000 */,(0x10000 /* 1.000000 */ + (_ctx.decay << 1)));
}

typedef Allpass__ctx_type_0 Allpass_getMaxDelay_type;

static_inline void Allpass_getMaxDelay_init(Allpass__ctx_type_0 &_output_){
   Allpass__ctx_type_0_init(_output_);
   return ;
}

static_inline int Allpass_getMaxDelay(Allpass__ctx_type_0 &_ctx){
   return 2048;
};

typedef Allpass__ctx_type_0 Allpass_getMaxDelayms_type;

static_inline void Allpass_getMaxDelayms_init(Allpass__ctx_type_0 &_output_){
   Allpass__ctx_type_0_init(_output_);
   return ;
}

static_inline fix16_t Allpass_getMaxDelayms(Allpass__ctx_type_0 &_ctx){
   if(_ctx.fs <= 0x0 /* 0.000000 */){
      return 0x0 /* 0.000000 */;
   }
   return fix_div(0x8000000 /* 2048.000000 */,_ctx.fs);
}

typedef Allpass__ctx_type_0 Allpass_setDelay_type;

static_inline void Allpass_setDelay_init(Allpass__ctx_type_0 &_output_){
   Allpass__ctx_type_0_init(_output_);
   return ;
}

static_inline void Allpass_setDelay(Allpass__ctx_type_0 &_ctx, int newDelay){
   _ctx.delay = int_clip(newDelay,0,Allpass_getMaxDelay(_ctx));
   _ctx.pos = 0;
}

typedef Allpass__ctx_type_0 Allpass_setDelayms_type;

static_inline void Allpass_setDelayms_init(Allpass__ctx_type_0 &_output_){
   Allpass__ctx_type_0_init(_output_);
   return ;
}

static_inline void Allpass_setDelayms(Allpass__ctx_type_0 &_ctx, fix16_t delayms){
   Allpass_setDelay(_ctx,fix_to_int(fix_mul(_ctx.fs,delayms)));
};

typedef Allpass__ctx_type_0 Allpass_setSamplerate_type;

static_inline void Allpass_setSamplerate_init(Allpass__ctx_type_0 &_output_){
   Allpass__ctx_type_0_init(_output_);
   return ;
}

static_inline void Allpass_setSamplerate(Allpass__ctx_type_0 &_ctx, fix16_t newFs){
   if(newFs > 0x0 /* 0.000000 */){
      _ctx.fs = newFs;
   }
};

typedef Allpass__ctx_type_0 Allpass_default_type;

static_inline void Allpass_default_init(Allpass__ctx_type_0 &_output_){
   Allpass__ctx_type_0_init(_output_);
   return ;
}

void Allpass_default(Allpass__ctx_type_0 &_ctx);

typedef struct Reverb__ctx_type_0 {
   fix16_t reverbtime;
   fix16_t fs;
   int comb3delay;
   CombFB__ctx_type_0 comb3;
   int comb2delay;
   CombFB__ctx_type_0 comb2;
   int comb1delay;
   CombFB__ctx_type_0 comb1;
   int comb0delay;
   CombFB__ctx_type_0 comb0;
   fix16_t buffer_c3[256];
   fix16_t buffer_c2[256];
   fix16_t buffer_c1[256];
   fix16_t buffer_c0[256];
   fix16_t buffer_a1[256];
   fix16_t buffer_a0[256];
   Allpass__ctx_type_0 allpass1;
   Allpass__ctx_type_0 allpass0;
} Reverb__ctx_type_0;

typedef Reverb__ctx_type_0 Reverb_process_type;

void Reverb__ctx_type_0_init(Reverb__ctx_type_0 &_output_);

static_inline void Reverb_process_init(Reverb__ctx_type_0 &_output_){
   Reverb__ctx_type_0_init(_output_);
   return ;
}

static_inline fix16_t Reverb_process(Reverb__ctx_type_0 &_ctx, fix16_t sample){
   fix16_t combs_filter;
   combs_filter = ((CombFB_process(_ctx.comb0,sample) + CombFB_process(_ctx.comb1,sample) + CombFB_process(_ctx.comb2,sample) + CombFB_process(_ctx.comb3,sample)) >> 2);
   return Allpass_process(_ctx.allpass1,Allpass_process(_ctx.allpass0,combs_filter));
}

typedef Reverb__ctx_type_0 Reverb_process_bufferTo_type;

static_inline void Reverb_process_bufferTo_init(Reverb__ctx_type_0 &_output_){
   Reverb__ctx_type_0_init(_output_);
   return ;
}

void Reverb_process_bufferTo(Reverb__ctx_type_0 &_ctx, int nb, fix16_t (&input)[256], fix16_t (&oBuffer)[256]);

typedef Reverb__ctx_type_0 Reverb_setSamplerate_type;

static_inline void Reverb_setSamplerate_init(Reverb__ctx_type_0 &_output_){
   Reverb__ctx_type_0_init(_output_);
   return ;
}

void Reverb_setSamplerate(Reverb__ctx_type_0 &_ctx, fix16_t newFs);

typedef Reverb__ctx_type_0 Reverb_setReverbTime_type;

static_inline void Reverb_setReverbTime_init(Reverb__ctx_type_0 &_output_){
   Reverb__ctx_type_0_init(_output_);
   return ;
}

void Reverb_setReverbTime(Reverb__ctx_type_0 &_ctx, fix16_t newReverbtime);

typedef Reverb__ctx_type_0 Reverb_setDelayms_type;

static_inline void Reverb_setDelayms_init(Reverb__ctx_type_0 &_output_){
   Reverb__ctx_type_0_init(_output_);
   return ;
}

void Reverb_setDelayms(Reverb__ctx_type_0 &_ctx, fix16_t delayms);

typedef Reverb__ctx_type_0 Reverb_default_type;

static_inline void Reverb_default_init(Reverb__ctx_type_0 &_output_){
   Reverb__ctx_type_0_init(_output_);
   return ;
}

void Reverb_default(Reverb__ctx_type_0 &_ctx);

typedef struct Processor_effects__ctx_type_0 {
   Reverb__ctx_type_0 reverb;
   fix16_t process_ret_3;
   fix16_t process_ret_2;
   fix16_t process_ret_1;
   fix16_t process_ret_0;
   fix16_t param4;
   fix16_t param3;
   fix16_t param2;
   fix16_t param1;
   fix16_t fs;
} Processor_effects__ctx_type_0;

typedef Processor_effects__ctx_type_0 Processor_effects_process_type;

void Processor_effects__ctx_type_0_init(Processor_effects__ctx_type_0 &_output_);

static_inline void Processor_effects_process_init(Processor_effects__ctx_type_0 &_output_){
   Processor_effects__ctx_type_0_init(_output_);
   return ;
}

void Processor_effects_process(Processor_effects__ctx_type_0 &_ctx, fix16_t in1, fix16_t in2, fix16_t in3, fix16_t in4, fix16_t fs);

typedef Processor_effects__ctx_type_0 Processor_effects_process_ret_0_type;

static_inline void Processor_effects_process_ret_0_init(Processor_effects__ctx_type_0 &_output_){
   Processor_effects__ctx_type_0_init(_output_);
   return ;
}

static_inline fix16_t Processor_effects_process_ret_0(Processor_effects__ctx_type_0 &_ctx){
   return _ctx.process_ret_0;
};

typedef Processor_effects__ctx_type_0 Processor_effects_process_ret_1_type;

static_inline void Processor_effects_process_ret_1_init(Processor_effects__ctx_type_0 &_output_){
   Processor_effects__ctx_type_0_init(_output_);
   return ;
}

static_inline fix16_t Processor_effects_process_ret_1(Processor_effects__ctx_type_0 &_ctx){
   return _ctx.process_ret_1;
};

typedef Processor_effects__ctx_type_0 Processor_effects_process_ret_2_type;

static_inline void Processor_effects_process_ret_2_init(Processor_effects__ctx_type_0 &_output_){
   Processor_effects__ctx_type_0_init(_output_);
   return ;
}

static_inline fix16_t Processor_effects_process_ret_2(Processor_effects__ctx_type_0 &_ctx){
   return _ctx.process_ret_2;
};

typedef Processor_effects__ctx_type_0 Processor_effects_process_ret_3_type;

static_inline void Processor_effects_process_ret_3_init(Processor_effects__ctx_type_0 &_output_){
   Processor_effects__ctx_type_0_init(_output_);
   return ;
}

static_inline fix16_t Processor_effects_process_ret_3(Processor_effects__ctx_type_0 &_ctx){
   return _ctx.process_ret_3;
};

typedef Processor_effects__ctx_type_0 Processor_effects_setParam1_type;

static_inline void Processor_effects_setParam1_init(Processor_effects__ctx_type_0 &_output_){
   Processor_effects__ctx_type_0_init(_output_);
   return ;
}

static_inline void Processor_effects_setParam1(Processor_effects__ctx_type_0 &_ctx, fix16_t knob, fix16_t mod, fix16_t input){
   _ctx.param1 = fix_clip((knob + fix_mul(input,mod)),0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
};

typedef Processor_effects__ctx_type_0 Processor_effects_setParam2_type;

static_inline void Processor_effects_setParam2_init(Processor_effects__ctx_type_0 &_output_){
   Processor_effects__ctx_type_0_init(_output_);
   return ;
}

static_inline void Processor_effects_setParam2(Processor_effects__ctx_type_0 &_ctx, fix16_t knob, fix16_t mod, fix16_t input){
   _ctx.param2 = fix_clip((knob + fix_mul(input,mod)),0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
};

typedef Processor_effects__ctx_type_0 Processor_effects_setParam3_type;

static_inline void Processor_effects_setParam3_init(Processor_effects__ctx_type_0 &_output_){
   Processor_effects__ctx_type_0_init(_output_);
   return ;
}

static_inline void Processor_effects_setParam3(Processor_effects__ctx_type_0 &_ctx, fix16_t knob, fix16_t mod, fix16_t input){
   _ctx.param3 = fix_clip((knob + fix_mul(input,mod)),0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
};

typedef Processor_effects__ctx_type_0 Processor_effects_setParam4_type;

static_inline void Processor_effects_setParam4_init(Processor_effects__ctx_type_0 &_output_){
   Processor_effects__ctx_type_0_init(_output_);
   return ;
}

static_inline void Processor_effects_setParam4(Processor_effects__ctx_type_0 &_ctx, fix16_t knob, fix16_t mod, fix16_t input){
   _ctx.param4 = fix_clip((knob + fix_mul(input,mod)),0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
};

typedef Processor_effects__ctx_type_0 Processor_effects_config_type;

static_inline void Processor_effects_config_init(Processor_effects__ctx_type_0 &_output_){
   Processor_effects__ctx_type_0_init(_output_);
   return ;
}

static_inline void Processor_effects_config(Processor_effects__ctx_type_0 &_ctx){
   Reverb_setReverbTime(_ctx.reverb,0xa0000 /* 10.000000 */);
   Reverb_setDelayms(_ctx.reverb,0x320000 /* 50.000000 */);
}

typedef Processor_effects__ctx_type_0 Processor_effects_setSamplerate_type;

static_inline void Processor_effects_setSamplerate_init(Processor_effects__ctx_type_0 &_output_){
   Processor_effects__ctx_type_0_init(_output_);
   return ;
}

static_inline void Processor_effects_setSamplerate(Processor_effects__ctx_type_0 &_ctx, fix16_t newFs){
   if(newFs > 0x0 /* 0.000000 */){
      _ctx.fs = newFs;
      Reverb_setSamplerate(_ctx.reverb,_ctx.fs);
      Processor_effects_config(_ctx);
   }
};

typedef Processor_effects__ctx_type_0 Processor_effects_default_type;

static_inline void Processor_effects_default_init(Processor_effects__ctx_type_0 &_output_){
   Processor_effects__ctx_type_0_init(_output_);
   return ;
}

static_inline void Processor_effects_default(Processor_effects__ctx_type_0 &_ctx){
   Reverb_default(_ctx.reverb);
   Processor_effects_setSamplerate(_ctx,0x2c1999 /* 44.100000 */);
}

typedef struct Processor_reverb__ctx_type_0 {
   fix16_t reverbTime;
   Reverb__ctx_type_0 reverb;
   fix16_t fs;
   fix16_t delayms;
   Util__ctx_type_3 _inst63b;
   Util__ctx_type_3 _inst23b;
} Processor_reverb__ctx_type_0;

typedef Processor_reverb__ctx_type_0 Processor_reverb_process_type;

void Processor_reverb__ctx_type_0_init(Processor_reverb__ctx_type_0 &_output_);

static_inline void Processor_reverb_process_init(Processor_reverb__ctx_type_0 &_output_){
   Processor_reverb__ctx_type_0_init(_output_);
   return ;
}

static_inline fix16_t Processor_reverb_process(Processor_reverb__ctx_type_0 &_ctx, fix16_t in){
   return Reverb_process(_ctx.reverb,in);
};

typedef Processor_reverb__ctx_type_0 Processor_reverb_applyDelay_type;

static_inline void Processor_reverb_applyDelay_init(Processor_reverb__ctx_type_0 &_output_){
   Processor_reverb__ctx_type_0_init(_output_);
   return ;
}

static_inline void Processor_reverb_applyDelay(Processor_reverb__ctx_type_0 &_ctx){
   Reverb_setDelayms(_ctx.reverb,_ctx.delayms);
};

typedef Processor_reverb__ctx_type_0 Processor_reverb_setDelay_type;

static_inline void Processor_reverb_setDelay_init(Processor_reverb__ctx_type_0 &_output_){
   Processor_reverb__ctx_type_0_init(_output_);
   return ;
}

static_inline void Processor_reverb_setDelay(Processor_reverb__ctx_type_0 &_ctx, fix16_t newDelay, uint8_t force){
   if(Util_change(_ctx._inst23b,newDelay) || force){
      _ctx.delayms = newDelay;
      Processor_reverb_applyDelay(_ctx);
   }
};

typedef Processor_reverb__ctx_type_0 Processor_reverb_applyReverb_type;

static_inline void Processor_reverb_applyReverb_init(Processor_reverb__ctx_type_0 &_output_){
   Processor_reverb__ctx_type_0_init(_output_);
   return ;
}

static_inline void Processor_reverb_applyReverb(Processor_reverb__ctx_type_0 &_ctx){
   Reverb_setReverbTime(_ctx.reverb,_ctx.reverbTime);
};

typedef Processor_reverb__ctx_type_0 Processor_reverb_setReverb_type;

static_inline void Processor_reverb_setReverb_init(Processor_reverb__ctx_type_0 &_output_){
   Processor_reverb__ctx_type_0_init(_output_);
   return ;
}

static_inline void Processor_reverb_setReverb(Processor_reverb__ctx_type_0 &_ctx, fix16_t newReverb, uint8_t force){
   if(Util_change(_ctx._inst63b,newReverb) || force){
      _ctx.reverbTime = newReverb;
      Processor_reverb_applyReverb(_ctx);
   }
};

typedef Processor_reverb__ctx_type_0 Processor_reverb_updateConfig_type;

static_inline void Processor_reverb_updateConfig_init(Processor_reverb__ctx_type_0 &_output_){
   Processor_reverb__ctx_type_0_init(_output_);
   return ;
}

static_inline void Processor_reverb_updateConfig(Processor_reverb__ctx_type_0 &_ctx){
   Processor_reverb_applyDelay(_ctx);
   Processor_reverb_applyReverb(_ctx);
}

typedef Processor_reverb__ctx_type_0 Processor_reverb_setSamplerate_type;

static_inline void Processor_reverb_setSamplerate_init(Processor_reverb__ctx_type_0 &_output_){
   Processor_reverb__ctx_type_0_init(_output_);
   return ;
}

static_inline void Processor_reverb_setSamplerate(Processor_reverb__ctx_type_0 &_ctx, fix16_t newFs){
   if((newFs > 0x0 /* 0.000000 */) && (newFs != _ctx.fs)){
      _ctx.fs = newFs;
      Reverb_setSamplerate(_ctx.reverb,_ctx.fs);
      Processor_reverb_updateConfig(_ctx);
   }
};

typedef Processor_reverb__ctx_type_0 Processor_reverb_default_type;

static_inline void Processor_reverb_default_init(Processor_reverb__ctx_type_0 &_output_){
   Processor_reverb__ctx_type_0_init(_output_);
   return ;
}

static_inline void Processor_reverb_default(Processor_reverb__ctx_type_0 &_ctx){
   Reverb_default(_ctx.reverb);
   Processor_reverb_setReverb(_ctx,0xa0000 /* 10.000000 */,true);
   Processor_reverb_setDelay(_ctx,0x320000 /* 50.000000 */,true);
   Processor_reverb_setSamplerate(_ctx,0x2c1999 /* 44.100000 */);
}



#endif // ENGINE_EFFECTS_H
