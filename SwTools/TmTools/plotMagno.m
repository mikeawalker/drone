function  plotMagno( magFile )


magDat=load(magFile);

%% MAG
time = magDat(:,1);
mag1 = magDat(:,2:4);
mag1x = mag1(:,1);
mag1y = mag1(:,2);
mag1z = mag1(:,3);


magU1 =sqrt( dot(mag1,mag1,2));

figure
subplot(3,1,1)
hold on
plot(time,mag1x)
plot(time,mag1y,'r')
plot(time,mag1z,'g')
xlabel('Time (s)')
ylabel('Mag1')

subplot(3,1,2)
hold on
plot(time,magU1)
xlabel('Time (s)')
ylabel('|Mag|')
subplot(3,1,3)
plot(time(2:end) , diff(time))
xlabel('Time (s)')
ylabel('\Delta Time (s)')