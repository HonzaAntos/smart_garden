#include <VirtualWire.h>
#include <UTFTGLUE.h>              
UTFTGLUE myGLCD(0,A2,A1,A3,A4,A0); 
#include <ArduinoJson.h>  
#include <SoftwareSerial.h> 
#include <math.h> 
SoftwareSerial espSerial (50,51);
#include <UTFT.h>
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <TouchScreen.h>
#define MINPRESSURE 200
#define MAXPRESSURE 10000

//-------dotyk---------
const int XP = 8, XM = A2, YP = A3, YM = 9; //ID=0x9341
const int TS_LEFT = 907, TS_RT = 136, TS_TOP = 942, TS_BOT = 139;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button on_btn, off_btn, sett_btn, add_btn, hlcl_btn, hlgr_btn, newmod_btn, dark_btn, light_btn ;

bool messageReady = false;
String serialMessage = "";

const int receive_pin = 17;
extern unsigned short TechCrow_logoText[];
extern unsigned short temperature[];
extern unsigned short humidity[];
extern unsigned short water_level[];
extern unsigned short battery[];

String message; 
String myString;
String str;

// sensors
double sensor1; 
float sensor1_cm;
float sensor2;
float sensor3;
float sensor4;
float data1; 
int data2; 
int data3; 
int data4; 
unsigned long wait = 0;

int pixel_x, pixel_y;     

int inc_to_send=0;

double arrayLevel[10];
int tmp = 0;
double newArray[10];

unsigned int actualWindow = 0;
bool darkMode = false;
bool lightMode = false;

double maxVal = arrayLevel[0];
double minVal = arrayLevel[0];

//ziskani bool hodnoty o stisku
bool Touch_getXY(void)
{
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);      
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   
    digitalWrite(XM, HIGH);
    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (pressed) {
        pixel_x = map(p.y, TS_LEFT, TS_RT, 0, 480);
        pixel_y = map(p.x, TS_TOP, TS_BOT, 0, 320);
    }
    return pressed;
}

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GREEN2  0x152C

void setup()
{
    Serial.begin(115200);
    espSerial.begin(115200);
    Serial.println("setup");
//nastaveni parametru pro radio prijem
    vw_set_rx_pin(receive_pin);
    vw_set_ptt_inverted(true);
    vw_setup(2000);  // Bits per sec
    vw_rx_start();   // zacatek prijimani
      
    randomSeed(analogRead(0));
  
// nastaveni parametru pro lcd shield
    myGLCD.InitLCD();
    myGLCD.clrScr();

    uint16_t ID = tft.readID();
    Serial.print("TFT ID = 0x");
    Serial.println(ID, HEX);
    if (ID == 0xD3D3) ID = 0x9486; // write-only shield
    tft.begin(ID);
    tft.setRotation(1);            //0 = PORTRAIT, 1 = LANDSCAPE
    tft.fillScreen(BLACK);
    switchWindow();
}

