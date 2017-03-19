byte val;
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
  delay(5);
  if(val==60){
  x1=numbeRead(); 
  delay(5);
  x2=numbeRead();
  
  }
  
Serial.print("<");
Serial.print((int)x1);
Serial.print((int)x2);


}
}

int numbeRead(){
  char cadena[22];
  int i=0;
  int x=0;
while (Serial1.available() > 0 ) { 

cadena[i]= Serial1.read();
if(cadena[i]=='>' || cadena[i]==',')break;
i++;
}
  cadena[i]=0;
  x=atoi(cadena);
  return x ;
} 
  
  
