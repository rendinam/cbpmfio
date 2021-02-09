/*!-----------------------------------------------------------------------+
* File         :  cbpmfio_rw_instrument_header.c                          |
*                                                                         |
* Description  :  Writes a summary of timings, gain settings/codes,       |
*                 temperatures, version/identification info for a         |
*                 particular instrument to the given file/stream pointer. |
*                                                                         |
* Arguments    :  Instrument index (int)                                  |
*                 Pointer to file stream (FILE)                           |
*                                                                         |
* Author       :  M. Rendina                                              |
*-------------------------------------------------------------------------+*/

#include "cbpmfio.h"


int cbpmfio_rw_instrument_header(FILE *fp, int fio_mode) {

  cbpmfio_rw_file_section(fp, fio_mode, num_RDV3_inst_header_specs, (CBPMFIO_FIELD_SPEC*)&(RDV3_inst_header_specs));

  return CBPMFIO_SUCCESS;

}