//vykresleni uvodni obrazovky
void drawHomeScreen(void)
{
  settParams();
  myGLCD.setBackColor(0,0,0); 
  myGLCD.setColor(45, 112, 138);
  myGLCD.fillRect(0, 0, 479, 20);
  myGLCD.setColor(45, 212, 138);
  myGLCD.fillRect(0, 20, 479, 40);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(45, 112, 138);
  
  myGLCD.setFont(BigFont);
  myGLCD.print("TECHCROWD - Smart Garden", CENTER, 1);
  myGLCD.setBackColor(45, 212, 138);
  myGLCD.print("YOU ARE IN MENU",CENTER, 20, 5);
  myGLCD.setColor(255, 0, 0); // nastaveni barvy na cervenou (R,G,B)
  myGLCD.drawLine(0,40,479,40); // nakresleni linky (x1,y1,x2,y2)
  myGLCD.setColor(255, 255, 255); 
  myGLCD.setFont(SmallFont); // nastaveni maleho fontu
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.print("www.techcrowd.cz", 20, 300); // vykresleni retezce
  myGLCD.setColor(16, 167, 103); 
  myGLCD.fillRoundRect (35, 90, 425, 130); // vykresleni zakulaceneho ctverce
  myGLCD.setColor(255, 255, 255); 
  myGLCD.drawRoundRect (35, 90, 425, 130); 
  myGLCD.setFont(BigFont); 
  myGLCD.setBackColor(16, 167, 103); 
  myGLCD.print("Pripojeni na WiFi", CENTER, 102); // vytisknuti retezce (x=stred,y=102px)

  //vykresleni bloku jako tlacitka (nastaveni, sensor)  
  myGLCD.setColor(16, 167, 103); 
  myGLCD.fillRoundRect (35, 190, 425, 230); 
  myGLCD.setColor(255, 255, 255); 
  myGLCD.drawRoundRect (35, 190, 425, 230); 
  myGLCD.setFont(BigFont); 
  myGLCD.setBackColor(16, 167, 103); 
  myGLCD.print("Nastaveni", CENTER, 202); 
  //vytvoreni tlacitek v oblasti vykreslenych bloku
    on_btn.initButton(&tft,  400, 280, 120, 60, WHITE, CYAN, BLACK, "sensor", 3);
    on_btn.drawButton(false);
    sett_btn.initButton(&tft, 230, 210, 390, 40, WHITE, GREEN2 , WHITE, "Nastaveni", 2);
    sett_btn.drawButton(false);
    light_btn.initButton(&tft, 1, 1, 1, 1, WHITE, CYAN, BLACK, "", 2);
    light_btn.drawButton(false);   
    
}
void loop()
{
    bool down = Touch_getXY();
    off_btn.press(down && off_btn.contains(pixel_x, pixel_y));
    on_btn.press(down && on_btn.contains(pixel_x, pixel_y));
    sett_btn.press(down && sett_btn.contains(pixel_x, pixel_y));
    add_btn.press(down && add_btn.contains(pixel_x, pixel_y));
    hlcl_btn.press(down && hlcl_btn.contains(pixel_x, pixel_y));
    hlgr_btn.press(down && hlgr_btn.contains(pixel_x, pixel_y));
    newmod_btn.press(down && newmod_btn.contains(pixel_x, pixel_y));
    dark_btn.press(down && dark_btn.contains(pixel_x, pixel_y));
    light_btn.press(down && light_btn.contains(pixel_x, pixel_y));
    //akce tlacitek po stisku         
    if (on_btn.justPressed()) {
        on_btn.drawButton(true);
        actualWindow = 1;
        myGLCD.clrScr();
        switchWindow();
    }
    if (off_btn.justPressed()) {
        off_btn.drawButton(true);
        actualWindow = 0;
        myGLCD.clrScr();
        switchWindow();
    }
    if (sett_btn.justPressed()) {
        sett_btn.drawButton(true);
        actualWindow = 5;
        myGLCD.clrScr();
        switchWindow();
    }
    if (add_btn.justPressed()) {
        add_btn.drawButton(true);
        actualWindow = 4;
        myGLCD.clrScr();
        switchWindow();
    }
    if (hlcl_btn.justPressed()) {
        hlcl_btn.drawButton(true);
        actualWindow = 1;
        myGLCD.clrScr();
        switchWindow();
    }   
    if (hlgr_btn.justPressed()) {
        hlgr_btn.drawButton(true);
        actualWindow = 2;
        myGLCD.clrScr();
        switchWindow();
    }
    if (newmod_btn.justPressed()) {
        newmod_btn.drawButton(true);
        actualWindow = 3;
        myGLCD.clrScr();
        newModule();
        switchWindow();
    }
      if (dark_btn.justPressed()) {
          dark_btn.drawButton(true);
          actualWindow = 0;
          myGLCD.clrScr();
          darkMode = true;  
          //lightMode = false;
          switchWindow();
      } 
    if (light_btn.justPressed()) {
        light_btn.drawButton(true);
        actualWindow = 0;
        myGLCD.clrScr();
        darkMode = false; 
        lightMode = true; 
        switchWindow();
    } 

    //vycitani prijateho retezce od modulu hladinomeru
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    
    if (vw_get_message(buf, &buflen)) 
    {
    int i;
    for (i = 0; i < buflen; i++)
    {
        char c = (buf[i]);
            message = message + c ; //vytvori retezec z prijatych znaku        
    }
    myString = message; 
    Serial.println(message);
  //rozdeleni retezce na jednotlive promenne pres funkci getValue() 
  String l = getValue(myString, ',', 0); // sensor1
  String m = getValue(myString, ',', 1); // sensor2
  String n = getValue(myString, ',', 2); // sensor3
  String o = getValue(myString, ',', 3); // sensor4

  //prekonvertujeme na pouzitelny format 
  data1 = l.toDouble();
  data2 = m.toInt();
  data3 = n.toInt();
  data4 = o.toInt();
  sensor1 = data1/100; 
  sensor2 = data2; 
  sensor3 = data3; 
  sensor4 = data4;
  //zobrazeni prijatych dat na seriovy monitor
  Serial.println("*********data************"); 
  Serial.println(sensor1);  
  Serial.println(sensor2);
  Serial.println(sensor3);
  Serial.println(sensor4);
  switchWindow();
//ukladani vysky hladiny do pole pro pozdejsi aplikaci
  for (tmp; tmp < 9;)
    {
    arrayLevel[tmp] = sensor1;
     
     Serial.println("pole s nactenymi hodnotami vysky hladiny: ");
     for (int i = 0; i < 9; i++)
     {
     Serial.print(arrayLevel[i]);
     if (arrayLevel[8] != NULL)//or null
     {
        arrayLevel[i] = arrayLevel[i+1];
        arrayLevel[8] = sensor1;
        Serial.print("###   ");
        Serial.print(arrayLevel[i]);
        Serial.println("      ");
      }
     }
     break;
    } 
     message = "";
     tmp ++;
     left(); 
    }
    //odesilani retezce prijatych dat do wifi modulu, pomoci seriove linky
      sensor1_cm=sensor1*100;
      str = String(sensor1_cm)+","+String(sensor2)+","+String(sensor3)+","+String(sensor4);
      //odesle data kazdych 5 sekund
      if(inc_to_send>10){
          espSerial.print(str);
          Serial.println(str);
          Serial.println("odesilani dat do WiFi modulu");
          inc_to_send = 0;
        }
       inc_to_send++;
      delay(500);
  }
  
