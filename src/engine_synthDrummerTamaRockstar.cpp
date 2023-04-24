
/* Code automatically generated by Vult https://github.com/modlfo/vult */
#include "engine_synthDrummerTamaRockstar.h"

void synthDrummerTamaRockstar_DrummerWrapper_getSlicesStart(int (&_output_)[12]){
   int _array_1[12];
   {
      _array_1[0] = 0;
      _array_1[1] = 3250;
      _array_1[2] = 28000;
      _array_1[3] = 31175;
      _array_1[4] = 41306;
      _array_1[5] = 48495;
      _array_1[6] = 62018;
      _array_1[7] = 65600;
      _array_1[8] = 79848;
      _array_1[9] = 82334;
      _array_1[10] = 90270;
      _array_1[11] = 92625;
   }
   int_copy_array(12,_output_,_array_1);
   return ;
}

void synthDrummerTamaRockstar_DrummerWrapper_getSlicesEnd(int (&_output_)[12]){
   int _array_1[12];
   {
      _array_1[0] = 3220;
      _array_1[1] = 27700;
      _array_1[2] = 31174;
      _array_1[3] = 41304;
      _array_1[4] = 48494;
      _array_1[5] = 62017;
      _array_1[6] = 65450;
      _array_1[7] = 79847;
      _array_1[8] = 82333;
      _array_1[9] = 90257;
      _array_1[10] = 92615;
      _array_1[11] = 97290;
   }
   int_copy_array(12,_output_,_array_1);
   return ;
}

void synthDrummerTamaRockstar_Drummer__ctx_type_0_init(synthDrummerTamaRockstar_Drummer__ctx_type_0 &_output_){
   synthDrummerTamaRockstar_Drummer__ctx_type_0 _ctx;
   _ctx.step = 0x0 /* 0.000000 */;
   int_init_array(12,0,_ctx.slices_start);
   int_init_array(12,0,_ctx.slices_end);
   _ctx.slice = 0;
   _ctx.size = 0;
   _ctx.sampleFs = 0x0 /* 0.000000 */;
   _ctx.posBase = 0;
   _ctx.pos = 0x0 /* 0.000000 */;
   _ctx.noteRatio = 0x0 /* 0.000000 */;
   _ctx.level = 0x0 /* 0.000000 */;
   _ctx.fsRatio = 0x0 /* 0.000000 */;
   _ctx.fs = 0x0 /* 0.000000 */;
   fix_init_array(256,0x0 /* 0.000000 */,_ctx.buffer_o);
   synthDrummerTamaRockstar_Drummer_default(_ctx);
   _output_ = _ctx;
   return ;
}

fix16_t synthDrummerTamaRockstar_Drummer_process(synthDrummerTamaRockstar_Drummer__ctx_type_0 &_ctx){
   fix16_t value;
   value = 0x0 /* 0.000000 */;
   if((_ctx.slice >= 0) && (_ctx.slice <= 12)){
      _ctx.pos = (_ctx.pos + _ctx.step);
      while(_ctx.pos >= 0x4000000 /* 1024.000000 */){
         _ctx.posBase = (1024 + _ctx.posBase);
         _ctx.pos = (-0x4000000 /* -1024.000000 */ + _ctx.pos);
      }
      int idx;
      idx = (_ctx.posBase + fix_to_int(_ctx.pos));
      if(idx >= _ctx.size){
         _ctx.slice = (-1);
         _ctx.posBase = 0;
         _ctx.pos = 0x0 /* 0.000000 */;
      }
      if(idx >= _ctx.slices_end[_ctx.slice]){
         _ctx.slice = (-1);
         _ctx.posBase = 0;
         _ctx.pos = 0x0 /* 0.000000 */;
      }
      else
      {
         value = fix_mul(_ctx.level,(synthDrummerTamaRockstar_DrummerWrapper_getSample(idx) + fix_mul((_ctx.pos % 0x10000 /* 1.000000 */),(synthDrummerTamaRockstar_DrummerWrapper_getSample((1 + idx)) + (- synthDrummerTamaRockstar_DrummerWrapper_getSample(idx))))));
      }
   }
   return value;
}

