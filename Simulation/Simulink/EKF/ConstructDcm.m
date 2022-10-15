function D = ConstructDcm( quat ) 

q1 = quat(1);
q2 = quat(2);
q3 = quat(3);
q4 = quat(4);




D = zeros(3,3);



D(1,1)= 1-(2*q2*q2) - (2*q3*q3);
D(1,2) = 2*( q1*q2 - q3*q4);
D(1,3) = 2*( q3*q1 + q2*q4);
D(2,1) = 2*( q1*q2 + q3*q4);
D(2,2) = 1-(2*q1*q1) - (2*q3*q3);
D(2,3) = 2*( q3*q2 - q1*q4);
D(3,1) = 2*( q1*q3 - q2*q4);
D(3,2) = 2*( q3*q2 + q1*q4);
D(3,3) = 1-(2*q2*q2) - (2*q1*q1);
