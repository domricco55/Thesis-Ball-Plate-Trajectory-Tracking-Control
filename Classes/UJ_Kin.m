classdef UJ_Kin
    %UJ_Kin This class generates the 
    %   Detailed explanation goes here
    
    properties
        VDefs
    end
    
    methods
        function obj = untitled(VDefs)
            %UNTITLED Construct an instance of this class
            %   Detailed explanation goes here
            obj.VDefs = VDefs;
        end
        
        function outputArg = method1(obj,inputArg)
            %METHOD1 Summary of this method goes here
            %   Detailed explanation goes here
            outputArg = obj.Property1 + inputArg;
        end
    end
end

