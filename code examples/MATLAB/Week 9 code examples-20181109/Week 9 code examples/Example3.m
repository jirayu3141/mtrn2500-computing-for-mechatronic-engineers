%---------------------------------------------------------------
% Example 3, for lecture M3, MTRN2500, session 2.2017
%---------------------------------------------------------------
% Example, for showing how, by using nested functions, we share COMMON variables.  

% In this example, we allow many functions to modify a common variable.
% Using common variables, by using nested functions, can simplify and make more efficient 
% certain parts of our programs; in particular for very large variables, which we prefer
% not to duplicate (e.g. by being passed BY VALUE, to functions, as we did in
% in example1.m ).
% In this way, we achieve the intended good performance, without the risks involved
% using global variables.
%---------------------------------------------------------------

% (btw: You should have read {Example1.m,Example2.m}, before inspecting this example.)

%---------------------------------------------------------------

function Example3() % "Main()"
 
 
 A2500=rand(2,50)*100;
 ETC = 123;                 
 % We create the variables A2500 and ETC, used in this function
 % All these variables, which we created in this function, will be visible
 % for any nested function; consequently, these variables will behave as
 % being global, for the child functions.
 
 DoMyProcessing();
 
 
 return ;       % this function's execution ends here.
 
 % However, here, we do not close the function's body ( using 'end')
 % end %<----------------- NO END.
 % This previous function will be the NESTING function (the "mother")
 
 
 % The following function is defined inside the body of the previous one
 % (it is NESTED!)
 % All the local variables of the mother function, are visible in this
 % child function.
 % However, the local variables of the child function are just local to it.
 function DoMyProcessing()
 
  
 figure(1) ; clf();
 plot(A2500(1,:),A2500(2,:),'b.');
 
 
 modify1();
 
 hold on;
 plot(A2500(1,:),A2500(2,:),'r.');

 modify2();
 
 plot(A2500(1,:),A2500(2,:),'g.');
 modify3();
 
 plot(A2500(1,:),A2500(2,:),'ko');

 
 % z=NonChildFunction(A2500);    

% We may run this part, for showing the scope of the variables, for 
% these two identical functions; one of which is nested, and the other is not. 



% Remove or add the commenting symbol, '%', as needed.
 clc();
 ShowCurrentVariablesContextNested();
 ShowCurrentVariablesContextNotNested() ;    

 
 end      % <----- We need to close the body of this child function.
          % except we tried to nest other functions to it.
          % ( But, in this example, we do not intend to do that; so, we close it)

 


%-------------------------------------------------
% We perform some trivial operation, just for showing the concept.
% We assume A2500 is a 2xL matrix.
function modify1()
    A2500(1,:)=A2500(1,:)+0.5;
    A2500(2,:)=A2500(2,:)+0.4;
end
% We simply read and write A2500; it is visible, as if it were global!

%-------------------------------------------------
%-------------------------------------------------
% we perform another trivial operation.
% we assume ....
function modify2()
    A2500 =A2500+ 0.8*rand(size(A2500));
 end
%-------------------------------------------------
%-------------------------------------------------

function ii=modify3()
    ii = find(A2500(1,:)<A2500(2,:));
    A2500=A2500(:,ii);
end

function ShowCurrentVariablesContextNested()
    disp('NESTED: This is the context which we see from here:');
    xyz=1234;
    whos(),
end


end      % < ----------  END of mother (nesting) function.


% Any function defined between the owner of this "END" (the mother function) and this "END",
% will have full access (read, write, redefine, clear) to the local variables of the mother
% function.



% Of course, we can define other functions, which not necessarily need to
% access the common variables of the previous functions.

function z=NonChildFunction(X)
    z=X+0.01*X;
end

function ShowCurrentVariablesContextNotNested()
    disp('NOT NESTED: This is the context which we see from here:');
    xyz=5678;
    whos(),
end
% BTW: A2500 is not visible here; because this function is not nested inside the function
% which owns that variable.

%---------------------------------------------------------------
%---------------------------------------------------------------

% Next step, in lecture M3: Read TestPersistent1.m, where we use Persistent variables,
 
%---------------------------------------------------------------
% Questions?
% Ask the lecturer, via Moodle's forum or by sending him an email:
% to: j.guivant@unsw.edu.au

% (Doubts? ASK, before the snowball gets big.)
%---------------------------------------------------------------
