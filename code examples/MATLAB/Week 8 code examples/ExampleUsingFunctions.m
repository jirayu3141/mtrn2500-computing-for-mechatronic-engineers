
% -----------------------------
% "ExampleUsingFunctions.m". We use this sample code, for understanding how
% to use (define and call) FUNCTIONS in Matlab programming language.
% MTRN2500 - 2017.S2
% Lecturer: Jose Guivant.
% Questions: Via Moodle's forum or email : j.guivant@unsw. edu.au

% -----------------------------
% In this example code, we see how functions are defined. We discuss about the
% involved variables (input, output and local variables)

% The first function in this file, is the MAIN function. It is the one actually called by
% the system, when we run/call this program FILE.

% The name of the function should be identical to the name of the file.
% (However, I usually like to call it MAIN.)

%function MAIN()
function ExampleUsingFunctions()
% In this particular example, the main function does not receive any input and
% does not return any result.
% (Equivalent to "void main(void), in C)"

% We create some local variables.
X = zeros(10,10)+1;
Y = ones(10,10);
% Note: all the variables, defined in this example program, are DOUBLE
% PRECISION, because we do not explicitly indicate a different numeric
% data type.

% We call some functions; which are defined, in this example, at the end of this file.

resultA1 = DoMyProcessing1(X,Y);
% You could see, this function receives 2 input variables and returns one.
% The function returns a variable, which we name "resultA1", in the caller's
% context.


[resultB1,resultB2] = DoMyProcessing2(X,Y);
% This function receives two input variables and returns two variables.


Z=rand(size(X));
[wA,wB] = DoMyProcessing2C(X,Z);      
% it should be OK; consistent inputs (see the code of the function)

 Z=rand(4,3);
 [wA,wB] = DoMyProcessing2C(X,Z); % it should fail, due to inconsistent inputs


 [ok,wA,wB] = DoMyProcessing2Cv2(X,Z);
 

%Although this called function does nominally return 2 output variables, I may ignore them if I want to.
DoMyProcessing2B(X,Y);


return ; % used to force the end of the function. 
% "return" is redundant here, because the function ends anyway ("end") 
end
% ........................................
% We may define other functions, that are visible just internally, in this module.
% (However, We may be able to offer those other "local" functions by using
% "pointers" (i.e. function handles). But we are not discussing those matters now.
% The only function that is externally visible is the first one (whose externally visible name 
% is the name of the file that contains the program). 



% Example: a function returning one veriable.
function r = DoMyProcessing1(x,y)
    % Usually, we should verify that the sizes are consistent.
    % however, for now, we assume that the call is consistent.
    r = x+y*2;      % here, some trivial processing.
end
% About parameters passing: Matlab uses a HYBRID approach.
% The input variables x,y are passed BY REFERENCE.
% However, as soon we try to modify one of them, a copy of the passed
% variable is created and made to be addressed by the local variable.
% When the function ends, these copies (of the input variables) are
% destroyed (lost).
% The caller's variables are NOT modified.
% All the local variables are destroyed when the function ends,
% EXCEPT the ones returned and the ones are still referencing certain caller variables. 
 
 
% About the output variables.
% The output variable, named "r" in the example, is dynamically created at
% run time, and returned to the caller.
% It will stay alive (keep existing) in the caller scope of variables,
% till the caller eventually deletes it or when the caller scope is
% destroyed.

% Note: the variables defined inside the functions are not visible for other functions, 
% i.e. they are LOCAL variables (like in C).

% There is a way for sharing scopes of variables, via NESTED functions and/or GLOBAL variables. 
% We will see those capabilities in a subsequent lecture.



% Example 2: a function returning more than one variable.
function [r1,r2] = DoMyProcessing2(a,b)
    r1 = a+b*2;   r2 = a*2+b*5;
end


function [r1,r2] = DoMyProcessing2B(a,b)
    if (a(1)==123)        % crazy thing, just to show how "return" can be used to affect the function's flow.
        r1 = a ; r2=b ;   
        return ;          % This function ends here and now (i.e. control is returned to caller, now)          
    end
    etc = a+b*2;       % etc:  is an auxiliary variable, LOCAL. 
    r1 = etc*3;
    r2 = a*2+etc;
    % END, (implicitly the function returns to called here).
end

% note: the variables "a" and "b" are used BY REFERENCE, provided we do not
% modify them, inside the function.
% This fact is transparent for us; however, you should know it.

%-------------------------------------------------


% Example 2: a function returning more than one variable.
function [r1,r2] = DoMyProcessing2C(a,b)
    % Checking consistency. I is a good practice, except if you are well sure
    % that the callers do not incur in mistakes (*)
    if (size(a)==size(b)), 
        r1 = a+b*2;   r2 = a*2+b*5;
        return ;
    end;  
    
    % If we are here, it is because inputs are not consistent, for the 
    % operations we try to do.
    disp('Error: Inconsistent input data!'); 
    %  We print, just for debugging purposes.
    r1=[]; r2=[]; % Alternate action, e.g. returning "empty results"
end

% (*): Matlab language is interpreted (or, in some cases, compiled in run time), so the
% consistency check is done also in run-time.



% We may return another variable, just for indicating success or not.
% Like this case, where I return a variable, which I named (locally)
% "oki".
function [oki,r1,r2] = DoMyProcessing2Cv2(a,b)
    % Checking consistency. I is a good practice, except if you are well sure
    % that the callers do not incur in mistakes (*)
    if (size(a)==size(b)), 
        r1 = a+b*2;   r2 = a*2+b*5; oki=1; %oki=1 means success (oki-doki).
        return ;
    end;  
    
    % If we are here, it is because inputs are not consistent, for the 
    % operations we try to do.
    r1=[]; r2=[]; oki=0 ; % returning "empty results" and ok=0
end




% -------------------------------------------------
% Questions: ask the lecturer, via Moodle or email (j.guivant@unsw.edu.au)
% -------------------------------------------------
