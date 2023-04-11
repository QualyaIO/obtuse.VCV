
/* Code automatically generated by Vult https://github.com/modlfo/vult */
#include "engine_utils.h"

void Trigg__ctx_type_0_init(Trigg__ctx_type_0 &_output_){
   Trigg__ctx_type_0 _ctx;
   bool_init_array(128,false,_ctx.triggers);
   _ctx.ticks = 0;
   _ctx.shift = 0;
   fix_init_array(128,0x0 /* 0.000000 */,_ctx.ptriggers);
   _ctx.position = 0;
   _ctx.n = 0;
   _ctx.magnitude = 0x0 /* 0.000000 */;
   _ctx.length = 0;
   _ctx.isautolength = false;
   _ctx.evolve = 0x0 /* 0.000000 */;
   _ctx.divider = 0;
   _ctx.dirty = false;
   _ctx.density = 0x0 /* 0.000000 */;
   _ctx.balance = 0x0 /* 0.000000 */;
   Trigg_default(_ctx);
   _output_ = _ctx;
   return ;
}

void Trigg__refresh(Trigg__ctx_type_0 &_ctx){
   if(_ctx.dirty || ((_ctx.evolve > 0x0 /* 0.000000 */) && (fix_random() <= _ctx.evolve))){
      int i;
      i = 0;
      while((i < 128) && (i < _ctx.length)){
         if(_ctx.dirty || ((_ctx.magnitude > 0x0 /* 0.000000 */) && (fix_random() <= _ctx.magnitude))){
            _ctx.triggers[i] = ((_ctx.ptriggers[i] > 0x0 /* 0.000000 */) && (fix_random() <= _ctx.ptriggers[i]));
         }
         i = (1 + i);
      }
   }
   _ctx.dirty = false;
}

int Trigg_process(Trigg__ctx_type_0 &_ctx){
   int trig;
   trig = 0;
   _ctx.ticks = (1 + _ctx.ticks);
   if(_ctx.length > 0){
      if((_ctx.divider > 0) && (((_ctx.shift + _ctx.ticks) % _ctx.divider) == 0)){
         if(_ctx.triggers[((_ctx.n + _ctx.position) % _ctx.length)]){
            trig = 1;
         }
         _ctx.n = (1 + _ctx.n);
      }
      if((_ctx.ticks % _ctx.divider) == 0){
         _ctx.ticks = 0;
      }
      if((_ctx.n % _ctx.length) == 0){
         Trigg__refresh(_ctx);
         _ctx.n = 0;
      }
   }
   return trig;
}

void Trigg__recompute(Trigg__ctx_type_0 &_ctx){
   fix16_t mod;
   mod = 0x0 /* 0.000000 */;
   mod = fix_div(0x10000 /* 1.000000 */,_ctx.density);
   fix16_t max_p;
   max_p = 0x10000 /* 1.000000 */;
   fix16_t min_p;
   min_p = 0x0 /* 0.000000 */;
   if((mod > 0x10000 /* 1.000000 */) && (_ctx.length > 0)){
      fix16_t fnbplus;
      fnbplus = fix_mul(_ctx.density,int_to_fix(_ctx.length));
      int nbplus;
      nbplus = fix_to_int(fnbplus);
      if((fnbplus % 0x10000 /* 1.000000 */) > 0x200 /* 0.007812 */){
         nbplus = (1 + nbplus);
      }
      int nbminus;
      nbminus = (_ctx.length + (- nbplus));
      fix16_t modp;
      modp = fix_div(int_to_fix(nbplus),int_to_fix(_ctx.length));
      if(modp >= _ctx.density){
         max_p = fix_div(fix_mul(_ctx.density,int_to_fix(_ctx.length)),int_to_fix(nbplus));
      }
      else
      {
         min_p = fix_div(((- int_to_fix(nbplus)) + fix_mul(_ctx.density,int_to_fix(_ctx.length))),int_to_fix(nbminus));
      }
   }
   int imod;
   imod = fix_to_int(mod);
   fix16_t accmod;
   accmod = 0x0 /* 0.000000 */;
   int i;
   i = 0;
   int ci;
   ci = 0;
   uint8_t upmod;
   upmod = false;
   while((i < 128) && (i < _ctx.length)){
      if(imod > 0){
         if(accmod >= 0xfe00 /* 0.992188 */){
            imod = (1 + fix_to_int(mod));
            accmod = (-0x10000 /* -1.000000 */ + accmod);
            upmod = true;
         }
         if((ci % imod) == 0){
            _ctx.ptriggers[i] = (_ctx.density + fix_mul(_ctx.balance,(max_p + (- _ctx.density))));
            if(upmod){
               imod = fix_to_int(mod);
               upmod = false;
            }
            ci = 0;
            accmod = (accmod + (mod % 0x10000 /* 1.000000 */));
         }
         else
         {
            _ctx.ptriggers[i] = (_ctx.density + (- fix_mul(_ctx.balance,(_ctx.density + (- min_p)))));
         }
      }
      else
      {
         _ctx.ptriggers[i] = _ctx.density;
      }
      ci = (1 + ci);
      i = (1 + i);
   }
}

