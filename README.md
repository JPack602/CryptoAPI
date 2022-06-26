![CNG](https://user-images.githubusercontent.com/80070644/175818490-5e94dff0-2945-4f39-b2b4-1b5502a7d363.png)
# Windows CNG のサンプルコード  
Windows CNG (Crypto Next Generatin)を使ったサンプルコードです。  
  
Restart Managerは本来Windowsの起動時や再起動時にアプリケーションを終了させるための機能です。  
あるアプリケーションにより開かれているファイルを強制的に削除したい場合などに使用します。  

実際に使用した例として、Wordファイルを削除しようとした際に以下の様に、ダイアログが表示されました。  
![screenshot](https://user-images.githubusercontent.com/80070644/175791202-57806996-044f-466f-9c33-c1b2c1a4e6c4.png)  
  
その為、削除したいWordファイル名をサンプルコード内にある関数"ForceShutdown"に渡してやることにより、ファイルを開いているWINWORD.EXE(Microsoft Word)を終了させ、無事にファイルの削除をすることが出来た経験があります。  

実際に使用する様子を以下に示します。  

## デモ  
https://user-images.githubusercontent.com/80070644/175790872-79e0ed9b-ccc4-44fd-bdf2-5be919d35817.mp4


## 参考文献
* [再起動マネージャーについて](https://docs.microsoft.com/ja-jp/windows/win32/rstmgr/about-restart-manager)