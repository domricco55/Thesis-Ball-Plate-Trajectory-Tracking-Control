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
    end
    
    methods
        function obj = DTW_Measure_1D(samp_f, response, setpoint, tsim, ylabel_str, plot_cmd)
            %DTW_Measure Construct an instance of this class
            %   Detailed explanation goes here

        %Control Output Resample
        obj.t_samp = linspace(tsim(1), tsim(end), samp_f*(tsim(end) - tsim(1)));  
        obj.resamp_rspnse = interp1(tsim,response, obj.t_samp);

        %Setpoint Resample
        %This will have sample frequency of samp_f
        obj.resamp_stpt = interp1(tsim, setpoint, obj.t_samp);

        if strcmp(plot_cmd,'yes')
            figure
            plot(obj.t_samp, obj.resamp_rspnse,obj.t_samp,obj.resamp_stpt)
            xlabel('time [s]')
            ylabel(ylabel_str)
            title('Resampled Controller Data')
            legend('Controller Output', 'Reference')
        end   
            
        end
        
        function []  = Get_DTW_Measure(obj)
            %Get_DTW_Measure Summary of this method goes here
            %   Detailed explanation goes here
  
            %Get the DTW distance measure for the resampled data, and get the indeces of the
            %warped data (the point to point correspondance that minimizes the DTW
            %distance measure for this particular simulation)
            [obj.DTW_dist, obj.i_wrpd_rspnse, obj.i_wrpd_stpt] = dtw(obj.resamp_rspnse, obj.resamp_stpt, 'absolute');
            
            obj.t_warped = linspace(obj.t_samp(1),obj.t_samp(end), numel(obj.i_wrpd_rspnse));
            
            
            
        end
        
        
    end
end

