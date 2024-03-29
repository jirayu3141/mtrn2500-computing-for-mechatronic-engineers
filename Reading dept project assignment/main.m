% ---------------------------------------
% Asst3, MTRN2500 S2 2018
% Author: j.guivant@unsw.edu.au
% Editied by: Jirayu Sirivorawing z5125805
% ---------------------------------------

function main(folder)
clc();
if ~exist('folder','var'),
    disp('YOU must specify the folder, where the files are located!');
    disp('I assume some default folder:');
    % I assume a default value, in case the caller does not specify its
    % value.
    folder = '.\Data\HomeC002\';
    %folder = '/Users/jirayu/Desktop/z5125805 _a2/Data/HomeC002/';
    
end;
disp('Using data from folder:');
disp(folder);
 
% load Depth and RGB images.
A = load([folder,'PSLR_C01_120x160.mat']); CC=A.CC ; A=[];
A = load([folder,'PSLR_D01_120x160.mat']); CR=A.CR ; A=[];

% length
L  = CR.N;

% Some global variable, for being shared (you may use nested functions, 
% in place of using globals).
global CCC; 
CCC=[]; CCC.flagPause=0; 

% We create the necessary plots/images/figures/etc.

% Create figure, where we will show Depth and RGB images.
figure(2); clf();

% subfigure, for Depth 
subplot(211) ; 
RR=CR.R(:,:,1);
hd = imagesc(RR);
ax=axis();
title('Depth');
colormap gray;
set(gca(),'xdir','reverse');

% In another subfigure, we show the associated RGB image.
subplot(212) ;
hc = image(CC.C(:,:,:,1));
title('RGB');
set(gca(),'xdir','reverse');

% .. another figure, for showing 3D points.
figure(4) ; clf() ; 

ha=axes('position',[0.20,0.1,0.75,0.85]);
hp = plot3(ha,0,0,0,'.','markersize',2) ; 
axis([0,3,-1.5,1.5,-0.4,0.9]);
title('3D');
xlabel('X (m)');
ylabel('Y (m)');
zlabel('Z (m)');
grid on;
rotate3d on ;

% Some control buttons (you may define extra buttons, for other purposes)
uicontrol('Style','pushbutton','String','Pause/Cont.','Position',[10,1,80,20],'Callback',{@MyCallBackA,1});
uicontrol('Style','pushbutton','String','ETC','Position',[90,1,80,20],'Callback',{@MyCallBackA,2});
% .. and one slider, and 1 checkbox.
uicontrol('Style','slider','Position',[10,50,40,150],'Callback',{@MyCallBackB,1});
uicontrol('Style','checkbox','Position',[20,250,30,50],'Callback',{@MyCallBackForCheckBox1});

i=0;
% Periodic loop!
while 1,
    tic
    while (CCC.flagPause), pause(0.3)  ; end	%stay here, if stopped.
    i=i+1;
    if i>L, break ; end;
    % Refresh RGB image, updating property 'cdata' of handle hc.
    set(hc,'cdata',CC.C(:,:,:,i));  % show RGB image
    RR=CR.R(:,:,i);                 % Depth image
    set(hd,'cdata',RR);             % show it.
    % "Processing"
    % obtain 3D points, for those pixels which are not faulty.
    iinz = find(RR>0);    %iinz=[]; <---- if empy, the function assumes ALL.
    %convert depth to 3D points
    [xx,yy,zz] = ConvertSelectedDepthsTo3DPoints(single(RR)*0.001,iinz);
    %correct perspective of the points
    [xx,zz]=Rotate3D(xx,zz,-10);
    % Show the 3D points (update it associated plot, using its handle (in "hp") )
    set(hp,'xdata',xx,'ydata',yy,'zdata',zz);
    pause(0.1);     % freeze for about 0.1 second; approximtely.
    toc
end

end

% ---------------------------------------
% Callback function. I defined it, and associated it to certain GUI button,
function MyCallBackA(~,~,x)   
    global CCC;
        
    if (x==1)
       CCC.flagPause = ~CCC.flagPause; %Switch ON->OFF->ON -> and so on.
       disp(x);disp(CCC.flagPause);
       return;
    end;
    if (x==2)
        disp('you pressed ETC!');
        return;
    end;
    return;    
end

% ...............................................
% I associated the following function, as a callback function for one slider control.
% Each time a new value is set, in the slider, our function is called
function MyCallBackB(a,~,~)   
    
    %  When the system calls our callback function,
    %  it offers us the handle of the slider object itself, through the argument
    %  "a"
    v = get(a,'value');     % the property "value" is the current
                            % value of the slider (position of the selector)
    % You may use it to set the value of certain relevant variable,
    % in your program.
    % Here, I just print its value, for testing purposes.
      disp(v) ;
    
    % BTW: the object ("a"), has many other properties; you may inspect them.  
    return;    
end
% ---------------------------------------
% I associated this function, as a callback function for one CheckBox.
% Each time the state of the checkbx is modified, our function is called
function MyCallBackForCheckBox1(a,~,~)   

    %  when the system calls our callback function,
    %  it offers us the handle of the object, through the argument
    %  "a"
    v = get(a,'value');     % the property "value" is the current
                            % value of the checkbox object.
    disp(v) ;
    % You may use it to set the value of certain relevant variable,
    % in your program.
    % Here, I just print its value, for testing purposes.
    
    
    % BTW: the object ("a"), has many other properties; you may inspect them.  
    return;    
end


