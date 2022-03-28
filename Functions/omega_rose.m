function [omega] = omega_rose(T,n,d)
%omega_rose This function computes the omega value (angular frequency) of a rose cure given a desired total
%period for the shape and the n and d values that select the rose curve

k = n/d; 

if floor(k) == k
%If k is an integer
    if ~rem(k,2)
    %If k is an even integer
        omega = 2*pi/T;
    else
    %If k is an odd integer
        omega = pi/T;
    end

else 
%k is rational
val = n*d;
    if ~rem(val,2)
    %If val is an even integer
        omega = pi*d*2/T;
    else
    %If val is an odd integer
        omega = pi*d/T;
    end
end