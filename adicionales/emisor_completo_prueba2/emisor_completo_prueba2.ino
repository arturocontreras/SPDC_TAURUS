#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>


#define  p 255

#define PIN_ANALOG_X  1 
#define PIN_ANALOG_Y  0 
#define JOY_SERVO_X   2 
#define JOY_SERVO_Y   3

int x,y,xs,ys;
int P[2];
int T[2];

int rate[]={0,0,0,0,0,0};
 
void setup(){
 
  Serial.begin(9600);

}
 
void loop(){
 
  
  x=analogRead(PIN_ANALOG_X);
  y=analogRead(PIN_ANALOG_Y);
  xs=analogRead(JOY_SERVO_X);
  ys=analogRead(JOY_SERVO_Y);
  
  s_cal(xs,ys,T);
  pwm(x,y,P);
  
  for(int i=0;i<4;i++){rate[i]=0;} 
  
  if(P[0]>0)rate[0]=P[0];
  else rate[1]=-P[0];
  if(P[1]>0)rate[2]=P[1];
  else rate[3]=-P[1]; 
  
  rate[4]=T[0];
  rate[5]=T[1];
 Serial.print(x);
 Serial.print(" ");
 Serial.print(y);
 Serial.print(" "); 
 Serial.print(rate[0]);
 Serial.print(" ");
 Serial.print(rate[1]);
 Serial.print(" ");
 Serial.print(rate[2]);
 Serial.print(" ");
 Serial.println(rate[3]); 

 
 delay(70);
} 


void pwm(int x,int y, int* P){
        x=1023-x;

       if(x<=510){x=map(x,0,510,-p,0);}
       else{x=map(x,511,1023,1,p);}
       if(y<=500){y=map(y,0,500,-p,0);}
       else{y=map(y,501,1023,1,p);} 
   
       if(y<5&&y>-5)y=0;
       if(x<5&&x>-5)x=0;
       if(x==0&&y==0){                        //centro
       *P=0;
       *(P+1)=0;         
       }
       else if(x==0){                         //eje y
       *P=y;
       *(P+1)=y; 
       }  
       else if(y==0){                         //eje x
       *P=x;
       *(P+1)=-x;       
       }   
       else if(y>=x&&x>0){
       *P=y;
       *(P+1)=map(p-x,255,0,255,100);         
       }
       else if(y<x&&y>0){
       *P=x;
       *(P+1)=map(y-p,0,-255,100,-255);         
       }       
       else if(x>=-y&&y<0){
       *P=-x;
       *(P+1)=map(y+p,255,0,255,-100);         
       }      
       else if(x<-y&&x>0){
       *P=y;
       *(P+1)=map(x-p,0,-255,-100,-255);         
       } 
       else if(x>=y&&x<0){
       *P=map(-p-x,-255,0,-255,-100);
       *(P+1)=y;         
       } 
       else if(x<y&&y<0){
       *P=map(y+p,0,255,-100,255);
       *(P+1)=x;         
       } 
       else if(x<=-y&&y>0){
       *P=map(y-p,-255,0,-255,100);
       *(P+1)=-x;         
       } 
       else if(x>-y&&x<0){
       *P=map(x+p,0,255,100,255);
       *(P+1)=y;         
       }

       }
      
      void s_cal(int x,int y, int* T){
 

       x=1023-x;                    

       if(x<=507){x=map(x,0,507,0,90);}
       else{x=map(x,507,1023,91,180);}
       if(y<=497){y=map(y,0,497,0,90);}
       else{y=map(y,498,1023,91,180);} 
       
       if(x<95&&x>85)x=90; 
       if(x>175)x=180;
       if(x<5)x=0;
       
       if(y<95&&y>85)y=90;
       if(y>175)y=180;
       if(y<5)y=0;
       
       *T=x;
       *(T+1)=y;
       }





