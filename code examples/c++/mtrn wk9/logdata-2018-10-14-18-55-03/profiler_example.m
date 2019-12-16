 function profiler_example()
% By Mark Whitty
% 100608

SWITCH_PROFILE = 1;   
% Just a variable to indicate whether you want the 
% profiler on (1) or not (0).

% Turn on profiling if it isn't already on
if SWITCH_PROFILE, turn_on_profiler(); end

for i = 1:1000
    j = myfun(i);
    word = sprintf('%d', j);
    disp(word);
end



if SWITCH_PROFILE
    profile report; % Brings the profiler up in your browser.
    profsave;  % Saves it to 'profile_results' folder.
    %copyfile('profile_results', [log_folder '\' 'profile_results'], 'f');   
    % Optional, I automatically copy the results 
    % on every test run I do.
end
end

% You may need to copy this into a new file.
function turn_on_profiler()

S = profile('status');
    if(isequal(S.ProfilerStatus, 'off'))
        profile on -detail builtin -timer cpu  % Check these flags. You can use real time or CPU time (change 'cpu' to 'real')
    else
        profile clear
    end
end

%% Do stuff in this function
function j = myfun(i)
    j = i+1;
end