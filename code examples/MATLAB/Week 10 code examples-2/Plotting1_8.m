
clc();


% --------------------------------------
% Plots/handles, etc. 
% Jose Guivant
% Updated by Mark Whitty
% ---------------------------------------


%% ---------------------------------------
d=0.1 ; x=(0:d:100)*5*pi/100;
y = cos(x).*sin(3*x);

figure(1) ; clf(); plot(x,y);
xlabel('x (in meters)');
ylabel('F(x) (in atm)');

% return;


% There are other useful properties.
% We inspect them, using the handle of the graphic object.

figure(1) ; clf(); 
h = plot(x,y);

get(h),

% we will see, it has many interesting properties

%These are usually useful:

% Color
% LineStyle
% LineWidth

% Marker
% MarkerSize
% 
% MarkerEdgeColor
% MarkerFaceColor
% XData
% YData
% Visible
% 

% I can set many of its properties, just using "SET" 

set(h,'color',[1,.1,.7],'linewidth',2);
pause;

set(h,'marker','*','markersize',3,'MarkerEdgeColor',[0,0,1]);
pause;
set(h,'marker','none');

% We can set certain properties, for refining our figures
% OR for performing certain animations; for showing
% time varying data; in "Real-Time"

% here, some basic animation ("Oscilloscope")
L=10;
for i=1:50
 a = y(1:L) ; y(1:end-L) = y(L+1:end) ; y(end-L+1:end)=a;
 set(h,'ydata',y);
 pause(0.02);
end

%% ---------------------------------------
% we can have many, being modified dynamically,
% in the same figures or in different ones.

y = cos(x).*sin(3*x);
y2=y;
figure(1) ; clf(); 
h1 = plot(x,y,'r');
hold on;
h2 = plot(x,y2,'b');
for i=1:20,
    
    a = y(1:L) ; y(1:end-L) = y(L+1:end) ; y(end-L+1:end)=a;
    y2=y2*0.95;
    % Some synthetic "signals", for playing here.
    % Shifting one of the signals.
    % Attenuating the other one.
    
    % update both graphic objects.
    set(h1,'ydata',y); 
    set(h2,'ydata',y2);
    pause(0.2);
end




%% -------------------------------------
N=200;
x = rand(1,N);
y = rand(1,N);
figure(1) ; clf(); 
h = plot(x,y,'.b');
axis([0,1,0,1]);
for i=1:80,
    
    y=y*0.97;
    set(h,'xdata',x*abs(sin(i/80*2.1*pi)),'ydata',y);
    pause(0.05);
end

%% -------------------------------------
% also for 3D plots (1D in 3D )
N=200;
x = rand(1,N);
y = rand(1,N);
z = rand(1,N);
figure(1) ; clf(); 
h = plot3(x,y,z,'.r');
axis([0,1,0,1,0,1]);
rotate3d on;


grid on; box on;

for i=1:80,
    %x=x*0.97;     
    %y=y*0.96; 
    z=z*0.99;
    x2 = x*abs(sin(i/80*2.1*pi));
    y2 = y*abs(cos(i/80*2.1*pi));
    set(h,'xdata',x2,'ydata',y2,'zdata',z);
    pause(0.05);
end


%% -------------------------------------
% Some curves (1D), in 3D

N=1000;
a = (0:N)*5*pi/N;       % parameter

% p(a) = (x(a),y(a),z(a))
x = cos(a);
y = sin(a);
z = a/pi;

figure(1) ; clf();
h = plot3(x,y,z,'r');
axis([-1,1,-1,1,-1,5]);
rotate3d on;  

%% -------------------------------------
% Again, some curves (1D), in 3D; 
% but including some dynamic changes.

N=1000;
a = (0:N)*5*pi/N;
x = cos(a);
y = sin(a);
z = a/pi;
figure(1) ; clf();
h = plot3(x,y,z,'r');
axis([-1,1,-1,1,-5,5]);

rotate3d on;  
pause;
for i=1:100,
    set(h,'zdata',z*sin(i*pi/20));
    pause(0.05);
end    

%% -------------------------------------
% Again, some curves (1D), in 3D; 
% but including some dynamic changes, 
% and more than just one.

N=1000;
a = (0:N)*5*pi/N;
x = cos(a);
y = sin(a);
z = a/pi;

figure(1) ; clf();

h = plot3(x,y,z,'r');
hold on;
h2 = plot3(x,y,z*1.1,'b.');

axis([-1,1,-1,1,-5,5]);

rotate3d on;  
pause;

for i=1:100,
    w=z*sin(i*pi/23);
    set(h,'zdata',w);
    set(h2,'xdata',y.*w,'zdata',w); % some crazy thing...
    
    pause(0.05);
end  


%%  ======================================
%  SURFACES  (2D in 3D)
%  Z=Z(X,Y)  OR   (X(a,b),Y(a,b),Z(a,b))

N=80; M=100;
x = (0:N-1);
y = (0:M-1);
x=x*5*pi/N;
y=y*2*pi/M;
[xx,yy] = meshgrid(x,y); % ( we will see some easy cases using it)

Z = sin(xx).*cos(yy);

figure(1) ; clf();
h=surf(xx,yy,Z);
% surf(xx,yy,Z,colors);  % you can specify the color, for each Z(i,j)

