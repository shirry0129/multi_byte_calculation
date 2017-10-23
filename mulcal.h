#define KETA 20

struct NUMBER
{
    int n[KETA];
    int sign;
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