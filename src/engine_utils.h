
/* Code automatically generated by Vult https://github.com/modlfo/vult */
#ifndef ENGINE_UTILS_H
#define ENGINE_UTILS_H
#include <stdint.h>
#include <math.h>
#include "vultin.h"
#include "engine_utils.tables.h"

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

typedef struct Util__ctx_type_4 {
   fix16_t x;
} Util__ctx_type_4;

typedef Util__ctx_type_4 Util_smooth_type;

static_inline void Util__ctx_type_4_init(Util__ctx_type_4 &_output_){
   Util__ctx_type_4 _ctx;
   _ctx.x = 0x0 /* 0.000000 */;
   _output_ = _ctx;
   return ;
}

static_inline void Util_smooth_init(Util__ctx_type_4 &_output_){
   Util__ctx_type_4_init(_output_);
   return ;
}

static_inline fix16_t Util_smooth(Util__ctx_type_4 &_ctx, fix16_t input, fix16_t coeff){
   _ctx.x = (_ctx.x + fix_mul(coeff,(input + (- _ctx.x))));
   return _ctx.x;
}

static_inline fix16_t Util_velocityToLevel(int velocity){
   velocity = int_clip(velocity,0,127);
   return fix_mul(0x204 /* 0.007874 */,int_to_fix(velocity));
}

typedef struct Trigg__ctx_type_0 {
   uint8_t triggers[128];
   int ticks;
   int shift;
   fix16_t ptriggers[128];
   int position;
   int n;
   fix16_t magnitude;
   int length;
   uint8_t isautolength;
   fix16_t evolve;
   int divider;
   uint8_t dirty;
   fix16_t density;
   fix16_t balance;
} Trigg__ctx_type_0;

typedef Trigg__ctx_type_0 Trigg__refresh_type;

void Trigg__ctx_type_0_init(Trigg__ctx_type_0 &_output_);

static_inline void Trigg__refresh_init(Trigg__ctx_type_0 &_output_){
   Trigg__ctx_type_0_init(_output_);
   return ;
}

void Trigg__refresh(Trigg__ctx_type_0 &_ctx);

typedef Trigg__ctx_type_0 Trigg_process_type;

static_inline void Trigg_process_init(Trigg__ctx_type_0 &_output_){
   Trigg__ctx_type_0_init(_output_);
   return ;
}

int Trigg_process(Trigg__ctx_type_0 &_ctx);

typedef Trigg__ctx_type_0 Trigg_restartLoop_type;

static_inline void Trigg_restartLoop_init(Trigg__ctx_type_0 &_output_){
   Trigg__ctx_type_0_init(_output_);
   return ;
}

static_inline void Trigg_restartLoop(Trigg__ctx_type_0 &_ctx){
   _ctx.n = 0;
   Trigg__refresh(_ctx);
}

typedef Trigg__ctx_type_0 Trigg_reset_type;

static_inline void Trigg_reset_init(Trigg__ctx_type_0 &_output_){
   Trigg__ctx_type_0_init(_output_);
   return ;
}

static_inline void Trigg_reset(Trigg__ctx_type_0 &_ctx){
   _ctx.ticks = 0;
   Trigg_restartLoop(_ctx);
}

typedef Trigg__ctx_type_0 Trigg__recompute_type;

static_inline void Trigg__recompute_init(Trigg__ctx_type_0 &_output_){
   Trigg__ctx_type_0_init(_output_);
   return ;
}

void Trigg__recompute(Trigg__ctx_type_0 &_ctx);

typedef Trigg__ctx_type_0 Trigg__getAutolength_type;

static_inline void Trigg__getAutolength_init(Trigg__ctx_type_0 &_output_){
   Trigg__ctx_type_0_init(_output_);
   return ;
}

int Trigg__getAutolength(Trigg__ctx_type_0 &_ctx);

typedef Trigg__ctx_type_0 Trigg__applyLength_type;

static_inline void Trigg__applyLength_init(Trigg__ctx_type_0 &_output_){
   Trigg__ctx_type_0_init(_output_);
   return ;
}

uint8_t Trigg__applyLength(Trigg__ctx_type_0 &_ctx, int newLength);

