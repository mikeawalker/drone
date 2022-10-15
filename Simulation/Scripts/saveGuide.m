fp3 = fopen('G:\Workspace\QuadDrone\EKF\SwTools\GuideTest\GuideTest\GuideTest\GuideInputs.dat','wb');
for k=1:length(guideTime)
    fwrite(fp3, guideTime(k) , 'double');%0
    fwrite(fp3, guidePos(k,:), 'double'); %1-3
    fwrite(fp3, guideVel(k,:), 'double'); %4-6
end
fclose(fp3)