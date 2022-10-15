
close all
xCov = squeeze(P_out(1,1,:));
yCov =squeeze( P_out(2,2,:));
zCov = squeeze(P_out(3,3,:));
vxCov =squeeze( P_out(4,4,:));
vyCov =squeeze( P_out(5,5,:));
vzCov =squeeze( P_out(6,6,:));

rCov = squeeze(P_out(7,7,:));
pCov = squeeze(P_out(8,8,:));
ywCov =squeeze( P_out(9,9,:));

axCov =squeeze( P_out(10,10,:));
ayCov =squeeze( P_out(11,11,:));
azCov = squeeze(P_out(12,12,:));
wxCov = squeeze(P_out(13,13,:));
wyCov = squeeze(P_out(14,14,:));
wzCov =squeeze( P_out(15,15,:));

figure
subplot(2,1,1)
hold on
plot(xCov,'b.')
plot(yCov,'g.')
plot(zCov,'r.')
subplot(2,1,2)
hold on
plot(vxCov,'b.')
plot(vyCov,'g.')
plot(vzCov,'r.')

figure
hold on
plot(rCov,'b')
plot(pCov,'g')
plot(ywCov,'r.')
ylabel('RPY Cov')
figure
subplot(2,1,1)
hold on
plot(axCov,'b.')
plot(ayCov,'g.')
plot(azCov,'r.')

subplot(2,1,2)
hold on
plot(wxCov,'b.')
plot(wyCov,'g.')
plot(wzCov,'r.')
