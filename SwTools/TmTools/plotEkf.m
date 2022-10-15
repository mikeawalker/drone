function plotEkf( ekfFile )


ekf=load(ekfFile);

time = ekf(:,1);
x = ekf(:,2);
y = ekf(:,3);
z = ekf(:,4);
vx = ekf(:,5);
vy = ekf(:,6);
vz = ekf(:,7);
q1 = ekf(:,8);
q2 = ekf(:,9);
q3 = ekf(:,10);
q4 = ekf(:,11);
ax = ekf(:,12);
ay = ekf(:,13);
az = ekf(:,14);
wx = ekf(:,15);
wy = ekf(:,16);
wz = ekf(:,17);


figure
subplot(2,1,1)
hold on
plot(time,x)
plot(time,y,'r')
plot(time,z,'g')
xlabel('Time (s)')
ylabel('Position')
subplot(2,1,2)
hold on
plot(time,vx)
plot(time,vy,'r')
plot(time,vz,'g')
xlabel('Time (s)')
ylabel('Velocity')

figure
hold on
plot(time,q1)
plot(time,q2,'r')
plot(time,q3,'g')
plot(time,q4,'k')
xlabel('Time (s)')
ylabel('Quaternion')


figure
plot3(x,y,z);
xlabel('X')
ylabel('Y')
zlabel('Z')