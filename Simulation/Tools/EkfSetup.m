%% Sensor Stats

%% IMU
IMU_DT = 0.01;
mean_a_bias = [.1 -.2 .33];
a_noise_var = 0.0001;
a_noise_seed = [1 2 3];

mean_w_bias =[0.03 -0.02 0.01];
w_noise_var = 0*0.00001;
w_noise_seed  = [4 5 6];
Q = diag([0.0001 0.0001 0.0001 .1 .1 .1]);

AccelQuant = 4.4e-3
GyroQuant = 1e-3;
%% GPS
r_gps = [0 0 0];
GPS_DT =.25;
h_noise_var =0*0.0001;
h_noise_seed = [7 8 9];

v_noise_var = .00;
v_noise_seed = [10 11 12];


R = diag([.1 .1 .1]);
%% MAG
MAG_DT = 0.1;
mag_bias = 0;
mag_noise_var = 00.000000001
mag_noise_seed = [12 13 14 ];
Rmag = diag([ 0.01  0.01  0.01 2 2 2]);
Mag2Dcm = [0 1 0; -1 0  0; 0 0 1];

%% KF Inits
rInit = [ 0 0 0];
rCov = [2 2 2 ];
vInit = [0 0 0 ];
vCov = 0*[.1 .1 .1];
th =0;
th_r = th+0;
qInit = [0 0  sind(th_r/2) cosd(th_r/2)];
R11 = [ cosd(th) sind(th) 0 ; -sind(th) cosd(th) 0 ; 0 0 1];
R22 = [0 1 0 ; -1 0 0; 0 0 1] * R11;
angCov = [.10 .10 .10];
%% SECTION TITLE
% DESCRIPTIVE TEXT
aBiasInit = mean_a_bias;[0,0,0];
aBiasCov = [1 1 1];
wBiasInit = [0 0 0];
wBiasInit =mean_w_bias
wBiasCov = [1 1 1 ];
%% SECTION TITLE
% DESCRIPTIVE TEXT
x_init = [rInit vInit qInit aBiasInit wBiasInit];
dx_init = zeros(1,15);
P_init = diag([rCov, vCov , angCov, aBiasCov , wBiasCov]);