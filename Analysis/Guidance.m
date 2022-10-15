
close all
clc
clearvars


rho = 1.23; 
Cd =10;
A=1;
m=1;


Kp = 2;
Kd =1;
Ki = .5;


%% Math

Do = rho*Cd*A/m;



Plant = tf(1,[1 Do 0])

Control = tf([Kd Kp Ki],[1 0])

OL = minreal( Control * Plant )
CL = minreal( OL / (1 + OL ) )

figure
nichols(OL)

figure
VM = nyquistAnalysis(OL)

figure
step(CL)

