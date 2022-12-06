classdef Lin_FSFB_Cntrl < handle
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

        %Strings for Simulink models for a particular architecture
        sim_file_string %String for the simulation Simulink file
        HIL_file_string %String for the HIL Simulink file (hardware testing)
        ctrl_file_string %String for the control architecture Simulink file (refernced model)
        

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

        %SimIn object
        %Saves the Simulink.SimulationInput object associated with the 
        %latest run of the controller simulation
        SimIn

        %HIL control parameters Struct:
        %since I can't use the Simulink.SimulationInput
        %object method for assigning variables in a Simulink Desktop
        %Real-Time environment, I need to use "assignin" instead. So to
        %have the control parameters associated with 
        HIL_cntrl_params

        %Might as well have a struct for the simulation as well
        Sim_cntrl_params

    end
    
    
    methods
        function obj = Lin_FSFB_Cntrl(Lnrzed_EOMs,plant_model, VDefs, type)
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
                
                case 'FSFB Integral Controller'

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
                    obj.sim_file_string = 'FSFB_Int_Sim';
                    %%obj.HIL_file_string = 'Simulink Models/Hardware Implementation/FSFB_Int_HIL';
                    obj.ctrl_file_string = 'FSFB_Int_Controller';
                    
                    
                case 'FSFB PID Controller'    
                    
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
                    obj.sim_file_string = 'FSFB_PID_Sim';
                    %%obj.HIL_file_string = 'Simulink Models/Hardware Implementation/FSFB_PID_HIL';
                    obj.ctrl_file_string = 'FSFB_PID_Controller';

                case 'FSFB FF Controller'

                    % X DIMENSION DERIVATIONS
                    %State vector augmented with integral of x 
                    obj.stateVec_1a = [VDefs.ix, VDefs.x, VDefs.x_dot, VDefs.beta, VDefs.beta_dot].'; 
                    obj.stateVec_1a_dot = [VDefs.x, VDefs.x_dot, VDefs.x_ddot, VDefs.beta_dot, VDefs.beta_ddot].';
                    
                    %Derive augmented dynamics for x direction
                    x_1a_dot_eqn = obj.stateVec_1a_dot == obj.stateVec_1a_dot;
                    x_1a_dot_eqn = obj.stateVec_1a_dot == subs(rhs(x_1a_dot_eqn),...
                        [VDefs.x_ddot VDefs.beta_ddot] , [rhs(Lnrzed_EOMs.Lin_EOMs1(2)) rhs(Lnrzed_EOMs.Lin_EOMs1(4))]);
                    
                    %Augmented A Matrix
                    obj.sys_mats.A1a = equationsToMatrix(rhs(x_1a_dot_eqn), obj.stateVec_1a);
                    
                    %Augmented B Matrix
                    obj.sys_mats.B1a = equationsToMatrix(rhs(x_1a_dot_eqn), VDefs.T_beta);

                    % y DIMENSION DERIVATIONS
                    %State vector augmented with integral of y
                    obj.stateVec_2a = [VDefs.iy, VDefs.y, VDefs.y_dot, VDefs.gamma, VDefs.gamma_dot].'; 
                    obj.stateVec_2a_dot = [VDefs.y, VDefs.y_dot, VDefs.y_ddot, VDefs.gamma_dot, VDefs.gamma_ddot].';
                    
                    
                    %Derive augmented dynamics for x direction
                    x_2a_dot_eqn = obj.stateVec_2a_dot == obj.stateVec_2a_dot;
                    x_2a_dot_eqn = obj.stateVec_2a_dot == subs(rhs(x_2a_dot_eqn),...
                        [VDefs.y_ddot VDefs.gamma_ddot] , [rhs(Lnrzed_EOMs.Lin_EOMs2(2)), rhs(Lnrzed_EOMs.Lin_EOMs2(4))]);
                    
                    %Augmented A Matrix
                    obj.sys_mats.A2a = equationsToMatrix(rhs(x_2a_dot_eqn), obj.stateVec_2a);
                    
                    %Augmented B Matrix
                    obj.sys_mats.B2a = equationsToMatrix(rhs(x_2a_dot_eqn), VDefs.T_gamma);    

                    %Set the name of the simulink model to use
                    obj.sim_file_string = 'FSFB_FF_Sim';
                    obj.HIL_file_string = 'FSFB_FF_HIL';
                    obj.ctrl_file_string = 'FSFB_FF_Controller';
                                    
                otherwise
                    
                    error('Not a valid controller type')
                    
            end
            
            
        end
        
        
        function [] = Run_Sim(obj, x_s, y_s, tspan, x_0, Tau, K1, K2)
            %Run_Sim Run a simulation for the control system specified by
            %obj.ctrl_type. 
            %   x_s and y_s are simfuns specifying the desired trajectories
            %   in the plate frame ball position variables. tspan specifies
            %   the simulation start and stop time. x_0 is the initial
            %   condition vector. Tau is the time constant for the first 
            %   order smoothing of the desired trajectory. K1 and K2 are 
            %   gain FSFB gain matrices.

            %Fill the control parameters struct for the Simulation run
            obj.Sim_cntrl_params.x_s = x_s;
            obj.Sim_cntrl_params.y_s = y_s;
            obj.Sim_cntrl_params.tspan = tspan;
            obj.Sim_cntrl_params.Tau = Tau;
            obj.Sim_cntrl_params.K1 = K1;
            obj.Sim_cntrl_params.K2 = K2;

            %Remove any dirac deltas from the derivatives of the setpoints. This function
            %returns the setpoint derivatives with any deltas resulting from
            %differentiation removed. Allows setpoints with jump discontinuities to be
            %handed in to Run_Sim. OTHER ISSUES WITH SETPOINTS THAT ARE TOO JUMPY THOUGH
            [d_x_s, d_y_s, dd_x_s, dd_y_s] = obj.remove_deltas(x_s, y_s);

            %Generate the setpoint vectors and store them in the
            %appropriate class properties.
            obj.Gen_Setpoints(x_s, y_s, d_x_s, d_y_s, dd_x_s, dd_y_s, tspan);

            
            %Load the objects controller Simulink file (referenced model within the
            %simulation file)
            load_system(strcat('Simulink Models/Models to Reference/',obj.ctrl_file_string))

            %Replace the definition of the "x_Setpoint_Function" MATLAB function block
            %with a function generated from x_setpoint_symfun
            block_path_string = strcat(obj.ctrl_file_string,'/Setpoint_Vectors/x_Setpoint_Function');
            matlabFunctionBlock(block_path_string, obj.x_s_vec,'FunctionName', 'x_s_vec')

            %Replace the definition of the "y_Setpoint_Function" MATLAB function block
            %with a function generated from y_setpoint_symfun
            block_path_string = strcat(obj.ctrl_file_string,'/Setpoint_Vectors/y_Setpoint_Function');
            matlabFunctionBlock(block_path_string, obj.y_s_vec,'FunctionName', 'y_s_vec')

            %If a feed-forward controller, replace the definition of the "u_FF" MATLAB function block       
            if strcmp(obj.ctrl_type,'FSFB FF Controller')
      
                block_path_string = strcat(obj.ctrl_file_string,'/u_FF');
                matlabFunctionBlock(block_path_string, obj.u_FF,'FunctionName', 'u_FF')

            end 

            %Load the Simulated_Plant model
            load_system('Simulink Models/Models to Reference/Simulated_Plant')

            %Replace the definition of the "Plant_Function" MATLAB function block with a
            %function generated from obj.plant symbolic function
            block_path_string = 'Simulated_Plant/Plant_Function';
            %Generate a matlab function from the linearized plant model
            input_chars = {'x', 'x_dot', 'beta', 'beta_dot','y', 'y_dot', 'gamma', 'gamma_dot', 'T_beta', 'T_gamma' };
            %output_chars = {'x_dot', 'x_ddot', 'beta_dot', 'beta_ddot','y_dot', 'y_ddot', 'gamma_dot', 'gamma_ddot' };
            matlabFunctionBlock(block_path_string, obj.plant, 'FunctionName', 'xdot','Vars',input_chars)
        
            %Load the systems simulation model
            %%load_system('Simulink Models/Models to Reference/Simulated_Plant')
            load_system(strcat('Simulink Models/Simulation/',obj.sim_file_string))

            %Set the Simulink Parameters (Matrices, times, gains, etc.)
            obj.SimIn = Simulink.SimulationInput(obj.sim_file_string);

            %Timespan
            obj.SimIn = obj.SimIn.setVariable('tspan',tspan);

            %Setpoint smoothing time constant
            obj.SimIn = obj.SimIn.setVariable('Tau',Tau);

            %ICs
            obj.SimIn = obj.SimIn.setVariable('x_0', x_0);

            %Gain matrix K1 - x direction
            obj.SimIn = obj.SimIn.setVariable('K1', K1);

            %Gain matrix K2 - y direction
            obj.SimIn = obj.SimIn.setVariable('K2', K2);

            %Saturation torque
            obj.SimIn = obj.SimIn.setVariable('Tmax',obj.VDefs.Tmax);

            %Run the configured simulation file
            obj.sim_response = sim(obj.SimIn);          
            
        end

        function [] = Run_HIL_Test(obj,x_s,y_s, tspan, Tau, K1, K2, Q_KF, R_KF)
            %Run_HIL_Test Run a Simulink Desktop Real-Time test on the
            %ball-and-plate hardware.
            %   x_s and y_s are simfuns specifying the desired trajectories
            %   in the plate frame ball position variables. tspan specifies
            %   the simulation start and stop time. x_0 is the initial
            %   condition vector. For now, the IC vector will be assumed 
            %   the zero vector. In the future, it would be ideal to have 
            %   access to a sensor reading of the IC for the ball. 
            %   Or perhaps, have a regulation controller run before the 
            %   trajectory tracking controller to place the state vector 
            %   at the origin. Tau is the time constant for the first 
            %   order smoothing of the desired trajectory. K1 and K2 are 
            %   gain FSFB gain matrices.

            %Fill the control parameters struct for the HIL run
            obj.HIL_cntrl_params.x_s = x_s;
            obj.HIL_cntrl_params.y_s = y_s;
            obj.HIL_cntrl_params.tspan = tspan;
            obj.HIL_cntrl_params.Tau = Tau;
            obj.HIL_cntrl_params.K1 = K1;
            obj.HIL_cntrl_params.K2 = K2;
            obj.HIL_cntrl_params.Q_KF = Q_KF;
            obj.HIL_cntrl_params.Q_KF = R_KF;
            obj.HIL_cntrl_params.Ts = 0.005; %0.005 is the frequency Scott says the system can handle

            %Remove any dirac deltas from the derivatives of the setpoints. This function
            %returns the setpoint derivatives with any deltas resulting from
            %differentiation removed. Allows setpoints with jump discontinuities to be
            %handed in to Run_Sim. OTHER ISSUES WITH SETPOINTS THAT ARE TOO JUMPY THOUGH
            [d_x_s, d_y_s, dd_x_s, dd_y_s] = obj.remove_deltas(x_s, y_s);

            %Generate the setpoint vectors and store them in the
            %appropriate class properties.
            obj.Gen_Setpoints(x_s, y_s, d_x_s, d_y_s, dd_x_s, dd_y_s, tspan);

            %Set up the Kalman filter
            obj.Gen_KF_Data;

            %Load the objects controller Simulink file (referenced model within the
            %simulation file)
            load_system(strcat('Simulink Models/Models to Reference/',obj.ctrl_file_string))

            %Replace the definition of the "x_Setpoint_Function" MATLAB function block
            %with a function generated from x_setpoint_symfun
            block_path_string = strcat(obj.ctrl_file_string,'/Setpoint_Vectors/x_Setpoint_Function');
            matlabFunctionBlock(block_path_string, obj.x_s_vec,'FunctionName', 'x_s_vec')

            %Replace the definition of the "y_Setpoint_Function" MATLAB function block
            %with a function generated from y_setpoint_symfun
            block_path_string = strcat(obj.ctrl_file_string,'/Setpoint_Vectors/y_Setpoint_Function');
            matlabFunctionBlock(block_path_string, obj.y_s_vec,'FunctionName', 'y_s_vec')

            %If a feed-forward controller, replace the definition of the "u_FF" MATLAB function block       
            if strcmp(obj.ctrl_type,'FSFB FF Controller')
      
                block_path_string = strcat(obj.ctrl_file_string,'/u_FF');
                matlabFunctionBlock(block_path_string, obj.u_FF,'FunctionName', 'u_FF')

            end 

            %Load the Simulated_Plant model
            load_system('Simulink Models/Models to Reference/Hardware_Plant')
        
            %Load the HIL Test file
            load_system(strcat('Simulink Models/Hardware Implementation/',obj.HIL_file_string))

            %Timespan
            assignin('base', "tspan",obj.HIL_cntrl_params.tspan)

            %Setpoint smoothing time constant
            assignin('base', "Tau",obj.HIL_cntrl_params.Tau)

            %Gain matrix K1 - x direction
            assignin('base', "K1",obj.HIL_cntrl_params.K1)

            %Gain matrix K2 - y direction
            assignin('base', "K2",obj.HIL_cntrl_params.K2)

            %Saturation torque
            assignin('base', "Tmax",obj.VDefs.Tmax)

            %Loop closure time
            assignin('base', "Ts",obj.HIL_cntrl_params.Ts) 
            
            %%For Kalman filter
            assignin('base', "Q_KF",Q_KF) %Process noise covariance matrix
            assignin('base', "R_KF",R_KF) %Measurement noise covariance martix

            %A matrix
            assignin('base', "A",double(obj.sys_mats.A_dscrt))

            %B matrix
            assignin('base', "B",double(obj.sys_mats.B_dscrt))

            %H matrix
            assignin('base', "H",obj.sys_mats.H)

            %Run the HIL test (don't know if there's another way to
            %programmatically run this)
            %%set_param(obj.HIL_file_string, 'SimulationCommand', 'start')


        end
        
        function [figure_obj_x, figure_obj_y] = plot_results(obj, title_str)
            %plot_results Plot simulation or HIL results. Format varies
            %with the type of controller specified by obj.ctrl_type


            switch obj.ctrl_type
                
                case 'FSFB Integral Controller'
                    
                    figure_obj_x = figure;
                    
                    title('SS_Integral_Controller x direction');
                    
                    ax1 = subplot(4,1,1);
                    plot(obj.sim_response.tout,obj.sim_response.x(:,1),...
                        obj.sim_response.tout,obj.sim_response.x_s_vec,'--r' )
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
                    set(gcf,'position',[0,0,1200,1200]);   

                    figure_obj_y = figure;
                    
                    ax1 = subplot(3,1,1);
                    plot(obj.sim_response.tout,obj.sim_response.x(:,5),...
                        obj.sim_response.tout,obj.sim_response.y_s_vec,'--r' )
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
                    set(gcf,'position',[0,0,1200,1200]);   
                    
                    %Plot the position space of the ball
                    i_plot = obj.sim_response.tout > obj.sim_response.tout(round(length(obj.sim_response.tout)/2));
                    figure
                    plot(obj.sim_response.x(i_plot,1), obj.sim_response.x(i_plot,5),'b',...
                         obj.sim_response.x_s_vec(i_plot,1), obj.sim_response.y_s_vec(i_plot,1), '--r')
                    xlabel('x [m]')
                    ylabel('y [m]')
                    title('Position space of the ball in the plate frame')
                    axis 'equal'
                    
                case 'FSFB PID Controller' 
                    
                    figure_obj_x = figure;
                    
                    
                    ax1 = subplot(4,1,1);
                    plot(obj.sim_response.tout,obj.sim_response.x(:,1),'b',obj.sim_response.tout,obj.sim_response.x_s_vec(:,1),'--r' )
                    xlabel('time [s]')
                    ylabel('x [m]')
                    title(strcat(title_str,' x direction'))
                    legend('actual', 'setpoint')

                    ax2 = subplot(4,1,2);
                    plot(obj.sim_response.tout,rad2deg(obj.sim_response.x(:,3)),'b')
                    xlabel('time [s]')
                    ylabel('\beta [deg]')


                    ax3 = subplot(4,1,3);
                    plot(obj.sim_response.tout,obj.sim_response.u(:,1),'b')
                    xlabel('time [s]')
                    ylabel('T_{\beta} [Nm]')

                    ax4 = subplot(4,1,4);
                    plot(obj.sim_response.tout,(obj.sim_response.x_s_vec(:,1) - obj.sim_response.x(:,1)),'b')
                    xlabel('time [s]')
                    ylabel('error in x [m]')

                    linkaxes([ax1,ax2, ax3, ax4],'x');
                    set(gcf,'position',[0,0,1200,1200]);

                    figure_obj_y = figure;

                    ax1 = subplot(3,1,1);
                    plot(obj.sim_response.tout,obj.sim_response.x(:,5),'b',obj.sim_response.tout,obj.sim_response.y_s_vec(:,1),'--r' )
                    xlabel('time [s]')
                    ylabel('y [m]')
                    title(strcat(title_str,' y direction'))
                    legend('actual', 'setpoint')

                    ax2 = subplot(3,1,2);
                    plot(obj.sim_response.tout,rad2deg(obj.sim_response.x(:,7)),'b')
                    xlabel('time [s]')
                    ylabel('\gamma [deg]')


                    ax3 = subplot(3,1,3);
                    plot(obj.sim_response.tout,obj.sim_response.u(:,2),'b')
                    xlabel('time [s]')
                    ylabel('T_{\gamma} [Nm]')
                    
                    linkaxes([ax1,ax2, ax3],'x');
                    set(gcf,'position',[0,0,1200,1200]);

                    %Plot the position space of the ball
                    i_plot = obj.sim_response.tout > obj.sim_response.tout(round(length(obj.sim_response.tout)/2));
                    figure
                    plot(obj.sim_response.x(i_plot,1), obj.sim_response.x(i_plot,5),'b',...
                         obj.sim_response.x_s_vec(i_plot,1), obj.sim_response.y_s_vec(i_plot,1),'--r')
                    xlabel('x [m]')
                    ylabel('y [m]')
                    title('Position space of the ball in the plate frame')
                    axis 'equal'
                     
               case 'FSFB FF Controller'

                    figure_obj_x = figure;
                    
                    
                    ax1 = subplot(4,1,1);
                    plot(obj.sim_response.tout,obj.sim_response.x(:,1),'b',obj.sim_response.tout,obj.sim_response.x_s_vec(:,1),'--r' )
                    xlabel('time [s]')
                    ylabel('x [m]')
                    title(strcat(title_str,' x direction'))
                    legend('actual', 'setpoint')


                    ax2 = subplot(4,1,2);
                    plot(obj.sim_response.tout,rad2deg(obj.sim_response.x(:,3)),'b',...
                         obj.sim_response.tout,rad2deg(obj.sim_response.x_s_vec(:,3)), '--r')
                    xlabel('time [s]')
                    ylabel('\beta [deg]')
                    legend('actual', 'setpoint')


                    ax3 = subplot(4,1,3);
                    plot(obj.sim_response.tout,obj.sim_response.u(:,1),'b',obj.sim_response.tout,obj.sim_response.u_FF(:,1), '--r')
                    xlabel('time [s]')
                    ylabel('T_{\beta} [Nm]')
                    legend('total torque', 'feed-forward torque')

                    ax4 = subplot(4,1,4);
                    plot(obj.sim_response.tout,(obj.sim_response.x_s_vec(:,1) - obj.sim_response.x(:,1)),'b')
                    xlabel('time [s]')
                    ylabel('error in x [m]')


                    linkaxes([ax1,ax2, ax3, ax4],'x');
                    set(gcf,'position',[0,0,1200,1200]);

                    figure_obj_y = figure;

                    ax1 = subplot(4,1,1);
                    plot(obj.sim_response.tout,obj.sim_response.x(:,5),'b',obj.sim_response.tout,obj.sim_response.y_s_vec(:,1),'--r' )
                    xlabel('time [s]')
                    ylabel('y [m]')
                    title(strcat(title_str,' y direction'))
                    legend('actual', 'setpoint')

                    ax2 = subplot(4,1,2);
                    plot(obj.sim_response.tout,rad2deg(obj.sim_response.x(:,7)),'b', ...
                         obj.sim_response.tout,rad2deg(obj.sim_response.y_s_vec(:,3)),'--r')
                    xlabel('time [s]')
                    ylabel('\gamma [deg]')
                    legend('actual', 'setpoint')

                    ax3 = subplot(4,1,3);
                    plot(obj.sim_response.tout,obj.sim_response.u(:,2),'b',obj.sim_response.tout,obj.sim_response.u_FF(:,2), '--r')
                    xlabel('time [s]')
                    ylabel('T_{\gamma} [Nm]')
                    legend('total torque', 'feed-forward torque')
                    
                    ax4 = subplot(4,1,4);
                    plot(obj.sim_response.tout,(obj.sim_response.y_s_vec(:,1) - obj.sim_response.x(:,5)),'b')
                    xlabel('time [s]')
                    ylabel('error in y [m]')

                    linkaxes([ax1,ax2, ax3, ax4],'x');
                    set(gcf,'position',[0,0,1200,1200]);

                    %Plot the position space of the ball
                    i_plot = obj.sim_response.tout > obj.sim_response.tout(round(length(obj.sim_response.tout)/2));
                    figure
                    plot(obj.sim_response.x(i_plot,1), obj.sim_response.x(i_plot,5),'b',...
                         obj.sim_response.x_s_vec(i_plot,1), obj.sim_response.y_s_vec(i_plot,1), '--r')
                    xlabel('x [m]')
                    ylabel('y [m]')
                    title('Position space of the ball in the plate frame')
                    axis 'equal'


            end 
            
        end 
        
        

        function [] = Gen_Setpoints (obj, x_s, y_s, d_x_s, d_y_s, dd_x_s, dd_y_s, tspan)

            %Depending on the control architecture, generate x_s_vec, y_s_vec, and u_FF
            %from x_setpoint_symfun and y_setpoint_symfun
            switch obj.ctrl_type
                case 'FSFB Integral Controller'

                    %Setpoint vectors here are just the smoothed x and y setpoints
                    obj.x_s_vec = x_s;
                    obj.y_s_vec = y_s;
                   

                case 'FSFB PID Controller' 



                    %For the PID the setpoint vector contains the derivative of 
                    % the desired x and y trajectories. 

                    obj.x_s_vec = [x_s; d_x_s]; 
                    obj.y_s_vec = [y_s; d_y_s];


                case 'FSFB FF Controller'

                    %Solve for the angular setpoints that are consistent with the x and y
                    %setpoints (in the linear dynamics)

                    syms beta_s(t) gamma_s(t) C1 C2

                    %Beta 
                    T_beta_eqn = isolate(obj.VDefs.beta_ddot == obj.Lnrzed_EOMs.Lin_EOMs(4), obj.VDefs.T_beta);
                    T_beta_eqn = subs(T_beta_eqn,[obj.VDefs.beta, obj.VDefs.beta_ddot],[beta_s, diff(beta_s,2)]);    
                    ode_beta_s = dd_x_s == subs(obj.Lnrzed_EOMs.Lin_EOMs(2), obj.VDefs.T_beta, rhs(T_beta_eqn));
                    ode_beta_s = subs(ode_beta_s, obj.VDefs.beta, beta_s); 
                    %Solve the linear ODE for beta_s(t)
                    beta_s_sol(obj.VDefs.t) = dsolve(ode_beta_s);
                    %Take only the particular solution 
                    beta_s_sol(obj.VDefs.t) = simplify(subs(beta_s_sol, [C1 C2], [0 0]));

                    %Plot the particular solution
