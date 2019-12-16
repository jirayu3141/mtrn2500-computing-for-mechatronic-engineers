
% This example shows how to use "indexes" for accessing multidimensional 
% variables.
% (We will use indexes, intensively, for efficiently solving our project, to be released soon)

% By Jose Guivant - For MTRN2500 - S2.2015


function RunExamples1(selector)
if nargin<1, 
    disp('No argument has been specified. BYE');
    return ;  
end;

x=selector(1);  
% I propose the input argument "selector" for specifying the example to be tested.
% We expect an scalar, but just in case: we get the first element.

% I may destroy certain variables if I am sure I do not need them anymore
% e.g. doing "selector=[];"  OR  "clear selector;"
% It is a good practice, if those are big!.

% Now, I use the value of "x" for knowing what the caller wants me to do.
switch(x)
    case 1
        Example1() ;
        return ; % I may do "return" here, if I want the function to end here.
        
    case 2
        Example2() ;
    case 3
        Example3() ;
    case 4
        Example4() ;
    case 5
        Example5() ;
    case 6
        ShowColorTables();
    
    otherwise,    
        disp('what???');
end;

end
%------------------------------------

% Example 1
function Example1()
 
 [aa,yy]=GetSomeData1();    %get some 1D data, to play.
  
 ii = find(yy>0.7)  ;       % <========== RELEVANT!  
 % infer indexes of elements yy(i) that do satisfy that "yy(i)>0.7"
 
 % Create a new figure, ( and clear it, just in case it does already exist)
 figure(1) ; clf() ;    
 plot(aa,yy,'c');       % Plot data, in cyan color.
                        % Do "help plot" for details about this function.

 AskUserToContinue();   % I made this function. ( Have a look.

 
 
 hold('on') ;              % set the figure to accept more plots, preserving previous  ones
 plot(aa(ii),yy(ii),'b.');      % <========== RELEVANT!   USING INDEXES
 AskUserToContinue();   % I made this function. ( Have a look.
 yy(ii)=0.71;                   % <========== RELEVANT!   USING INDEXES
 plot(aa,yy,'r.');      % plot the modified data, by using red points
 
                        % some labels, etc.
 xlabel('argument (degrees)');
 ylabel('function value');
 title('Test01');
end 

function Example2()
 
 [aa,yy]=GetSomeData1();
 ii = find( (yy>0)&(yy<1.5) )  ; % similar to example#1, but specifying
 % a condition, a bit more complicated than that of Example1.
 % ^ ========= RELEVANT!   OBTAINING INDEXES
 
 figure(1) ; clf() ;    
 % create a new figure (and clear it in case it already exists) 
 plot(aa,yy,'c');  
 
 AskUserToContinue();   % wait for user,...
 
 hold('on');                % allow more plots, preserving previous  ones
 plot(aa(ii),yy(ii),'b.');  % <========== RELEVANT!   USING INDEXES
 
 AskUserToContinue();% wait for user,...
 yy(ii)=yy(ii)+0.2;         % <========== RELEVANT!   USING INDEXES
 plot(aa,yy,'r.');
 
 xlabel('argument (degrees)');
 ylabel('function value');
 title('Test02');
end 

function Example3()
 
 [aa,yy]=GetSomeData1();
 ii = find( (yy>0)&(yy<1.5))  ;     % OBTAINING INDEXES, of elements of interest
 
 figure(1) ; clf() ;    
 % create a new figure, and clear it if it was previously created 
 subplot(211);          % divide figure in subregions where to plot.
                        % ask for help: "help subplot", for details.
 plot(aa,yy,'c');  
 
 hold('on') ;              % enable for more plots, preserving previous  ones
 plot(aa(ii),yy(ii),'b.');
 yy(ii)=yy(ii)+0.2;
 plot(aa,yy,'r.');
 ylabel('function value');
 title('Test03');
 
 subplot(212);
 plot(aa(ii),yy(ii),'r.');
 xlabel('argument (degrees)');
 
 
end 

%-------------------------------------------
% how to find/identify the elements of a matrix (or any multidimensional matrix)
% that do satisfy certain condition.
% And how to manipulate their values, if desired.

function Example4()

% For our test, we create some 2D data.
A=GetSomeData2();

figure(1) ; clf();
imagesc(A);     % show/visualize a 2D matrix by using an image. 

colormap gray;  %specify the color scheme to be used.

AskUserToContinue();% wait for user,...


% we "detect" the elements of the matrix that meet certain condition, e.g.
% (A(i,j)>0.3)&(A(i,j)<0.6)
ii = find((A>0.3)&(A<0.6));
A(ii)=0;        % Modify them (here I just make them = 0 )
imagesc(A);     % show a 2D matrix by using an image.
% elements forced to be =0; should look BLACK
% (in the color scheme being used)

end 

function Example5()
 

% For our test, we create some 2D data.
A=GetSomeData2();

% we show it.
figure(1) ; clf();
imagesc(A);     % show a 2D matrix by using an image. 
colormap gray;  %specify the color scheme to be used.

AskUserToContinue();% wait for user,...

% we "detect" the elements of the matrix that meet certain condition, e.g.
% (A(i,j)>0.3)&(A(i,j)<0.6)
ii = find((A>0.3)&(A<0.6));     % OBTAINING INDEXES, of elements of interest.
                                % ATTENTION: "ii" is an array, for
                                % accessing "A" linearly. To be explained
                                % in class.

fprintf('%d elements do satisfy the condition\n',numel(ii));
if numel(ii)>0
    A(ii)=0;        % We modify them, e.g. make them =0        
    imagesc(A);     % show the new 2D matrix, again,  by using an image.
    
    % "A(ii)" , where "ii" is a vector: We are accessing the matrix "A" using LINEAR
    % indexes.
    
    % and we show some extra info, e.g. show points where the elements were
    % modified.
    hold('on');
    
    [i1,i2]=ind2sub(size(A),ii);  
    % convert linear indexes into multi dimensional indexes.
    % (in class, we discuss about how the data is located in memory.)
    
    plot(i2,i1,'*');
end;

end 

% just for showing how the colors look (look-up table)
function ShowColorTables()
    x = (0:100)/100 ; % show 101 values, linearly increasing.
    figure(1) ; clf();
    imagesc(x);
    colormap('gray');       %choose color scheme, for visualization.
    AskUserToContinue();    % wait for user,...
    colormap('jet');        % just change the colormap. Same values would look different.
    
    % do "help colormap" for info
    
end


%-------------------------------------------
% Some auxiliary functions, I made for this example program.

function [x,y]=GetSomeData1()

 x = (0:200)*2*pi/200 ; 
 % 201 elements, regularly spread from 0 to 2*Pi
 y=2.7*sin(x).*cos(3*x);  % use ".*" for elementwise operation
 x=x*180/pi;
 end

function M=GetSomeData2()
    M = rand(5,10); M(1,1)=0; M(1,2)=1;
end

function AskUserToContinue()
    disp('Press a key to continue...');
    pause;                 % wait for user, to continue.
end