void synthDrummerTamaRockstar_Drummer_process_bufferTo(synthDrummerTamaRockstar_Drummer__ctx_type_0 &_ctx, int nb, fix16_t (&oBuffer)[256]){
   nb = int_clip(nb,0,256);
   if(nb == 0){
      nb = 256;
   }
   fix16_t value;
   int i;
   i = 0;
   while(i < nb){
      value = 0x0 /* 0.000000 */;
      if((_ctx.slice >= 0) && (_ctx.slice <= 12)){
         _ctx.pos = (_ctx.pos + _ctx.step);
         while(_ctx.pos >= 0x4000000 /* 1024.000000 */){
            _ctx.posBase = (1024 + _ctx.posBase);
            _ctx.pos = (-0x4000000 /* -1024.000000 */ + _ctx.pos);
         }
         int idx;
         idx = (_ctx.posBase + fix_to_int(_ctx.pos));
         if(idx >= _ctx.size){
            _ctx.slice = (-1);
            _ctx.posBase = 0;
            _ctx.pos = 0x0 /* 0.000000 */;
         }
         if(idx >= _ctx.slices_end[_ctx.slice]){
            _ctx.slice = (-1);
            _ctx.posBase = 0;
            _ctx.pos = 0x0 /* 0.000000 */;
         }
         else
         {
            value = fix_mul(_ctx.level,(synthDrummerTamaRockstar_DrummerWrapper_getSample(idx) + fix_mul((_ctx.pos % 0x10000 /* 1.000000 */),(synthDrummerTamaRockstar_DrummerWrapper_getSample((1 + idx)) + (- synthDrummerTamaRockstar_DrummerWrapper_getSample(idx))))));
         }
      }
      oBuffer[i] = value;
      i = (1 + i);
   }
}

void synthDrummerTamaRockstar_Drummer_setSlices(synthDrummerTamaRockstar_Drummer__ctx_type_0 &_ctx, int (&newSlicesStart)[12], int (&newSlicesEnd)[12]){
   if((12 == 12) && (12 == 12) && (12 == 12)){
      int i;
      i = 0;
      int s;
      int e;
      while(i < 12){
         s = int_clip(newSlicesStart[i],0,((-1) + _ctx.size));
         e = int_clip(newSlicesEnd[i],0,((-1) + _ctx.size));
         if(s <= e){
            _ctx.slices_start[i] = s;
            _ctx.slices_end[i] = e;
         }
         i = (1 + i);
      }
   }
}

void synthDrummerTamaRockstar_Drummer_setSamplerate(synthDrummerTamaRockstar_Drummer__ctx_type_0 &_ctx, fix16_t newFs){
   if(newFs > 0x0 /* 0.000000 */){
      _ctx.fs = newFs;
      _ctx.fsRatio = fix_div(_ctx.sampleFs,_ctx.fs);
   }
   synthDrummerTamaRockstar_Drummer_updateStep(_ctx);
}

void synthDrummerTamaRockstar_Drummer_noteOn(synthDrummerTamaRockstar_Drummer__ctx_type_0 &_ctx, int note, int velocity, int channel){
   note = int_clip(note,0,127);
   int root;
   root = 60;
   _ctx.slice = (note % 12);
   if((_ctx.slice >= 0) && (_ctx.slice < 12)){
      _ctx.posBase = _ctx.slices_start[_ctx.slice];
      _ctx.pos = 0x0 /* 0.000000 */;
   }
   int slice_root;
   slice_root = (note + (- _ctx.slice));
   fix16_t log_two;
   log_two = 0xb172 /* 0.693147 */;
   fix16_t octave;
   octave = fix_mul(0x1555 /* 0.083333 */,int_to_fix((slice_root + (- root))));
   _ctx.noteRatio = fix_exp(fix_mul(log_two,octave));
   synthDrummerTamaRockstar_Drummer_updateStep(_ctx);
   synthDrummerTamaRockstar_Drummer_setLevel(_ctx,synthDrummerTamaRockstar_Util_velocityToLevel(velocity));
}

