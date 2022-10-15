function [X Y Z] = enu2ecef( E, N , U , X0 ,Y0, Z0)


lat  = atan( Z0 / sqrt(X0*X0 + Y0*Y0) );
long = atan2( Y0 , X0 );

Rot1 = [ cos(long) , sin(long) , 0;  ...
         -sin(long) , cos(long), 0 ; ...
           0,0,1];
       
Rot2 = [ cos(lat) , 0 , sin(lat);...
         0,1,0;...
         -sin(lat), 0 , cos(lat)];
     
DCM = (Rot2*Rot1)';
for k=1:length(E)
    UEN = [ U(k) , E(k) , N(k) ]';
    ECEF = DCM*UEN;
    X(k) = ECEF(1) + X0;
    Y(k) = ECEF(2) + Y0;
    Z(k) = ECEF(3) + Z0;
end
