% initialise_file_logging is a function which sets up file logging 
% Mark Whitty
% UNSW Mechatronics
% m.whitty@gmail.com
% 090916
% 140506 v2 Rationalised.
function [log_folder, log_iteration] = initialise_file_logging(additional_program_description)
global LOG
LOG.log_iteration = 1;
log_folder = ['logdata-' datestr(clock, 'yyyy-mm-dd-HH-MM-SS')];
mkdir(log_folder);
description_file = fopen([log_folder '\' 'description_file-' datestr(clock, 'yyyy-mm-dd-HH-MM-SS') '.txt'], 'w');
fwrite(description_file, [sprintf('%s', additional_program_description)]);
fclose(description_file);
copyfile('*.m', log_folder);  % Autobackup the m files in the working directory
copyfile(['configfile.m'], [log_folder '\configfile.m']);  % Autobackup the configfile
LOG.log_folder = log_folder;
end
