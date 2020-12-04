# TRUST-DOG PROJECT

## 0.プロジェクト概要
ドローン用ブラシレスモータを使って、Spot miniのような動的な制御ができる四足歩行ロボットを作るというプロジェクト。

## 1.ハードウェア
### 1.1. ハードウェア概要
一脚につき3軸のアクチュエータを有する、全12軸四脚ロボット。  
構成自体はSpot miniやLaikagoと同じ。  
縦（）×横（）×高さ（）

### 1.2. アクチュエータ
+ モータ：tarot 4008　330kv
+ ドライバ：Odrive v4.6

TRUST DOGに使うアクチュエータは自作の遊星歯車減速機と一体型となっております。。
遊星歯車減速機は減速機が1/8で非常にコンパクトな設計となっております。
ギア部とシャフト部のみ金属加工品で他は３Dプリント品とコスト面や柔軟性も意識した設計となっております。

### 1.3. 脚
脚は第1軸、第2軸はアクチュエータと直接接続されており、第3軸はベルト伝達機構となっております。
ベルト伝達機構のメリットはバックラッシを軽減できるなどがあります。
また、現時点でのベルト伝達機構の減速比は１：１ですが、トルクが必要となったとき簡単に設計が変更できる柔軟性も大きなメリットです。
プーリーは３Dプリント品なので非常に低コストです。

### 2.

* huga 3.5.2
* hogehuga 1.0.2

# Installation

Requirementで列挙したライブラリなどのインストール方法を説明する

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

# Author

作成情報を列挙する

* 作成者
* 所属
* E-mail

# License
ライセンスを明示する

"hoge" is under [MIT license](https://en.wikipedia.org/wiki/MIT_License).

社内向けなら社外秘であることを明示してる

"hoge" is Confidential.
