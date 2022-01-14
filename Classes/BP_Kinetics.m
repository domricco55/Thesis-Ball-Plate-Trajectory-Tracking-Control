classdef BP_Kinetics < handle
    %BP_Kinetics This class generates the kinetic equations of motion for the system in
    %terms of the state variables. 
    %   Detailed explanation goes here
    
    properties
        
    end
   
    properties (SetAccess = private)
        %Objects
        VDefs
        UJ_Knmtcs
        BP_Knmtcs
        
        %Derived Symbolic Expressions
        Omega2b
        Hb2s
        Hb2ds
        Hp2s
        Hp1s
        Hp1ds
        NL_EOMs
        SumMBall
        SumMPlate
        
        %Substituted numerical parameters and assumptions (keep track of what 
        %is being substituted and assumed away)
        NL_NumEOMs
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
        
        
        function [Omega2b, Hb2s, Hb2ds, SumMBall, Hp1s, Hp1ds, armp1s, rb1s, ap1s,...
                ab1s, Hb1ds, SumMPlate, CoeffMat, ExtTerms, NL_EOMs] = Derive_NL_EOMs(obj)
            %Derive_NL_EOMs Derive the Equations of Motion for the Ball and Plate system
            %   Detailed explanation goes here 
            
            %Derive the ball's angular momentum vector
            obj.Omega2b = obj.UJ_Knmtcs.Omega2vs + obj.BP_Knmtcs.Psi2vs;
            obj.Hb2s = expand(obj.VDefs.Ib2ms*(obj.Omega2b));
           
            %Find the time derivative of Hb2s
            obj.Hb2ds = expand(simplify(obj.VDefs.R02*diff(obj.VDefs.R20*obj.Hb2s)));
            obj.Hb2ds = subs(obj.Hb2ds, obj.VDefs.symFunVec, obj.VDefs.symVarVec); %NO LONGER NEED TO DIFFERENTIATE 
                                                                           %so I can subsitute the symfuns for symvars
                                                                           
            %Take the sum of moments about the ball's contact point, for the ball alone.
            %This is done in the S2 basis. 
            obj.SumMBall = expand(cross(obj.VDefs.armb2s, obj.VDefs.R02*obj.VDefs.Wb0s) == ...
                cross(obj.VDefs.armb2s, obj.VDefs.m_b*obj.BP_Knmtcs.ab2s) + obj.Hb2ds);
            obj.SumMBall = subs(obj.SumMBall, obj.VDefs.symFunVec, obj.VDefs.symVarVec);
            
            %Derive the Plate's angular momentum vector. First, find it in the S2 basis,
            %then rotate it into the S1 basis - moments will be taken in the u-joint axle
            %frame
            obj.Hp2s = obj.VDefs.Ip2ms*(obj.UJ_Knmtcs.Omega2vs); %In S2, the plates Inertia
            %tensor is easily defined and its angular velocity is known from prior analysis
            obj.Hp1s = obj.VDefs.R21*obj.Hp2s; %Apply rotation matrix to S2 angular momentum vector
           
            %Find the time derivative of Hp2s
            obj.Hp1ds = simplify(obj.VDefs.R01*diff(obj.VDefs.R10*obj.Hp1s));
            obj.Hp1ds = subs(obj.Hp1ds, obj.VDefs.symFunVec, obj.VDefs.symVarVec);
           
            
            %Rotate plate's moment arm into the S1 basis
            armp1s = subs(obj.VDefs.R21*obj.VDefs.armp2s, obj.VDefs.symFunVec, obj.VDefs.symVarVec);
           
            %Rotate the ball's displacement vector into the S1 basis
            rb1s = subs(obj.VDefs.R21*obj.VDefs.rb2s, obj.VDefs.symFunVec, obj.VDefs.symVarVec);
            
            %Rotate pertinent vectors into S1 basis
            ap1s = expand(subs(obj.VDefs.R21*obj.BP_Knmtcs.ap2s, obj.VDefs.symFunVec, obj.VDefs.symVarVec));
            ab1s = subs(obj.VDefs.R21*obj.BP_Knmtcs.ab2s, obj.VDefs.symFunVec, obj.VDefs.symVarVec);
            Hb1ds = expand(obj.VDefs.R21*obj.Hb2ds);
            
            %Sum moments about the center of the u-joint for the ball and plate combined
            %system. This is done in the S1 basis
            obj.SumMPlate = cross(armp1s, obj.VDefs.R01*obj.VDefs.Wp0s) + ...
                cross(rb1s,obj.VDefs.R01*obj.VDefs.Wb0s) + obj.VDefs.Tb1 +...
                obj.VDefs.Tg1 + obj.VDefs.Mz1 == cross(armp1s, obj.VDefs.m_p*ap1s)...
                + obj.Hp1ds + cross(rb1s, obj.VDefs.m_b*ab1s) + Hb1ds;
            obj.SumMPlate = expand(subs(obj.SumMPlate, obj.VDefs.symFunVec, obj.VDefs.symVarVec));
            
            %Generate equations of motion by isolating the highest order terms in the x
            %and y moment equations
            Moment_Eqns = [obj.SumMBall(1:2);obj.SumMPlate(1:2)];
            HOTs = [obj.VDefs.x_ddot; obj.VDefs.beta_ddot; obj.VDefs.y_ddot; obj.VDefs.gamma_ddot];
            [CoeffMat,ExtTerms] = equationsToMatrix(Moment_Eqns, HOTs);
            
            HighOrderEOMs = CoeffMat\ExtTerms;
            
            obj.NL_EOMs = obj.VDefs.stateVec_dot == subs(obj.VDefs.stateVec_dot, HOTs, HighOrderEOMs);

            %Return outputs
            Omega2b = obj.Omega2b;
            Hb2s = obj.Hb2s;
            Hb2ds = obj.Hb2ds;
            Hp1s = obj.Hp1s;
            Hp1ds = obj.Hp1ds;
            SumMPlate = obj.SumMPlate;
            SumMBall = obj.SumMBall;
            NL_EOMs = obj.NL_EOMs;
        end 
        
        function [Num_Params, Sym_Params, Assumption_Params, Assumptions,...
                NL_NumEOMs] = Num_Params_n_Assumptions(obj)
            %Num_Params_n_Assumptions Input estimated numerical parameters of the system
            % and simplify the system with a few assumptions
            %   Detailed explanation goes here
            

            %Numerical Parameters in terms of symbolic variables utilized in 
            %the model 
            Num_Params = [obj.VDefs.rB  (obj.VDefs.rC+obj.VDefs.rB) ...
            obj.VDefs.mB obj.VDefs.mP obj.VDefs.IP obj.VDefs.IB ...
            obj.VDefs.g_num obj.VDefs.rG];
        
            Sym_Params = [obj.VDefs.r_b obj.VDefs.z_b obj.VDefs.m_b...
                obj.VDefs.m_p obj.VDefs.I_p_xx obj.VDefs.I_b obj.VDefs.g...
                obj.VDefs.z_p];
            
            %Simplifying assumptions
            Assumption_Params = [obj.VDefs.psi_dot_z obj.VDefs.psi_z obj.VDefs.I_p_zz];
            Assumptions = [0 0 0];
            
            %Substitute in all numerical parameters and assumptions
            obj.NL_NumEOMs = subs(obj.NL_EOMs, [Sym_Params Assumption_Params],[Num_Params  Assumptions]);
            
            %Return outputs
            NL_NumEOMs = obj.NL_NumEOMs;

        end
    end
end