//nastaveni rezimu zobrazeni
void settParams(void){
    if (darkMode == true && lightMode == false )
  {
    tft.fillScreen(BLACK);
    Serial.println("dark mode ON");
  }
    if (lightMode == true && darkMode == false) 
  {
    tft.fillScreen(WHITE);
    Serial.println("dark mode OFF");
  }
}
//prepinani mezi jednotlivymi obrazovkami 
void switchWindow (void){
     //switchCase pro prepinani mezi jednotlivymi okny 
  switch (actualWindow) {
    case 0:   
      Serial.println("switching to home");
      drawHomeScreen();
      break;
    case 1:   
      Serial.println("switching to classicWindow");
      classicWindow();
      break;
    case 2:   
      myGLCD.clrScr();
      Serial.println("switching to graph");
      graph();
      break;
    case 3:    
      Serial.println("switching to new module(s)");
      newModule();
      break;
    case 4:    
      Serial.println("switching to addModule");
      addModule();
      break;
    case 5:    
      Serial.println("switching to setting");
      setting();
      break;
  } 
}
//hledani minima a maxima vysky hladiny pro nasledny vypis do okna "graph"
void left (void) {
     Serial.print(".    ");
     if (arrayLevel[8] != NULL)//or null
     {
        for (int i = 0; i < 9; i++)
        {
          arrayLevel[i] = arrayLevel[i+1];
          arrayLevel[9] = sensor1;
          Serial.print("   ------>   ");
          Serial.print(arrayLevel[i]);
          Serial.println("      ");
        if (arrayLevel[i] > maxVal) {
         maxVal = arrayLevel[i];
          }
        if (arrayLevel[i] < minVal) {
         minVal = arrayLevel[i];
          }
      }
         Serial.print("absolutni maximum vysky hladiny: "); 
         Serial.println(maxVal);
         Serial.print("absolutni minimum vysky hladiny: "); 
         Serial.println(minVal);
     }
  }
