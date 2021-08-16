classdef Var_Defs
    %This class defines symbolic variables, generally, for use with the symbolic
    %toolbox throughout the Ball and Plate thesis project. 
    %   Defines symvars and symfuns for scalars, vectors, and matrices. The
    %   definitions are kept as general as possible and contain a minimal amount
    %   of derived results. Detailed derivations and variable descriptions can be found in
    %   the "Var_Defs_Developement.mlx" file. 

    properties (SetAccess = private)
    %Scalars
        %Miscellaneous
        t 
        g 
        
        %Angle Variables
        beta_hat
        gamma_hat 
        theta_hat_3 
        theta_hat_4 
        theta_hat_5 
        theta_hat_6 
        theta_hat_7
        theta_hat_8
        beta 
        gamma 
        theta_3 
        theta_4 
        theta_5 
        theta_6 
        theta_7 
        theta_8 
        beta_dot 
        gamma_dot 
        beta_ddot 
        gamma_ddot
        
        %Angular Velocities for Omega Vectors/Matrices
        omega_hat_x  
        omega_hat_y  
        omega_hat_z 
        psi_hat_x 
        psi_hat_y 
        psi_hat_z 
        omega_x 
        omega_y 
        omega_z 
        psi_x 
        psi_y 
        psi_z
        omega_dot_x 
        omega_dot_y 
        omega_dot_z 
        psi_dot_x 
        psi_dot_y 
        psi_dot_z
        
        %Length Related System Parameters
        w       
        z_Pc    
        z_p       
        L_carm  
        L_crod 
        
        %Variables Related to Mass and Geometry of the Ball
        I_b  
        I_p__xx 
        I_p__yy   
        I_p__zz  
        m_b    
        m_p     
        r_b    
        
        %Coordinate of the Ball's Center of Mass in the S2 (plate) Frame  
        x_hat          
        y_hat           
        z_b                     
        ix               
        x          
        y     
        x_dot  
        y_dot   
        x_ddot 
        y_ddot 
        
        %Components of Arbitrary displacment vector in S2 Frame
        r_hat_1 
        r_hat_2 
        r_hat_3 
        r_1     
        r_2  
        r_3     
        r_dot_1 
        r_dot_2 
        r_dot_3  
        r_ddot_1   
        r_ddot_2 
        r_ddot_3
        
        %U-Joint Axle Torques and Reactions
        T_beta 
        T_gamma 
        M_z     
        
        %Error States and Setpoints (x and y Variables)
        e_x      
        e_x_dot 
        e_x_ddot
        e_ix    
        ix_s    
        x_s     
        x_dot_s 
        x_ddot_s
        
    %Vectors
        %Symbolic Angular Velocity Vectors
        Omega2vs
        Psi2vs    
                
        %Arbitrary Displacment Vector in Plate Frame S2        
        r2s          
        
        %Displacement Vectors Centers of Mass
        rb2s    
        rp2s   
        
        %Moment Arms
        armb2s  
        armp2s
                    
        %Force and Moment Vectors
        Wb0s
        Wp0s
        Tb1
        Tg1
        Mz1
        
        %Displacement Vectors of the Constraining Kinematic Loops
        d_oc_1
        d_oc_2
        L_oa
        L_ab
        L_bc
        L_oc
        
        d_of_1
        d_of_2
        L_od
        L_de
        L_ef
        L_of
        
    %Matrices
        %Omega Matrices
        Omega2ms
        
        %Inertia Tensors
        Ib2ms
        Ip2ms
        
        %Rotation Matrices
        R01
        R10
        R01d
        R10d
        R12
        R21
        R12d
        R21d
        R02
        R20
        R03
        R30
        R34
        R43
        R45
        R54
        R06
        R60
        R67
        R76
        R78
        R87
        R05
        R50
        R08
        R80
        
    %State Space Model Related
        %Full 8th order system
        stateVec 
        stateVec_dot
        inputVec
        
        %Two decoupled 4th order systems
        stateVec1
        stateVec1_dot 
        stateVec2
        stateVec2_dot
        
    %Vectors for Subs Function 
        %Exchange Variable for its Twin Symvar or Symfun
        symVarVec
        symFunVec
        
        %Arbitrary Displacement Vector to Ball and Plate Displacements - 
        %Symfun to Symvar
        symFunVec_r2
        symFunVec_rb2
        symFunVec_rp2
        
    end
    
