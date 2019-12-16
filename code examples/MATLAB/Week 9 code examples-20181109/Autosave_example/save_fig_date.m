function save_fig_date(fig_handle, unique_prefix)
% Save figure script with the unique prefix as part of the name
% Mark Whitty
% 120614
% Adapted from code by Lin Chi Mak
% 120623 Modified to include the corresponding log file name and date so can be
% regenerated and referenced.
figure(fig_handle); % To ensure print actually uses the correct figure, which may not be the current one.
global FIGURES LOG
my_cwd = pwd;
figures_dir = [my_cwd '\' FIGURES.output_figure_folder];
if(exist(figures_dir) ~= 7)
    % directory doesn't exist
    mkdir(figures_dir);
end
cd(figures_dir);

saveas(fig_handle,['fig_',unique_prefix,'_',LOG.log_folder,'.fig']);
print('-r300','-dmeta',['fig_',unique_prefix,'_',LOG.log_folder,'.emf']);
print('-r300','-depsc2',['fig_',unique_prefix,'_',LOG.log_folder,'.eps']);

cd(my_cwd);

