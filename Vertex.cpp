#include "Vertex.h"

Vertex::Vertex()
{
    m_key = -1; // -1 reset
    m_size = 0;
    m_pEHead = NULL;
    m_pNext = NULL;
}

Vertex::Vertex(int key)
{
    m_key = key;
    m_size = 0;
    m_pEHead = NULL;
    m_pNext = NULL;
}

Vertex::~Vertex()
{
}

void Vertex::Clear()
{
    return;
}
