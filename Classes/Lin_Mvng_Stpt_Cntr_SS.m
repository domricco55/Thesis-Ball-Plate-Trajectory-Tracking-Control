classdef Lin_Mvng_Stpt_Cntr_SS < handle
    %Lin_Mvng_Stpt_Cntr_SS  Summary of this class goes here
    %   Detailed explanation goes here
    
    properties (SetAccess = private)
        
        %Bring in class objects
        VDefs %Variable definitions object
        Lnrzed_EOMs %Linearized EOMs object

        sys_mats %System Matrices
        sim_response %Latest system response for this object
        ctrl_type %The type of control system this object represents 
                  %(SS Integral Controller, or SS PID Controller)
                  
        %Definitions of the state vector, roc of state vector, and setpoint
        %vector for a particular controller associated with an instance of the class        
        stateVec_1a 
        stateVec_1a_dot
        stateVec_2a 
        stateVec_2a_dot
        x_setpointVec
        y_setpointVec

        %String for name of Simulink Model to use
        sim_string

        %Plant symfun or MATLAB Anonymous function
        plant

        %Setpoint symfuns - the input to the "Run_Sim" method is a desired x_s and y_s
        %trajectory (position only). This class then generates the necessary x_s_vec and
        %y_s_vec from those setpoints, depending on the control architecture selected. 
        x_s_vec
        y_s_vec

        %Feed-Forward torque - depending on the control architecture, a feed-forward
        %torque symfun may or may not be generated
        u_FF

    end
    
    
    methods
        function obj = Lin_Mvng_Stpt_Cntr_SS(Lnrzed_EOMs,plant_model, VDefs, type)
            %Lin_Mvng_Stpt_Cntr_SS Construct an instance of this class
            %   Detailed explanation goes here
            
            %Set this object's controller type
            obj.ctrl_type = type;
            
            %Bring in the plant function/model
            obj.plant = plant_model;

            %Bring in a VDefs object
            obj.VDefs = VDefs;

            %Bring in a Lnrzed_EOMs object
            obj.Lnrzed_EOMs = Lnrzed_EOMs;

            switch type
                
                case 'SS Integral Controller'

                    % X DIMENSION DERIVATIONS
                    %State vector augmented with integral of the error in x
                    obj.stateVec_1a = [VDefs.e_ix, VDefs.x, VDefs.x_dot, VDefs.beta, VDefs.beta_dot].'; 
                    obj.stateVec_1a_dot = [VDefs.e_x, VDefs.x_dot, VDefs.x_ddot, VDefs.beta_dot, VDefs.beta_ddot].';
                    
                    %Augmented A Matrix
                    obj.sys_mats.A1a = [zeros(5,1),[-1 0 0 0; Lnrzed_EOMs.A1]]; 
                    
                    %Augmented B Matrix
                    obj.sys_mats.B1a = [0;Lnrzed_EOMs.B1];
                    
                    %S matrix, the setpoint matrix
                    obj.sys_mats.S1 = sym([1;0;0;0;0]);
                    
                    %Our desired control output is the x state (want it to match as 
                    %closely as possible to x_s for all times). C and D select the x state
                    %from the augmented state vector
                    obj.sys_mats.C1a = sym([0 1 0 0 0]); 
                    obj.sys_mats.D1a = 0;  

                    % Y DIMENSION DERIVATIONS
                    %State vector augmented with integral of the error in y
                    obj.stateVec_2a = [VDefs.e_iy, VDefs.y, VDefs.y_dot, VDefs.gamma, VDefs.gamma_dot].'; 
                    obj.stateVec_2a_dot = [VDefs.e_y, VDefs.y_dot, VDefs.y_ddot, VDefs.gamma_dot, VDefs.gamma_ddot].';
                    
                    %Augmented A Matrix
                    obj.sys_mats.A2a = [zeros(5,1),[-1 0 0 0; Lnrzed_EOMs.A2]]; 
                    
                    %Augmented B Matrix
                    obj.sys_mats.B2a = [0;Lnrzed_EOMs.B2];
                    
                    %S matrix, the setpoint matrix
                    obj.sys_mats.S2 = sym([1;0;0;0;0]);
                    
                    %Our desired control output is the x state (want it to match as 
                    %closely as possible to y_s for all times). C and D select the y state
                    %from the augmented state vector
                    obj.sys_mats.C2a = sym([0 1 0 0 0]); 
                    obj.sys_mats.D2a = 0;  


                    %Set the name of the simulink model to use
                    obj.sim_string = 'Linear_Moving_Setpoint_SS_Int';
                    
                    
                case 'SS PID Controller'    
                    
                    % X DIMENSION DERIVATIONS
                    %State vector augmented with integral of the error in x AND with x and x_dot replaced with error states
                    obj.stateVec_1a = [VDefs.e_ix, VDefs.e_x, VDefs.e_x_dot, VDefs.beta, VDefs.beta_dot].'; 
                    obj.stateVec_1a_dot = [VDefs.e_x, VDefs.e_x_dot, VDefs.e_x_ddot, VDefs.beta_dot, VDefs.beta_ddot].';
                    
                    %Setpoint vector
                    obj.x_setpointVec = [VDefs.x_s VDefs.x_dot_s VDefs.x_ddot_s].';
                    
                    %Derive augmented dynamics for x direction, SS PID controller
                    x_1a_dot_eqn = obj.stateVec_1a_dot == [VDefs.e_x VDefs.e_x_dot...
                        (VDefs.x_ddot_s - VDefs.x_ddot) VDefs.beta_dot rhs(Lnrzed_EOMs.Lin_EOMs1(4))].';
                    x_1a_dot_eqn = obj.stateVec_1a_dot == subs(rhs(x_1a_dot_eqn),...
                        VDefs.x_ddot , rhs(Lnrzed_EOMs.Lin_EOMs1(2)));
                    x_1a_dot_eqn = subs(x_1a_dot_eqn, VDefs.x, VDefs.x_s - VDefs.e_x);
                    
                    %Augmented A Matrix
                    obj.sys_mats.A1a = equationsToMatrix(rhs(x_1a_dot_eqn), obj.stateVec_1a);
                    
                    %Augmented B Matrix
                    obj.sys_mats.B1a = equationsToMatrix(rhs(x_1a_dot_eqn), VDefs.T_beta);
                    
                    %S matrix
                    obj.sys_mats.S1 = equationsToMatrix(rhs(x_1a_dot_eqn), obj.x_setpointVec);
                    
                    %Our desired control output is the x state (want it to match as closely as possible to x_s
                    %for all times). Given that x = x_s - e_x, C and D are:
                    obj.sys_mats.C1a = [0 -1 0 0 0]; 
                    obj.sys_mats.D1a = [1 0 0];

                    % y DIMENSION DERIVATIONS
                    %State vector augmented with integral of the error in y AND with y and y_dot replaced with error states
                    obj.stateVec_2a = [VDefs.e_iy, VDefs.e_y, VDefs.e_y_dot, VDefs.gamma, VDefs.gamma_dot].'; 
                    obj.stateVec_2a_dot = [VDefs.e_y, VDefs.e_y_dot, VDefs.e_y_ddot, VDefs.gamma_dot, VDefs.gamma_ddot].';
                    
                    %Setpoint vector
                    obj.y_setpointVec = [VDefs.y_s VDefs.y_dot_s VDefs.y_ddot_s].';
                    
                    %Derive augmented dynamics for x direction, SS PID controller
                    x_2a_dot_eqn = obj.stateVec_2a_dot == [VDefs.e_y VDefs.e_y_dot...
                        (VDefs.y_ddot_s - VDefs.y_ddot) VDefs.gamma_dot rhs(Lnrzed_EOMs.Lin_EOMs2(4))].';
                    x_2a_dot_eqn = obj.stateVec_2a_dot == subs(rhs(x_2a_dot_eqn),...
                        VDefs.y_ddot , rhs(Lnrzed_EOMs.Lin_EOMs2(2)));
                    x_2a_dot_eqn = subs(x_2a_dot_eqn, VDefs.y, VDefs.y_s - VDefs.e_y);
                    
                    %Augmented A Matrix
                    obj.sys_mats.A2a = equationsToMatrix(rhs(x_2a_dot_eqn), obj.stateVec_2a);
                    
                    %Augmented B Matrix
                    obj.sys_mats.B2a = equationsToMatrix(rhs(x_2a_dot_eqn), VDefs.T_gamma);
                    
                    %S matrix
                    obj.sys_mats.S2 = equationsToMatrix(rhs(x_2a_dot_eqn), obj.y_setpointVec);
                    
                    %Our desired control output is the y state (want it to match as closely as possible to y_s
                    %for all times). Given that y = y_s - e_y, C and D are:
                    obj.sys_mats.C2a = [0 -1 0 0 0]; 
                    obj.sys_mats.D2a = [1 0 0];
                    

                    %Set the name of the simulink model to use
                    obj.sim_string = 'Linear_Moving_Setpoint_SS_PID';

                case 'SS PID FF Controller'

                    % X DIMENSION DERIVATIONS
                    %State vector augmented with integral of the error in x AND all states
                    %replaced by error states
                    obj.stateVec_1a = [VDefs.e_ix, VDefs.e_x, VDefs.e_x_dot, VDefs.e_beta, VDefs.e_beta_dot].'; 
                    obj.stateVec_1a_dot = [VDefs.e_x, VDefs.e_x_dot, VDefs.e_x_ddot, VDefs.e_beta_dot, VDefs.e_beta_ddot].';
                    
                    %Setpoint vector
                    obj.x_setpointVec = [VDefs.x_s VDefs.x_dot_s VDefs.x_ddot_s VDefs.beta_dot_s VDefs.beta_ddot_s].';
                    
                    %Derive augmented dynamics for x direction
                    x_1a_dot_eqn = obj.stateVec_1a_dot == [VDefs.e_x VDefs.e_x_dot...
                        (VDefs.x_ddot_s - VDefs.x_ddot) VDefs.e_beta_dot (VDefs.beta_ddot_s - VDefs.beta_ddot)].';
                    x_1a_dot_eqn = obj.stateVec_1a_dot == subs(rhs(x_1a_dot_eqn),...
                        [VDefs.x_ddot VDefs.beta_ddot] , [rhs(Lnrzed_EOMs.Lin_EOMs1(2)) rhs(Lnrzed_EOMs.Lin_EOMs1(4))]);
                    x_1a_dot_eqn = subs(x_1a_dot_eqn, [VDefs.x, VDefs.beta], [VDefs.x_s - VDefs.e_x, VDefs.beta_s - VDefs.e_beta]);
                    
                    %Augmented A Matrix
                    obj.sys_mats.A1a = equationsToMatrix(rhs(x_1a_dot_eqn), obj.stateVec_1a);
                    
                    %Augmented B Matrix
                    obj.sys_mats.B1a = equationsToMatrix(rhs(x_1a_dot_eqn), VDefs.T_beta);
                    
                    %S matrix
                    obj.sys_mats.S1 = equationsToMatrix(rhs(x_1a_dot_eqn), obj.x_setpointVec);
                    
                    %Our desired control output is the x state (want it to match as closely as possible to x_s
                    %for all times). Given that x = x_s - e_x, C and D are:
                    obj.sys_mats.C1a = [0 -1 0 0 0]; 
                    obj.sys_mats.D1a = [1 0 0];

                    % y DIMENSION DERIVATIONS
                    %State vector augmented with integral of the error in y AND all states
                    %replaced by error states
                    obj.stateVec_2a = [VDefs.e_iy, VDefs.e_y, VDefs.e_y_dot, VDefs.e_gamma, VDefs.e_gamma_dot].'; 
                    obj.stateVec_2a_dot = [VDefs.e_y, VDefs.e_y_dot, VDefs.e_y_ddot, VDefs.e_gamma_dot, VDefs.e_gamma_ddot].';
                    
                    %Setpoint vector
                    obj.y_setpointVec = [VDefs.y_s VDefs.y_dot_s VDefs.y_ddot_s VDefs.gamma_dot_s VDefs.gamma_ddot_s].';
                    
                    %Derive augmented dynamics for x direction, SS PID controller
                    x_2a_dot_eqn = obj.stateVec_2a_dot == [VDefs.e_y VDefs.e_y_dot...
                        (VDefs.y_ddot_s - VDefs.y_ddot) VDefs.e_gamma_dot (VDefs.gamma_ddot_s - VDefs.gamma_ddot)].';
                    x_2a_dot_eqn = obj.stateVec_2a_dot == subs(rhs(x_2a_dot_eqn),...
                        [VDefs.y_ddot VDefs.gamma_ddot] , [rhs(Lnrzed_EOMs.Lin_EOMs2(2)), rhs(Lnrzed_EOMs.Lin_EOMs2(4))]);
                    x_2a_dot_eqn = subs(x_2a_dot_eqn, [VDefs.y VDefs.gamma], [VDefs.y_s - VDefs.e_y, VDefs.gamma_s - VDefs.e_gamma]);


                    
                    %Augmented A Matrix
                    obj.sys_mats.A2a = equationsToMatrix(rhs(x_2a_dot_eqn), obj.stateVec_2a);
                    
                    %Augmented B Matrix
                    obj.sys_mats.B2a = equationsToMatrix(rhs(x_2a_dot_eqn), VDefs.T_gamma);
                    
                    %S matrix
                    obj.sys_mats.S2 = equationsToMatrix(rhs(x_2a_dot_eqn), obj.y_setpointVec);
                    
                    %Our desired control output is the y state (want it to match as closely as possible to y_s
                    %for all times). Given that y = y_s - e_y, C and D are:
                    obj.sys_mats.C2a = [0 -1 0 0 0]; 
                    obj.sys_mats.D2a = [1 0 0 0 0];
                    

                    %Set the name of the simulink model to use
                    obj.sim_string = 'Linear_Moving_Setpoint_SS_w_FF';

                                    
                otherwise
                    
                    error('Not a valid moving setpoint controller type/dimension specification')
                    
            end
            
            
        end
        
        
        function [] = Run_Sim(obj,x_s,y_s, tspan, x_0, Tau, K1, K2)
            %METHOD1 Summary of this method goes here
            %   Detailed explanation goes here

            %Depending on the control architecture, generate x_s_vec, y_s_vec, and u_FF
            %from x_setpoint_symfun and y_setpoint_symfun
            switch obj.ctrl_type
                case 'SS Integral Controller'

                    %Smooth path to trajectory from the initial conditions
                    x_s = x_s*(1-exp(-obj.VDefs.t/Tau)) + x_0(1)*exp(-obj.VDefs.t/Tau);
                    y_s = y_s*(1-exp(-obj.VDefs.t/Tau)) + x_0(5)*exp(-obj.VDefs.t/Tau);

                    %Setpoint vectors here are just the smoothed x and y setpoints
                    obj.x_s_vec = x_s;
                    obj.y_s_vec = y_s;

                case 'SS PID Controller' 

                    %Smooth path to trajectory from the initial conditions
                    x_s = x_s*(1-exp(-obj.VDefs.t/Tau)) + x_0(1)*exp(-obj.VDefs.t/Tau);
                    y_s = y_s*(1-exp(-obj.VDefs.t/Tau)) + x_0(5)*exp(-obj.VDefs.t/Tau);

                    %For the PID the setpoint vector contains the derivative of 
                    % the desired x and y trajectories
                    obj.x_s_vec = [x_s; diff(x_s,1)]; 
                    obj.y_s_vec = [y_s; diff(y_s,1)];

                case 'SS PID FF Controller'

                    %Solve for the angular setpoints that are consistent with the x and y
                    %setpoints (in the linear dynamics)

                    syms beta_s(t) gamma_s(t) C1 C2

                    %Beta 
                    T_beta_eqn = isolate(obj.VDefs.beta_ddot == obj.Lnrzed_EOMs.Lin_EOMs(4), obj.VDefs.T_beta);
                    T_beta_eqn = subs(T_beta_eqn,[obj.VDefs.beta, obj.VDefs.beta_ddot],[beta_s, diff(beta_s,2)]);    
                    ode_beta_s = diff(x_s,2) == subs(obj.Lnrzed_EOMs.Lin_EOMs(2), obj.VDefs.T_beta, rhs(T_beta_eqn));
                    ode_beta_s = subs(ode_beta_s, obj.VDefs.beta, beta_s); 
                    %Solve the linear ODE for beta_s(t)
                    beta_s_sol(obj.VDefs.t) = dsolve(ode_beta_s);
                    %Take only the particular solution 
                    beta_s_sol(obj.VDefs.t) = subs(beta_s_sol, [C1 C2], [0 0]);

                    %Gamma
                    T_gamma_eqn = isolate(obj.VDefs.gamma_ddot == obj.Lnrzed_EOMs.Lin_EOMs(8), obj.VDefs.T_gamma);
                    T_gamma_eqn = subs(T_gamma_eqn,[obj.VDefs.gamma, obj.VDefs.gamma_ddot],[gamma_s, diff(gamma_s,2)]);    
                    ode_gamma_s = diff(y_s,2) == subs(obj.Lnrzed_EOMs.Lin_EOMs(6), obj.VDefs.T_gamma, rhs(T_gamma_eqn));
                    ode_gamma_s = subs(ode_gamma_s, obj.VDefs.gamma, gamma_s); 
                    %Solve the linear ODE for gamma_s(t)
                    gamma_s_sol(obj.VDefs.t) = dsolve(ode_gamma_s);
                    %Take only the particular solution 
                    gamma_s_sol(obj.VDefs.t) = subs(gamma_s_sol, [C1 C2], [0 0]);

                    %Feed-Forward input functions
                    T_beta = subs(rhs(T_beta_eqn), [obj.VDefs.x, beta_s, diff(beta_s,2)], [x_s beta_s_sol diff(beta_s_sol,2)]);
                    T_gamma = subs(rhs(T_gamma_eqn), [obj.VDefs.y, gamma_s, diff(gamma_s,2)], [y_s gamma_s_sol diff(gamma_s_sol,2)]);
                    obj.u_FF = [T_beta;T_gamma];

                    %Apply a first order smoothing to both the position and angular
                    %setpoints
                    x_s = x_s*(1-exp(-obj.VDefs.t/Tau)) + x_0(1)*exp(-obj.VDefs.t/Tau);
                    y_s = y_s*(1-exp(-obj.VDefs.t/Tau)) + x_0(5)*exp(-obj.VDefs.t/Tau);
                    beta_s_sol = beta_s_sol*(1-exp(-obj.VDefs.t/Tau)) + x_0(3)*exp(-obj.VDefs.t/Tau);
                    gamma_s_sol = gamma_s_sol*(1-exp(-obj.VDefs.t/Tau)) + x_0(7)*exp(-obj.VDefs.t/Tau);

                    %Bring setpoints together into the setpoint vectors
                    obj.x_s_vec = [x_s; diff(x_s); beta_s_sol; diff(beta_s_sol)];
                    obj.y_s_vec = [y_s; diff(y_s); gamma_s_sol; diff(gamma_s_sol)];
                    

            end 

            %Set the Simulink Parameters (Matrices, times, gains, etc.)
        
            %Timespan
            tspan = Simulink.Parameter(tspan);
            assignin('base', 'tspan', tspan)

            %ICs
            x_0 = Simulink.Parameter(x_0);
            assignin('base', 'x_0', x_0);  

            %Gain matrix K1 - x direction
            K1 = Simulink.Parameter(K1);
            assignin('base', 'K1', K1); %Create the simulink paramter in the base workspace   

            %Gain matrix K2 - y direction
            K2 = Simulink.Parameter(K2);
            assignin('base', 'K2', K2); %Create the simulink paramter in the base workspace  

            %Saturation torque
            Tmax = Simulink.Parameter(obj.VDefs.Tmax);
            assignin('base', 'Tmax', Tmax); %Create the simulink paramter in the base workspace             
        
        %Load the sytem's Simulink Model
            load_system(obj.sim_string);

        %Replace the definition of the "x_Setpoint_Function" MATLAB function block
        %with a function generated from x_setpoint_symfun
            sim_path_string = strcat(obj.sim_string,'/Setpoint_Vectors/x_Setpoint_Function');
            matlabFunctionBlock(sim_path_string, obj.x_s_vec,'FunctionName', 'x_s_vec')

        %Replace the definition of the "y_Setpoint_Function" MATLAB function block
        %with a function generated from y_setpoint_symfun
            sim_path_string = strcat(obj.sim_string,'/Setpoint_Vectors/y_Setpoint_Function');
            matlabFunctionBlock(sim_path_string, obj.y_s_vec,'FunctionName', 'y_s_vec')

        %If a feed-forward controller, replace the definition of the "u_FF" MATLAB function block       
        if strcmp(obj.ctrl_type,'SS PID FF Controller')
  
            sim_path_string = strcat(obj.sim_string,'/u_FF');
            matlabFunctionBlock(sim_path_string, obj.u_FF,'FunctionName', 'u_FF')
        end 

        %Replace the definition of the "Plant_Function" MATLAB function block with a
        %function generated from obj.plant symbolic function
            sim_path_string = 'Plant/Plant_Function';
            %Generate a matlab function from the linearized plant model
            input_chars = {'x', 'x_dot', 'beta', 'beta_dot','y', 'y_dot', 'gamma', 'gamma_dot', 'T_beta', 'T_gamma' };
            %output_chars = {'x_dot', 'x_ddot', 'beta_dot', 'beta_ddot','y_dot', 'y_ddot', 'gamma_dot', 'gamma_ddot' };
            matlabFunctionBlock(sim_path_string, obj.plant, 'FunctionName', 'xdot','Vars',input_chars)
        
        %Run the simulation    
            obj.sim_response = sim(obj.sim_string);
            

            
        end
        
        function [figure_obj_x, figure_obj_y] = plot_results(obj, title_str)
            %plot_results Summary of this method goes here
            %   Detailed explanation goes here 
            
            switch obj.ctrl_type
                
                case 'SS Integral Controller'
                    
                    figure_obj_x = figure;
                    
                    title('SS_Integral_Controller x direction');
                    
                    ax1 = subplot(4,1,1);
                    plot(obj.sim_response.tout,obj.sim_response.x(:,1),...
                        obj.sim_response.tout,obj.sim_response.x_s_vec,'--' )
                    xlabel('time [s]')
                    ylabel('x [m]')
                    title(strcat(title_str,' x direction'))
                    legend('x', 'x_s')

                    ax2 = subplot(4,1,2);
                    plot(obj.sim_response.tout,rad2deg(obj.sim_response.x(:,3)))
                    xlabel('time [s]')
                    ylabel('\beta [deg]')


                    ax3 = subplot(4,1,3);
                    plot(obj.sim_response.tout,obj.sim_response.u(:,1)*1000)
                    xlabel('time [s]')
                    ylabel('Tbeta [mNm]')
                    
                    ax4 = subplot(4,1,4);
                    plot(obj.sim_response.tout,(obj.sim_response.x_s_vec(:,1) - obj.sim_response.x(:,1)))
                    xlabel('time [s]')
                    ylabel('error in x [m]')

                    linkaxes([ax1,ax2, ax3 ax4],'x');
                    set(gcf,'position',[0,0,800,900]);   

                    figure_obj_y = figure;
                    
                    ax1 = subplot(3,1,1);
                    plot(obj.sim_response.tout,obj.sim_response.x(:,5),...
                        obj.sim_response.tout,obj.sim_response.y_s_vec,'--' )
                    xlabel('time [s]')
                    ylabel('y [m]')
                    title(strcat(title_str,' y direction'))
                    legend('y', 'y_s')

                    ax2 = subplot(3,1,2);
                    plot(obj.sim_response.tout,rad2deg(obj.sim_response.x(:,7)))
                    xlabel('time [s]')
                    ylabel('\gamma[deg]')


                    ax3 = subplot(3,1,3);
                    plot(obj.sim_response.tout,obj.sim_response.u(:,2)*1000)
                    xlabel('time [s]')
                    ylabel('Tgamma [mNm]')
                    
                    linkaxes([ax1,ax2, ax3],'x');
                    set(gcf,'position',[0,0,800,900]);   
                    

                    
                case 'SS PID Controller' 
                    
                    figure_obj_x = figure;
                    
                    
                    ax1 = subplot(4,1,1);
                    plot(obj.sim_response.tout,obj.sim_response.x(:,1),obj.sim_response.tout,obj.sim_response.x_s_vec(:,1),'--' )
                    xlabel('time [s]')
                    ylabel('x [m]')
                    title(strcat(title_str,' x direction'))
                    legend('x', 'x_s')

                    ax2 = subplot(4,1,2);
                    plot(obj.sim_response.tout,rad2deg(obj.sim_response.x(:,3)))
                    xlabel('time [s]')
                    ylabel('\beta [deg]')


                    ax3 = subplot(4,1,3);
                    plot(obj.sim_response.tout,obj.sim_response.u(:,1)*1000)
                    xlabel('time [s]')
                    ylabel('Tbeta [mNm]')

                    ax4 = subplot(4,1,4);
                    plot(obj.sim_response.tout,(obj.sim_response.x_s_vec(:,1) - obj.sim_response.x(:,1)))
                    xlabel('time [s]')
                    ylabel('error in x [m]')

                    linkaxes([ax1,ax2, ax3, ax4],'x');
                    set(gcf,'position',[0,0,800,900]);

                    figure_obj_y = figure;

                    ax1 = subplot(3,1,1);
                    plot(obj.sim_response.tout,obj.sim_response.x(:,5),obj.sim_response.tout,obj.sim_response.y_s_vec(:,1),'--' )
                    xlabel('time [s]')
                    ylabel('y [m]')
                    title(strcat(title_str,' y direction'))
                    legend('y', 'y_s')

                    ax2 = subplot(3,1,2);
                    plot(obj.sim_response.tout,rad2deg(obj.sim_response.x(:,7)))
                    xlabel('time [s]')
                    ylabel('\gamma [deg]')


                    ax3 = subplot(3,1,3);
                    plot(obj.sim_response.tout,obj.sim_response.u(:,2)*1000)
                    xlabel('time [s]')
                    ylabel('Tgamma [mNm]')
                    
                    linkaxes([ax1,ax2, ax3],'x');
                    set(gcf,'position',[0,0,800,900]);
                     
               case 'SS PID FF Controller'

                    figure_obj_x = figure;
                    
                    
                    ax1 = subplot(4,1,1);
                    plot(obj.sim_response.tout,obj.sim_response.x(:,1),obj.sim_response.tout,obj.sim_response.x_s_vec(:,1),'--' )
                    xlabel('time [s]')
                    ylabel('x [m]')
                    title(strcat(title_str,' x direction'))
                    legend('x', 'x_s')


                    ax2 = subplot(4,1,2);
                    plot(obj.sim_response.tout,rad2deg(obj.sim_response.x(:,3)),...
                         obj.sim_response.tout,rad2deg(obj.sim_response.x_s_vec(:,3)))
                    xlabel('time [s]')
                    ylabel('\beta [deg]')
                    legend('beta', 'beta_s')


                    ax3 = subplot(4,1,3);
                    plot(obj.sim_response.tout,obj.sim_response.u(:,1)*1000)
                    xlabel('time [s]')
                    ylabel('Tbeta [mNm]')

                    ax4 = subplot(4,1,4);
                    plot(obj.sim_response.tout,(obj.sim_response.x_s_vec(:,1) - obj.sim_response.x(:,1)))
                    xlabel('time [s]')
                    ylabel('error in x [m]')


                    linkaxes([ax1,ax2, ax3, ax4],'x');
                    set(gcf,'position',[0,0,800,900]);

                    figure_obj_y = figure;

                    title('SS PID w FF Controller y direction');

                    ax1 = subplot(4,1,1);
                    plot(obj.sim_response.tout,obj.sim_response.x(:,5),obj.sim_response.tout,obj.sim_response.y_s_vec(:,1),'--' )
                    xlabel('time [s]')
                    ylabel('y [m]')
                    title(strcat(title_str,' y direction'))
                    legend('y', 'y_s')

                    ax2 = subplot(4,1,2);
                    plot(obj.sim_response.tout,rad2deg(obj.sim_response.x(:,7)), ...
                         obj.sim_response.tout,rad2deg(obj.sim_response.y_s_vec(:,3)))
                    xlabel('time [s]')
                    ylabel('\gamma [deg]')
                    legend('gamma', 'gamma_s')

                    ax3 = subplot(4,1,3);
                    plot(obj.sim_response.tout,obj.sim_response.u(:,2)*1000)
                    xlabel('time [s]')
                    ylabel('Tgamma [mNm]')
                    
                    ax4 = subplot(4,1,4);
                    plot(obj.sim_response.tout,(obj.sim_response.x_s_vec(:,1) - obj.sim_response.x(:,1)))
                    xlabel('time [s]')
                    ylabel('error in x [m]')

                    linkaxes([ax1,ax2, ax3, ax4],'x');
                    set(gcf,'position',[0,0,800,900]);


            end 
            
        end 

    end
end

