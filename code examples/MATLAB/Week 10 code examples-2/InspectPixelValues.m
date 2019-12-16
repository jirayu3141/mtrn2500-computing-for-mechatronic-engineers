
% Small program for inspecting RGB values of pixels.
% Useful, for "feeling" the colors, to define rules, later, for color detection. 

% By Jose Guivant - For MTRN2500 - S2.2015

function InspectPixelValues()     
    A = imread('test001.jpg');  
    ShowValueOfPixels(A);
end


function ShowValueOfPixels(A)
    figure(12); clf();
    image(A);
    ylabel('click here to leave the loop');

    while 1,
        zoom on;                % enable zoom 
        title('Press a key for enabling mouse selection..');
        pause;
                               % pause till the use decides.
                                % in addition, he/she may zoom in/out
        title('Now, select a pixel');
        pp=ginput(1);           %get position of mouse click from user
                                %the user should click some point in the
                                %figure, by using the mouse
        
        pp =round(pp);          %round to nearest integer.
        
        ax=axis();             
        % get the current region being shown in the figure
        if ((pp(1)<ax(1))||(pp(1)>ax(2))||(pp(2)<ax(3))||(pp(2)>ax(4))), 
            disp('Mouse hit outside the image, it means you want to leave. BYE');
            break ;         % if the point coordinate is outside the axis ==> BYE
                            % I used that way to letting the funciton to
                            % know the intention to leave the loop, by the
                            % user
        end;
        
        % use the obtained 2D point to point to the pixel
        c = A(pp(2),pp(1),:);
        
        % tell the use about the RGB value of the pixel
        fprintf('Pixel (h=%d,v=%d) RGB values =[%03d][%03d][%03d]\n',pp,c);
    end;
    ylabel('');
    title('DONE');
    
return ;
end
% function AskUserToContinue()
%     disp('Phess a key to continue...');
%     pause;                 % wait for user, to continue.
% end
