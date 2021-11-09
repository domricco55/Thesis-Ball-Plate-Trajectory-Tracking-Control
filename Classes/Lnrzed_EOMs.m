classdef Lnrzed_EOMs < handle
    %Lnrze_EOMs Summary of this class goes here
    %   Detailed explanation goes here
    
    properties (SetAccess = private)
        %Ball Plate System Objects
        VDefs
        BP_Kinetics
        
        %8th order system
        y_vec
        C
        D
        C_obs
        D_obs
        A
        B

        %Two Uncoulpled 4th order systems
        A1
        B1
        A2
        B2
        Lin_EOMs
        Lin_EOMs1
        Lin_EOMs2
    end
    
    methods
        function obj = Lnrzed_EOMs(Var_Defs, BP_Kinetics)
            %Lnrzed_EOMs Construct an instance of this class
            %   Detailed explanation goes here
            
            
            %Assign the inputs to the constructor to the class properties
            obj.VDefs = Var_Defs;          
            obj.BP_Kinetics = BP_Kinetics;
            
        end 
        
        function [A, B, y_vec, C, D, C_obs, D_obs, TF, Lin_EOMs] = Derive_8th_Ordr_Lin_Sys(obj)
            %Derive_8th_Ordr_Lin_Sys Linearize the NL EOMS and produce an 8th order linear
            %system of equations representing the dynamics near the unstable equilibrium
            %point
            %   Detailed explanation goes here
            
            
            %Derive the linearized 8th order equations of motion
            J_states(obj.VDefs.stateVec) = jacobian(rhs(obj.BP_Kinetics.NL_NumEOMs),...
                obj.VDefs.stateVec); %Take Jacobian WRT States
            J_inputs(obj.VDefs.stateVec) = jacobian(rhs(obj.BP_Kinetics.NL_NumEOMs),...
                obj.VDefs.inputVec); %Take Jacobian WRT Inputs
            
            %State Coupling and Input Matrices from evaluation of the Jacobians at the
            %unstable equilibrium point
            obj.A = J_states(0,0,0,0,0,0,0,0);
            obj.B = J_inputs(0,0,0,0,0,0,0,0);
            
            A = obj.A;
            B =obj.B;

            
            %Define these symbolic quantities for use in further analysis:
            obj.y_vec = [obj.VDefs.x obj.VDefs.y obj.VDefs.beta obj.VDefs.gamma].';
            obj.C = sym([1 0 0 0 0 0 0 0;0 0 1 0 0 0 0 0;0 0 0 0 1 0 0 0;0 0 0 0 0 0 1 0]);
            obj.D = sym(zeros(4,2));  
            
            %Get system transfer function
            obj.C_obs = eye(8);
            obj.D_obs = sym(zeros(8,2));
            TF = obj.C_obs*(obj.VDefs.s*eye(8) - obj.A)\obj.B + obj.D_obs; 

            %Create symbolic equation object for the total system (used later in
            %control system design)
            obj.Lin_EOMs = obj.A*obj.VDefs.stateVec + obj.B*[obj.VDefs.T_beta;obj.VDefs.T_gamma];

           %Return outputs
            y_vec = obj.y_vec;
            C = obj.C;
            D = obj.D;
            C_obs = obj.C_obs;
            D_obs = obj.D_obs;
            Lin_EOMs = obj.Lin_EOMs;
            
        end
        
        function [A1, B1, A2, B2, Lin_EOMs1, Lin_EOMs2] = Derive_4th_Ordr_Lin_Sys(obj)
            %Derive_4th_Ordr_Lin_Sys Separate the uncoupled linear equations of the 8th
            %order system into two entirely separate 4th order linear systems
            %   Detailed explanation goes here
            
            %Extract out the elements from A_uc and B_uc associated with the two decoupled
            %4th order systems
            obj.A1 = obj.A(1:4,1:4);
            obj.B1 = obj.B(1:4,1);
            obj.A2 = obj.A(5:8,5:8);
            obj.B2 = obj.B(5:8,2);

            %Create symbolic equation object for each of these two systems (used later in
            %control system design)
            obj.Lin_EOMs1 = obj.VDefs.stateVec1_dot == obj.A1*obj.VDefs.stateVec1 + obj.B1*obj.VDefs.T_beta;
            obj.Lin_EOMs2 = obj.VDefs.stateVec2_dot == obj.A2*obj.VDefs.stateVec2 + obj.B2*obj.VDefs.T_gamma;
            
            %Return Outputs
            A1 = obj.A1;
            B1 = obj.B1;
            A2 = obj.A2;
            B2 = obj.B2;
            Lin_EOMs1 = obj.Lin_EOMs1;
            Lin_EOMs2 = obj.Lin_EOMs2;
            
        end

        
    end
end

