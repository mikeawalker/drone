figure
plot(time , a1, time ,a2, time,a3,'LineWidth',2)
xlabel('Time (s)')
ylabel('Corrected Acceleration (m/s^2)')
comb = [a1;a2;a3];
axis([0 max(time) min(comb) max(comb)])
figure
plot(time,w1,time,w2,time,w3,'LineWidth',2)
comb = [w1;w2;w3];
axis([0 max(time) min(comb) max(comb)])
xlabel('Time (s)')
ylabel('Corrected Angular Velocity (rad/s)')