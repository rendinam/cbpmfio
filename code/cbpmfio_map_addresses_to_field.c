//
// cbpmfio_map_addresses_to_field.c
//

#include "cbpmfio.h"

int cbpmfio_map_addresses_to_field(CBPMFIO_FIELD_SPEC *specs, int ID, fio_addrs addrs) {

  int addr;
  for (addr = 0; addr < CBPMFIO_MAX_FIELD_ADDRESSES; addr++) {
    specs[ID].addresses[addr] = addrs[addr];
  }

  return CBPMFIO_SUCCESS;
}
