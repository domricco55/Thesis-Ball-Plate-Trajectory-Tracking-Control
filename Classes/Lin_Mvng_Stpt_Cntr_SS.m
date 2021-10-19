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
    end
    
    
    methods
        function obj = Lin_Mvng_Stpt_Cntr_SS(Lnrzed_EOMs, VDefs, type_dim)
            %Lin_Mvng_Stpt_Cntr_SS Construct an instance of this class
            %   Detailed explanation goes here
            
            %Set this object's controller/dimension type
            obj.ctrl_type_dim = type_dim;
            
            switch type_dim
                
                case 'SS Integral Controller x dimension'
                    
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
                    obj.sys_mats.C = sym([0 1 0 0 0]); 
                    obj.sys_mats.D = 0;  
                    
                    %x setpoint selector matrix (plotting in Simulink purposes)
                    obj.sys_mats.x_s_select = 1;
                    
                case 'SS PID Controller x dimension'    
                    
                    
                    %State vector augmented with integral of the error in x AND with x and x_dot replaced with error states
                    obj.stateVec_a = [VDefs.e_ix, VDefs.e_x, VDefs.e_x_dot, VDefs.beta, VDefs.beta_dot].'; 
                    obj.stateVec_a_dot = [VDefs.e_x, VDefs.e_x_dot, VDefs.e_x_ddot, VDefs.beta_dot, VDefs.beta_ddot].';
                    
                    %Setpoint vector
                    obj.setpointVec = [VDefs.x_s VDefs.x_dot_s VDefs.x_ddot_s].';
                    
                    %Derive augmented dynamics for x direction, SS PID controller
                    x_1a_dot_eqn = obj.stateVec_a_dot == [VDefs.e_x VDefs.e_x_dot...
                        (VDefs.x_ddot_s - VDefs.x_ddot) VDefs.beta_dot rhs(Lnrzed_EOMs.Lin_EOMs1(4))].'
                    x_1a_dot_eqn = obj.stateVec_a_dot == subs(rhs(x_1a_dot_eqn),...
                        VDefs.x_ddot , rhs(Lnrzed_EOMs.Lin_EOMs1(2)))
                    x_1a_dot_eqn = subs(x_1a_dot_eqn, VDefs.x, VDefs.x_s - VDefs.e_x)
                    
                    %Augmented A Matrix
                    obj.sys_mats.Aa = equationsToMatrix(rhs(x_1a_dot_eqn), obj.stateVec_a);
                    
                    %Augmented B Matrix
                    obj.sys_mats.Ba = equationsToMatrix(rhs(x_1a_dot_eqn), VDefs.T_beta);
                    
                    %S matrix
                    obj.sys_mats.S = equationsToMatrix(rhs(x_1a_dot_eqn), obj.setpointVec);
                    
                    %Our desired control output is the x state (want it to match as closely as possible to x_s
                    %for all times). Given that x = x_s - e_x, C and D are:
                    obj.sys_mats.C = [0 -1 0 0 0]; 
                    obj.sys_mats.D = [1 0 0];
                    
                    %x setpoint selector matrix (plotting in Simulink purposes)
                    obj.sys_mats.x_s_select = obj.sys_mats.D;


%JUST TESTING A FULL STATE FEEDBACK WITH THIS CODE, COMMENTED OUT THE PID ABOVE
%                     %Augmented A Matrix
%                     obj.sys_mats.Aa = [0 1 0 0;
%                                        5.217 0 -4.0111 0;
%                                        0 0 0 1;
%                                        112.8871 0 64.8295 0];
%                     
%                     %Augmented B Matrix
%                     obj.sys_mats.Ba = [0;17.7268;0;383.5785];
%                     
%                     %S matrix
%                     obj.sys_mats.S = [ 0 0 0;
%                                        5.2170 0 1;
%                                        0 0 0;
%                                        112.8871 0 0];
%                    
%                     %Our desired control output is the x state (want it to match as closely as possible to x_s
%                     %for all times). Given that x = x_s - e_x, C and D are:
%                     obj.sys_mats.C = [1 0 0 0]; 
%                     obj.sys_mats.D = 0;
                    
                    %x setpoint selector matrix (plotting in Simulink purposes)
                    obj.sys_mats.x_s_select = obj.sys_mats.D;
                    

%                     
                otherwise
                    error('Not a valid moving setpoint controller type/dimension specification')
                    
            end
            
            
        end
        
        
        function [] = Run_Sim(obj,setpoint_symfun, tspan, xa_0, K)
            %METHOD1 Summary of this method goes here
            %   Detailed explanation goes here
         
            
            %Set the Simulink Parameters (Matrices, times, gains, etc.)
        
                %Timespan
                tspan = Simulink.Parameter(tspan);
                assignin('base', 'tspan', tspan)

                %ICs
                xa_0 = Simulink.Parameter(xa_0);
                assignin('base', 'xa_0', xa_0);

                %Symbolic matrices derived or assigned in the constructor
                Aa = Simulink.Parameter(double(obj.sys_mats.Aa));
                assignin('base', 'Aa', Aa); %Create the simulink paramter in the base workspace 
                Ba = Simulink.Parameter(double(obj.sys_mats.Ba));
                assignin('base', 'Ba', Ba); %Create the simulink paramter in the base workspace 
                S = Simulink.Parameter(double(obj.sys_mats.S));
                assignin('base', 'S', S); %Create the simulink paramter in the base workspace 
                C = Simulink.Parameter(double(obj.sys_mats.C));
                assignin('base', 'C', C); %Create the simulink paramter in the base workspace 
                D = Simulink.Parameter(double(obj.sys_mats.D));
                assignin('base', 'D', D); %Create the simulink paramter in the base workspace 
                x_s_select = Simulink.Parameter(obj.sys_mats.x_s_select);
                assignin('base', 'x_s_select', x_s_select); %Create the simulink paramter in the base workspace         

                %Gain matrix K
                K = Simulink.Parameter(K);
                assignin('base', 'K', K); %Create the simulink paramter in the base workspace   
            
            %Replace the definition of the "Input_Function" MATLAB function block with the
            %setpoint_symfun input
                load_system('Linear_Moving_Setpoint_SS');
                matlabFunctionBlock('Linear_Moving_Setpoint_SS/Input_Function', setpoint_symfun)
            
            %Run the simulation    
                obj.sim_response = sim('Linear_Moving_Setpoint_SS');
                
            
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
                    ylabel('x [mm]')
                    title(title_str)


                    ax2 = subplot(3,1,2);
                    plot(obj.sim_response.tout,rad2deg(obj.sim_response.xa(:,4)))
                    xlabel('time [s]')
                    ylabel('\beta [deg]')


                    ax3 = subplot(3,1,3);
                    plot(obj.sim_response.tout,obj.sim_response.T)
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
                    ylabel('x [mm]')
                    title(title_str)


                    ax2 = subplot(3,1,2);
                    plot(obj.sim_response.tout,rad2deg(obj.sim_response.xa(:,4)))
                    xlabel('time [s]')
                    ylabel('\beta [deg]')


                    ax3 = subplot(3,1,3);
                    plot(obj.sim_response.tout,obj.sim_response.T)
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
        
    end
end

