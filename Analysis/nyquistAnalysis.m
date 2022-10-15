function VM =  nyquistAnalysis( OL )

lim = 100;

f= linspace(0,lim,100000);

n = OL.num{1};
d = OL.den{1};
N = polyval( n , 1j*f );
D = polyval( d, 1j*f );

Envelope = N./D;

Ang = (180/pi)*atan2( imag(Envelope) , real(Envelope ));
Mag = 10*log10( Envelope.*conj(Envelope)) ;

CritPnt = -1;

D = Envelope - CritPnt ;

[VM k] = min( sqrt( D.*conj(D) ) );

angK = atan2( imag(D(k)) , real(D(k)) );
%% do the nyquist plot
figure
set(gcf,'Position', [100, 100, 1000, 550]);
nyquist(OL)
hold on
%% do gain and phase margin
th = [0:.01:2*pi];
plot( -1+VM*cos(th) , VM*sin(th) , 'r' )

quiver( -1,0, VM*cos(angK) , VM*sin(angK) ,1,'r');

VectorM= sprintf('Vector Margin: %.3f', VM );

% Create textbox
annotation(gcf,'textbox',...
    [0.153295128939828 0.82367954521827 0.381880697319675 0.0658910069289687],...
    'String',{VectorM},...
    'LineStyle','none',...
    'FontWeight','bold',...
    'FontSize',20,...
    'FontName','Helvetica');

end

