#ifndef EDGE_H
#define EDGE_H

#ifndef NULL
#define NULL	0
#endif

class Edge
{
private:
    // the key of this edge
    int m_key;
    // the weight of this edge
    int m_weight;
    // the next pointer for the linked list of the edges
    Edge* m_pNext;

public:
	/// constructor
    Edge();

	/// copy constructor
    Edge(int key, int weight);

    /// set the next pointer of this edge
    void SetNext(Edge* pNext) { m_pNext = pNext; }

    /// get the key of this edge
    int GetKey() const { return m_key; }

    /// get the weight of this edge
    int GetWeight() const { return m_weight; }

    /// get the next pointer of this edge
    Edge* GetNext() const { return m_pNext; }
};

#endif