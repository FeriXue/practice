#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

// 管理string的一个类
// 实现一个新的集合类型的最简单的方法是使用某个标准库容器来管理元素。采用这种方法，我们可以借助标准库类型来管理元素所
// 使用的内存空间。
// 不能在一个Blob对象内直接保存vector，为了保证在多个对象之间共享数据我们将vector保存在动态内存中

class StrBlob {
    friend class StrBlobPtr;
public :
    typedef vector<string>::size_type size_type;
    StrBlob() = default;
    StrBlob(initializer_list<string> il);

private:
    shared_ptr<vector<string>> data;
    void chek(size_type i, const string &msg) const;
} ;


// 作为weak_ptr用途的一个展示，我们将为StrBlob类定义一个伴随指针类
// 保存一个weak_ptr，指向StrBlob的data成员, 这是初始化时提供给它的；
// 通过使用weak_ptr不会影响一个给定的strblob所指向的vector的生存期，但是可以阻止用户访问一个不再存在的vector的企图
class StrBlobPtr {
public:
    StrBlobPtr(): curr(0) {}
    StrBlobPtr(StrBlob &a, size_t sz = 0): wptr(a.data), curr(sz) {}
    string &deref() const;
    StrBlobPtr& incr();
    StrBlobPtr& operator++(); // 前置递增
    StrBlobPtr& operator--(); // 前置递减
    StrBlobPtr operator++(int); 
    StrBlobPtr operator--(int); 
    string& operator*() const;
    string* operator->() const;

private:
    shared_ptr<vector<string>> check(size_t, const string &) const;
    // 保存一个weak_ptr，意味着底层vector可能会被销毁
    weak_ptr<vector<string>> wptr;
    size_t curr; // 在数组中当前的位置；
} ;

shared_ptr<vector<string>> StrBlobPtr::check(size_t i, const string &msg) const
{
    auto ret = wptr.lock();
    if (!ret) {
        throw runtime_error("unbound StrBlobPtr");
    }
    if (i > ret->size()) {
        throw out_of_range(msg);
    }
    return ret;
}

string& StrBlobPtr::deref() const 
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

StrBlobPtr& StrBlobPtr::incr()
{
    check(curr, "increment past end of StrBlobPtr");
    ++ curr;
    return *this;
}

StrBlobPtr& StrBlobPtr::operator++()
{
    check(curr, "invrement past end of StrBlobPtr");
    ++curr;
    return *this;
}

StrBlobPtr& StrBlobPtr::operator--()
{
    --curr;
    check(curr, "decrement begin of StrBlobPtr");
    return *this;
}

StrBlobPtr StrBlobPtr::operator++(int)
{
    StrBlobPtr ret = *this;
    ++*this;
    return ret;
}

StrBlobPtr StrBlobPtr::operator--(int)
{
    StrBlobPtr ret = *this;
    --*this;
    return ret;
}

string& StrBlobPtr::operator*() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

// 调用解引用运算符并返回解引用结果元素的地址；
string* StrBlobPtr::operator->() const
{
    // 将实际工作委托给解引用运算符
    return & this->operator*();
}
