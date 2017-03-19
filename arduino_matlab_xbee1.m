%ABRIR el puerto COM6 SerXbee
delete(instrfind({'Port'},{'COM33'})); %ajustar puerto serie
delete(instrfind({'Port'},{'COM7'})); %ajustar puerto serie
clc; disp('BEGIN')
SerXbee = serial('COM33');
set(SerXbee,'BaudRate',9600);
set(SerXbee,'DataBits',8);
set(SerXbee,'Parity','none');
set(SerXbee,'StopBits',1);
set(SerXbee,'FlowControl','none');
fopen(SerXbee);
%*-*-*-*-*-*-
%ABRIR el puerto COM8 Arduino Mando
clc; disp('BEGIN')
SerArdu = serial('COM7');
set(SerArdu,'BaudRate',9600);
set(SerArdu,'DataBits',8);
set(SerArdu,'Parity','none');
set(SerArdu,'StopBits',1);
set(SerArdu,'FlowControl','none');
fopen(SerArdu);
%*-*-*-*-*-*-
a=zeros()
while(1)
    
a = fread(SerArdu,4,'uint8');

x1=a(1);
x2=a(2);
x3=a(3);
x4=a(4);

disp(x1);
disp(x2);
disp(x3);
disp(x4);

fwrite(SerXbee,'S','char');
fwrite(SerXbee,x1,'uint8');
fwrite(SerXbee,x2,'uint8');
fwrite(SerXbee,x3,'uint8');
fwrite(SerXbee,x4,'uint8');

end




fclose(SerXbee);
delete(SerXbee)
clear SerXbee
fclose(SerArdu);
delete(SerArdu)
clear SerArdu
disp('STOP')