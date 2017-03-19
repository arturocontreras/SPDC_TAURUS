char val;
int x1;
int x2;

void setup()
{
Serial.begin(9600); // Iniciamos el puerto serie a 9600 SIEMPRE, SIEMPRE ,SIEMPRE hay que empezar por esto.
Serial1.begin(9600);
Serial3.begin(9600);

pinMode(13,OUTPUT);
}

void loop()
{
  if(Serial1.available()){
   val=Serial1.read(); 
   Serial.print(val);
   Serial3.print(val);
  }
 
}



  
