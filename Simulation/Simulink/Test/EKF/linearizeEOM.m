function [A   G ]= linearizeEOM(  Xstar  , win )
%#eml
% Breakout States
wb = Xstar(5:7);
%

w1 = win(1) - wb(1);
w2 = win(2) - wb(2);
w3 = win(3) - wb(3);

Wx  = -[0 w3 -w2 ; ...
       -w3 0 w1; ...
       w2  -w1 0];

z3 = zeros(3,3)
A = [ -Wx  , -eye(3) ;...
       z3 , z3];
   
   
G = zeros(6 , 3 );
G(1:3 ,1:3) = -eye(3);
G(4:6, 1:3) = eye(3);


