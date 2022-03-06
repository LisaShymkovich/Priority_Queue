#ifndef priority_queue_hpp
#define priority_queue_hpp

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

constexpr auto START_LINE = __LINE__;
enum class Priority
{
    high = 1,
    med,
    low
};
constexpr auto priorities_num = __LINE__ - START_LINE - 3;
const string priorities_names[] = { "High","Medium","Low"};

class PriorityQueue
{
public:
    struct Node
    {
    public:
        friend class PriorityQueue;
        
        int value;
        Priority priority;
        
        Node(int x, Priority pr)
        {
            value = x;
            priority = pr;
        }
        
    private:
        Node* next{nullptr};
    };
    
    PriorityQueue();
    PriorityQueue(const PriorityQueue&);
    PriorityQueue(PriorityQueue&& queue) noexcept;
    PriorityQueue& operator=(const PriorityQueue& queue);
    PriorityQueue& operator=(PriorityQueue&& queue) noexcept;
    ~PriorityQueue();
    bool IsEmpty() const;
    void Insert(int value, Priority priority);
    bool Pop();
    void Clone(const PriorityQueue&);
    void Erase();
    int GetHeadValue() const;
    Priority GetHeadPriority() const;
    int GetCountOfPriority(Priority priority_) const;
    int GetTotalSize() const;
    ostream& WriteToStream(ostream& s);
private:
    Node* head_;
    Node* rear_high;
    Node* rear_medium;
    Node* rear_low;
    int priority_sizes_[priorities_num];
    void Move(Node*& a, Node*& b);
};

#endif 
