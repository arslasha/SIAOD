typedef unsigned int typeitem;
const unsigned int N = 100;

struct typeX {
    unsigned int n = 0;
    typeitem x[N] = {};
};

bool isDecreasing(typeX *a);
void input_arr(typeX* a);
void removeValueWithFive(typeX *a, int elem);
void insertElement(typeX *a, int elem);
void input_arr(typeX *a);
void call_arr(typeX *a);
void del_elem(typeX *a, int pos);
void paste_elem(typeX *a, int pos, int elem);