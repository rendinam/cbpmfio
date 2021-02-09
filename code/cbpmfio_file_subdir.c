//
// cbpmfio_file_subdir.c
//

#include "cbpmfio.h"

int cbpmfio_file_subdir( int file_idx, char *subdir_string ) {
  
  int subdir_val;

  // Determine target directory number
  subdir_val = file_idx / CBPMFIO_FILES_PER_DIR;

  if (subdir_val < 100) {
    sprintf( subdir_string, "%02d/", subdir_val );
  } else {
    sprintf( subdir_string, "%03d/", subdir_val );
  }
  sprintf( subdir_string, "%02d/", subdir_val );
  
  return CBPMFIO_SUCCESS;

}