int Trigg__getAutolength(Trigg__ctx_type_0 &_ctx){
   if(_ctx.density <= 0x0 /* 0.000000 */){
      return 0;
   }
   fix16_t mod;
   mod = fix_div(0x10000 /* 1.000000 */,_ctx.density);
   fix16_t autolength;
   autolength = fix_floor(mod);
   int iautolength;
   iautolength = fix_to_int(autolength);
   fix16_t mine;
   mine = 0x200 /* 0.007812 */;
   if((mod % 0x10000 /* 1.000000 */) > mine){
      autolength = fix_mul(mod,fix_div(0x10000 /* 1.000000 */,(mod % 0x10000 /* 1.000000 */)));
      if((autolength % 0x10000 /* 1.000000 */) > mine){
         iautolength = fix_to_int((0x10000 /* 1.000000 */ + autolength));
      }
      else
      {
         iautolength = fix_to_int(autolength);
      }
   }
   return iautolength;
}

uint8_t Trigg__applyLength(Trigg__ctx_type_0 &_ctx, int newLength){
   newLength = int_clip(newLength,0,128);
   if(newLength != _ctx.length){
      _ctx.length = newLength;
      Trigg__recompute(_ctx);
      _ctx.dirty = true;
      if(_ctx.length <= _ctx.n){
         Trigg_restartLoop(_ctx);
      }
      else
      {
         Trigg__refresh(_ctx);
      }
      return true;
   }
   return false;
}

void Trigg_setLength(Trigg__ctx_type_0 &_ctx, int newLength){
   newLength = int_clip(newLength,0,128);
   if((newLength == 0) && bool_not(_ctx.isautolength)){
      _ctx.isautolength = true;
      newLength = Trigg__getAutolength(_ctx);
   }
   else
   {
      if((newLength > 0) && _ctx.isautolength){
         _ctx.isautolength = false;
      }
   }
   Trigg__applyLength(_ctx,newLength);
}

