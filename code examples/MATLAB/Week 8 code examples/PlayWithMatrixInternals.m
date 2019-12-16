% ----------------------------------------------------
% Basic example, using sub-matrixes. 
% For Lecture 1, Matlab.MTRN2500, S2.2017 
% Questions?, Ask lecturer, via Moodle or by email (j.guivant@unsw.edu.au)
% ----------------------------------------------------

% Script file, starts here ( see note (*) ).

% Clear console's screen. (So, we do not get distracted with previous prints.)   
clc() ;             

% We call/run this function, which I made, for creating certain matrix, 
% It is useful for our example. You do not need to care about its internals.
% BTW: I implemented it in another file, "makeMyData1.m".
M = makeMyData1();   

% Show the current contents of M
disp('This is M:'); disp(M);
disp('(press a key...)') ; pause;
% Pause script, till our brains are ready to carry on... 


M2 = M*0 ; 
% Create/define M2, as result of operating with M.
% M2 = zeros(size(M)) ; would give the same result in this case.
% I simply wanted M2 to be a matrix, having the size of M, but filled with zeros.

disp('After doing "M2 = M*0 ;" ');
disp('This is M2, now:'); disp(M2);
disp('(press a key...)') ; pause;

% now, we modify part of M2, by using a scalar
M2( 3:5,4:7)  =100 ;

disp('After doing "M2( 3:5,4:7)  =100 ;" ');
disp('This is M2:'); disp(M2);
disp('press a key...') ; pause;

% ..now, we modify part of M2, by using parts of M
M2( 3:5,4:7) = M( 3:5,4:7)*10;

% Show the current contents of M, again, to help to verify results.
disp('Remember, this is M:'); disp(M);


disp('After doing "M2( 3:5,4:7) = M( 3:5,4:7)*10;" ');
disp('This is M2, now:'); disp(M2);
disp('(press a key...)') ; pause;



M2( 1:3,1:4) = -M( 3:5,4:7);
M2( 1:3,end-2:end) = 111;
disp('After doing "M2( 1:3,1:4) = -M( 3:5,4:7); M2( 1:3,end-2:end) = 111;" ');
disp('This is M2, now:'); disp(M2);
disp('(press a key...)') ; pause;

clc();
disp('Done. Bye.') ;

% ----------------------------------------------------
% Even if this script program does end, the variables M and M2 do still exist,
% in the context.
% You can inpect the current context, by executing the function/command
% whos

% If you do not need them anymore, you can destroy some of them (so, you would free
% the memory used by them).

% here, I release both.
%       clear M M2 ;
% ----------------------------------------------------


% ----------------------------------------------------
% Note for students (NfS): you should verify, visually, the results

% (*), NfS.2: A script file is simply a sequence of commands.
% For more serious programming, we will later implement/organize our programs 
% by using functions.

% ----------------------------------------------------
% NfS.3:
% Easy experiments to try, using the functions :
% ndims()         :   reports the number of dimensions of a variable.
% size()          :   reports the size of a variable.
% numel()         :   reports the total number of elements of a variable.
% class()         :   reports the numeric class of  variable.    

% e.g.   "ndims(M)"
% use matlab's help  ( "help ndims" )
% ----------------------------------------------------