void synthDrummerTamaRockstar_Drummer_default(synthDrummerTamaRockstar_Drummer__ctx_type_0 &_ctx){
   _ctx.size = synthDrummerTamaRockstar_DrummerWrapper_getSampleSize();
   synthDrummerTamaRockstar_Drummer_setLevel(_ctx,0x10000 /* 1.000000 */);
   _ctx.sampleFs = 0x1e0000 /* 30.000000 */;
   synthDrummerTamaRockstar_Drummer_setSamplerate(_ctx,0x2c1999 /* 44.100000 */);
   int kit_slices_start[12];
   {
      kit_slices_start[0] = 0;
      kit_slices_start[1] = 3250;
      kit_slices_start[2] = 28000;
      kit_slices_start[3] = 31175;
      kit_slices_start[4] = 41306;
      kit_slices_start[5] = 48495;
      kit_slices_start[6] = 62018;
      kit_slices_start[7] = 65600;
      kit_slices_start[8] = 79848;
      kit_slices_start[9] = 82334;
      kit_slices_start[10] = 90270;
      kit_slices_start[11] = 92625;
   }
   int kit_slices_end[12];
   {
      kit_slices_end[0] = 3220;
      kit_slices_end[1] = 27700;
      kit_slices_end[2] = 31174;
      kit_slices_end[3] = 41304;
      kit_slices_end[4] = 48494;
      kit_slices_end[5] = 62017;
      kit_slices_end[6] = 65450;
      kit_slices_end[7] = 79847;
      kit_slices_end[8] = 82333;
      kit_slices_end[9] = 90257;
      kit_slices_end[10] = 92615;
      kit_slices_end[11] = 97290;
   }
   synthDrummerTamaRockstar_Drummer_setSlices(_ctx,kit_slices_start,kit_slices_end);
   synthDrummerTamaRockstar_Buffer_buffer(_ctx.buffer_o);
   _ctx.slice = (-1);
}

void synthDrummerTamaRockstar_Poly__ctx_type_0_init(synthDrummerTamaRockstar_Poly__ctx_type_0 &_output_){
   synthDrummerTamaRockstar_Poly__ctx_type_0 _ctx;
   synthDrummerTamaRockstar_Drummer__ctx_type_0_init(_ctx.voice3);
   synthDrummerTamaRockstar_Drummer__ctx_type_0_init(_ctx.voice2);
   synthDrummerTamaRockstar_Drummer__ctx_type_0_init(_ctx.voice1);
   synthDrummerTamaRockstar_Drummer__ctx_type_0_init(_ctx.voice0);
   _ctx.should_leftovers = false;
   synthDrummerTamaRockstar_Poly_default(_ctx);
   _output_ = _ctx;
   return ;
}

fix16_t synthDrummerTamaRockstar_Poly_getSample(synthDrummerTamaRockstar_Poly__ctx_type_0 &_ctx, int voice){
   switch(voice) {
      case 0:
         return synthDrummerTamaRockstar_Drummer_process(_ctx.voice0);
      break;
      case 1:
         return synthDrummerTamaRockstar_Drummer_process(_ctx.voice1);
      break;
      case 2:
         return synthDrummerTamaRockstar_Drummer_process(_ctx.voice2);
      break;
      case 3:
         return synthDrummerTamaRockstar_Drummer_process(_ctx.voice3);
      break;
    
   }
   return 0x0 /* 0.000000 */;
}

void synthDrummerTamaRockstar_Poly_default(synthDrummerTamaRockstar_Poly__ctx_type_0 &_ctx){
   _ctx.should_leftovers = true;
   synthDrummerTamaRockstar_Drummer_default(_ctx.voice0);
   synthDrummerTamaRockstar_Drummer_default(_ctx.voice1);
   synthDrummerTamaRockstar_Drummer_default(_ctx.voice2);
   synthDrummerTamaRockstar_Drummer_default(_ctx.voice3);
}

