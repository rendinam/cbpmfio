
function load_CBPM_input(varargin)
  if ~libisloaded('libcbpmfio')
      
    if length(varargin) == 1
        disp(['Using basedir override = ' varargin{1}]);
        basedir = varargin{1};
    else
        basedir = getenv('ACC_RELEASE_DIR');
    end
    fprintf('Loading CBPM file input library...  ')
    libdir = [basedir '/solib'];
    incdir = [basedir '/cbpmfio/include'];
    mexpath = [basedir, '/cbpmfio/matlab'];
    addpath(mexpath);
  
    % [notfound, warnings] = 
    loadlibrary([libdir '/libcbpmfio.so'], ...
                [incdir '/cbpmfio_matlab.h']);
  
    fprintf('DONE.\n')
  end
end
  













