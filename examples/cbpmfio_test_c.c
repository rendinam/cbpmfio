//
// Test program for decoupled C FIO mechanism.
//


#include "cbpmfio.h"

int main(void) {

  int file_idx;
  int retval;
  int num_insts, num_bunches, num_turns;
  char timestamp[50] = "";
  float ff;
  int zero  = 0;
  int one   = 1;
  int two   = 2;
  int three = 3;
  int iidx, bunch, button;
  int *dat0, *dat1, *dat2, *dat3;
  float *fdat0, *fdat1, *fdat2, *fdat3;
  int rf_bucket;
  char name[20] = ".";
  int namecount = 0;
  char names[110][20];


  //file_idx = 4080;
  file_idx = 8360;
  printf("F I R S T    F I L E\n");

  retval = cbpm_read_rawfile(&file_idx);
  printf("cbpm_read_rawfile_ returned: %d\n", retval);

  num_insts = cbpm_rawfile_num_instruments();
  num_bunches = cbpm_rawfile_num_bunches();
  num_turns = cbpm_rawfile_num_turns();

  cbpm_rawfile_timestamp_(timestamp);
  printf("File ID     : %d\n", file_idx);
  printf("TIMESTAMP   = %s\n", timestamp);
  printf("NUM_INSTS   = %d\n", num_insts);
  printf("NUM_BUNCHES = %d\n", num_bunches);
  printf("NUM_TURNS   = %d\n", num_turns);
  printf("CONDX #     = %d\n", cbpm_rawfile_condx_number());
  ff = cbpm_rawfile_cern_current(); //necessary intermediate
  printf("CERN CURR   = %f\n", ff);

  cbpm_rawfile_inst_names_(name);
  strcpy(names[namecount], name);
  namecount++;
  while(strcmp(name, "") != 0) {
    cbpm_rawfile_inst_names_(name);
    strcpy(names[namecount], name);
    namecount++;
  }

  for (iidx = 0; iidx < num_insts; iidx++) {
    printf("\n\nLocation: %s\n", names[iidx]);
    bunch = 1;
    rf_bucket = cbpm_rawfile_rf_bucket(&bunch);
    printf("RF bucket = %d\n", rf_bucket);
    printf("PEDS            %f %f %f %f\n",
	   cbpm_rawfile_pedestal(names[iidx], &bunch, &zero),
	   cbpm_rawfile_pedestal(names[iidx], &bunch, &one),
	   cbpm_rawfile_pedestal(names[iidx], &bunch, &two),
	   cbpm_rawfile_pedestal(names[iidx], &bunch, &three));
    
    printf("GAINS           %f %f %f %f\n",
	   cbpm_rawfile_gain_factor(names[iidx], &bunch, &zero),
	   cbpm_rawfile_gain_factor(names[iidx], &bunch, &one),
	   cbpm_rawfile_gain_factor(names[iidx], &bunch, &two),
	   cbpm_rawfile_gain_factor(names[iidx], &bunch, &three));

    dat0 = cbpm_rawfile_raw_ptr(names[iidx], &zero);
    dat1 = cbpm_rawfile_raw_ptr(names[iidx], &one);
    dat2 = cbpm_rawfile_raw_ptr(names[iidx], &two);
    dat3 = cbpm_rawfile_raw_ptr(names[iidx], &three);
    printf("RAW............ %d %d %d %d\n",
	   *dat0,
	   *dat1,
	   *dat2,
	   *dat3);
    printf("                %d %d %d %d\n",
	   *(dat0+1),
	   *(dat1+1),
	   *(dat2+1),
	   *(dat3+1));

    fdat0 = cbpm_rawfile_tbt_ptr(names[iidx], &zero);
    fdat1 = cbpm_rawfile_tbt_ptr(names[iidx], &one);
    fdat2 = cbpm_rawfile_tbt_ptr(names[iidx], &two);
    fdat3 = cbpm_rawfile_tbt_ptr(names[iidx], &three);
    printf("TBT............ %f %f %f %f\n",
	   *fdat0,
	   *fdat1,
	   *fdat2,
	   *fdat3);
    printf("                %f %f %f %f\n",
	   *(fdat0+1),
	   *(fdat1+1),
	   *(fdat2+1),
	   *(fdat3+1));


    fdat0 = cbpm_rawfile_pos_ptr(names[iidx], &zero);
    fdat1 = cbpm_rawfile_pos_ptr(names[iidx], &one);
    printf("POS x y         %f %f\n",
	   *fdat0,
	   *fdat1);
    printf("POS x y         %f %f\n",
	   *(fdat0+1),
	   *(fdat1+1));

    dat0 = cbpm_rawfile_phase_ptr(names[iidx], &zero);
    dat1 = cbpm_rawfile_phase_ptr(names[iidx], &one);
    printf("phase word x y  %3d %3d\n",
	   *(dat0),
	   *(dat1));
    printf("phase word x y  %3d %3d\n",
	   *(dat0+1),
	   *(dat1+1));


  } //endFOR iidx
  namecount = 0;


  //  file_idx = 8362;
  file_idx = 8361;
  printf("S E C O N D    F I L E\n");

  retval = cbpm_read_rawfile(&file_idx);
  printf("cbpm_read_rawfile_ returned: %d\n", retval);

  num_insts = cbpm_rawfile_num_instruments();
  num_bunches = cbpm_rawfile_num_bunches();
  num_turns = cbpm_rawfile_num_turns();

  cbpm_rawfile_timestamp_(timestamp);
  printf("File ID     : %d\n", file_idx);
  printf("TIMESTAMP   = %s\n", timestamp);
  printf("NUM_INSTS   = %d\n", num_insts);
  printf("NUM_BUNCHES = %d\n", num_bunches);
  printf("NUM_TURNS   = %d\n", num_turns);
  printf("CONDX #     = %d\n", cbpm_rawfile_condx_number());
  ff = cbpm_rawfile_cern_current(); //necessary intermediate
  printf("CERN CURR   = %f\n", ff);

  cbpm_rawfile_inst_names_(name);
  //printf("NAME = %s\n", name);
  strcpy(names[namecount], name);
  namecount++;
  while(strcmp(name, "") != 0) {
    cbpm_rawfile_inst_names_(name);
    //printf("NAME = %s\n", name);
    strcpy(names[namecount], name);
    namecount++;
  }

  for (iidx = 0; iidx < num_insts; iidx++) {
    printf("\n\nLocation: %s\n", names[iidx]);
    bunch = 1;
    rf_bucket = cbpm_rawfile_rf_bucket(&bunch);
    printf("RF bucket = %d\n", rf_bucket);
    printf("PEDS            %f %f %f %f\n",
	   cbpm_rawfile_pedestal(names[iidx], &bunch, &zero),
	   cbpm_rawfile_pedestal(names[iidx], &bunch, &one),
	   cbpm_rawfile_pedestal(names[iidx], &bunch, &two),
	   cbpm_rawfile_pedestal(names[iidx], &bunch, &three));
    
    printf("GAINS           %f %f %f %f\n",
	   cbpm_rawfile_gain_factor(names[iidx], &bunch, &zero),
	   cbpm_rawfile_gain_factor(names[iidx], &bunch, &one),
	   cbpm_rawfile_gain_factor(names[iidx], &bunch, &two),
	   cbpm_rawfile_gain_factor(names[iidx], &bunch, &three));

    dat0 = cbpm_rawfile_raw_ptr(names[iidx], &zero);
    dat1 = cbpm_rawfile_raw_ptr(names[iidx], &one);
    dat2 = cbpm_rawfile_raw_ptr(names[iidx], &two);
    dat3 = cbpm_rawfile_raw_ptr(names[iidx], &three);
    printf("RAW............ %d %d %d %d\n",
	   *dat0,
	   *dat1,
	   *dat2,
	   *dat3);
    printf("                %d %d %d %d\n",
	   *(dat0+1),
	   *(dat1+1),
	   *(dat2+1),
	   *(dat3+1));

    fdat0 = cbpm_rawfile_tbt_ptr(names[iidx], &zero);
    fdat1 = cbpm_rawfile_tbt_ptr(names[iidx], &one);
    fdat2 = cbpm_rawfile_tbt_ptr(names[iidx], &two);
    fdat3 = cbpm_rawfile_tbt_ptr(names[iidx], &three);
    printf("TBT............ %f %f %f %f\n",
	   *fdat0,
	   *fdat1,
	   *fdat2,
	   *fdat3);
    printf("                %f %f %f %f\n",
	   *(fdat0+1),
	   *(fdat1+1),
	   *(fdat2+1),
	   *(fdat3+1));


    fdat0 = cbpm_rawfile_pos_ptr(names[iidx], &zero);
    fdat1 = cbpm_rawfile_pos_ptr(names[iidx], &one);
    printf("POS x y         %f %f\n",
	   *fdat0,
	   *fdat1);
    printf("POS x y         %f %f\n",
	   *(fdat0+1),
	   *(fdat1+1));

    dat0 = cbpm_rawfile_phase_ptr(names[iidx], &zero);
    dat1 = cbpm_rawfile_phase_ptr(names[iidx], &one);
    printf("phase word x y  %3d %3d\n",
	   *(dat0),
	   *(dat1));
    printf("phase word x y  %3d %3d\n",
	   *(dat0+1),
	   *(dat1+1));


  } //endFOR iidx
  

  return CBPMFIO_SUCCESS;
}

