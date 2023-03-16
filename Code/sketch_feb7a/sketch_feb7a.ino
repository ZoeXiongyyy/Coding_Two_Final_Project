 // Code to send and receive data from openFrameworks
bool buttonState1 = 0;//Switch off
bool buttonState2 = 0;//Switch off
int ledPin1 = 13;
int ledPin2 = 12;
int buttonPin1 = 2;
int buttonPin2 = 3;

int potpin=A0;//定义模拟接口0
int ledpin=11;//定义数字接口11（PWM 输出）
int val= 0;// 暂存来自传感器的变量数值

void setup() {
  // Start the serial communication
  Serial.begin(9600);
  pinMode(ledPin1, OUTPUT);  // Declaring the LED pin as output
  pinMode(ledPin2, OUTPUT); 
  pinMode(ledpin,OUTPUT);//定义数字接口11 为输出
  pinMode(buttonPin1,INPUT);
  pinMode(buttonPin2,INPUT);
}

void loop() {
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);

  val=analogRead(potpin);

  if (Serial.available() > 0) { // If there is any data available
    analogWrite(ledpin,val/4);
    if((val/4) >-1){
      Serial.write(val/4);
      //delay(300);
    }
      //inByte = Serial.read(); // store the incoming data
    if(buttonState1 == HIGH) {  // Whether the received data is '1'
      digitalWrite(ledPin1, HIGH); // Change the LED state
      Serial.write(1);
      //delay(300);
      // Turn the LED
    }else{
      digitalWrite(ledPin1, LOW);
      //Serial.write(buttonState1);
      //Serial.write(0);
     // delay(300);
    }
     if(buttonState2 == HIGH) {  // Whether the received data is '1'
      digitalWrite(ledPin2, HIGH); // Change the LED state
      Serial.write(2);
      //delay(300);
      // Turn the LED
    }else{
      digitalWrite(ledPin2, LOW);
      //Serial.write(buttonState2);
     // Serial.write(0);
      //delay(300);
    }
  }
  //delay(300);
  //Serial.write(buttonState);
}
