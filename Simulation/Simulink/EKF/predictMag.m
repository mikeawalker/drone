function [y C] = predictMag(Xstar , a  ) 
%#eml

q1 = Xstar(7);
q2 = Xstar(8);
q3 = Xstar(9);
q4 = Xstar(10);
Ba = Xstar(11:13);
   DCM_l2b = [ 1-2*q2*q2-2*q3*q3 , 2*(q1*q2 + q3*q4) , 2*(q3*q1 - q2*q4) ;... 
               2*(q1*q2 - q3*q4) , 1 - 2*q1*q1 - 2*q3*q3 , 2*(q3*q2 + q1*q4) ;...  
               2*(q1*q3 + q2*q4) , 2*(q3*q2 - q1*q4) , 1 - 2*q2*q2 - 2*q1*q1];


M = [0; 24.6; -40.4];
Mhat = M ./sqrt(dot(M,M));

Mbody =  Mhat;

%Mbody2 = DCM_l2b*Mhat2;
m1 = Mbody(1);
m2 = Mbody(2);
m3 = Mbody(3);
skew_mag =[0 m3 -m2 ; -m3 0 m1 ; m2 -m1 0]'  ;

%skew_mag2 = DCM2 * skew_mag;
dm_de = skew_mag; 
%dm2_de = skew_mag2;
% Gps accel compare

gEnu =  -[0 ;0 ;9.80665] ;% -Ba ;
accelS =gEnu ./sqrt(dot(gEnu,gEnu));
A1 = accelS(1);
A2 = accelS(2);
A3 = accelS(3);
skew_accel = [ 0 A3 -A2; -A3 0 A1 ; A2 -A1 0]';

y = [DCM_l2b*Mbody ;DCM_l2b* accelS]; % M is in enu
%

C = zeros(6,15);
C(1:3 , 7:9) =DCM_l2b*dm_de;
C(4:6 , 7:9) = DCM_l2b*skew_accel;
%C(4:6 , 10:12) = -eye(3);


