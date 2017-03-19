
byte val;
int x1;
int x2;

void setup()
{
Serial.begin(9600); // Iniciamos el puerto serie a 9600 SIEMPRE, SIEMPRE ,SIEMPRE hay que empezar por esto.
pinMode(13,OUTPUT);
}

void loop()
{
  if(Serial.available()){

   val=Serial.read(); 
    delay(5);
  if(val==60){
  x1=numbeRead(); 
  delay(5);
  x2=numbeRead();
  
  }

  analogWrite(3,x1);
  analogWrite(5,x2);
//  Serial.println(x1);
//  Serial.println(x2);
  

}
}

int numbeRead(){
  char cadena[22];
  int i=0;
  int x=0;
while (Serial.available() > 0 ) { 

cadena[i]= Serial.read();
if(cadena[i]=='>' || cadena[i]==',')break;
i++;
}
  cadena[i]=0;
  x=atoi(cadena);
  return x ;
} 
  
  
