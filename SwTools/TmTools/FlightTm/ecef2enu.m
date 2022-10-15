function [E N U] = ecef2enu( X , Y , Z )


X0 = X(1);
Y0 = Y(1);
Z0 = Z(1);

lat  = atan( Z0 / sqrt(X0*X0 + Y0*Y0) );
long = atan2( Y0 , X0 );

Rot1 = [ cos(long) , sin(long) , 0;  ...
         -sin(long) , cos(long), 0 ; ...
           0,0,1];
       
Rot2 = [ cos(lat) , 0 , sin(lat);...
         0,1,0;...
         -sin(lat), 0 , cos(lat)];
     

for k=1:length(X)
    ECEF = [ X(k) ; Y(k); Z(k)] - [X0;Y0;Z0];
    UEN  = Rot2*Rot1*ECEF;
    U(k) = UEN(1);
    E(k) = UEN(2);
    N(k) = UEN(3);
end

end