void synthDrummerTamaRockstar_Notes__ctx_type_0_init(synthDrummerTamaRockstar_Notes__ctx_type_0 &_output_){
   synthDrummerTamaRockstar_Notes__ctx_type_0 _ctx;
   _ctx.poly = false;
   int_init_array(128,0,_ctx.notes);
   _ctx.nb_notes = 0;
   int_init_array(128,0,_ctx.last_notes);
   synthDrummerTamaRockstar_Notes_default(_ctx);
   _output_ = _ctx;
   return ;
}

int synthDrummerTamaRockstar_Notes_firstNote(synthDrummerTamaRockstar_Notes__ctx_type_0 &_ctx){
   int first_played;
   first_played = 0;
   if(_ctx.nb_notes > 0){
      first_played = _ctx.last_notes[0];
   }
   return first_played;
}

int synthDrummerTamaRockstar_Notes_lastNote(synthDrummerTamaRockstar_Notes__ctx_type_0 &_ctx){
   int last_played;
   last_played = 0;
   if(_ctx.nb_notes > 0){
      last_played = _ctx.last_notes[((-1) + _ctx.nb_notes)];
   }
   return last_played;
}

uint8_t synthDrummerTamaRockstar_Notes_noteOn(synthDrummerTamaRockstar_Notes__ctx_type_0 &_ctx, int note, int velocity, int channel){
   note = int_clip(note,0,127);
   if(_ctx.notes[note] <= 0){
      if(bool_not(_ctx.poly)){
         _ctx.nb_notes = (1 + _ctx.nb_notes);
         if(_ctx.nb_notes > 128){
            _ctx.nb_notes = 128;
         }
      }
      else
      {
         int last_note;
         last_note = synthDrummerTamaRockstar_Notes_lastNote(_ctx);
         if(last_note > 0){
            _ctx.notes[((-1) + last_note)] = 0;
         }
         _ctx.nb_notes = 1;
      }
      _ctx.notes[note] = _ctx.nb_notes;
      _ctx.last_notes[((-1) + _ctx.nb_notes)] = (1 + note);
      return true;
   }
   return false;
}

uint8_t synthDrummerTamaRockstar_Notes_noteOff(synthDrummerTamaRockstar_Notes__ctx_type_0 &_ctx, int note, int channel){
   note = int_clip(note,0,127);
   if(_ctx.notes[note] > 0){
      if(_ctx.poly){
         _ctx.notes[note] = 0;
         _ctx.nb_notes = 0;
      }
      else
      {
         int i;
         i = ((-1) + _ctx.notes[note]);
         while(i < _ctx.nb_notes){
            if(i < 127){
               _ctx.last_notes[i] = _ctx.last_notes[(1 + i)];
            }
            else
            {
               _ctx.last_notes[i] = 0;
            }
            if(_ctx.last_notes[i] > 0){
               _ctx.notes[((-1) + _ctx.last_notes[i])] = (1 + i);
            }
            i = (1 + i);
         }
         _ctx.notes[note] = 0;
         _ctx.nb_notes = ((-1) + _ctx.nb_notes);
         if(_ctx.nb_notes < 0){
            _ctx.nb_notes = 0;
         }
      }
      return true;
   }
   return false;
}

void synthDrummerTamaRockstar_Voice__ctx_type_0_init(synthDrummerTamaRockstar_Voice__ctx_type_0 &_output_){
   synthDrummerTamaRockstar_Voice__ctx_type_0 _ctx;
   synthDrummerTamaRockstar_Notes__ctx_type_0_init(_ctx.voicesinactive);
   synthDrummerTamaRockstar_Notes__ctx_type_0_init(_ctx.voicesactive);
   _ctx.voices_ratio = 0x0 /* 0.000000 */;
   int_init_array(4,0,_ctx.voices);
   synthDrummerTamaRockstar_Poly__ctx_type_0_init(_ctx.poly);
   _ctx.number_voices = 0;
   int_init_array(128,0,_ctx.notes);
   _ctx.normalize = false;
   _ctx.leftovers_decay = 0x0 /* 0.000000 */;
   _ctx.leftovers = 0x0 /* 0.000000 */;
   int_init_array(4,0,_ctx.last_velocities);
   fix_init_array(4,0x0 /* 0.000000 */,_ctx.last_values);
   _ctx.fs = 0x0 /* 0.000000 */;
   fix_init_array(256,0x0 /* 0.000000 */,_ctx.buffer_v3);
   fix_init_array(256,0x0 /* 0.000000 */,_ctx.buffer_v2);
   fix_init_array(256,0x0 /* 0.000000 */,_ctx.buffer_v1);
   fix_init_array(256,0x0 /* 0.000000 */,_ctx.buffer_v0);
   synthDrummerTamaRockstar_Voice_default(_ctx);
   _output_ = _ctx;
   return ;
}

