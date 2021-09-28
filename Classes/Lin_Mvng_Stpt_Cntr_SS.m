classdef Lin_Mvng_Stpt_Cntr_SS < handle
    %UNTITLED Summary of this class goes here
    %   Detailed explanation goes here
    
    properties (SetAccess = private)
        
        sys_mats %System Matrices
        
    end
    
    properties 
        
        K
        tspan
        
    end 
    
    methods
        function obj = Lin_Mvng_Stpt_Cntr_SS(Lnrzed_EOMs,type)
            %Lin_Mvng_Stpt_Cntr_SS Construct an instance of this class
            %   Detailed explanation goes here
            
            switch type
                
                case 'SS Integral Controller'
                    
                    %Augmented A Matrix
                    obj.sys_mats.Aa = [zeros(5,1),[-1 0 0 0; Lnrzed_EOMs.A1]]; 
                    
                    %Augmented B Matrix
                    obj.sys_mats.Ba = [0;Lnrzed_EOMs.B1];
                    
                    %S matrix, the setpoint matrix
                    obj.sys_mats.Sa = sym([1;0;0;0;0]);
                    

                case 'SS PID Controller'    
                    
                otherwise
                    error('Not a valid moving setpoint controller type')
                    
            end 
        end
        
        
        function sim_response = Run_Sim(obj,sp_symfun, tspan, K)
            %METHOD1 Summary of this method goes here
            %   Detailed explanation goes here
            
            
            %Bring in the gain matrix K
            obj.K = K;
            
            %Set the Simulink Parameters for the matrices
            Aa = Simulink.Parameter(double(obj.sys_mats.Aa));
            assignin('base', 'Aa', Aa);

            Ba = Simulink.Parameter(double(obj.sys_mats.Ba));
            assignin('base', 'Ba', Ba);

            Sa = Simulink.Parameter(double(obj.sys_mats.Sa));
                    assignin('base', 'Sa', Sa);
            
            sim_response = simout;
            
        end
        
        function [] = plot_results(obj, sim_results)
            %METHOD2 Summary of this method goes here
            %   Detailed explanation goes here 
        end 
        
        function [] = create_animation(obj, sim_results)
            %METHOD3 Summary of this method goes here
            %   Detailed explanation goes here
        end 
        
    end
end

