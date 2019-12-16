% ------------------------------------------------
% This is a simple program, which reads a JPG image from a file;
% then it produces some versions of the original image, by modifying the associated
% matrix that contains it.

% We could try the same, in real-time, when we directly read images from a camera.
% as we will see, during the lecture.

% In this example, I implemented this program, through a function.
% This function does not return any variable, and does not expect any input argument.
% you may change this functionality later.

% By Jose Guivant, for Lecture Matlab.1, MTRN2500/s2.2017
% ------------------------------------------------

function playWithRGB_2()
% "void playWithRGB_2(void)", in C.

fileName = 'Photo1.jpg' ;
% You may propose other files to be tried.

% Read image using imread(), Matlab function to load JPG images.
rgb1 = imread(fileName);
% You may verify that the variable rgb1 will be a 3D matrix( WxHx3 ) of class integer "uint8".
% In this case WxH = 640x480, because the image in the file was taken using
% that pixel resolution. 

clc() ;            % clear console's screen. 

whos ;
% this command just prints the list of variables of this current context (function's scope).

% Now, we show the original image, in a figure.
figure(1) ;     % select/create figure #1, 
clf() ;         % clear it (in case it existed from previous plotting)
subplot(211) ;  % divide the figure in 2 subfigures, select the top one ( see matlab help ), 
image(rgb1) ;   % show the original image, in the current subfigure.
title('Original Image');  % write some title
disp('press a key to continue..');
pause;

rgb2 = rgb1 ;                           % create a copy of the original image.
rgb2( 20:100, 30:300, :) = 0 ;          % we modify some rectangular ROI.
subplot(212) ;  % select the lower subfigure ( see Matlab's help ), 
image(rgb2) ;   % show the new (modified) image.
title('Effect of "My action 1"'); 

whos ;
% Again, this command just print the current list of variables in this scope.


% if you expect not to use the variable rgb1, anymore in this program, you
% may destroy it (e.g. to release memory resources).
% Because in this example we are not using too much memory, so we do not
% really care about this matter, now.
clear rgb1 ;    % anyway, I clear this currently useless variable...

disp('press a key to continue..');
pause;          %blocks, till user press a key, to continue;


i1 = (250:400);j1 = (100:250);
rgb2( i1, j1, [2,3]) = 0 ;
% destroy info in channels2 and 3 (G and B), just for this area of the image.
subplot(212) ;  % select the lower subfigure ( see Matlab's help ), 
image(rgb2) ;   % show the new image.
title('Effect of "My action 2"'); 

disp('press a key to continue..');
pause;

% More "processing" of the image. 
% Switch channels R and B, just for certain areas of the image.
i1 = (250:450);j1 = (440:540);
rgb2( i1, j1, [1,3]) = rgb2( i1, j1, [3,1]);

i1 = (280:310);j1 = (260:320);
rgb2( i1, j1, [1,3]) = rgb2( i1, j1, [3,1]);


subplot(212) ;  % select the lower subfigure ( see Matlab's help ), 
image(rgb2) ;   % show the new image.
title('Effect of "My action 3"'); 

% Enough "enhancement" of the image; mission accomplished.
disp('Bye');

end
%--------------------------------------
% note: the function "image()" shows a matrix as being an image. If the matrix is
% a 3D matrix of numeric class "uint8", then it will interpret the numbers
% as RGB pixels assuming the dimensions as ( Height, Width, RGB layers ),
% where layer 1 is RED, layer 2 is GREEN and layer 3 is assumed to be the
% BLUE channel.
% 
% The function "image()" has many other functionalities, when used with
% other types of data. 
% You could read more details, using Matlab's help.
% "help image"

% The function "imread()" allows to read a file containing a picture (JPG, BMP, etc.)
% It returns a matrix of size MxNx3, of class uint8, i.e. the RGB
% representation of the picture, using the order convention we have discussed.

%--------------------------------------
% Questions? Ask the lecturer, via Moodle or by email (j.guivant@unsw.edu.au)
%--------------------------------------
