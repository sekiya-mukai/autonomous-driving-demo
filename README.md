````
# Autonomous Driving Demo

C++17で実装した、自動運転システム向けの簡易シミュレータです。

前走車との車間距離や速度差をもとに、

- Adaptive Cruise Control（ACC）
- Collision Detection（衝突リスク判定）

を行います。

また、センサデータの妥当性を検証する `SensorDataValidator` と、安全性を統合的に判定する `DrivingSafetyChecker` を実装しています。

GoogleTestによる単体テスト・境界値テスト・異常値テスト・統合テストを実施し、各ロジックの動作を検証しています。

---

## 概要

本プロジェクトでは、自動運転システムにおける基本的な判断ロジックをシンプルに再現しています。

センサ情報を入力とし、

- センサデータの妥当性検証
- 目標速度の計算
- 衝突リスクの判定
- 安全性の判定

を行います。

また、正常な入力だけでなく、負値・`NaN`・`+Infinity`・`-Infinity` などの異常なセンサデータについても検証しています。

---

## システム構成

```mermaid
flowchart LR

    Sensor["センサ情報"]

    Validator["Sensor Data Validator"]

    ACC["Adaptive Cruise Control"]

    Collision["Collision Detector"]

    Safety["Driving Safety Checker"]

    Controller["車両制御"]

    Sensor --> Validator

    Validator --> ACC
    Validator --> Collision

    ACC --> Safety
    Collision --> Safety

    Safety --> Controller
````

 センサ情報を `SensorDataValidator` で検証した後、Adaptive Cruise ControlおよびCollision Detectionによる判断を行います。

 それぞれの結果を `DrivingSafetyChecker` で確認し、安全性を考慮した制御処理につなげます。

---

 ## クラス構成

```
classDiagram

class SensorData {
    +double currentSpeed
    +double frontVehicleSpeed
    +double distanceToObstacle
}

class SensorDataValidator {
    +bool isValid()
}

class AdaptiveCruiseControl {
    +double calculateTargetSpeed()
}

class CollisionDetector {
    +bool isCollisionRisk()
}

class DrivingSafetyChecker {
    +bool isSafe()
}

class PIDController {
    +double calculate()
}

SensorData --> SensorDataValidator
SensorData --> AdaptiveCruiseControl
SensorData --> CollisionDetector

DrivingSafetyChecker --> SensorDataValidator
DrivingSafetyChecker --> CollisionDetector

AdaptiveCruiseControl --> PIDController
```

 `SensorData` は自車速度、前方車両速度、車間距離などのセンサ情報を保持します。

 `SensorDataValidator` は入力値の妥当性を検証し、Adaptive Cruise ControlおよびCollision Detectionで利用するセンサ情報を確認します。

 `DrivingSafetyChecker` はセンサデータの検証結果と衝突判定を組み合わせ、安全性を確認します。

 `PIDController` は目標値と現在値との差分を利用して制御量を計算します。

---

 ## 処理フロー

```
flowchart TD

    A["センサ情報取得"]

    B{"センサデータは正常？"}

    C["異常データとして処理"]

    D["目標速度計算"]

    E["衝突リスク判定"]

    F["安全性判定"]

    G["制御処理"]

    A --> B

    B -- "No" --> C

    B -- "Yes" --> D
    B -- "Yes" --> E

    D --> F
    E --> F

    F --> G
```

 センサ情報を取得した後、まず入力値の妥当性を検証します。

 異常な値が入力された場合は、そのデータを後続の判断処理に利用しません。

 正常なデータについては、目標速度計算と衝突リスク判定を行い、その結果をもとに安全性を判定します。

---

 ## 実装機能

 ### Adaptive Cruise Control

 以下の情報をもとに目標速度を計算します。

 - 自車速度
- 前方車両速度
- 車間距離

 安全車間距離として `30.0 m` を使用しています。

 車間距離が安全車間距離を下回る場合や、十分な車間距離が確保されている場合など、複数の条件を考慮して目標速度を計算します。

 また、以下の境界値についてテストしています。

 - `distance < 30.0 m`
- `distance = 30.0 m`
- `distance > 30.0 m`
- 目標速度の境界値
- 前方車両速度の境界値

---

 ### Collision Detection

 以下の情報をもとに衝突リスクを判定します。

 - 自車速度
- 前方車両速度
- 車間距離
- 相対速度
- TTC（Time To Collision）

 相対速度は以下の式で計算します。

```
relativeSpeed = egoSpeed - frontSpeed
```

 衝突方向の相対速度が存在する場合、TTCを以下の式で計算します。

```
TTC = distance / relativeSpeed
```

 現在の実装では、TTCが `3.0 sec` 未満の場合を衝突リスクありとして判定します。

 以下の境界値についてもテストしています。

 - 相対速度が負の場合
- 相対速度が0の場合
- 相対速度が正の場合
- `TTC < 3.0 sec`
- `TTC = 3.0 sec`
- `TTC > 3.0 sec`

---

 ### Sensor Data Validation

 `SensorDataValidator` を利用して、センサ情報に含まれる値が妥当であるかを検証します。

 以下の異常値を対象としています。

 - 負の自車速度
- 負の前方車両速度
- 負の車間距離
- `NaN`
- `+Infinity`
- `-Infinity`

 センサデータに異常値が含まれている場合、そのデータを不正な入力として扱います。

---

 ### Driving Safety Check

 `DrivingSafetyChecker` を利用して、センサデータの妥当性検証と衝突判定を組み合わせた安全性チェックを行います。

```
flowchart TD

    A["Sensor Data"]

    B["SensorDataValidator"]

    C{"Valid?"}

    D["CollisionDetector"]

    E["Safety Result"]

    A --> B
    B --> C

    C -- "No" --> E
    C -- "Yes" --> D

    D --> E