typedef Trigg__ctx_type_0 Trigg_setLength_type;

static_inline void Trigg_setLength_init(Trigg__ctx_type_0 &_output_){
   Trigg__ctx_type_0_init(_output_);
   return ;
}

void Trigg_setLength(Trigg__ctx_type_0 &_ctx, int newLength);

typedef Trigg__ctx_type_0 Trigg_getLength_type;

static_inline void Trigg_getLength_init(Trigg__ctx_type_0 &_output_){
   Trigg__ctx_type_0_init(_output_);
   return ;
}

static_inline int Trigg_getLength(Trigg__ctx_type_0 &_ctx){
   return _ctx.length;
};

typedef Trigg__ctx_type_0 Trigg_setDivider_type;

static_inline void Trigg_setDivider_init(Trigg__ctx_type_0 &_output_){
   Trigg__ctx_type_0_init(_output_);
   return ;
}

static_inline void Trigg_setDivider(Trigg__ctx_type_0 &_ctx, int newDivider){
   _ctx.divider = int_clip(newDivider,1,newDivider);
};

typedef Trigg__ctx_type_0 Trigg_setShift_type;

static_inline void Trigg_setShift_init(Trigg__ctx_type_0 &_output_){
   Trigg__ctx_type_0_init(_output_);
   return ;
}

static_inline void Trigg_setShift(Trigg__ctx_type_0 &_ctx, int newShift){
   _ctx.shift = int_clip(newShift,0,newShift);
};

typedef Trigg__ctx_type_0 Trigg_setEvolve_type;

static_inline void Trigg_setEvolve_init(Trigg__ctx_type_0 &_output_){
   Trigg__ctx_type_0_init(_output_);
   return ;
}

