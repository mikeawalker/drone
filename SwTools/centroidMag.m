
close all
%tm = magDat(:,4);
%mag = magDat(:,1:3);
colat = 90-32;
mhat = [0;-sind(colat);-2*cosd(colat)];
x= m1; y =m2; z=m3;
mag = [m1,m2,m3];


vertMagUnit = mhat(3) / sqrt(dot(mhat,mhat));
%% Calculate roation
cx  = min(x) + .5*( max(x) - min(x) );
cy  = min(y) + .5*( max(y) - min(y) );
cz = (min(z) + .5*( max(z) - min(z) )) ;

rx = x  - cx;
ry = y  - cy;
rz = z  - cz;

rxz = sqrt( rx.*rx + rz.*rz );
ryz = sqrt( ry.*ry + rz.*rz );

[m kxz] = max( rxz );
[m kyz] = max( ryz );

ang_yz = (180/pi)*atan2( rz(kyz) , ry(kyz) );
ang_xz =(180/pi)* atan2( rz(kxz) , rx(kxz) );
if( ang_yz > 90 )
   ang_yz = -(180 - ang_yz); 
end

if( ang_xz > 90 ) 
   ang_xz = -(180 - ang_xz); 
end


Rx = [cosd(ang_xz) , 0 , sind(ang_xz);...
      0 , 1 , 0;...
      -sind(ang_xz) , 0 , cosd(ang_xz)];
Ry = [1 , 0 ,0;...
      0 , cosd(ang_yz) , sind(ang_yz);...
      0 , -sind(ang_yz) , cosd(ang_yz)];
  
  
%% Redo Rotations
  DCM = Rx*Ry;
  for k= 1:length(x)
     % temp_vec = [rx(k);ry(k); rz(k)];
      temp_vec = [x(k);y(k); z(k)];
      new_vec = DCM*temp_vec;
      x_new(k) = new_vec(1);
      y_new(k) = new_vec(2);
      z_new(k) = new_vec(3);
  end
  

%% Calculate current offsets  
cxx  = min(x_new) + .5*( max(x_new) - min(x_new) );
cyy  = min(y_new) + .5*( max(y_new) - min(y_new) );
czz = (max(z_new) + .5*( min(z_new) - max(z_new) ))+40.4 ;

scale = 1;


x_corr = scale*(x_new - cxx );
y_corr = scale*(y_new  -cyy);
z_corr = scale*(z_new - czz);
corr_mag = sqrt( x_corr.^2 + y_corr.^2 + z_corr.^2);

x_unit = x_corr./corr_mag;
y_unit = y_corr./corr_mag;
z_unit = z_corr./corr_mag;

%% Plots
figure
hold on
plot( mag(:,1) , mag(:,2) , 'r.')
plot( mag(:,2) , mag(:,3) , 'g.')
plot( mag(:,1) , mag(:,3) , 'k.')


plot( cx , cy , 'rx')
plot( cx , cz , 'kx')
plot(cy,cz , 'gx')


figure
hold on
plot( x-cx , y-cy , 'r.');
plot( x-cx , z-cz , 'k.')
plot( y-cy , z-cz ,'g.')
axis equal


figure
hold on
plot(x_new,y_new,'r.')
plot(x_new,z_new,'k.')
plot(y_new,z_new,'g.')
axis equal

figure
hold on
plot(x_corr,y_corr,'r.')
plot(x_corr,z_corr,'k.')
plot(y_corr,z_corr,'g.')
axis equal

figure
hold on
plot(x_unit,y_unit,'r.')
plot(x_unit,z_unit,'k.')
plot(y_unit,z_unit,'g.')
plot([-1 1], vertMagUnit.*[1 1] ,'r')



figure
plot(sqrt(x_unit.^2 + y_unit.^2 + z_unit.^2) )

%%
disp('Rotation Matrix')
disp(Rx*Ry)
disp('Offsets')
disp(cxx)
disp(cyy)
disp(czz)
disp(scale)

%%
vectorOut = [ DCM(1,:) , DCM(2,:) , DCM(3,:) , cxx,cyy,czz,scale];
fp = fopen('MagCal.dat','w');
fwrite(fp , vectorOut , 'double');
fclose(fp);