rotate3d on;  
axis([ x(1),x(end),y(1),y(end),-2,+2]);
pause;

for i=1:100,
    set(h,'zdata',Z.*cos(xx*i/40));
    pause(0.05);
end  

%BTW: you may also change 'xdata','ydata' (simultaneously)
% (next example)

%% -------------------------------
% ALSO: surfaces, 2D parameterized.
%  ( x(a,b),y(a,b),z(a,b) )

N=80; M=100;
a = (0:N);
b = (0:M);
a=a*5*pi/N;
b=b*2*pi/M;
[A,B] = meshgrid(a,b); 

Z = sin(A).*cos(B);

figure(1) ; clf();
h=surf(cos(A),sin(B),Z);
% surf(..,..,..,colors);  % you can specify the color, for each Z(i,j)

axis([ -1,1,-1,1,-1,+1]);
rotate3d on;  
pause;


for i=1:100
    set(h,'xdata',cos(A*i/80),'zdata',Z.*cos(A*i/80)); 
    %(non sense!, but beautiful)
    pause(0.1);
end  

%% ---------------------------------------------------
% Using "AXES"
% We can define axes (where to plot), 
% at any place in any figure.

N=200;
figure(1) ; clf();

x=rand(N,1);
h1 = plot(x,'b');
hold on;
h2 = plot(rand(N,1),'r');

% Here, we create a context, where to plot.
ha = axes('position',[0.6,0.6,0.35,0.35]);

h3 = plot(ha,x,'m');  % I instruct PLOT to use that context

pause;

for i=1:50
    x=rand(N,1);
    set(h1,'ydata',x);
    set(h2,'ydata',0.2*rand(N,1));
    set(h3,'ydata',x);
    pause(0.1);
end  


%% ---------------------------------------------------
% EXAMPLE USING "AXES"
% We can define axes (where to plot), at any place in any figure.

% we create a figure.
figure(1) ; 
clf();          % I clean it, just in case.

% now, We define some AXES
% position = RECT = [x0,y0,DX,DY], normalized to [0,1]
ha1 = axes('position',[0.6,0.6,0.35,0.35]);
ha2 = axes('position',[0.1,0.1,0.4,0.3]);
ha3 = axes('position',[0.1,0.5,0.4,0.3],'box','on');
ha4 = axes('position',[0.55,0.1,0.4,0.3],'box','on');


% now, we do what we want to do.
N=200;
x=rand(N,1);
h1 = plot(ha1,x,'b');  % <------ We tell plot to plot in a particular axes insance.

h2 = plot(ha2,rand(N,1),'r');  %<--- this one, in a different one.

% and so on..
h3 = plot(ha3,x,'b');
h4 = plot(ha4,0,0,'+g');
ht4 = title(ha4,'.');
pause;

% now some action.
for i=1:100
    x=rand(N,1);
    set(h1,'ydata',x);
    set(h2,'ydata',0.2*rand(N,1));
    set(h3,'ydata',x);
    
    % E.g.: a random number of randon numbers...
    NP = floor(20+50*rand(1,1));
    xx=rand(NP,1);
    yy=rand(NP,1);
    set(h4,'xdata',xx,'ydata',yy);
    set(ht4,'string',sprintf('%d random points',NP));
    
    pause(0.1);
end  

%% ---------------------------------------------------
% EXAMPLE USING "AXES"
% of course, we can use other graphical objects
% e.g. IMAGES 

% as usual, we create a figure.
figure(1) ; 
clf();          % I clean it, just in case.

% Now, We define some AXES
ha1 = axes('position',[0.6,0.6,0.35,0.35]);
ha2 = axes('position',[0.1,0.1,0.4,0.3]);
ha3 = axes('position',[0.1,0.5,0.4,0.3],'box','on');
ha4 = axes('position',[0.55,0.1,0.4,0.3],'box','on');


% Now, we do what we want to do.
N=200;
x=rand(N,1);
h1 = plot(ha1,x,'b');  % <------ We tell plot to plot in a particular axes insance.
h2 = plot(ha2,rand(N,1),'r');  %<--- this one, in a different one.

% And so on..
% load our data..

load('C:\Users\z3099851\Google Drive\Teaching\MTRN2500 S2 2018\Assignment 3 + Quiz 3\Data\HomeC001\PSLR_C01_120x160.mat'); 

% create an IMAGE object, and we preserve its handle.
h3 = image(CC.C(:,:,:,1),'parent',ha3); 
%'parent' <--- This property specifies the AXES to be used

h4 = plot(ha4,0,0,'+g');
ht4 = title(ha4,'.');
pause;

% now some action.
for i=1:100
    
    % HERE! update the image content.
    set(h3,'cdata',CC.C(:,:,:,i) );
      
    % the rest, is as the previous example..
    x=rand(N,1);
    set(h1,'ydata',x);
    set(h2,'ydata',0.2*rand(N,1));
    
    NP = floor(20+50*rand(1,1));
    xx=rand(NP,1);
    yy=rand(NP,1);
    set(h4,'xdata',xx,'ydata',yy);
    set(ht4,'string',sprintf('%d random points',NP));
    
    pause(0.1);
end  
