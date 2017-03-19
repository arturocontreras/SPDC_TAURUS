char val;
int x1;
int x2;
int set_point[4];
int out[2];

void setup()
{
Serial.begin(9600); // Iniciamos el puerto serie a 9600 SIEMPRE, SIEMPRE ,SIEMPRE hay que empezar por esto.
Serial1.begin(9600);
Serial3.begin(9600);

pinMode(13,OUTPUT);
}

void loop()
{
  
  //recepcion del XBEE
  if(Serial1.available()>0)
  {
    val=Serial1.read();
      if(val=='S'){
      while(Serial1.available()==0){};
        int i=0;
        for(i=0;i<4;i=i+1){
         set_point[i]=Serial1.read();
          while(Serial1.available()==0){};
         } 
       }  
   //envio al PIC Serial3   
//   Serial3.print('S');
//   Serial3.print(set_point[0]);
//   Serial3.print(set_point[1]);
   
   //enviando al monitor serial
   Serial.print(set_point[0]);
   Serial.print(" ");
   Serial.print(set_point[1]);
   Serial.print(" ");
   Serial.print(set_point[2]);
   Serial.print(" ");
   Serial.println(set_point[3]);
   
 }     

   //recibir datos del OUT del PIC
//   if(Serial3.available()>0)
//  {
//    val=Serial3.read();
//      if(val=='X'){
//      while(Serial3.available()==0){};
//        int i=0;
//        for(i=0;i<4;i=i+1){
//         out[i]=Serial3.read();
//          while(Serial3.available()==0){};
//         } 
//       }  
// } 
//  //enviando al monitor serial
//   Serial.print(out[0]);
//   Serial.print(" ");
//   Serial.print(out[1]);
//   Serial.print(" ");
//   Serial.print(out[2]);
//   Serial.print(" ");
//   Serial.println(out[3]); 
   
}



  
