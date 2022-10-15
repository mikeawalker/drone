%% Dead Zone
accel_dead = 0*0.2;
torque_dead = 0.0*0.05;

%% Controllers
a_scale = 01;
% Hover
KPhover = 5;
KDhover = 2;
KIhover = 2;



%KPec =-1;
%KIec = -.2;
%KDec =2;
%Kii =0
Kpr =0.5
Kir =0.1
Kdr =0
Kpv =1
Kiv =0
Kdv = 0
Kpt = 1 ;
Kit = .1;
Kdt = 0.001;

GuideDt = 0.1;
%% Ap Gains
KaY = 1.2;
KthP = 0.04;
KP = 1;

%
%
KaQ =1000
KthQ =-300
KQ = -30

KaR =-1000
KthR =-300;
KR = -30

%% Drone Blade Layout
J = 0.01;
I1 = 1/2;
I2 = 1/2
I3 = 1/1;
blade_rate_max = 1;
MinPwmWidth = 1;
MaxPwmWidth = 4;
MaxPropRate =blade_rate_max;

RateToForce = 20;
I_motor = RateToForce * sind( BladePitch );
wtom = [ I1 I1  -I1 -I1;... % M1
         -I2 I2 I2 -I2;... % M2
        I3 I3 I3 I3 ;... % M3
         .25 -.25 .25 -.25]; % F

mtow = inv(wtom);
RunUpLimit = 10.4
RunUpStartThrottle = .1;