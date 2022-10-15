clearvars
clc
close all

% Physical
G=0.1
Iax = 1;
%
%
Ft=10.81
p1 = 1;
p2 =3;
p3 = 3;
Kss= 1
Ka_Ft = p1*p2*p3
Kq = -(p1 + p2 + p3)
Ksyn = -(p3*p1 + p3*p2 + p1*p2)  - Kq

Ka = Ka_Ft/Ft;


s = tf('s');



th_dm = tf([1],[Iax 0 -G]);
q_dm =s*th_dm;
Am_dm = th_dm;



dM_dAc = (1/s)*Ka*Kss / (1 + Ka*Am_dm/s  - (Ksyn/s)*q_dm - Kq*q_dm  );
FNyq =  (1/s)*Ka*Kss / (1   - (Ksyn/s)*q_dm - Kq*q_dm  );


U = 1/s;


% problem th_dm*dM_dAc ~= Am_Ac/Ft ???
Am_Ac = minreal(Am_dm * dM_dAc)
Th_Ac = minreal( th_dm * dM_dAc)
Q_Ac = minreal( q_dm* dM_dAc)
rlocus(Am_Ac,0)
step(Am_Ac)
fnyq = minreal(FNyq)

FVT = minreal((s) * Am_Ac * U )
figure
%rlocus( Am_Ac , 0)
nyquist( fnyq )
%grid on