//
// cbpmfio_utils.c
//

#include "cbpmfio.h"


// Provide the string reflecting the measurement timestamp.
// This string has a maxmimum length of CBI_MAX_STRING_LENGTH.
int cbpm_rawfile_timestamp_(char *timestamp) {

  strcpy( timestamp, (*p_v3_file_header).timestamp );

  return CBPMFIO_SUCCESS;

}


// Provide the number of turns for the measurement found in the file.
int cbpm_rawfile_num_instruments(void) {
  return p_v3_file_header->num_instruments;
}


// Provide the number of bunches for the measurement found in the file.
int cbpm_rawfile_num_bunches(void) {
  return (*p_v3_file_header).num_bunches;
}


// Provide the number of turns for the measurement found in the file.
int cbpm_rawfile_num_turns(void) {
  return (*p_v3_file_header).num_turns;
}


// Returns the value of the CESR CONDX number obtained from the
// CESR databse when a data file is written.
int cbpm_rawfile_condx_number(void) {
  return p_v3_cesr_header->condx;
}


// Returns a floating point value representing the CESR CERN total
// current measurement stored when the BPM measurement was taken.
float cbpm_rawfile_cern_current(void) {
  return p_v3_cesr_header->mA_current;
}



// Provide a single instrument name/location identifier string from the
// given data file each time this function is called until there are no
// more left to retrieve in the file.  At that point, this function
// will place an empty string in name.
int cbpm_rawfile_inst_names_(char *name) {

  int iidx;

  for (iidx = inst_count_g; iidx <= p_v3_file_header->num_instruments; iidx++) {

    if (iidx == inst_count_g) {
    
      if (iidx == p_v3_file_header->num_instruments) {
	inst_count_g = 0;
	strcpy( name, "\0" );
	return CBPMFIO_FAILURE;
      } else {
	inst_count_g++;
	strcpy( name, p_v3_inst_array[iidx].location );
	return CBPMFIO_SUCCESS;
      }

    }
    
  } //endFOR
  return CBPMFIO_FAILURE;

}



// Returns the CESR RF bucket number for the bunch index provided.
// Automatically takes into account the mapping of the bunch indexes
// for the timing setup the instruments were in when the measurement
// was performed.
//
// bunch index argument starts at 1.
// RF buckets are indexed here starting from 1.
// If bunch index is out of range for the timing setup found, return -1.
int cbpm_rawfile_rf_bucket(int *bunch) {

  int retval = -1;

  // 4ns timing setups
  if (p_v3_file_header->timing_setup[0] == '4') {
    if (*bunch > 640) {
      retval = -1;
    }
    retval = *bunch * 2;
  }

  // 14ns timing setups
  if (p_v3_file_header->timing_setup[0] == '1') {
    if (*bunch > 183) {
      retval = -1;
    }
    retval = (((*bunch-1)*14) / 2) + 1;
  }

  return retval;

}



// Return pedestal value for a given instrument, bunch, and button.
float cbpm_rawfile_pedestal( char *inst_location, int *bunch, int *button ) {
  
  // Necessary for making a proper comparison between the string passed
  // in from Fortran (potentially with padding spaces) and the C string.
  cbpmfio_strip(inst_location);

  int iidx;
  int array_idx = (*bunch)-1;
  float retval = 0.0;
  int tblock;
  
  for (iidx = 0; iidx <  p_v3_file_header->num_instruments; iidx++) {
    if (strcmp( inst_location, p_v3_inst_array[iidx].location) == 0 ) { 
      
      tblock = p_v3_inst_array[iidx].timing_blocks[array_idx]; 	
      retval = p_v3_inst_array[iidx].pedestals[tblock][*button];
      return retval;
      
    } //endIF
  } //endFOR
  return CBPMFIO_FAILURE;
}


// Return gain scale factor for a given instrument, bunch, and button.
float cbpm_rawfile_gain_factor( char *inst_location, int *bunch, int *button ) {

  // Necessary for making a proper comparison between the string passed
  // in from Fortran (potentially with padding spaces) and the C string.
  cbpmfio_strip(inst_location);

  int iidx, tblock;
  int array_idx = (*bunch)-1;
  float retval;
    
  for (iidx = 0; iidx <  p_v3_file_header->num_instruments; iidx++) {
    if (strcmp( inst_location, p_v3_inst_array[iidx].location) == 0 ) { 

      tblock = p_v3_inst_array[iidx].timing_blocks[array_idx]; 	
      retval = p_v3_inst_array[iidx].gain_coeffs[tblock][*button];
      return retval;

    } //endIF
  } //endFOR
  return CBPMFIO_FAILURE;
}



