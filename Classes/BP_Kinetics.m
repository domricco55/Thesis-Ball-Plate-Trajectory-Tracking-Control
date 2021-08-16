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
        SolvedEOMs
        
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
        
        
        function [Omega2b, Hb2s, Hb2ds, SumMBall, Hp1s] = Derive_NL_EOMs(obj)
            %Derive_NL_EOMs Derive the Equations of Motion for the Ball and Plate system
            %   Detailed explanation goes here 
            
            %Derive the ball's angular momentum vector
            Omega2b = obj.UJ_Knmtcs.Omega2vs + obj.BP_Knmtcs.Psi2vs;
            Hb2s = expand(obj.VDefs.Ib2ms*(Omega2b));
           
            %Find the time derivative of Hb2s
            Hb2ds = expand(simplify(obj.VDefs.R02*diff(obj.VDefs.R20*Hb2s)));
            Hb2ds = subs(Hb2ds, obj.VDefs.symFunVec, obj.VDefs.symVarVec); %NO LONGER NEED TO DIFFERENTIATE 
                                                                           %so I can subsitute the symfuns for symvars
                                                                           
            %Take the sum of moments about the ball's contact point, for the ball alone.
            %This is done in the S2 basis. 
            SumMBall = expand(cross(obj.VDefs.armb2s, obj.VDefs.R02*obj.VDefs.Wb0s) == ...
                cross(obj.VDefs.armb2s, obj.VDefs.m_b*obj.BP_Knmtcs.ab2s) + Hb2ds);
            SumMBall = subs(SumMBall, obj.VDefs.symFunVec, obj.VDefs.symVarVec);
            
            %Derive the Plate's angular momentum vector. First, find it in the S2 basis,
            %then rotate it into the S1 basis - moments will be taken in the u-joint axle
            %frame
            Hp2s = obj.VDefs.Ip2ms*(obj.UJ_Knmtcs.Omega2vs); %In S2, the plates Inertia tensor is easily defined and its angular velocity is known from prior analysis
            Hp1s = obj.VDefs.R21*Hp2s; %Apply rotation matrix to S2 angular momentum vector
           
           
           
           
        end 
        

        
    end
    
end

