fp1 = fopen('G:\Workspace\QuadDrone\EKF\SwTools\NavTest\NavTest\NavTest\NavInputs.dat','wb');
for k=1:20000
    fwrite(fp1, sensorAccel(k,:) , 'double');%0-2
    fwrite(fp1, sensorGyro(k,:), 'double'); %3-5
    fwrite(fp1, sensorGps(k,:), 'double'); %6-9
    fwrite(fp1, sensorMag(k,:), 'double'); %10-13
    fwrite(fp1, sensorGpsAccel(k,:),'double');%14-16
end
fclose(fp1)