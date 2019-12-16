%Author: Jirayu Sirivorawing z5125805

function [xx,yy,zz] = ConvertSelectedDepthsTo3DPoints(rr,iinz)
    %this function covert depth values and put them into x,y,z coordinates
    %filter points that are useful into row and column
    [r,c] = ind2sub(size(rr),iinz);
    %data of useful points (pixels that are not faulty)
    depth = rr(iinz);
    %these formula are given in the description sheet
    xx = depth;
    yy = depth.*(c-80)*(4/594);
    zz = -depth.*(r-60)*(4/592);
end

