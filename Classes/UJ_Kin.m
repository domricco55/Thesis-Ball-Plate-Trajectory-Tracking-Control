classdef UJ_Kin
    %UJ_Kin This class generates the 
    %   Detailed explanation goes here
    
    properties
        VDefs
        r0s
    end
    
    methods
        function obj = UJ_Kin(Var_Defs)
            %UNTITLED Construct an instance of this class
            %   Detailed explanation goes here
            
            %Assign the Var_Defs object that was in the constructor argument to the
            %classes VDefs property
            obj.VDefs = Var_Defs;
            
            %Derive r0s, the arbitrary displacement vector originally defined in frame S2,
            %rotated into the S0 basis
            obj.r0s = obj.VDefs.R20*obj.VDefs.r2s;
            
        end
    end
end

