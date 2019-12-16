% ---------------------------------------
% Example program, useful for solving Asst3, MTRN2500 S2 2018
% Author: j.guivant@unsw.edu.au

% ---------------------------------------
% e.g. run it this way: 
%      Asst3Example('.\Data\HomeC001\');

function main(folder)
clc();
if ~exist('folder','var'),
    disp('YOU must specify the folder, where the files are located!');
    disp('I assume some default folder:');
    % I assume a default value, in case the caller does not specify its
    % value.
    %folder = '.\Data\HomeC002\';
    folder = '/Users/jirayu/Desktop/MTRN2500 S2 2018 Asst3 Files/Data/HomeC002/';
    
 end;
disp('Using data from folder:');
disp(folder);
 
% load Depth and RGB images.
A = load([folder,'PSLR_C01_120x160.mat']); CC=A.CC ; A=[];
A = load([folder,'PSLR_D01_120x160.mat']); CR=A.CR ; A=[];

% length
L  = CR.N;

% Create a global variable struct to be used in multiple functions
global CCC;
CCC = []; CCC.flagPause = 0; CCC.AngleCorrection = 1; CCC.Roll = 0; CCC.Detection = 1; CCC.Restart = 0;
CCC.Pitch = -10;
CCC.r_in = 0.75;
CCC.r_out = 1.25;

%------------------
% We create the necessary plots/images/figures/etc.

% Create figure, where we will show Depth and RGB images.
figure(1); clf();

% subfigure, for Depth 
subplot(211); 
RR = CR.R(:,:,1);
hd = imagesc(RR);
ax = axis();
title('Depth');
colormap gray;
set(gca(),'xdir','reverse');


% In another subfigure, we show the associated RGB image.
subplot(212) ; hc = image(CC.C(:,:,:,1));
title('RGB');
set(gca(),'xdir','reverse');


% .. another figure, for showing 3D points.
figure(2) ; clf() ; 

ha=axes('position',[0.20,0.1,0.75,0.85]);
hp = plot3(ha,0,0,0,'.','markersize',2);

%plot filtered data
hold on
hf = plot3(ha,0,0,0,'.','markersize',2);

[x_in,y_in,x_out,y_out] = getCircleDataPoints(CCC.r_in,CCC.r_out);

innerCircle = plot3(x_in,y_in,zeros(1,numel(x_in)),'color','r');
outerCircle = plot3(x_out,y_out,zeros(1,numel(x_out)),'color','k');
hold off

axis([0,3,-1.5,1.5,-0.2,0.9]);
title('3D Cloud Points');
xlabel('X (m)');
ylabel('Y (m)');
zlabel('Z (m)');
grid on;
rotate3d on ;

% Creating UI objects and passing in circle plot handles
[RollText,PitchText] = CreateUIObjects(innerCircle,outerCircle);

% Create a handle to functions in UserAPI.m
A3D = UserAPI();

i=0;
% Periodic loop!
while 1
    tic
    while (CCC.flagPause), pause(0.3)  ; end       %stay here, if stopped.
    if(CCC.Restart)
        i = 0;
        CCC.Restart = 0;
    end
    i=i+1;
    if i>L, break ; end
    
    % Refresh RGB image, updating property 'cdata' of handle hc.
    set(hc,'cdata',CC.C(:,:,:,i));  % show RGB image
    
    RR = CR.R(:,:,i);                 % Depth image
    set(hd,'cdata',RR);             % show it.
   
    % "Processing"
    % obtain 3D points, for those pixels which are not faulty.
    iinz = find(RR>0);    %iinz=[]; <---- if empy, the function assumes ALL.
    
    [xx,yy,zz] = A3D.ConvertSelectedDepthsTo3DPoints(single(RR)*0.001,iinz);
    
    
    if (CCC.AngleCorrection)
    [xx,yy,zz] = A3D.Rotate3D(xx,yy,zz,CCC.Roll,CCC.Pitch,0); %roll,pitch,yaw; yaw is always 0
    end
    
    % Call removal fucntion
    [xx,yy,zz] = A3D.KeepPointsOfInterest(xx,yy,zz);
    
       
    % Fitler useful points
    % Find points which are inside in a vertical cylindrical ring centred at the 
    % origin (of user de?ned inner and outer radii), and are higher than 15cm in Z. Those points are then to 
    % be shown in red, while the rest of the points are shown in blue.
    
    [xx,yy,zz,xx_filtered,yy_filtered,zz_filtered] = A3D.FilterUsefulPoints(xx,yy,zz,CCC.r_in,CCC.r_out);  
    
    % If detection is checked then show red points otherwise show blue
    % points
    if(CCC.Detection ~= 1)
        Color = [0, 0.4470, 0.7410]; %default matlab light bluish color
    else
        Color = [1 0 0]; %red color
    end
    
    % Show the 3D points (update it associated plot, using its handle)
    
    % hf is the handle for filtered points to be shown in red when
    % filtering is enabled otherwise these points are shown in default blue
    % color
    set(hf,'xdata',xx_filtered,'ydata',yy_filtered,'zdata',zz_filtered,'color', Color);
    
    % hp is the handle for non-useful points. Always shown in blue
    set(hp,'xdata',xx,'ydata',yy,'zdata',zz);
    
    % Update slider textboxes to reflect current Pitch and Roll values
    set(PitchText,'String',['Pitch = ' num2str(round(CCC.Pitch))]);
    set(RollText,'String',['Roll = ' num2str(round(CCC.Roll))]);
    pause(0.099);     % freeze for about 0.1 second approximtely to achieve 10hz refresh rate
    toc
end

end

function [RollText,PitchText] = CreateUIObjects(innerCircle,outerCircle)

    global CCC;



    RollText = uicontrol('Style','text','Position',[50,50,70,20],'String',['Roll = ' CCC.Roll],'foregroundcolor','b');
    PitchText = uicontrol('Style','text','Position',[50,380,70,20],'String',['Pitch = ' CCC.Pitch]);

    RollSlider = uicontrol('Style','slider','Position',[10,50,40,150],'Callback',{@RollSliderCallBack},'Max',45,'Min',-45,'Value', CCC.Roll);
    PitchSlider = uicontrol('Style','slider','Position',[10,250,40,150],'Callback',{@PitchSliderCallBack},'Max',45,'Min',-45,'Value', CCC.Pitch);



    uicontrol('Style','checkbox','String','Angle Correction','Position',[180,0,120,20],'Callback',{@AngleCorrectionCallBack},'Value',1);
    uicontrol('Style','checkbox','String','Detection','Position',[300,0,100,20],'Callback',{@DetectionCheckBoxCallBack},'Value',1);

    uicontrol('Style','slider','Position',[370,5,80,20],'Callback',{@UpdateInnerRadius,innerCircle},'Min',0.5,'Max',1,'Value', CCC.r_in);
    uicontrol('Style','slider','Position',[455,5,80,20],'Callback',{@UpdateOuterRadius,outerCircle},'Min',1,'Max',2,'Value', CCC.r_out);
    
end

function PushButtonCallBack(~,~,x)   %same call back but check which button pressed
    global CCC;
    
    if (x==1)
       CCC.flagPause = ~CCC.flagPause; %Switch ON->OFF->ON -> and so on.
       disp(x);
       disp(CCC.flagPause);
    end
    if (x==2)
        CCC.Restart = 1;
        disp('Restart');
    end
end
function RollReset(~,~,handle)
    % Reset roll to default 0 and update roll slider value
    global CCC;
    CCC.Roll = 0;
    set(handle,'Value',CCC.Roll);
end

function PitchReset(~,~,handle)
    % Reset pitch to default -10 and update pitch slider value
    global CCC;
    CCC.Pitch = -10;
    set(handle,'Value',CCC.Pitch);
end

function PitchSliderCallBack(a,~,~)
    % Read slider value and update pitch variable
    global CCC;
    v = get(a,'value');
    CCC.Pitch = v;
end

function RollSliderCallBack(a,~,~)
    % Read slider value and update roll variable
    global CCC;
    v = get(a,'value');
    CCC.Roll = v; 
end

function AngleCorrectionCallBack(a,~,~)
    % Call back for angle correction checkbox
    global CCC;
    v = get(a,'value');
    CCC.AngleCorrection = v;  
end

function DetectionCheckBoxCallBack(a,~,~)
    % Call back for detection checkbox
    global CCC;
    v = get(a,'value'); 
    CCC.Detection = v;  
end

function [x_in,y_in,x_out,y_out] = getCircleDataPoints(r_in,r_out)
    % calculate inner and outer circles data points
    % and pass those data back to be used to update circle plots
    theta = -pi:0.01:pi;
    x_in = r_in*cos(theta);
    y_in = r_in*sin(theta);
    x_out = r_out*cos(theta);
    y_out = r_out*sin(theta);
end

function UpdateInnerRadius(obj,~,innerCircle)
    global CCC;
    CCC.r_in = obj.Value; %read current slider value
    [x_in,y_in,~,~] = getCircleDataPoints(CCC.r_in,CCC.r_out); %get datasets
    set(innerCircle,'xdata',x_in,'ydata',y_in,'zdata',zeros(1,numel(x_in))); %update plot
end
function UpdateOuterRadius(obj,~,outerCircle)
    global CCC;
    CCC.r_out = obj.Value; %read current slider value
    [~,~,x_out,y_out] = getCircleDataPoints(CCC.r_in,CCC.r_out); %get datasets
    set(outerCircle,'xdata',x_out,'ydata',y_out,'zdata',zeros(1,numel(x_out))); %update plot
end