void Trigg_setBalance(Trigg__ctx_type_0 &_ctx, fix16_t newBalance){
   newBalance = fix_clip(newBalance,0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
   if(newBalance != _ctx.balance){
      _ctx.balance = newBalance;
      Trigg__recompute(_ctx);
      _ctx.dirty = true;
      Trigg__refresh(_ctx);
   }
}

void Trigg_setDensity(Trigg__ctx_type_0 &_ctx, fix16_t newDensity){
   newDensity = fix_clip(newDensity,0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
   if(newDensity != _ctx.density){
      _ctx.density = newDensity;
      uint8_t update;
      update = true;
      if(_ctx.isautolength){
         update = bool_not(Trigg__applyLength(_ctx,Trigg__getAutolength(_ctx)));
      }
      if(update){
         Trigg__recompute(_ctx);
         _ctx.dirty = true;
         Trigg__refresh(_ctx);
      }
   }
}

void Trigg_default(Trigg__ctx_type_0 &_ctx){
   _ctx.divider = 1;
   _ctx.length = 16;
   _ctx.density = 0x8000 /* 0.500000 */;
   _ctx.balance = 0x8000 /* 0.500000 */;
   _ctx.evolve = 0x3333 /* 0.200000 */;
   _ctx.magnitude = 0x4000 /* 0.250000 */;
   Trigg__recompute(_ctx);
   _ctx.dirty = true;
   Trigg__refresh(_ctx);
}

void Processor_trigg__ctx_type_0_init(Processor_trigg__ctx_type_0 &_output_){
   Processor_trigg__ctx_type_0 _ctx;
   _ctx.trign = 0;
   Trigg__ctx_type_0_init(_ctx.trigg);
   _ctx.tail = 0;
   _ctx.fs = 0x0 /* 0.000000 */;
   Util__ctx_type_3_init(_ctx._inst73b);
   Util__ctx_type_1_init(_ctx._inst551);
   Util__ctx_type_3_init(_ctx._inst43b);
   Util__ctx_type_1_init(_ctx._inst351);
   Util__ctx_type_3_init(_ctx._inst223b);
   Util__ctx_type_3_init(_ctx._inst193b);
   Util__ctx_type_3_init(_ctx._inst163b);
   Util__ctx_type_3_init(_ctx._inst13b);
   Util__ctx_type_3_init(_ctx._inst133b);
   Util__ctx_type_3_init(_ctx._inst103b);
   _output_ = _ctx;
   return ;
}

int Processor_trigg_process(Processor_trigg__ctx_type_0 &_ctx, fix16_t clock, fix16_t reset){
   int trigger;
   trigger = 0;
   if((_ctx.trign > 0) && (_ctx.trign < _ctx.tail)){
      _ctx.trign = (1 + _ctx.trign);
      trigger = 1;
   }
   else
   {
      _ctx.trign = 0;
   }
   if(Util_edge(_ctx._inst351,(reset >= 0x1999 /* 0.100000 */))){
      Trigg_reset(_ctx.trigg);
   }
   if(Util_edge(_ctx._inst551,(clock >= 0x1999 /* 0.100000 */))){
      int newTrigger;
      newTrigger = Trigg_process(_ctx.trigg);
      if(newTrigger > 0){
         trigger = 1;
         _ctx.trign = 1;
      }
   }
   return trigger;
}

int Clock_compareTimeFract(int time1S, fix16_t time1Fract, int time2S, fix16_t time2Fract){
   while(time1Fract < 0x0 /* 0.000000 */){
      time1S = ((-1) + time1S);
      time1Fract = (0x10000 /* 1.000000 */ + time1Fract);
   }
   while(time1Fract > 0x10000 /* 1.000000 */){
      time1S = (1 + time1S);
      time1Fract = (-0x10000 /* -1.000000 */ + time1Fract);
   }
   while(time2Fract < 0x0 /* 0.000000 */){
      time2S = ((-1) + time2S);
      time2Fract = (0x10000 /* 1.000000 */ + time2Fract);
   }
   while(time2Fract > 0x10000 /* 1.000000 */){
      time2S = (1 + time2S);
      time2Fract = (-0x10000 /* -1.000000 */ + time2Fract);
   }
   if((time1S == time2S) && (time1Fract == time2Fract)){
      return 0;
   }
   else
   {
      if((time1S < time2S) || ((time1S == time2S) && (time1Fract <= time2Fract))){
         return 1;
      }
      else
      {
         return (-1);
      }
   }
}

void Clock__ctx_type_5_init(Clock__ctx_type_5 &_output_){
   Clock__ctx_type_5 _ctx;
   _ctx.swing = 0x0 /* 0.000000 */;
   _ctx.subSize = 0;
   _ctx.pos = 0;
   _ctx.orderMix = false;
   _ctx.lastTimeS = 0;
   _ctx.lastTimeFract = 0x0 /* 0.000000 */;
   _ctx.lastBeatS = 0;
   _ctx.lastBeatFract = 0x0 /* 0.000000 */;
   _ctx.init = false;
   _ctx.ibiB = 0x0 /* 0.000000 */;
   _ctx.ibiA = 0x0 /* 0.000000 */;
   _ctx.ibi = 0x0 /* 0.000000 */;
   _ctx.groupSize = 0;
   _ctx.groupRatio = 0x0 /* 0.000000 */;
   _ctx.bpm = 0x0 /* 0.000000 */;
   Clock_default(_ctx);
   _output_ = _ctx;
   return ;
}

int Clock_process(Clock__ctx_type_5 &_ctx, int timeS, fix16_t timeFract){
   int trigger;
   trigger = 0;
   if(bool_not(_ctx.init) || (Clock_compareTimeFract(timeS,timeFract,_ctx.lastBeatS,_ctx.lastBeatFract) > 0)){
      _ctx.init = true;
      _ctx.lastBeatS = timeS;
      _ctx.lastBeatFract = timeFract;
      trigger = 1;
      _ctx.pos = 1;
      _ctx.ibi = _ctx.ibiA;
   }
   else
   {
      if((Clock_compareTimeFract(_ctx.lastTimeS,_ctx.lastTimeFract,timeS,timeFract) != 0) && (Clock_compareTimeFract((timeS + (- _ctx.lastBeatS)),(timeFract + (- _ctx.lastBeatFract)),fix_to_int(_ctx.ibi),(_ctx.ibi % 0x10000 /* 1.000000 */)) <= 0)){
         _ctx.lastBeatS = (_ctx.lastBeatS + fix_to_int(_ctx.ibi));
         _ctx.lastBeatFract = (_ctx.lastBeatFract + (_ctx.ibi % 0x10000 /* 1.000000 */));
         while(_ctx.lastBeatFract >= 0x10000 /* 1.000000 */){
            _ctx.lastBeatS = (1 + _ctx.lastBeatS);
            _ctx.lastBeatFract = (-0x10000 /* -1.000000 */ + _ctx.lastBeatFract);
         }
         if((bool_not(_ctx.orderMix) && (_ctx.pos < _ctx.subSize)) || (_ctx.orderMix && ((((_ctx.pos / 2) < _ctx.subSize) && ((_ctx.pos % 2) == 0)) || ((_ctx.pos / 2) > (_ctx.groupSize + (- _ctx.subSize)))))){
            _ctx.ibi = _ctx.ibiA;
            if(_ctx.pos == 0){
               trigger = 1;
            }
            else
            {
               trigger = 2;
            }
         }
         else
         {
            _ctx.ibi = _ctx.ibiB;
            trigger = 3;
         }
         _ctx.pos = (1 + _ctx.pos);
         _ctx.pos = (_ctx.pos % _ctx.groupSize);
      }
   }
   _ctx.lastTimeS = timeS;
   _ctx.lastTimeFract = timeFract;
   return trigger;
}

void Clock__recompute(Clock__ctx_type_5 &_ctx){
   _ctx.subSize = int_clip(fix_to_int(fix_mul(_ctx.groupRatio,int_to_fix((1 + _ctx.groupSize)))),1,((-1) + _ctx.groupSize));
   uint8_t isIBIA;
   isIBIA = (_ctx.ibi == _ctx.ibiA);
   fix16_t bibi;
   bibi = fix_div(0x3c0000 /* 60.000000 */,_ctx.bpm);
   if(_ctx.swing <= 0x8000 /* 0.500000 */){
      _ctx.ibiA = fix_clip((fix_mul(_ctx.swing,bibi) << 1),0x83 /* 0.002000 */,bibi);
      _ctx.ibiB = fix_div(((- fix_mul(_ctx.ibiA,int_to_fix(_ctx.subSize))) + fix_mul(bibi,int_to_fix(_ctx.groupSize))),int_to_fix((_ctx.groupSize + (- _ctx.subSize))));
   }
   else
   {
      _ctx.ibiB = fix_clip((fix_mul(bibi,(0x10000 /* 1.000000 */ + (- _ctx.swing))) << 1),0x83 /* 0.002000 */,bibi);
      _ctx.ibiA = fix_div(((- fix_mul(_ctx.ibiB,int_to_fix((_ctx.groupSize + (- _ctx.subSize))))) + fix_mul(bibi,int_to_fix(_ctx.groupSize))),int_to_fix(_ctx.subSize));
   }
   if(isIBIA){
      _ctx.ibi = _ctx.ibiA;
   }
   else
   {
      _ctx.ibi = _ctx.ibiB;
   }
}

void Clock_setBPM(Clock__ctx_type_5 &_ctx, fix16_t newBPM){
   newBPM = fix_clip(newBPM,0x4189 /* 0.256000 */,0x75300000 /* 30000.000000 */);
   if(newBPM != _ctx.bpm){
      _ctx.bpm = newBPM;
      Clock__recompute(_ctx);
   }
}

void Clock_setGroupSize(Clock__ctx_type_5 &_ctx, int newGroupSize){
   newGroupSize = int_clip(newGroupSize,2,128);
   if(newGroupSize != _ctx.groupSize){
      _ctx.groupSize = newGroupSize;
      Clock__recompute(_ctx);
      _ctx.pos = (_ctx.pos % _ctx.groupSize);
   }
}

void Clock_setGroupRatio(Clock__ctx_type_5 &_ctx, fix16_t newGroupRatio){
   newGroupRatio = fix_clip(newGroupRatio,0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
   if(newGroupRatio != _ctx.groupRatio){
      _ctx.groupRatio = newGroupRatio;
      Clock__recompute(_ctx);
   }
}

void Clock_setSwing(Clock__ctx_type_5 &_ctx, fix16_t newSwing){
   newSwing = fix_clip(newSwing,0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
   if(_ctx.swing != newSwing){
      _ctx.swing = newSwing;
      Clock__recompute(_ctx);
   }
}

void Processor_clock__ctx_type_0_init(Processor_clock__ctx_type_0 &_output_){
   Processor_clock__ctx_type_0 _ctx;
   _ctx.lastTrigg = 0x0 /* 0.000000 */;
   _ctx.gate = false;
   _output_ = _ctx;
   return ;
}

uint8_t Processor_clock_gate1ms(Processor_clock__ctx_type_0 &_ctx, uint8_t trig, fix16_t time){
   if(trig){
      _ctx.lastTrigg = time;
      _ctx.gate = true;
   }
   else
   {
      if((time + (- _ctx.lastTrigg)) > 0x41 /* 0.001000 */){
         _ctx.gate = false;
      }
   }
   return _ctx.gate;
}

void Processor_clock__ctx_type_2_init(Processor_clock__ctx_type_2 &_output_){
   Processor_clock__ctx_type_2 _ctx;
   _ctx.process_ret_3 = 0x0 /* 0.000000 */;
   _ctx.process_ret_2 = 0x0 /* 0.000000 */;
   _ctx.process_ret_1 = 0x0 /* 0.000000 */;
   _ctx.process_ret_0 = 0x0 /* 0.000000 */;
   Clock__ctx_type_5_init(_ctx.cloclo);
   Util__ctx_type_3_init(_ctx._inst73b);
   Processor_clock__ctx_type_0_init(_ctx._inst4d8);
   Util__ctx_type_3_init(_ctx._inst43b);
   Processor_clock__ctx_type_0_init(_ctx._inst3d8);
   Processor_clock__ctx_type_0_init(_ctx._inst2d8);
   Processor_clock__ctx_type_0_init(_ctx._inst1d8);
   Util__ctx_type_3_init(_ctx._inst13b);
   Util__ctx_type_3_init(_ctx._inst133b);
   Util__ctx_type_3_init(_ctx._inst103b);
   _output_ = _ctx;
   return ;
}

void Processor_clock_process(Processor_clock__ctx_type_2 &_ctx, int timeS, fix16_t timeFract){
   fix16_t out1;
   fix16_t out2;
   fix16_t out3;
   fix16_t out4;
   int beat;
   beat = Clock_process(_ctx.cloclo,timeS,timeFract);
   out1 = Processor_clock_bool2real(Processor_clock_gate1ms(_ctx._inst1d8,(beat > 0),(timeFract + int_to_fix(timeS))));
   out2 = Processor_clock_bool2real(Processor_clock_gate1ms(_ctx._inst2d8,(beat == 1),(timeFract + int_to_fix(timeS))));
   out3 = Processor_clock_bool2real(Processor_clock_gate1ms(_ctx._inst3d8,((beat == 1) || (beat == 2)),(timeFract + int_to_fix(timeS))));
   out4 = Processor_clock_bool2real(Processor_clock_gate1ms(_ctx._inst4d8,(beat == 3),(timeFract + int_to_fix(timeS))));
   _ctx.process_ret_0 = out1;
   _ctx.process_ret_1 = out2;
   _ctx.process_ret_2 = out3;
   _ctx.process_ret_3 = out4;
   return ;
}


