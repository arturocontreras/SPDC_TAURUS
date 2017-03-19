%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
close all;clear all;clc;

delete(instrfind({'Port'},{'COM6'})); %ajustar puerto serie
delete(instrfind({'Port'},{'COM5'})); %ajustar puerto serie

s = serial('COM5','BaudRate',9600,'Terminator','CR/LF');
%Para abrir el puerto serial mediante este comando:
%abrir puert
fopen(s);

pause(2)

% primero se captura un stream de video usando videoinput, con argumento
%de winvideo, numero de dispositivo y formato de la camara, si no sabes usa la
%funcion imaqtool para averiguarlo es YUY o RGB
imaqreset
vid=videoinput('winvideo',1,'YUY2_640x480');
%640x480 160x120
% Se configura las opciones de adquision de video
set(vid, 'FramesPerTrigger', Inf);
set(vid, 'ReturnedColorspace', 'rgb')
vid.FrameGrabInterval = 5;
%framegrabinterval significa que tomara cada 5 frame del stream de video adquirida
%con start(vid) se activa la adquisicion, pero todavia se toma la primera foto
start(vid)

% creamos un bucle que puede ser while always o while true en este caso
%y como mi compu es una netbook trucha(trucha=cagada=lenta=barata)
%hago que despues de 100 frames adquiridos se salga del bucle para evitar colgadas
while(vid.FramesAcquired<=500)

% se toma una snapshot del stream y se la almacena en data para trabajar mas
%facil
data = getsnapshot(vid);

% ahora vamos a reconocer el color rojo en tiempo real
% tenemos que extraer el color rojo
% de la imagen en escala de grises de la imagen adquirida en data
diff_im = imsubtract(data(:,:,1), rgb2gray(data));
%imsubstract sirve para sacar algun valor constante de una imagen, usamos como
%argumento el array de data y la funcion rgb2gray de data
%se usa medfilt2 para filtrar la senial del ruido
diff_im = medfilt2(diff_im, [3 3]);
% Convertir la imagen en escala de grises a una imagen binaria.
diff_im = im2bw(diff_im,0.18);

% para determinar el tamanio a reconocer se usa bwareopen para descartar
%imagen de rojo de menos de 300 pixels
diff_im = bwareaopen(diff_im,30);

% Etiquetamos los elementos conectados en la imagen
bw = bwlabel(diff_im, 8);

% Ahora hacemos el analisis del "objeto" detectado(que solo son pixels rojos)
%agrupados de mas de 300
% onfiguramos la region etiquetada
stats = regionprops(bw, 'BoundingBox', 'Centroid');

% mostramos la imagen
imshow(data)
% figure(2)
% imshow(diff_im)

hold on

%este es un bucle para encerrar el objeto rojo en un rectangulp y una cruz en el
%centroide(solo es programacion basica de matlab)
for object = 1:length(stats)
bb = stats(object).BoundingBox;
bc = stats(object).Centroid;

% coord_x=uint8(bc(1));
% coord_y=uint8(bc(2));

coord_x=bc(1);
coord_y=bc(2);

pause();
fwrite(s,'S','char');
fwrite(s,coord_x/4,'uint8');
fwrite(s,coord_y/4,'uint8');
a=fread(s,1)
b=fread(s,1)

rectangle('Position',bb,'EdgeColor','r','LineWidth',2)
plot(bc(1),bc(2), '-m+')
a=text(bc(1)+15,bc(2), strcat('X: ', num2str(round(bc(1))), ' Y: ', num2str(round(bc(2)))));
set(a, 'FontName', 'Arial', 'FontWeight', 'bold', 'FontSize', 12, 'Color', 'yellow');
end

hold off
end
% aqui terminan los 2 bucles

% detenemos la captura
stop(vid);
fclose(s);

%FLUSHDATA remueve la imagen del motor de adquisicion y la almacena en el buffer
flushdata(vid);

% borramos todo(como en cualquier programa)
clear all
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%