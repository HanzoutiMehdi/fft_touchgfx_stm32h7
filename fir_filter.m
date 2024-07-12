close all;
clear all;
clc;

pkg load signal


%FIR1
fs=250; 
fc=20; %20Hz  
wc=fc/(fs/2);   % normalized frequency

b=fir1(80,wc);  % Low pass filter

figure;
stem(b);   

freqz(b,1,2^12,fs);   %frequency response of filter 
[H,f]=freqz(b,1,2^12,fs);
figure;
plot(f,abs(H));
xlabel('Frequency Hz');
ylabel('Freq Response');
box off; grid on; axis tight;


