function quat = dcmToQuat( DCM ) 
%#eml

q4_2   = .25*(  1 + DCM(1,1) + DCM(2,2) + DCM(3,3) ) ;
q1_2   = .25*(  1 + DCM(1,1) - DCM(2,2) -DCM(3,3) ) ;
q2_2   = .25*(  1 - DCM(1,1) + DCM(2,2) - DCM(3,3) ) ;
q3_2   = .25*(  1 - DCM(1,1) - DCM(2,2) + DCM(3,3) ) ;
[Q_pick ind]  = max( [ q1_2, q2_2 , q3_2 , q4_2]);

Q_pick = sqrt(Q_pick);
switch ind
    case 1
        q1 = Q_pick;
        q4 = .25*( DCM(2,1) - DCM(1,2) ) / q1;
        q2 = .25*( DCM(1,2) + DCM(2,1) ) / q1;
        q3 = .25*( DCM(1,3) + DCM(3,1) ) / q1;
        
    case 2
        q2 = Q_pick;
        q4 = .25*( DCM(1,3) - DCM(3,1) ) / q2;
        q1 = .25*( DCM(1,2) + DCM(2,1) ) / q2;
        q3 = .25*( DCM(2,3) + DCM(3,2) ) / q2;

    case 3
        q3 = Q_pick;
        q4 = .25*( DCM(2,1) - DCM(1,2) ) / q3;
        q1 = .25*( DCM(1,3) + DCM(3,1) ) / q3;
        q2 = .25*( DCM(2,3) + DCM(3,2) ) / q3;
       
    case 4
        q4 = Q_pick;
        q1 = .25*( DCM(3,2) - DCM(2,3) ) / q4;
        q2 = .25*( DCM(1,3) - DCM(3,1) ) / q4;
        q3 = .25*( DCM(2,1) - DCM(1,2) ) / q4;
    otherwise
        q1 = 0; q2 = 0; q3 = 0; q4 = 1;
end

if( q4 < 0 )
   q4 = -q4; 
   q1 = .25*( DCM(3,2) - DCM(2,3) ) / q4;
   q2 = .25*( DCM(1,3) - DCM(3,1) ) / q4;
   q3 = .25*( DCM(2,1) - DCM(1,2) ) / q4; 
end

Tchk = [ q1.^2 - q2.^2 - q3.^2 + q4.^2 , 2*(q1*q2 - q3*q4) , 2*(q1*q3 + q2*q4);         2*(q1*q2 - q3*q4) , -q1.^2 + q2.^2 - q3.^2 + q4.^2 , 2*(q2*q3 - q1*q4);         2*(q1*q3 - q2*q4) , 2*(q2*q3  + q1*q4) , -q1.^2 - q2.^2 + q3.^2 + q4.^2];
q = [q1;q2;q3;q4];
quat = q./sqrt(dot(q,q));

