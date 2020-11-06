#include <M5Atom.h>
#include <BleKeyboard.h>
// bt remote control page-down/up
BleKeyboard bleKeyboard("M5AtomPrintScreen");
int oldX, oldY;
boolean smart = false;
//key code
int up = KEY_UP_ARROW ;//有问题
int down = KEY_DOWN_ARROW ;
int left = KEY_LEFT_ARROW ;
int right = KEY_RIGHT_ARROW ;
//上下翻页 KEY_PAGE_UP  KEY_PAGE_DOWN 

void setup() {
  M5.begin(true,false,true);
  bleKeyboard.begin();
  M5.IMU.Init();
  oldX = -1;
  oldY = -1;
}

void loop() {
  float accX, accY, accZ;
  int x, y;
  M5.Btn.read();

  M5.IMU.getAccelData(&accX, &accY, &accZ);
  x = constrain(accX * 5 + 2, 0, 4);
  y = constrain(accY * 5 + 2, 0, 4);
  Serial.print("x=");
  Serial.print(x);
  Serial.print(" y=");
  Serial.println(y);
  if (oldX != x || oldY != y) {
    M5.dis.drawpix(oldX, oldY, 0x000000);
    M5.dis.drawpix(x, y, 0xffffff);
    oldX = x;
    oldY = y;
  }

  if(M5.Btn.isPressed()){
    Serial.println("butt Pressed");  
    //配准

    //切换键位模式

    //灵敏度
    smart=!smart;
    Serial.print("smart=");
    Serial.println(smart);
  }

  if(bleKeyboard.isConnected()){
      M5.dis.drawpix(0,0x0000ff);

      if(x==0){
        bleKeyboard.write(up);  
        bleKeyboard.write(up);  
      } 
      if(x==1 and smart){
        bleKeyboard.write(up); 
      }   
//    down 
      if(x==3 and smart){
        bleKeyboard.write(down);  
      }   
      if(x==4){
        bleKeyboard.write(down);  
        bleKeyboard.write(down);   
      }
//    left
      if(y==0){
        bleKeyboard.write(left);  
        bleKeyboard.write(left);  
      } 
      if(y==1 and smart){
        bleKeyboard.write(left);    
      }
//    right 
      if(y==3 and smart){
        bleKeyboard.write(right);
      }     
      if(y==4){
        bleKeyboard.write(right);  
        bleKeyboard.write(right);
      } 
      delay(250);
//    }
  }
  else{
    M5.dis.drawpix(0,0x00ff00);
  }
  delay(100);
}
