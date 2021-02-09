/*!-----------------------------------------------------------------------+
* File         :  cbpmfio_rw_cesr_header.c                                |
*                                                                         |
* Description  :  Writes selected CESR machine information such as beam   |
*                 current etc. to the data file.                          |
*                                                                         |
* Arguments    :  FILE pointer to destination file                        |
*                 int  file type identifier                               |
*                 int  instrument index                                   |
*                 int  file index value                                   |
*                                                                         | 
* Author       :  M. Rendina                                              |
*-------------------------------------------------------------------------+*/

#include "cbpmfio.h"


int cbpmfio_rw_cesr_header(FILE *fp, int fio_mode) {

  cbpmfio_rw_file_section(fp, fio_mode, num_RDV3_cesr_specs, (CBPMFIO_FIELD_SPEC*)&(RDV3_cesr_specs));
  // Divider line between header sections
  if (fio_mode == CBPMFIO_WRITE) {
    fprintf(fp, "\n");
  }

  return CBPMFIO_SUCCESS;

}
