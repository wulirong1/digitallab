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

const int row[] = {
  ROW1, ROW2, ROW3, ROW4, ROW5, ROW6, ROW7, ROW8
};
const int col[] = {
  COL1, COL2, COL3, COL4, COL5, COL6, COL7, COL8
};

byte scan[8][8] = {
  {1, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 1}
};

byte circle[8][8] = {
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {0, 0, 1, 1, 1, 1, 0, 0}
};


void setup()
{

  for (byte i = 0; i <= sizeof(row) / sizeof(row[0]); i++) {
    pinMode(row[i], OUTPUT);
    digitalWrite(row[i],HIGH);
  }
  for (byte i = 0; i <= sizeof(col); i++) {
    pinMode(col[i], OUTPUT);
    digitalWrite(col[i],LOW);
  }

  Serial.begin(9600);

}

void loop()
{
  if (Serial.available() >= 8) {
    for (int row = 0; row < 8; row++) {
      byte b = Serial.read();
      for (int col = 0; col < 8; col++) {
        circle[row][col] = (b >> (7 - col)) & 0x01;
      }
    }
  }
  showPattern(circle);
}

void showPattern(byte matrix[8][8]) {
  for (byte rowIdx = 0; rowIdx < 8; rowIdx++) {
    // 啟用當前 row（LOW for 共陽）
    digitalWrite(row[rowIdx], LOW);

    // 為當前 row 設定每個 column 的值（HIGH: 亮, LOW: 滅）
    for (byte colIdx = 0; colIdx < 8; colIdx++) {
      if (matrix[rowIdx][colIdx] == 1) {
        digitalWrite(col[colIdx], HIGH);  // 給 HIGH 表示亮
      } else {
        digitalWrite(col[colIdx], LOW);   // 關閉
      }
    }

    delay(2);  // 保持顯示一小段時間，讓人眼能看到

    // 關閉當前 row & 清空 col
    digitalWrite(row[rowIdx], HIGH);
    for (byte colIdx = 0; colIdx < 8; colIdx++) {
      digitalWrite(col[colIdx], LOW);
    }
  }
}