fix16_t synthDrummerTamaRockstar_Voice_process(synthDrummerTamaRockstar_Voice__ctx_type_0 &_ctx){
   fix16_t value;
   value = 0x0 /* 0.000000 */;
   int i;
   i = 0;
   while(i < _ctx.number_voices){
      _ctx.last_values[i] = synthDrummerTamaRockstar_Poly_getSample(_ctx.poly,i);
      value = (value + _ctx.last_values[i]);
      i = (1 + i);
   }
   if(_ctx.leftovers != 0x0 /* 0.000000 */){
      _ctx.leftovers = fix_mul(_ctx.leftovers,_ctx.leftovers_decay);
      value = (_ctx.leftovers + value);
   }
   if(_ctx.normalize){
      return fix_mul(_ctx.voices_ratio,value);
   }
   return value;
}

void synthDrummerTamaRockstar_Voice_process_bufferTo(synthDrummerTamaRockstar_Voice__ctx_type_0 &_ctx, int nb, fix16_t (&oBuffer)[256]){
   nb = int_clip(nb,0,256);
   if(nb == 0){
      nb = 256;
   }
   int v;
   v = 0;
   int i;
   i = 0;
   if(v < _ctx.number_voices){
      synthDrummerTamaRockstar_Poly_runVoice(_ctx.poly,v,nb,_ctx.buffer_v0);
      i = 0;
      while(i < nb){
         oBuffer[i] = _ctx.buffer_v0[i];
         i = (1 + i);
      }
      if(nb > 0){
         _ctx.last_values[v] = _ctx.buffer_v0[((-1) + nb)];
      }
      v = (1 + v);
   }
   while(v < _ctx.number_voices){
      synthDrummerTamaRockstar_Poly_runVoice(_ctx.poly,v,nb,_ctx.buffer_v0);
      i = 0;
      while(i < nb){
         oBuffer[i] = (_ctx.buffer_v0[i] + oBuffer[i]);
         i = (1 + i);
      }
      if(nb > 0){
         _ctx.last_values[v] = _ctx.buffer_v0[((-1) + nb)];
      }
      v = (1 + v);
   }
   i = 0;
   while((_ctx.leftovers != 0x0 /* 0.000000 */) && (i < nb)){
      _ctx.leftovers = fix_mul(_ctx.leftovers,_ctx.leftovers_decay);
      oBuffer[i] = (_ctx.leftovers + oBuffer[i]);
      i = (1 + i);
   }
   if(_ctx.normalize){
      i = 0;
      while(i < nb){
         oBuffer[i] = fix_mul(_ctx.voices_ratio,oBuffer[i]);
         i = (1 + i);
      }
   }
}

