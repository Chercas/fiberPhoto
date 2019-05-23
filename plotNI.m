function plotNI(~,b)
     global totalTime;
     subplot(3,1,1);plot(b.TimeStamps,b.Data(:,1), 'r'); hold on; title('PSM')
     axis([0 totalTime -0.3 3.5]); ylabel('Voltage [V]'); xlabel('Time [sec]')
     subplot(3,1,2);plot(b.TimeStamps,b.Data(:,2), 'b'); hold on; title('Trigger')
     axis([0 totalTime -0.3 3.5]); ylabel('Voltage [V]'); xlabel('Time [sec]')
end