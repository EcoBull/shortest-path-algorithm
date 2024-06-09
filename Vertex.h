#ifndef VERTEX_H
#define VERTEX_H

#ifndef NULL
#define NULL	0
#endif

#include "Edge.h"

class Vertex
{
private:
    // the key of this vertex
    int m_key;
    // the number of the edges from this vertex to others
    int m_size;
    // the head pointer for the linked list of the edges
    Edge* m_pEHead;
    // the next pointer for the linked list of the vertics
    Vertex* m_pNext;

public:
    Vertex();
    Vertex(int key);
    ~Vertex();

    /// <summary>
    /// set the next pointer of this vertex
    /// </summary>
    void SetNext(Vertex* pNext) { m_pNext = pNext; }
    /// <summary>
    /// get the key of this vertex
    /// </summary>
    ///
    /// <returns>
    /// the key of this vertex
    /// </returns>
    int GetKey() const { return m_key; }
    /// <summary>
    /// get the next pointer of this vertex
    /// </summary>
    ///
    /// <returns>
    /// the next pointer of this vertex
    /// </returns>
    Vertex* GetNext() const { return m_pNext; }

    /// <summary>
    /// get the number of the edges
    /// </summary>
    ///
    /// <returns>
    /// the number of the edges
    /// </returns>
    int Size() const { return m_size; }
    void SetSize(int size) { m_size = size; } //set size
    /// <summary>
    /// add edge with edgeNum at the end of the linked list for the edges
    /// </summary>
    ///
    /// <param name="edgeKey">
    /// the key of the vertex for the edge
    /// </param>
    /// <param name="weight">
    /// the weight of the edge
    /// </param>
    void AddEdge(int edgeKey, int weight) {
        Edge* newedge = new Edge(edgeKey, weight); //create new edge

        if (m_pEHead == NULL) {
            m_pEHead = newedge;
            return;
        } // when edge empty

        Edge* tempedge = new Edge(); //temp edge
        tempedge = m_pEHead;
        while (tempedge->GetNext() != NULL) {
            tempedge = tempedge->GetNext();
        } // find edge to insert

        tempedge->SetNext(newedge); //next edge push

        return;

    }
    /// <summary>
    /// get the head pointer of the edge
    /// </summary>
    ///
    /// <returns>
    /// the ehad pointer of the edge
    /// </returns>
    Edge* GetHeadOfEdge() const { return m_pEHead; }
    /// <summary>
    /// memory free for edges
    /// </summary>
    void Clear();
};

#endif
