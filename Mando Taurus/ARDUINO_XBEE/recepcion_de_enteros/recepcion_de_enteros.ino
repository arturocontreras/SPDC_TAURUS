void setup() {
Serial.begin(9600);
}

char cadena[24];
byte contador=0;
int valor=0;

void loop(){
if(Serial.available()){
memset(cadena, 0, sizeof(cadena));
while (Serial.available()>0){
delay(5);
cadena[contador]=Serial.read();
contador++;
}
valor=atoi(cadena);
Serial.println(valor+1);
contador=0;
}
}
