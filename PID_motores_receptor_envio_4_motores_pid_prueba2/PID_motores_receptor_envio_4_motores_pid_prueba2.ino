int ibyte;
int velocidades[2];
int set_point[4];
char val;
int m1a=0;
int m1r=0;
int m2a=0;
int m2r=0;//señal para motores
int m3a=0;
int m3r=0;
int m4a=0;
int m4r=0;//señal para motores

int Encoder_m1=A0;
int Encoder_m2=A1;
int Encoder_m3=A2;
int Encoder_m4=A3;

int set_point1=A4;

///////////////
unsigned long lastTime;
double Input,Input2,Input3,Input4, Output,Output2,Output3,Output4, Setpoint_m1,Setpoint_m2,Setpoint_m3,Setpoint_m4;
double errSum,errSum2,errSum3,errSum4, lastInput,lastInput2,lastInput3,lastInput4;
double kp,kp2,kp3,kp4,ki,ki2,ki3,ki4,kd,kd2,kd3,kd4;
int SampleTime = 20; 
//////////////

void Compute()
{
unsigned long now = millis();
int timeChange = (now - lastTime);
Serial.println((int)timeChange);
if(timeChange>=SampleTime)
{
// Calcula todas las variables de errores.
double error = Setpoint_m1 - Input;
double error2 = Setpoint_m2- Input2;
double error3 = Setpoint_m3 - Input3;
double error4 = Setpoint_m4 - Input4;

errSum += error;
errSum2 += error2;
errSum3 += error3;
errSum4 += error4;

double dInput = (Input - lastInput);
double dInput2 = (Input2 - lastInput2);
double dInput3 = (Input3 - lastInput3);
double dInput4 = (Input4 - lastInput4);

// Calculamos la función de salida del PID.
Output=  kp * error + ki * errSum - kd * dInput;
Output2= kp2 * error2 + ki2 * errSum2 - kd2 * dInput2;
Output3= kp3 * error3 + ki3 * errSum3 - kd3 * dInput3;
Output4= kp4 * error4 + ki4 * errSum4 - kd4 * dInput4;

//saturacion
if(Output<0) Output=0;
if(Output>100) Output=100;
Output=(Output*255)/100;

if(Output2<0) Output2=0;
if(Output2>100) Output2=100;
Output2=(Output2*255)/100;

if(Output3<0) Output3=0;
if(Output3>100) Output3=100;
Output3=(Output3*255)/100;

if(Output4<0) Output4=0;
if(Output4>100) Output4=100;
Output4=(Output4*255)/100;

// Guardamos el valor de algunas variables para el próximo ciclo de cálculo.
lastInput = Input;
lastInput2 = Input2;
lastInput3 = Input3;
lastInput4 = Input4;

lastTime = now;
}
}

void SetTunings(double Kp, double Ki, double Kd)
{
double SampleTimeInSec = ((double)SampleTime)/1000;
kp = Kp;
ki = Ki * SampleTimeInSec;
kd = Kd / SampleTimeInSec;
}

void SetTunings2(double Kp, double Ki, double Kd)
{
double SampleTimeInSec = ((double)SampleTime)/1000;
kp2 = Kp;
ki2 = Ki * SampleTimeInSec;
kd2 = Kd / SampleTimeInSec;
}

void SetTunings3(double Kp, double Ki, double Kd)
{
double SampleTimeInSec = ((double)SampleTime)/1000;
kp3 = Kp;
ki3 = Ki * SampleTimeInSec;
kd3 = Kd / SampleTimeInSec;
}

void SetTunings4(double Kp, double Ki, double Kd)
{
double SampleTimeInSec = ((double)SampleTime)/1000;
kp4 = Kp;
ki4 = Ki * SampleTimeInSec;
kd4 = Kd / SampleTimeInSec;
}



///////////////////////////////////////////

void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  Serial1.begin(9600);
  //pines motor
  
  pinMode(4, OUTPUT);   //m1a
  pinMode(5, OUTPUT);   //m1r
  pinMode(6, OUTPUT);   //m2a
  pinMode(7, OUTPUT);   //m2r
  pinMode(8, OUTPUT);   //m4a
  pinMode(9, OUTPUT);    //m4r
  pinMode(10, OUTPUT);   //m3r
  pinMode(11, OUTPUT);   //m3a
  
  pinMode(A5, OUTPUT);
  digitalWrite(A5, HIGH);
  pinMode(A6, OUTPUT);
  digitalWrite(A6, LOW);
  
  SetTunings(6, 4, 0); //kp,ki,kd
  SetTunings2(6,4, 0);
  SetTunings3(5, 2, 0);
  SetTunings4(5, 2, 0);
   
}

void loop() {
  
//if(Serial1.available()>0)
//  {
//    val=Serial1.read();
//      if(val=='S'){ 
//      while(Serial1.available()==0){};
//        int i=0;
//        for(i=0;i<4;i=i+1){
//         set_point[i]=Serial1.read();
//          while(Serial1.available()==0){};
//         } 
//      } 
//  } 
//Asignacion de variables
// 255 0 255 0
Setpoint_m1=map(set_point[0], 0, 255, 0, 49);//escalar para maximo 100 equivalente a 255
Setpoint_m2=map(set_point[0], 0, 255, 0, 58);//escalar para maximo 100 equivalente a 255
Setpoint_m3=map(set_point[0], 0, 255, 0, 45);//escalar para maximo 100 equivalente a 255
Setpoint_m4=map(set_point[0], 0, 255, 0, 53);//escalar para maximo 100 equivalente a 255


Input= map(analogRead(Encoder_m1), 0, 1023, 0, 100);
Input2=map(analogRead(Encoder_m2), 0, 1023, 0, 100);
Input3=map(analogRead(Encoder_m4), 0, 1023, 0, 100);
Input4=map(analogRead(Encoder_m3), 0, 1023, 0, 100);

//modelo del movil
// M1-----M2
// M3 --- M4

//Serial.print((int)Setpoint_m2);
//Serial.print(",");
//Serial.print((int)Input);
//Serial.print(",");
//Serial.print((int)Input2);
//Serial.print(",");
//Serial.print((int)Input3);
//Serial.print(",");
//Serial.println((int)Input4);

//m1=4
// Rutina del controlador PID
Compute();
m1a=Output;
m2a=Output2;
m3a=Output3;
m4a=Output4;
//ejecucion de pwms
//Serial.println((int)m2a);
analogWrite(4,m1a);
analogWrite(6,m2a);
analogWrite(10,m4a);
analogWrite(8,m3a);

//analogWrite(4,255);
//analogWrite(6,255);
//analogWrite(10,255);
//analogWrite(8,255);

}