// Provide a pointer to the raw ADC value buffers for a given instrument and button.
int *cbpm_rawfile_raw_ptr(char *inst_location, int *button) {

  // Necessary for making a proper comparison between the string passed
  // in from Fortran (potentially with padding spaces) and the C string.
  cbpmfio_strip(inst_location);

  int  iidx;

  for (iidx = 0; iidx <  p_v3_file_header->num_instruments; iidx++) {
    if (strcmp( inst_location, p_v3_inst_array[iidx].location) == 0 ) {

      switch (*button) {
      case 0:
	return (int *)p_v3_inst_array[iidx].TIraw;
	break;
      case 1:
	return (int *)p_v3_inst_array[iidx].BIraw;
	break;
      case 2:
	return (int *)p_v3_inst_array[iidx].BOraw;
	break;
      case 3:
	return (int *)p_v3_inst_array[iidx].TOraw;
	break;
      default:
	return NULL;
	break;
      }

    } //endIF strcmp

  } //endFOR iidx

  // Instrument not found.
  return NULL;

}



// Provide a pointer to the scaled data buffers for the given instrument and button.
float *cbpm_rawfile_tbt_ptr(char *inst_location, int *button) {

  // Necessary for making a proper comparison between the string passed
  // in from Fortran (potentially with padding spaces) and the C string.
  cbpmfio_strip(inst_location);

  int  iidx;

  for (iidx = 0; iidx <  p_v3_file_header->num_instruments; iidx++) {
    if (strcmp( inst_location, p_v3_inst_array[iidx].location) == 0 ) {

      switch (*button) {
      case 0:
	return (float *)p_v3_inst_array[iidx].TIcorrected;
	break;
      case 1:
	return (float *)p_v3_inst_array[iidx].BIcorrected;
	break;
      case 2:
	return (float *)p_v3_inst_array[iidx].BOcorrected;
	break;
      case 3:
	return (float *)p_v3_inst_array[iidx].TOcorrected;
	break;
      default:
	return NULL;
	break;
      }

    } //endIF strcmp

  } //endFOR iidx

  return NULL;

}


float cbpmfio_compute_pos(int plane, float coeffs[], float TI, float BI, float BO, float TO) {

  float Xcoeff, Ycoeff, Xnum, Ynum, Xpos, Ypos, sum;
  
  Xcoeff = coeffs[0];
  Ycoeff = coeffs[1];

  sum  = TI + BI + BO + TO;
  Xnum = TO + BO - BI - TI;
  Ynum = TO - BO - BI + TI;

  if (plane == 0) {
    Xpos = Xcoeff * (Xnum/sum);
    return Xpos;
  } else {
    Ypos = Ycoeff * (Ynum/sum);
    return Ypos;
  }


}


// Provide a pointer to the calculated position buffer for the given plane.
float* cbpm_rawfile_pos_ptr(char *inst_location, int *plane) {

  // Necessary for making a proper comparison between the string passed
  // in from Fortran (potentially with padding spaces) and the C string.
  cbpmfio_strip(inst_location);

  int  iidx;

  for (iidx = 0; iidx <  p_v3_file_header->num_instruments; iidx++) {
    if (strcmp( inst_location, p_v3_inst_array[iidx].location) == 0 ) {

      switch (*plane) {
      case 0:
	return (float *)p_v3_inst_array[iidx].Xpos;
	break;
      case 1:
	return (float *)p_v3_inst_array[iidx].Ypos;
	break;
      default:
	return NULL;
	break;
      }

    } //endIF strcmp

  } //endFOR iidx
  
  // Instrument not found.
  return NULL;

}


// Provide a pointer to the phase word buffers for the given instrument and button.
int *cbpm_rawfile_phase_ptr(char *inst_location, int *plane) {

  // Necessary for making a proper comparison between the string passed
  // in from Fortran (potentially with padding spaces) and the C string.
  cbpmfio_strip(inst_location);

  int  iidx;

  for (iidx = 0; iidx <  p_v3_file_header->num_instruments; iidx++) {
    if (strcmp( inst_location, p_v3_inst_array[iidx].location) == 0 ) {

      switch (*plane) {
      case 0:
	return (int *)p_v3_inst_array[iidx].X_phase_words;
	break;
      case 1:
	return (int *)p_v3_inst_array[iidx].Y_phase_words;
	break;
      default:
	return NULL;
	break;
      }

    } //endIF strcmp

  } //endFOR iidx
  
  // Instrument not found.
  return NULL;

}



