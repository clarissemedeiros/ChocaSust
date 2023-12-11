int AC_LOAD = 3;
int dimming = 125;
unsigned long time;
unsigned long timeout;
int brilho[3];
int i=0;
int flag=0;
char temp;
int x,y;

void setup()
{
  Serial.begin(9600);
  pinMode(AC_LOAD, OUTPUT);
  attachInterrupt(0, zero_crosss_int, RISING);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  
}

void zero_crosss_int() 
{
  int dimtime = (65*dimming);
  delayMicroseconds(dimtime); 
  digitalWrite(AC_LOAD, HIGH); 
  delayMicroseconds(8.33); 
  digitalWrite(AC_LOAD, LOW); 
}

void loop()
{
  time = millis()%2;
  if(time==1||time==0)
  {
  timeout++;
    if (timeout>500)
    {
    i=0;
    flag=0;
    }  
   }
 

  if(digitalRead(4)==1 && dimming >10)
  {
   dimming= dimming -5;
    y=dimming/1.25;
    y=(y-100)*(-1);
    Serial.print(y);
    Serial.println("%");
    Serial.print("Resolucao: ");
    Serial.println(dimming);
    delay(100);
  }
  
  if(digitalRead(5)==1&& dimming<125)
  {
    dimming= dimming +5; 
    y=dimming/1.25;
    y=(y-100)*(-1);
    Serial.print(y);
    Serial.println("%");
    Serial.print("Resolucao: ");
    Serial.println(dimming);
    delay(100);
  }

  if (Serial.available()>0)
  {
    flag=1;
    timeout=0;
  
    temp = Serial.read();
    brilho[i]=temp-48;
    i++;
  }
  
if (timeout>200&&flag==1)
{
  flag=0;
  
   
   switch(i)
   {
   case 1:
   x=brilho[0];
   break;
   
   case 2:
   x=brilho[0]*10 + brilho[1];
   break;
   
   case 3:
   x=brilho[0]*100 + brilho[1]*10 + brilho[2];
   break;
   }  
 
    Serial.print(x);
    Serial.println("%");
     delay(30);
   
    if(x>100||x<0)
    {
    Serial.println("Excedeu o limite");
    }
    else
    {
    x=100-x;
    dimming=x*1.25;
      if(dimming<8)
      {
      dimming=8;
      }
 
    Serial.print("Resolucao: ");
    Serial.println(dimming);
    }

}
}
