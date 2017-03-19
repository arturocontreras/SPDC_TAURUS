byte inByte;

void setup()
{
Serial1.begin(9600); // Iniciamos el puerto serie a 9600 SIEMPRE, SIEMPRE ,SIEMPRE hay que empezar por esto.
Serial.begin(9600);
pinMode(13,OUTPUT);
}
void loop()
{
if (Serial1.available() > 0) { // Comprobamos si en el buffer (sála de espera) hay algo…..si lo hay entramos en el IF.
inByte = Serial1.read(); // leemos el primer caracter del buffer
if(inByte==65){ //Si inByte== a la letra a
Serial.println("a");}
if(inByte==67){ //Si inByte== a la letra c
Serial.println("c");}
}
}

