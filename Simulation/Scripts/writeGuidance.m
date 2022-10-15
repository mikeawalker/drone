clc
close all
clearvars


dt = 0.01;
t = [0:dt:400];
xc =0+0.1*t;
yc = 0.1*t ; 
zc = 5*ones(size(t));

vc = [ .1+0.*t ; 0.1+ 0.*t];
% 
% % 
%   xc = 10*sind(2*t);
%    yc = 10*cosd(2*t) -10 ;
%       zc = 5*ones(size(t)) + 5*ones(size(t)).*(t>100) - .025.*t;
% %  %
%    vc = [ (pi/180)*20*cosd(2*t) ; (pi/180)*20*-sind(2*t)];

fp = fopen('../../DataFiles/a.dat','wb');

for k=1:length(t)
    fwrite( fp, t(k), 'double');
    fwrite( fp , xc(k) ,'double'); 
    fwrite( fp , yc(k) ,'double'); 
    fwrite( fp , zc(k) ,'double'); 
    fwrite( fp , vc(1,k) ,'double'); 
    fwrite( fp , vc(2,k) ,'double'); 
 
end

fclose(fp);