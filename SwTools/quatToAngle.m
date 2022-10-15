function ypr = quatToAngle( quat ) 

q1=quat(1,:);
q2=quat(2,:);
q3 = quat(3,:);
q4 = quat(4,:);

C11 = 1 - 2*q2.*q2 - 2*q3.*q3;
C12 = 2*( q1.*q2 - q3.*q4 );
C13 = 2*(q3.*q1 + q2.*q4);
C21 = 2*(q1.*q2 + q3.*q4);
C22 = 1 - 2*q1.*q1 - 2.*q3.*q3;
C23 = 2*( q3.*q2 - q1.*q4);
C31 = 2*( q1.*q3 - q2.*q4);
C32 = 2*(q3.*q2 + q1.*q4);
C33 = 1 - 2*q1.*q1 - 2*q2.*q2;


roll =  asind( C32 );
pitch  = atan( -C12 ./ C22 )*180/pi;
yaw = atan2( -C31 , C33)*180/pi;

ypr = [roll; pitch; yaw];