
#include <Keypad.h>
#include <Servo.h>

#define codeLength 4
Servo myservo;
char code[codeLength];
char passW[codeLength]="123";
byte keycount=0;

const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS]={9,8,7};
byte colPins[COLS]={5,4,3};

Keypad customKeypad=Keypad(makeKeymap(hexaKeys),rowPins, colPins, ROWS ,COLS); 
void setup()
{
  Serial.begin(9600);
  //pinMode(LED_BUILTIN, OUTPUT);
  myservo.attach(10);
}

void loop()
{
  //digitalWrite(LED_BUILTIN, HIGH);
  //delay(1000); // Wait for 1000 millisecond(s)
  //digitalWrite(LED_BUILTIN, LOW);
  //delay(1000); // Wait for 1000 millisecond(s)
  char customKey=customKeypad.getKey();
  if(customKey){
    //Serial.println(customKey);
    code[keycount]=customKey;
    Serial.print(code[keycount]);
    keycount++;
  }
  if(keycount==codeLength-1){
    Serial.println(" ");
    if(!strcmp(code,passW)){
      Serial.println("Correct");
      myservo.write(80);//unlock
      delay(20);
    }
    else{
    Serial.println("Incorrect");
      myservo.write(10);//lock
      delay(20);
    }
    deletecount();
  }
}
void deletecount()
{
  while(keycount!=0)
    code[keycount--]=0;
  return;
}
