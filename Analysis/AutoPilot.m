close all
%% Pitch
I = 2;
Kr = -1000;
Kq = -30;
Ksyn = -300;
set(0,'defaultlinelinewidth',3)
%% Pitch / Roll Auto pilot

OL = tf( [ -Kr ] , [I -Kq -Ksyn 0] );
CL = minreal( OL / (1 + OL ) );

nyquistAnalysis(OL)

nicholsAnalysis(OL)

figure
set(gcf,'Position', [100, 100, 1000, 550]);
step( CL )
%% Yaw
I = .5;
Kr = 20;
Kq = -7;
Ksyn =-8;

%% Yaw autopilot

OL2 = tf([Kr],[I -Kq -Ksyn 0])
CL2 = minreal( OL2 / (1 + OL2 ) );

nyquistAnalysis(OL2)

nicholsAnalysis(OL2)


figure
set(gcf,'Position', [100, 100, 1000, 550]);
step( CL2 )