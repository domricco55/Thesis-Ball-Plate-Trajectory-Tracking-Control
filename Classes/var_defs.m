classdef Var_Defs
    %This class defines symbolic variables, generally, for use with the symbolic
    %toolbox throughout the Ball and Plate thesis project. 
    %   Defines symvars and symfuns for scalars, vectors, and matrices. The
    %   definitions are kept as general as possible and do not contain any
    %   non-fundamental derived results. 
    
    properties 
    %Scalars
        %Miscellaneous
        t %time symbolic variable
        g %gravitational constant symbolic variable
        
        %Angle Variables
        
        %Angular Velocities for Omega Vectors/Matrices
        
        %Length Related System Parameters
        
        %Variables Related to Mass and Geometry of the Ball
        I_b %mass moment of inertia of the ball (spherically symmetric)
        
        I_p_xx %x direction mass moment of inertia of plate (principle axis)
        
        I_pyy %y direction mass moment of inertia of plate (principle axis)
        
        I_pzz %z direction mass moment of inertia of plate (principle axis)
        
        m_b %mass of the ball
        
        m_p %mass of the plate
        
        r_b %radius of the ball
        
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
        
        %Arbitrary displacment vector in S2
        r_hat_1 %arbitrary displacement vector component 1 (symfun)
        
        r_hat_2 %arbitrary displacement vector component 2 (symfun)
        
        r_hat_3 %arbitrary displacement vector component 3 (symfun)
        
        r_1     %arbitrary displacement vector component 1 (symvar)
        
        r_2     %arbitrary displacement vector component 2 (symvar)
        
        r_3     %arbitrary displacement vector component 3 (symvar) 
        
        r_dot_1 
        
        r_dot_2 
        
        r_dot_3 
        
        r_ddot_1 
        
        r_ddot_2 
        
        r_ddot_3;
        
    %Vectors
    
    %Matrices
    
    %State Space Model - Related
    
    %
    end
    
    properties (SetAccess = private)
        
    end 
    
    methods
        function obj = Var_Defs()
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

