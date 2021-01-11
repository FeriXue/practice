#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Folders;

class Message {
    friend class Folders;

public:
    explicit Message(const string &strr = ""): contents(strr) {}
    Message(const Message&);
    Message &operator=(const Message&);
    ~Message();

    void save_to(Folders&);
    void remove_from(Folders&);

private:
    string contents;
    set<Folders *> folders;

    // 拷贝赋值运算符通常执行拷贝构造函数和析构函数也要做的工作，这种情况下，公共的工作应该放在private的工具函数中完成；
    // 将信息添加到指定的文件夹中
    void add_to_folders(const Message&);
    // 从所有文件夹中每个包含该信息的文件夹中删除该信息；
    void remove_from_folders();
} ;






int main()
{
    return 0;
}

