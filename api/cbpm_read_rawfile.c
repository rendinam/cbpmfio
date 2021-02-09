/*!-----------------------------------------------------------------------+
* File         :  cbpm_read_rawfile.c                                     |
*                                                                         |
* Description  :  Reads in selected contents of a CBPM RAW data file and  |
*                 stores the gain-scaled and pedestal-subtracted values   |
*                 in an internal buffer for each instrument, bunch, and   |
*                 turn worth of data found in the file.                   |
*-------------------------------------------------------------------------+*/

#include "cbpmfio.h"


int cbpm_read_rawfile(int *file_idx) {

  char *func_name = (char *)__FUNCTION__;

  FILE *fp;
  int   iidx, num_insts;

  char full_filename[150] = "";
  char temp_name[50];

  // Determine which CESR OFFLINE data directory holds the
  // RAW data file with the index provided.
  char subdir_string[6] = "";
  strcpy( full_filename, CBPMFIO_ONLINE_RAW_DATA_DIR );
  cbpmfio_file_subdir( *file_idx, subdir_string );
  strcat( full_filename, subdir_string );
  sprintf( temp_name, "RD-%06d.dat", *file_idx );
  strcat( full_filename, temp_name );
  

  struct stat buffer;
  if ( stat(full_filename, &buffer) != 0) {
    printf("Unable to stat %s\n", full_filename );
    
    strcpy( full_filename, CBPMFIO_OFFLINE_RAW_DATA_DIR );
    strcat( full_filename, subdir_string );
    strcat( full_filename, temp_name );

    if ( stat(full_filename, &buffer) != 0) {
      printf("Unable to stat %s\n", full_filename );
      return CBPMFIO_FAILURE;
    }
  }

  fp = fopen(full_filename, "r");
  if (fp == NULL) {
    printf("[%s] ERROR opening data file %s!\n", func_name, full_filename);
    perror(func_name);
    return CBPMFIO_SUCCESS;
  }


  if (cbpmfio_memory_allocated == CBPMFIO_TRUE) {
    for (iidx = 0; iidx < p_v3_file_header->num_instruments; iidx++) {
      cbpmfio_v3_free_inst_mem(iidx);
    }
    free(p_v3_file_header);
    free(p_v3_cesr_header);
    cbpmfio_memory_allocated = CBPMFIO_FALSE;
  }

  if (cbpmfio_memory_allocated == CBPMFIO_FALSE) {
    p_v3_file_header = malloc(sizeof(RDV3_FILE_HEADER));
    p_v3_cesr_header = malloc(sizeof(RDV3_CESR_HEADER));
  }


  inst_count_g = 0;

  // Begin field mapping
  fio_addrs addrs;
  addrs[0] = (long)&(p_v3_file_header->instrument_type);
  cbpmfio_map_addresses_to_field(&RDV3_header_specs, 0, addrs);

  addrs[0] = (long)&(p_v3_file_header->command_ID);
  cbpmfio_map_addresses_to_field(&RDV3_header_specs, 1, addrs);

  addrs[0] = (long)&(p_v3_file_header->file_type);
  cbpmfio_map_addresses_to_field(&RDV3_header_specs, 2, addrs);

  addrs[0] = (long)&(p_v3_file_header->file_id);
  cbpmfio_map_addresses_to_field(&RDV3_header_specs, 3, addrs);

  addrs[0] = (long)&(p_v3_file_header->file_version);
  cbpmfio_map_addresses_to_field(&RDV3_header_specs, 4, addrs);

  addrs[0] = (long)&(p_v3_file_header->timestamp);
  cbpmfio_map_addresses_to_field(&RDV3_header_specs, 5, addrs);

  addrs[0] = (long)&(p_v3_file_header->core_commstruct_rev);
  cbpmfio_map_addresses_to_field(&RDV3_header_specs, 6, addrs);

  addrs[0] = (long)&(p_v3_file_header->platform_commstruct_rev);
  cbpmfio_map_addresses_to_field(&RDV3_header_specs, 7, addrs);

  addrs[0] = (long)&(p_v3_file_header->bunch_patt_name);
  cbpmfio_map_addresses_to_field(&RDV3_header_specs, 8, addrs);

  addrs[0] = (long)&(p_v3_file_header->bunch_pattern);
  cbpmfio_map_addresses_to_field(&RDV3_header_specs, 9, addrs);

  addrs[0] = (long)&(p_v3_file_header->species_name);
  cbpmfio_map_addresses_to_field(&RDV3_header_specs, 10, addrs);

  addrs[0] = (long)&(p_v3_file_header->num_instruments);
  cbpmfio_map_addresses_to_field(&RDV3_header_specs, 11, addrs);

  addrs[0] = (long)&(p_v3_file_header->num_bunches);
  cbpmfio_map_addresses_to_field(&RDV3_header_specs, 12, addrs);

  addrs[0] = (long)&(p_v3_file_header->num_turns);
  cbpmfio_map_addresses_to_field(&RDV3_header_specs, 13, addrs);

  addrs[0] = (long)&(p_v3_file_header->turn_spacing);
  cbpmfio_map_addresses_to_field(&RDV3_header_specs, 14, addrs);

  addrs[0] = (long)&(p_v3_file_header->timing_setup);
  cbpmfio_map_addresses_to_field(&RDV3_header_specs, 15, addrs);

  addrs[0] = CBPMFIO_NO_ADDRESS;
  cbpmfio_map_addresses_to_field(&RDV3_header_specs, 16, addrs);
  // field-to-address mapping end

  cbpmfio_rw_file_header(fp, CBPMFIO_READ);


  
  
  // Field to address mapping
  addrs[0] = (long)&(p_v3_cesr_header->condx);
  cbpmfio_map_addresses_to_field(&RDV3_cesr_specs, 0, addrs);

  addrs[0] = (long)&(p_v3_cesr_header->raw_current);
  cbpmfio_map_addresses_to_field(&RDV3_cesr_specs, 1, addrs);

  addrs[0] = (long)&(p_v3_cesr_header->mA_current);
  cbpmfio_map_addresses_to_field(&RDV3_cesr_specs, 2, addrs);


  cbpmfio_rw_cesr_header(fp, CBPMFIO_READ);


  
  // Allocate memory for the number of instrument headers needed.
  p_v3_inst_array = malloc(p_v3_file_header->num_instruments * sizeof(RDV3_INST_DATA));


  // Allocate memory for the turn data for each instrument
  int num_words = p_v3_file_header->num_bunches * p_v3_file_header->num_turns;
  int wordcount, bunch, turn;

  for (iidx = 0; iidx < p_v3_file_header->num_instruments; iidx++) {
    
    if (cbpmfio_memory_allocated == CBPMFIO_FALSE) {
      cbpmfio_v3_inst_alloc(iidx);
    }

    // Field to address mapping
    addrs[0] = (long)&(p_v3_inst_array[iidx].location);
    cbpmfio_map_addresses_to_field(&RDV3_inst_header_specs, 0, addrs);
    
    addrs[0] = (long)&(p_v3_inst_array[iidx].hostname);
    cbpmfio_map_addresses_to_field(&RDV3_inst_header_specs, 1, addrs);

    addrs[0] = (long)&(p_v3_inst_array[iidx].IP_address);
    cbpmfio_map_addresses_to_field(&RDV3_inst_header_specs, 2, addrs);
    
    addrs[0] = (long)&(p_v3_inst_array[iidx].detector_type);
    cbpmfio_map_addresses_to_field(&RDV3_inst_header_specs, 3, addrs);
    
    addrs[0] = (long)&(p_v3_inst_array[iidx].horz_coeff);
    addrs[1] = (long)&(p_v3_inst_array[iidx].vert_coeff);
    cbpmfio_map_addresses_to_field(&RDV3_inst_header_specs, 4, addrs);
    
    addrs[0] = (long)&(p_v3_inst_array[iidx].ldr_name);
    cbpmfio_map_addresses_to_field(&RDV3_inst_header_specs, 5, addrs);
    
    addrs[0] = (long)&(p_v3_inst_array[iidx].build_timestamp);
    cbpmfio_map_addresses_to_field(&RDV3_inst_header_specs, 6, addrs);
    
    addrs[0] = (long)&(p_v3_inst_array[iidx].fpga_maj);
    addrs[1] = (long)&(p_v3_inst_array[iidx].fpga_min);
    cbpmfio_map_addresses_to_field(&RDV3_inst_header_specs, 7, addrs);
    
    addrs[0] = (long)&(p_v3_inst_array[iidx].fpga_id[0]);
    addrs[1] = (long)&(p_v3_inst_array[iidx].fpga_id[1]);
    addrs[2] = (long)&(p_v3_inst_array[iidx].fpga_id[2]);
    addrs[3] = (long)&(p_v3_inst_array[iidx].fpga_id[3]);
    cbpmfio_map_addresses_to_field(&RDV3_inst_header_specs, 8, addrs);
    
    addrs[0] = (long)&(p_v3_inst_array[iidx].timing_setup);
    cbpmfio_map_addresses_to_field(&RDV3_inst_header_specs, 9, addrs);
    
    addrs[0] = (long)&(p_v3_inst_array[iidx].num_turns);
    cbpmfio_map_addresses_to_field(&RDV3_inst_header_specs, 10, addrs);
    
    addrs[0] = (long)&(p_v3_inst_array[iidx].turn_counter);
    cbpmfio_map_addresses_to_field(&RDV3_inst_header_specs, 11, addrs);
    
    addrs[0] = (long)&(p_v3_inst_array[iidx].turn_spacing);
    cbpmfio_map_addresses_to_field(&RDV3_inst_header_specs, 12, addrs);
    
    addrs[0] = (long)&(p_v3_inst_array[iidx].trigger);
    cbpmfio_map_addresses_to_field(&RDV3_inst_header_specs, 13, addrs);
    
    addrs[0] = (long)&(p_v3_inst_array[iidx].bp_offsets[0]);
    addrs[1] = (long)&(p_v3_inst_array[iidx].bp_offsets[1]);
    cbpmfio_map_addresses_to_field(&RDV3_inst_header_specs, 14, addrs);
    
    addrs[0] = (long)&(p_v3_inst_array[iidx].ctmd);
    cbpmfio_map_addresses_to_field(&RDV3_inst_header_specs, 15, addrs);
    
    addrs[0] = (long)&(p_v3_inst_array[iidx].btmds[0]);
    addrs[1] = (long)&(p_v3_inst_array[iidx].btmds[1]);
    cbpmfio_map_addresses_to_field(&RDV3_inst_header_specs, 16, addrs);
    
    addrs[0] = (long)&(p_v3_inst_array[iidx].block_delays[0]);
    addrs[1] = (long)&(p_v3_inst_array[iidx].block_delays[1]);
    cbpmfio_map_addresses_to_field(&RDV3_inst_header_specs, 17, addrs);
    
    addrs[0] = (long)&(p_v3_inst_array[iidx].chan_delays[0][0]);
    addrs[1] = (long)&(p_v3_inst_array[iidx].chan_delays[0][1]);
    addrs[2] = (long)&(p_v3_inst_array[iidx].chan_delays[0][2]);
    addrs[3] = (long)&(p_v3_inst_array[iidx].chan_delays[0][3]);
    addrs[4] = (long)&(p_v3_inst_array[iidx].chan_delays[1][0]);
    addrs[5] = (long)&(p_v3_inst_array[iidx].chan_delays[1][1]);
    addrs[6] = (long)&(p_v3_inst_array[iidx].chan_delays[1][2]);
    addrs[7] = (long)&(p_v3_inst_array[iidx].chan_delays[1][3]);
    cbpmfio_map_addresses_to_field(&RDV3_inst_header_specs, 18, addrs);
    
    addrs[0] = (long)&(p_v3_inst_array[iidx].gain_settings[0][0]);
    addrs[1] = (long)&(p_v3_inst_array[iidx].gain_settings[0][1]);
    addrs[2] = (long)&(p_v3_inst_array[iidx].gain_settings[0][2]);
    addrs[3] = (long)&(p_v3_inst_array[iidx].gain_settings[0][3]);
    addrs[4] = (long)&(p_v3_inst_array[iidx].gain_settings[1][0]);
    addrs[5] = (long)&(p_v3_inst_array[iidx].gain_settings[1][1]);
    addrs[6] = (long)&(p_v3_inst_array[iidx].gain_settings[1][2]);
    addrs[7] = (long)&(p_v3_inst_array[iidx].gain_settings[1][3]);
    cbpmfio_map_addresses_to_field(&RDV3_inst_header_specs, 19, addrs);
    
    addrs[0] = (long)&(p_v3_inst_array[iidx].gain_codes[0][0]);
    addrs[1] = (long)&(p_v3_inst_array[iidx].gain_codes[0][1]);
    addrs[2] = (long)&(p_v3_inst_array[iidx].gain_codes[0][2]);
    addrs[3] = (long)&(p_v3_inst_array[iidx].gain_codes[0][3]);
    addrs[4] = (long)&(p_v3_inst_array[iidx].gain_codes[1][0]);
    addrs[5] = (long)&(p_v3_inst_array[iidx].gain_codes[1][1]);
    addrs[6] = (long)&(p_v3_inst_array[iidx].gain_codes[1][2]);
    addrs[7] = (long)&(p_v3_inst_array[iidx].gain_codes[1][3]);
    cbpmfio_map_addresses_to_field(&RDV3_inst_header_specs, 20, addrs);
    
    addrs[0] = (long)&(p_v3_inst_array[iidx].gain_coeffs[0][0]);
    addrs[1] = (long)&(p_v3_inst_array[iidx].gain_coeffs[0][1]);
    addrs[2] = (long)&(p_v3_inst_array[iidx].gain_coeffs[0][2]);
    addrs[3] = (long)&(p_v3_inst_array[iidx].gain_coeffs[0][3]);
    addrs[4] = (long)&(p_v3_inst_array[iidx].gain_coeffs[1][0]);
    addrs[5] = (long)&(p_v3_inst_array[iidx].gain_coeffs[1][1]);
    addrs[6] = (long)&(p_v3_inst_array[iidx].gain_coeffs[1][2]);
    addrs[7] = (long)&(p_v3_inst_array[iidx].gain_coeffs[1][3]);
    cbpmfio_map_addresses_to_field(&RDV3_inst_header_specs, 21, addrs);
    
    addrs[0] = (long)&(p_v3_inst_array[iidx].pedestals[0][0]);
    addrs[1] = (long)&(p_v3_inst_array[iidx].pedestals[0][1]);
    addrs[2] = (long)&(p_v3_inst_array[iidx].pedestals[0][2]);
    addrs[3] = (long)&(p_v3_inst_array[iidx].pedestals[0][3]);
    addrs[4] = (long)&(p_v3_inst_array[iidx].pedestals[1][0]);
    addrs[5] = (long)&(p_v3_inst_array[iidx].pedestals[1][1]);
    addrs[6] = (long)&(p_v3_inst_array[iidx].pedestals[1][2]);
    addrs[7] = (long)&(p_v3_inst_array[iidx].pedestals[1][3]);
    cbpmfio_map_addresses_to_field(&RDV3_inst_header_specs, 22, addrs);
    
    addrs[0] = (long)&(p_v3_inst_array[iidx].dig_temp_c);
    cbpmfio_map_addresses_to_field(&RDV3_inst_header_specs, 23, addrs);
    
    addrs[0] = (long)&(p_v3_inst_array[iidx].card_temps_c[0]);
    addrs[1] = (long)&(p_v3_inst_array[iidx].card_temps_c[1]);
    addrs[2] = (long)&(p_v3_inst_array[iidx].card_temps_c[2]);
    addrs[3] = (long)&(p_v3_inst_array[iidx].card_temps_c[3]);
    cbpmfio_map_addresses_to_field(&RDV3_inst_header_specs, 24, addrs);
    
    addrs[0] = (long)&(p_v3_inst_array[iidx].adc_saturation[0][0]);
    addrs[1] = (long)&(p_v3_inst_array[iidx].adc_saturation[1][0]);
    cbpmfio_map_addresses_to_field(&RDV3_inst_header_specs, 25, addrs);

    addrs[0] = (long)&(p_v3_inst_array[iidx].adc_high[0][0]);
    addrs[1] = (long)&(p_v3_inst_array[iidx].adc_high[1][0]);
    cbpmfio_map_addresses_to_field(&RDV3_inst_header_specs, 26, addrs);

    addrs[0] = (long)&(p_v3_inst_array[iidx].adc_low[0][0]);
    addrs[1] = (long)&(p_v3_inst_array[iidx].adc_low[1][0]);
    cbpmfio_map_addresses_to_field(&RDV3_inst_header_specs, 27, addrs);
    // End field mapping

    cbpmfio_rw_instrument_header(fp, CBPMFIO_READ);



    // First call to read a turn data line simply scans through
    // the file to find the data block start indicator.
    // Subsequent calls, in the loop below, actually harvest
    // the data.
    int tblock, timing_block, phase_word, TI, BI, BO, TO;
    addrs[0] = (long)&(tblock);
    addrs[1] = (long)&(phase_word);
    addrs[2] = (long)&(TI);
    addrs[3] = (long)&(BI);
    addrs[4] = (long)&(BO);
    addrs[5] = (long)&(TO);
    cbpmfio_map_addresses_to_field(&RDV3_raw_data_spec, 0, addrs);
    cbpmfio_rw_file_section(fp, CBPMFIO_READ, 1, (CBPMFIO_FIELD_SPEC*)&RDV3_raw_data_spec);

    float geometric_coeffs[2];
    wordcount = 0;
    for (bunch = 0; bunch < p_v3_file_header->num_bunches; bunch++) {
      for (turn = 0; turn < p_v3_file_header->num_turns; turn++) {
	addrs[0] = (long)&(timing_block);
	addrs[1] = (long)&(phase_word);
	addrs[2] = (long)&(TI);
	addrs[3] = (long)&(BI);
	addrs[4] = (long)&(BO);
	addrs[5] = (long)&(TO);
	cbpmfio_map_addresses_to_field(&RDV3_raw_data_spec, 0, addrs);
	cbpmfio_rw_file_section(fp, CBPMFIO_READ, 1, (CBPMFIO_FIELD_SPEC*)&RDV3_raw_data_spec);

	p_v3_inst_array[iidx].timing_blocks[bunch] = timing_block;
	p_v3_inst_array[iidx].phase_words[wordcount] = phase_word;
	p_v3_inst_array[iidx].TIraw[wordcount] = TI;
	p_v3_inst_array[iidx].BIraw[wordcount] = BI;
	p_v3_inst_array[iidx].BOraw[wordcount] = BO;
	p_v3_inst_array[iidx].TOraw[wordcount] = TO;

	// Apply pedestal subtraction and gain scaling.
	tblock = p_v3_inst_array[iidx].timing_blocks[bunch];

	p_v3_inst_array[iidx].TIcorrected[wordcount] =
	  p_v3_inst_array[iidx].TIraw[wordcount] -
	  p_v3_inst_array[iidx].pedestals[tblock][0];

	p_v3_inst_array[iidx].TIcorrected[wordcount] *=
	  (1.0 / p_v3_inst_array[iidx].gain_coeffs[tblock][0]);
	
	p_v3_inst_array[iidx].BIcorrected[wordcount] =
	  p_v3_inst_array[iidx].BIraw[wordcount] -
	  p_v3_inst_array[iidx].pedestals[tblock][1];
	p_v3_inst_array[iidx].BIcorrected[wordcount] *=
	  (1.0 / p_v3_inst_array[iidx].gain_coeffs[tblock][1]);

	p_v3_inst_array[iidx].BOcorrected[wordcount] =
	  p_v3_inst_array[iidx].BOraw[wordcount] -
	  p_v3_inst_array[iidx].pedestals[tblock][2];
	p_v3_inst_array[iidx].BOcorrected[wordcount] *=
	  (1.0 / p_v3_inst_array[iidx].gain_coeffs[tblock][2]);

	p_v3_inst_array[iidx].TOcorrected[wordcount] =
	  p_v3_inst_array[iidx].TOraw[wordcount] -
	  p_v3_inst_array[iidx].pedestals[tblock][3];
	p_v3_inst_array[iidx].TOcorrected[wordcount] *=
	  (1.0 / p_v3_inst_array[iidx].gain_coeffs[tblock][3]);

	geometric_coeffs[0] = p_v3_inst_array[iidx].horz_coeff;
	geometric_coeffs[1] = p_v3_inst_array[iidx].vert_coeff;

	p_v3_inst_array[iidx].Xpos[wordcount] =
	  cbpmfio_compute_pos(0,
			      geometric_coeffs,
			      p_v3_inst_array[iidx].TIcorrected[wordcount],
			      p_v3_inst_array[iidx].BIcorrected[wordcount],
			      p_v3_inst_array[iidx].BOcorrected[wordcount],
			      p_v3_inst_array[iidx].TOcorrected[wordcount]);

	p_v3_inst_array[iidx].Ypos[wordcount] =
	  cbpmfio_compute_pos(1,
			      geometric_coeffs,
			      p_v3_inst_array[iidx].TIcorrected[wordcount],
			      p_v3_inst_array[iidx].BIcorrected[wordcount],
			      p_v3_inst_array[iidx].BOcorrected[wordcount],
			      p_v3_inst_array[iidx].TOcorrected[wordcount]);

	// Extract shaker drive amplitude words for each plane from raw data stream.
	p_v3_inst_array[iidx].X_phase_words[wordcount] =
	  (p_v3_inst_array[iidx].phase_words[wordcount] >> 19) & 0x000001FF;
	p_v3_inst_array[iidx].Y_phase_words[wordcount] =
	  (p_v3_inst_array[iidx].phase_words[wordcount] >> 10) & 0x000001FF;


	wordcount++;
      }
    }
  }

  cbpmfio_memory_allocated = CBPMFIO_TRUE;
 
  fclose(fp);

  return CBPMFIO_SUCCESS;

}
