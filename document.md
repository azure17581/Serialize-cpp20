# bitRW
シリアライズ/デシリアライズするライブラリ

# シリアライズ
```c++
bitRW::bitSave writer("out");
writer.open();

//serialize
writer.write(3);
writer.write("hoge");
/*
    ...
*/
writer.close();
```
ファイルパス`out`に`.write()`の引数の値を書き込んでいく．  
原始型 (`int`, `float`,...), `pair<T1, T2>`, `vector<T>`, `list<T>`, `map<T>`, `array<T>`, ポインタ(参照先の値), ユーザー定義クラスに対応．  
```c++
int arr[3] = {2,3,4};
writer.write(arr, 3);
```
と書くことで組込み配列にも対応．
```C++
writer.write(1,2,3,"hoge", 3.14);
```
のように書くことで複数まとめて書き込む．


# デシリアライズ
```c++
bitRW::bitLoad reader("dst");
reader.open();

//deserialize
int x;
string s;
reader.read(x);
reader.read(s);
/*
    ...
*/
reader.close();
```
ファイルパス`dst`のバイナリデータを`.read()`の引数の変数に読み込む．  
原始型 (`int`, `float`,...), `pair<T1, T2>`, `vector<T>`, `list<T>`, `string`, `(unordered_)map<T>`, `array<T>`, ポインタ(参照先へ読み込む), ユーザー定義クラスに対応．
```c++
int arr[3];
reader.read(arr, 3);
```
のように書くことで組込み配列へ読み込む．
```c++
reader.read(x, y, z);
```
のように書くことで複数まとめて読み込む．

# ユーザー定義クラスへの対応[?]
```c++
class myClass{
public:
    void RW(bitRW::senderS& ss);
    void RW(bitRW::senderW& sw);
private:
    int val1;
    int val2;
    double val3;
    string name;
    /*
        ...
    */
};

void myClass::RW(bitRW::senderS& ss){
    ss(this.val1, this.val2, this.val3, this.name);
}

void myClass::RW(bitRW::senderW& sw){
    ?
}
```
`public`メソッドに `void RW(bitRW::senderS& ss)`, `void RW(bitRW::senderW& sw)` を追加．  
`.RW()`メソッドには保存したいメンバ変数をまとめて`ss()`へ渡す．

# 実装状況
型|bitLoad|bitSave
-|:-:|:-:
BASIC| o|o
Array|
S_Container|
Pair|
Pointer|
Dictionary|