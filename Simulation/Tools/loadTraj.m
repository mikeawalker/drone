
dt = .01;
hoverTime = 0;
hoverAlt = 0;
tH = [0:dt:hoverTime-dt];
xH = zeros(size(tH));
yH = zeros(size(tH));
zH = hoverAlt.*ones(size(tH));
vH = zeros(size(tH));
%% Traj
circAlt = 5;
 tT = [0:dt:200];
xT = 0.0+0.0*tT;
 yT =0.0+ 0.0*tT; 
 zT = circAlt*ones(size(tT));
% 
vT = [0.0+0.0*tT ;0.0+0*tT];

% tT=  [0:dt:100+dt]
% xT = [xT -xT];
% yT = [yT yT];
% zT = [zT zT];
% vT = [vT -vT];
%  circRad = 10;
%  f = 2*pi/180;
%  xT = circRad*sin( f*tT );
%  yT = circRad*cos( f*tT )-circRad;
%  vX = f*circRad*cos(f*tT);
%  vY = -f*circRad*sin(f*tT);
%  vT = [vX;vY];
%% 



tc = [ tH , tT+hoverTime];
xc = [ xH , xT];
yc = [yH , yT];
zc = [zH , zT];

vc = [ vH , vT(1,:) ; vH , vT(2,:)];