/*
  Project:     ArduBook OS (For Arduino Uno R3)
               Powered by Open-ArduBook Project.
  Author:      SRInternet
  Date:        2025-12
  License:     MIT
  Description: An E-book reader system for Arduino Uno R3 with GB2312 support.
  Repo:        github.com/SRInternet/Open-ArduBook
*/

#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>

// ================= Logo =================
const unsigned char logo_bmp [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 
  0x0c, 0x00, 0x1f, 0xc0, 0x00, 0x00, 0x30, 0x00, 0x1f, 0x80, 0x7c, 0x00, 0x01, 0xc0, 0x00, 0x0c, 
  0x00, 0x1f, 0xe0, 0x00, 0x00, 0x30, 0x00, 0x3f, 0xe0, 0xfe, 0x00, 0x01, 0xe0, 0x00, 0x0c, 0x00, 
  0x1c, 0x60, 0x00, 0x00, 0x30, 0x00, 0x70, 0x71, 0xc6, 0x00, 0x03, 0xe1, 0xb0, 0xec, 0xc3, 0x1c, 
  0x60, 0xe0, 0x1c, 0x31, 0x80, 0xe0, 0x31, 0x80, 0x00, 0x03, 0x61, 0xf3, 0xfc, 0xc3, 0x1c, 0xe1, 
  0xf8, 0x7e, 0x37, 0x80, 0xc0, 0x31, 0xc0, 0x00, 0x07, 0x71, 0xe7, 0x1c, 0xc3, 0x1f, 0xe3, 0x0c, 
  0xc3, 0x3e, 0x00, 0xc0, 0x38, 0xfc, 0x00, 0x07, 0x31, 0x86, 0x0c, 0xc3, 0x1f, 0xe6, 0x07, 0x81, 
  0xbc, 0x00, 0xc0, 0x38, 0x7e, 0x00, 0x07, 0xf9, 0x86, 0x0c, 0xc3, 0x1c, 0x76, 0x03, 0x19, 0xb8, 
  0x00, 0xc0, 0x38, 0x07, 0x00, 0x0f, 0xf9, 0x86, 0x0c, 0xc3, 0x1c, 0x36, 0x63, 0x19, 0xbc, 0x00, 
  0xe0, 0x30, 0x03, 0x00, 0x0c, 0x19, 0x86, 0x0c, 0xc3, 0x1c, 0x76, 0x07, 0x81, 0xbe, 0x00, 0x70, 
  0x71, 0x87, 0x00, 0x0c, 0x1d, 0x87, 0xbc, 0x7f, 0x1f, 0xe3, 0x0c, 0xc3, 0x37, 0x00, 0x3f, 0xe1, 
  0xfe, 0x00, 0x1c, 0x0d, 0x83, 0xfc, 0x7e, 0x1f, 0xc1, 0xf8, 0x7e, 0x33, 0x80, 0x1f, 0xc0, 0xfe, 
  0x00, 0x00, 0x00, 0x00, 0x40, 0x18, 0x00, 0x00, 0xe0, 0x1c, 0x00, 0x00, 0x02, 0x00, 0x10, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// ================= 硬件 =================
const int XP=6, XM=A2, YP=A1, YM=7; 
const int TS_LEFT=909, TS_RT=252, TS_TOP=382, TS_BOT=759;
#define SD_CS 10
MCUFRIEND_kbv tft;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// ================= 参数 =================
#define BLACK   0x0000
#define WHITE   0xFFFF
#define GREY    0x5AEB
#define DARKGREY 0x2104 
#define NAVY    0x000F
#define RED     0xF800
#define YELLOW  0xFFE0

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define HEADER_HEIGHT 28    
#define FOOTER_HEIGHT 30   
#define TEXT_TOP_MARGIN 32 
#define TEXT_BOTTOM_LIMIT 205
#define LINE_HEIGHT 24      
#define ENG_CHAR_WIDTH 12   
#define CN_CHAR_WIDTH 16    
#define FILE_BTN_HEIGHT 25
#define MAX_FILES_ON_SCREEN 6 

#define HISTORY_SIZE 50
#define SAVE_VERSION 0x53 

enum AppState { STATE_MENU, STATE_READING, STATE_SETTINGS };
AppState currentState = STATE_MENU;

File root;
File myBook;
File myFont;

unsigned long pageHistory[HISTORY_SIZE]; 
int historyIndex = 0;          
int pageNum = 1;
char currentBookName[13]; 
char lastReadBook[13]; 

// ================= 初始化 =================
void setup() {
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(1); 
  
  pinMode(SD_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH);

  showSplashScreen();
  
  // 注意：全局必须使用 F() 宏节省 RAM
  if (!SD.begin(SD_CS)) showError(F("SD Fail!"));
  if (!SD.exists("HZK16")) showError(F("No HZK16!"));

  loadSystemConfig();
  delay(2000); 
  drawFileList();
}

void drawBitmapScaled(int x, int y, const uint8_t *bitmap, int w, int h, uint16_t color, int scale) {
  int byteWidth = (w + 7) / 8;
  for (int j = 0; j < h; j++) {
    for (int i = 0; i < w; i++) {
      if (pgm_read_byte(bitmap + j * byteWidth + i / 8) & (128 >> (i & 7))) {
        tft.fillRect(x + i * scale, y + j * scale, scale, scale, color);
      }
    }
  }
}

void centerPrint(const __FlashStringHelper *text, int y, int size) {
  tft.setTextSize(size);
  String s = String(text);
  int len = s.length() * 6 * size;
  tft.setCursor((SCREEN_WIDTH - len) / 2, y);
  tft.print(s);
}

// 兼容普通 char* 的重载
void centerPrint(const char* text, int y, int size) {
  tft.setTextSize(size);
  int len = strlen(text) * 6 * size;
  tft.setCursor((SCREEN_WIDTH - len) / 2, y);
  tft.print(text);
}

void showError(const __FlashStringHelper *msg) {
  tft.fillScreen(BLACK);
  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.setCursor(10, 100);
  tft.print(F("ERR: ")); tft.print(msg);
  while(1);
}

void showSplashScreen() {
  tft.fillScreen(BLACK);
  int scale = 2;
  int logoW = 116 * scale;
  int logoH = 22 * scale;
  int logoX = (SCREEN_WIDTH - logoW) / 2;
  int logoY = 60; 
  drawBitmapScaled(logoX, logoY, logo_bmp, 116, 22, WHITE, scale);
  
  tft.setTextSize(1);
  tft.setTextColor(YELLOW); 
  centerPrint(F("Tiny Core, Infinite World"), logoY + logoH + 20, 1);
  
  tft.setTextColor(GREY);
  centerPrint(F("v1.0 - github.com/SRInternet/Open-ArduBook"), SCREEN_HEIGHT - 20, 1);
}

// ================= 主循环 =================
void loop() {
  TSPoint p = ts.getPoint();
  pinMode(XM, OUTPUT); pinMode(YP, OUTPUT);

  if (p.z > 20) { 
    int x = map(p.y, TS_TOP, TS_BOT, 0, tft.width()); 
    int y = map(p.x, TS_RT, TS_LEFT, 0, tft.height());
    delay(150); 
    
    if (currentState == STATE_MENU) handleMenuClick(x, y);
    else if (currentState == STATE_READING) handleReadingClick(x, y);
    else if (currentState == STATE_SETTINGS) handleSettingsClick(x, y);
    
    while(ts.getPoint().z > 10) {}; 
  }
}

// ================= 配置系统 =================
void saveSystemConfig() {
  if (SD.exists("SYS.CFG")) SD.remove("SYS.CFG");
  File cfg = SD.open("SYS.CFG", FILE_WRITE);
  if (cfg) {
    cfg.write((uint8_t*)currentBookName, 13);
    cfg.close();
    strcpy(lastReadBook, currentBookName); 
  }
}

void loadSystemConfig() {
  lastReadBook[0] = 0; 
  if (SD.exists("SYS.CFG")) {
    File cfg = SD.open("SYS.CFG");
    if (cfg) {
      cfg.read((uint8_t*)lastReadBook, 13);
      cfg.close();
    }
  }
}

// ================= 书签逻辑 =================
void saveBookmark() {
  char saveName[13]; 
  strcpy(saveName, currentBookName);
  char* dot = strrchr(saveName, '.');
  if (dot) *dot = 0; 
  strcat(saveName, ".SAV");
  if (SD.exists(saveName)) SD.remove(saveName);
  
  File saveFile = SD.open(saveName, FILE_WRITE);
  if (saveFile) {
    saveFile.write((uint8_t)SAVE_VERSION);
    saveFile.write((uint8_t*)&pageNum, 2);
    uint8_t hIdx = (uint8_t)historyIndex;
    saveFile.write(&hIdx, 1);
    for(int i=0; i<=historyIndex; i++) saveFile.write((uint8_t*)&pageHistory[i], 4);
    saveFile.close();
  }
  saveSystemConfig();
}

bool loadBookmark() {
  char saveName[13];
  strcpy(saveName, currentBookName);
  char* dot = strrchr(saveName, '.');
  if (dot) *dot = 0; 
  strcat(saveName, ".SAV");
  
  if (SD.exists(saveName)) {
    File saveFile = SD.open(saveName);
    if (saveFile) {
      uint8_t ver = 0;
      if (saveFile.read(&ver, 1) != 1 || ver != SAVE_VERSION) {
        saveFile.close(); return false; 
      }
      saveFile.read((uint8_t*)&pageNum, 2);
      uint8_t hIdx = 0;
      saveFile.read(&hIdx, 1);
      historyIndex = hIdx;
      if (historyIndex >= HISTORY_SIZE) historyIndex = HISTORY_SIZE - 1;
      for(int i=0; i<=historyIndex; i++) saveFile.read((uint8_t*)&pageHistory[i], 4);
      saveFile.close();
      
      unsigned long currentPos = pageHistory[historyIndex];
      if (currentPos < myBook.size()) {
        myBook.seek(currentPos);
        tft.fillScreen(BLACK);
        centerPrint(F("Restoring..."), 100, 2);
        delay(800);
        return true;
      }
    }
  }
  return false; 
}

void clearAllHistory() {
  tft.fillScreen(BLACK);
  centerPrint(F("Deleting History..."), 100, 2);
  
  root = SD.open("/");
  while(true) {
    File entry = root.openNextFile();
    if (! entry) break;
    if (!entry.isDirectory()) {
      char* fname = entry.name();
      if (strstr(fname, ".SAV") || strstr(fname, "SYS.CFG")) {
         SD.remove(fname);
      }
    }
    entry.close();
  }
  root.close();
  
  lastReadBook[0] = 0; 
  delay(1000);
  drawFileList();
}

// ================= 设置界面 =================
void drawSettings() {
  currentState = STATE_SETTINGS;
  tft.fillScreen(BLACK);
  
  tft.fillRect(0, 0, SCREEN_WIDTH, 30, NAVY);
  tft.setTextColor(WHITE); tft.setTextSize(2);
  tft.setCursor(10, 8); tft.print(F("Settings"));

  // Clear History (13 char -> 156px -> X=82)
  tft.drawRect(40, 60, 240, 40, RED);
  tft.setCursor(82, 72); tft.setTextColor(RED);
  tft.print(F("Clear History"));

  // About (5 char -> 60px -> X=130)
  tft.drawRect(40, 120, 240, 40, WHITE);
  tft.setCursor(130, 132); tft.setTextColor(WHITE);
  tft.print(F("About"));

  // Back (4 char -> 48px -> X=136)
  tft.drawRect(40, 180, 240, 40, GREY);
  tft.setCursor(136, 192); tft.setTextColor(GREY);
  tft.print(F("Back"));
}

void handleSettingsClick(int x, int y) {
  if (y > 60 && y < 100) {
    clearAllHistory();
  }
  else if (y > 120 && y < 160) {
    showSplashScreen(); 
    delay(2000);
    drawSettings(); 
  }
  else if (y > 180 && y < 220) {
    drawFileList();
  }
}

// ================= 文件菜单 =================
void drawFileList() {
  currentState = STATE_MENU;
  tft.fillScreen(BLACK);
  tft.fillRect(0, 0, SCREEN_WIDTH, 30, NAVY);
  tft.setTextColor(WHITE); tft.setTextSize(2);
  tft.setCursor(10, 8); tft.print(F("My Library"));

  // 此时 myFont 必须是关闭的！
  root = SD.open("/");
  if (!root) showError(F("SD Open Fail"));

  int yPos = 35; int fileCount = 0;
  while(true) {
    File entry = root.openNextFile();
    if (! entry) break;
    if (entry.isDirectory()) { entry.close(); continue; }
    
    char* fname = entry.name();
    if ((strstr(fname, ".TXT") || strstr(fname, ".txt")) && !strstr(fname, ".SAV")) {
      tft.drawRect(10, yPos, 300, FILE_BTN_HEIGHT, GREY);
      tft.setCursor(20, yPos + 5);
      tft.setTextSize(2); 
      
      if (lastReadBook[0] != 0 && strcmp(fname, lastReadBook) == 0) {
        tft.setTextColor(YELLOW); 
        tft.print(F("* ")); 
      } else {
        tft.setTextColor(WHITE);
      }
      tft.print(fname);
      
      yPos += (FILE_BTN_HEIGHT + 2); fileCount++;
    }
    entry.close();
    if (fileCount >= MAX_FILES_ON_SCREEN) break;
  }
  // 没找到书的提示
  if (fileCount == 0) {
    tft.setCursor(50, 100);
    tft.setTextColor(GREY);
    tft.print(F("No TXT Files Found"));
  }

  root.close();

  // Settings Btn
  tft.fillRect(0, 210, SCREEN_WIDTH, 30, DARKGREY);
  tft.drawLine(0, 210, SCREEN_WIDTH, 210, GREY);
  tft.setCursor(88, 218); tft.setTextColor(WHITE); tft.setTextSize(2);
  tft.print(F("[ SETTINGS ]"));
}

void handleMenuClick(int x, int y) {
  if (y > 210) {
    drawSettings();
    return;
  }
  if (y > 35) {
    int index = (y - 35) / (FILE_BTN_HEIGHT + 2);
    if (index >= 0 && index < MAX_FILES_ON_SCREEN) openFileByIndex(index);
  }
}

void openFileByIndex(int targetIndex) {
  root = SD.open("/");
  int currentTxtCount = 0;
  while(true) {
    File entry = root.openNextFile();
    if (! entry) break; 
    if (!entry.isDirectory()) {
      char* fname = entry.name();
      if ((strstr(fname, ".TXT") || strstr(fname, ".txt")) && !strstr(fname, ".SAV")) {
        if (currentTxtCount == targetIndex) {
          strncpy(currentBookName, fname, 12); 
          currentBookName[12] = 0; 
          
          myBook = SD.open(fname);
          entry.close();
          root.close();
          if (myBook) startReading();
          return;
        }
        currentTxtCount++;
      }
    }
    entry.close();
  }
  root.close();
}

// ================= 阅读模式 =================
void startReading() {
  currentState = STATE_READING;
  
  myFont = SD.open("HZK16");
  if(!myFont) showError(F("Font Open Fail"));

  bool hasBookmark = loadBookmark();
  if (!hasBookmark) {
    pageNum = 1; historyIndex = 0; pageHistory[0] = 0;
  }
  drawReadingFrame();
  displayPage();
}

void closeBook() {
  saveBookmark(); 
  myBook.close();
  myFont.close(); // 释放内存
  drawFileList();
}

void drawReadingFrame() {
  tft.fillScreen(BLACK);
  tft.fillRect(0, 0, SCREEN_WIDTH, HEADER_HEIGHT, NAVY);
  tft.setTextSize(2); tft.setTextColor(WHITE);
  tft.setCursor(5, 6); tft.print(currentBookName); 
  tft.fillRect(290, 0, 30, HEADER_HEIGHT, RED);
  tft.setCursor(298, 6); tft.print(F("X"));

  tft.fillRect(0, 210, SCREEN_WIDTH, FOOTER_HEIGHT, DARKGREY);
  tft.drawLine(0, 210, SCREEN_WIDTH, 210, GREY);
  tft.drawRect(5, 213, 60, 24, WHITE);
  tft.setCursor(15, 218); tft.setTextSize(1); tft.print(F("PREV"));
  tft.drawRect(255, 213, 60, 24, WHITE);
  tft.setCursor(270, 218); tft.print(F("NEXT"));
}

void handleReadingClick(int x, int y) {
  if (y < HEADER_HEIGHT && x > 280) { closeBook(); return; }
  if (y > HEADER_HEIGHT) {
    if (x < SCREEN_WIDTH / 2) { 
       goPrevPage();
       tft.fillRect(5, 213, 60, 24, WHITE); delay(50);
       tft.fillRect(5, 213, 60, 24, DARKGREY); tft.drawRect(5, 213, 60, 24, WHITE);
       tft.setCursor(15, 218); tft.setTextSize(1); tft.setTextColor(WHITE); tft.print(F("PREV"));
    } else {
       goNextPage();
       tft.fillRect(255, 213, 60, 24, WHITE); delay(50);
       tft.fillRect(255, 213, 60, 24, DARKGREY); tft.drawRect(255, 213, 60, 24, WHITE);
       tft.setCursor(270, 218); tft.setTextSize(1); tft.setTextColor(WHITE); tft.print(F("NEXT"));
    }
  }
}

// ================= 显示核心 =================
void displayPage() {
  tft.fillRect(0, HEADER_HEIGHT, SCREEN_WIDTH, TEXT_BOTTOM_LIMIT - HEADER_HEIGHT, BLACK); 
  myBook.seek(pageHistory[historyIndex]);
  int cursorX = 5; int cursorY = TEXT_TOP_MARGIN;
  
  while (myBook.available()) {
    if (cursorY + LINE_HEIGHT > TEXT_BOTTOM_LIMIT) break;
    unsigned char c1 = myBook.read();
    if (c1 == '\n') { cursorX = 5; cursorY += LINE_HEIGHT; continue; }
    if (c1 == '\r') continue; 

    if (c1 < 128) {
      if (cursorX + ENG_CHAR_WIDTH > 315) {
        cursorX = 5; cursorY += LINE_HEIGHT;
        if (cursorY + LINE_HEIGHT > TEXT_BOTTOM_LIMIT) { myBook.seek(myBook.position() - 1); break; }
      }
      tft.drawChar(cursorX, cursorY + 1, c1, WHITE, BLACK, 2); cursorX += ENG_CHAR_WIDTH; 
    } else {
      if (!myBook.available()) break;
      unsigned char c2 = myBook.read();
      if (cursorX + CN_CHAR_WIDTH > 315) {
        cursorX = 5; cursorY += LINE_HEIGHT;
        if (cursorY + LINE_HEIGHT > TEXT_BOTTOM_LIMIT) { myBook.seek(myBook.position() - 2); break; }
      }
      drawChinese(cursorX, cursorY, c1, c2, WHITE); cursorX += CN_CHAR_WIDTH; 
    }
  }
  updatePageNum();
}

void updatePageNum() {
  tft.fillRect(100, 212, 120, 26, DARKGREY);
  tft.setCursor(130, 218);
  tft.setTextSize(2); tft.setTextColor(GREY); 
  tft.print(F("- ")); tft.print(pageNum); tft.print(F(" -"));
}

void drawChinese(int x, int y, unsigned char c1, unsigned char c2, uint16_t color) {
  if (c1 < 0xA1 || c2 < 0xA1) return; 
  unsigned char buffer[32]; 
  long offset = ((long)(c1 - 0xA1) * 94 + (long)(c2 - 0xA1)) * 32;
  
  myFont.seek(offset); myFont.read(buffer, 32);
  for (int i = 0; i < 16; i++) {       
    for (int k = 0; k < 2; k++) {      
      unsigned char byteData = buffer[i * 2 + k];
      for (int j = 0; j < 8; j++) {    
        if ((byteData >> (7 - j)) & 0x01) {
          tft.drawPixel(x + k * 8 + j, y + i, color);
        }
      }
    }
  }
}

void goNextPage() {
  if (!myBook.available()) return; 
  if (historyIndex < HISTORY_SIZE - 1) {
    historyIndex++; pageHistory[historyIndex] = myBook.position();
  } else {
    for(int i = 0; i < HISTORY_SIZE - 1; i++) pageHistory[i] = pageHistory[i+1];
    pageHistory[HISTORY_SIZE - 1] = myBook.position();
  }
  pageNum++; displayPage();
}

void goPrevPage() {
  if (historyIndex > 0) {
    historyIndex--; pageNum--; displayPage(); 
  }
}