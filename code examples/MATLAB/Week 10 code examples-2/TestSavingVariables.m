 

% A small program, to show how to "save" and "load" data (variables)
% MTRN2500 - S2.2016


function TestSavingVariables()

clc();      %(just clear the console)

% We generate some variables, for this test.
A = rand(1,6);
B = [1,2,200];
C = 1000 ;

disp('1) Showing current context');
whos;
pause ;
% Here, we see how to save variables, to disk; for being used later.

%------------------------------
% Now, suppose that after some relevant processing, you decide to save 
% some results. Suppose those are in the variables A and B;
% If we want to save the variables, using the standard format in Matlab,
% we do it as follows.
% Two usual ways:
% save('GoodData01.mat','A','B');
save 'GoodData01.mat'  A B ;
% btw: Here, we decided to save A and B, but not C; in a file named
% 'GoodData01.mat'
%------------------------------

% Now we clear all the variables, from memory (destroy them)
clear all ; % or selectively "clear A B C;" in this case;

% We see: no variables do exist in this context.
disp('2) Showing current context');
whos ;
pause;          % wait for user...
%------------------------------

Z = 3000;   % I may have other variables.
% Here, we pretend that we are in the future, and we load the file.
load('GoodData01.mat');
disp('3) Showing current context');
% We see the variables we currently have in memory.
whos() ;


%AlternativeWay('GoodData01.mat')


end


function AlternativeWay(fileName)

% We load the variables (which are contained in the MAT file), to be
% organized in a structure.
X = load(fileName);
X,
% X is organized as a structure, whose fields are the variables originally 
% saved in the file!

% Now we can use them, according to our wish/needs
% We can keep them as a structure, or extract the fields again, etc.
A2=X.A;
B2=X.B;
clear X;


end