//okno zobrazeni prijatych dat 
 void classicWindow (void){
  settParams();
  myGLCD.setFont(BigFont);
  myGLCD.setColor(45, 112, 138);
  myGLCD.fillRect(0, 0, 479, 20);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(45, 112, 138);
  myGLCD.print("TECHCROWD - Smart Garden", CENTER, 1);
  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRoundRect(7, 27, 203, 303);
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRoundRect(10, 30, 200, 300);
  //vykresleni bitmap
  myGLCD.drawBitmap(30, 90, 38, 38, water_level);
  myGLCD.drawBitmap(30, 150, 38, 38, battery);
  myGLCD.drawBitmap(30, 200, 35, 38, temperature);
  myGLCD.drawBitmap(30, 250, 38, 38, humidity);
  //vykresleni namerenych dat 
  myGLCD.setColor(0, 0, 0);
  myGLCD.setBackColor(255, 255, 255);
  myGLCD.print("Hladinomer", 30, 50 );
  myGLCD.printNumF(sensor1, 2, 90, 115);
  myGLCD.print(" m", 167, 115);
  myGLCD.printNumI(sensor2, 90, 165);
  myGLCD.print(" %", 120, 165);
  myGLCD.printNumI(sensor3, 90, 215);
  myGLCD.print(" °C", 120, 215);
  myGLCD.printNumI(sensor4, 90, 265);
  myGLCD.print(" %", 120, 265);
  //zobrazeni a inicializace tlacitek
    myGLCD.setColor(255, 0, 0);
    myGLCD.fillRoundRect(400, 30, 460, 90);
    myGLCD.setColor(255, 255, 255);
    myGLCD.fillRoundRect(405, 35, 455, 85);
    myGLCD.setColor(255, 0, 0);
    add_btn.initButton(&tft, 430, 60, 50, 50, WHITE, (17, 86, 125), WHITE, "ADD", 2);
    on_btn.initButton(&tft, 1, 1, 1, 1, WHITE, (17, 86, 125), WHITE, "", 2);
    sett_btn.initButton(&tft, 1, 1, 1, 1, WHITE, (17, 86, 125), WHITE, "", 2);
    hlcl_btn.initButton(&tft, 1, 1, 1, 1, WHITE, (17, 86, 125), WHITE, "", 2);
    hlgr_btn.initButton(&tft, 1, 1, 1, 1, WHITE, (17, 86, 125), WHITE, "", 2);
    newmod_btn.initButton(&tft, 1, 1, 1, 1, WHITE, (17, 86, 125), WHITE, "", 2);
    dark_btn.initButton(&tft, 1, 1, 1, 1, WHITE, (17, 86, 125), WHITE, "", 2);
    off_btn.initButton(&tft, 430, 220, 60, 60, WHITE, CYAN, BLACK, "menu", 2);
    light_btn.initButton(&tft, 1, 1, 1, 1, WHITE, CYAN, BLACK, "", 2);    
    
    light_btn.drawButton(false); 
    add_btn.drawButton(false);
    on_btn.drawButton(false);
    sett_btn.drawButton(false);
    hlcl_btn.drawButton(false);
    hlgr_btn.drawButton(false);
    dark_btn.drawButton(false);
    newmod_btn.drawButton(false);
    off_btn.drawButton(false);
     }

