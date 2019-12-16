
% -------------------------------------------------
% Example of a basic script program, in Matlab.
% Lecture Matlab.1 ; MTRN2500 - s2.2017
% Solving Example_L1_01.m in a different way.

N = 1000; 
freq1 = pi/500;
X = (1:N)';         % create a column vector (Nx1), monotonically increasing from 1 to N.
Y = sin(freq1*X).*cos(freq1*10*X);    % <---- note that we used the operator ".*" in place of simply "*". ELEMENT-WISE multiplication.

% plot the data (as in previous example).
figure(1) ; clf();
plot(X*freq1*180/pi,Y,'b');
ylabel('F(x)'); xlabel('x (degrees)');

% -------------------------------------------------

% See how we created and used the variables X,Y, i, N, freq1;
% You may read help information about the functions we used to plot.

% -------------------------------------------------
% Questions: ask the lecturer, via Moodle or email (j.guivant@unsw.edu.au)
% -------------------------------------------------
