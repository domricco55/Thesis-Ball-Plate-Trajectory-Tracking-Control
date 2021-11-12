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

        %x-axis results
        SumMBall_y
        SumMPlate_y
        SolvedEOMs_y
        g_2
        f_2

        %Total decoupled system
        f
        g
        DcpldEOMs
        
        %Numerical EOMs
        NumDcpldEOMs
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


            %Decouple the y axis

            %Ball Kinetics y direction
            obj.SumMBall_y = simplify(subs(obj.BP_Kinetics.SumMBall(1),[obj.VDefs.beta obj.VDefs.beta_dot obj.VDefs.beta_ddot ], [0 0 0]));
            
            %Plate Kinetics y direction
            obj.SumMPlate_y = subs(obj.BP_Kinetics.SumMPlate(1),[obj.VDefs.beta obj.VDefs.beta_dot obj.VDefs.beta_ddot ], [0 0 0]);

            %Bring Together Nonlinear Decoupled Moment Equations and Solve for Highest Order Terms
            EOMS_y = simplify([obj.SumMBall_y;obj.SumMPlate_y]);
            [CoeffMat_y,ExtTerms_y] = equationsToMatrix(EOMS_y , [obj.VDefs.y_ddot, obj.VDefs.gamma_ddot]); 
            obj.SolvedEOMs_y = obj.VDefs.stateVec2_dot == [obj.VDefs.y_dot; [1 0]*(CoeffMat_y\ExtTerms_y); obj.VDefs.gamma_dot;[0 1]*(CoeffMat_y\ExtTerms_y)];


            %Find input matrix g(y) y direction
            [obj.g_2,g_2_extra_terms] = equationsToMatrix(obj.SolvedEOMs_y , obj.VDefs.T_gamma);
            obj.g_2 = -obj.g_2;
            g_2_extra_terms = -g_2_extra_terms;
            
            obj.f_2 = - g_2_extra_terms + obj.VDefs.stateVec2_dot;

            %Total Decoupled System
            obj.f = [obj.f_1;obj.f_2];
            obj.g = [obj.g_1,zeros(size(obj.g_1));zeros(size(obj.g_1)),obj.g_2];
            obj.DcpldEOMs = obj.VDefs.stateVec_dot == obj.f + obj.g*obj.VDefs.inputVec;    


        end

        function [] = Num_Params(obj)
        %Num_ParamsInput estimated numerical parameters of the system
            %   Detailed explanation goes here
            

            %Numerical Parameters in terms of symbolic variables utilized in 
            %the model 
            Num_Params = [obj.VDefs.rB  (obj.VDefs.rC+obj.VDefs.rB) ...
            obj.VDefs.mB obj.VDefs.mP obj.VDefs.IP obj.VDefs.IB ...
            obj.VDefs.g_num obj.VDefs.rG];
        
            Sym_Params = [obj.VDefs.r_b obj.VDefs.z_b obj.VDefs.m_b...
                obj.VDefs.m_p obj.VDefs.I_p__xx obj.VDefs.I_b obj.VDefs.g...
                obj.VDefs.z_p];
            
            
            %Substitute in all numerical parameters and assumptions
            obj.NumDcpldEOMs = subs(obj.DcpldEOMs, Sym_Params, Num_Params );
            
        end
    end
end