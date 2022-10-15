 

clearvars
clc
close all

imuDat = load('G:\Workspace\QuadDrone\EKF\FlightSoftware\Build\TmGrabber\Debug\ImuData.dat');
magDat = load('G:\Workspace\QuadDrone\EKF\FlightSoftware\Build\TmGrabber\Debug\MagData.dat');
ekfDat = load('G:\Workspace\QuadDrone\EKF\FlightSoftware\Build\TmGrabber\Debug\StateData.dat');

%% IMU
t = imuDat(:,1);
accel = imuDat(:,2:4);
gyro = imuDat(:,5:7);

%% MAG
tm = magDat(:,1);
mag = magDat(:,2:4);

magU =sqrt( dot(mag,mag,2));
%% EKF

pos = ekfDat(:,2:4);
vel = ekfDat(:,5:7);
quat = ekfDat(:,8:11);
accelz = ekfDat(:,12:14);
om = ekfDat(:,15:17);
tekf = ekfDat(:,1);

%% Plots

figure
subplot(3,1,1)
plot(t,accel)
ylabel('Accelleration (m/s^2)')
xlabel('Time (s)')
subplot(3,1,2)
plot(t,gyro)
ylabel('Angular Velocity (rad/s)')
xlabel('Time (s)')
legend('X','Y','Z')
subplot(3,1,3)
plot( t(2:end) , 1./diff(t) )
ylabel('\Delta T')
xlabel('Time (s)')


figure
subplot(2,1,1)
plot(tm,mag)
ylabel('Magnetic Field')
xlabel('Time (s)')
legend('X','Y','Z')
subplot(2,1,2)
plot(tm , magU )
hold on
%plot(tm,(180/pi)*atan2( mag(:,2) , mag(:,1)),'r')
%plot( tm(2:end) , 1./diff(tm) )
ylabel('\Delta T')
xlabel('Time (s)')


figure
subplot(3,1,1)
plot(tekf,pos)
xlabel('Time (s)')
ylabel('Position')
subplot(3,1,2)
plot(tekf,vel)
xlabel('Time (s)')
ylabel('Velocity')
subplot(3,1,3)
plot(tekf,accelz)
figure
subplot(3,1,1)
plot(tekf,quat)
xlabel('Time (s)')
ylabel('Orientation')
subplot(3,1,2)
plot( tekf,quatToAngle(quat')' )
legend('roll','pitch','yaw')
xlabel('Time (s)')
ylabel('Angles')
subplot(3,1,3)
plot(tekf,om)
xlabel('Time (s)')
ylabel('Ang Vel')