classdef BP_Kin < handle
    %BP_Kin This class generates the kinematic equations for the motion of the ball
    %   Detailed explanation goes here
    
    properties

    end
   
    properties (SetAccess = private)
        VDefs
        UJ_Kin
    end 
    
    methods
        function obj = BP_Kin(Var_Defs, UJ_Kin)
            %UNTITLED Construct an instance of this class
            %   Detailed explanation goes here
            
            
            %Assign the inputs to the constructor to the class properties
            obj.VDefs = Var_Defs;          
            obj.UJ_Kin = UJ_Kin;

        end
        
        
        function [] = derive_(obj)
            %UNTITLED Construct an instance of this class
            %   Detailed explanation goes here 
            

            
        end 
        
        function [] = derive_(obj)  
            %UNTITLED Construct an instance of this class
            %   Detailed explanation goes here
            
            
            
        end
        
        function [] = derive_(obj)
            %UNTITLED Construct an instance of this class
            %   Detailed explanation goes here 
            
           
            
        end
        
    end
end

