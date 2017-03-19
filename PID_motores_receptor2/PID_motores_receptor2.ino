int ibyte;
int velocidades[2];

int m1a=0;
int m1r=0;
int m2a=0;
int m2r=0;//señal para motores

int Encoder_m1=A0;
int Encoder_m2=A1;
int Encoder_m3=A2;
int Encoder_m4=A3;
int set_point1=A4;


///////////////
unsigned long lastTime;
double Input, Output, Setpoint_m1;
double errSum, lastInput;
double kp, ki, kd;
int SampleTime = 20; 
//////////////

void Compute()
{
unsigned long now = millis();
int timeChange = (now - lastTime);
if(timeChange>=SampleTime)
{
// Calcula todas las variables de errores.
double error = Setpoint_m1 - Input;

errSum += error;
double dInput = (Input - lastInput);
// Calculamos la función de salida del PID.
Output= kp * error + ki * errSum - kd * dInput;

if(Output<0) Output=0;

if(Output>100) Output=100;
Output=(Output*255)/100;
// Guardamos el valor de algunas variables para el próximo ciclo de cálculo.
lastInput = Input;
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

///////////////////////////////////////////

void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  Serial1.begin(9600);
  //pines motor
  pinMode(9, OUTPUT);   //m2r
  pinMode(10, OUTPUT);   //m2a
  pinMode(11, OUTPUT);   //m1r
  pinMode(12, OUTPUT);   //m1a
  
  pinMode(A5, OUTPUT);
  digitalWrite(A5, HIGH);
  pinMode(A6, OUTPUT);
  digitalWrite(A6, LOW);

  SetTunings(4, 3, 0);
}

void loop() {
  
//Recepcionando los valores de velocidad setpoint , enviados por 
//el controlador de navegacion
// TX1 , RX1

// if(Serial1.available()>0)
//  {
//    ibyte=Serial1.read();
//      if(ibyte=='S'){ 
//      while(Serial1.available()==0){};
//        int i=0;
//        for(i=0;i<2;i=i+1){
//         velocidades[i]=Serial1.read();
//          while(Serial1.available()==0){};
//         } 
//     }  
//  }
  
//Asignacion de variables
Setpoint_m1=map(analogRead(set_point1), 0, 1023, 0, 61);//escalar para maximo 100 equivalente a 255
Input=map(analogRead(Encoder_m3), 0, 1023, 0, 100);
// Setpoint_m2=velocidades[1];
//modelo del movil
// M1-----M2
// M3 --- M4

Serial.print((int)Setpoint_m1);
Serial.print(",");
Serial.println((int)Input);
  
// Rutina del controlador PID
Compute();
m1a=Output;
//ejecucion de pwms
analogWrite(11,m1a);

}
