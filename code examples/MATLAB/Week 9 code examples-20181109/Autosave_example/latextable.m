function lattable=latextable(arr,colformat,caption,label)
% lattable=LatexTable(arr,colformat)
%
% Produces latex table from matlab cell array
%
% By:
% -------------------------------------------------------
% Peter Kjaer Willendrup, Cand. Scient. (Physics)
% 
% Copenhagen University Hospital
% Neurobiology Research Unit
% 
% Phone: +45 35456721
% email: willend@nru.dk
% -------------------------------------------------------
% From:
% http://www.mathworks.com/matlabcentral/newsreader/view_thread/26818

  sarr=size(arr);
  % loop over each colum to make header:
  header='\begin{table} \footnotesize \centering \caption{';
  header = [header caption '} \label{' label '}\begin{tabular}{'];
  for j=1:sarr(2)
    if nargin==1 % Is column format defined?
      header=[header 'c'];
    else
      header=[header colformat{j} ''];
    end
  end
  lattable=[header '}'];
  lattable=strvcat(lattable,'\toprule');
  % loop over each row:
  for j=1:sarr(1)
    row=parseentry(arr{j,1});
    % loop over each column
    for k=2:sarr(2);
      if j > 1
        row=[row ' &\hfill ' parseentry(arr{j,k})];
      else
        row=[row ' & ' parseentry(arr{j,k})];
      end
    end
    row=[row ' \\'];
    lattable=strvcat(lattable,row);
    if j == sarr(1)
        lattable=strvcat(lattable, '\bottomrule');
    elseif j == 2
        lattable=strvcat(lattable, '\midrule');
    end
  end
  lattable=strvcat(lattable,'\end{tabular}\end{table}');
  
  
function ret=parseentry(entry)
  if isempty(entry)
    entry=' ';
  end
  if isstr(entry)
    ret=entry;
  else
    ret=num2str(entry, '%.4f');
    idxdot=findstr('.',ret);
    len=length(ret);
    if isempty(idxdot)
      ret=[ret '.00'];
    else
      if idxdot==len-1
ret=[ret '0'];
      end
    end
  end 