//zobrazeni okna nabídky zobrazeni 
void addModule (void) {
  settParams();
  myGLCD.setFont(BigFont);
  myGLCD.setColor(51, 51, 51);
  myGLCD.fillRect(0, 20, 479, 360);
  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRoundRect(7, 27, 313, 293);
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRoundRect(10, 30, 310, 290);
  myGLCD.setColor(0, 0, 0);
  myGLCD.setBackColor(255, 255, 255);
  myGLCD.print("Vyberte: ", 30, 40 );
  myGLCD.setColor(45, 112, 138);
  myGLCD.fillRect(0, 0, 479, 20);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(45, 112, 138);
  myGLCD.print("TECHCROWD - Smart Garden", CENTER, 1);

  //zobrazeni a inicializace tlacitek
    hlcl_btn.initButton(&tft, 150, 100, 220, 50, BLACK, CYAN, BLACK, "Classic", 2);
    hlgr_btn.initButton(&tft, 150, 170, 220, 50, RED, CYAN, BLACK, "Graph", 2);
    newmod_btn.initButton(&tft, 150, 240, 220, 50, BLUE, CYAN, BLACK, "New module(s)", 2);
    add_btn.initButton(&tft, 430, 1, 1, 1, 1, WHITE, (17, 86, 125), WHITE, "", 2);
    on_btn.initButton(&tft, 1, 1, 1, 1, WHITE, (17, 86, 125), WHITE, "", 2);
    sett_btn.initButton(&tft, 1, 1, 1, 1, WHITE, (17, 86, 125), WHITE, "", 2);
    dark_btn.initButton(&tft, 1, 1, 1, 1, WHITE, (17, 86, 125), WHITE, "", 2);
    off_btn.initButton(&tft, 430, 180, 60, 60, WHITE, CYAN, BLACK, "menu", 2);
    light_btn.initButton(&tft, 1, 1, 1, 1, WHITE, CYAN, BLACK, "", 2);

    light_btn.drawButton(false);         
    add_btn.drawButton(false);
    on_btn.drawButton(false);
    sett_btn.drawButton(false);
    dark_btn.drawButton(false);
    off_btn.drawButton(false);    
    hlcl_btn.drawButton(false);
    hlgr_btn.drawButton(false);
    newmod_btn.drawButton(false);
  }

//obrazovka nastaveni   
void setting (void) {
      settParams();
      myGLCD.setFont(BigFont);
      myGLCD.setColor(45, 112, 138);
      myGLCD.fillRect(0, 0, 479, 20);
      myGLCD.setColor(45, 212, 138);
      myGLCD.fillRect(0, 20, 479, 40);     
      myGLCD.setColor(255, 255, 255);
      myGLCD.setBackColor(45, 112, 138);
      myGLCD.print("TECHCROWD - Smart Garden", CENTER, 1);
      myGLCD.setBackColor(45, 212, 138);
      myGLCD.print("YOU ARE IN SETTING ",CENTER, 20, 5);
      myGLCD.setColor(0, 0, 0);
      myGLCD.fillRoundRect(15, 65, 265, 295);
      myGLCD.setColor(126, 126, 126);
      myGLCD.fillRoundRect(20, 70, 260, 290);
      myGLCD.setColor(0, 0, 0);
      myGLCD.setBackColor(126,126,126);
      myGLCD.print("Choose mode: ", 40, 75);
  //zobrazeni a inicializace tlacitek
    hlcl_btn.initButton(&tft,  1, 1, 1, 1, BLACK, CYAN, BLACK, "", 2);
    hlgr_btn.initButton(&tft,  1, 1, 1, 1, RED, CYAN, BLACK, "", 2);
    newmod_btn.initButton(&tft,  1, 1, 1, 1, BLUE, CYAN, BLACK, "", 2);
    add_btn.initButton(&tft, 1, 1, 1, 1, WHITE, (17, 86, 125), WHITE, "", 2);
    on_btn.initButton(&tft, 1, 1, 1, 1, WHITE, (17, 86, 125), WHITE, "", 2);
    sett_btn.initButton(&tft, 1, 1, 1, 1, WHITE, (17, 86, 125), WHITE, "", 2);
    dark_btn.initButton(&tft, 200, 160, 90, 90, WHITE, BLACK, WHITE, "Dark", 2);
    off_btn.initButton(&tft, 430, 180, 60, 60, WHITE, CYAN, BLACK, "menu", 2);
    light_btn.initButton(&tft, 80, 160, 90, 90, WHITE, WHITE, BLACK, "Light", 2);
        
    add_btn.drawButton(false);
    on_btn.drawButton(false);
    sett_btn.drawButton(false);
    dark_btn.drawButton(false);
    off_btn.drawButton(false);    
    hlcl_btn.drawButton(false);
    hlgr_btn.drawButton(false);
    newmod_btn.drawButton(false);
    light_btn.drawButton(false);
  }
