#ifndef STACK_H
#define STACK_H

#ifndef NULL
#define NULL    0
#endif

template <typename T>
class Stack
{
private:
    class StackNode
    {
    public:
        T Data;
        StackNode* pNext;

        StackNode(T data) : Data(data), pNext(NULL) {}
    };

private:
    // the head pointer of the stack and queue
    StackNode* m_pTop;

public:
    Stack() {
        m_pTop = NULL;
    }
    ~Stack() {


    }

    /// <summary>
    /// push the data into this stack and queue
    /// </summary>
    ///
    /// <param name="data">
    /// a data to push into this stack and queue
    /// </param>
    void Push(T data) {
        StackNode* node = new StackNode(data); // new alloc

        if (m_pTop==NULL) {
            m_pTop = node;
        }
        else {
            StackNode* temp = m_pTop;
            node->pNext = m_pTop;
            m_pTop = node;
            //change m_pTop
        }
        
    }
    /// <summary>
    /// pop(remove) the last-in data from this stack and queue
    /// </summary>
    void Pop() {
        if (m_pTop == NULL) {
            cout << "error: stack NULL" << endl;
            return;
        }

        StackNode* temp = m_pTop->pNext;
        delete m_pTop; //delete m_pTop
        m_pTop = temp;  //change m_pTop
        
    }
    /// <summary>
    /// get the last-in data of this stack and queue
    /// </summary>
    /// 
    /// <returns>
    /// the last-in data of this stack and queue
    /// </returns>
    T Top() {
        return m_pTop->Data;
    }
    /// <summary>
    /// check whether this stack and queue is empty or not.
    /// </summary>
    ///
    /// <returns>
    /// true if this stack and queue is empty.
    /// false otherwise.
    /// </returns>
    bool IsEmpty() {
        if (m_pTop == NULL) {
            return true;
        }
        else {
            return false;
        }
    }
};

#endif
