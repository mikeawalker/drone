clearvars
clc
close all

% Physical
G=0
Ft=10.81;
Iax = 1;

T= Ft;

Ka = 1000;
Kw = -30;
Ks = -300;

F = tf(Ka,[Iax -Kw -Ks]);
G = tf(1/T , [1 0 1 0]);
%G = tf(1/T , [1 0] );

CL = F*G/(1 + F*G);
OL = F*G;
CL = minreal(CL)
OL = minreal(OL)
figure
nyquist(OL)


figure
nichols(OL)

figure
rlocus(OL)



tf2 = tf(1,[1  1 1])

figure
nyquist(tf1,tf2)