```

 不正なセンサデータについては、衝突判定処理へ進めないことを検証しています。

---

 ### PID Controller

 `PIDController` は、目標値と現在値との差分を利用して制御量を計算します。

 PID制御では、

 - 比例項（P）
- 積分項（I）
- 微分項（D）

 を利用します。

 速度制御などの車両制御への利用を想定しています。

---

 ### 単体テスト

 GoogleTestを利用して各ロジックを検証しています。

 実施しているテストケースは以下の通りです。

 - Collision Detectionの機能テスト
- Collision Detectionの境界値テスト
- Adaptive Cruise Controlの機能テスト
- Adaptive Cruise Controlの境界値テスト
- Sensor Data Validationの異常値テスト
- Driving Safety Checkの統合テスト

---

 ## テストケース

 ### Collision Detection

```
CD-F-001 ～ CD-F-003
CD-BV-001 ～ CD-BV-006
```

 以下の条件を検証しています。

 - 衝突リスクあり
- 衝突リスクなし
- 前方車両の方が速い場合
- 相対速度の境界値
- TTCの境界値

---

 ### Adaptive Cruise Control

```
ACC-F-001 ～ ACC-F-003
ACC-BV-001 ～ ACC-BV-009
```

 以下の条件を検証しています。

 - 目標速度の境界値
- 前方車両速度の境界値
- 車間距離の境界値
- 安全車間距離 `30.0 m` の境界
- 前方車両への追従

---

 ### Sensor Data Validation

```
SDV-IV-001 ～ SDV-IV-012
```

 以下の異常値を検証しています。

 - `egoSpeed` の負値
- `frontSpeed` の負値
- `distance` の負値
- `egoSpeed` の `NaN`
- `frontSpeed` の `NaN`
- `distance` の `NaN`
- `egoSpeed` の `+Infinity`
- `frontSpeed` の `+Infinity`
- `distance` の `+Infinity`
- `egoSpeed` の `-Infinity`
- `frontSpeed` の `-Infinity`
- `distance` の `-Infinity`

---

 ### Sensor Data Integration

```
SDV-IT-001 ～ SDV-IT-007
```

 `SensorDataValidator` と `DrivingSafetyChecker` の統合動作を検証しています。

 主に、

 - 正常なセンサデータ
- 負値
- `NaN`
- `+Infinity`
- `-Infinity`

 などの入力に対する安全性判定を確認しています。

---

 ## ディレクトリ構成

```
autonomous-driving-demo
├── CMakeLists.txt
├── README.md
│
├── docs
│   └── design.md
│
├── include
│   ├── AdaptiveCruiseControl.hpp
│   ├── CollisionDetector.hpp
│   ├── DrivingSafetyChecker.hpp
│   ├── PIDController.hpp
│   ├── SensorData.hpp
│   └── SensorDataValidator.hpp
│
├── src
│   ├── AdaptiveCruiseControl.cpp
│   ├── CollisionDetector.cpp
│   ├── DrivingSafetyChecker.cpp
│   ├── PIDController.cpp
│   ├── SensorDataValidator.cpp
│   └── main.cpp
│
└── tests
    ├── AdaptiveCruiseControlTest.cpp
    ├── CollisionDetectorTest.cpp
    ├── DrivingSafetyCheckerTest.cpp
    └── SensorDataValidatorTest.cpp
```

---

 ## ビルド方法

```
mkdir build

cd build

cmake ..

make
```

 または、プロジェクトルートから以下のコマンドでもビルドできます。

```
cmake -S . -B build

cmake --build build -j
```

 GoogleTestはCMakeの `FetchContent` を利用して取得します。

---

 ## 実行方法

```
./autonomous_demo
```

 ビルドディレクトリから実行する場合は、

```
./build/autonomous_demo
```

 を使用します。

---

 ## 実行例

```
Target Speed : 50 km/h
Collision Risk : true
```

---

 ## テスト実行

```
ctest --test-dir build --output-on-failure
```

 詳細なテスト結果を確認する場合は、

```
ctest --test-dir build --verbose
```

 を使用します。

 個別のテストを実行する場合は、

```
./build/collision_detector_test
```

```
./build/adaptive_cruise_control_test
```

```
./build/sensor_data_validator_test
```

```
./build/sensor_data_integration_test
```

 を使用します。

---

 ## 使用技術

 - C++17
- CMake
- GoogleTest
- Mermaid
- オブジェクト指向設計
- 単体テスト
- 境界値テスト
- 異常値テスト
- 統合テスト

---

 ## 今後の拡張案

 - Lane Keeping Assist（LKA）
- TTC（Time To Collision）によるリスク評価
- 複数障害物対応
- 経路計画（Path Planning）
- センサフュージョン
- AUTOSARを意識したインターフェース分離
- CI/CDによる自動ビルド・自動テスト
- テストカバレッジの計測
- 静的解析・コードフォーマットチェック

---

 ## 作成目的

 自動運転ソフトウェア開発で用いられる考え方を学習するために作成しました。

 特に、

 - C++による設計
- CMakeによるビルド環境構築
- GoogleTestによる単体テスト
- 境界値テスト
- 異常値テスト
- 統合テスト
- センサデータの妥当性検証
- 自動運転アルゴリズムの基礎実装

 を経験することを目的としています。

 正常系だけでなく、異常入力や境界条件についても検証することで、自動運転ソフトウェアにおける安全性を意識した設計・実装・テストを学習します。

`````
