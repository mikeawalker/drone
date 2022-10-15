function plotImu( imuFile )



imu=load(imuFile);
time=imu(:,1);
ax = imu(:,2);
ay = imu(:,3);
az = imu(:,4);
wx = imu(:,5);
wy = imu(:,6);
wz = imu(:,7);

figure
subplot(3,1,1)
hold on
plot(time,ax)
plot(time,ay,'r')
plot(time,az,'g')
xlabel('Time (s)')
ylabel('Accel')
subplot(3,1,2)
hold on
plot(time,wx)
plot(time,wy,'r')
plot(time,wz,'g')
xlabel('Time (s)')
ylabel('\omega')
subplot(3,1,3)
plot(time(2:end) , diff(time))
xlabel('Time (s)')
ylabel('\Delta Time (s)')