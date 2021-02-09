//
// cbpmfio_constants.h
//

#ifndef CBPMFIO_CONSTANTS_H
#define CBPMFIO_CONSTANTS_H

#include "cbpmfio_f_constants.h"

#define CBPMFIO_ONLINE_RAW_DATA_DIR   "/nfs/cesr/online/instr/data/cbpmII/raw/"
#define CBPMFIO_OFFLINE_RAW_DATA_DIR  "/nfs/cesr/offline/instr/data/cbpmII/raw/"

#define CBPMFIO_TRUE   1
#define CBPMFIO_FALSE  0

#define CBPMFIO_MAX_FORMAT_LENGTH   2048
#define CBPMFIO_MAX_FILE_LINE_LENGTH   2048
#define CBPMFIO_DATA_BLOCK_START   "--BEGIN DATA--\n"
#define CBPMFIO_MAX_FORMAT_TOKEN_LENGTH   10
#define CBPMFIO_ONLINE_RAW_DATA_DIR   "/nfs/cesr/online/instr/data/cbpmII/raw/"
#define CBPMFIO_OFFLINE_RAW_DATA_DIR  "/nfs/cesr/offline/instr/data/cbpmII/raw/"
#define CBPMFIO_NO_ADDRESS   1
#define CBPMFIO_FILES_PER_DIR   1000

  
enum CBPMFIO_MODES {
  CBPMFIO_READ,
  CBPMFIO_WRITE,
  CBPMFIO_READWRITE
};

#define CBPMFIO_MAX_FIELD_ADDRESSES   10

#endif
