function ydot = DroneEom(t,y)
%#eml
V = y(4:6);
a = y(7:9);
w = y(10:12);
q = y(13:16);
q = q./sqrt(dot(q,q));


%%
Vdot = a;
Rdot = V ;
adot = [0;0;0];  
wdot =[0;0;0];%wd;%/???

q1 = q(1);
q2 = q(2);
q3 = q(3);
q4 =q(4);

Q =  .5*[ q4 , -q3 , q2 ;...
          q3 , q4  , -q1 ; ...
          -q2 , q1 , q4 ; ...
           -q1 , -q2, - q3];

qdot = Q*w;


ydot = [Rdot;Vdot; adot ; wdot;qdot ];








