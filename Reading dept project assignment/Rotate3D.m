%Author: Jirayu Sirivorawing z5125805

function [xx,zz]=Rotate3D(xx,zz,deg)
    %this function take the original coordinate and adjust it so that it
    %shows the correct perspective.
    rad = -deg*pi/180;
    %rotation transformation for x-coordinate
    xx = xx.*cos(rad)+zz.*sin(rad);
    %rotation transformation for z-coordinate
    zz = -xx.*sin(rad)+zz.*cos(rad)+0.2;
end