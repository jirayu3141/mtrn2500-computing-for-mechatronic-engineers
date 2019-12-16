
% -------------------------------------------------
% Example of a basic program, in Matlab.
% Lecture Matlab.1 ; MTRN2500 - s2.2017

N = 1000; 
X = zeros(N,1);         % define the vectors/matrixes we use.
Y = zeros(N,1);
freq1 = pi/500;
for i=1:N              % "FOR" loop. ("brute force", for the intended purpose)
    X(i) = i*freq1;
    Y(i) = sin(X(i))*cos(X(i)*10);
end;

% We "plot" the data. We just use the function "plot()" for the purpose of inspecting
% results. We will discuss about plot() and many other graphical functions, in another lecture.
figure(1) ; clf();
plot(X*180/pi,Y,'b');
ylabel('F(x)'); xlabel('x (degrees)');

% -------------------------------------------------

% See how we create and use the variables X,Y, i, N, freq1;

% You may read the help information about the functions we used to plot.
% In this example, we implemented the task using a LOOP. See example #2 for
% a more efficient way.

% -------------------------------------------------
% Questions: ask the lecturer, via Moodle or email (j.guivant@unsw.edu.au)
% -------------------------------------------------

