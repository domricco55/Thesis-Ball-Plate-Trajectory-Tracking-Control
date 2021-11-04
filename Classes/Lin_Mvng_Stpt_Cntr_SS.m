classdef Lin_Mvng_Stpt_Cntr_SS < handle
    %Lin_Mvng_Stpt_Cntr_SS  Summary of this class goes here
    %   Detailed explanation goes here
    
    properties (SetAccess = private)
        
        sys_mats %System Matrices
        sim_response %Latest system response for this object
        ctrl_type_dim %The type of control system this object represents 
                  %(SS Integral Controller, or SS PID Controller)
                  
        %Definitions of the state vector, roc of state vector, and setpoint
        %vector for a particular controller associated with an instance of the class        
        stateVec_a 
        stateVec_a_dot
        setpointVec

        %String for name of Simulink Model to use
        sim_string

        %Plant symfun or MATLAB Anonymous function
        plant
    end
    
    
    methods
        function obj = Lin_Mvng_Stpt_Cntr_SS(plant_model, VDefs, type_dim)
            %Lin_Mvng_Stpt_Cntr_SS Construct an instance of this class
            %   Detailed explanation goes here
            
            %Set this object's controller/dimension type
            obj.ctrl_type_dim = type_dim;
            
            %Bring in the plant function/model
            obj.plant = plant_model;

            switch type_dim
                
                case 'SS Integral Controller x dimension'
                    
                    


                    %Set the name of the simulink model to use
                    obj.sim_string = 'Linear_Moving_Setpoint_SS_Int';
                    
                    
                case 'SS PID Controller x dimension'    
                    
                    
%                     %S matrix
%                     obj.sys_mats.S = equationsToMatrix(rhs(x_1a_dot_eqn), obj.setpointVec);
                    
                    %Our desired control output is the x state (want it to match as closely as possible to x_s
                    %for all times). Given that x = x_s - e_x, C and D are:
                    obj.sys_mats.C = [0 -1 0 0 0]; 
                    obj.sys_mats.D = [1 0 0];
                    
                    %x setpoint selector matrix (plotting in Simulink purposes)
                    obj.sys_mats.x_s_select = obj.sys_mats.D;
                    
                    %x setpoint selector matrix (plotting in Simulink purposes)
                    obj.sys_mats.x_s_select = obj.sys_mats.D;

                    %Set the name of the simulink model to use
                    obj.sim_string = 'Linear_Moving_Setpoint_SS_PID';
                                    
                otherwise
                    
                    error('Not a valid moving setpoint controller type/dimension specification')
                    
            end
            
            
        end
        
        
        function [] = Run_Sim(obj,setpoint_symfun,tspan, xa_0, K)
            %METHOD1 Summary of this method goes here
            %   Detailed explanation goes here
         
            
            %Set the Simulink Parameters (Matrices, times, gains, etc.)
        
                %Timespan
                tspan = Simulink.Parameter(tspan);
                assignin('base', 'tspan', tspan)

                %ICs
                xa_0 = Simulink.Parameter(xa_0);
                assignin('base', 'xa_0', xa_0);     

                %Gain matrix K
                K = Simulink.Parameter(K);
                assignin('base', 'K', K); %Create the simulink paramter in the base workspace   
            
            %Replace the definition of the "Setpoint_Function" MATLAB function block with the
            %setpoint_symfun input
                setpoint = setpoint_symfun;
                sim_path_string = strcat(obj.sim_string,'/Setpoint_Function');
                load_system(obj.sim_string);
                matlabFunctionBlock(sim_path_string, setpoint)

            %Replace the definition of the "Setpoint_Function" MATLAB function block with the
            %setpoint_symfun input
                sim_path_string = strcat(obj.sim_string,'/Plant_Function');
                load_system(obj.sim_string);
                matlabFunctionBlock(sim_path_string, obj.plant)
            
            %Run the simulation    
                obj.sim_response = sim(obj.sim_string);
                
            
        end
        
        function [figure_obj] = plot_results(obj, title_str)
            %plot_results Summary of this method goes here
            %   Detailed explanation goes here 
            
            switch obj.ctrl_type_dim
                
                case 'SS Integral Controller x dimension'
                    
                    figure_obj = figure;
                    
                    title(obj.ctrl_type_dim);
                    
                    ax1 = subplot(3,1,1);
                    plot(obj.sim_response.tout,obj.sim_response.y,...
                        obj.sim_response.tout,obj.sim_response.x_s_vec,'--' )
                    xlabel('time [s]')
                    ylabel('x [m]')
                    title(title_str)


                    ax2 = subplot(3,1,2);
                    plot(obj.sim_response.tout,rad2deg(obj.sim_response.xa(:,4)))
                    xlabel('time [s]')
                    ylabel('\beta [deg]')


                    ax3 = subplot(3,1,3);
                    plot(obj.sim_response.tout,obj.sim_response.T*1000)
                    xlabel('time [s]')
                    ylabel('Torque [mNm]')
                    
                    linkaxes([ax1,ax2, ax3],'x');
                    set(gcf,'position',[0,0,800,900]);   
                    

                    
                case 'SS PID Controller x dimension' 
                    
                    figure_obj = figure;
                    
                    title(obj.ctrl_type_dim);
                    
                    ax1 = subplot(3,1,1);
                    plot(obj.sim_response.tout,obj.sim_response.y,obj.sim_response.tout,obj.sim_response.x_s_vec(:,1),'--' )
                    xlabel('time [s]')
                    ylabel('x [m]')
                    title(title_str)


                    ax2 = subplot(3,1,2);
                    plot(obj.sim_response.tout,rad2deg(obj.sim_response.xa(:,4)))
                    xlabel('time [s]')
                    ylabel('\beta [deg]')


                    ax3 = subplot(3,1,3);
                    plot(obj.sim_response.tout,obj.sim_response.T*1000)
                    xlabel('time [s]')
                    ylabel('Torque [mNm]')
                    
                    linkaxes([ax1,ax2, ax3],'x');
                    set(gcf,'position',[0,0,800,900]);
                    
                case 'SS Integral Controller y dimension'   
                    
                    
                case 'SS PID Controller y dimension'    
                    
            end 
            
        end 
%         
%         function [] = create_animation(obj)
%             %METHOD3 Summary of this method goes here
%             %   Detailed explanation goes here
%         end 
        
%         
%         function [] = create_animation(obj)
%             %METHOD3 Summary of this method goes here
%             %   Detailed explanation goes here
%         end 


    end
end

