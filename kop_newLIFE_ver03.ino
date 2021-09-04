#include<Console.h>

int anodPins[] = {A1, A2, A3, A4}; // Задаем пины для кажого разряда
int segmentsPins[] = {5, 6, 7, 8, 9, 10, 11, 12}; //Задаем пины для каждого сегмента (из 7 + 1(точка))
int photocellPin = 14; // сенсор и понижающий резистор 10 кОм подключены к a0
int LEDpin =2;
int incBtn = 0;
int decBtn = 13;
int clearBtn = 1;
int BtnSleep = 3;
double time_begin = 0,
            time_end = 0;

int photocellReading;
int photocellReadingPrev;// считываем аналоговые значения с делителя сенсора




void setup() {
 // pinMode(14, OUTPUT);
   Serial.begin(9600);
   pinMode(LEDpin, OUTPUT);
   digitalWrite(LEDpin, 1);
   pinMode(BtnSleep, OUTPUT);
   pinMode(19, INPUT);

   //pinMode(0, OUTPUT);
  
  // Все выходы программируем как OUTPUT
  for (int i = 0; i < 4; i++) {
    pinMode(anodPins[i], OUTPUT);
  }
  for (int i = 0; i < 8; i++) {
    pinMode(segmentsPins[i], OUTPUT);
  }
}

//{A, B, C, D, E, F, G,DP} - распиновка сегментов
int seg[10][8] = {
  {1, 1, 1, 1, 1, 1, 0, 0}, //Цифра 0
  {0, 1, 1, 0, 0, 0, 0, 0}, //Цифра 1
  {1, 1, 0, 1, 1, 0, 1, 0}, //Цифра 2
  {1, 1, 1, 1, 0, 0, 1, 0}, //Цифра 3
  {0, 1, 1, 0, 0, 1, 1, 0}, //Цифра 4
  {1, 0, 1, 1, 0, 1, 1, 0}, //Цифра 5
  {1, 0, 1, 1, 1, 1, 1, 0}, //Цифра 6
  {1, 1, 1, 0, 0, 0, 0, 0}, //Цифра 7
  {1, 1, 1, 1, 1, 1, 1, 0}, //Цифра 8
  {1, 1, 1, 1, 0, 1, 1, 0}  //Цифра 9
};

int t = 0;
int digid = 0;
int count = 0;
int num[4];
int currflag = 0;
int prevflag = 0;
unsigned long Time_start = 0;
unsigned long Time_end = 0;
unsigned long Time = 0;
int flag1 = 1;
int flag2 = 1;
int emptysignal = analogRead(photocellPin);
int last_sens_signal = 0;
int empty_signal = analogRead(photocellPin);
int sens_signal = 0;
int coin_flag = 0,
    sleep_flag = 0;
int recogn_flag = 0;

void Out(int count)
{
  int temp = count;
  for (int i = 0; i<4; i++)
  {
      num[i] = temp % 10;
      temp = temp / 10;
  } 

  for (int i = 0; i < 4; i++) { // Каждый разряд по очереди
    for (int k = 0; k < 8; k++) {// Каждый сегмент по очереди - исходя из заданной карты
      digitalWrite(segmentsPins[k], ((seg[num[3-i]][k] == 1) ? LOW : HIGH));
    }
    digitalWrite(anodPins[i], HIGH);
    delay(1); 
    digitalWrite(anodPins[i], LOW); 
  }
}

long int countIter = 0;
long int countPush1 = 0;
long int countPush2 = 0;

