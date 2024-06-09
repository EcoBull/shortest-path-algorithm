#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <utility>
#include <vector>

template<typename TKey, typename TValue>
class MinHeap
{
private:
    // array for the elements which should be heap-sorted
    std::vector<std::pair<TKey, TValue>> m_vec;

public:
    MinHeap() {}
    ~MinHeap() {}
    /// <summary>
    /// insert key-value pair
    /// </summary>
    ///
    /// <param name="key">
    /// the key that is used for sorting
    /// </param>
    ///
    /// <param name="value">
    /// the value that is managed in this heap
    /// </param>
    void Push(TKey key, TValue value) {
        m_vec.push_back(make_pair(key, value));
        int parent, child;
        parent = m_vec.size() / 2 - 1;
        child = m_vec.size() - 1;
        //parent, child setting

        if (parent < 0) {
            return;
        } // parent negative return
        while (child > 0 && m_vec[parent].first > m_vec[child].first) {
            auto temp = m_vec[parent];
            m_vec[parent] = m_vec[child];
            m_vec[child] = temp;
            child = parent;
            parent = (parent - 1) / 2;
            //parent, child setting
        }
    }
    /// <summary>
    /// remove the minimum element
    /// </summary>
    void Pop() {
        if (m_vec.size() == 1) {
            m_vec.pop_back();
            return;
        }
        if (m_vec[0] == m_vec[m_vec.size() - 1])
            return;

        m_vec[0] = m_vec[m_vec.size() - 1];
        m_vec.pop_back();
        Heapify(0);
    }
    /// <summary>
    /// get the minimum element
    /// </summary>
    ///
    /// <returns>
    /// the minimum element
    /// </returns>
    std::pair<TKey, TValue> Top() {
        return m_vec[0];
    }
    /// <summary>
    /// get the key-value pair which the value is the same as the target
    /// </summary>
    ///
    /// <returns>
    /// the key-value pair which the value is the same as the target
    /// </returns>
    std::pair<TKey, TValue> Get(TValue target) {

        for (int i = 0; i < m_vec.size(); i++)
        {
            if (m_vec[i].second == target) return m_vec[i];
            //return m_vec[i]
        }
        return make_pair(IN_FINITY, IN_FINITY);
    }
    /// <summary>
    /// check whether this heap is empty or not
    /// </summary>
    ///
    /// <returns>
    /// true if this heap is empty
    /// </returns>
    bool IsEmpty() {
        if (m_vec.size() == 0) {
            return true;
        }
        else
            return false;
    }
    /// <summary>
    /// change the key of the node which the value is the target.<para/>
    /// In general, the newKey should be smaller than the old key.<para/>
    /// </summary>
    ///
    /// <parma name="target">
    /// the target to change the key
    /// </param>
    ///
    /// <param name="newKey">
    /// new key for the target
    /// </param>
    void DecKey(TValue target, TKey newKey) {

        int i = 0;
        for (i = 0; i < m_vec.size(); i++) {
            if (m_vec[i].second == target)
                break;
            //find m_vec[] target
        }

        if (i == m_vec.size())
            return;//not target

        m_vec[i] = make_pair(newKey, target);
        
        while (i != 0 && m_vec[(i - 1) / 2].first > m_vec[i].first) {
            exchange(m_vec[i], m_vec[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

private:
    /// <summary>
    /// heap-sort, heapify.<para/>
    /// this function can be called recursively
    /// </summary>
    void Heapify(int index) {
        int size = m_vec.size();
        int child_l = index * 2 + 1;
        int child_r = index * 2 + 2;
        int S_variable = index;
        if (child_l < (int)size && m_vec[child_l].first < m_vec[S_variable].first) // index change condition
            S_variable = child_l;
        else if (child_r < (int)size && m_vec[child_r].first < m_vec[S_variable].first) // index change condition
            S_variable = child_r;
        if (S_variable != index) 
        {
            exchange(m_vec[index], m_vec[S_variable]);
            Heapify(S_variable);
        }
    }

    void exchange(pair<TKey, TValue>& a, pair<TKey, TValue>& b)
    {
        pair<TKey, TValue> s = a;
        a = b;
        b = s;
    } // exchange value
};

#endif
