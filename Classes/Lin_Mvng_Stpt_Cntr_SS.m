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
        function obj = Lin_Mvng_Stpt_Cntr_SS(Lnrzed_EOMs,plant_model, VDefs, type_dim)
            %Lin_Mvng_Stpt_Cntr_SS Construct an instance of this class
            %   Detailed explanation goes here
            
            %Set this object's controller/dimension type
            obj.ctrl_type_dim = type_dim;
            
            %Bring in the plant function/model
            obj.plant = plant_model;

            switch type_dim
                
                case 'SS Integral Controller'
                    
                    %State vector augmented with integral of the error in x
                    obj.stateVec_a = [VDefs.e_ix, VDefs.x, VDefs.x_dot, VDefs.beta, VDefs.beta_dot].'; 
                    obj.stateVec_a_dot = [VDefs.e_x, VDefs.x_dot, VDefs.x_ddot, VDefs.beta_dot, VDefs.beta_ddot].';
                    
                    %Augmented A Matrix
                    obj.sys_mats.Aa = [zeros(5,1),[-1 0 0 0; Lnrzed_EOMs.A1]]; 
                    
                    %Augmented B Matrix
                    obj.sys_mats.Ba = [0;Lnrzed_EOMs.B1];
                    
                    %S matrix, the setpoint matrix
                    obj.sys_mats.S = sym([1;0;0;0;0]);
                    
                    %Our desired control output is the x state (want it to match as 
                    %closely as possible to x_s for all times). C and D select the x state
                    %from the augmented state vector
                    obj.sys_mats.Ca = sym([0 1 0 0 0]); 
                    obj.sys_mats.Da = 0;  

                    %Set the name of the simulink model to use
                    obj.sim_string = 'Linear_Moving_Setpoint_SS_Int';
                    
                    
                case 'SS PID Controller'    
                    
                    
                    %State vector augmented with integral of the error in x AND with x and x_dot replaced with error states
                    obj.stateVec_a = [VDefs.e_ix, VDefs.e_x, VDefs.e_x_dot, VDefs.beta, VDefs.beta_dot].'; 
                    obj.stateVec_a_dot = [VDefs.e_x, VDefs.e_x_dot, VDefs.e_x_ddot, VDefs.beta_dot, VDefs.beta_ddot].';
                    
                    %Setpoint vector
                    obj.setpointVec = [VDefs.x_s VDefs.x_dot_s VDefs.x_ddot_s].';
                    
                    %Derive augmented dynamics for x direction, SS PID controller
                    x_1a_dot_eqn = obj.stateVec_a_dot == [VDefs.e_x VDefs.e_x_dot...
                        (VDefs.x_ddot_s - VDefs.x_ddot) VDefs.beta_dot rhs(Lnrzed_EOMs.Lin_EOMs1(4))].';
                    x_1a_dot_eqn = obj.stateVec_a_dot == subs(rhs(x_1a_dot_eqn),...
                        VDefs.x_ddot , rhs(Lnrzed_EOMs.Lin_EOMs1(2)));
                    x_1a_dot_eqn = subs(x_1a_dot_eqn, VDefs.x, VDefs.x_s - VDefs.e_x);
                    
                    %Augmented A Matrix
                    obj.sys_mats.Aa = equationsToMatrix(rhs(x_1a_dot_eqn), obj.stateVec_a);
                    
                    %Augmented B Matrix
                    obj.sys_mats.Ba = equationsToMatrix(rhs(x_1a_dot_eqn), VDefs.T_beta);
                    
                    %S matrix
                    obj.sys_mats.S = equationsToMatrix(rhs(x_1a_dot_eqn), obj.setpointVec);
                    
                    %Our desired control output is the x state (want it to match as closely as possible to x_s
                    %for all times). Given that x = x_s - e_x, C and D are:
                    obj.sys_mats.Ca = [0 -1 0 0 0]; 
                    obj.sys_mats.Da = [1 0 0];
                    

                    %Set the name of the simulink model to use
                    obj.sim_string = 'Linear_Moving_Setpoint_SS_PID';
                                    
                otherwise
                    
                    error('Not a valid moving setpoint controller type/dimension specification')
                    
            end
            
            
        end
        
        
        function [] = Run_Sim(obj,setpoint_symfun,tspan, x_0, K1, K2)
            %METHOD1 Summary of this method goes here
            %   Detailed explanation goes here
         
            
            %Set the Simulink Parameters (Matrices, times, gains, etc.)
        
                %Timespan
                tspan = Simulink.Parameter(tspan);
                assignin('base', 'tspan', tspan)

                %ICs
                x_0 = Simulink.Parameter(x_0);
                assignin('base', 'xa_0', x_0);  
                
                %Output matrix
                C = Simulink.Parameter(obj.sys_mats.C);
                assignin('base', 'C', C); 

                %Gain matrix K1 - x direction
                K1 = Simulink.Parameter(K1);
                assignin('base', 'K1', K1); %Create the simulink paramter in the base workspace   

                %Gain matrix K2 - y direction
                K2 = Simulink.Parameter(K2);
                assignin('base', 'K2', K2); %Create the simulink paramter in the base workspace  
            
            %Replace the definition of the "Setpoint_Function" MATLAB function block with the
            %setpoint_symfun input
                setpoint = setpoint_symfun;
                sim_path_string = strcat(obj.sim_string,'/Setpoint_Function');
                load_system(obj.sim_string);
                matlabFunctionBlock(sim_path_string, setpoint)

            %Replace the definition of the "Setpoint_Function" MATLAB function block with the
            %setpoint_symfun input
                sim_path_string = strcat(obj.sim_string,'/Plant/Plant_Function');
                load_system(obj.sim_string);
                %Generate a matlab function from the linearized plant model
                input_chars = {'x', 'x_dot', 'beta', 'beta_dot','y', 'y_dot', 'gamma', 'gamma_dot', 'T_beta', 'T_gamma' };
                output_chars = {'x_dot', 'x_ddot', 'beta_dot', 'beta_ddot','y_dot', 'y_ddot', 'gamma_dot', 'gamma_ddot' };
                matlabFunctionBlock(sim_path_string, obj.plant, 'FunctionName', 'xdot','Vars',input_chars)
            
            %Run the simulation    
                obj.sim_response = sim(obj.sim_string);
                
            
        end
        
        function [figure_obj] = plot_results(obj, title_str)
            %plot_results Summary of this method goes here
            %   Detailed explanation goes here 
            
            switch obj.ctrl_type_dim
                
                case 'SS Integral Controller'
                    
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
                    

                    
                case 'SS PID Controller' 
                    
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

