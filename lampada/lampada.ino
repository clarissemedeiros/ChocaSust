int lamp = 5; 

void setup()
{
  pinMode(4, INPUT);
  pinMode(lamp, OUTPUT);
  
}


void loop()
{
  digitalWrite(lamp, 0);
}