//okno se zobrazenym grafem prubehu vysky hladiny
void graph (void) {
      settParams();
      myGLCD.setFont(BigFont);
      myGLCD.setColor(45, 112, 138);
      myGLCD.fillRect(0, 0, 479, 20);
      myGLCD.setColor(45, 212, 138);
      myGLCD.fillRect(0, 20, 479, 40); 
      myGLCD.setColor(255, 255, 255);
      myGLCD.setBackColor(45, 112, 138);
      myGLCD.print("TECHCROWD - Smart Garden", CENTER, 1);
      myGLCD.setBackColor(45, 212, 138);
      myGLCD.print("YOU ARE IN GRAPH",CENTER, 20, 5);
      myGLCD.setColor(255, 0, 0);
      myGLCD.fillRoundRect(400, 50, 460, 110);
      myGLCD.setColor(255, 255, 255);
      myGLCD.fillRoundRect(405, 55, 455, 105);
      myGLCD.setColor(255, 255, 255);
      myGLCD.fillRoundRect(10, 60, 85, 315);
      myGLCD.setBackColor(255, 255, 255);
      //tabulka 
      for (int i = 0; i < 9; i++)
      {
      myGLCD.setColor(255, 0, 0);
      myGLCD.drawRoundRect(9,59,86,316); 
      myGLCD.setFont(SmallFont);
      myGLCD.print("ID", 12, 70 );  
      myGLCD.print("vyska", 41, 70 );  
      myGLCD.setColor(0, 0, 0); 
      myGLCD.printNumI(arrayLevel[i],40 ,(295-25*i));
      myGLCD.printNumI((9-i),13 ,(295-25*i));
      myGLCD.setColor(128, 128, 128); 
      myGLCD.drawLine(10,(90+25*i),85,(90+25*i));
      }
      myGLCD.drawLine(30, 60, 30, 315);
      //graf
      myGLCD.drawLine(100, 300, 360, 300);
      myGLCD.drawLine(100, 100, 100, 300);
      myGLCD.setColor(0,255,0);
      for (int i = 0; i < 9; i++)
      {
        myGLCD.setColor(255, 0, 0);
        myGLCD.drawLine((100+i*33), 295, (100+i*33), 305); //x
        myGLCD.drawLine(95,(100+i*25),105 ,(100+i*25));  //y
        if (arrayLevel[8] != NULL){
        myGLCD.setColor(0, 0, 255);
        myGLCD.fillCircle((100+i*33),round(300-(500/200)*arrayLevel[i]),3);
        }
        if(i>=1){
          myGLCD.drawLine((100+(i-1)*33),round(300-(500/200)*arrayLevel[i-1]), (100+i*33), round(300-(500/200)*arrayLevel[i]));//bod1(x,y);bod2(x,y)
          }
        myGLCD.setColor(0, 0, 0);
        myGLCD.printNumI(maxVal,100,95);
        myGLCD.printNumI(minVal,100,305);
      }
  //zobrazeni a inicializace tlacitek
    hlcl_btn.initButton(&tft,  1, 1, 1, 1, BLACK, CYAN, BLACK, "", 2);
    hlgr_btn.initButton(&tft,  1, 1, 1, 1, RED, CYAN, BLACK, "", 2);
    newmod_btn.initButton(&tft,  1, 1, 1, 1, BLUE, CYAN, BLACK, "", 2);
    add_btn.initButton(&tft, 430, 80, 50, 50, WHITE, (17, 86, 125), WHITE, "ADD", 2);
    on_btn.initButton(&tft, 1, 1, 1, 1, WHITE, (17, 86, 125), WHITE, "", 2);
    sett_btn.initButton(&tft, 1, 1, 1, 1, WHITE, (17, 86, 125), WHITE, "", 2);
    dark_btn.initButton(&tft, 1, 1, 1, 1, WHITE, GREEN, BLACK, "", 2);
    off_btn.initButton(&tft, 430, 180, 60, 60, WHITE, CYAN, BLACK, "menu", 2);
    light_btn.initButton(&tft, 1, 1, 1, 1, WHITE, CYAN, BLACK, "", 2); 

    light_btn.drawButton(false);
    add_btn.drawButton(false);
    on_btn.drawButton(false);
    sett_btn.drawButton(false);
    dark_btn.drawButton(false);
    off_btn.drawButton(false);    
    hlcl_btn.drawButton(false);
    hlgr_btn.drawButton(false);
    newmod_btn.drawButton(false);

  }
