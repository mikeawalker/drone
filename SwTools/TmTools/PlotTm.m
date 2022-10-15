clc
clearvars
close all
type = 0
if type == 1
plotMagno('G:\Workspace\QuadDrone\EKF\FlightSoftware\Build\TmGrabber\Debug\MagData.dat');
plotImu('G:\Workspace\QuadDrone\EKF\FlightSoftware\Build\TmGrabber\Debug\ImuData.dat');
plotEkf('G:\Workspace\QuadDrone\EKF\FlightSoftware\Build\TmGrabber\Debug\StateData.dat');
else
plotFileEkf('G:\Workspace\QuadDrone\DroneData\Dec262014_Car\ekf_044654.txt');
[lla] =plotFileGps('G:\Workspace\QuadDrone\DroneData\Dec262014_Car\gps_044654.txt');
end


out = ge_plot3(lla(:,2) , lla(:,1) , 0*lla(:,3)  ,...
                    'lineWidth',3,...
                    'lineColor','ff32a4ff',...
                         'name','out01');
kmlName = 'file1.kml'
ge_output(kmlName, out)