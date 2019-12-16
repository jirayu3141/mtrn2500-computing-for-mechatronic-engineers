% Plot setup information
% Mark Whitty
% UNSW Mechatronics
% m.whitty@gmail.com
% 090225
% 140506 v2
function setup_plots()
global FIGURES SWITCH

% Other variables for plotting
FIGURES.f_text_offset = [0.5 0.5];

% note these properties should have been set by startup.m
set(0, 'DefaultFigurePaperType', 'A4');
set(0, 'DefaultFigureWindowStyle', 'normal'); % 'docked'
set(0, 'DefaultFigurePosition', [100 50 900 600]);
set(0, 'DefaultFigureColor', [1 1 1]);
set(0, 'DefaultAxesBox', 'off');
set(0, 'DefaultAxesFontSize', 10);
set(0, 'DefaultAxesFontName', 'times new roman');
set(0, 'DefaultAxesFontAngle', 'normal');
set(0, 'DefaultAxesColorOrder', [0,0,0;1,0,0;0,0.5,0;0,0,1;0.5,0.25,0;0,0.25,0.5;0.5,0,0.5;0.5 0.5 0]);
set(0, 'DefaultTextFontSize', 10);

FIGURES.FontName = 'times new roman';
FIGURES.FontAngle = 'normal';
FIGURES.FontSize = 16; % Normally 10. For half column width plots, 16 is better, but still small.
FIGURES.Colour = {[0,0,0],[1,0,0],[0,0.5,0],[0,0,1],[0.8,0.4,0],[0,0.25,0.5],[0.5,0,0.5], [0.5 0.5 0]}; FIGURES.NumColours = 8;

% these properties could not be set up in startup.m as LineStyle defaults
% cannot be changed.
FIGURES.LineStyle = {'-','--','-.',':'}; FIGURES.NumLineStyles = 4;
FIGURES.Marker = {'*','o','s','d','x','p','h', '^'}; FIGURES.NumMarkers = 8;
FIGURES.MarkerSize = 5;
FIGURES.LineWidth = 0.75;

if SWITCH.MAIN_PLOT 
    FIGURES.fmain=figure;
    set(FIGURES.fmain, 'Position', [150, 0, 500, 500]);
    set(gcf,'PaperPositionMode','auto')
    set(0, 'DefaultAxesFontSize', 10);
    set(0, 'DefaultTextFontSize', 10);
    FIGURES.hmain.axes(1) = axes('OuterPosition', [0 0 1 1]); % Can easily overlay additional axes later.
    hold on
    axis([-1 1 -1 1]);
    axis square

    xlabel('X [m]'), ylabel('Y [m]')
    set(gcf, 'name', 'Simulator')
    colormap jet
    colormap(flipud(colormap))
    %colorbar
    FIGURES.hmain.title = title('Title 1');
    
    % Handle to one item to be drawn in the plot later. Add more directly
    % below.
    FIGURES.hmain.data_to_plot = plot3(NaN, NaN, NaN, '+', 'erasemode', 'normal', 'markersize',5, 'MarkerEdgeColor', [0.8 0.8 0.8], 'MarkerFaceColor', [0.8 0.8 0.8]);
    
    legend_h = legend([FIGURES.hmain.data_to_plot], 'Data to plot');
    % Properties must be set in this order so that the bo is turned off but
    % the legend has a solid fill. Leave 'Visible' 'off' to have background
    % show through. 
    %set(legend_h, 'box', 'off');
    set(legend_h, 'Color', 'w'); 
    set(legend_h, 'Visible', 'on', 'Location', 'EastOutside');
    
    caxis(gca, [0 0.5]);
    set(gca, 'Layer', 'top');
    % grid lines to show deformation more clearly.
    set(gca, 'XGrid', 'on', 'YGrid', 'on', 'GridLineStyle', '-');
    FIGURES.pcount = 0;
else
    FIGURES.fmain = 0;
    FIGURES.hmain = 0;
    FIGURES.pcount = 0;
end

FIGURES.output_figure_folder = 'output_figures';

end