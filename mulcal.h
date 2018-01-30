#define KETA 202

struct NUMBER
{
    int n[KETA];
    int sign;   //0<=:1,0>:-1
};

//表示
void dispNumber(const struct NUMBER *a);

//ゼロサプレス表示
void dispNumberZeroSuppress(struct NUMBER *a);

//ゼロクリア
void clearByZero(struct NUMBER *a);

//乱数設定
void setRnd(struct NUMBER *a,int keta);

//コピー
//source → target
void copyNumber(const struct NUMBER *source,struct NUMBER *target);

//絶対値
//sourceの絶対値をtargetに返す
void getAbs(const struct NUMBER *source,struct NUMBER *target);

//ゼロ判別
//0なら0を返す
int isZero(const struct NUMBER *a);

//*10
int mulBy10(const struct NUMBER *a,struct NUMBER *b);

// /10
int divBy10(const struct NUMBER *a,struct NUMBER *b);

//aとbの交換
void swap(struct NUMBER *a,struct NUMBER *b);

//int型変数の設定
int setInt(struct NUMBER *a,int x);

//int型変数の取得
int getInt(const struct NUMBER *a,int *x);

//符号設定
void setSign(struct NUMBER *a,const int sign);

//符号取得
int getSign(const struct NUMBER *a);

//大小比較
///0…a==b
///1…a>b
///-1…a<b
int numComp(const struct NUMBER *a,const struct NUMBER *b);

//加算
//a + b = sum
int add(const struct NUMBER *a,const struct NUMBER *b,struct NUMBER *sum);

//減算
//a - b = diff
int sub(const struct NUMBER *a,const struct NUMBER *b,struct NUMBER *diff);

//インクリメント
//a + 1 = b
int increment(const struct NUMBER *a,struct NUMBER *b);

//デクリメント
//a - 1 = b
int decrement(const struct NUMBER *a,struct NUMBER *b);

//乗算
//a * b = product
int multiple(const struct NUMBER *a,const struct NUMBER *b,struct NUMBER *product);

//除算
//a / b = quotient 余り remainder
int divide(const struct NUMBER *a,const struct NUMBER *b,struct NUMBER *quotient,struct NUMBER *remainder);

//一桁整数による除算
//a / b = c 余り d
int int_divide(const struct NUMBER *a,const int b,struct NUMBER *quotient,int *remainder);

//平方根
//b = √a
int sqrt_newton(const struct NUMBER *a,struct NUMBER *b);

//*10^n
int mulBy10n(const struct NUMBER *a,int n,struct NUMBER *b);

//正誤判定
void diff(int count);