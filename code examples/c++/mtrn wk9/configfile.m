%%% Configuration file
%%% Permits various adjustments to parameters of the algorithm.
% Mark Whitty
% UNSW Mechatronics
% m.whitty@gmail.com

% Random configuration parameters go here...

% Number of main while loop iterations between: 
RECORD_INTERVAL = 10;                           % logging current state

% Iteration of program before which nothing is plotted to speed up debugging.
PAUSE_ITERATION = 80;  % Set this to an integer to pause 
                                                
% switches
SWITCH.PROFILE= 1; % if 1, turn on MatLab profiling to measure time consumed by simulator functions
SWITCH.MAIN_PLOT = 1;  % if 0, turns off the main visualisation plot
SWITCH.LOG_DATA_TO_FILE = 0; % if 1, turns on a logging system and puts a snapshot of data
% from each logging interval into a separate file in a subfolder called
% logdata-YYYY-MM-DD-hh-mm-ss
% Data may be logged at the end anyway, but not normally on every loop
% iteration.

% Turn on profiling if it isn't already on
if SWITCH.PROFILE, 
    S = profile('status')
    if(isequal(S.ProfilerStatus, 'off'))
        profile on -detail builtin -timer real -memory
    else
        profile clear
    end
end








