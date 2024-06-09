#include "Edge.h"

Edge::Edge()
{
    m_key = -1; // -1 reset
    m_weight = 0;
    m_pNext = NULL;

}

Edge::Edge(int key, int weight)
{
    m_key = key;
    m_weight = weight;
    m_pNext = NULL;
}
