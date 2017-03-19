clear all;close all;clc
%borrar previos
delete(instrfind({'Port'},{'COM34'}));
%crear objeto serie
s = serial('COM34','BaudRate',9600,'Terminator','CR/LF');
warning('off','MATLAB:serial:fscanf:unsuccessfulRead');
%abrir puerto
fopen(s);
% parámetros de medidas
tmax = 300; % tiempo de captura en s
rate = 33; % resultado experimental (comprobar)

% preparar la figura
f = figure('Name','Captura');
a = axes('XLim',[0 tmax],'YLim',[0 100]);
l1 = line(nan,nan,'Color','r','LineWidth',2);
l2 = line(nan,nan,'Color','b','LineWidth',2);
l3 = line(nan,nan,'Color','g','LineWidth',2);
l4 = line(nan,nan,'Color','k','LineWidth',2);
l5 = line(nan,nan,'Color','m','LineWidth',2);

 
xlabel('Tiempo (s)')
ylabel('Voltaje (V)')
title('Captura de voltaje en tiempo real con Arduino')
grid on
hold on
% inicializar
v1 = zeros(1,tmax*rate);%referencia
v2 = zeros(1,tmax*rate);%motor1
v3 = zeros(1,tmax*rate);%motor2
v4 = zeros(1,tmax*rate);%motor3
v5 = zeros(1,tmax*rate);%motor4

i = 1;
t = 0;
 
% ejecutar bucle cronometrado
tic
while t<tmax
    t = toc;
    % leer del puerto serie
    a = fscanf(s,'%d,%d,%d,%d,%d')';
    v1(i)=a(1); 
    v2(i)=a(2); 
    v3(i)=a(3);
    v4(i)=a(4);
    v5(i)=a(5);
    % dibujar en la figura
    x = linspace(0,i/rate,i);
    set(l1,'YData',v1(1:i),'XData',x);
    set(l2,'YData',v2(1:i),'XData',x);
    set(l3,'YData',v3(1:i),'XData',x);
    set(l4,'YData',v4(1:i),'XData',x);
    set(l5,'YData',v5(1:i),'XData',x);
    drawnow
    % seguir
    i = i+1;
end
% resultado del cronometro
clc;
delete(instrfind({'Port'},{'COM34'}));
fprintf('%g s de captura a %g cap/s \n',t,i/t);
savefigure('captura_multi','s',[4.5 3],'po','-dpdf')
%% Limpiar la escena del crimen
fclose(s);
delete(s);
clear s;