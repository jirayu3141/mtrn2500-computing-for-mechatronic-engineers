
%---------------------------------------------------------------
% Example 4 (TestPersistent1.m), for lecture M3, MTRN2500, session 2.2017
%---------------------------------------------------------------
% Example, for showing how to use PERSISTENT variables.  
% Here, we implement a function, for testing the persistency of variables.
%---------------------------------------------------------------
% (btw: You should have read {Example1.m,Example2.m,Example3.m} before inspecting this example.)
%---------------------------------------------------------------

function y=TestPersistent1()
   persistent  ZZZ ;            % We declare that ZZZ is "persistent".
   % You may declare more than one to be persistent, if needed.   
   
   if ~isempty(ZZZ),    % Easy way to verify if our local ZZZ was aready created (*).                    
   
       % Here, because the variable ZZZ does already exist, we simple proceed to use it.
       % The current value of ZZZ is the one we got the last time we
       % created/modified it, in this function.
        
       ZZZ = ZZZ+1;             
       % Here we performed some operation (a trivial one, in this case)
       % on the persistent variable.
       % BTW: We can read its current contents, modify them, resize the
       % variable, etc. We have full control of it, as with any other local
       % variable.
       
       % Note: operator '~'  : Logical NOT  ;  "y=not(x);" or  "y=~x;" ;
       
       disp('I just used the veriable.');
   
   else    % It does no exist, yet; so, we create it now.  
       ZZZ = zeros(1,6) ;       
       disp('Hello, caller; I am CREATING my persistent variables, now!');
       % For teaching/debugging purposes, a message is printed here/now.
   end
   
   y = ZZZ;         % We return it, fr inspecting it, from outside the function.
   
   % The current value of ZZZ (just before this function ends executing) 
   % will be found the next time, when we call/run this function again (**).
end


% -------------------------------------------------------------
% (*) just my way for verifying the existence of a persistent variable.
% There are other ways to do it (e.g. using the function "exist()")
% However, one matter must be clear: 
% --> You need to create the variable, at least once, before using it.
% -------------------------------------------------------------
% Analogy, with C/C++:
% Persistent variables have a role similar to that of local STATIC variables, 
% in C/C++ functions.
% However, in Matlab, we create them dynamically; while in C/C++ you can
% define them statically, i.e. in compiling time.
% This is why we needed to detect its existence, before using it, in our
% example.

% -------------------------------------------------------------

% (**) Except, we do "clear" the context of the function.
% For instance:
% doing "clear all;" from the main terminal, to clear all Matlab contexts.

% Doing "clear TestPersistent1;"     
% For clearing the context of the function TestPersistent1 (if that is in memory).

% Or because we mofified the function's M file, from the Matlab editor.
% Matlab may "re-load" it into memory (consequently, destroying its
% previous context)
%---------------------------------------------------------------

% How to test this example?
% From the console, you may run this short piece of code: 
% for i=1:5, r=TestPersistent1();  disp(r); end;

%What you will see in the console, will be consistent with the explanation.

%---------------------------------------------------------------

% You may have imagined, during this explanation, that the creation of a
% persistent variable could be done in a "constructor". Yes, you may
% implement a class, where some data can be shared by the instances of the
% object.

%---------------------------------------------------------------
% Questions?
% Ask the lecturer, via Moodle's forum or by sending him an email:
% to: j.guivant@unsw.edu.au

% (Doubts? ASK, before the snowball gets big.)
%---------------------------------------------------------------


