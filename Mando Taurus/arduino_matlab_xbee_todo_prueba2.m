%ABRIR el puerto COM6 SerXbee
delete(instrfind({'Port'},{'COM14'})); %ajustar puerto serie

delete(instrfind({'Port'},{'COM15'})); %ajustar puerto serie
clc; disp('BEGIN')

SerXbee = serial('COM14');
set(SerXbee,'BaudRate',9600);
set(SerXbee,'DataBits',8);
set(SerXbee,'Parity','none');
set(SerXbee,'StopBits',1);
set(SerXbee,'FlowControl','none');
fopen(SerXbee);
%*-*-*-*-*-*-
%ABRIR el puerto COM8 Arduino Mando
clc; disp('BEGIN')
SerArdu = serial('COM15');
set(SerArdu,'BaudRate',9600);
set(SerArdu,'DataBits',8);
set(SerArdu,'Parity','none');
set(SerArdu,'StopBits',1);
set(SerArdu,'FlowControl','none');
fopen(SerArdu);
%*-*-*-*-*-*-
a=zeros()
while(1)
    
    
a = fread(SerArdu,7,'uint8');

id=a(1);
if id=='A'
x1=a(2);
x2=a(3);
x3=a(4);
x4=a(5);
x5=a(6);
x6=a(7);
else
x1=0;
x2=0;
x3=0;
x4=0;
x5=0;
x6=0;
end
disp(x1);
disp(x2);
disp(x3);
disp(x4);
disp(x5);
disp(x6);

fwrite(SerXbee,'S','char');
fwrite(SerXbee,x1,'uint8');
fwrite(SerXbee,x2,'uint8');
fwrite(SerXbee,x3,'uint8');
fwrite(SerXbee,x4,'uint8');
fwrite(SerXbee,x5,'uint8');
fwrite(SerXbee,x6,'uint8');

pause(0.01);
end

fclose(SerXbee);
delete(SerXbee)
clear SerXbee
fclose(SerArdu);
delete(SerArdu)
clear SerArdu
disp('STOP')