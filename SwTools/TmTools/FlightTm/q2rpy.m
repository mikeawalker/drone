function [r p y] = q2rpy(q1,q2,q3,q4)



p = (180/pi).*atan( 2.*(q4.*q1+ q2.*q3) ./ (1 -2.*q1.*q1 - 2.*q2.*q2) );
r = (180/pi) .* asin(2 .* (q4.*q2 - q3.*q1)) ;
y  = (180/pi).* atan2(2 .* (q4.*q3 + q1.*q2), (1 - 2 .* q2.*q2 - 2 .* q3.*q3));