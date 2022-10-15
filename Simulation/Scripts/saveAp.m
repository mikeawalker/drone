fp2 = fopen('G:\Workspace\QuadDrone\EKF\SwTools\ApTest\ApTest\ApTest\AutopilotInputs.dat','wb');
for k=1:length(QAp)
   fwrite(fp2,QAp(k,:),'double'); %0-3
   fwrite(fp2,OmegaAp(k,:),'double');%4-6
   fwrite(fp2,mCmd(k,:),'double');%7-9
   fwrite(fp2,AccelAp(k,:),'double');%10-12
   fwrite(fp2,ApAccelCmd(k,:),'double');%13-15
   fwrite(fp2,ApVelCmd(k,:),'double');%16 17
   fwrite(fp2,ApFtot(k,:),'double');%18
   fwrite(fp2,VelEst(k,:),'double'); %19 20 21  
   fwrite(fp2,yawCmdSim(k,:),'double');%22
end
fclose(fp2)
