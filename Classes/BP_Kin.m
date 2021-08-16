classdef BP_Kin < handle
    %BP_Kin This class generates the kinematic equations for the motion of the centers of
    %mass of the ball and the plate.
    %   Detailed explanation goes here
    
    properties
        
    end
   
    properties (SetAccess = private)
        VDefs
        UJ_Kin
        
        vb2s
        ab2s
        Psi2vs
        vp2s
        ap2s
    end 
    
    methods
        function obj = BP_Kin(Var_Defs, UJ_Kin)
            %UNTITLED Construct an instance of this class
            %   Detailed explanation goes here
            
            
            %Assign the inputs to the constructor to the class properties
            obj.VDefs = Var_Defs;          
            obj.UJ_Kin = UJ_Kin;

        end
        
        
        function [vb2s, ab2s, constr_eqn_rws, Psi2vs] = Derive_B_Kin(obj)
            %UNTITLED Construct an instance of this class
            %   Detailed explanation goes here 
            
            %Substitute the ball's displacement vector in the S2 (plate) frame for the
            %arbitrary dispaclement vector r2 of the u-joint kinematics velocity equation
            obj.vb2s = subs(obj.UJ_Kin.v2s, obj.VDefs.symFunVec_r2, obj.VDefs.symFunVec_rb2);
            
            %Substitute the ball's displacement vector in the S2 (plate) frame for the
            %arbitrary dispaclement vector r2 of the u-joint kinematics acceleration equation
            obj.ab2s = subs(obj.UJ_Kin.a2s, obj.VDefs.symFunVec_r2, obj.VDefs.symFunVec_rb2);
            
            %Rollling without slip constraint equation
            constr_eqn_rws = diff(obj.VDefs.rb2s,obj.VDefs.t,1) == cross(obj.VDefs.Psi2vs, obj.VDefs.armb2s); %Contraint Equation Rolling Without Slip (RWS)
            
            
            %Retrieve a Psi2vs symbolic variable from VDefs object
            obj.Psi2vs = obj.VDefs.Psi2vs;
            
            %Isolate Psi2vs components in the constraint equations to get an expression
            %for the balls angular velocity in terms of its linear velocities (all
            %expressed in the S2 basis)
            obj.Psi2vs(1) = rhs(isolate(constr_eqn_rws(2), obj.VDefs.Psi2vs(1)));
            obj.Psi2vs(2) = rhs(isolate(constr_eqn_rws(1), obj.VDefs.Psi2vs(2)));
            
            %Return outputs
            vb2s = obj.vb2s;
            ab2s = obj.ab2s;
            Psi2vs = obj.Psi2vs;
            
        end 
        
        function [vp2s, ap2s] = Derive_P_Kin(obj)  
            %UNTITLED Construct an instance of this class
            %   Detailed explanation goes here
            
            %Substitute the plate's displacement vector in the S2 (plate) frame for the
            %arbitrary dispaclement vector r2 of the u-joint kinematics velocity equation
            obj.vp2s = subs(obj.UJ_Kin.v2s, obj.VDefs.symFunVec_r2, obj.VDefs.symFunVec_rp2);
            
            %Substitute the plate's displacement vector in the S2 (plate) frame for the
            %arbitrary dispaclement vector r2 of the u-joint kinematics acceleration equation
            obj.ap2s = subs(obj.UJ_Kin.a2s, obj.VDefs.symFunVec_r2, obj.VDefs.symFunVec_rp2);
            
            
            %Return outputs
            vp2s = obj.vp2s;
            ap2s = obj.ap2s;
        end
        
        function [vb2s, ab2s, constr_eqn_rws, Psi2vs, vp2s, ap2s] = Derive_Both(obj)
            %UNTITLED Construct an instance of this class
            %   Detailed explanation goes here 
            
            [vb2s, ab2s, constr_eqn_rws, Psi2vs] = obj.Derive_B_Kin;
            [vp2s, ap2s] = obj.Derive_P_Kin;
           
        end
        
    end
end

