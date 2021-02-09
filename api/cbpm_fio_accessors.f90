#include "cbpmfio_f_constants.h"

module cbpm_file_input

use,intrinsic :: iso_c_binding

interface
   function cbpm_read_rawfile_f(file_idx) result (val) bind(c,name='cbpm_read_rawfile')
     Integer file_idx
     Integer val
   end function cbpm_read_rawfile_f
end interface

interface
   function cbpm_rawfile_num_instruments_f() result (val) bind(c,name='cbpm_rawfile_num_instruments')
     Integer val
   end function cbpm_rawfile_num_instruments_f
end interface

interface
   function cbpm_rawfile_num_bunches_f() result (val) bind(c,name='cbpm_rawfile_num_bunches')
     Integer val
   end function cbpm_rawfile_num_bunches_f
end interface

interface
   function cbpm_rawfile_num_turns_f() result (val) bind(c,name='cbpm_rawfile_num_turns')
     Integer val
   end function cbpm_rawfile_num_turns_f
end interface

interface
   function cbpm_rawfile_condx_number_f() result (val) bind(c,name='cbpm_rawfile_condx_number')
     Integer val
   end function cbpm_rawfile_condx_number_f
end interface

interface
   function cbpm_rawfile_cern_current_f() result (val) bind(c,name='cbpm_rawfile_cern_current')
     Integer val
   end function cbpm_rawfile_cern_current_f
end interface



interface
   function cbpm_rawfile_rf_bucket_f(bunch) result (val) bind(c,name='cbpm_rawfile_rf_bucket')
     Integer bunch
     Integer val
   end function cbpm_rawfile_rf_bucket_f
end interface




contains


!--------------------------
  Function cbpm_rawfile_timestamp_f( timestamp ) result (val)

  Implicit None

  Integer val
  Integer i
  Integer, external ::  cbpm_rawfile_timestamp

  Character(*) timestamp
  Character(CBPMFIO_MAX_STRING_LENGTH) temptimestamp

  val = cbpm_rawfile_timestamp( temptimestamp )


  ! Strip off the null character before passing the string back.
  do i = 1, CBPMFIO_MAX_STRING_LENGTH
     if ( ichar(temptimestamp(i:i)) == 0) then
        timestamp = temptimestamp(1:i-1)
        exit
     end if
  end do

end Function cbpm_rawfile_timestamp_f



Function cbpm_rawfile_inst_names_f( name ) result (val)
  
  Implicit None
  
  Integer val
  Integer ccount
  Integer, external :: cbpm_rawfile_inst_names
  
  Character(*) name
  Character(CBPMFIO_MAX_STRING_LENGTH) tempname

  val = cbpm_rawfile_inst_names( tempname )

  ! Strip off the null character before passing the string back.
  do ccount = 1, CBPMFIO_MAX_STRING_LENGTH
     if ( ichar(tempname(ccount:ccount)) == 0) then
        name = tempname(1:ccount-1)
        exit
     end if
  end do
  
end Function cbpm_rawfile_inst_names_f



!!--------------------------------------------------------------------------
!! Intermediate layer definitions to access data buffers follow
!!--------------------------------------------------------------------------

