#define ROW1 13
#define ROW2 12
#define ROW3 11
#define ROW4 10
#define ROW5 9
#define ROW6 8
#define ROW7 7
#define ROW8 6

#define COL1 5
#define COL2 4
#define COL3 3
#define COL4 A4
#define COL5 A3
#define COL6 A2
#define COL7 A1
#define COL8 A0

#define BUTTON 2

const int row[] = {ROW1, ROW2, ROW3, ROW4, ROW5, ROW6, ROW7, ROW8};
const int col[] = {COL1, COL2, COL3, COL4, COL5, COL6, COL7, COL8};

int imgIndexNow = 0;
bool isPressing = false;
int incomingByte = 0;

// === 圖案資料 ===
int circle[8][8] = {
  {1,1,0,0,0,0,1,1},
  {1,0,1,1,1,1,0,1},
  {0,1,1,1,1,1,1,0},
  {0,1,1,1,1,1,1,0},
  {0,1,1,1,1,1,1,0},
  {0,1,1,1,1,1,1,0},
  {1,0,1,1,1,1,0,1},
  {1,1,0,0,0,0,1,1}
};

int face[8][8] = {
  {1,1,0,0,0,0,1,1},
  {1,0,1,1,1,1,0,1},
  {0,1,1,0,0,1,1,0},
  {0,1,1,1,1,1,1,0},
  {0,1,0,1,1,0,1,0},
  {0,1,1,0,0,1,1,0},
  {1,0,1,1,1,1,0,1},
  {1,1,0,0,0,0,1,1}
};

int H[8][8] = {
  {1,1,1,1,1,1,1,1},
  {1,1,0,1,1,0,1,1},
  {1,1,0,1,1,0,1,1},
  {1,1,0,0,0,0,1,1},
  {1,1,0,0,0,0,1,1},
  {1,1,0,1,1,0,1,1},
  {1,1,0,1,1,0,1,1},
  {1,1,1,1,1,1,1,1}
};

int A[8][8] = {
  {1,1,1,1,1,1,1,1},
  {1,1,1,0,0,1,1,1},
  {1,1,0,1,1,0,1,1},
  {1,1,0,1,1,0,1,1},
  {1,1,0,0,0,0,1,1},
  {1,1,0,1,1,0,1,1},
  {1,1,0,1,1,0,1,1},
  {1,1,1,1,1,1,1,1}
};

// === 設定階段 ===
void setup() {
  Serial.begin(9600);

  // 初始化列腳（行）
  for (byte i = 0; i < sizeof(row) / sizeof(row[0]); i++) {
    pinMode(row[i], OUTPUT);
  }

  // 初始化行腳（列）
  for (byte i = 0; i < sizeof(col) / sizeof(col[0]); i++) {
    pinMode(col[i], OUTPUT);
  }

  // 初始化所有 LED 為關閉
  for (int i = 3; i <= 13; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }

  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);

  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);

  // 設定按鈕為上拉
  pinMode(BUTTON, INPUT_PULLUP);
}

// === 主循環 ===
void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();

    if (incomingByte == 'c') showPattern(circle);
    else if (incomingByte == 'H') showPattern(H);
    else if (incomingByte == 'A') showPattern(A);

    incomingByte = 0;  // 清除避免重複
  }

  // 處理按鈕切換圖案
  if (digitalRead(BUTTON) == LOW && !isPressing) {
    isPressing = true;
    imgIndexNow += 1;
    if (imgIndexNow > 2) imgIndexNow = 0;
  } else if (digitalRead(BUTTON) == HIGH && isPressing) {
    isPressing = false;
  }

  // 根據目前索引顯示圖案
  if (imgIndexNow == 0) lightup(A);
  else if (imgIndexNow == 1) lightup(circle);
  else if (imgIndexNow == 2) lightup(face);
}

// === 顯示圖案函數 ===
void lightup(int matrix[8][8]) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(col[i], HIGH);  // 啟用第 i 欄
    for (int j = 0; j < 8; j++) {
      // 這裡改成 HIGH 代表亮，LOW 代表暗
      digitalWrite(row[j], matrix[j][i] == 1 ? HIGH : LOW);
    }
    delay(1);
    for (int j = 0; j < 8; j++) {
      digitalWrite(row[j], LOW);  // 關閉列
    }
    digitalWrite(col[i], LOW);  // 關閉欄
  }
}


// 封裝的 showPattern 函數
void showPattern(int matrix[8][8]) {
  for (int i = 0; i < 200; i++) {  // 顯示一段時間
    lightup(matrix);
  }
}
























