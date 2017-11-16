#define KETA 20

struct NUMBER
{
    int n[KETA];
    int sign;   //0<=:1,0>:-1
};

//表示
void dispNumber(struct NUMBER *a);

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
int isZero(struct NUMBER *a);

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

//正誤判定
void diff(struct NUMBER *a,int x);