
[roll, pitch ,yaw] = q2rpy( q1,q2,q3,q4 );

figure
subplot(3,1,1)
plot(time,roll,'LineWidth',2)
xlabel('time (s)')
ylabel('roll (deg)')
axis([0 max(time) min(roll) max(roll)])
subplot(3,1,2)
plot(time,pitch,'LineWidth',2)
axis([0 max(time) min(pitch) max(pitch)])
xlabel('time (s)')
ylabel('pitch (deg)')
subplot(3,1,3)
plot(time,yaw,'LineWidth',2)
axis([0 max(time) min(yaw) max(yaw)])
xlabel('time (s)')
ylabel('heading (deg)')
