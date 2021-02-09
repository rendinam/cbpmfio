//
// cbpmfio_defs.c
//

#define CBPMFIO_NO_EXTERN

#include "cbpmfio.h"

// Placeholder no-operation function for I/O use.
void cbpmfio_noop(int dummy, ...) {
}

int cbpmfio_memory_allocated = CBPMFIO_FALSE;

CBPMFIO_FIELD_SPEC RDV3_header_specs[] = {
  {
    0,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Instrument_Type   : %s\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    1,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Command_ID        : %s\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    2,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "File_type         : %s\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    3,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "File_ID           : %d\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    4,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "File_Version      : %d\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    5,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Timestamp         : %s",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    6,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Core_commstruct_v : %010d\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    7,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Plat_commstruct_v : %010d\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    8,
    CBPMFIO_READWRITE,
    &(cbpmfio_noop),
    &(cbpmfio_scan_line_output),
    "Bunch_Patt_Name   : ****\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    9,
    CBPMFIO_READWRITE,
    &(cbpmfio_bunch_patt_input),
    &(cbpmfio_bunch_patt_output),
    "Bunch_Patt_(hex)  : ",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    10,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Species           : %s\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    11,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Num_Instruments   : %d\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    12,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Number_of_Bunches : %d\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    13,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Number_of_Turns   : %d\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    14,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Turn_Spacing      : %d\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    15,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Timing_Setup      : %s\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    16,
    CBPMFIO_READWRITE,
    &(cbpmfio_noop),
    &(cbpmfio_scan_line_output),
    "Trigger           : ****", // no LF here?
    {(long)CBPMFIO_NO_ADDRESS}
  }
};
int num_RDV3_header_specs = sizeof(RDV3_header_specs)/sizeof(CBPMFIO_FIELD_SPEC);



CBPMFIO_FIELD_SPEC RDV3_cesr_specs[] = {
  {
    0,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "CESR CONDX        : %d\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    1,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "CERN Current Raw  : %d\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    2,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "CERN Current mA   : %f\n",
    {(long)CBPMFIO_NO_ADDRESS}
  }
};
int num_RDV3_cesr_specs = sizeof(RDV3_cesr_specs)/sizeof(CBPMFIO_FIELD_SPEC);



CBPMFIO_FIELD_SPEC RDV3_inst_header_specs[] = {
  {
    0,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Location          : %s\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    1,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "BPM_hostname      : %s\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    2,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "BPM_IP_Address    : %s\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    3,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Detector_Type     : %s\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    4,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Detector_Coeffs   : %f  %f\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    5,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "EXE_Name          : %s\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    6,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "EXE_Build_ID      : %010d\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    7,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Dig.Board_FPGA    : %d.%d\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    8,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Front-End_FPGAs   : %d %d %d %d\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    9,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Timing_Setup      : %s\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    10,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Number_of_Turns   : %d\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    11,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Turn_sync_counter : %d\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    12,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Turn_spacing      : %d\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    13,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Trigger           : %s\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    14,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Bunch_Pat_offsets : %d  %d\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    15,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Com_Turnmrk_Dly   : %d\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    16,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Blk_Turnmrk_Dlys  : %d  %d\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    17,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Block_Delays      : %d  %d\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    18,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Channel_Delays    : %d  %d  %d  %d    %d  %d  %d  %d\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    19,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Gain_Settings     : %d  %d  %d  %d    %d  %d  %d  %d\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    20,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Gain_Codes        : %d  %d  %d  %d    %d  %d  %d  %d\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    21,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Gain_Coeffs       : %f  %f  %f  %f    %f  %f  %f  %f\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    22,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Pedestals         : %f  %f  %f  %f    %f  %f  %f  %f\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    23,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Digital_Temp_C    : %3.1f\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    24,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "Card_Temps_C      : %3.1f  %3.1f  %3.1f  %3.1f\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    25,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "ADC_saturation    : %04d    %04d\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    26,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "ADC_High          : %04d    %04d\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    27,
    CBPMFIO_READWRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "ADC_Low           : %04d    %04d\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
};
int num_RDV3_inst_header_specs = sizeof(RDV3_inst_header_specs)/sizeof(CBPMFIO_FIELD_SPEC);



CBPMFIO_FIELD_SPEC RDV3_raw_data_label_specs[] = {
  {
    0,
    CBPMFIO_WRITE,
    &(cbpmfio_noop),
    &(cbpmfio_scan_line_output),
    "# Timing  Encoded     Card-0   Card-1   Card-2   Card-3\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    1,
    CBPMFIO_WRITE,
    &(cbpmfio_noop),
    &(cbpmfio_scan_line_output),
    "# Block  Phase word   b3(TI)   b1(BI)   b2(BO)   b4(TO)\n",
    {(long)CBPMFIO_NO_ADDRESS}
  },
  {
    2,
    CBPMFIO_WRITE,
    &(cbpmfio_noop),
    &(cbpmfio_scan_line_output),
    "--BEGIN DATA--\n",
    {(long)CBPMFIO_NO_ADDRESS}
  }
};
int num_RDV3_raw_data_label_specs = sizeof(RDV3_raw_data_label_specs)/sizeof(CBPMFIO_FIELD_SPEC);



CBPMFIO_FIELD_SPEC RDV3_raw_data_spec[] = {
  {
    0,
    CBPMFIO_WRITE,
    &(cbpmfio_scan_line_input),
    &(cbpmfio_scan_line_output),
    "%d       %07x  %7d  %7d  %7d  %7d\n",
    {(long)CBPMFIO_NO_ADDRESS}
  }
};


RDV3_FILE_HEADER *p_v3_file_header;
RDV3_CESR_HEADER *p_v3_cesr_header;
RDV3_INST_DATA   *p_v3_inst_array;

int inst_count_g;
