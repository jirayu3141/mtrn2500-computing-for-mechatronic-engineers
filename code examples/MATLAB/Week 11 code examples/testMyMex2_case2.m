% .............................................

% MTRN2500 - Session 1.2016
% Example, for testing our MEX file MyMex2.c
% (MyMex2.c implements a 2D Occupancy Grid)

% Questions : ask the lecturer. 
% Jose Guivant - j.guivant@unsw.edu.au OR via MTRN2500's Moodle

% .............................................



% Try one
A= [-100;100;-200;200;5];  % ROI -100<x<100, -200<y<200, delta=5
B = rand(2,10000)*300-150; % Some random points
M1 = MyMex2(A,B);
figure(1) ; clf(); imagesc(M1);

pause;

% Try again, with some different case.
A= [-100;100;-200;200;4];  % ROI -100<x<100, -200<y<200, delta=4
B=[] ; B(2,:) = (-300:100); B(1,:) = 50; 
M2 = MyMex2(A,B);
figure(2) ; clf(); imagesc(M2);

% DONE.
% .............................................