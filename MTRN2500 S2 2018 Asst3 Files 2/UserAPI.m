% ---------------------------------------
% Assignment 3 MTRN2500
% Author: Kanadech Jirapongtanavech z5176970

function A = UserAPI()
    % Useful Functions
    A.ConvertSelectedDepthsTo3DPoints = @ConvertSelectedDepthsTo3DPoints;     %"@MyFunctionA" handle to function "MyFunctionA"
    A.Rotate3D = @Rotate3D;
    A.KeepPointsOfInterest = @KeepPointsOfInterest;
    A.FilterUsefulPoints = @FilterUsefulPoints;

end

function [xx,yy,zz] = ConvertSelectedDepthsTo3DPoints(rr,iinz)
    % Convert the raw data in a specified image frame to 3D points x,y,z
    [r,c] = ind2sub(size(rr),iinz);
    depth = rr(iinz);
    xx = depth;
    yy = depth.*(c-80)*4/594;
    zz = -depth.*(r-60)*4/592 + 0.2; %0.2m offset according to specification
    xx = xx'; yy = yy'; zz = zz';
end
 
function [x,y,z] = Rotate3D(xx,yy,zz,degX,degY,degZ)
    % Apply a rotation matrix to coordinates x,y,z
    yaw = -degZ*pi/180;     %Z
    pitch = -degY*pi/180;   %Y
    roll = -degX*pi/180;    %X

    Rm = [cos(pitch)*cos(yaw) -cos(roll)*sin(yaw)+sin(roll)*sin(pitch)*cos(yaw) sin(roll)*sin(yaw)+cos(roll)*sin(pitch)*cos(yaw);
          cos(pitch)*sin(yaw) cos(roll)*cos(yaw)+sin(roll)*sin(pitch)*sin(yaw) -sin(roll)*cos(yaw)+cos(roll)*sin(pitch)*sin(yaw);
          -sin(pitch) sin(roll)*cos(pitch) cos(roll)*cos(pitch)];%Rotation Matrix


    x = xx.*Rm(1,1)+yy.*Rm(1,2)+zz.*Rm(1,3);
    y = xx.*Rm(2,1)+yy.*Rm(2,2)+zz.*Rm(2,3);
    z = xx.*Rm(3,1)+yy.*Rm(3,2)+zz.*Rm(3,3);
end

function [xx_poi,yy_poi,zz_poi] = KeepPointsOfInterest(xx,yy,zz)
    % poi = point of interest
    % This function removes points of no interest
    poi_index = zz>0.05 & zz<1; % points of interest are points with Z value between 0.05 and 1
    xx_poi = xx(poi_index);
    yy_poi = yy(poi_index);
    zz_poi = zz(poi_index);
end

function [xx,yy,zz,xx_f,yy_f,zz_f] = FilterUsefulPoints(xx,yy,zz,r_in,r_out)
    % Find points which are inside in a vertical cylindrical ring centred at the 
    % origin (of user de?ned inner and outer radii), and are higher than 15cm in Z.
    magnitude = sqrt(xx.^2+yy.^2);
    fil_index  = magnitude>r_in & magnitude<r_out & zz > 0.15;
    xx_f = xx(fil_index);
    yy_f = yy(fil_index);
    zz_f = zz(fil_index);
    xx(fil_index) = [];
    yy(fil_index) = [];
    zz(fil_index) = [];
end