classdef BP_Kinetics < handle
    %BP_Kinetics This class generates the kinetic equations of motion for the system in
    %terms of the state variables. 
    %   Detailed explanation goes here
    
    properties
        
    end
   
    properties (SetAccess = private)
        VDefs
        UJ_Knmtcs
        BP_Knmtcs
        vb2s
        ab2s
        Psi2vs
        vp2s
        ap2s
    end 
    
    methods
        function obj = BP_Kinetics(Var_Defs, UJ_Knmtcs, BP_Knmtcs)
            %UNTITLED Construct an instance of this class
            %   Detailed explanation goes here
            
            
            %Assign the inputs to the constructor to the class properties
            obj.VDefs = Var_Defs;          
            obj.UJ_Knmtcs = UJ_Knmtcs;
            obj.BP_Knmtcs = BP_Knmtcs;

        end
        
        
        function [] = Derive...(obj)
            %UNTITLED Construct an instance of this class
            %   Detailed explanation goes here 
            
           
            
        end 
        
        function [] = Derive...(obj)  
            %UNTITLED Construct an instance of this class
            %   Detailed explanation goes here
        
        end
        
        function [] = Derive...(obj)
            %UNTITLED Construct an instance of this class
            %   Detailed explanation goes here 
         
           
        end
        
    end
end

