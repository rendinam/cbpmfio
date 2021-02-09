!
! Test program for calling a C function wrapped in a Fortran function for
! reading a raw data file (RD-V3 or later).
!
#include "cbpmfio_f_constants.h"


PROGRAM cbpmfio_test_f

  use cbpm_file_input

  type (c_ptr) c_pointer

  integer, pointer :: raw_array0(:)
  integer, pointer :: raw_array1(:)
  integer, pointer :: raw_array2(:)
  integer, pointer :: raw_array3(:)

  Integer retval, num_bunches, num_turns, bunch, inst, val, condx_number
  Real fretval0, fretval1, fretval2, fretval3
  Real*4 cern_curr
  
  ! Filename must be NULL terminated before being passed to cbpm_read_rawfile_f!
  !Character*(60) :: filename = "/nfs/cesr/online/instr/data/cbpmII/raw/04/RD-004080.dat"//CHAR(0)
  
  Character*(40) :: timestamp
  Character*(6)  :: inst_name
  
  Real*4, pointer :: tbt_array0(:)
  Real*4, pointer :: tbt_array1(:)
  Real*4, pointer :: tbt_array2(:)
  Real*4, pointer :: tbt_array3(:)
  
  Real*4, pointer :: pos_array_h(:)
  Real*4, pointer :: pos_array_v(:)
  
  Integer, pointer ::  phase_array_h(:)
  Integer, pointer ::  phase_array_v(:)
  
  Integer num_instruments
  Integer zero
  Integer one
  Integer two
  Integer three
  Integer file_idx
  Integer num_words
  Integer rf_bucket
  
  bunch = 1
  zero = 0
  one = 1
  two = 2
  three = 3

  !! Disable the above clause and enable this one instead for
  !! access by full path name of file.
  !!retval = cbpm_read_rawfile_by_name_f( filename )
  !!print *,"cbpm_read_rawfile_by_name_f returned: ",retval

  ! Read data from file, specified by file index number.
  print *,"F I R S T    F I L E"
  file_idx = 4080
  retval = cbpm_read_rawfile_f( file_idx )
  print *,"cbpm_read_rawfile returned: ",retval
  
  ! Get key numerical values
  retval = cbpm_rawfile_timestamp_f(timestamp)

  num_instruments = cbpm_rawfile_num_instruments_f()
  num_bunches = cbpm_rawfile_num_bunches_f()
  num_turns = cbpm_rawfile_num_turns_f()
  condx_number = cbpm_rawfile_condx_number_f()
  cern_curr = cbpm_rawfile_cern_current_f()

  print *,"File ID     : ", file_idx
  print *,"TIMESTAMP   = ", timestamp
  print *,"NUM_INSTS   = ", num_instruments
  print *,"NUM BUNCHES = ", num_bunches
  print *,"NUM TURNS   = ", num_turns
  print *,"CONDX #     = ", condx_number
  print *,"CERN CURR   = ", cern_curr    
  print *,""
  print *,""
  
  num_words = num_bunches * num_turns
  inst_name = "."

  do while (inst_name(1:1) .NE. " ")
 
     retval = cbpm_rawfile_inst_names_f(inst_name)
     if (inst_name .EQ. " ") exit
     print *,"Location: ",inst_name
     
     rf_bucket = cbpm_rawfile_rf_bucket_f(three)
     print *,"RF bucket      ", rf_bucket


     fretval0 = cbpm_rawfile_pedestal_f(inst_name, bunch, zero)
     fretval1 = cbpm_rawfile_pedestal_f(inst_name, bunch, one)
     fretval2 = cbpm_rawfile_pedestal_f(inst_name, bunch, two)
     fretval3 = cbpm_rawfile_pedestal_f(inst_name, bunch, three)
     print *,"PEDS            ", fretval0, fretval1, fretval2, fretval3
     

     fretval0 = cbpm_rawfile_gain_factor_f(inst_name, bunch, zero)
     fretval1 = cbpm_rawfile_gain_factor_f(inst_name, bunch, one)
     fretval2 = cbpm_rawfile_gain_factor_f(inst_name, bunch, two)
     fretval3 = cbpm_rawfile_gain_factor_f(inst_name, bunch, three)
     print *,"GAINS           ", fretval0, fretval1, fretval2, fretval3


     raw_array0 => cbpm_rawfile_raw_ptr_f(inst_name, zero)
     raw_array1 => cbpm_rawfile_raw_ptr_f(inst_name, one)
     raw_array2 => cbpm_rawfile_raw_ptr_f(inst_name, two)
     raw_array3 => cbpm_rawfile_raw_ptr_f(inst_name, three)
     print *, "RAW............ ", raw_array0(1), raw_array1(1), raw_array2(1), raw_array3(1)
     print *, "                ", raw_array0(2), raw_array1(2), raw_array2(2), raw_array3(2)



     tbt_array0 => cbpm_rawfile_tbt_ptr_f(inst_name, zero)
     tbt_array1 => cbpm_rawfile_tbt_ptr_f(inst_name, one)
     tbt_array2 => cbpm_rawfile_tbt_ptr_f(inst_name, two)
     tbt_array3 => cbpm_rawfile_tbt_ptr_f(inst_name, three)
     print *,"TBT............ ", tbt_array0(1), tbt_array1(1), tbt_array2(1), tbt_array3(1)
     print *,"TBT             ", tbt_array0(2), tbt_array1(2), tbt_array2(2), tbt_array3(2)


     pos_array_h => cbpm_rawfile_pos_ptr_f(inst_name, CBPM_HORZ_DIM)
     pos_array_v => cbpm_rawfile_pos_ptr_f(inst_name, CBPM_VERT_DIM)
     print *,"POS x y         ", pos_array_h(1), pos_array_v(1)
     print *,"                ", pos_array_h(2), pos_array_v(2)


     phase_array_h => cbpm_rawfile_phase_ptr_f(inst_name, CBPM_HORZ_DIM)
     phase_array_v => cbpm_rawfile_phase_ptr_f(inst_name, CBPM_VERT_DIM)
     print *,"phase word x y  ", phase_array_h(1), phase_array_v(1)
     print *,"phase word x y  ", phase_array_h(2), phase_array_v(2)

     print *,""
     print *,""

  end do



  file_idx = 8362
  retval = cbpm_read_rawfile_f( file_idx )
  print *,"cbpm_read_rawfile returned: ",retval
  
  ! Get key numerical values
  retval = cbpm_rawfile_timestamp_f(timestamp)

  num_instruments = cbpm_rawfile_num_instruments_f()
  num_bunches = cbpm_rawfile_num_bunches_f()
  num_turns = cbpm_rawfile_num_turns_f()
  condx_number = cbpm_rawfile_condx_number_f()
  cern_curr = cbpm_rawfile_cern_current_f()

  print *,"File ID     : ", file_idx
  print *,"TIMESTAMP   = ", timestamp
  print *,"NUM_INSTS   = ", num_instruments  
  print *,"NUM BUNCHES = ", num_bunches
  print *,"NUM TURNS   = ", num_turns
  print *,"CONDX #     = ", condx_number
  print *,"CERN CURR   = ", cern_curr    
  print *,""
  print *,""
  
  num_words = num_bunches * num_turns
  inst_name = "."

  do while (inst_name(1:1) .NE. " ")
 
     retval = cbpm_rawfile_inst_names_f(inst_name)
     if (inst_name .EQ. " ") exit
     print *,"Location: ",inst_name
     
     rf_bucket = cbpm_rawfile_rf_bucket_f(three)
     print *,"RF bucket      ", rf_bucket


     fretval0 = cbpm_rawfile_pedestal_f(inst_name, bunch, zero)
     fretval1 = cbpm_rawfile_pedestal_f(inst_name, bunch, one)
     fretval2 = cbpm_rawfile_pedestal_f(inst_name, bunch, two)
     fretval3 = cbpm_rawfile_pedestal_f(inst_name, bunch, three)
     print *,"PEDS            ", fretval0, fretval1, fretval2, fretval3
     

     fretval0 = cbpm_rawfile_gain_factor_f(inst_name, bunch, zero)
     fretval1 = cbpm_rawfile_gain_factor_f(inst_name, bunch, one)
     fretval2 = cbpm_rawfile_gain_factor_f(inst_name, bunch, two)
     fretval3 = cbpm_rawfile_gain_factor_f(inst_name, bunch, three)
     print *,"GAINS           ", fretval0, fretval1, fretval2, fretval3


     raw_array0 => cbpm_rawfile_raw_ptr_f(inst_name, zero)
     raw_array1 => cbpm_rawfile_raw_ptr_f(inst_name, one)
     raw_array2 => cbpm_rawfile_raw_ptr_f(inst_name, two)
     raw_array3 => cbpm_rawfile_raw_ptr_f(inst_name, three)
     print *, "RAW............ ", raw_array0(1), raw_array1(1), raw_array2(1), raw_array3(1)
     print *, "                ", raw_array0(2), raw_array1(2), raw_array2(2), raw_array3(2)



     tbt_array0 => cbpm_rawfile_tbt_ptr_f(inst_name, zero)
     tbt_array1 => cbpm_rawfile_tbt_ptr_f(inst_name, one)
     tbt_array2 => cbpm_rawfile_tbt_ptr_f(inst_name, two)
     tbt_array3 => cbpm_rawfile_tbt_ptr_f(inst_name, three)
     print *,"TBT............ ", tbt_array0(1), tbt_array1(1), tbt_array2(1), tbt_array3(1)
     print *,"TBT             ", tbt_array0(2), tbt_array1(2), tbt_array2(2), tbt_array3(2)


     pos_array_h => cbpm_rawfile_pos_ptr_f(inst_name, CBPM_HORZ_DIM)
     pos_array_v => cbpm_rawfile_pos_ptr_f(inst_name, CBPM_VERT_DIM)
     print *,"POS x y         ", pos_array_h(1), pos_array_v(1)
     print *,"                ", pos_array_h(2), pos_array_v(2)


     phase_array_h => cbpm_rawfile_phase_ptr_f(inst_name, CBPM_HORZ_DIM)
     phase_array_v => cbpm_rawfile_phase_ptr_f(inst_name, CBPM_VERT_DIM)
     print *,"phase word x y  ", phase_array_h(1), phase_array_v(1)
     print *,"phase word x y  ", phase_array_h(2), phase_array_v(2)

     print *,""
     print *,""

  end do


end program cbpmfio_test_f
