%----------------------------------------------------------
% Playing with RGB data
%----------------------------------------------------------
% Simple example, using typical data we use in projects, recorded from a RGB-D camera.
% The data is contained in a structure. One of the fields corresponds
% to the sequence of RGB images (V by H by 3 by L, in a 4D matrix).
% (We inspect the data, in class)
%----------------------------------------------------------
function PlayRGB1( )
load('CarmineRGB.mat') ;      % load some data (which I saved before)


figure(1) ; clf() ;           % as usual, we create a figure for showing results.  

for i=1:Co.L,                 % loop
    A = Co.RGBs(:,:,:,i);     % one image of the sequence  
 
    % we usually use it, for something...
    A(20:80,80:end-10,:)=A(20:80,80:end-10,[2,1,3]);  % some "filtering"
    
    % we may see it, now.
    image(A);                % show it (by a brute force approach (*))
    pause(0.05);             % wait some short period of time (so, human brains have time to appreciate the results).
end;    
end
%----------------------------------------------------------
% (*) Brute force program, which just re-plots the new image, at each iteration,

% In addition: It does not offer any GUI capabilities at all.
% The only way to end it is by waiting it to reach the end of the data or by 
% interrupting it (Control-C, in the Matlab console)

% More refined implementations will be tried later, when we learn about 
% resources for ploting, etc.

% By Jose Guivant - For MTRN2500 - S1.2017
%----------------------------------------------------------