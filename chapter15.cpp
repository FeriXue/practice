#include <iostream>

using namespace std;

// 基类 Quote的对象表示按原价销售的书籍
class Quote {
public:
    string isbn() const;
    virtual double net_price(size_t n) const;
} ;

// Quote派生出另一个名为bulk_quto的类，它表示可以打折销售的书籍
class Bulk_quto : public Quote { // 因为Bulk_quoto在它的派生列表中使用了public关键字，因此我们完全可以把bulk_quto对象当成quoto的对象来使用
    double net_price(size_t) const override;
} ;

// 计算并打印销售给定数量的某种书籍所得的费用

double print_total(ostream &os, const Quote &item, size_t n)
{

}
