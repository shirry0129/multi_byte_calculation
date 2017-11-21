#define KETA 4

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
void setRnd(struct NUMBER *a,int k);

//コピー
void copyNumber(struct NUMBER *a,struct NUMBER *b);

//絶対値
void getAbs(struct NUMBER *a,struct NUMBER *b);

//ゼロ判別
int isZero(const struct NUMBER *a);

//*10
int mulBy10(struct NUMBER *a,struct NUMBER *b);

// /10
int divBy10(struct NUMBER *a,struct NUMBER *b);

//aとbの交換
void swap(struct NUMBER *a,struct NUMBER *b);

//int型変数の設定
int setInt(struct NUMBER *a,int x);

//int型変数の取得
int getInt(struct NUMBER *a,int *x);

//setInt正誤判定
void setInt_diff(struct NUMBER *a,int x);

//符号設定
void setSign(struct NUMBER *a,int s);

//符号取得
int getSign(const struct NUMBER *a);

//大小比較
///0…a==b
///1…a>b
///-1…a<b
int numComp(struct NUMBER *a,struct NUMBER *b);

//numComp正誤判定
void numComp_diff(int sl,int x,int y);

//加算
int add(struct NUMBER *a,struct NUMBER *b,struct NUMBER *c);