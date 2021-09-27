classdef Lnrzed_EOMs < handle
    %Lnrze_EOMs Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        Property1
    end
    
    methods
        function obj = Lnrzed_EOMs(Var_Defs, UJ_Knmtcs, BP_Kineticss)
            %UNTITLED Construct an instance of this class
            %   Detailed explanation goes here
            
            
            %Assign the inputs to the constructor to the class properties
            obj.VDefs = Var_Defs;          
            obj.UJ_Knmtcs = UJ_Knmtcs;
            obj.BP_Kinetics = BP_Kinetics;
        end 
        

        end
    end
end

