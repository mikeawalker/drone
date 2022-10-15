function [y C] = PredictMeasurement(Xstar , w ) 
%#eml
r_gps = [0; 1; 0];
q1 = Xstar(7);
q2 = Xstar(8);
q3 = Xstar(9);
q4 = Xstar(10);
wb = Xstar(14:16);
   DCM_l2b = [ 1-2*q2*q2-2*q3*q3 , 2*(q1*q2 + q3*q4) , 2*(q3*q1 - q2*q4) ;... 
               2*(q1*q2 - q3*q4) , 1 - 2*q1*q1 - 2*q3*q3 , 2*(q3*q2 + q1*q4) ;...  
               2*(q1*q3 + q2*q4) , 2*(q3*q2 - q1*q4) , 1 - 2*q2*q2 - 2*q1*q1];

DCM_b2l = DCM_l2b';

r = Xstar(1:3) +  DCM_b2l*r_gps;
v = Xstar(4:6) + DCM_b2l*cross((w - wb),r_gps);
y = [r ; v ];
%
drm_dr = eye(3);
dvm_dv = eye(3);

C = zeros(6,15);
C(1:3 , 1:3) = drm_dr;
C(4:6 , 4:6) = dvm_dv;