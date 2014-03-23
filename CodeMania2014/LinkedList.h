#pragma once

template<typename T>
struct LinkedList {
    struct ListNode {
        T item;
        ListNode* next;
        
        ListNode(T item, ListNode* next = nullptr)
        : item(item)
        , next(next)
        { }
        
        ~ListNode() {
            if(next) {
                delete next;
            }
        }
    };
    
    ListNode* head;
    ListNode* tail;
    
    LinkedList()
    : head(nullptr), tail(nullptr)
    { }
    
    ~LinkedList() {
        if(head) {
            delete head; // deletes the whole list
        }
    }
    
    void push(T item) {
        auto node = new ListNode(item);
        if(tail){
            tail->next = node;
        }
        tail = node;
        if(!head) {
            head = node;
        }
    }
    
    T pop() {
        if(head) {
            T ret = head->item;
            ListNode* oldhead = head;
            swap(head->next, head);
            
            oldhead->next = nullptr;
            delete oldhead;
            return ret;
        } else {
            return T();
        }
    }
    
    template<typename TCallback>
    void iterate(TCallback cb) {
        for(auto n = head; n; n = n->next) {
            if(n)
                cb(n->item);
        }
    }
};
