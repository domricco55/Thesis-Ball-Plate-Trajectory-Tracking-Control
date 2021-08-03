classdef Var_Defs
    %This class defines symbolic variables, generally, for use with the symbolic
    %toolbox throughout the Ball and Plate thesis project. 
    %   Defines symvars and symfuns for scalars, vectors, and matrices. The
    %   definitions are kept as general as possible and contain a minimal amount
    %   of derived results. 
    
    
    
    properties 
    %Scalars
        %Miscellaneous
        t %time symbolic variable
        g %gravitational constant symbolic variable
        
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
        w       %width of plate
        z_Pc    %Vertical distance from u-joint to push rod pivot (Pc is "point c")
        z_p     %height of the plate's center of mass with respect to the frame's 
                %origin at the center of the u-joint    
        L_carm  %length of motor mechanism crank arm
        L_crod  %length of motor mechanism connecting rod
        
        %Variables Related to Mass and Geometry of the Ball
        I_b     %mass moment of inertia of the ball (spherically symmetric)
        I_p_xx  %x direction mass moment of inertia of plate (principle axis)
        I_pyy   %y direction mass moment of inertia of plate (principle axis)
        I_pzz   %z direction mass moment of inertia of plate (principle axis)
        m_b     %mass of the ball
        m_p     %mass of the plate
        r_b     %radius of the ball
        
        %Coordinate of the Ball's Center of Mass in the S2 (plate) Frame  
        x_hat   %x location of ball in plate frame (symfun)        
        y_hat   %y location of ball in plate frame (symfun)        
        z_b     %constant distance from the center of the u-joint to 
                %the C.O.M of the ball (symvar)                
        ix      %time integral of x location of the ball in the plate frame 
                %(symvar)                
        x       %like x_hat but a symvar        
        y       %like y_hat but a symvar 
        x_dot   %time rate of change of x (symvar)
        y_dot   %time rate of change of y (symvar)
        x_ddot  %time rate of change of x_dot (symvar)
        y_ddot  %time rate of change of y_dot (symvar)
        
        %Components of Arbitrary displacment vector in S2 Frame
        r_hat_1 %arbitrary displacement vector component 1 (symfun) 
        r_hat_2 %arbitrary displacement vector component 2 (symfun)
        r_hat_3 %arbitrary displacement vector component 3 (symfun)
        r_1     %arbitrary displacement vector component 1 (symvar)
        r_2     %arbitrary displacement vector component 2 (symvar)
        r_3     %arbitrary displacement vector component 3 (symvar) 
        r_dot_1 %time rate of change of r_1 (symvar)
        r_dot_2 %time rate of change of r_2 (symvar)
        r_dot_3 %time rate of change of r_3 (symvar)    
        r_ddot_1%time rate of change of r_dot_1 (symvar)       
        r_ddot_2%time rate of change of r_dot_2 (symvar)   
        r_ddot_3%time rate of change of r_dot_3 (symvar) 
        
        %U-Joint Axle Torques and Reactions
        T_beta  %Torque about beta axis of u-joint (symvar)
        T_gamma %Torque about gamma axis of u-joint (symvar)
        M_z     %Reaction moment supplied by u-joint in its z-direction (symvar)
        
        %Error States and Setpoints (x and y Variables)
        e_x     %error in x (symvar)   
        e_x_dot %error in x_dot (symvar)   
        e_x_ddot%error in x_ddot (symvar) 
        e_ix    %error in the integral of x (symvar) 
        ix_s    %integral of the x setpoint - time integral of desired
                %x trajectory (symvar)
        x_s     %x setpoint - desired x trajectory (symvar)
        x_dot_s %x_dot setpoint - velocity of desired x trajectory (symvar)
        x_ddot_s%x_ddot setpoint - acceleration of desired x trajectory (symvar) 
        
    %Vectors
        %Symbolic Angular Velocity Vectors
        Omega2vs%Angular velocity of the plate relative to the inertial frame 
                %with components expressed in the S2 basis
        Psi2vs  %Angular velocity of the ball relative to the plate frame 
                %with components expressed in S2 Basis      
                
        %Arbitrary Displacment Vector in Plate Frame S2        
        r2s          
        
        %Displacement Vectors Centers of Mass
        rb2s    %Displacement vector of the ball's center of mass expressed 
                %in S2 basis.   
        rp2s    %Displacement vector of the plate's center of mass expressed 
                %in S2 basis
        
        %Moment Arms
        armb2s  %Moment arm from the contact point of the ball to its 
                %center of mass expressed in S2 basis.
        armp2s  %Moment arm from the center of the u-joint to the plate's 
                %Center of Mass. 
                    
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
 
            syms z_b ix x y z x_dot y_dot x_ddot y_ddot;

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
%             obj.theta_hat_4 
%             obj.theta_hat_5 
%             obj.theta_hat_6 
%             obj.theta_hat_7
%             obj.theta_hat_8
            obj.beta = beta;
            obj.gamma = gamma;
