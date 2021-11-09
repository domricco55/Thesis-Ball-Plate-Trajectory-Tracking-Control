classdef NL_Dcpld_EOMs <handle
    %NL_Dcpld_EOMs Summary of this class goes here
    %   Detailed explanation goes here

    properties (SetAccess = private)
        %Ball Plate System Objects
        VDefs
        BP_Kinetics

        %x-axis results
        SumMBall_x
        SumMPlate_x
        SolvedEOMs_x
        g_1
        f_1

        %Numerical EOMs

    end

    methods
        function obj = NL_Dcpld_EOMs(VDefs, BP_Kinetics)
            %NL_Dcpld_EOMs Construct an instance of this class
            %   Detailed explanation goes here

            %Assign the inputs to the constructor to the class properties
            obj.VDefs = VDefs;          
            obj.BP_Kinetics = BP_Kinetics;

            %Decouple the x axis

            %Ball Kinetics x direction
            obj.SumMBall_x = simplify(subs(obj.BP_Kinetics.SumMBall(2),[obj.VDefs.gamma obj.VDefs.gamma_dot obj.VDefs.gamma_ddot ], [0 0 0]));
            
            %Plate Kinetics x direction
            obj.SumMPlate_x = subs(obj.BP_Kinetics.SumMPlate(2),[obj.VDefs.gamma obj.VDefs.gamma_dot obj.VDefs.gamma_ddot], [0 0 0]);

            %Bring Together Nonlinear Decoupled Moment Equations and Solve for Highest Order Terms
            EOMS_x = [obj.SumMBall_x;obj.SumMPlate_x];
            [CoeffMat_x,ExtTerms_x] = equationsToMatrix(EOMS_x , [obj.VDefs.x_ddot, obj.VDefs.beta_ddot]); 
            obj.SolvedEOMs_x = obj.VDefs.stateVec1_dot == [obj.VDefs.x_dot; [1 0]*(CoeffMat_x\ExtTerms_x); obj.VDefs.beta_dot;[0 1]*(CoeffMat_x\ExtTerms_x)];

            %Find input matrix g(x) x direction
            [obj.g_1,g_1_extra_terms] = equationsToMatrix(obj.SolvedEOMs_x , obj.VDefs.T_beta);
            obj.g_1 = -obj.g_1;
            g_1_extra_terms = -g_1_extra_terms;
            
            obj.f_1 = - g_1_extra_terms + obj.VDefs.stateVec1_dot;
        end

        function [] = Num_Params_n_Assumptions(obj)
%         %Num_Params_n_Assumptions Input estimated numerical parameters of the system
%             % and simplify the system with a few assumptions
%             %   Detailed explanation goes here
%             
% 
%             %Numerical Parameters in terms of symbolic variables utilized in 
%             %the model 
%             Num_Params = [obj.VDefs.rB  (obj.VDefs.rC+obj.VDefs.rB) ...
%             obj.VDefs.mB obj.VDefs.mP obj.VDefs.IP obj.VDefs.IB ...
%             obj.VDefs.g_num obj.VDefs.rG];
%         
%             Sym_Params = [obj.VDefs.r_b obj.VDefs.z_b obj.VDefs.m_b...
%                 obj.VDefs.m_p obj.VDefs.I_p__xx obj.VDefs.I_b obj.VDefs.g...
%                 obj.VDefs.z_p];
%             
%             %Simplifying assumptions
%             Assumption_Params = [obj.VDefs.psi_dot_z obj.VDefs.psi_z obj.VDefs.I_p__zz];
%             Assumptions = [0 0 0];
%             
%             %Substitute in all numerical parameters and assumptions
%             obj.NL_NumEOMs = subs(obj.NL_EOMs, [Sym_Params Assumption_Params],[Num_Params  Assumptions]);
%             
%             %Return outputs
%             NL_NumEOMs = obj.NL_NumEOMs;

        end
    end
end