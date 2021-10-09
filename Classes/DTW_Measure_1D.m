classdef DTW_Measure_1D < handle
    %DTW_Measure_Dev  Summary of this class goes here
    %   Detailed explanation goes here
    
    properties (SetAccess = private)
        
        %Computed in the constructor
        t_samp %resampled time points
        resamp_rspnse %resampled controller response (position of ball)
        resamp_stpt %resampled setpoint (desired position of ball)
        
        %Computed DTW results
        DTW_dist
        i_wrpd_rspnse
        i_wrpd_stpt
        t_warped
        
        %y axis label
        ylabel_str
    end
    
    methods
        function obj = DTW_Measure_1D(samp_f, response, setpoint, tsim, ylabel_str, plot_cmd)
            %DTW_Measure Construct an instance of this class
            %   Detailed explanation goes here
            
            %Object's y axis label (what is the trajectory we are talking about?)
            obj.ylabel_str = ylabel_str;
            
            %Control Output Resample
            obj.t_samp = linspace(tsim(1), tsim(end), samp_f*(tsim(end) - tsim(1)));  
            obj.resamp_rspnse = interp1(tsim,response, obj.t_samp);

            %Setpoint Resample
            %This will have sample frequency of samp_f
            obj.resamp_stpt = interp1(tsim, setpoint, obj.t_samp);

            %If the plot_cmd is true, plot the resampled signals
            if plot_cmd

                figure
                plot(obj.t_samp, obj.resamp_rspnse,obj.t_samp,obj.resamp_stpt)
                xlabel('time [s]')
                ylabel(obj.ylabel_str)
                title('Resampled Controller Data')
                legend('Controller Output', 'Reference')

            end   
            
        end
        
        function [DTW_dist]  = Get_DTW_Measure(obj, plot_cmd)
            %Get_DTW_Measure Get the DTW distance measure and warping path (indices of
            %linked points in the minimization). If plot_cmd is true, plot the 
            %warped signals in a manner that spaces the data equally in the time axis. 
            %   Detailed explanation goes here
  
            %Get the DTW distance measure for the resampled data, and get the indeces of the
            %warped data (the point to point correspondance that minimizes the DTW
            %distance measure for this particular simulation)
            [DTW_dist, obj.i_wrpd_rspnse, obj.i_wrpd_stpt] = dtw(obj.resamp_rspnse, obj.resamp_stpt, 'absolute');
            
            obj.DTW_dist = DTW_dist;
            
            obj.t_warped = linspace(obj.t_samp(1),obj.t_samp(end), numel(obj.i_wrpd_rspnse));
            
            %If the plot_cmd is true, plot the warped signals
            if plot_cmd
                
                figure
                % plot(1:numel(i_wrp_trj_int), y1_int(i_wrp_trj_int),1:numel(i_wrp_trj_int), x_s_int(i_wrp_sp_int))
                plot(obj.t_warped, obj.resamp_rspnse(obj.i_wrpd_rspnse),obj.t_warped, obj.resamp_stpt(obj.i_wrpd_stpt))
                xlabel('time [s]')
                ylabel(obj.ylabel_str)
                title('Dynamic Time Warped Integral Controller Data')
                legend('Warped Controller Output', 'Warped Reference')   
                
                
            end
            
        end 
        
        function [] = Plot_DTW_Links(obj, num_links)
            %Plot_DTW_Links Plot as many DTW links as num_links
            %     The DTW algorithm relates adjacent data points of two trajectories,
            %     duplicating some of the points (warping) in such a way as to minimize the total
            %     euclidean distance between each pair of points in the warped
            %     trajectories. This function plots a line between some of these pairs of
            %     points, but not all - only num_links many. This decreases the clutter in
            %     the resulting plots. 
           
            %The evenly spaced increment between the first link and the last link that
            %produces the number of links, less than originally output from the DTW
            %algorithm, present in the plot
            increment = length(obj.i_wrpd_stpt)/num_links;

            %Since the increment is likely not an integer, the sparse index vector
            %generated with even spacing 
            sparser_index_vec = round(1:increment:length(obj.i_wrpd_stpt));
            
            sparse_i_wrpd_rspnse = obj.i_wrpd_rspnse(sparser_index_vec);
            sparse_i_wrpd_stpt = obj.i_wrpd_stpt(sparser_index_vec);

            figure
            plot(obj.t_samp, obj.resamp_rspnse,obj.t_samp,obj.resamp_stpt, ...
                [obj.t_samp(sparse_i_wrpd_rspnse); obj.t_samp(sparse_i_wrpd_stpt)],...
                [obj.resamp_rspnse(sparse_i_wrpd_rspnse); obj.resamp_stpt(sparse_i_wrpd_stpt)], 'r')
            xlabel('time [s]')
            ylabel(obj.ylabel_str)
            title('Dynamic Time Warping Links')
            legend('Controller Output', 'Reference')

            
        end
            
            
        
        
    end
end

