function autosave_wrapper()
%   Use this as a sample for autosaving results.
% Version 1.0
% Mark Whitty
% UNSW Mechatronics
% m.whitty@gmail.com
close all hidden;  
clear variables;
clear global;  clc;
dbstop if error % – so when I’m debugging my code, it will automatically stop when it hits an error, instead of just reporting the error and clearing it

prog_description = 'Testing autosave 180920';

% Set up global variables for managing things that should be shared
global FIGURES SWITCH LOG DATA
configfile; 
% Setup plots and animations
setup_plots();
initialise_file_logging(prog_description);
it = 1;
start_main_loop_time = clock();

% Main loop 
while 1
    it = it+1;
    if(it > 100), break; end
    DATA.i = it;
    % Do stuff!
    test_fun_1();
    test_fun_2();
        
    % Log data
    if(mod(it, RECORD_INTERVAL) == 0) 
if SWITCH.MAIN_PLOT
        do_plots();
end

if SWITCH.LOG_DATA_TO_FILE
        save([pwd '\' LOG.log_folder sprintf('\\log%04d.mat', LOG.log_iteration)], 'DATA')
        LOG.log_iteration = LOG.log_iteration + 1;
end

    end
    drawnow

    if it > PAUSE_ITERATION
        pause(0.1); 
    end
end % end of main loop

end_main_loop_time = clock();

if SWITCH.PROFILE, 
    profile report
    profile_stats = profile('info');
    save([LOG.log_folder '\' 'profile_results'], 'profile_stats');

    profile_stats = profile('info');
    real_names = {'Stuff 1', 'Stuff 2'};
    fun_names = {'test_fun_1', 'test_fun_2'};
    num_fun_names = length(fun_names);
    fun_times = zeros(size(fun_names));
    fun_num_calls = zeros(size(fun_names));
    table(1, 1:2) = {'Function', 'Average time per iteration'};
    table(2, 1:2) = {'', '$\left[ms\right]$'};

    for i = 1:size(profile_stats.FunctionTable, 1)
        for j = 1:num_fun_names
            if(isequal(fun_names{j}, profile_stats.FunctionTable(i).FunctionName))
                fun_times(j) = profile_stats.FunctionTable(i).TotalTime;
                fun_num_calls(j) = profile_stats.FunctionTable(i).NumCalls;
                table(j+2, 1) = {real_names{j}};
                table(j+2, 2) = {profile_stats.FunctionTable(i).TotalTime/profile_stats.FunctionTable(i).NumCalls*1000};
            end
        end
    end
    % Output a table in Latex format
    %lattable=latextable(table,{'p{0.4\textwidth}', 'p{0.2\textwidth}'}, 'Speeds of function calls.', 'tab:data1')
    
end

save([LOG.log_folder '\data' datestr(clock, 'yyyy-mm-dd-HH-MM-SS') '.mat'])

if SWITCH.MAIN_PLOT
    save_fig_date(FIGURES.fmain, 'main')
end

clear global DATA 