void loop() {
  int i = 0;

  photocellReading = analogRead(photocellPin);
  empty_signal = photocellReading;

  countIter++;
  

  /* if (photocellReading < 10)
   {
      if ( currflag == 0 &&  prevflag == 0) 
         {
          Time_start=micros();
            prevflag = 1;
           // count++;
          }
      else 
        if (prevflag == 1)  currflag = 0;
        else
        {
          currflag = 1;
        }
  }
    else 
    {
      currflag = 0;
      prevflag = 0;
      Time_end = micros();
    }*/

    

  /*  if (photocellReading < 1)
    {
        if (prevflag == 0)
        {
            count++;
            Time_start = millis();
            currflag = 1;
        }
        //currflag = 0;
        prevflag = 1;
        flag1 = 0;
    }
    else
    {
        //currflag = 0;
        prevflag = 0;
        if (currflag == 1) 
        {
          flag1 = 1;
          Time_end = millis(); //////////////////////////   прошлая прога
          currflag = 0;
        }
        else flag1 = 0;
    }
    
    if (flag1 == 1)
    {
        Time = Time_end - Time_start;
        if (Time > 1000000) count++;
        Console.println ("Hello World!");
        Time_end = 0;
        Time_start = 0;
    }*/


     //time_begin = micros();
    // if (abs(photocellReadingPrev-photocellReading) > 10 ) time_begin = micros();
    // else time_end = micros();


    //if( emptysignal - photocellReading >)
    // double time1 = time_end-time_begin;
   // Serial.println (photocellReading);


    last_sens_signal = empty_signal;
   /* Serial.println ( "Last = ");
     Serial.println (last_sens_signal);
     Serial.println ( "empty = ");
      Serial.println (empty_signal);*/
      //Serial.println ( "Read = ");
      //Serial.println (digitalRead(4));

      
    if (digitalRead(4) == HIGH || sleep_flag == 1){
      sleep_flag = 1;
    
    while (1) {
      countIter++;
      if (countIter > 20)
      {
        sens_signal = analogRead(photocellPin);  // далее такой же алгоритм, как при калибровке
        if (sens_signal < last_sens_signal) last_sens_signal = sens_signal;
        //Serial.println (last_sens_signal);
        if (countIter % 1000 == 0)
        {
           Serial.print ( "Last = ");
           Serial.println (last_sens_signal);
           Serial.print ( "sens = ");
           Serial.println (sens_signal);
           Serial.print ( "empty = ");
           Serial.println (empty_signal);
           Serial.print ( "coin_flag = ");
           Serial.println (coin_flag);
           Serial.println (" ");
        }
        if ((abs(empty_signal - sens_signal)) > 15) coin_flag = true;
        if (coin_flag && (abs(empty_signal - sens_signal)) < 14) 
        {
          int delta = abs(empty_signal - last_sens_signal); 
           Serial.print ( "Last_bala = ");
           Serial.println (last_sens_signal); 
           Serial.println (" ");
          if (delta >= 0 && delta <= 26)
          {
              count ++;
              
          }
		  else if (delta >= 106 && delta <= 126)
			{
				count += 2;
			}
			else if (delta >= 126 && delta <= 130)
				{
					count += 5;
				}
				else if (delta >= 36 && delta <= 96)
				{
					count += 10;
				}
          coin_flag = false;
          break;
        }
        //coin_flag = false;
        Out(count);
       // Serial.println (analogRead(19)); 
        if (flag1 == 1 && digitalRead(incBtn) == 0)
        {
          //count += 10 + 10* countPush1;
          count += 50;
          flag1 = 0;
          countPush1++;
        }
        else
        {
          if (flag1 == 0 && digitalRead(incBtn)==HIGH)
            flag1 = 1;
        }
  
         if (flag2 == 1 && digitalRead(decBtn)==LOW)
        {
         // count -= 10+ 10* countPush2;
          count -= 10;
          flag2 = 0;
          countPush2++;
        }
        else
        {
          if (flag2 == 0 && digitalRead(decBtn)==HIGH)
            flag2 = 1;
        }
  
        /*if (digitalRead(clearBtn)==LOW) 
        {
          count= 0;
          countPush1 = 0;
          countPush2 = 0;
        }*/
        
      }
      
    }
    
    }
    // if ( time1 >  100) 
   //  {
   //     count++;
   //     Serial.println (time1);
  //   }
    

    //currflag = 0;
    //prevflag = 0;

    
   // delay(4000);
    
   //num[0] = 9765 % 10;
  //if (photocellReading < 30) digid  = 0;
  //else digid = 3;
 // Serial.println(photocellReading);
//  photocellReading = photocellReading % 10; 
 // digid = photocellReading;
 // t += 1;
 // if (t > 9999) t = 0;
 // if ((t % 1000) == 0) {
 //   digid = t / 1000; //Каждую секунду отображаем цифры подряд
 // }
  // digid = num[0];

  //Out(count);

  /*int temp = count;
  for (int i = 0; i<4; i++)
  {
      num[i] = temp % 10;
      temp = temp / 10;
  } 

  for (int i = 0; i < 4; i++) { // Каждый разряд по очереди
    for (int k = 0; k < 8; k++) {// Каждый сегмент по очереди - исходя из заданной карты
      digitalWrite(segmentsPins[k], ((seg[num[3-i]][k] == 1) ? LOW : HIGH));
    }
    digitalWrite(anodPins[i], HIGH);
    delay(1); 
    digitalWrite(anodPins[i], LOW); 
  }
*/
}