%             obj.theta_3 
%             obj.theta_4 
%             obj.theta_5 
%             obj.theta_6 
%             obj.theta_7 
%             obj.theta_8 
%             obj.beta_dot 
%             obj.gamma_dot 
%             obj.beta_ddot 
%             obj.gamma_ddot
% 
%             %Angular Velocities for Omega Vectors/Matrices
%             obj.omega_hat_x  
%             obj.omega_hat_y  
%             obj.omega_hat_z 
%             obj.psi_hat_x 
%             obj.psi_hat_y 
%             obj.psi_hat_z 
%             obj.omega_x 
%             obj.omega_y 
%             obj.omega_z 
%             obj.psi_x 
%             obj.psi_y 
%             obj.psi_z
%             obj.omega_dot_x 
%             obj.omega_dot_y 
%             obj.omega_dot_z 
%             obj.psi_dot_x 
%             obj.psi_dot_y 
%             obj.psi_dot_z
% 
%             %Length Related System Parameters
%             obj.w       
%             obj.z_Pc    
%             obj.z_p             
%             obj.L_carm  
%             obj.L_crod  
% 
%             %Variables Related to Mass and Geometry of the Ball
%             obj.I_b     
%             obj.I_p_xx  
%             obj.I_pyy   
%             obj.I_pzz   
%             obj.m_b     
%             obj.m_p    
%             obj.r_b     
% 
%             %Coordinate of the Ball's Center of Mass in the S2 (plate) Frame  
%             obj.x_hat          
%             obj.y_hat       
%             obj.z_b     
%                                
%             obj.ix                 
%             obj.x         
%             obj.y       
%             obj.x_dot   
%             obj.y_dot   
%             obj.x_ddot  
%             obj.y_ddot  
% 
%             %Components of Arbitrary displacment vector in S2 Frame
%             obj.r_hat_1 
%             obj.r_hat_2 
%             obj.r_hat_3 
%             obj.r_1     
%             obj.r_2     
%             obj.r_3     
%             obj.r_dot_1 
%             obj.r_dot_2 
%             obj.r_dot_3  
%             obj.r_ddot_1     
%             obj.r_ddot_2
%             obj.r_ddot_3
% 
%             %U-Joint Axle Torques and Reactions
%             obj.T_beta  
%             obj.T_gamma 
%             obj.M_z     
% 
%             %Error States and Setpoints (x and y Variables)
%             obj.e_x       
%             obj.e_x_dot  
%             obj.e_x_ddot
%             obj.e_ix   
%             obj.x_s     
%             obj.x_dot_s 
%             obj.x_ddot_s
% 
%         %Vectors
%             %Symbolic Angular Velocity Vectors
%             obj.Omega2vs
%             obj.Psi2vs  
% 
%             %Arbitrary Displacment Vector in Plate Frame S2        
%             obj.r2s          
% 
%             %Displacement Vectors Centers of Mass
%             obj.rb2s    
%             obj.rp2s    
% 
%             %Moment Arms
%             obj.armb2s  
%             obj.armp2s  
% 
%             %Force and Moment Vectors
%             obj.Wb0s
%             obj.Wp0s
%             obj.Tb1
%             obj.Tg1
%             obj.Mz1
% 
%             %Displacement Vectors of the Constraining Kinematic Loops
%             obj.d_oc_1
%             obj.d_oc_2
%             obj.L_oa
%             obj.L_ab
%             obj.L_bc
%             obj.L_oc
%             obj.d_of_1
%             obj.d_of_2
%             obj.L_od
%             obj.L_de
%             obj.L_ef
%             obj.L_of
% 
%         %Matrices
%             %Omega Matrices
%             obj.Omega2ms
% 
%             %Inertia Tensors
%             obj.Ib2ms
%             obj.Ip2ms
% 
%             %Rotation Matrices
%             obj.R01
%             obj.R10
%             obj.R01d
%             obj.R10d
%             obj.R12
%             obj.R21
%             obj.R12d
%             obj.R21d
%             obj.R02
%             obj.R20
%             obj.R03
%             obj.R30
%             obj.R34
%             obj.R43
%             obj.R45
%             obj.R54
%             obj.R06
%             obj.R60
%             obj.R67
%             obj.R76
%             obj.R78
%             obj.R87
%             obj.R05
%             obj.R50
%             obj.R08
%             obj.R80
% 
%         %State Space Model Related
%             %Full 8th order system
%             obj.stateVec 
%             obj.stateVec_dot
%             obj.inputVec
% 
%             %Two decoupled 4th order systems
%             obj.stateVec1
%             obj.stateVec1_dot 
%             obj.stateVec2
%             obj.stateVec2_dot
% 
%         %Vectors for Subs Function 
%             %Exchange Variable for its Twin Symvar or Symfun
%             obj.symVarVec
%             obj.symFunVec
% 
%             %Arbitrary Displacement Vector to Ball and Plate Displacements - 
%             %Symfun to Symvar
%             obj.symFunVec_r2
%             obj.symFunVec_rb2
%             obj.symFunVec_rp2
%             
%             
%             
%             
%             
%             
%             
%             
%             
%             
%             
%             
%             
%             
%             obj.Omega2vs = [obj.omega_hat_x(t); obj.omega_hat_y(t); omega_hat_z(t)]
%  
%             Psi2vs = [psi_hat_x(t); psi_hat_y(t); psi_hat_z(t)]
%  
%             r2s = [r_hat_1(t); r_hat_2(t); r_hat_3(t)]
% 
%             rb2s = [x_hat(t);y_hat(t);z_b]
%             
%             rp2s = [0; 0; z_p]
%             
%            
%             armb2s = [0; 0; r_b] 
%             
%             armp2s = [0;0;z_p]
%              
%             Wb0s = [0; 0; -m_b*g] 
%             
%             Wp0s = [0;0;-m_p*g]
%            
%             Tb1 = [0;T_beta;0]
%             
%             Tg1 = [T_gamma;0;0]
%             
%             Mz1 = [0;0;M_z]
%             
%             d_oc_1 = sym('d__oc_', [3 1],'real'); 
%             
%             d_oc_2 = d_oc_1;
%             
%             L_oa = sym('L__oa_', [3 1],'real'); 
%             
%             L_oa(2) = -L_oa(2);
%             
%             L_oa(3) = -L_oa(3);
%             
%             L_ab = [0; L_carm; 0];
%             
%             L_bc = [0; 0; L_crod];
% 
%             L_oc = [w;0;z_Pc]; 
%             
%             d_of_1 = sym('d__of_', [3 1],'real');
%             
%             d_of_2 = d_of_1;
%             
%             L_od = sym('L__od_', [3 1],'real');
%             
%             L_de = [-L_carm; 0; 0];
%             
%             L_ef = [0; 0; L_crod];
% 
%             L_of = [0;w;z_Pc]; 
%             
%             Omega2ms = sym('NA', [3 3]);
%             Omega2ms(:,:) = [       0          -omega_hat_z       omega_hat_y;
% 
%                                 omega_hat_z           0            -omega_hat_x; 
% 
%                                -omega_hat_y     omega_hat_x            0       ];
%             
%             Ib2ms = [I_b 0 0; 0 I_b 0; 0 0 I_b];
%             
%             Ib2ms = subs(Ib2ms, I_b, 2/5*m_b*r_b^2); 
%             
%             Ip2ms = [I_p__xx 0 0; 0 I_p__xx 0; 0 0 I_p__zz];
% 
%             R01 = sym('WHOCARES', [3 3]);
%             R01(:,:) = [cos(beta_hat)   0   -sin(beta_hat);
%                         0          1          0   ;    
%                         sin(beta_hat)   0   cos(beta_hat) ;]
% 
%                     
%             R10 = R01.'; 
%             
%             R01d = diff(R01,t);
%             
%             R10d = diff(R10,t);
%             
%             R12 = sym('WHOCARES', [3 3]);
%             R12(:,:) = [    1                 0                        0       ;
%                             0          cos(gamma_hat(t))          sin(gamma_hat(t));    
%                             0          -sin(gamma_hat(t))         cos(gamma_hat(t));];
%             
%                         
%             R21 = R12.';
%             
%             R12d = diff(R12,t);
%             
%             R21d = diff(R21,t);
%             
%             R02 = R12*R01;
%             
%             R20 = R02.';
%             
%             R03 = sym('WHOCARES', [3 3]);
%             R03(:,:) = [    1                 0                        0       ;
%                             0          cos(theta_hat_3(t))          sin(theta_hat_3(t));    
%                             0          -sin(theta_hat_3(t))         cos(theta_hat_3(t));];
% 
%             R30 = simplify(inv(R03));
% 
%             R34 = sym('WHOCARES', [3 3]);
%             R34(:,:) = [    1                 0                        0       ;
%                             0          cos(theta_hat_4(t))          sin(theta_hat_4(t));    
%                             0          -sin(theta_hat_4(t))         cos(theta_hat_4(t));];
% 
% 
%             R43 = R34.';
% 
%             R45 = sym('WHOCARES', [3 3]);
%             R45(:,:) = [cos(theta_hat_5(t))   0   -sin(theta_hat_5(t));
%                                0          1          0   ;    
%                         sin(theta_hat_5(t))   0   cos(theta_hat_5(t)) ;];
% 
%             R54 = R45.';
% 
%             R06 = sym('WHOCARES', [3 3]);
%             R06(:,:) = [cos(theta_hat_6(t))   0   -sin(theta_hat_6(t));
%                                0          1          0   ;    
%                         sin(theta_hat_6(t))   0   cos(theta_hat_6(t)) ;];
% 
% 
%             R60 = simplify(inv(R06));
% 
%             R67 = sym('WHOCARES', [3 3]);
%             R67(:,:) = [cos(theta_hat_7(t))   0   -sin(theta_hat_7(t));
%                                0          1          0   ;    
%                         sin(theta_hat_7(t))   0   cos(theta_hat_7(t)) ;]; 
% 
%             R76 = simplify(inv(R67));
% 
%             R78 = sym('WHOCARES', [3 3]);
%             R78(:,:) = [    1                 0                        0       ;
%                             0          cos(theta_hat_8(t))          sin(theta_hat_8(t));    
%                             0          -sin(theta_hat_8(t))         cos(theta_hat_8(t));];
% 
%             R87 = R78.';
% 
%             R05 = simplify(R45*R34*R03);
%             
%             R50 = R05.';
%             
%             R08 = simplify(R78*R67*R06);
%             
%             R80 = R08.';
% 
%             stateVec = [x, y, beta, gamma, x_dot, y_dot, beta_dot, gamma_dot].'
%             
%             stateVec_dot = [x_dot, y_dot, beta_dot, gamma_dot, x_ddot,...
%                             y_ddot, beta_ddot, gamma_ddot].'
%             
%             inputVec = [T_beta T_gamma ].'
% 
%             stateVec1 = [x, x_dot, beta, beta_dot].' 
%             
%             stateVec1_dot = [x_dot, x_ddot, beta_dot, beta_ddot].'
% 
%             
%             % stateVec1a = [e_ix, x, x_dot, beta, beta_dot].' %State vector augmented with integral of the error in x
%             % stateVec1a_dot = [e_x, x_dot, x_ddot, beta_dot, beta_ddot].'
%             % stateVec1ae = [e_ix, e_x, e_x_dot, beta, beta_dot].' %State vector augmented with integral of the error in x AND x and x_dot replaced with error states
%             % stateVec1ae_dot = [e_x, e_x_dot, e_x_ddot, beta_dot, beta_ddot].'
%             % setpointVec1 = [x_s x_dot_s x_ddot_s].'
%             
%             stateVec2 = [y, y_dot, gamma, gamma_dot].'
%             stateVec2_dot = [y_dot, y_ddot, gamma_dot, gamma_ddot].'
% 
% 
%             symVarVec = [x      y      r_1      r_2      r_3       beta      gamma      omega_x     omega_y     omega_z     psi_x     psi_y     psi_z theta_3 theta_4 theta_5 theta_6 theta_7 theta_8...
%                          x_dot  y_dot  r_dot_1  r_dot_2  r_dot_3   beta_dot  gamma_dot  omega_dot_x omega_dot_y omega_dot_z psi_dot_x psi_dot_y psi_dot_z...
%                          x_ddot y_ddot r_ddot_1 r_ddot_2 r_ddot_3  beta_ddot gamma_ddot];
% 
%             symFunVec = [x_hat(t) y_hat(t) r_hat_1(t) r_hat_2(t)  r_hat_3(t) beta_hat(t) gamma_hat(t) omega_hat_x(t) omega_hat_y(t) omega_hat_z(t) psi_hat_x(t) psi_hat_y(t) psi_hat_z(t) theta_hat_3(t) theta_hat_4(t) theta_hat_5(t) theta_hat_6(t) theta_hat_7(t) theta_hat_8(t)...
%                    diff([x_hat(t) y_hat(t) r_hat_1(t) r_hat_2(t)  r_hat_3(t) beta_hat(t) gamma_hat(t) omega_hat_x(t) omega_hat_y(t) omega_hat_z(t) psi_hat_x(t) psi_hat_y(t) psi_hat_z(t)] ,t,1)...
%                    diff([x_hat(t) y_hat(t) r_hat_1(t) r_hat_2(t)  r_hat_3(t) beta_hat(t) gamma_hat(t) ], t,2)];
% 
% 
%             symFunVec_r2 = [r2s.' diff(r2s,t,1).' diff(r2s,t,2).'];
% 
%             symFunVec_rb2 = [rb2s.', diff(rb2s,t,1).', diff(rb2s,t,2).'];
% 
%             symFunVec_rp2 = [rp2s.', diff(rp2s.',t,1), diff(rp2s.',t,2)];
% 



        end
        
    end
end

%Testing GIT with this comment

