[English Document](README.md) | [日本語ドキュメント](README_JP.md)

# Starlight

Starlightはスプラトゥーン2の実行ファイルへのLinkとHookを実装し、任意のC++コードを実行することができる仕組みです。

## 貢献者一覧 
[@shibbo](https://github.com/shibbo) - リバースエンジニアリング

[@Thog](https://github.com/Thog) - rtldの実装に関する専門知識

[@3096](https://github.com/3096) - スプラトゥーン2の内部データに関する専門知識

[@khang06](https://github.com/khang06) - スプラトゥーン2の内部データに関する専門知識

[@OatmealDome](https://github.com/OatmealDome) - スプラトゥーン2の内部データに関する専門知識

[@Random0666](https://github.com/random0666) -  スプラトゥーン2の内部データに関する専門知識

## 必要なもの
Dockerが実行できるUbuntu 18.04の環境が必要です。WSL(Windows Subsystem for Linux)はバージョン2でないとDockerをサポートしていないので、アップグレードする必要があります。

 - Ubuntu 18.04 （Python3が必須）
 - Windows 10 (ビルドIDが18917以上であること)
 - 未対策Nintendo Switch（ポート5000でFTPが有効であること）
 - スプラトゥーン2のバージョン3.1.0（v1441792）(国内版・北米版などリージョンは問わない) 
   - もし3.1.0を所持していない場合LFS（Layered File System）を使って擬似的にダウングレードする必要があります。[参考文献は以下の記事をどうぞ]
   
> [任意のバージョンを3.1.0に擬似的にダウングレードする方法](https://tkgstrator.work/?p=27445)

# Windowsでおこなうこと

もしWSLではなく、ネイティブのUbuntu 18.04でStarlightを実行しようと考えている場合、このセクションはスキップしてください。

## WSLの有効化

デフォルトではWSLは無効化されているのでコマンドで有効化する必要があります。まず、WindowsのバージョンがWSL2をサポートしているか`ver`コマンドでチェックします。管理者権限でコマンドプロンプトを開いて`ver`と入力し、エンターキーを押してください。

```
C:\Users\devonly>ver
Microsoft Windows [Version 10.0.19628.1]
```

この場合、バージョンは19628なのでインストール要件である18917以上を満たしています。満たしたいない場合はWindowsのアップデートを行ってください。

WSL2を使うためにWSLとHyperVを有効化します。管理者権限でコマンドプロンプトを起動し、以下の二つのコマンドを実行してください。

`dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart`

`dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart`

できたら、Windowsを再起動します。

## Ubuntu 18.04のインストール

以下のリンクをクリックすればWindows10にUbuntu 18.04がインストールできます。

[Ubuntu 18.04 Microsoft Store](https://www.microsoft.com/store/apps/9N9TNGVNDL3Q)

## WSL1をWSL2に変換する

コマンドプロンプトを管理者権限で実行し`wsl -l -v`と入力してエンターキーを押します。

```
C:\Users\devonly>wsl -l -v
  NAME                   STATE           VERSION
* docker-desktop-data    Running         2
  Ubuntu-18.04           Running         1 <=== WSL1
  docker-desktop         Running         2
```

この場合、Ubuntu 18.04のWSLバージョンは1ですので、これを2に変換します。コマンドを実行してから約5分ほどかかります。

```
C:\Users\devonly>wsl --set-version Ubuntu-18.04 2
Conversion in progress, this may take a few minutes...
Conversion complete.
```

完了したら再度コマンドを入力し、Ubuntu 18.04のWSLバージョンが2になっていることを確認してください。

```
C:\Users\devonly>wsl -l -v
  NAME                   STATE           VERSION
* docker-desktop-data    Running         2
  Ubuntu-18.04           Running         2 <=== WSL2
  docker-desktop         Running         2
```

ここでWSLのデフォルトバージョンを2にしておくと、今後この作業が不要になります。

```
C:\Users\devonly>wsl --set-default-version 2
For information on key differences with WSL 2 please visit https://aka.ms/wsl2
```

## Docker Desktop for Windowsのインストール

以下のリンクからDocker Desktop for Windowsをダウンロードし、インストールしてください。

[Docker Desktop for Windows](https://hub.docker.com/editions/community/docker-ce-desktop-windows)

WSL2の機能を有効化するために、以下の設定をチェックします。

 - Settings->General
   - `Use the WSL2 based engine`にチェック
- Settings->Resources->WSL INTEGRATION
   - `Enable integration with my default WSL distro`にチェック
   - `Ubuntu-18.04`を有効化

# Ubuntu 18.04でおこなうこと

Starlightで作成したパッチをニンテンドースイッチにFTP経由で送信するためにPytthon3が必要になるのでインストールします。

```bash
sudo apt update
sudo apt upgrade
sudo apt install -y python3 make
```

Starlightレポジトリのクローンを行います。

```bash
git clone https://github.com/tkgstrator/Starlight.git
cd Starlight
make
```

## Starlightの設定

自身の環境を反映させるため、`vi Makefile`などのコマンドでMakefileを編集します。

```makefile
# TODO (Khangaroo): Make this process a lot less hacky (no, export did not work)
# See MakefileNSO

.PHONY: all clean starlight install 

S2VER ?= 310 # スプラトゥーン2のバージョン（変更不要）
S2VERSTR ?= 3.1.0 # スプラトゥーン2のバージョン文字列（変更不要）
S2ROMTYPE ?= TrialUS20 # スプラトゥーン2のリージョン（以下の表を参考）
IP ?= 192.168.0.22 # ニンテンドースイッチのIPアドレス
```

|  Region  |  RomType |    Title ID    |
|   :--:   |   :--:   |      :--:      |
|    JP    |JP Product|01003C700009C000|
|    US    |US Product|01003BC0000A0000|
|    EU    |EU Product|0100F8F0000A2000|
|   EveJP  |JP Premiere|0100D070040F8000|
|   EveUS  |US Premiere|01003870040FA000|
|   EveEU  |EU Premiere|010086F0040FC000|
|TrialJP   |US Demo '19|Not supported|
|TrialUS   |US Demo '19|01006BB00D45A000|
|TrialEU   |US Demo '19|Not supported|
|TrialJP20 |JP Demo '20|0100998011330000|
|TrialUS20 |US Demo '20|01002120116C4000|
|TrialEU20 |EU Demo '20|01009240116CC000|
|ShowFloor |N/A|Not supported|
|ShowDL |Testfire|010000A00218E000|

## 使えるコマンド

```bash
make # Dockerコンテナを使ってStarlightをビルドします
make clean # Dockerコンテナ内だけでサポートされています
make starlight # Dockerコンテナ内だけでサポートされています
make install # Dockerコンテナを使ってStarlightをビルドしたあと、ニンテンドースイッチに自動的にパッチを送信します
```

## 謝辞

[@shadowninja108](https://twitter.com/shadowninja108) - スプラトゥーン2の内部データに関する専門知識

[@container12345](https://twitter.com/container12345) - サーモンランに関するクラスの解析

# クレジット
0CBH0 - nsnsotool

libnx - Makefile creation


