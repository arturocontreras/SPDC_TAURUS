int x1;
int x2;
int x3;
int x4;

void setup(){
Serial.begin(9600);
}

void loop(){
  
 x1=analogRead(0);
 x2=analogRead(1);
 x3=analogRead(2);
 x4=analogRead(3);
  

// Serial.write('<');
// Serial.write(x1);
// Serial.write(',');
// Serial.write(x2);
// Serial.write(',');
// Serial.write(x3);
// Serial.write(',');
// Serial.write(x4);
// Serial.write('>');

// Serial.print('<');

 x1=map(x1,0,1023,0,255);
 x2=map(x2,0,1023,0,255);


 Serial.print((char)x1);
 //Serial.print(',');
 Serial.print((char)x2);

// Serial.print(',');
// Serial.print(x3);
// Serial.print(',');
// Serial.print(x4);
// Serial.println('>');



 delay(20);
}