void synthDrummerTamaRockstar_Voice_process_bufferTo_alt(synthDrummerTamaRockstar_Voice__ctx_type_0 &_ctx, int nb, fix16_t (&oBuffer)[256]){
   nb = int_clip(nb,0,256);
   if(nb == 0){
      nb = 256;
   }
   synthDrummerTamaRockstar_Poly_runVoice(_ctx.poly,0,nb,_ctx.buffer_v0);
   synthDrummerTamaRockstar_Poly_runVoice(_ctx.poly,1,nb,_ctx.buffer_v1);
   synthDrummerTamaRockstar_Poly_runVoice(_ctx.poly,2,nb,_ctx.buffer_v2);
   synthDrummerTamaRockstar_Poly_runVoice(_ctx.poly,3,nb,_ctx.buffer_v3);
   if(nb > 0){
      _ctx.last_values[0] = _ctx.buffer_v0[((-1) + nb)];
      _ctx.last_values[1] = _ctx.buffer_v1[((-1) + nb)];
      _ctx.last_values[2] = _ctx.buffer_v2[((-1) + nb)];
      _ctx.last_values[3] = _ctx.buffer_v3[((-1) + nb)];
   }
   int i;
   i = 0;
   if(_ctx.normalize){
      while(i < nb){
         oBuffer[i] = fix_mul(_ctx.voices_ratio,(_ctx.buffer_v0[i] + _ctx.buffer_v1[i] + _ctx.buffer_v2[i] + _ctx.buffer_v3[i]));
         i = (1 + i);
      }
      i = 0;
      while((_ctx.leftovers != 0x0 /* 0.000000 */) && (i < nb)){
         _ctx.leftovers = fix_mul(_ctx.leftovers,_ctx.leftovers_decay);
         oBuffer[i] = (oBuffer[i] + fix_mul(_ctx.leftovers,_ctx.voices_ratio));
         i = (1 + i);
      }
   }
   else
   {
      while(i < nb){
         oBuffer[i] = (_ctx.buffer_v0[i] + _ctx.buffer_v1[i] + _ctx.buffer_v2[i] + _ctx.buffer_v3[i]);
         i = (1 + i);
      }
      i = 0;
      while((_ctx.leftovers != 0x0 /* 0.000000 */) && (i < nb)){
         _ctx.leftovers = fix_mul(_ctx.leftovers,_ctx.leftovers_decay);
         oBuffer[i] = (_ctx.leftovers + oBuffer[i]);
         i = (1 + i);
      }
   }
}

void synthDrummerTamaRockstar_Voice_noteOff(synthDrummerTamaRockstar_Voice__ctx_type_0 &_ctx, int note, int channel){
   note = int_clip(note,0,127);
   int v;
   v = _ctx.notes[note];
   if((v > 0) && (v <= 4)){
      if(synthDrummerTamaRockstar_Notes_noteOff(_ctx.voicesactive,((-1) + v),0)){
         synthDrummerTamaRockstar_Poly_sendNoteOff(_ctx.poly,((-1) + v),note,channel);
         _ctx.notes[note] = 0;
         _ctx.voices[((-1) + v)] = 0;
         if(v <= _ctx.number_voices){
            synthDrummerTamaRockstar_Notes_noteOn(_ctx.voicesinactive,((-1) + v),127,0);
         }
      }
   }
}

void synthDrummerTamaRockstar_Voice_noteOn(synthDrummerTamaRockstar_Voice__ctx_type_0 &_ctx, int note, int velocity, int channel){
   note = int_clip(note,0,127);
   velocity = int_clip(velocity,0,127);
   if(_ctx.notes[note] <= 0){
      int v;
      v = synthDrummerTamaRockstar_Notes_firstNote(_ctx.voicesinactive);
      if((v <= 0) || (v > _ctx.number_voices)){
         int active_v;
         active_v = synthDrummerTamaRockstar_Notes_firstNote(_ctx.voicesactive);
         if(active_v > 0){
            synthDrummerTamaRockstar_Voice_noteOff(_ctx,_ctx.voices[((-1) + active_v)],0);
         }
      }
      v = synthDrummerTamaRockstar_Notes_firstNote(_ctx.voicesinactive);
      if((v > 0) && (v <= _ctx.number_voices)){
         if(synthDrummerTamaRockstar_Notes_noteOff(_ctx.voicesinactive,((-1) + v),0) && synthDrummerTamaRockstar_Notes_noteOn(_ctx.voicesactive,((-1) + v),127,0)){
            if(synthDrummerTamaRockstar_Poly_shouldLeftOvers(_ctx.poly)){
               _ctx.leftovers = (_ctx.leftovers + _ctx.last_values[((-1) + v)]);
            }
            else
            {
               int diff_velocity;
               diff_velocity = (_ctx.last_velocities[((-1) + v)] + (- velocity));
               fix16_t diff_level;
               diff_level = 0x0 /* 0.000000 */;
               if(diff_velocity > 0){
                  diff_level = fix_mul(0x204 /* 0.007874 */,int_to_fix(diff_velocity));
               }
               _ctx.leftovers = (_ctx.leftovers + fix_mul(diff_level,_ctx.last_values[((-1) + v)]));
            }
            synthDrummerTamaRockstar_Poly_sendNoteOn(_ctx.poly,((-1) + v),note,velocity,channel);
            _ctx.notes[note] = v;
            _ctx.voices[((-1) + v)] = note;
            _ctx.last_velocities[((-1) + v)] = velocity;
         }
      }
   }
}