//zobrazeni okna new module, ktery je zde pripraven pro dalsi zakomponovani noveho modulu  
void newModule (void) {
    settParams();
    myGLCD.setFont(BigFont);
    myGLCD.setColor(45, 112, 138);
    myGLCD.fillRect(0, 0, 479, 20);
    myGLCD.setColor(45, 212, 138);
    myGLCD.fillRect(0, 20, 479, 40); 
    myGLCD.setColor(255, 255, 255);
    myGLCD.setBackColor(45, 112, 138);
    myGLCD.print("TECHCROWD - Smart Garden", CENTER, 1);
    myGLCD.setBackColor(45, 212, 138);
    myGLCD.print("YOU ARE IN NEW MODULE(S)",CENTER, 20, 5);
    myGLCD.setColor(255, 255, 255);
    myGLCD.fillRoundRect(30, 60, 360, 150);
    myGLCD.setColor(0, 0, 0); 
    myGLCD.setFont(SmallFont);
    myGLCD.setBackColor(255, 255, 255);
    myGLCD.print("This option is not activated right now.", 50, 80 );  
    myGLCD.print("Please wait till next update.", 50, 110 ); 
    myGLCD.setColor(255, 0, 0);
    myGLCD.fillRoundRect(400, 50, 460, 110);
    myGLCD.setColor(255, 255, 255);
    myGLCD.fillRoundRect(405, 55, 455, 105);
    myGLCD.setColor(255, 255, 255);
  //zobrazeni a inicializace tlacitek
    hlcl_btn.initButton(&tft,  1, 1, 1, 1, BLACK, CYAN, BLACK, "", 2);
    hlgr_btn.initButton(&tft,  1, 1, 1, 1, RED, CYAN, BLACK, "", 2);
    newmod_btn.initButton(&tft,  1, 1, 1, 1, BLUE, CYAN, BLACK, "", 2);
    add_btn.initButton(&tft, 430, 80, 50, 50, WHITE, (17, 86, 125), WHITE, "ADD", 2);
    on_btn.initButton(&tft, 1, 1, 1, 1, WHITE, (17, 86, 125), WHITE, "", 2);
    sett_btn.initButton(&tft, 1, 1, 1, 1, WHITE, (17, 86, 125), WHITE, "", 2);
    dark_btn.initButton(&tft, 1, 1, 1, 1, WHITE, GREEN, BLACK, "", 2);
    off_btn.initButton(&tft, 430, 180, 60, 60, WHITE, CYAN, BLACK, "menu", 2);
    light_btn.initButton(&tft, 1, 1, 1, 1, WHITE, CYAN, BLACK, "", 2);   
     
    light_btn.drawButton(false);     
    add_btn.drawButton(false);
    on_btn.drawButton(false);
    sett_btn.drawButton(false);
    dark_btn.drawButton(false);
    off_btn.drawButton(false);    
    hlcl_btn.drawButton(false);
    hlgr_btn.drawButton(false);
    newmod_btn.drawButton(false);
  }

//funkce pro ziskani dat z retezce pomoci oddelovaciho znaku
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;
 
    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
