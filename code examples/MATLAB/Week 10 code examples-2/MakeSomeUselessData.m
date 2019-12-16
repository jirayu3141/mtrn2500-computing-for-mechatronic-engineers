
% Example, MTRN2500, Matlab Part.

% Basic function, to show how the data, which we use in the lecture,
% (although those images were obtained from a real camera)
% was saved in a structure.
% So, in place of having many variables for containing the diverse
% components of interest, we "pack" them in just one variable, which has 
% multiple fields, of/for diverse types/purposes.

% We will see, in week 10, how to define/use arrays of structures, cells and
% classes.
% For the moment, we just use structures in a basic way.

function ok=MakeSomeUselessData(L,fileName)

if (L<1), ok=-1 ; return ; end;     
if (numel(L)~=1), ok= -2; return ; end;
% we should usually check if the request does make sense.

% Additional sanity checks could be considered. 

L = min(150,L);      %and also avoid crazy things; just by assuming someting.


% We create a empty variable (or destroy its contents, if "Co" already exists)
Co =[] ;            

% Now, we "add" fields to the variable.

Co.L = L;       % how many images?

% Here, we just generate some random imagery.
% (sure, it will look like pure noise, when we play it back.)
Co.RGBs = randi(50,   120,320,3,L,   'uint8');

% we also pretend measured the sample times, etc. 
Co.t = 1000*uint32(1:L);        % sample times.
Co.cx = uint32(1:L);            % image number

% some extra info (however, we do not
% really use it, in our processing, later.)
e=[];
e.str    = 'Some synthetic random data, for MTRN2500.';
e.help1  = 'No help, today.';
e.help2  = 'Ask the lecturer, tomorrow.';
e.Author = 'Dr. Zoidberg.';
e.sensor = 'RGB-D, Carmine Primesense, model 1.082';
e.dateCreation  = date();
e.tm     = 1000*uint32(1:L);
e.t64    = e.tm;
e.t64_0 = uint64(0);

Co.extra = e;

clear e;            
% No real need to clear it; the function is almost ending.
% However, we usually release/destroy the variables not needed anymore; 
% in particular, if those are big.


% save "the experimental data", for eventual post-processing.
save(fileName,'Co');
% You may save many variables, in the same file.
% (use the HELP, for more details about "save()".)
disp('Success!');

%done!
ok=1;
end
