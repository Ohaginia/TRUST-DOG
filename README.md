# TRUST-DOG PROJECT
 <img width="" alt="trust_dog" src="https://github.com/Ohaginia/TRUST-DOG/blob/master/docs/images/trust_dog1.PNG?raw=true">     
 
## 0.プロジェクト概要
ドローン用ブラシレスモータを使って、Spot miniのような動的な制御ができる四足歩行ロボットを作るというプロジェクト。 
## 1.ハードウェア
### 1.1. ハードウェア概要

一脚につき3軸のアクチュエータを有する、全12軸四脚ロボット。  
構成自体はSpot miniやLaikagoと同じ。  
縦464[mm] × 横337[mm] × 高さ334[mm] (上図姿勢時）

### 1.2. アクチュエータ
 <img width="200" alt="tarot4008" src="https://github.com/Ohaginia/TRUST-DOG/blob/master/docs/images/tarot4008.jpg?raw=true"> 　<img width="200" alt="ODrive" src="https://github.com/Ohaginia/TRUST-DOG/blob/master/docs/images/odrive.jpg?raw=true">  <img width="180" alt="AS5047P" src="https://github.com/Ohaginia/TRUST-DOG/blob/master/docs/images/AS5047P.jpeg?raw=true">  

+ モータ：[tarot4008　330kv](https://www.aliexpress.com/i/32697306634.html)
+ ドライバ：[Odrive v3.6](https://odriverobotics.com/)  
+ エンコーダ：[AS5047P](https://www.mouser.jp/ProductDetail/ams/AS5047P-TS_EK_AB?qs=Rt6VE0PE%2FOfJKFTMKo%252BL0Q%3D%3D)  

<img width="300" alt="actuator1" src="https://github.com/Ohaginia/TRUST-DOG/blob/master/docs/images/actuator_tsd.PNG?raw=true">   <img width="300" alt="acuator2" src="https://github.com/Ohaginia/TRUST-DOG/blob/master/docs/images/actuator2_tsd.PNG?raw=true">  
TRUST DOGに使うアクチュエータには自作の遊星歯車減速機を使用しております。  
減速比は8/1でモータと一体型になっております。　　
また、ギア部とシャフト部のみ金属加工品で他は３Dプリント品とコスト面や柔軟性も意識した設計となっております。

### 1.3. 脚
<img width="" alt="acuator2" src="https://github.com/Ohaginia/TRUST-DOG/blob/master/docs/images/leg_tsd.PNG?raw=true">    
脚は第1軸、第2軸はアクチュエータと直接接続されており、第3軸はベルト伝達機構となっております。  
ベルト伝達機構のメリットはバックラッシを軽減できるなどがあります。  
また、現時点でのベルト伝達機構の減速比は１：１ですが、トルクが必要となったとき簡単に設計が変更できる柔軟性も大きなメリットです。  
<img width="300" alt="pulley" src="https://github.com/Ohaginia/TRUST-DOG/blob/master/docs/images/pulley_tsd.PNG?raw=true">  
プーリーは３Dプリント品なので非常に低コストです。

### 1.4 テストスタンド
逆運動学やインピーダンス制御の実験を行うスタンド。

## 2. ソフトウェア
### 2.1　使用環境
+ ROS: Melodic
+ 使用言語: C/C++

### 2.2 開発フェーズ


#### 2.2.1 逆運動学とは
[逆運動学](https://en.wikipedia.org/wiki/Inverse_kinematics)とは足先の位置座標から関節角度を計算する手法。


#### 2.2.2 インピーダンス制御とは
インピーダンス制御とは、脚先を仮想的なマス・バネ・ダンパ系と固定することで動物のような脚の柔軟性を実現できるという制御手法。
https://youtu.be/9AXlkIq_FQM
↑この動画のように脚の仮想インピーダンスを適切に調節することでジャンプすることも可能に！

インピーダンス制御と逆運動学を組み合わせることで、安定した歩行が可能になるという仮説をもとに開発を勧めていきます。



```bash
pip install huga_package
```

# Usage

DEMOの実行方法など、"hoge"の基本的な使い方を説明する

```bash
git clone https://github.com/hoge/~
cd examples
python demo.py
```

# Note

注意点などがあれば書く

# 作成者

作成情報を列挙する

* 作成者：上原昇馬
* 所属：TRUST SMITH 株式会社
* E-mail：Hamashoma@gmail.com

# ライセンス

"TRUST DOG" プロジェクトは [MIT license](https://en.wikipedia.org/wiki/MIT_License)とします。
