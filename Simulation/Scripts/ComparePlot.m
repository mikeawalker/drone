function ComparePlot( V1 , V2 , mode)
figure

if( mode == 1)
    
    plot(V1-V2,'.')
else
    
    plot(V1,'.')
    hold on
    plot(V2,'o')
end