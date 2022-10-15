function [A   G DCM_Xs YPR]= linearizeEOM( dx , Xstar , ain , win )
%#eml

%DCM true
q1 = Xstar(7);
q2 = Xstar(8);
q3 = Xstar(9);
q4 = Xstar(10);
DCM_Xs = [ 1-2*q2*q2-2*q3*q3 , 2*(q1*q2 + q3*q4) , 2*(q3*q1 - q2*q4) ;... 
               2*(q1*q2 - q3*q4) , 1 - 2*q1*q1 - 2*q3*q3 , 2*(q3*q2 + q1*q4) ;...  
               2*(q1*q3 + q2*q4) , 2*(q3*q2 - q1*q4) , 1 - 2*q2*q2 - 2*q1*q1];

DCM_c2b = DCM_Xs;
DCM_b2c = DCM_c2b';           



%% Setup the matrixes

A = zeros(15,15);
G = zeros(15 , 6 );

%% Translational Motion

a_b = Xstar(11:13);
a_e = DCM_b2c*(ain);
Sx  = a_e(1);
Sy = a_e(2);
Sz = a_e(3);

Ab_skew = [ 0 -Sz Sy ; Sz 0 -Sx ; -Sy Sx 0 ];

% Error DCM



% NOTE: We are going to do different error states than actual states
% Real States: [r v a_bias w_bias q_i2b]
% Error States: [r v rpy a_bias w_bias ]


% d_rdot/d_dv  
d_rdot_dv = eye(3);


A = zeros(15,15);
A(1:3 , 4:6) = d_rdot_dv;
A(4:6 , 7:9) = Ab_skew;%sign error?

A(4:6 , 10:12) = -DCM_b2c;

G(4:6 , 1:3) = DCM_b2c;



%% Orientation Stuff


% Breakout States
wb = Xstar(14:16);
%

w1 = win(1) - wb(1);
w2 = win(2) - wb(2);
w3 = win(3) - wb(3);

Wx  = -[0 w3 -w2 ; ...
       -w3 0 w1; ...
       w2  -w1 0];

   
A( 7:9 , 7:9 ) = Wx;
A( 7:9 , 13:15) = -DCM_c2b';

G(7:9 ,4:6) = eye(3);

G(13:15 ,4:6) = 0*eye(3);





