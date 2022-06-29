#include <M5Atom.h> //Atomのヘッダファイルを準備

//水分センサーとポンプのピンは決まっている。
//以下のとおり
#define SENSOR_PIN 32
#define PUMP_PIN 26

// FastLEDライブラリの設定（CRGB構造体）
CRGB dispColor(uint8_t r, uint8_t g, uint8_t b)
{
  return (CRGB)((r << 16) | (g << 8) | b);
}
// 初期設定 -----------------------------------------------
void setup()
{
  // 本体初期化（UART有効, I2C無効, LED有効）
  M5.begin(true, false, true);
  // LED全消灯（赤, 緑, 青）
  M5.dis.drawpix(0, dispColor(0, 0, 0));

  pinMode(SENSOR_PIN, INPUT);
  pinMode(PUMP_PIN, OUTPUT);

  // pinMode(25, OUTPUT);
  // digitalWrite(25, 0);
}
// メイン -------------------------------------------------
void loop()
{
  M5.update(); //本体のボタン状態更新

  if (M5.Btn.isPressed())
  {                                          //ボタンが押されていれば
    M5.dis.drawpix(0, dispColor(0, 0, 255)); // LED（指定色）
    Serial.println("Pressed");

    digitalWrite(PUMP_PIN, true);

    int rawADC = analogRead(SENSOR_PIN);
    Serial.print("Sensor:");
    Serial.println(String(rawADC));
  }
  else
  {
    //ボタンが押されてなければ
    M5.dis.drawpix(0, dispColor(20, 20, 20)); // LED（白）
    // Serial.println("Release");
    digitalWrite(PUMP_PIN, false);
  }
  delay(100); // 100ms待機
}