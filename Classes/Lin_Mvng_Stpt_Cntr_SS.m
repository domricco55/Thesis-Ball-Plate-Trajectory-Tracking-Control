classdef Lin_Mvng_Stpt_Cntr_SS < handle
    %UNTITLED Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        Property1
    end
    
    methods
        function obj = untitled(inputArg1,inputArg2)
            %UNTITLED Construct an instance of this class
            %   Detailed explanation goes here
            obj.Property1 = inputArg1 + inputArg2;
        end
        
        function  [] = Set_Sim_Params(obj,Params)
            %METHOD1 Summary of this method goes here
            %   Detailed explanation goes here
            
            
        end
        
        function sim_results = run_sim(obj,sp_symfun, tspan, sim_string)
            
            
            sim_results = simout;
            
        end
        
        function [] = plot_results(obj, sim_results)
            
        end 
        
    end
end

