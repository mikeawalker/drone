clearvars -except *Kf *Est debug*
mode =1
close all 

figure
title('Pos'); hold on
subplot(3,1,1)
ComparePlot( PosEst(1:end-1,1),xKf , mode)
ylabel('x')
subplot(3,1,2)
ComparePlot(yKf,PosEst(1:end-1,2), mode );
ylabel('y')
subplot(3,1,3)
ComparePlot( zKf,PosEst(1:end-1,3) ,mode)

ylabel('z')
figure
title('Vel')
subplot(3,1,1)
ComparePlot(vxKf, VelEst(1:end-1,1),mode)
ylabel('vx')
subplot(3,1,2)
ComparePlot(vyKf, VelEst(1:end-1,2),mode)
ylabel('vy')
subplot(3,1,3)
ComparePlot(vzKf, VelEst(1:end-1,3),mode)
ylabel('vz')


figure
title('Q')
subplot(4,1,1)
ComparePlot(q0Kf, QuatEst(1:end-1,1),mode)
ylabel('q1')
subplot(4,1,2)
ComparePlot(q1Kf, QuatEst(1:end-1,2),mode)
ylabel('q2')
subplot(4,1,3)
ComparePlot(q2Kf, QuatEst(1:end-1,3),mode)
ylabel('q3')
subplot(4,1,4)
ComparePlot(q3Kf, QuatEst(1:end-1,4),mode)
ylabel('q4')

figure
title('A Bias')
subplot(3,1,1)
ComparePlot(ab1Kf,AccelBiasEst(1:end-1,1),mode)
subplot(3,1,2)
ComparePlot(ab2Kf,AccelBiasEst(1:end-1,2),mode)
subplot(3,1,3)
ComparePlot(ab3Kf,AccelBiasEst(1:end-1,3),mode)

figure
title('W Bias')
subplot(3,1,1)
ComparePlot(wb1Kf,wBiasEst(1:end-1,1),mode)
subplot(3,1,2)
ComparePlot(wb2Kf,wBiasEst(1:end-1,2),mode)
subplot(3,1,3)
ComparePlot(wb3Kf,wBiasEst(1:end-1,3),mode)


for k=1:15
   figure
   hold on
   ComparePlot( PKf(:,k) , squeeze(P_Est(k,k,1:end-1)) , mode )
    
end


figure
ComparePlot( debugX(1:end-1,1) , xpKf ,mode)

figure
ComparePlot( debugX(1:end-1,2) , ypKf ,mode)

figure
ComparePlot( debugX(1:end-1,3) , zpKf ,mode)
