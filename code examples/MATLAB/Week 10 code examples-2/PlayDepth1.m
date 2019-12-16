%----------------------------------------------------------
% Playing with Depth data (from a RGB-D camera)
%----------------------------------------------------------
% Simple example, using typical data we use, recorded from a RGB-D camera.
% The data is contained in a structure. One of the fields corresponds
% to the sequence of "1 layer"-images.      ( V by H by images )
%----------------------------------------------------------
load('CarmineD.mat') ;  %load data, contained in a MAT file (which was provided).
% the file contains a saved variable, named "D".

figure(1) ; clf() ;

RangeOfInterest = [0,4000];  % 0 to 4000mm

for i=1:D.L,
    A = D.Depths(:,:,i)'; 
    time = D.t(i);
    imagesc(A,RangeOfInterest);colorbar(); 
    s= sprintf('image at time =[%.3f]\n',double(time)*0.0001);
    title(s);
    pause(0.1);     % wait some short period of time (so, human brains have time to appreciate the results).
end;    
%----------------------------------------------------------    
% (*) Brute force program, which just re-plots the new image, at each iteration,

% In addition: It does not offer any GUI capabilities at all.
% The only way to end it is by waiting it to reach the end of the data or by 
% interrupting it (Control-C, in the Matlab console)

% More refined implementations will be tried later, when we learn about 
% resources for plotting, etc.

% By Jose Guivant - For MTRN2500 - S1.2017
%----------------------------------------------------------
