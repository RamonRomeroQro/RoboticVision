//Declara tus brikos
//Declara tus brikos


//Declara tus brikos

distancebk sensordistancia (PORT7);
temperaturebk sensortemperatura (PORT5);
lightbk sensorluz (PORT3);
buzzerbk bocina (PORT4);


motorbk motor1 (PORT2);
motorbk motor2 (PORT6);

// These values were calculated by measuring the robot’s movement 
// speed
int degree90 = 918;
int degree60 = 1224;
int water=1;

void firefight(){
  motor1.set(LEFT);
  motor2.set(RIGHT);
  delay(2000);
  
 
  bk7println("stopped"); //I

  
  //if (sensortemperatura.read(F) > 25 and water == 1)
  //{
  //  motor1.set(STOP);
  //  motor2.set(STOP);
  //  
  //  while(sensordistancia.read(CM) > 15)
  //  {
  //    motor1.set(LEFT);
  //    motor2.set(RIGHT);
  //  }
  //  
  //  motor1.set(STOP);
  //  motor2.set(STOP);
  //  delay(3000);
  //  water = 0;
  //}
  water=1;
  
  if(water == 1 and sensorluz.read() > 40)
  {
    motor1.set(STOP);
    motor2.set(STOP);
    
    while(sensordistancia.read(CM) > 15)
    {
      motor1.set(LEFT);
      motor2.set(RIGHT);
    }
    
    motor1.set(STOP);
    motor2.set(STOP);
    bocina.set(ON);
    delay(3000);
  bocina.set(OFF);
    water = 0;
  }
  
  
  motor1.set(LEFT);
  motor2.set(LEFT);
  int d = random(0,918);
  delay(d);
  motor1.set(STOP);
  motor2.set(STOP);
 
  
}


//


/////Escribe tu codigo
code(){


firefight();


//int temp = sensortemperatura.read();
//bk7println(temp);



}
/////Termina loop




















