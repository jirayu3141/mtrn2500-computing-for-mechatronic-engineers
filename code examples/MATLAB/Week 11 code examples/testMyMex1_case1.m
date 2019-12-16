
% .............................................

% MTRN2500 - Session 1.2017
% Example, for testing our MEX file MyMex1.c

% Questions : ask the lecturer. 
% Jose Guivant - j.guivant@unsw.edu.au OR via MTRN2500's Moodle

% .............................................

% MyMex1.c is a basic example of a C-MEX function, which we implemented to
% understand how 
%   1)  to receive variables, from Matlab
%   2)  to return variables to Matlab from our C function.

clc();

x = [1000,200];
y = zeros(12,3,4,'single');
z = uint32([1,2,3]);



% I call my MEX function, expecting 2 returned variables, and calling it
% with 3 input arguments.
[a,b]=MyMex1(x,y,z);
% we see what the function printed on the terminal.
pause;
clc;

% now, We expect 4 ouputs, and we use 6 inputs.
[a,b,c,d]=MyMex1(x,y,z,x,11111, {x,y} );
% we see what the function printed on the terminal.




