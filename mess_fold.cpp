#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Folders;
// addmesg remmsg 分别完成在给定文件夹对象的消息集合中添加和删除信息的工作；

class Message {
    friend class Folders;
    friend void swap(Message &lhs, Message &rhs);

public:
    explicit Message(const string &strr = ""): contents(strr) {}
    Message(const Message&);
    Message &operator=(const Message);
    ~Message();

    // 将本message存放在给定的文件夹中
    void save_to(Folders&);
    // 删除本message；
    void remove_from(Folders&);

private:
    string contents;
    set<Folders *> folders;

    // 拷贝赋值运算符通常执行拷贝构造函数和析构函数也要做的工作，这种情况下，公共的工作应该放在private的工具函数中完成；
    // 将信息添加到指定的文件夹中
    void add_to_folders(const Message&);
    // 从所有文件夹中每个包含该信息的文件夹中删除该信息；
    void remove_from_folders();
    void move_folders(Message*);
} ;

void Message::move_folders(Message *m)
{
    // p479
}

void Message::save_to(Folders &f)
{
    folders.insert(&f);
    //f.addmsg(this);
}

// 关联容器的删除操作
// c.erase(k) 从c中删除每个关键字为k的元素，返回一个size_type值，指出删除元素的数量
// c.erase(p) 从c中删除迭代器p指定的元素。p必须指向c中一个真实元素，不能等于c.end()，返回一个指向p之后元素的迭代器，若p指向c中的尾元素，则返回c.end();
// c.erase(b, e)删除迭代器对b和e所表示范围中的元素，返回e
void Message::remove_from(Folders &f) 
{
    folders.erase(&f);
    //f.remsg(this);
}

// 当我们拷贝一个信息时，得到的副本信息应该与原信息出现在相同的文件夹中，因此我们必须遍历原信息文件夹指针集合，对每个包含原信息的文件夹添加一个指向新信息的
// 指针。拷贝构造函数和拷贝赋值运算符都需要做这个工作，因此我们定义一个函数来完成这个公共操作；
Message::Message(const Message &m): contents(m.contents), folders(m.folders) {
    add_to_folders(m);
}

void Message::add_to_folders(const Message &m)
{
    for (auto &f : m.folders) {
        cout << f << endl;
        // f->addmsg(this);
    }
}

void Message::remove_from_folders()
{
    for (auto &f : folders) {
        cout << f << endl;
        // f->remsg(this);
    }
}


Message::~Message()
{
    // 调用remove_from_folders确保没有任何文件夹保存正在销毁的信息的指针。编译器自动调用string的析构函数来释放contents，并调用set的析构函数来清理集合成员使用的内存;
    remove_from_folders();
}


/*Message &Message::operator=(const Message &rhs)
{
    remove_from_folders();
    contents = rhs.contents;
    folders = rhs.folders;
    add_to_folders(rhs);
    return *this;
} */

void swap(Message &lhs, Message &rhs)
{
    for (auto &f : lhs.folders) {
        f->remsg(&lhs);
    }
    for (auto &f : rhs.folders) {
        f->remsg(&rhs);          
    }                            

    swap(lhs.contents, rhs.contents);
    swap(lhs.folders, rhs.folders);

    for (auto &f : lhs.folders) {
        f->addmsg(&lhs);
    }
    for (auto &f : rhs.folders) {
        f->addmsg(&rhs);
    }
}

// swap版本的拷贝赋值运算符
Message &Message::operator=(Message rhs)
{
    swap(*this, rhs);
    return *this;
}