function cbpm_rawfile_pedestal_f(inst_location, bunch, button) result (val)

  Implicit None
  character(*) inst_location
  Integer bunch, button
  Real val

  interface
     function cbpm_rawfile_pedestal(inst_location, bunch, button) result (val) bind(c)
       import c_char
       Character(c_char) inst_location(*)
       Integer bunch, button
       Real val
     end function cbpm_rawfile_pedestal
  end interface
  
  val = cbpm_rawfile_pedestal(trim(inst_location)//C_NULL_CHAR, bunch, button)
  
end function cbpm_rawfile_pedestal_f




function cbpm_rawfile_gain_factor_f(inst_location, bunch, button) result (val)

  Implicit None
  character(*) inst_location
  Integer bunch, button
  Real val

  interface
     function cbpm_rawfile_gain_factor(inst_location, bunch, button) result (val) bind(c)
       import c_char
       Character(c_char) inst_location(*)
       Integer bunch, button
       Real val
     end function cbpm_rawfile_gain_factor
  end interface
  
  val = cbpm_rawfile_gain_factor(trim(inst_location)//C_NULL_CHAR, bunch, button)
  
end function cbpm_rawfile_gain_factor_f
  



function cbpm_rawfile_raw_ptr_f(inst_location, button) result (dptr)
  
  Implicit None
  Integer, Pointer :: dptr(:)
  Type (c_ptr) c_pointer
  character(*) inst_location
  Integer button, num_bunches, num_turns

  interface
     function cbpm_rawfile_raw_ptr(inst_location, button) result (c_pointer) bind(c)
       import c_ptr, c_char
       Character(c_char) inst_location(*)
       Integer button
       type (c_ptr) :: c_pointer
     end function cbpm_rawfile_raw_ptr
  end interface

  c_pointer = cbpm_rawfile_raw_ptr(trim(inst_location)//C_NULL_CHAR, button)
  num_bunches = cbpm_rawfile_num_bunches_f()
  num_turns = cbpm_rawfile_num_turns_f()
  call c_f_pointer(c_pointer, dptr, [num_bunches*num_turns])

end function cbpm_rawfile_raw_ptr_f




function cbpm_rawfile_tbt_ptr_f(inst_location, button) result (dptr)

  Implicit None
  Real*4, Pointer :: dptr(:)
  Type (c_ptr) c_pointer
  character(*) inst_location
  Integer button, num_bunches, num_turns

  interface
     function cbpm_rawfile_tbt_ptr(inst_location, button) result (c_pointer) bind(c)
       import c_ptr, c_char
       Character(c_char) inst_location(*)
       Integer button
       type (c_ptr) :: c_pointer
     end function cbpm_rawfile_tbt_ptr
  end interface
  
  c_pointer = cbpm_rawfile_tbt_ptr(trim(inst_location)//C_NULL_CHAR, button)
  num_bunches = cbpm_rawfile_num_bunches_f()
  num_turns = cbpm_rawfile_num_turns_f()

  call c_f_pointer(c_pointer, dptr, [num_bunches*num_turns])

end function cbpm_rawfile_tbt_ptr_f




function cbpm_rawfile_pos_ptr_f(inst_location, plane) result (dptr)

  Implicit None
  Real*4, Pointer :: dptr(:)
  Type (c_ptr) c_pointer
  character(*) inst_location
  Integer plane, num_bunches, num_turns

  interface
     function cbpm_rawfile_pos_ptr(inst_location, plane) result (c_pointer) bind(c)
       import c_ptr, c_char
       Character(c_char) inst_location(*)
       Integer plane
       type (c_ptr) :: c_pointer
     end function cbpm_rawfile_pos_ptr
  end interface

  c_pointer = cbpm_rawfile_pos_ptr(trim(inst_location)//C_NULL_CHAR, plane)
  num_bunches = cbpm_rawfile_num_bunches_f()
  num_turns = cbpm_rawfile_num_turns_f()
  call c_f_pointer(c_pointer, dptr, [num_bunches*num_turns])

end function cbpm_rawfile_pos_ptr_f




function cbpm_rawfile_phase_ptr_f(inst_location, plane) result (dptr)
  
  Implicit None
  Integer, Pointer :: dptr(:)
  Type (c_ptr) c_pointer
  character(*) inst_location
  Integer plane, num_turns

  interface
     function cbpm_rawfile_phase_ptr(inst_location, plane) result (c_pointer) bind(c)
       import c_ptr, c_char
       Character(c_char) inst_location(*)
       Integer plane
       type (c_ptr) :: c_pointer
     end function cbpm_rawfile_phase_ptr
  end interface

  c_pointer = cbpm_rawfile_phase_ptr(trim(inst_location)//C_NULL_CHAR, plane)
  num_turns = cbpm_rawfile_num_turns_f()
  call c_f_pointer(c_pointer, dptr, [num_turns])

end function cbpm_rawfile_phase_ptr_f



end module cbpm_file_input
