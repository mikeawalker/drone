r0 = [0 0 0];
v0 = [0 0 0 ];
w0 = [0 0 0 ];
q0 = [0 0 0 1];


Re = 6378e3;
lat = 32.2217;%deg
long = -110.9264;%deg
%% Drone
I = diag([ 2 , 2 , 1]);
BladePitch = 10; %deg
m =  1; %mass
Cd = 10;
A = 1;

% Blade Locs
armLen =1;

r1 = armLen*[ cosd(45) sind(45) 0 ]; 
r2 = armLen*[ cosd(45) -sind(45) 0 ];
r3 = armLen*[ -cosd(45) -sind(45) 0 ];
r4 = armLen*[ -cosd(45) sind(45) 0 ];
%% Physics

rho = 1.2754; %km/m^3
g = 9.80665;

ecef2enu =  [0 1 0 ; 0 0 1; 1 0 0]* ... proper enu
            [ cosd(lat) 0 sind(lat) ; 0 1 0 ; -sind(lat) 0 cosd(lat)]*... prime to uen
            [ cosd(long) sind(long) 0; -sind(long) cosd(long) 0; 0 0 1]; %ecef to prime
enu2ecef = ecef2enu';