void synthDrummerTamaRockstar_Voice_setNbVoices(synthDrummerTamaRockstar_Voice__ctx_type_0 &_ctx, int nbvoices){
   nbvoices = int_clip(nbvoices,0,4);
   int i;
   i = synthDrummerTamaRockstar_Notes_nbNotes(_ctx.voicesactive);
   while((i > nbvoices) && (i > 0)){
      synthDrummerTamaRockstar_Voice_noteOff(_ctx,_ctx.voices[((-1) + i)],0);
      synthDrummerTamaRockstar_Notes_noteOff(_ctx.voicesinactive,((-1) + i),0);
      i = ((-1) + i);
   }
   i = synthDrummerTamaRockstar_Notes_nbNotes(_ctx.voicesinactive);
   if(i < nbvoices){
      while(i < nbvoices){
         synthDrummerTamaRockstar_Notes_noteOn(_ctx.voicesinactive,i,127,0);
         i = (1 + i);
      }
   }
   else
   {
      while(i >= nbvoices){
         synthDrummerTamaRockstar_Notes_noteOff(_ctx.voicesinactive,i,0);
         i = ((-1) + i);
      }
   }
   _ctx.number_voices = nbvoices;
   if(_ctx.number_voices > 0){
      _ctx.voices_ratio = fix_div(0x10000 /* 1.000000 */,int_to_fix(_ctx.number_voices));
   }
}

void synthDrummerTamaRockstar_Voice_setSamplerate(synthDrummerTamaRockstar_Voice__ctx_type_0 &_ctx, fix16_t newFs){
   if(newFs > 0x0 /* 0.000000 */){
      _ctx.fs = newFs;
   }
   synthDrummerTamaRockstar_Poly_setSamplerate(_ctx.poly,_ctx.fs);
   fix16_t log_base;
   log_base = 0x24d76 /* 2.302585 */;
   _ctx.leftovers_decay = fix_exp(fix_div(fix_mul(-0xc4 /* -0.003000 */,log_base),fix_mul(0x3333 /* 0.200000 */,_ctx.fs)));
}

void synthDrummerTamaRockstar_Voice_default(synthDrummerTamaRockstar_Voice__ctx_type_0 &_ctx){
   synthDrummerTamaRockstar_Poly_default(_ctx.poly);
   synthDrummerTamaRockstar_Buffer_buffer(_ctx.buffer_v0);
   synthDrummerTamaRockstar_Buffer_buffer(_ctx.buffer_v1);
   synthDrummerTamaRockstar_Buffer_buffer(_ctx.buffer_v2);
   synthDrummerTamaRockstar_Buffer_buffer(_ctx.buffer_v3);
   if(_ctx.number_voices == 0){
      _ctx.number_voices = 4;
   }
   synthDrummerTamaRockstar_Voice_setNbVoices(_ctx,_ctx.number_voices);
   synthDrummerTamaRockstar_Notes_default(_ctx.voicesactive);
   synthDrummerTamaRockstar_Notes_setPoly(_ctx.voicesactive,false);
   synthDrummerTamaRockstar_Notes_default(_ctx.voicesinactive);
   synthDrummerTamaRockstar_Notes_setPoly(_ctx.voicesinactive,false);
   synthDrummerTamaRockstar_Voice_setNormalize(_ctx,true);
   synthDrummerTamaRockstar_Voice_setSamplerate(_ctx,0x2c1999 /* 44.100000 */);
}

