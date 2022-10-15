function x_prop = PropXf_Eom( X , U  , dt  )
%#eml
% State
% r = x 1-3
% v = x 4-6
% a = x 7-9

% w = x 10-12
% q = x 13

y0 = X;

%options = odeset('AbsTol',1e-8*ones(size(y0)),'RelTol',1e-8);
%[t X2]  = ode45('DroneEom',[0 dt],y0, options);

iter = 100;
xup = X;
for k=1:iter
  t2 = (dt/iter);
  dx = DroneEom( t2 , xup );
  xup = xup + dx*t2;
end
X2 = xup;
q_up = X2(13:16);
qnorm = q_up./sqrt(dot(q_up,q_up));

X2(13:16) = qnorm;

X2 = X2(1:16);
x_prop = X2;
