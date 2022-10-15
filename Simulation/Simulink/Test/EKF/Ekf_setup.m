clearvars
clc
close all
addpath('../')
EkfSetup

r0 = [0 0 1];
v0 = [0 0 0];
w0 = [0 0 0];
q0 = [0 0 0 1];


sim('EKF_Test')

t_cpu = [0.01:0.01:length(PosEst)*0.01];
PlotEkf