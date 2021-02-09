//
// cbpmfio_rw_file_section.c
//

#include "cbpmfio.h"

int cbpmfio_rw_file_section(FILE *fp, int mode, int num_specs, CBPMFIO_FIELD_SPEC *specs) {

  int sidx;
  int (*p_IO)()  = NULL;

  int addr, addrcount;
  for (sidx = 0; sidx < num_specs; sidx++) {

    // Set function pointers based on mapping entry
    if (mode == CBPMFIO_READ) {
      p_IO = (void*)(specs[sidx].input_func);
    } else { // CBPMFIO_WRITE
      p_IO = (void*)(specs[sidx].output_func);
    }

    // Calculate the number of address entries that exist, use this
    // value to choose the appropriate function call.
    addrcount = 0;
    //printf("format = %s\n", specs[sidx].format);
    for (addr = 0; addr < CBPMFIO_MAX_FIELD_ADDRESSES; addr++) {
      if (specs[sidx].addresses[addr] != (long)NULL) {
	addrcount++;
	//printf("addrcount = %d;  addr = %d\n\n", 
	//      addrcount, 
	//     specs[sidx].addresses[addr]);
      }
    }
    //printf("\n");
    switch (addrcount) {
      
    case 1:
      (*p_IO) (fp,
	       specs[sidx].format,
	       specs[sidx].addresses[0],
	       NULL);
      break;

    case 2:
      (*p_IO) (fp,
	       specs[sidx].format,
	       specs[sidx].addresses[0],
	       specs[sidx].addresses[1],
	       NULL);
      break;

    case 3:
      (*p_IO) (fp,
	       specs[sidx].format,
	       specs[sidx].addresses[0],
	       specs[sidx].addresses[1],
	       specs[sidx].addresses[2],
	       NULL);
      break;

    case 4:
      (*p_IO) (fp,
	       specs[sidx].format,
	       specs[sidx].addresses[0],
	       specs[sidx].addresses[1],
	       specs[sidx].addresses[2],
	       specs[sidx].addresses[3],
	       NULL);
      break;

    case 5:
      (*p_IO) (fp,
	       specs[sidx].format,
	       specs[sidx].addresses[0],
	       specs[sidx].addresses[1],
	       specs[sidx].addresses[2],
	       specs[sidx].addresses[3],
	       specs[sidx].addresses[4],
	       NULL);
      break;

    case 6:
      (*p_IO) (fp,
	       specs[sidx].format,
	       specs[sidx].addresses[0],
	       specs[sidx].addresses[1],
	       specs[sidx].addresses[2],
	       specs[sidx].addresses[3],
	       specs[sidx].addresses[4],
	       specs[sidx].addresses[5],
	       NULL);
      break;

    case 7:
      (*p_IO) (fp,
	       specs[sidx].format,
	       specs[sidx].addresses[0],
	       specs[sidx].addresses[1],
	       specs[sidx].addresses[2],
	       specs[sidx].addresses[3],
	       specs[sidx].addresses[4],
	       specs[sidx].addresses[5],
	       specs[sidx].addresses[6],
	       NULL);
      break;

    case 8:
      (*p_IO) (fp,
	       specs[sidx].format,
	       specs[sidx].addresses[0],
	       specs[sidx].addresses[1],
	       specs[sidx].addresses[2],
	       specs[sidx].addresses[3],
	       specs[sidx].addresses[4],
	       specs[sidx].addresses[5],
	       specs[sidx].addresses[6],
	       specs[sidx].addresses[7],
	       NULL);
      break;

    case 9:
      (*p_IO) (fp,
	       specs[sidx].format,
	       specs[sidx].addresses[0],
	       specs[sidx].addresses[1],
	       specs[sidx].addresses[2],
	       specs[sidx].addresses[3],
	       specs[sidx].addresses[4],
	       specs[sidx].addresses[5],
	       specs[sidx].addresses[6],
	       specs[sidx].addresses[7],
	       specs[sidx].addresses[8],
	       NULL);
      break;

    case 10:
      (*p_IO) (fp,
	       specs[sidx].format,
	       specs[sidx].addresses[0],
	       specs[sidx].addresses[1],
	       specs[sidx].addresses[2],
	       specs[sidx].addresses[3],
	       specs[sidx].addresses[4],
	       specs[sidx].addresses[5],
	       specs[sidx].addresses[6],
	       specs[sidx].addresses[7],
	       specs[sidx].addresses[8],
	       specs[sidx].addresses[9],
	       NULL);
      break;

    }

  } //end for(sidx)

  return CBPMFIO_SUCCESS;

}
