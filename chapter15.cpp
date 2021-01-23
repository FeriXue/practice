#include <iostream>

using namespace std;

// 基类 Quote的对象表示按原价销售的书籍
class Quote {
public:
    Quote() = default;
    Quote(const string &book, double sales_price): book_no(book), price(sales_price) {}

    string isbn() const {return book_no;}

    virtual double net_price(size_t n) const {return n * price;}
    virtual ~Quote() = default;

private :
    string book_no;
protected:
    double price = 0.0;
} ;

// 抽象基类
class Disc_quote : public Quote {
public:
    Disc_quote() = default;
    Disc_quote(const string &book, double price, size_t qty, double disc) : Quote(book, price), quntity(qty), discount(disc) {}

    double net_price(size_t) const = 0; // 纯虚函数  
protected:
    size_t quntity = 0; // 折扣适用的购买数量
    double discount = 0.0; // 表示折扣的小数值；
} ;


class Bulk_quto : public Disc_quote { // 因为Bulk_quoto在它的派生列表中使用了public关键字，因此我们完全可以把bulk_quto对象当成quoto的对象来使用
public:
    Bulk_quto() = default;
    Bulk_quto(const string &book, double price , size_t qty, double disc): Disc_quote(book, price, qty, disc) {}

    double net_price(size_t) const override;
} ;


// 计算并打印销售给定数量的某种书籍所得的费用


double print_total(ostream &os, const Quote &item, size_t n)
{
    // 当我们使用基类的引用或指针调用一个虚成员函数时会执行动态绑定
    double ret = item.net_price(n);
    os << "ISBN IS : " << item.isbn() << " sold : " << n << "total due : " << ret << endl;
    return ret;
}