%                     figure
%                     fplot(matlabFunction(beta_s_sol),tspan)
%                     xlabel('Time [s]')
%                     ylabel('beta [rad]')
%                     title('beta analytical particular solution')

                    %Gamma
                    T_gamma_eqn = isolate(obj.VDefs.gamma_ddot == obj.Lnrzed_EOMs.Lin_EOMs(8), obj.VDefs.T_gamma);
                    T_gamma_eqn = subs(T_gamma_eqn,[obj.VDefs.gamma, obj.VDefs.gamma_ddot],[gamma_s, diff(gamma_s,2)]);    
                    ode_gamma_s = dd_y_s == subs(obj.Lnrzed_EOMs.Lin_EOMs(6), obj.VDefs.T_gamma, rhs(T_gamma_eqn));
                    ode_gamma_s = subs(ode_gamma_s, obj.VDefs.gamma, gamma_s); 
                    %Solve the linear ODE for gamma_s(t)
                    gamma_s_sol(obj.VDefs.t) = simplify(dsolve(ode_gamma_s));
                    %Take only the particular solution 
                    gamma_s_sol(obj.VDefs.t) = simplify(subs(gamma_s_sol, [C1 C2], [0 0]));
                    
                    %Plot the particular solution
%                     figure
%                     fplot(matlabFunction(gamma_s_sol),tspan)
%                     xlabel('Time [s]')
%                     ylabel('gamma [rad]')
%                     title('gamma analytical particular solution')

                    %Feed-Forward input functions
                    T_beta(obj.VDefs.t) = subs(rhs(T_beta_eqn), [obj.VDefs.x, beta_s, diff(beta_s,2)], [x_s beta_s_sol diff(beta_s_sol,2)]);
                    T_gamma(obj.VDefs.t) = expand(simplify(subs(rhs(T_gamma_eqn), [obj.VDefs.y, gamma_s, diff(gamma_s,2)], [y_s gamma_s_sol diff(gamma_s_sol,2)])));
                    obj.u_FF = [T_beta;T_gamma];

                    %Bring setpoints together into the setpoint vectors
                    obj.x_s_vec = [x_s; d_x_s; beta_s_sol; diff(beta_s_sol)];
                    obj.y_s_vec = [y_s; d_y_s; gamma_s_sol; diff(gamma_s_sol)];                  


            end 

        end


        function [] = Gen_KF_Data(obj)
            
            %Observation matrix (extracts measured values from state
            %vector)
            obj.sys_mats.H = zeros(6,8);
            obj.sys_mats.H(1,1) = 1; %Ball x position is measured (Touch Screen)
            obj.sys_mats.H(2,3) = 1; %beta is measured (IMU) 
            obj.sys_mats.H(3,4) = 1; %beta_dot is measured (IMU)
            obj.sys_mats.H(4,5) = 1; %Ball y position is measured (Touch Screen)
            obj.sys_mats.H(5,7) = 1; %gamma is measured (IMU) 
            obj.sys_mats.H(6,8) = 1; %gamma_dot is measured (IMU) 
            
            A = double(obj.Lnrzed_EOMs.A);
            B = double(obj.Lnrzed_EOMs.B);
            discreteSys = ss(A,B, eye(8),zeros(8,2),obj.HIL_cntrl_params.Ts);
            obj.sys_mats.A_dscrt = discreteSys.A;
            obj.sys_mats.B_dscrt = discreteSys.B;
            
        end

    end



    methods (Static)
        function [d_x_s, d_y_s, dd_x_s, dd_y_s] = remove_deltas(x_s, y_s)

                    %Make sure there are no dirac delta's in the derivatives of the
                    %setpoint functions

                    %First derivatives
                    d_x_s = diff(x_s,1);
                    sub_exps_d_x_s = children(d_x_s); %get each term in the derivative
                    for n = 1:length(sub_exps_d_x_s)
                        %If there is a delta, set its term to zero
                        if hasSymType(sub_exps_d_x_s{n},'dirac')
                            sub_exps_d_x_s{n} = sym(0);
                        end
                    
                    end
                    d_x_s = sum(cell2sym(sub_exps_d_x_s));
                    
                    d_y_s = diff(y_s,1);
                    sub_exps_d_y_s = children(d_y_s); %get each term in the derivative
                    for n = 1:length(sub_exps_d_x_s)
                        %If there is a delta, set its term to zero
                        if hasSymType(sub_exps_d_y_s{n},'dirac')
                            sub_exps_d_y_s{n} = sym(0);
                        end
                    
                    end
                    d_y_s = sum(cell2sym(sub_exps_d_y_s));


                    %Second derivatives
                    dd_x_s = diff(d_x_s,1);
                    sub_exps_dd_x_s = children(dd_x_s); %get each term in the derivative
                    for n = 1:length(sub_exps_dd_x_s)
                        %If there is a delta, set its term to zero
                        if hasSymType(sub_exps_d_y_s{n},'dirac')
                            sub_exps_d_y_s{n} = 0;
                        end
                    
                    end
                    dd_x_s = sum(cell2sym(sub_exps_dd_x_s));
                    
                    dd_y_s = diff(d_y_s,1);
                    sub_exps_dd_y_s = children(dd_y_s); %get each term in the derivative
                    for n = 1:length(sub_exps_dd_x_s)
                        %If there is a delta, set its term to zero
                        if hasSymType(sub_exps_d_y_s{n},'dirac')
                            sub_exps_d_y_s{n} = 0;
                        end
                    
                    end
                    dd_y_s = sum(cell2sym(sub_exps_dd_y_s));

        end


    end
end

