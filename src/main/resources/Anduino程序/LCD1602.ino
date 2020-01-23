String comdata ="";//接收的字符串
String temp = "";//存放临时字符串
int DI = 12; 
int RW = 11; 
int DB[] = {3, 4, 5, 6, 7, 8, 9, 10};//使用数组来定义总线需要的管脚 
int Enable = 2; 

void LcdCommandWrite(int value) {
  // 定义所有引脚 
  int i = 0; 
  for (i=DB[0]; i <= DI; i++) //总线赋值 
  { 
    digitalWrite(i,value & 01);//因为1602液晶信号识别是D7-D0(不是D0-D7)，这里是用来反转信号。 
    value >>= 1; 
  } 
  digitalWrite(Enable,LOW); 
  delayMicroseconds(1); 
  digitalWrite(Enable,HIGH); 
  delayMicroseconds(1); // 延时1ms 
  digitalWrite(Enable,LOW); 
  delayMicroseconds(1); // 延时1ms 
} 


void LcdDataWrite(int value) { 
  // 定义所有引脚 
  int i = 0; 
  digitalWrite(DI, HIGH); 
  digitalWrite(RW, LOW); 
  for (i=DB[0]; i <= DB[7]; i++) { 
    digitalWrite(i,value & 01); 
    value >>= 1; 
  } 
  digitalWrite(Enable,LOW); 
  delayMicroseconds(1); 
  digitalWrite(Enable,HIGH); 
  delayMicroseconds(1); 
  digitalWrite(Enable,LOW); 
  delayMicroseconds(1); // 延时1ms 
} 
  
void setup (void) { 
  Serial.begin(9600);//设置于电脑通信的波特率为9600每秒
  int i = 0; 
  for (i=Enable; i <= DI; i++) { 
    pinMode(i,OUTPUT); 
  } 
  delay(100); 
  // 短暂的停顿后初始化LCD 
  // 用于LCD控制需要 
  LcdCommandWrite(0x38); // 设置为8-bit接口，2行显示，5x7文字大小 
  delay(64); 
  LcdCommandWrite(0x38); // 设置为8-bit接口，2行显示，5x7文字大小 
  delay(50); 
  LcdCommandWrite(0x38); // 设置为8-bit接口，2行显示，5x7文字大小 
  delay(20); 
  LcdCommandWrite(0x06); // 输入方式设定 
  // 自动增量，没有显示移位 
  delay(20); 
  LcdCommandWrite(0x0E); // 显示设置 
  // 开启显示屏，光标显示，无闪烁 
  delay(20); 
  LcdCommandWrite(0x01); // 屏幕清空，光标位置归零 
  delay(100); 
  LcdCommandWrite(0x80); // 显示设置 
  // 开启显示屏，光标显示，无闪烁 
  delay(20); 
} 


void loop (void) {
    LcdCommandWrite(0x01); // 屏幕清空，光标位置归零 
    delay(10); 
    LcdCommandWrite(0x80+3); 
    delay(10); 
 // 读取粉丝数信息
 if(Serial.available() > 0){
    temp="";//如果java程序有数据传输过来就将temp清零
    comdata += char(Serial.read());
    temp+=comdata;
    delay(2);
 }else{
    comdata=temp;//如果java程序无数据传输过来，就将comdata设置为上次的数据
 }
  
  LcdDataWrite('F'); 
  LcdDataWrite('A'); 
  LcdDataWrite('N');
  LcdDataWrite('S'); 
  LcdDataWrite(':');     
  for(int i=0;i<comdata.length();i++){
      LcdDataWrite(comdata[i]); 
  }
  Serial.println("写入粉丝数据成功");
  delay(10); 
  LcdCommandWrite(0xc0+1); // 定义光标位置为第二行第二个位置 
  delay(10); 
  LcdDataWrite('W'); 
  LcdDataWrite('E'); 
  LcdDataWrite('C');
  LcdDataWrite('H'); 
  LcdDataWrite('A'); 
  LcdDataWrite('T'); 
  LcdDataWrite(':'); 
  LcdDataWrite('W'); 
  LcdDataWrite('E'); 
  LcdDataWrite('N'); 
  delay(200000); 
  comdata="";
}
