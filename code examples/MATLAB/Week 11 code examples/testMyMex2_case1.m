
% .............................................

% MTRN2500 - Session 1.2017
% Example, for testing our MEX file MyMex2.c

% Questions : ask the lecturer. 
% Jose Guivant - j.guivant@unsw.edu.au OR via MTRN2500's Moodle

% .............................................
% we need to read the example "MyMex2.c" to see how it works.



Lp=100000;
% A population of points, randomly generated.
% according to a Gaussian ( aka "Normal" ) distribution (do "help randn")

sdev1 = 2 ; % standard deviation = 2;
pp1 = sdev1*randn(2,Lp);   % Each element "pp1(:,i)" is a 2x1 vector that we assume
% to be a 2D point , i.e. [x;y]
%


% another set of samples, twice the number of pp1()
sdev2 = 3 ; % standard deviation = 3;
pp2 = sdev2*randn(2,  2*Lp);
% I shift it, to have a mean at (x,y)=(4,2)
pp2(2,:)=pp2(2,:)+6;
pp2(1,:)=pp2(1,:)+4;


% I concatenate both arrays of points
ppAll = [ pp1,pp2 ] ;  % try to see why I use "," and not ";".

% clear pp1 pp2;   % I do not need these variables anymore. So, I can destroy them.


% I call my MEX function, for obtaining a 2D histogram
% The grid would cover the region [-10,10]X[-10,10], in cells of size 0.25
% we can assume all the values of x and y are in meters.
% (to give it some practical interpretation.)

% we call the MEX function, accordingly to the calling convention.
m=MyMex2([-10;10;-10;10;0.25],ppAll);

% we use IMAGE, for visualizing the results.
figure(1) ; clf() ; imagesc(m);
title('Population per cell');


% DONE.
% .............................................

