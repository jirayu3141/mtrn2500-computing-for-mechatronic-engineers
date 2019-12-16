
% MTRN2500

% TODAY: CELL arrays, Structs, Struct arrays, intro to OOP (Object Oriented Programming) in Matlab. 

% These pieces of code are used to explain capabilities, syntax, concepts.

% Questions: Ask the lecturer, via Forum or email (j.guivant@unsw.edu.au)

%------------------------------------------------------
%CELLS

% By using cells, we can pack different "things"; usually done dynamically.

% example, creating a cell array
ccc = { 2,3,[3,4,5],zeros(3,3),'Hello colleagues',uint32([3,3,3])} ;
% Wee see how it looks.
disp(ccc);

%......................................
% Selecting a subset of elements of a cell array.
% parentheses, "(...)", are used for generating subsets, as arrays.
% braces "{...}" for extracting ( or addressing ) contents.

c5 = ccc{5};          % Using "{index}": actual content in individual cell #5, in array of cells.


% extracting part of the array (using  "(indexes)" )
cccPart = ccc(2:5);   % subset of ccc (another cell array), whose elements are a subset
                      % of the original array.
disp(cccPart);
                      
% "ccc{2:5}" 
% contents of a subset; it could be used in particular cases (we see it later)
% We cannot do "m=ccc{4:5} because those contents are not usually compatible.

% Again, using indexes:
cccPart = ccc([1,3,5]);
disp(cccPart);


% Relevant: note the difference between using "(index)" and "{index}"
x = ccc{3};
y = ccc(3);

% show the class of variable/item, to appreciate differences. 
class(x),
class(y),

z1=x+10;   % this is OK, because x is a vector.
%z2=y+10;   % this is wrong, because y is a cell. (there is no defined addition operation for cells)

%......................................
% Items, of an array of cells, can be Function handles.
% here I redefine element 4 of ccc.
ccc{ 4 } = @MyFunctionB01  ;   
% In this case, I have a function defined in MyFunctionB01.m, so I can use it.
ccc([4,5,6]) = {@MyFunctionB01,@MyFunctionB01,@MyFunctionB02}  ;

%I can use those "function pointers"
% As (I know) the function is implemented as "function r=MyFunctionB01(a)",
% I use it this way:
r=ccc{4}(100); disp(r);


%......................................
% Items of a cell array can also be cell arrays.  (we can nest "things")
ccc = { 2, 3, [3,4,5], zeros(3,3), 'Hello colleagues',  {'3333',[4,5,6]}   } ;

% So we may double address the contents; like in this example, in which we intend to address
% element 2 of the cells array contained by element 6 of ccc.
x= ccc{6}{2};

% Question. What are the effects of the following operations:
x1= ccc{6}{2};
x2= ccc{6}(2);
%x3= ccc(6){2};      %<----valid? 
%x4= ccc(6)(2);      %<----valid?



% Modifying individual cells
ccc{1} = 1111;             % <--- write content of cell #1
ccc(2) = {2222};           % <--- set element of array of cells, using another cell (a "scalar" cell). 
% both have the same effect. 


%------------------------------------------------------
% we can selectively modify contents of elements of the cell arrays

% suppose we had this cell array:
ccc = { 2, 3, [3,4,5], zeros(3,3), 'Hello colleagues',  {'3333',[4,5,6]}   } ;
% and we want to modify the vector  [3,4,5] to became [3,40,50]

% the current value is:
disp(ccc{3});

% ..now we modify it.
ccc{3}(2:3) = [40,50];

% so, the current value is now:
disp(ccc{3});
%...........................

%again, similarly,
disp(ccc);
ccc{5}(1:5) = 'Bye, ';
disp(ccc);
%------------------------------------------------------

% 2D cell arrays (yes, arrays of cells can be multidimensional) .
ccc = { 2,3,[3,4,5] ; zeros(3,3),'Hello colleagues',{'wewwe3333',3} } ;   
s =ccc{2,2}; 
x=ccc{2,3}{1};   %< -- double addressing level, because element is a cell array as well. 

% again, accessing its content.
str=ccc{2,2}(1:5) ; disp(str);


%------------------------------------------------------
% Creating empty cell arrays, of any dimension;
ccc = cell(2,4);disp(ccc);

% We can use it immediately, 
% e.g., in this case, using 2D indexing (because it is a 2D cell array),
ccc{1,4} = 'here, cell 1,4'; disp(ccc);