%     properties (SetAccess = private)
%         
%     end 
    
    methods
        function obj = Var_Defs()
            %UNTITLED Construct an instance of this class
            %   Detailed explanation goes here
            
            %Generate the necessary symbolic variables and functions
            syms t g real

            syms beta_hat(t) gamma_hat(t) theta_hat_3(t) theta_hat_4(t)... 
            theta_hat_5(t) theta_hat_6(t) theta_hat_7(t) theta_hat_8(t)
            
            beta = sym('beta'); 
            gamma = sym('gamma');
            %Idk why I had to do this in the class definition
            %but not in the script I have been using for ages. 
            %I couldnt use beta or gamma with 'syms'
            %because beta and gamma are already defined
            %matlab functions. Maybe the conflict only
            %exists in .m files. 
            
            syms  theta_3 theta_4 theta_5 theta_6 theta_7... 
            theta_8 beta_dot gamma_dot beta_ddot gamma_ddot

            syms omega_hat_x(t) omega_hat_y(t) omega_hat_z(t) ...
                psi_hat_x(t) psi_hat_y(t) psi_hat_z(t)

            syms omega_x omega_y omega_z psi_x psi_y psi_z
            
            syms omega_dot_x omega_dot_y omega_dot_z psi_dot_x psi_dot_y psi_dot_z

            syms w z_Pc z_p L_carm L_crod real

            syms I_b I_p__xx  I_p__yy I_p__zz m_b m_p r_b real 
            assume(I_b>0 & I_p__xx>0 &   I_p__yy>0 &  I_p__zz>0 &  m_b>0 &  m_p>0 &  r_b>0)

            syms x_hat(t) y_hat(t) 
 
            syms z_b ix x y x_dot y_dot x_ddot y_ddot;

            syms r_hat_1(t) r_hat_2(t) r_hat_3(t)

            syms r_1 r_2 r_3 r_dot_1 r_dot_2 r_dot_3 r_ddot_1 r_ddot_2 r_ddot_3

            syms T_beta T_gamma M_z

            syms e_x e_x_dot e_x_ddot e_ix ix_s x_s x_dot_s x_ddot_s 

            
            
            
            %Assign the generated symvars to the properties of the class
          
        %Scalars
            %Miscellaneous
            obj.t = t; 
            obj.g = g; 

            %Angle Variables
            obj.beta_hat = beta_hat;
            obj.gamma_hat = gamma_hat; 
            obj.theta_hat_3 = theta_hat_3;
            obj.theta_hat_4 = theta_hat_4;
            obj.theta_hat_5 = theta_hat_5;
            obj.theta_hat_6 = theta_hat_6;
            obj.theta_hat_7 = theta_hat_7;
            obj.theta_hat_8 = theta_hat_8;
            obj.beta = beta;
            obj.gamma = gamma;
            obj.theta_3 = theta_3; 
            obj.theta_4 = theta_4;
            obj.theta_5 = theta_5; 
            obj.theta_6 = theta_6;
            obj.theta_7 = theta_7; 
            obj.theta_8 = theta_8; 
            obj.beta_dot = beta_dot; 
            obj.gamma_dot = gamma_dot; 
            obj.beta_ddot = beta_ddot; 
            obj.gamma_ddot = gamma_ddot;

            %Angular Velocities for Omega Vectors/Matrices
            obj.omega_hat_x = omega_hat_x; 
            obj.omega_hat_y = omega_hat_y;
            obj.omega_hat_z = omega_hat_z; 
            obj.psi_hat_x = psi_hat_x; 
            obj.psi_hat_y = psi_hat_y; 
            obj.psi_hat_z = psi_hat_z;
            obj.omega_x = omega_x; 
            obj.omega_y = omega_y; 
            obj.omega_z = omega_z; 
            obj.psi_x = psi_x; 
            obj.psi_y = psi_y; 
            obj.psi_z = psi_z;
            obj.omega_dot_x = omega_dot_x; 
            obj.omega_dot_y = omega_dot_y; 
            obj.omega_dot_z = omega_dot_z; 
            obj.psi_dot_x = psi_dot_x; 
            obj.psi_dot_y = psi_dot_y; 
            obj.psi_dot_z = psi_dot_z;

            %Length Related System Parameters
            obj.w = w;      
            obj.z_Pc = z_Pc;    
            obj.z_p = z_p;            
            obj.L_carm = L_carm; 
            obj.L_crod = L_crod; 

            %Variables Related to Mass and Geometry of the Ball
            obj.I_b = I_b;    
            obj.I_p__xx = I_p__xx; 
            obj.I_p__yy = I_p__yy;   
            obj.I_p__zz = I_p__zz;   
            obj.m_b = m_b;    
            obj.m_p = m_p;   
            obj.r_b = r_b;    

            %Coordinate of the Ball's Center of Mass in the S2 (plate) Frame  
            obj.x_hat = x_hat;          
            obj.y_hat = y_hat;      
            obj.z_b  = z_b;     
                               
            obj.ix = ix;                
            obj.x  = x;        
            obj.y = y;      
            obj.x_dot = x_dot;   
            obj.y_dot = y_dot;   
            obj.x_ddot = x_ddot; 
            obj.y_ddot = y_ddot;  

            %Components of Arbitrary displacment vector in S2 Frame
            obj.r_hat_1 = r_hat_1; 
            obj.r_hat_2 = r_hat_2;
            obj.r_hat_3 = r_hat_3; 
            obj.r_1 = r_1;      
            obj.r_2 = r_2;    
            obj.r_3 = r_3;     
            obj.r_dot_1 = r_dot_1;
            obj.r_dot_2 = r_dot_2;
            obj.r_dot_3 = r_dot_3;  
            obj.r_ddot_1 = r_ddot_1;     
            obj.r_ddot_2 = r_ddot_2;
            obj.r_ddot_3 = r_ddot_3;

            %U-Joint Axle Torques and Reactions
            obj.T_beta = T_beta;  
            obj.T_gamma = T_gamma; 
            obj.M_z = M_z;       

            %Error States and Setpoints (x and y Variables)
            obj.e_x = e_x;       
            obj.e_x_dot = e_x_dot; 
            obj.e_x_ddot = e_x_ddot;
            obj.e_ix = e_ix;   
            obj.x_s = x_s;      
            obj.x_dot_s = x_dot_s;
            obj.x_ddot_s = x_ddot_s;

        %Vectors
            %Symbolic Angular Velocity Vectors

            obj.Omega2vs = [obj.omega_hat_x(t); obj.omega_hat_y(t); obj.omega_hat_z(t)];
            obj.Psi2vs = [obj.psi_hat_x(t); obj.psi_hat_y(t); obj.psi_hat_z(t)];
            
            %Arbitrary Displacment Vector in Plate Frame S2        
            obj.r2s = [obj.r_hat_1(t); obj.r_hat_2(t); obj.r_hat_3(t)];       

            %Displacement Vectors Centers of Mass
            obj.rb2s = [obj.x_hat(t);obj.y_hat(t);obj.z_b]; 
            obj.rp2s = [0; 0; obj.z_p];

            %Moment Arms
            obj.armb2s = [0; 0; obj.r_b];  
            obj.armp2s = [0;0;obj.z_p];

            %Force and Moment Vectors
            obj.Wb0s = [0; 0; -obj.m_b*obj.g];           
            obj.Wp0s = [0;0;-obj.m_p*obj.g];           
            obj.Tb1 = [0;obj.T_beta;0];            
            obj.Tg1 = [obj.T_gamma;0;0];            
            obj.Mz1 = [0;0;obj.M_z];

            %Displacement Vectors of the Constraining Kinematic Loops
            obj.d_oc_1 = sym('d__oc_', [3 1],'real');             
            obj.d_oc_2 = obj.d_oc_1;            
            obj.L_oa = sym('L__oa_', [3 1],'real');             
            obj.L_oa(2) = -obj.L_oa(2);           
            obj.L_oa(3) = -obj.L_oa(3);           
            obj.L_ab = [0; obj.L_carm; 0];           
            obj.L_bc = [0; 0; obj.L_crod];
            obj.L_oc = [obj.w;0;obj.z_Pc]; 
            
            obj.d_of_1 = sym('d__of_', [3 1],'real');           
            obj.d_of_2 = obj.d_of_1;            
            obj.L_od = sym('L__od_', [3 1],'real');            
            obj.L_de = [-obj.L_carm; 0; 0];            
            obj.L_ef = [0; 0; obj.L_crod];
            obj.L_of = [0;obj.w;obj.z_Pc]; 

        %Matrices
            %Omega Matrices
            obj.Omega2ms = sym('NA', [3 3]);
            obj.Omega2ms(:,:) = [       0          -omega_hat_z       omega_hat_y;

                                    omega_hat_z           0            -omega_hat_x; 

                                    -omega_hat_y     omega_hat_x            0       ];


            %Inertia Tensors
            obj.Ib2ms = [obj.I_b 0 0; 0 obj.I_b 0; 0 0 obj.I_b];
            obj.Ib2ms = subs(obj.Ib2ms, obj.I_b, 2/5*obj.m_b*obj.r_b^2); 
            obj.Ip2ms = [obj.I_p__xx 0 0; 0 obj.I_p__xx 0; 0 0 obj.I_p__zz];

            %Rotation Matrices
            obj.R01 = sym('WHOCARES', [3 3]);
            obj.R01(:,:) = [cos(obj.beta_hat)   0   -sin(obj.beta_hat);
                                     0          1          0   ;    
                            sin(obj.beta_hat)   0   cos(obj.beta_hat) ;];

                    
            obj.R10 = obj.R01.'; 
            
            obj.R01d = diff(obj.R01,obj.t);
            
            obj.R10d = diff(obj.R10,obj.t);
            
            obj.R12 = sym('WHOCARES', [3 3]);
            obj.R12(:,:) = [    1             0                      0       ;
                                0   cos(obj.gamma_hat(t))  sin(obj.gamma_hat(t));    
                                0   -sin(obj.gamma_hat(t)) cos(obj.gamma_hat(t));];
            
                        
            obj.R21 = obj.R12.';
            
            obj.R12d = diff(obj.R12,obj.t);
            
            obj.R21d = diff(obj.R21,obj.t);
            
            obj.R02 = obj.R12*obj.R01;
            
            obj.R20 = obj.R02.';
            
            obj.R03 = sym('WHOCARES', [3 3]);
            obj.R03(:,:) = [    1                 0                        0       ;
                            0          cos(obj.theta_hat_3(t))          sin(obj.theta_hat_3(t));    
                            0          -sin(obj.theta_hat_3(t))         cos(obj.theta_hat_3(t));];

            obj.R30 = simplify(inv(obj.R03));

            obj.R34 = sym('WHOCARES', [3 3]);
            obj.R34(:,:) = [    1                 0                        0       ;
                            0          cos(obj.theta_hat_4(t))          sin(obj.theta_hat_4(t));    
                            0          -sin(obj.theta_hat_4(t))         cos(obj.theta_hat_4(t));];


            obj.R43 = obj.R34.';

            obj.R45 = sym('WHOCARES', [3 3]);
            obj.R45(:,:) = [cos(obj.theta_hat_5(t))   0   -sin(obj.theta_hat_5(t));
                                     0                1               0;    
                            sin(obj.theta_hat_5(t))   0   cos(obj.theta_hat_5(t)) ;];

            obj.R54 = obj.R45.';

            obj.R06 = sym('WHOCARES', [3 3]);
            obj.R06(:,:) = [cos(obj.theta_hat_6(t))   0   -sin(obj.theta_hat_6(t));
                               0          1          0   ;    
                        sin(obj.theta_hat_6(t))   0   cos(obj.theta_hat_6(t)) ;];


            obj.R60 = simplify(inv(obj.R06));

            obj.R67 = sym('WHOCARES', [3 3]);
            obj.R67(:,:) = [cos(obj.theta_hat_7(t))   0   -sin(obj.theta_hat_7(t));
                                           0          1          0   ;    
                            sin(obj.theta_hat_7(t))   0   cos(obj.theta_hat_7(t)) ;]; 

            obj.R76 = simplify(inv(obj.R67));

            obj.R78 = sym('WHOCARES', [3 3]);
            obj.R78(:,:) = [    1                    0                                    0       ;
                                0          cos(obj.theta_hat_8(t))          sin(obj.theta_hat_8(t));    
                                0          -sin(obj.theta_hat_8(t))         cos(obj.theta_hat_8(t));];

            obj.R87 = obj.R78.';

            obj.R05 = simplify(obj.R45*obj.R34*obj.R03);
            
            obj.R50 = obj.R05.';
            
            obj.R08 = simplify(obj.R78*obj.R67*obj.R06);
            
            obj.R80 = obj.R08.';


        %State Space Model Related
            %Full 8th order system
            obj.stateVec = [obj.x, obj.y, obj.beta, obj.gamma,obj.x_dot, obj.y_dot, obj.beta_dot, obj.gamma_dot].';
            obj.stateVec_dot = [obj.x_dot, obj.y_dot, obj.beta_dot, obj.gamma_dot, obj.x_ddot,obj.y_ddot,obj.beta_ddot,obj.gamma_ddot].';            
            obj.inputVec = [obj.T_beta obj.T_gamma ].';


            %Two decoupled 4th order systems
            obj.stateVec1 = [obj.x, obj.x_dot, obj.beta, obj.beta_dot].'; 
            obj.stateVec1_dot = [obj.x_dot, obj.x_ddot, obj.beta_dot, obj.beta_ddot].';

            
            % stateVec1a = [e_ix, x, x_dot, beta, beta_dot].' %State vector augmented with integral of the error in x
            % stateVec1a_dot = [e_x, x_dot, x_ddot, beta_dot, beta_ddot].'
            % stateVec1ae = [e_ix, e_x, e_x_dot, beta, beta_dot].' %State vector augmented with integral of the error in x AND x and x_dot replaced with error states
            % stateVec1ae_dot = [e_x, e_x_dot, e_x_ddot, beta_dot, beta_ddot].'
            % setpointVec1 = [x_s x_dot_s x_ddot_s].'
            
            obj.stateVec2 = [obj.y, obj.y_dot, obj.gamma, obj.gamma_dot].';
            obj.stateVec2_dot = [obj.y_dot, obj.y_ddot, obj.gamma_dot, obj.gamma_ddot].';


        %Vectors for Subs Function 
            %Exchange Variable for its Twin Symvar or Symfun
            obj.symVarVec = [obj.x      obj.y      obj.r_1      obj.r_2      obj.r_3       obj.beta      obj.gamma      obj.omega_x     obj.omega_y     obj.omega_z     obj.psi_x     obj.psi_y     obj.psi_z  obj.theta_3 obj.theta_4 obj.theta_5  obj.theta_6  obj.theta_7   obj.theta_8...
                             obj.x_dot  obj.y_dot  obj.r_dot_1  obj.r_dot_2  obj.r_dot_3   obj.beta_dot  obj.gamma_dot  obj.omega_dot_x obj.omega_dot_y obj.omega_dot_z obj.psi_dot_x obj.psi_dot_y obj.psi_dot_z ...
                             obj.x_ddot obj.y_ddot obj.r_ddot_1 obj.r_ddot_2 obj.r_ddot_3  obj.beta_ddot obj.gamma_ddot];
                         
            obj.symFunVec = [obj.x_hat(t) obj.y_hat(t) obj.r_hat_1(t) obj.r_hat_2(t)  obj.r_hat_3(t) obj.beta_hat(t) obj.gamma_hat(t) obj.omega_hat_x(t) obj.omega_hat_y(t) obj.omega_hat_z(t) obj.psi_hat_x(t) obj.psi_hat_y(t) obj.psi_hat_z(t) obj.theta_hat_3(t) obj.theta_hat_4(t) obj.theta_hat_5(t) obj.theta_hat_6(t) obj.theta_hat_7(t) obj.theta_hat_8(t)...
                       diff([obj.x_hat(t) obj.y_hat(t) obj.r_hat_1(t) obj.r_hat_2(t)  obj.r_hat_3(t) obj.beta_hat(t) obj.gamma_hat(t) obj.omega_hat_x(t) obj.omega_hat_y(t) obj.omega_hat_z(t) obj.psi_hat_x(t) obj.psi_hat_y(t) obj.psi_hat_z(t)] ,obj.t,1)...
                       diff([obj.x_hat(t) obj.y_hat(t) obj.r_hat_1(t) obj.r_hat_2(t)  obj.r_hat_3(t) obj.beta_hat(t) obj.gamma_hat(t) ], obj.t,2)];




            %Arbitrary Displacement Vector to Ball and Plate Displacements - 
            %Symfun to Symvar
            obj.symFunVec_r2 = [obj.r2s.' diff(obj.r2s,obj.t,1).' diff(obj.r2s,obj.t,2).'];
            obj.symFunVec_rb2 = [obj.rb2s.', diff(obj.rb2s,obj.t,1).', diff(obj.rb2s,obj.t,2).'];
            obj.symFunVec_rp2 = [obj.rp2s.', diff(obj.rp2s.',obj.t,1), diff(obj.rp2s.',obj.t,2)];


            


        end
        
    end
end


