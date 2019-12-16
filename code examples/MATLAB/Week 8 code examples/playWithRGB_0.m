% ------------------------------------------------
% This is a simple program, which reads a JPG image from a file;
% then it produces some versions of the image, by just inverting
% some of the RGB channels.
% Jose Guivant  - Lecture Matlab.1;  MTRN2500 - s2.2017

% We could try the same, in real-time, when we directly read images from a camera.
% as we will see during the lecture.

% ------------------------------------------------

% We read the photo using imread(), which is a Matlab function to load JPG images.
rgb1 = imread('Photo1.jpg');
% You could verify that rgb1 will be a 640x480x3 matrix, of class integer "uint8".
% (it is size WxH = 640x480, because the JPG image has that pixel resolution)

% Now we create another variable, of the same size and class (for representing RGB images, too),
% but we copy to it the original rgb, switching certain channels.
% We do it, easily, by just using indexes.

rgb2 = rgb1(:,:,[2,1,3]);
% red and green channels, are swapped 


rgb3 = rgb1(:,:,[3,2,1]);
% and in this case, red and blue channels ... 


rgb4 = rgb1(:,:,[1,3,2]);
% green and blue channels , 

rgb5 = rgb1(:,:,[3,1,2]);

% blue <---red
% green <---blue
% red <--- blue;, 


% "show the new images, to the humans"
% NfS: In this lecture and examples, we do not intend to investigate about how to
% show data; however, we use some basic image functions, for the purpose of this lecture. 


figure(1) ; clf() ; 
subplot(321) ; image(rgb2) ;title('R<-->G');
subplot(322) ; image(rgb3) ;title('R<-->B');
subplot(323) ; image(rgb4) ;title('G<-->B');
subplot(324) ; image(rgb5) ;title('RGB<->BRG');
subplot(313) ; 
image(rgb1); title('Original Image');

% ------------------------------------------------
