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

    end

    methods
        function obj = NL_Dcpld_EOMs(VDefs, BP_Kinetics)
            %NL_Dcpld_EOMs Construct an instance of this class
            %   Detailed explanation goes here

            %Assign the inputs to the constructor to the class properties
            obj.VDefs = VDefs;          
            obj.BP_Kinetics = BP_Kinetics;

            %Decouple the x axis

            %Ball Kinetics  x only
            obj.SumMBall_x = simplify(subs(obj.BP_Kinetics.SumMBall(2),[obj.VDefs.gamma obj.VDefs.gamma_dot obj.VDefs.gamma_ddot ], [0 0 0]));
            
            %Plate Kinetics x only
            obj.SumMPlate_x = subs(obj.BP_Kinetics.SumMPlate(2),[obj.VDefs.gamma obj.VDefs.gamma_dot obj.VDefs.gamma_ddot], [0 0 0]);

            %Bring Together Nonlinear Decoupled Moment Equations and Solve for Highest Order Terms
            EOMS_x = [obj.SumMBall_x;obj.SumMPlate_x];
            [CoeffMat_x,ExtTerms_x] = equationsToMatrix(EOMS_x , [obj.VDefs.x_ddot, obj.VDefs.beta_ddot]); 
            obj.SolvedEOMs_x = obj.VDefs.stateVec1_dot == [obj.VDefs.x_dot; [1 0]*(CoeffMat_x\ExtTerms_x); obj.VDefs.beta_dot;[0 1]*(CoeffMat_x\ExtTerms_x)];


        end

        function [] = Num_Params_n_Assumptions(obj)


        end
    end
end