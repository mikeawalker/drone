
[E N U] = ecef2enu(XE,YE,ZE);
%% plotting
figure
subplot(3,1,1)
plot(time,x,'LineWidth',2)
hold on
plot(gpsTime , E , '.', 'MarkerSize',10)
ylabel('East (m)')
xlabel('Time (s)')
legend('Estimated','GPS')
axis([0 max(time) min(x) max(x)])
subplot(3,1,2)
plot(time,y,'LineWidth',2)

hold on
plot(gpsTime , N , '.', 'MarkerSize',10)
ylabel('North (m)')
xlabel('Time (s)')
axis([0 max(time) min(y) max(y)])
subplot(3,1,3)
plot(time,z,'LineWidth',2)
hold on
plot(gpsTime , U , '.', 'MarkerSize',10)
ylabel('Up (m)')
xlabel('Time (s)')
axis([0 max(time) min(z) max(z)])


figure
plot(time,vx,time,vy,time,vz,'LineWidth',2)
xlabel('Time (s)')
ylabel('Velocity (m/s)')
legend('Veast','Vnorth','Vup')

%% Kml Plot Generation
[Xs Ys Zs] = enu2ecef( x,y,z , XE(1) , YE(1) , ZE(1));
lat = (180/pi)* atan( Zs ./ sqrt(Xs.*Xs + Ys.*Ys) );
long = (180/pi)*atan2( Ys , Xs );
alt = 10+(sqrt(Xs.*Xs + Ys.*Ys + Zs.*Zs ) - sqrt( XE(1)*XE(1) + ZE(1)*ZE(1) +YE(1)*YE(1)));
kmlStr = ge_plot3( long , lat , alt,'lineWidth',4,'lineColor','ff32a4ff');
ge_output('demo_ge_plot3.kml',kmlStr);