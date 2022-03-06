#include "priority_queue.hpp"
#include "priority_queue.hpp"

PriorityQueue::PriorityQueue()
{
    head_ = nullptr;
    rear_high = nullptr;
    rear_medium = nullptr;
    rear_low = nullptr;
    for (int i = 0; i < priorities_num; i++)
    {
        priority_sizes_[i] = 0;
    }
}

PriorityQueue::PriorityQueue(const PriorityQueue& queue)
{
    head_ = nullptr;
    rear_high = nullptr;
    rear_medium = nullptr;
    rear_low = nullptr;
    for (int i = 0; i < priorities_num; i++)
    {
        priority_sizes_[i] = 0;
    }
    Clone(queue);
}

PriorityQueue::PriorityQueue(PriorityQueue&& queue) noexcept
{
    Move(head_, queue.head_);
    Move(rear_low, queue.rear_low);
    Move(rear_medium, queue.rear_medium);
    Move(rear_high, queue.rear_high);
    for (int i = 0; i < priorities_num; i++)
    {
        priority_sizes_[i] = queue.priority_sizes_[i];
    }
}

PriorityQueue& PriorityQueue::operator=(const PriorityQueue& queue)
{
    if (&queue != this)
    {
        Erase();
        Clone(queue);
    }
    return *this;
}

PriorityQueue& PriorityQueue::operator=(PriorityQueue&& queue) noexcept
{
    if (&queue != this)
    {
        Move(head_, queue.head_);
        Move(rear_low, queue.rear_low);
        Move(rear_medium, queue.rear_medium);
        Move(rear_high, queue.rear_high);
        for (int i = 0; i < priorities_num; i++)
        {
            priority_sizes_[i] = queue.priority_sizes_[i];
        }
    }
    return *this;
}

PriorityQueue::~PriorityQueue()
{
    Erase();
}


void PriorityQueue::Insert(int value, Priority priority)
{
    Node* el = new Node(value, priority);
    switch (priority)
    {
        case Priority::high:
            if (rear_high != nullptr)
            {
                el->next = rear_high->next;
                rear_high->next = el;
            }
            else
            {
                el->next = head_;
                head_ = el;
            }
            rear_high = el;
            break;
        case Priority::med:
            if (rear_medium != nullptr)
            {
                el->next = rear_medium->next;
                rear_medium->next = el;
            }
            else
            {
                if (rear_high != nullptr)
                {
                    el->next = rear_high->next;
                    rear_high->next = el;
                }
                else
                {
                    el->next = head_;
                    head_ = el;
                }
            }
            rear_medium = el;
            break;
        case Priority::low:
            if (rear_low != nullptr)
            {
                el->next = rear_low->next;
                rear_low->next = el;
            }
            else
            {
                if (rear_medium != nullptr)
                {
                    rear_medium->next = el;
                }
                else
                {
                    if (rear_high != nullptr)
                    {
                        rear_high->next = el;
                    }
                    else
                    {
                        head_ = el;
                    }
                }
            }
            rear_low = el;
            break;
        default:
            throw runtime_error("Неправильно введен приоритет!");
            break;
    }
    
    priority_sizes_[int(priority)-1]++;
}

bool PriorityQueue::IsEmpty() const
{
    return (head_ == nullptr);
}


bool PriorityQueue::Pop()
{
    if (IsEmpty())
    {
        return false;
    }
    else
    {
        Node* tmp = head_;
        int head_priority_idx = int(tmp->priority) - 1;
        priority_sizes_[head_priority_idx]--;
        if (tmp == rear_high)
        {
            rear_high = nullptr;
        }
        if (tmp == rear_medium)
        {
            rear_medium = nullptr;
        }
        if (tmp == rear_low)
        {
            rear_low = nullptr;
        }
        head_ = head_->next;
        delete tmp;
        return true;
    }
}

void PriorityQueue::Clone(const PriorityQueue& other)
{
    if (other.GetTotalSize() > 0)
    {
        Node* _tmp = other.head_;
        while (_tmp->next != nullptr)
        {
            Insert(_tmp->value,_tmp->priority);
            _tmp = _tmp->next;
        }
    }
}

void PriorityQueue::Erase()
{
    while (Pop())
    {
        
    }
}

int PriorityQueue::GetHeadValue() const
{
    if (head_ != nullptr)
    {
        return head_->value;
    }
    else
    {
        throw runtime_error("Очередь пуста!");
    }
}

Priority PriorityQueue::GetHeadPriority() const
{
    if (head_ != nullptr)
    {
        return head_->priority;
    }
    else
    {
        throw runtime_error("Очередь пуста!");
    }
}

void PriorityQueue::Move(Node*& a, Node*& b)
{
    a = b;
    b = nullptr;
}

int PriorityQueue::GetCountOfPriority(Priority priority_) const
{
    return priority_sizes_[int(priority_) - 1];
}

int PriorityQueue::GetTotalSize() const
{
    int size = 0;
    for (int i = 0; i < priorities_num; i++)
    {
        size += priority_sizes_[i];
    }
    return size;
}

ostream& PriorityQueue::WriteToStream(ostream& s)
{
    if (!IsEmpty())
    {
        Node* _tmp = head_;
        while (_tmp != nullptr)
        {
            s << _tmp->value;
            if (_tmp->next != nullptr)
            {
                s << "   ";
            }
            _tmp = _tmp->next;
        }
    }
    else
    {
        s << "Очередь пуста!";
    }
    return s;
}



