clearvars -except qout *Kf
close all
mode = 0
figure
ComparePlot(qout(1:end-1,1) , q0Kf ,mode )
figure
ComparePlot(qout(1:end-1,2) , q1Kf ,mode )
figure
ComparePlot(qout(1:end-1,3) , q2Kf ,mode )
figure
ComparePlot(qout(1:end-1,4) , q3Kf ,mode )