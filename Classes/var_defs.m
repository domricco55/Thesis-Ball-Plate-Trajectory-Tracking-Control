classdef Var_Defs
    %This class defines symbolic variables, generally, for use with the symbolic
    %toolbox throughout the Ball and Plate thesis project. 
    %   Defines symvars and symfuns for scalars, vectors, and matrices. The
    %   definitions are kept as general as possible and no component is yet
    %   defined in terms of other system parameters, state variables, etc. 
    
    properties (SetAccess = public
    %Scalars
        %Miscellaneous
        t %time symbolic variable
        g %gravitational constant symbolic variable
        
        %Angle Variables
        
        %Angular Velocities for Omega Vectors/Matrices
        
    %Vectors
    
    %Matrices
    
    %State Space Model - Related
    
    %
    end
    
%     properties (SetAccess = private)
%         
%     end 
    
    methods
        function obj = Var_Defs(inputArg1,inputArg2)
            %UNTITLED Construct an instance of this class
            %   Detailed explanation goes here
%             obj.Property1 = inputArg1 + inputArg2;
        end
        
        function outputArg = method1(obj,inputArg)
            %METHOD1 Summary of this method goes here
            %   Detailed explanation goes here
            outputArg = obj.Property1 + inputArg;
        end
    end
end

