# bitRW
concept(C++20) を使ってシリアライズ/デシリアライズするライブラリ

# 導入
全ヘッダ，ソースファイルをコピー．`serialize.h` をインクルードする．

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
原始型 (`int`, `float`,...), `pair<T1, T2>`, `vector<T>`, `list<T>`, `map<T>`, `array<T>`, ユーザー定義クラスに対応．  

```C++
writer.write(1,2,3,"hoge", 3.14);
```
のように可変長引数を渡すことで，先頭から順に複数まとめて書き込むことも可能．


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
原始型 (`int`, `float`,...), `pair<T1, T2>`, `vector<T>`, `list<T>`, `string`, `(unordered_)map<T>`, `array<T>`, ユーザー定義クラスに対応．
```c++
reader.read(x, y, z);
```
のように可変長引数を渡すことで，先頭から順に複数まとめて読み込むことも可能．

# ユーザー定義クラスへの対応
```c++
class myClass{
public:
    void BITRW_BITSAVE(bitRW::senderS sd) const;
    void BITRW_BITLOAD(bitRW::senderL sd);
private:
    int val1;
    int val2;
    double val3;
    string name;
};

void myClass::BITRW_BITSAVE(bitRW::senderS sd) const{
    sd(this->val1, this->val2, this->val3, this->name);
}

void myClass::BITRW_BITLOAD(bitRW::senderL sd){
    sd(this->val1, this->val2, this->val3, this->name);
}
```
`public`メソッドに ` void BITRW_BITSAVE(bitRW::senderS sd) const`, `void BITRW_BITLOAD(bitRW::senderL sd)` を追加．  
各メソッドでは保存/読込したいメンバ変数をまとめて`sd()`へ渡す．順番を一致させる．  
対応させたクラスの変数をシリアライズ/デシリアライズするには，他の型と同様にして`bitSave.write()`や`bitLoad.read()`の引数へ渡す．

# 対応状況
型|bitLoad|bitSave
-|:-:|:-:
`int`, `double`,...| o|o
`std::pair`|o|o
`std::vector`|o|o
`std::list`|o|o
`std::basic_string`|o|o
`std::array`|o|o
`std::map`|o|o
`std::unordered_map`|o|o
`std::multimap`|x|x
`std::unordered_multimap`|x|x
ユーザー定義 class|o|o
(可変長引数)|o|o

`std::multimap`, `std::unordered_multimap` もおそらく問題なく動くが未検証なので対応させていない．