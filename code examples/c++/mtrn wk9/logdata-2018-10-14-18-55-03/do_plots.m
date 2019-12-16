function pcount = do_plots()
% Mark Whitty
% UNSW Mechatronics
% m.whitty@gmail.com
global FIGURES SWITCH DATA

% Plots
set(0,'CurrentFigure',FIGURES.fmain)
set(FIGURES.fmain, 'CurrentAxes', FIGURES.hmain.axes(1));
if SWITCH.MAIN_PLOT
    FIGURES.pcount= FIGURES.pcount+1;
    set(FIGURES.hmain.data_to_plot, 'xdata', DATA.path(1,1:DATA.i), 'ydata', DATA.path(2,1:DATA.i), 'zdata', zeros(1, size(DATA.path(2,1:DATA.i), 2)))    
end

end