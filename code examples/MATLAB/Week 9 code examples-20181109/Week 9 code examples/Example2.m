%---------------------------------------------------------------
% Example2.m, for lecture M3, MTRN2500, session 2.2017
%---------------------------------------------------------------
% Example, for showing how a global variable is visible (read/modified) from many
% functions.
%---------------------------------------------------------------
% In this example, we allow many functions to modify a 'global' variable.
% By using global variables we can simplify, and make more efficient certain parts
% of our programs; in particular, for very large variables, which we prefer
% not to duplicate (e.g. which occurs, when being passed BY VALUE, to functions, as we did in
% in example1.m ).
% However, using global variables is a promiscuous way of sharing data; which may imply some
% disadvantages, as well.
%---------------------------------------------------------------

function Example2() % Main()

 global A2500;
  % We declared that the variable A2500, used in this function, is  GLOBAL
 
 % The rest of this example has certain similarity with Example1.m
 % (btw: You should have read Example1.m, before inspecting this example.)
 
 N=50;  A2500 = rand(2,N)*100;
 
 figure(1) ; clf();
 plot(A2500(1,:),A2500(2,:),'b.');
 
 
 modify1();
 
 hold on;
 plot(A2500(1,:),A2500(2,:),'r.');

 modify2();
 
 plot(A2500(1,:),A2500(2,:),'g.');
 modify3();
 
 plot(A2500(1,:),A2500(2,:),'ko');

 
end


%-------------------------------------------------
% We perform some trivial operation, just for showing the concept.
% We assume A2500 is a 2xL matrix.

function modify1()
    global A2500;           % we also locally declare the global variables to be used here.
    A2500(1,:)=A2500(1,:)+0.5;
    A2500(2,:)=A2500(2,:)+0.4;
end

%-------------------------------------------------
%-------------------------------------------------
% We perform another trivial operation.
% We assume ....
function modify2()
    global A2500;
    A2500 =A2500+ 0.8*rand(size(A2500));
 end
%-------------------------------------------------

function ii=modify3()
    global A2500;
    ii = find(A2500(1,:)<A2500(2,:));
    A2500=A2500(:,ii);
end

%---------------------------------------------------------------
%---------------------------------------------------------------

% Next step, in lecture M3: Read example3.m, where we use NESTED FUNCTIONS,
% for sharing variables.

%---------------------------------------------------------------
% Questions?
% Ask the lecturer, via Moodle's forum or by sending him an email:
% to: j.guivant@unsw.edu.au

% (Doubts? ASK, before the snowball gets big.)
%---------------------------------------------------------------


