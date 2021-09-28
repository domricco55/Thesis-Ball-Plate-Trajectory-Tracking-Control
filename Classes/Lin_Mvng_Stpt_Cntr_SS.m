classdef Lin_Mvng_Stpt_Cntr_SS < handle
    %UNTITLED Summary of this class goes here
    %   Detailed explanation goes here
    
    properties (SetAccess = private)
        
        sys_matrices
        
    end
    
    properties 
        
        K
        tspan
        
    end 
    
    methods
        function obj = Lin_Mvng_Stpt_Cntr_SS(Lnrzed_EOMs,type)
            %UNTITLED Construct an instance of this class
            %   Detailed explanation goes here
            
            switch type
                
                case 'SS Integral Controller'
                 
                case 'SS PID Controller'    
                    
                otherwise
                    error('Not a valid moving setpoint controller type')
                    
            end 
        end
        
        
        function sim_response = Run_Sim(obj,sp_symfun, tspan, sim_string)
            %METHOD1 Summary of this method goes here
            %   Detailed explanation goes here
            sim_response = simout;
            
        end
        
        function [] = plot_results(obj, sim_results)
            
        end 
        
    end
end

