function q = updateQuat( q0 , dA)


mag1 = sqrt(dot(dA,dA))*0.5;
if( mag1 <= 1 )
   scale =  1/sqrt(1-mag1);
else
    scale =  1/sqrt(1+mag1);
end


dq = scale*[.5*dA;1];

% dq cross q0
p1 = dq(1);
p2 = dq(2);
p3 = dq(3);
p4 = dq(4);


P = [  p4 -p3 p2 p1 ;...
      p3 p4 -p1 p2;...
      -p2 p1 p4 p3;...
      -p1 -p2 -p3 p4];
  
  q = P*q0;