static_inline void Trigg_setEvolve(Trigg__ctx_type_0 &_ctx, fix16_t newEvolve){
   _ctx.evolve = fix_clip(newEvolve,0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
};

typedef Trigg__ctx_type_0 Trigg_setMagnitude_type;

static_inline void Trigg_setMagnitude_init(Trigg__ctx_type_0 &_output_){
   Trigg__ctx_type_0_init(_output_);
   return ;
}

static_inline void Trigg_setMagnitude(Trigg__ctx_type_0 &_ctx, fix16_t newMagnitude){
   _ctx.magnitude = fix_clip(newMagnitude,0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
};

typedef Trigg__ctx_type_0 Trigg_setBalance_type;

static_inline void Trigg_setBalance_init(Trigg__ctx_type_0 &_output_){
   Trigg__ctx_type_0_init(_output_);
   return ;
}

void Trigg_setBalance(Trigg__ctx_type_0 &_ctx, fix16_t newBalance);

typedef Trigg__ctx_type_0 Trigg_setDensity_type;

static_inline void Trigg_setDensity_init(Trigg__ctx_type_0 &_output_){
   Trigg__ctx_type_0_init(_output_);
   return ;
}

void Trigg_setDensity(Trigg__ctx_type_0 &_ctx, fix16_t newDensity);

typedef Trigg__ctx_type_0 Trigg_setPosition_type;

static_inline void Trigg_setPosition_init(Trigg__ctx_type_0 &_output_){
   Trigg__ctx_type_0_init(_output_);
   return ;
}

static_inline void Trigg_setPosition(Trigg__ctx_type_0 &_ctx, int newPosition){
   _ctx.position = int_clip(newPosition,0,128);
};

typedef Trigg__ctx_type_0 Trigg_default_type;

static_inline void Trigg_default_init(Trigg__ctx_type_0 &_output_){
   Trigg__ctx_type_0_init(_output_);
   return ;
}

void Trigg_default(Trigg__ctx_type_0 &_ctx);

typedef struct Processor_trigg__ctx_type_0 {
   int trign;
   Trigg__ctx_type_0 trigg;
   int tail;
   fix16_t fs;
   Util__ctx_type_3 _inst73b;
   Util__ctx_type_1 _inst551;
   Util__ctx_type_3 _inst43b;
   Util__ctx_type_1 _inst351;
   Util__ctx_type_3 _inst223b;
   Util__ctx_type_3 _inst193b;
   Util__ctx_type_3 _inst163b;
   Util__ctx_type_3 _inst13b;
   Util__ctx_type_3 _inst133b;
   Util__ctx_type_3 _inst103b;
} Processor_trigg__ctx_type_0;

typedef Processor_trigg__ctx_type_0 Processor_trigg_process_type;

void Processor_trigg__ctx_type_0_init(Processor_trigg__ctx_type_0 &_output_);

static_inline void Processor_trigg_process_init(Processor_trigg__ctx_type_0 &_output_){
   Processor_trigg__ctx_type_0_init(_output_);
   return ;
}

int Processor_trigg_process(Processor_trigg__ctx_type_0 &_ctx, fix16_t clock, fix16_t reset);

typedef Processor_trigg__ctx_type_0 Processor_trigg_setLength_type;

static_inline void Processor_trigg_setLength_init(Processor_trigg__ctx_type_0 &_output_){
   Processor_trigg__ctx_type_0_init(_output_);
   return ;
}

static_inline void Processor_trigg_setLength(Processor_trigg__ctx_type_0 &_ctx, int param, uint8_t force){
   if(Util_change(_ctx._inst13b,int_to_fix(param)) || force){
      Trigg_setLength(_ctx.trigg,param);
   }
};

typedef Processor_trigg__ctx_type_0 Processor_trigg_setDivider_type;

static_inline void Processor_trigg_setDivider_init(Processor_trigg__ctx_type_0 &_output_){
   Processor_trigg__ctx_type_0_init(_output_);
   return ;
}

static_inline void Processor_trigg_setDivider(Processor_trigg__ctx_type_0 &_ctx, int param, uint8_t force){
   if(Util_change(_ctx._inst43b,int_to_fix(param)) || force){
      Trigg_setDivider(_ctx.trigg,param);
   }
};

typedef Processor_trigg__ctx_type_0 Processor_trigg_setShift_type;

static_inline void Processor_trigg_setShift_init(Processor_trigg__ctx_type_0 &_output_){
   Processor_trigg__ctx_type_0_init(_output_);
   return ;
}

static_inline void Processor_trigg_setShift(Processor_trigg__ctx_type_0 &_ctx, int param, uint8_t force){
   if(Util_change(_ctx._inst73b,int_to_fix(param)) || force){
      Trigg_setShift(_ctx.trigg,param);
   }
};

typedef Processor_trigg__ctx_type_0 Processor_trigg_setPosition_type;

static_inline void Processor_trigg_setPosition_init(Processor_trigg__ctx_type_0 &_output_){
   Processor_trigg__ctx_type_0_init(_output_);
   return ;
}

static_inline void Processor_trigg_setPosition(Processor_trigg__ctx_type_0 &_ctx, int param, uint8_t force){
   if(Util_change(_ctx._inst103b,int_to_fix(param)) || force){
      Trigg_setPosition(_ctx.trigg,param);
   }
};

typedef Processor_trigg__ctx_type_0 Processor_trigg_setEvolve_type;

static_inline void Processor_trigg_setEvolve_init(Processor_trigg__ctx_type_0 &_output_){
   Processor_trigg__ctx_type_0_init(_output_);
   return ;
}

static_inline void Processor_trigg_setEvolve(Processor_trigg__ctx_type_0 &_ctx, fix16_t param, uint8_t force){
   if(Util_change(_ctx._inst133b,param) || force){
      Trigg_setEvolve(_ctx.trigg,param);
   }
};

typedef Processor_trigg__ctx_type_0 Processor_trigg_setMagnitude_type;

static_inline void Processor_trigg_setMagnitude_init(Processor_trigg__ctx_type_0 &_output_){
   Processor_trigg__ctx_type_0_init(_output_);
   return ;
}

static_inline void Processor_trigg_setMagnitude(Processor_trigg__ctx_type_0 &_ctx, fix16_t param, uint8_t force){
   if(Util_change(_ctx._inst163b,param) || force){
      Trigg_setMagnitude(_ctx.trigg,param);
   }
};

typedef Processor_trigg__ctx_type_0 Processor_trigg_setBalance_type;

static_inline void Processor_trigg_setBalance_init(Processor_trigg__ctx_type_0 &_output_){
   Processor_trigg__ctx_type_0_init(_output_);
   return ;
}

static_inline void Processor_trigg_setBalance(Processor_trigg__ctx_type_0 &_ctx, fix16_t param, uint8_t force){
   if(Util_change(_ctx._inst193b,param) || force){
      Trigg_setBalance(_ctx.trigg,param);
   }
};

typedef Processor_trigg__ctx_type_0 Processor_trigg_setDensity_type;

static_inline void Processor_trigg_setDensity_init(Processor_trigg__ctx_type_0 &_output_){
   Processor_trigg__ctx_type_0_init(_output_);
   return ;
}

static_inline void Processor_trigg_setDensity(Processor_trigg__ctx_type_0 &_ctx, fix16_t param, uint8_t force){
   if(Util_change(_ctx._inst223b,param) || force){
      Trigg_setDensity(_ctx.trigg,param);
   }
};

typedef Processor_trigg__ctx_type_0 Processor_trigg_setSamplerate_type;

static_inline void Processor_trigg_setSamplerate_init(Processor_trigg__ctx_type_0 &_output_){
   Processor_trigg__ctx_type_0_init(_output_);
   return ;
}

static_inline void Processor_trigg_setSamplerate(Processor_trigg__ctx_type_0 &_ctx, fix16_t newFs){
   if((newFs > 0x0 /* 0.000000 */) && (newFs != _ctx.fs)){
      _ctx.fs = newFs;
      _ctx.tail = fix_to_int(_ctx.fs);
   }
};

static_inline fix16_t Clock_getMinBPM(){
   return 0x83 /* 0.002000 */;
};

static_inline fix16_t Clock_getMaxBPM(){
   return 0x75300000 /* 30000.000000 */;
};

static_inline int Clock_getMinGroupSize(){
   return 2;
};

static_inline int Clock_getMaxGroupSize(){
   return 128;
};

typedef struct Clock__ctx_type_4 {
   fix16_t swing;
   int subSize;
   int pos;
   uint8_t orderMix;
   fix16_t lastBeat;
   uint8_t init;
   fix16_t ibiB;
   fix16_t ibiA;
   fix16_t ibi;
   int groupSize;
   fix16_t groupRatio;
   fix16_t bpm;
} Clock__ctx_type_4;

typedef Clock__ctx_type_4 Clock_process_type;

void Clock__ctx_type_4_init(Clock__ctx_type_4 &_output_);

static_inline void Clock_process_init(Clock__ctx_type_4 &_output_){
   Clock__ctx_type_4_init(_output_);
   return ;
}

int Clock_process(Clock__ctx_type_4 &_ctx, fix16_t time);

typedef Clock__ctx_type_4 Clock_reset_type;

static_inline void Clock_reset_init(Clock__ctx_type_4 &_output_){
   Clock__ctx_type_4_init(_output_);
   return ;
}

static_inline void Clock_reset(Clock__ctx_type_4 &_ctx){
   _ctx.init = false;
};

typedef Clock__ctx_type_4 Clock__recompute_type;

static_inline void Clock__recompute_init(Clock__ctx_type_4 &_output_){
   Clock__ctx_type_4_init(_output_);
   return ;
}

void Clock__recompute(Clock__ctx_type_4 &_ctx);

typedef Clock__ctx_type_4 Clock_setBPM_type;

static_inline void Clock_setBPM_init(Clock__ctx_type_4 &_output_){
   Clock__ctx_type_4_init(_output_);
   return ;
}

void Clock_setBPM(Clock__ctx_type_4 &_ctx, fix16_t newBPM);

typedef Clock__ctx_type_4 Clock_setGroupSize_type;

static_inline void Clock_setGroupSize_init(Clock__ctx_type_4 &_output_){
   Clock__ctx_type_4_init(_output_);
   return ;
}

void Clock_setGroupSize(Clock__ctx_type_4 &_ctx, int newGroupSize);

typedef Clock__ctx_type_4 Clock_setGroupRatio_type;

static_inline void Clock_setGroupRatio_init(Clock__ctx_type_4 &_output_){
   Clock__ctx_type_4_init(_output_);
   return ;
}

void Clock_setGroupRatio(Clock__ctx_type_4 &_ctx, fix16_t newGroupRatio);

typedef Clock__ctx_type_4 Clock_setSwing_type;

static_inline void Clock_setSwing_init(Clock__ctx_type_4 &_output_){
   Clock__ctx_type_4_init(_output_);
   return ;
}

void Clock_setSwing(Clock__ctx_type_4 &_ctx, fix16_t newSwing);

typedef Clock__ctx_type_4 Clock_setOrderMix_type;

static_inline void Clock_setOrderMix_init(Clock__ctx_type_4 &_output_){
   Clock__ctx_type_4_init(_output_);
   return ;
}

static_inline void Clock_setOrderMix(Clock__ctx_type_4 &_ctx, uint8_t flag){
   _ctx.orderMix = flag;
};

typedef Clock__ctx_type_4 Clock_default_type;

static_inline void Clock_default_init(Clock__ctx_type_4 &_output_){
   Clock__ctx_type_4_init(_output_);
   return ;
}

static_inline void Clock_default(Clock__ctx_type_4 &_ctx){
   Clock_setBPM(_ctx,0x780000 /* 120.000000 */);
   Clock_setGroupSize(_ctx,4);
   Clock_setGroupRatio(_ctx,0x8000 /* 0.500000 */);
   Clock_setSwing(_ctx,0x8000 /* 0.500000 */);
}

typedef struct Processor_clock__ctx_type_0 {
   fix16_t lastTrigg;
   uint8_t gate;
} Processor_clock__ctx_type_0;

typedef Processor_clock__ctx_type_0 Processor_clock_gate1ms_type;

void Processor_clock__ctx_type_0_init(Processor_clock__ctx_type_0 &_output_);

static_inline void Processor_clock_gate1ms_init(Processor_clock__ctx_type_0 &_output_){
   Processor_clock__ctx_type_0_init(_output_);
   return ;
}

uint8_t Processor_clock_gate1ms(Processor_clock__ctx_type_0 &_ctx, uint8_t trig, fix16_t time);

static_inline fix16_t Processor_clock_bool2real(uint8_t b){
   if(b){
      return 0x10000 /* 1.000000 */;
   }
   else
   {
      return 0x0 /* 0.000000 */;
   }
};

typedef struct Processor_clock__ctx_type_2 {
   fix16_t process_ret_3;
   fix16_t process_ret_2;
   fix16_t process_ret_1;
   fix16_t process_ret_0;
   Clock__ctx_type_4 cloclo;
   Util__ctx_type_3 _inst73b;
   Processor_clock__ctx_type_0 _inst4d8;
   Util__ctx_type_3 _inst43b;
   Processor_clock__ctx_type_0 _inst3d8;
   Processor_clock__ctx_type_0 _inst2d8;
   Processor_clock__ctx_type_0 _inst1d8;
   Util__ctx_type_3 _inst13b;
   Util__ctx_type_3 _inst133b;
   Util__ctx_type_3 _inst103b;
} Processor_clock__ctx_type_2;

typedef Processor_clock__ctx_type_2 Processor_clock_process_type;

void Processor_clock__ctx_type_2_init(Processor_clock__ctx_type_2 &_output_);

static_inline void Processor_clock_process_init(Processor_clock__ctx_type_2 &_output_){
   Processor_clock__ctx_type_2_init(_output_);
   return ;
}

void Processor_clock_process(Processor_clock__ctx_type_2 &_ctx, fix16_t time);

typedef Processor_clock__ctx_type_2 Processor_clock_process_ret_0_type;

static_inline void Processor_clock_process_ret_0_init(Processor_clock__ctx_type_2 &_output_){
   Processor_clock__ctx_type_2_init(_output_);
   return ;
}

static_inline fix16_t Processor_clock_process_ret_0(Processor_clock__ctx_type_2 &_ctx){
   return _ctx.process_ret_0;
};

typedef Processor_clock__ctx_type_2 Processor_clock_process_ret_1_type;

static_inline void Processor_clock_process_ret_1_init(Processor_clock__ctx_type_2 &_output_){
   Processor_clock__ctx_type_2_init(_output_);
   return ;
}

static_inline fix16_t Processor_clock_process_ret_1(Processor_clock__ctx_type_2 &_ctx){
   return _ctx.process_ret_1;
};

typedef Processor_clock__ctx_type_2 Processor_clock_process_ret_2_type;

static_inline void Processor_clock_process_ret_2_init(Processor_clock__ctx_type_2 &_output_){
   Processor_clock__ctx_type_2_init(_output_);
   return ;
}

static_inline fix16_t Processor_clock_process_ret_2(Processor_clock__ctx_type_2 &_ctx){
   return _ctx.process_ret_2;
};

typedef Processor_clock__ctx_type_2 Processor_clock_process_ret_3_type;

static_inline void Processor_clock_process_ret_3_init(Processor_clock__ctx_type_2 &_output_){
   Processor_clock__ctx_type_2_init(_output_);
   return ;
}

static_inline fix16_t Processor_clock_process_ret_3(Processor_clock__ctx_type_2 &_ctx){
   return _ctx.process_ret_3;
};

typedef Processor_clock__ctx_type_2 Processor_clock_setBPM_type;

static_inline void Processor_clock_setBPM_init(Processor_clock__ctx_type_2 &_output_){
   Processor_clock__ctx_type_2_init(_output_);
   return ;
}

static_inline void Processor_clock_setBPM(Processor_clock__ctx_type_2 &_ctx, fix16_t param, uint8_t force){
   if(Util_change(_ctx._inst13b,param) || force){
      Clock_setBPM(_ctx.cloclo,param);
   }
};

typedef Processor_clock__ctx_type_2 Processor_clock_setSwing_type;

static_inline void Processor_clock_setSwing_init(Processor_clock__ctx_type_2 &_output_){
   Processor_clock__ctx_type_2_init(_output_);
   return ;
}

static_inline void Processor_clock_setSwing(Processor_clock__ctx_type_2 &_ctx, fix16_t param, uint8_t force){
   if(Util_change(_ctx._inst43b,param) || force){
      Clock_setSwing(_ctx.cloclo,param);
   }
};

typedef Processor_clock__ctx_type_2 Processor_clock_setGroupSize_type;

static_inline void Processor_clock_setGroupSize_init(Processor_clock__ctx_type_2 &_output_){
   Processor_clock__ctx_type_2_init(_output_);
   return ;
}

static_inline void Processor_clock_setGroupSize(Processor_clock__ctx_type_2 &_ctx, int param, uint8_t force){
   if(Util_change(_ctx._inst73b,int_to_fix(param)) || force){
      Clock_setGroupSize(_ctx.cloclo,param);
   }
};

typedef Processor_clock__ctx_type_2 Processor_clock_setGroupRatio_type;

static_inline void Processor_clock_setGroupRatio_init(Processor_clock__ctx_type_2 &_output_){
   Processor_clock__ctx_type_2_init(_output_);
   return ;
}

static_inline void Processor_clock_setGroupRatio(Processor_clock__ctx_type_2 &_ctx, fix16_t param, uint8_t force){
   if(Util_change(_ctx._inst103b,param) || force){
      Clock_setGroupRatio(_ctx.cloclo,param);
   }
};

typedef Processor_clock__ctx_type_2 Processor_clock_setOrderMix_type;

static_inline void Processor_clock_setOrderMix_init(Processor_clock__ctx_type_2 &_output_){
   Processor_clock__ctx_type_2_init(_output_);
   return ;
}

static_inline void Processor_clock_setOrderMix(Processor_clock__ctx_type_2 &_ctx, fix16_t param, uint8_t force){
   if(Util_change(_ctx._inst133b,Processor_clock_bool2real((param > 0x8000 /* 0.500000 */))) || force){
      Clock_setOrderMix(_ctx.cloclo,(param > 0x8000 /* 0.500000 */));
   }
};

static_inline fix16_t Processor_clock_getMinBPM(){
   return 0x83 /* 0.002000 */;
};

static_inline fix16_t Processor_clock_getMaxBPM(){
   return 0x75300000 /* 30000.000000 */;
};

static_inline int Processor_clock_getMinGroupSize(){
   return 2;
};

static_inline int Processor_clock_getMaxGroupSize(){
   return 128;
};



#endif // ENGINE_UTILS_H
