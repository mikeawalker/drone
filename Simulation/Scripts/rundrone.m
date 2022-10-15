clearvars
clc
close all
addpath('../Simulink');
addpath('../Simulink/EKF');
addpath('../Tools/EKF/');
addpath('../Tools/')
%% command
abstol = 1e-6


InitialConditions
ControllerSetup
EkfSetup
loadTraj
%% Do the sim
tsim = 50;
sim('drone')


%% Do some plots

%PlotEkf
%PlotState



%% Write Outs
saveAp
saveGuide
saveKalman
%% Write 
sim.time = t_cpu(1:klen);
sim.Acmd = acmd(1:klen,:);
sim.fTot = fTot(1:klen,:);
sim.inTrackAccel = inTrackCmd(1:klen,:);
sim.xTrackAccel = xTrackCmd(1:klen,:);
sim.inTrackVel = inTrackVcmd(1:klen,:);
sim.xTrackVel = xTrackVcmd(1:klen,:);
sim.hAccel = hAccel(1:klen);
sim.stateEst = xout(1:klen,:)
sim.quatCmd = qCmd(1:klen,:);
sim.omegaCmd = wCmd(1:klen,:);
sim.momCmd = mCmd(1:klen,:);
sim.bladeCom = bladeCmd(1:klen,:);
sim.aCmd = aCmd(1:klen,:);
sim.vCmd  = vCmd(1:klen,:);
sim.fTot = fTot(1:klen,:);
sim.dQs = dq(1:klen,:);
sim.qerr = qErr(1:klen,:);
sim.wMom = wMom(1:klen,:);
sim.F0 = fTot;
clearvars -except sim
save SimData