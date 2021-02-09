%------------------------------------------------------------------
% Simple example function that loads all MEX-wrapped libraries
% necessary for CBPM file input operations, reads in a 
% CBPM raw data file, and then provides access to select file
% data components as native MATLAB data types.
%------------------------------------------------------------------

function cbpmFileInputDemo( )
       
    addpath([getenv('ACC_RELEASE_DIR') '/cbpmfio/matlab']); load_CBPM_input();

    cbpm_read_rawfile_m( 4080 );
    
    timestamp = cbpm_file_timestamp_m()
    bunches = cbpm_file_num_bunches_m()
    num_insts = cbpm_file_num_insts_m()
    turns = cbpm_file_num_turns_m()
    cern_current = cbpm_file_current_m()
    condx = cbpm_file_condx_m()
    
%     bucket = cbpm_file_rf_bucket_m(1) - UNIMPLEMENTED - placeholder

    for num = drange(1:num_insts)
      num
      loc = cbpm_file_inst_locs_m()
%       index = cbpm_file_cesr_index_m(loc) - UNIMPLEMENTED - placeholder
    end

    ped = cbpm_file_pedestal_m( '2W', 1, 0 )
    ped = cbpm_file_pedestal_m( '2W', 1, 1 )
    ped = cbpm_file_pedestal_m( '2W', 1, 2 )
    ped = cbpm_file_pedestal_m( '2W', 1, 3 )
    
    dat = cbpm_file_raw_data_m( '1W' )
    dat = cbpm_file_tbt_data_m( '1W' )
    dat = cbpm_file_pos_data_m( '1W' )
    dat = cbpm_file_shaker_phase_m( '1W' )
   
end


