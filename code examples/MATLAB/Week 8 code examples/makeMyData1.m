
% ----------------------------------------------------
% Basic function, for creating some useful data; for lecture 1.
% For Lecture 1, Matlab.MTRN2500, S2.2016 
% Questions: ask lecturer, via Moodle or by email (j.guivant@unsw.edu.au)
 
% Note for students (NfS): This piece of code is needed but it 
% is not relevant for Lecture 1.


% ----------------------------------------------------

function M = makeMyData1()
    [Mx,My] = meshgrid( (1:8)+10,((1:8)-1)*10); 
    M = Mx+My;
end

% ----------------------------------------------------


