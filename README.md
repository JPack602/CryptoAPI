![CNG](https://user-images.githubusercontent.com/80070644/175818490-5e94dff0-2945-4f39-b2b4-1b5502a7d363.png)
# Windows CNG のサンプルコード  
Windows CNG (Crypto Next Generatin)を使ったサンプルコードです。  
  
CNGは非推奨となったCryptAPIの代替として用意された背景があります。  

今回は数ある機能のうちRSAを使用して、文字列を暗号化・復号するサンプルプログラムを用意しました。  

使用する鍵(公開鍵・秘密鍵)は「CNG - GenKey」にて生成した鍵をソースコード内にハードコーディングしています。  
また、「KeySample.txt」内に鍵のサンプルを用意していますので、参考にして頂けますと幸いです。

## 参考文献
* [CNG について](https://docs.microsoft.com/ja-jp/windows/win32/seccng/about-cng)
