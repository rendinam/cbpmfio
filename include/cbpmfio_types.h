//
// cbpmfio_types.h
//

#ifndef CBPMFIO_TYPES_H
#define CBPMFIO_TYPES_H

#include "cbpmfio_constants.h"

typedef struct {
  int field_ID;
  int  mode;
  void *input_func;
  void *output_func;
  char format[60];
  long addresses[CBPMFIO_MAX_FIELD_ADDRESSES];
} CBPMFIO_FIELD_SPEC;

typedef long fio_addrs[CBPMFIO_MAX_FIELD_ADDRESSES];



typedef struct {
  char instrument_type[8];
  char command_ID[30];
  char file_type[50];
  int file_id;
  int file_version;
  char timestamp[50];
  int core_commstruct_rev;
  int platform_commstruct_rev;
  char bunch_patt_name[50];
  int bunch_pattern[40];
  char species_name[10];
  int num_instruments;
  int num_bunches;
  int num_turns;
  int turn_spacing;
  char timing_setup[30];
} RDV3_FILE_HEADER;

typedef struct {
  int condx;
  int raw_current;
  float mA_current;
} RDV3_CESR_HEADER;

typedef struct {
  char location[10];
  char hostname[10];
  char IP_address[17];
  char detector_type[10];
  float horz_coeff;
  float vert_coeff;
  char ldr_name[20];
  int build_timestamp;
  int fpga_maj;
  int fpga_min;
  int fpga_id[4];
  char timing_setup[20];
  int num_turns;
  int turn_counter;
  int turn_spacing;
  char trigger[10];
  int bp_offsets[2];
  int ctmd;
  int btmds[2];
  int block_delays[2];
  int chan_delays[2][4];
  int gain_settings[2][4];
  int gain_codes[2][4];
  float gain_coeffs[2][4];
  float pedestals[2][4];
  float dig_temp_c;
  float card_temps_c[4];
  int adc_saturation[2][4];
  int adc_high[2][4];
  int adc_low[2][4];
  int *timing_blocks;
  int *phase_words;
  int *TIraw;
  int *BIraw;
  int *BOraw;
  int *TOraw;
  float *TIcorrected;
  float *BIcorrected;
  float *BOcorrected;
  float *TOcorrected;
  float *Xpos;
  float *Ypos;
  int *X_phase_words;
  int *Y_phase_words;
} RDV3_INST_DATA;




#endif
