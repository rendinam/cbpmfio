#include "cbpmfio.h"


int cbpmfio_v3_inst_alloc(int iidx) {

  int num_words = p_v3_file_header->num_bunches * p_v3_file_header->num_turns;

  p_v3_inst_array[iidx].timing_blocks = malloc(p_v3_file_header->num_bunches*sizeof(int));
  p_v3_inst_array[iidx].phase_words = malloc(num_words*sizeof(int));
  p_v3_inst_array[iidx].TIraw = malloc(num_words*sizeof(int));
  p_v3_inst_array[iidx].BIraw = malloc(num_words*sizeof(int));
  p_v3_inst_array[iidx].BOraw = malloc(num_words*sizeof(int));
  p_v3_inst_array[iidx].TOraw = malloc(num_words*sizeof(int));
  
  p_v3_inst_array[iidx].TIcorrected = malloc(num_words*sizeof(float));
  p_v3_inst_array[iidx].BIcorrected = malloc(num_words*sizeof(float));
  p_v3_inst_array[iidx].BOcorrected = malloc(num_words*sizeof(float));
  p_v3_inst_array[iidx].TOcorrected = malloc(num_words*sizeof(float));
  
  p_v3_inst_array[iidx].Xpos = malloc(num_words*sizeof(float));
  p_v3_inst_array[iidx].Ypos = malloc(num_words*sizeof(float));
  
  p_v3_inst_array[iidx].X_phase_words = malloc(num_words*sizeof(int));
  p_v3_inst_array[iidx].Y_phase_words = malloc(num_words*sizeof(int));
  
  return CBPMFIO_SUCCESS;

}


int cbpmfio_v3_free_inst_mem(int iidx) {

  free(p_v3_inst_array[iidx].timing_blocks);
  free(p_v3_inst_array[iidx].phase_words);
  free(p_v3_inst_array[iidx].TIraw);
  free(p_v3_inst_array[iidx].BIraw);
  free(p_v3_inst_array[iidx].BOraw);
  free(p_v3_inst_array[iidx].TOraw);
  free(p_v3_inst_array[iidx].TIcorrected);
  free(p_v3_inst_array[iidx].BIcorrected);
  free(p_v3_inst_array[iidx].BOcorrected);
  free(p_v3_inst_array[iidx].TOcorrected);
  free(p_v3_inst_array[iidx].Xpos);
  free(p_v3_inst_array[iidx].Ypos);
  free(p_v3_inst_array[iidx].X_phase_words);
  free(p_v3_inst_array[iidx].Y_phase_words);

}






