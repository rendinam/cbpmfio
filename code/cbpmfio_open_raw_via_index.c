//
// cbpmfio_open_raw_via_index.c
//

#include "cbpmfio.h"

FILE *fio_open_raw_via_index( int file_idx ) {

  char *func_name = (char *)__FUNCTION__;
  char full_filename[150] = "";
  char temp_name[50];
  
  // Determine which CESR OFFLINE data directory holds the
  // RAW data file with the index provided.
  char subdir_string[6] = "";
  strcpy( full_filename, CBPMFIO_ONLINE_RAW_DATA_DIR );
  cbpmfio_file_subdir( file_idx, subdir_string );
  strcat( full_filename, subdir_string );
  sprintf( temp_name, "RD-%06d.dat", file_idx );
  strcat( full_filename, temp_name );

  struct stat buffer;
  if ( stat(full_filename, &buffer) != 0) {
    printf("Unable to stat %s\n", full_filename );
    
    strcpy( full_filename, CBPMFIO_OFFLINE_RAW_DATA_DIR );
    strcat( full_filename, subdir_string );
    strcat( full_filename, temp_name );

    if ( stat(full_filename, &buffer) != 0) {
      printf("Unable to stat %s\n", full_filename );
      return NULL;
    } 
  }

  FILE *fp;
  fp = fopen(full_filename, "r");
  if (fp == NULL) {
    printf("[%s] ERROR opening data file %s!\n", func_name, full_filename);
    perror(func_name);
    return NULL;
  }

  return fp;

}
