function [y C DCM_l2b] = predictMag(Xstar  ) 
%#eml

q1 = Xstar(1);
q2 = Xstar(2);
q3 = Xstar(3);
q4 = Xstar(4);
   DCM_l2b = [ 1-2*q2*q2-2*q3*q3 , 2*(q1*q2 + q3*q4) , 2*(q3*q1 - q2*q4) ;... 
               2*(q1*q2 - q3*q4) , 1 - 2*q1*q1 - 2*q3*q3 , 2*(q3*q2 + q1*q4) ;...  
               2*(q1*q3 + q2*q4) , 2*(q3*q2 - q1*q4) , 1 - 2*q2*q2 - 2*q1*q1];




colat = 90-32.2;
M = [0; -sind(colat); -2*cosd(colat)];
Mhat = M./sqrt(dot(M,M));
Mhat2 = [0 1 0; -1 0 0; 0 0 1]*Mhat;
Mbody = DCM_l2b * Mhat;
Mbody2 = DCM_l2b*Mhat2;
m1 = Mbody(1);
m2 = Mbody(2);
m3 = Mbody(3);
skew_mag =[0 m3 -m2 ; -m3 0 m1 ; m2 -m1 0]'  ;

m1 = Mbody2(1);
m2 = Mbody2(2);
m3 = Mbody2(3);
skew_mag2 = [0 m3 -m2 ; -m3 0 m1 ; m2 -m1 0]';
dm_de = DCM_l2b*skew_mag; 
dm2_de = DCM_l2b*skew_mag2;

y = [DCM_l2b*Mhat ;DCM_l2b*Mhat2]; % M is in enu
%


%C = zeros(3,6);
%C(1:3 , 1:3) = dm_de;


C = zeros(6,6);
C(1:3 , 1:3) = dm_de;
C(4:6 , 1:3) = dm2_de;