% ..or even using linear indexing (like with any Matlab's array).
ccc{8} = 'here, cell 2,4'; disp(ccc);


%We may use indexes, as we usually do with other n-D variables.
ccc = cell(2,5);     % here we create 2x5 cells.   

% here we set certain elements to point to the same cell/content (using linear indexes).
ccc(2:4) = {444} ;   
disp(ccc);



% again:
ccc([5,6,1]) = {200,[3,30,300],'good day'} ;
disp(ccc);

% using 2D indexing
ccc(:,5) = { 'hello' };
disp(ccc);


ccc(:,4) = { 'hello';'bye' };
disp(ccc);


%etc, etc...
ccc([7,8,9]) = ccc([2,1,1]);
disp(ccc);


% I can extract many elements (which may be of different types), assigning
% contents to variables.
[a,b,c] = ccc{ [ 1,4,6] };

% same effect would be obtained by this:
indexes = [1,4,6];
[a2,b2,c2] = ccc{ indexes+1 };


% note:
% which is different to creating a subset of cells; e.g.
A = ccc( [ 1,4,6] );  % < --- in this case, A is assigned to be a cell array, whose elements are taken from ccc 



% we can address certain elements of a cell array, and assign values to
% them by using another cell array.
ccc([1,4,6]) = {  1 , 'hello ffgffgf' , [3,3] } ;
ccc([1,4,6]) = ccc([3,4,6])

iiL = sub2ind(size(ccc),[1,2,1,2],[1,2,3,4]);
ccc(iiL) = {'here'} ;

iiL = sub2ind(size(ccc),[1,2,1,2],[1,2,3,4]);
ccc(iiL) = {'here1','here2','here3','here4'} ;

ccc(iiL) = {[]} ;

cNew = {  2,3,ccc{[1,4,6]},'last' } ;
% which is different result to "cNew = {  2,3,ccc([1,4,6]),'last' }" ;
% this one would have 4 elements, where element #3 would be a cell array itself. 


%----------------------------------------------------------
%More about accessing data from a cells array.

% "cell2mat()"
ccc = { [1;11],[2;22],[3;33]; 'MTRN2500','MTRN4010','MTRN4110'} ;
M = cell2mat(ccc(1,:));
% ONLY if the addressed cells' contents are consistent: type and shape.

%......................
% E.g. this case would also be valid: (like concatenation cases)
ccc = { [1;11],  [[2;22],[2;22]],  [3;33]; 'MTRN2500','MTRN4010','MTRN4110'} ;

%......................


%But these cases would FAIL: (Why?)
ccc = { [1;11],[2;22],int32([3;33]); 'MTRN2500','MTRN4010','MTRN4110'} ;
%M = cell2mat(ccc(1,:));  % All contents of the input cell array must be of the same data type.

ccc = { [1;11],[2;22],[3;33;0]; 
    'MTRN2500','MTRN4010','MTRN4110'} ;
%M = cell2mat(ccc(1,:)); % Dimensions of arrays being concatenated are not consistent.


% But this one, would be valid again. Why?
ccc = { [1;11],[2;22],[3;33;0]; 'MTRN2500','MTRN4010','MTRN4110'} ;
M = cell2mat(ccc(1,  1:2 ));    %<--- 1:2 


%----------------------------------------------------------


% "Inefficient" but easy: Using FOR/WHILE loops
for i=1:numel(ccc)
    x = ccc{i};  x,  %( and do something with x..)
end    

for i=1:3
    x = ccc{2,i};  x,
end 



% 
ccc=cell(3,5);
for i=1:3
    s = sprintf('Hello%d',i);
    ccc{2,i}=s;
end;  



% This is also valid, but forces Matlab to resize the array, many times (inefficient!).
% (writing to an "out-of-range" address results in resizing the array)
ccc=cell(0,0);
for i=1:3
    s = sprintf('Hello%d',i);
    ccc{12,i}=s;
end;  


%----------------------------------------------------------


% more examples;

% Nesting cell arrays.
ccc = { [1;11],[2;22],[3;33;0]; 'MTRN2500','MTRN4010','MTRN4110'} ;
ccc = { ccc,ccc(1,:)} ;   % <--- effect??  
% creates a cell array, of 2 cells, each of them being a cell array by itself (nested cell arrays). 



% You may dynamically expand it (as we usually can do for other types of matrixes.)
ccc = { [1;11],[2;22],[3;33;0]; 'MTRN2500','MTRN4010','MTRN4110'} ;
ccc(:,end+1) = ccc(:,1) ;


% and again...
ccc(:,end+1) = {[];[]} ;
% in this case, using empty cells.



% or this way, concatenating. It is really explanding the cell array.
ccc = [ccc,{'rrrrrr';[123,44]}];     % note that it is not ccc = {ccc,{[];[]}}; 


%however, this one would fail; why?
%ccc = [ccc,{[],[]}];   
%answer: shape of added part.


% what do the next lines mean?
ccc2 = ccc(:, 1:2 ) ; 
ccc3 = ccc(:, [1,1,3] ) ; 

% we have a look..
disp(ccc2);
disp(ccc3);

% ==========================================================
% ==========================================================


% structs / arrays of structs


% we can define a structure, dynamically, at run time.
% There are different ways to do it.


% Here, defining a struct and an instance of it (1x1: scalar) 
s1 = struct('Temp',[100,120],'Pressure',1000);
s2 = struct('Temp','cold day','Pressure',1000);

% we can define it, without even filling its fields
s = struct('Temp',[],'Pressure',[]);


% and later, assign contents
disp(s);
s.Temp = 100;
disp(s);

%...............................

% we can create an array of instances of the same struct.
sA = struct('Temp',{[100,120],99} ,'Pressure',{  1000,1010});
% note: we use CELLS for specifying the content of the multiple elements of each field.

% note: lenghts of the cells arrays must be identical.
% Except if we use an scalar in one of them; so the VM does assume the same value for
% all instances.
sA = struct('Temp',{[100,120],99} ,'Pressure',33);


% cells can be higher dimensional.
sA = struct('Temp',{ [100,120],99;  5,'cold'} ,'Pressure',{ 1000,1010 ; 0,1 });
% here, we would produce a 2x2 struct array.



%BTW: we can inspect the size, etc.; as usual.
numel(sA),
% and reshape it.
sA = reshape(sA,numel(sA),1);
% and use linear indexes and subscripts
sB = sA([1,3,4]);

% .........................................
% we can extract the values of one field for all the elements of the array
temps = {sA.Temp};
% Note: they need to BE organized as an array of cells (because there is not
% certainty that  they will be of the same type/size)
% similarly, for selected subsets, via indexes.
temps = {sA([1,3]).Temp}; disp(temps);


% alternatively, we can assign to individual variables;
[tA,tB]= sA([1,4]).Temp;
% of course, we neeed to know how many.


% .....................................................
% Modifying the struct definition.

% We can add fields at any time, dynamically:
sA(1).etc = 'what?';
% All the elements of the array will have now that field as well; however 
% those no addressed here will be empty, (i.e. =[] )
% (this would happen in cases where the field does not previously exist)


%There are more Matlab's built-in functions, for modifications of the structure definition (removing fields, etc.) 

%The names of fields can even be decided dynamically!
%E.g.; here we add three fields
for i=1:3,
    name = sprintf('Here_%d',i);
    sA(1).(name)='' ; 
end;

for i=1:3,
    name = sprintf('ETC_%d',i);
    s1.(name)='' ; 
end;



%.............................................
% we can use an array of cells for initializing an array of structs.
% Using "cell2struct()" ;

ccc = {   111,1200,[20,22] ; 'Japan','India','here'} ;
sA = cell2struct(ccc,{ 'Population','Nation' },1 );
% structArray = cell2struct(cellArray, fields, dim )
% "dim" specifies the dimension used to navigate through the fields.
% "dim=1" means that field#1 is associated to row#1, and so on.

sA.Population,
sA.Nation,

% other useful functions:
%   "strcut2cell"
%   "iscell" / "isstruct" 

%.............................................

clear sA S; 
% Another way for creating structs.
% Scalar struct 
S=[] ; S.x = 1234; S.y = [2,2] ;

% Here I force Matlab to create an array of 10 elements, of class "S"
sA(10)=S;
% Elements 1 to 9 would be empty instances of the struct.

% get an array of cells.
xx = { sA(:).x };
% we need to use cells, because the instances of the field "x" can be
% anything (i.e. not the same class and size)

% valid, but risky:
cell2mat(xx),

x10 = xx{10} ;

% more examples and discussion in class.
% ........................................................





