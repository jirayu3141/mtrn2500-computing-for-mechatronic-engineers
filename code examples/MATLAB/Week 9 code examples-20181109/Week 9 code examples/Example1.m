
% Example1, for lecture M3, MTRN2500, session 2.2017

% In this example we do the following:
% Define some functions
% Call the functions.
% plot some results for visualizing effects.



%--------------------------------------------------------
function Example1() % "Main()"

% here, we create some test data, a 2xN matrix.
 N=50;  A = rand(2,N)*100;         


 % We may consider that each A(:,i) is a 2D, (x;y), point; (note: A(:,i) is "2x1"
 % so, A(1,:) are the x-coordinates, and A(2,:) the y's of the N (x;y) points.
 % However, in general terms, A would have other interpretations.
 
 figure(1) ; clf();         % Here, we create a figure, in which we plot results.
 plot(A(1,:),A(2,:),'b.');  % Now, we plot the original data
 
 % We perform some basic processing.
 A = modify1(A);            % modify A  ( in this case, we do "A=F(A)" : we overwrite its previous contents)
 
 hold on;                    % To keep adding plots, we use the command "hold on".
 plot(A(1,:),A(2,:),'r.');

 A = modify2(A);
 [B,~] = modify3(A);
 % btw: I used the symbol '~' to specify I do not need the second output
 % variable, which is returned by the called function.
  
 plot(A(1,:),A(2,:),'g.');
 plot(B(1,:),B(2,:),'ko');

 legend({'original','version 1','version 2','version 3'});
end
%--------------------------------------------------------


%-------------------------------------------------
% In Matlab, the arguments (input variables), are shared
% "BY VALUE" when those are modified inside the called
% function.
% The following function, receives 'x' by reference; however, as soon
% we try to modify it (inside the called function), a new copy of 'x' 
% is generated, locally.
% We will never be able to touch the original (caller's variable)

function modify0(x)     % This is a useless funcion (why???).
    x(1,:)=x(1,:)+1.5;
    x(2,:)=x(2,:)+0.5;
end
% This function is WRONG: It would fail in modifying 'x' (if that was its purpose)

%-------------------------------------------------
% We perform some trivial operation, just for showing the concept.
% (We assume the input variable, x, is a 2xL matrix.
% so, we do not verify consistency of the input variables.)

function y=modify1(x)
    x(1,:)=x(1,:)+0.5;    x(2,:)=x(2,:)+0.4;    y = x ;
end

% function y=modify1(x)
%     y = x;  y(1,:)=y(1,:)+0.5;    y(2,:)=y(2,:)+0.4;    
% end



%-------------------------------------------------
%-------------------------------------------------
% We perform another trivial operation.
function y=modify2(x)
    y =x+ 0.8*rand(size(x));  %we add a "bit of noise" to the original data.
 end
%-------------------------------------------------
%-------------------------------------------------
% We perform another operation (we assume A is 2xL, as before)
% We return the points whose first row is lower than the second one 
% (x<y, according to the meaning of the data, in our example)
function [B,ii]=modify3(A)
    ii = find(A(1,:)<A(2,:));
    B=A(:,ii);
end
%The function returns the new points, and their associated indexes.
% (Note: We discussed about indexes, in Lecture M2)
%-------------------------------------------------



%---------------------------------------------------------------

% Next step, in lecture M3: Read example2.m, in which we use GLOBAL VARIABLES,
% for sharing variables.

%---------------------------------------------------------------
%---------------------------------------------------------------
% Questions?
% Ask the lecturer, via Moodle's forum or by sending him an email:
% to: j.guivant@unsw.edu.au

% (Doubts? ASK, before the snowball gets big.)
%---------------------------------------------------------------
