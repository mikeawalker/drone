wb = [2e-3 1e-3 -3e-3];

d = 45;
DCM_l2b = [ cosd(d) sind(d) 0 ; -sind(d) cosd(d) 0 ; 0 0 1];
DCM11=[     0.8975    0.2994    0.3237;...
   -0.2474    0.9496   -0.1925;...
   -0.3650    0.0927    0.9264];

colat = 90-32.2;
M = [0; -sind(colat); -2*cosd(colat)];
Mhat = M./sqrt(dot(M,M));
Mbody = DCM_l2b * Mhat;
m1 = Mhat(1);
m2 = Mhat(2);
m3 = Mhat(3);

Mhat2 = [Mhat(2);-Mhat(1);Mhat(3)];

y = DCM_l2b*Mhat; % M is in enu
y2 = DCM_l2b*Mhat2;
%
MagMeasure = [ y; y2];

Rmag = diag([ 0.00000001  0.00000001  0.00000001 0.00000001  0.00000001  0.00000001 ]);

wBiasCov = [1 1 1 ];
angCov = [.5 .5 .5];
P_init = diag([ angCov , wBiasCov]);

dx_init = zeros(1,6);

qInit = [0 0 0 1];
wBiasInit = [0 0 0 ];
x_init = [ qInit  wBiasInit];
Q = diag([ 0.1 0.1 0.1]);