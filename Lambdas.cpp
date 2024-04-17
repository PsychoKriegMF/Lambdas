#include <iostream>
#include <functional>

class A;
void ExternalCaller(A& z, A& x, std::function<bool(A& q, A& w)>func);


class A {
public:
    int a;

    int GetA()const { return a; }
    void SetA(int a) { this->a = a; }

    void LambdaExample() {
        A tmp;
        tmp.a = 86;

       auto lfunc = [this](A& q, A& w)mutable->bool {
            if (q.a <= w.a) {
                this->SetA(w.a);
            }
            return q.a > w.a;
            };
        ExternalCaller(*this, tmp, lfunc);
    }

};



void ExternalCaller(A& z, A& x, std::function<bool(A& q, A& w)>func) {
    if (func(z, x)) {
        std::cout << z.a << " greatest\n";
    }
    else {
        std::cout << x.a << " greatest\n";
    }

}

int main()
{
    std::pair<A*, A*> lastCompare;
    auto lFunc = [&lastCompare](A& q, A& w)mutable->bool { 
        lastCompare.first = &q;
        lastCompare.second = &w;
        return q.a > w.a;
        };
    A f;
    A t;
    f.SetA(8);
    t.a = 10;
    ExternalCaller(f, t, lFunc);

    std::cout << "Last Compare: \n" << lastCompare.first << " width value - " << lastCompare.first->a << '\n';
    std::cout << lastCompare.second << " width vlue - " << lastCompare.second->a << '\n';
}

