#include <iostream>
#include <string>
#include <utility>
#include <memory>

using namespace std;

class StrVec {
public:
    StrVec(): elements(nullptr), first_free(nullptr), cap(nullptr) {};
    StrVec(const StrVec&);
    StrVec& operator=(const StrVec&);
    ~StrVec();

    void push_back(const string&);
    size_t size() const {return first_free - elements; }
    size_t capacity() const {return cap - elements; }
    string *begin() const {return elements; }
    string *end() const {return first_free; }

private:
    static allocator<string> alloc;
    void chk_n_alloc()
    {
        if (size() == capacity()) {
            reallocate();
        }
    }

    pair<string*, string*> alloc_n_copy(const string*, const string *);

    void reallocate();
    void free();
    string *elements;
    string *first_free;
    string *cap;
} ;

void StrVec::push_back(const string &s)
{
    chk_n_alloc();
    alloc.construct(first_free++, s);
}

pair<string*, string*> StrVec::alloc_n_copy(const string *b, const string *e)
{
    auto data = alloc.allocate(e - b);
    return {data, uninitialized_copy(b, e, data)};
}

void StrVec::free()
{
    if (elements) {
        for (auto p = first_free; p != elements;) {
            alloc.destroy(--p); // destroy 函数会运行string的析构函数，string的析构函数会释放string自己分配的内存空间；
        }
        alloc.deallocate(elements, cap - elements);
    }
}


StrVec::StrVec(const StrVec &s)
{
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::~StrVec()
{
    free();
}

StrVec &StrVec::operator=(const StrVec &rhs)
{
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

void StrVec::reallocate()
{
    auto new_capacity = size() ? size() * 2 : 1;
    auto data = alloc.allocate(new_capacity);

    auto dest = data;
    auto elem = elements;

    for (size_t i = 0; i != size(); ++ i) {
        alloc.construct(dest++, std::move(*elem++));
    }

    free();

    elements = data;
    first_free = dest;
    cap = elements + new_capacity;
}








