classdef NL_Dcpld_EOMs <handle
    %NL_Dcpld_EOMs Summary of this class goes here
    %   Detailed explanation goes here

    properties (SetAccess = private)
        VDefs
        BP_Kinetics

    end

    methods
        function obj = NL_Dcpld_EOMs(Var_Defs, BP_Kinetics)
            %NL_Dcpld_EOMs Construct an instance of this class
            %   Detailed explanation goes here

            %Assign the inputs to the constructor to the class properties
            obj.VDefs = Var_Defs;          
            obj.BP_Kinetics = BP_Kinetics;

            

        end


    end
end