void synthDrummerTamaRockstar_Voice__ctx_type_1_init(synthDrummerTamaRockstar_Voice__ctx_type_1 &_output_){
   synthDrummerTamaRockstar_Voice__ctx_type_1 _ctx;
   synthDrummerTamaRockstar_Voice__ctx_type_0_init(_ctx._inst275);
   synthDrummerTamaRockstar_Voice__ctx_type_0_init(_ctx._inst1b9);
   _output_ = _ctx;
   return ;
}

int synthDrummerTamaRockstar_Processor_cvToPitch(fix16_t cv){
   fix16_t pitch;
   pitch = (0x3c0000 /* 60.000000 */ + fix_mul(0x780000 /* 120.000000 */,cv));
   if((pitch % 0x10000 /* 1.000000 */) >= 0x8000 /* 0.500000 */){
      pitch = fix_floor((0x10000 /* 1.000000 */ + pitch));
   }
   else
   {
      pitch = fix_floor(pitch);
   }
   pitch = fix_clip(pitch,0x0 /* 0.000000 */,0x7f0000 /* 127.000000 */);
   return fix_to_int(pitch);
}

void synthDrummerTamaRockstar_Processor__ctx_type_1_init(synthDrummerTamaRockstar_Processor__ctx_type_1 &_output_){
   synthDrummerTamaRockstar_Processor__ctx_type_1 _ctx;
   synthDrummerTamaRockstar_Voice__ctx_type_0_init(_ctx.voice);
   int_init_array(16,0,_ctx.last_pitches);
   _ctx.last_nbcables = 0;
   bool_init_array(16,false,_ctx.last_gates);
   _ctx.fs = 0x0 /* 0.000000 */;
   synthDrummerTamaRockstar_Processor_default(_ctx);
   _output_ = _ctx;
   return ;
}

void synthDrummerTamaRockstar_Processor_setNote(synthDrummerTamaRockstar_Processor__ctx_type_1 &_ctx, fix16_t gate, fix16_t voct, fix16_t vel, int cable){
   fix16_t velocity;
   velocity = fix_mul(0x7f0000 /* 127.000000 */,fix_clip(vel,0x0 /* 0.000000 */,0x10000 /* 1.000000 */));
   if(velocity == 0x0 /* 0.000000 */){
      velocity = 0x7f0000 /* 127.000000 */;
   }
   if(bool_not(_ctx.last_gates[cable]) && (gate >= 0x1999 /* 0.100000 */)){
      _ctx.last_gates[cable] = true;
      _ctx.last_pitches[cable] = synthDrummerTamaRockstar_Processor_cvToPitch(voct);
      synthDrummerTamaRockstar_Voice_noteOn(_ctx.voice,_ctx.last_pitches[cable],fix_to_int(velocity),0);
   }
   else
   {
      if(_ctx.last_gates[cable] && (gate < 0x1999 /* 0.100000 */)){
         if(_ctx.last_pitches[cable] >= 0){
            synthDrummerTamaRockstar_Voice_noteOff(_ctx.voice,_ctx.last_pitches[cable],0);
         }
         _ctx.last_gates[cable] = false;
         _ctx.last_pitches[cable] = (-1);
      }
   }
}

void synthDrummerTamaRockstar_Processor_nbCables(synthDrummerTamaRockstar_Processor__ctx_type_1 &_ctx, int nbcables){
   if(nbcables != _ctx.last_nbcables){
      _ctx.last_nbcables = nbcables;
      int c;
      c = nbcables;
      while((c < 16) && (c < 16)){
         if(_ctx.last_gates[c] && (_ctx.last_pitches[c] >= 0)){
            synthDrummerTamaRockstar_Voice_noteOff(_ctx.voice,_ctx.last_pitches[c],0);
         }
         _ctx.last_gates[c] = false;
         _ctx.last_pitches[c] = (-1);
         c = (1 + c);
      }
   }
}


