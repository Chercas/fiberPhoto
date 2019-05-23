function startFiber(tTime, F0Time)
close all;

% %--Manual Start----
% tTime = 20;
% F0Time = 10; %Real time in [sec]
% %------------------

global totalTime;
totalTime = tTime;
daq.getDevices;
s = daq.createSession('ni');
sampRate = 100; 
s.Rate = sampRate;
s.DurationInSeconds = totalTime;

%Adding channels
addAnalogInputChannel(s, 'Dev1', 0, 'Voltage'); % PSM -> NI+TBS1154
addAnalogInputChannel(s, 'Dev1', 1, 'Voltage'); % Analog sync+TBS1154

lh = addlistener(s,'DataAvailable', @plotNI); % Listner 
[data,time] = s.startForeground; %Start acquisition
%plot(time, data); axis([0 10 -3 3]);

numChannels = size(data,2);

for i=1:numChannels
    chNumber = strcat('ch', num2str(i-1));
    ni.(chNumber) = data(:,i);
end

%Finding time-dept. baseline F0
F0TimeLabel = F0Time*sampRate; %Time to data map
F0Data = F0TimeLabel; %Data is mapped one-to-one with time
F0 = mean(ni.ch0(1:F0Data));
%Calculating relative change in signal representation
relSigChange = (ni.ch0 - F0)/F0;
forgetFactor = 0.7;
movExpAver = dsp.MovingAverage('Method', 'Exponential weighting', 'ForgettingFactor', forgetFactor);
deltaFF = movExpAver(relSigChange);
%Plotting result
subplot(3,1,3);plot(time, relSigChange, 'Color', [0.7 0.7 0.7]); hold on;...
plot(time, deltaFF, 'r'); legend('Signal Change', 'Exp weighting');...
title('Fluorescence Signal Change'); xlabel('Time [sec]'); ylabel('{\Delta}F/F'); 

%[data,time] = startForeground(s);
wait(s)
delete(lh)

filename = 'FibePhotoTest.mat';
save(filename)

end