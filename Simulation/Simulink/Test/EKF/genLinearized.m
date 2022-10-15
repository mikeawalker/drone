function [DCM dLdq1 dLdq2 dLdq3 dLdq4] = genLinearized(q1,q2,q3,q4) 
%#eml


DCM = zeros(3,3);
dLdq1 = zeros(3,3);
dLdq2 = zeros(3,3);
dLdq3 = zeros(3,3);
dLdq4 = zeros(3,3);


DCM =     [ q1*q1 - q2*q2 - q3*q3 + q4*q4 , 2*(q1*q2+q3*q4) , 2*(q1*q3-q2*q4) ;...
            2*(q1*q2 - q3*q4 ) , -q1*q1 + q2*q2 - q3*q3 + q4*q4 , 2*(q2*q3+q1*q4);...
            2*(q1*q3 + q2*q4) , 2*(q2*q3 - q1*q4) , -q1*q1 - q2*q2 + q3*q3 + q4*q4];

dLdq1 = 2*[q1 q2 q3 ; q2 -q1 q4; q3 -q4 -q1];
dLdq2 = 2*[-q2 q1 -q4; q1 q2 q3 ; q4 q3 -q2];
dLdq3 = 2*[-q3 q4 q1 ; -q4 -q3 q2 ; q1 q2 q3];
dLdq4 = 2*[q4 q3 -q2; -q3 q4 q1; q2 q1 q4];