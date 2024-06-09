#include "Graph.h"
#include "Stack.h"
#include "MinHeap.h"
#include <set>
#include <algorithm>
#include <vector>

#define BFS_FIRST_PATH

Graph::Graph()
{
    m_pVHead = NULL;
    m_vSize = 0;
    // TODO: implement
}
Graph::~Graph()
{
    m_pVHead = NULL;
    m_vSize = 0;
    // TODO: implement
}

void Graph::AddVertex(int vertexKey)
{
    Vertex* newvertex = new Vertex(vertexKey); //create new vertex

    if (m_pVHead == NULL) {
        m_pVHead = newvertex;
        return;
    } //when vertex empty

    Vertex* tempvertex = new Vertex(); // temp vertex
    tempvertex = m_pVHead;
    while (tempvertex->GetNext() != NULL) {
        tempvertex = tempvertex->GetNext();
    } //find vertex to insert
    
    tempvertex->SetNext(newvertex); //next vertex push

    return;
}

void Graph::AddEdge(int startVertexKey, int endVertexKey, int weight)
{
    if (m_pVHead == NULL) {
        cout << "error : no vertex" <<endl;
        return;
    } // does not exist
    

    Vertex* tempvertex = new Vertex(); // temp vertex
    tempvertex = m_pVHead;

    while (tempvertex->GetKey() != startVertexKey)
    {
        tempvertex = tempvertex->GetNext();
    } // find vertex to insert

    tempvertex->AddEdge(endVertexKey, weight); // add edge
    tempvertex->SetSize(tempvertex->Size() + 1); // add size
    
    return;
}

Vertex* Graph::FindVertex(int key)
{
    Vertex* temp;
    temp = m_pVHead;
    while (temp->GetKey() != key) {
        temp = temp->GetNext();
        if (temp == NULL) break;
    }// find vertex

    return temp;
}

Edge* Graph::FindEdge(int startVertexKey, int endVertexKey)
{
    Edge* edge_temp;
    Vertex* vertex_temp;

    vertex_temp = FindVertex(startVertexKey); //find startVertexKey
    edge_temp = vertex_temp->GetHeadOfEdge();
    while (1) {
        if (edge_temp->GetKey() == endVertexKey) {
            return edge_temp; // find edge
        }
        if (edge_temp->GetNext() == NULL) {
            cout << "not exist path" << endl;
            return 0; //not exist path
        }
        edge_temp = edge_temp->GetNext(); // next edge
    }
}

void Graph::Clear() 
{
    Vertex* vertex = m_pVHead;
    m_vSize = 0;
    m_pVHead = NULL;
    delete vertex;
    //clear
}

void Graph::Print(std::ofstream& fout)
{
    Vertex* tempvertex = new Vertex(); // temp vertex
    Edge* tempedge = new Edge(); //temp edge
    tempvertex = m_pVHead;

    for (int i = 0; i < m_vSize; i++) {
        tempedge = tempvertex->GetHeadOfEdge();
        for (int j = 0; j < m_vSize; j++) {
            if (tempedge->GetKey() == j) {
                cout << tempedge->GetWeight() << " ";  // weight print
                fout << tempedge->GetWeight() << " ";  // weight print

                if(tempedge->GetNext() != NULL)
                    tempedge = tempedge->GetNext();
            } // key print
            else {
                cout << "0 ";
                fout << "0 ";
            }
        }
        cout << endl;
        fout << endl;

        tempvertex = tempvertex->GetNext();
    } // matrix print 

}

bool Graph::IsNegativeEdge() 
{
    Vertex* temp_vertex = m_pVHead;
    Edge* temp_edge;
    while (temp_vertex != NULL) {
        temp_edge = temp_vertex->GetHeadOfEdge();
        while (temp_edge != NULL) {
            if (temp_edge->GetWeight() < 0) {
                return true; //exist negative edge
            }
            temp_edge = temp_edge->GetNext(); //get next edge point
        }
        temp_vertex = temp_vertex->GetNext(); //get next vertex point
    }
    
    return false; //not exist negative edge
}

std::vector<int> Graph::FindPathDfs(int startVertexKey, int endVertexKey)
{
    vector<int> path; //result path
    Stack<int> stack;
    bool* visit = new bool[m_vSize];
    fill(visit, visit + m_vSize, false); //fill visit false
    //visit[startVertexKey] = true;

    Vertex* tempvertex = FindVertex(startVertexKey);
    
    int vertex_key = startVertexKey;
    int count = 0;
    stack.Push(startVertexKey);
    while (1) {
        vertex_key = stack.Top();
        if (visit[vertex_key] == false) {
            path.push_back(vertex_key);
        }
        if (path.back()== endVertexKey)
            break; // end, find path
        if (visit[vertex_key] == false)
            visit[vertex_key] = true;

        Vertex* findvertex = FindVertex(vertex_key); // find
        Edge* edge = findvertex->GetHeadOfEdge();
        while (edge != NULL) { //repeat
            if (!visit[edge->GetKey()]) {
                stack.Push(edge->GetKey());
                count++;
            }
            edge = edge->GetNext();
        }
        if (count == 0) {
            path.pop_back();
            stack.Pop();
        }
    }
    delete[] visit;
    
    return path;
}

std::vector<int> Graph::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey)
{
    if (IsNegativeEdge() == true) {
        return vector<int>(-1);
    } //error negativeEdge

    vector<int> result_path; //result path
    vector<int> distance(m_vSize, IN_FINITY);
    vector<int> visit(m_vSize, 0);
    vector<int> path(m_vSize, -1);
    //setting
    
    distance[startVertexKey] = 0; //initialize to 0, start vertexKey
    Edge* temp_edge;

    int pre_path = startVertexKey;
    int pre_weight = 0;
    vector<int> sort_distance;

    for (int i = 0; i < m_vSize; i++) {
        temp_edge = FindVertex(pre_path)->GetHeadOfEdge();
        visit[pre_path] = 1;
        for (int j = 0; j < FindVertex(pre_path)->Size(); j++) {
            if (distance[temp_edge->GetKey()] > pre_weight + temp_edge->GetWeight()) {
                distance[temp_edge->GetKey()] = pre_weight + temp_edge->GetWeight(); //Save min weight
                path[temp_edge->GetKey()] = pre_path; //Save pre_path 
            }
            temp_edge = temp_edge->GetNext();
        }

        int min = IN_FINITY;
        int min_index =0;
        for (int k = 0; k < m_vSize; k++) {
            if (visit[k] == 0 && min > distance[k]) {
                min = distance[k];
                min_index = k;
                //find min distance
            }
        }

        if (min_index == endVertexKey) {
            int start = min_index;
            while (start != startVertexKey) {
                result_path.insert(result_path.begin(), start); //first insert vertex
                start = path[result_path.front()]; //Find route
                //reverse route search
            }
            result_path.insert(result_path.begin(), start);
            return result_path; //reverse path
        }

        pre_weight = distance[min_index];
        pre_path = min_index;
        //set pre_weight, pre_path
    }
}

std::vector<int> Graph::FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey)
{
    /*
    if (IsNegativeEdge() == true) {
        return vector<int>(-1);
    } //error negativeEdge

    vector<vector<int> > result_path(m_vSize, vector<int>(m_vSize, IN_FINITY));//MH_DJK_path of all vertex
    vector<int> distance(m_vSize, IN_FINITY);
    vector<int> visit(m_vSize, 0);
    vector<int> path(m_vSize, -1);
    MinHeap<int, int> minheap;
    //setting

    distance[startVertexKey] = 0; //initialize to 0, start vertexKey
    for (int i = 0; i != m_vSize; i++) //
    {
        result_path[i][0] = startVertexKey;
        minheap.Push(distance[i], i);
    }//setting

    Edge* temp_edge;

    int pre_path = startVertexKey;
    int pre_path_u;
    int pre_weight = 0;

    while (!minheap.IsEmpty()) {
        pair<int, int> temp_heap = minheap.Top();
        minheap.Pop(); //

        pre_path_u = temp_heap.second;
        temp_edge = FindVertex(pre_path_u)->GetHeadOfEdge();

        while (temp_edge != NULL) {
            pre_path = temp_edge->GetKey();
            pre_weight = temp_edge->GetWeight();
            //get key, weight

            if (distance[pre_path] > distance[pre_path_u] + pre_weight) {
                if (minheap.Get(pre_path) != make_pair(IN_FINITY, IN_FINITY) && distance[pre_path_u] != IN_FINITY && pre_weight + distance[pre_path_u] < distance[pre_path]) {

                    distance[pre_path] = distance[pre_path_u] + pre_weight;
                    minheap.DecKey(pre_path, distance[pre_path]);
                    //save path distance
                }
                int k = 0;
                for (k = 0; k< m_vSize-1; k++) {
                    result_path[pre_path][k] = result_path[pre_path_u][k];
                }
                result_path[pre_path][k] = pre_path;
                //save result_path 
            }
            temp_edge = temp_edge->GetNext(); //next edge path
        }
    }

    vector<int> result;
    while (1) {
        result.push_back(endVertexKey);
        //endVertexKey = result_path[endVertexKey][0];
        if (startVertexKey == endVertexKey) {
            return result;
        }
        for (int i = 0; i < m_vSize; i++) {
            if (result_path[endVertexKey][i] == endVertexKey) {
                endVertexKey = i;
                break;
            }
        }

    }


    return result_path[endVertexKey]; //return end vertexkey path
    
    //return vector<int>(0);
    */
    if (IsNegativeEdge()) 
        return vector<int>(0, 0);
    MinHeap<int, int> minheap;
    vector<int> distance(m_vSize, IN_FINITY); // distance of all vertex
    vector<vector<int> > result_path(m_vSize, vector<int>(m_vSize, IN_FINITY));
    //result_path initial

    for (int i = 0; i != m_vSize; i++) // loop m_vSize when
    {
        result_path[i][0] = startVertexKey;//initialize start
        minheap.Push(distance[i], i); //push
    }
    distance[startVertexKey] = 0;
    minheap.DecKey(startVertexKey, distance[startVertexKey]);

    while (!minheap.IsEmpty()) //not empty
    {
        pair<int, int> tmp = minheap.Top();
        minheap.Pop(); // pop

        int pre_vertex_key = tmp.second;
        Edge* temp_edge = FindVertex(pre_vertex_key)->GetHeadOfEdge(); // head edge

        while (temp_edge != NULL) // loop when edge existing
        {
            int pre_key = temp_edge->GetKey();
            int weight = temp_edge->GetWeight();
            if (distance[pre_key] > distance[pre_vertex_key] + weight) // new short path
            {
                if (minheap.Get(pre_key) != make_pair(IN_FINITY, IN_FINITY) && distance[pre_vertex_key] != IN_FINITY && weight + distance[pre_vertex_key] < distance[pre_key]) // identify path condtion
                {
                    distance[pre_key] = distance[pre_vertex_key] + weight; 
                    minheap.DecKey(pre_key, distance[pre_key]); 
                    //Save path distance
                }
                int i = 0;
                for (i = 0; IN_FINITY != result_path[pre_vertex_key][i]; i++)
                {
                    result_path[pre_key][i] = result_path[pre_vertex_key][i];
                    //Save result_path
                    if (i == m_vSize - 1) break;
                }
                result_path[pre_key][i] = pre_key;
            }
            temp_edge = temp_edge->GetNext(); //next edge
        }
    }
    return result_path[endVertexKey];
}

std::vector<int> Graph::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey)
{
    vector<int> distance(m_vSize, IN_FINITY);  //Reset to infinite distance, IN_FINITY = 99999
    vector<int> result_path; // result path
    vector<vector<int> > result(m_vSize, vector<int>(m_vSize, IN_FINITY));
    vector<int> visit(m_vSize, IN_FINITY);

    vector<vector<int>> length(m_vSize, vector<int>(m_vSize, INFINITY));
    //initial INFINITY

    distance[startVertexKey] = 0; //startpoint 0

    int nega_cycle = 0; // negative cycle 0: not exist, 1: exist

    for (int i = 0; i < m_vSize; i++)//size-cycle
    {
        nega_cycle = false;
        for (int j = 0; j < m_vSize; j++) {//all vertex approach
            Edge* temp = FindVertex(j)->GetHeadOfEdge(); // head edge 
            while (temp != NULL) // loop when edge existing
            {
                int v = temp->GetKey();
                int weight = temp->GetWeight();
                if (distance[j] != IN_FINITY && distance[v] > distance[j] + weight)// select min
                {
                    distance[v] = distance[j] + weight;
                    nega_cycle = true;
                    int k;
                    for (k = 0; IN_FINITY != result[j][k] ; k++)
                    {
                        result[v][k] = result[j][k];
                        if (k == m_vSize - 1)
                            break;
                    }
                    result[v][k] = v;
                }
                temp = temp->GetNext(); // next
            }
        }
    }

    if (nega_cycle == 1) {
        return vector<int>(-1);
    }//negative cycle


    Vertex* temp_vertex;
    Edge* temp_edge;
    temp_vertex = FindVertex(startVertexKey);

    for (int j = 0; j < m_vSize; j++) {
        temp_edge = temp_vertex->GetHeadOfEdge();
        for (int k = 0; k < temp_vertex->Size(); k++) {
            int next = temp_edge->GetKey();
            int weight = temp_edge->GetWeight();
            //setting next weight

            if (distance[next] > distance[j] + weight) {

                distance[next] = distance[j] + weight; //Save weight
                visit[next] = j; //Save pre_path 
            }
            temp_edge = temp_edge->GetNext(); // next edge
        }
        temp_vertex = temp_vertex->GetNext(); //nest vertex

    }

    int end = endVertexKey;
    result_path.push_back(end);
    while (1) {
        result_path.insert(result_path.begin(), visit[end]);
        if (visit[end] == startVertexKey) {
            return result_path;
        }
        end = visit[end];
    }
    //path visit 
    //return result_path

    /*
    vector<int> distance(m_vSize, IN_FINITY); // Reset to infinite distance, IN_FINITY = 99999
    vector<vector<int>> result_path(m_vSize, vector<int>(m_vSize, IN_FINITY)); // Reset to infinite path
    //look 2D array

    for (int i = 0; i < m_vSize; i++) {
        result_path[i][0] = startVertexKey;
    } // reset startvertexkey

    int negative_cycle = 0; 
    // negative cycle, 0: not exist 1: exist 
    Edge* temp_edge;

    for (int i = 0; i < m_vSize; i++) {
        negative_cycle = 0;
        for (int j = 0; j < m_vSize; j++) {
            temp_edge = FindVertex(j)->GetHeadOfEdge();
            while (temp_edge != NULL) {
                int key = temp_edge->GetKey();
                int weight = temp_edge->GetWeight();
                if (distance[key] > distance[j] + weight) {
                    distance[key] = distance[j] + weight;
                    negative_cycle = 1;
                    int k = 0; 
                    for (k = 0; k < m_vSize - 1; k++) {
                        result_path[key][k] = result_path[j][k];
                    }
                    result_path[key][k] = key;
                }
                temp_edge = temp_edge->GetNext();
            }
        }
    }

    if (negative_cycle == 1) {
        return vector<int>(-1);
    }//negative cycle

    return result_path[endVertexKey];
    */
}

std::vector<vector<int>> Graph::FindShortestPathFloyd()
{
    vector<int> distance(m_vSize, IN_FINITY); // Reset to infinite distance, IN_FINITY = 99999
    vector<vector<int>> distance_v(m_vSize, vector<int>(m_vSize, IN_FINITY));
    vector<vector<int>> result_path(m_vSize, vector<int>(m_vSize, IN_FINITY));
    // Reset to infinite path

    Vertex* temp_vertex = m_pVHead;
    Edge* temp_edge;

    for (int i = 0; i < m_vSize; i++) {
        temp_edge = temp_vertex->GetHeadOfEdge();
        for (int j = 0; j < m_vSize; j++) {
            if (i == j) {
                distance_v[i][j] = 0;
                result_path[i][j] = 0; // array col == row, 0
            }
            else if (temp_edge->GetKey() == j) {
                distance_v[i][j] = temp_edge->GetWeight();
                result_path[i][j] = temp_edge->GetWeight(); //save weihgt
                if (temp_edge->GetNext() != NULL)
                    temp_edge = temp_edge->GetNext(); // next edge
            } // key print
        }
        temp_vertex = temp_vertex->GetNext(); //next vertex
    } // matrix A0 setting


    int negative_cycle = 0; // negative cycle, 0: not exist 1: exist 
    /*
    for (int i = 0; i < m_vSize; i++) {
        for (int j = 0; j < m_vSize; j++) {
            distance_v[j][0] = i;
        }
        
        distance[i] = 0;
        for (int j = 0; j < m_vSize; j++) {
            negative_cycle = 0;

            for (int k = 0; k < m_vSize; k++) {

                temp_edge = FindVertex(j)->GetHeadOfEdge();
                while (temp_edge != NULL)
                {
                    int key = temp_edge->GetKey();
                    int weight = temp_edge->GetWeight();
                    if (distance[j] != IN_FINITY && distance[key] > distance[k] + weight) {
                        distance[key] = distance[k] + weight;
                        negative_cycle = 1;
                        int m = 0;
                        for (m = 0; m < m_vSize - 1; m++) {
                            distance_v[key][m] = distance_v[k][m];
                        }
                        distance_v[key][m] = key;
                    }
                    temp_edge = temp_edge->GetNext();

                }
            }
        }
    }
    */

    if (negative_cycle == 1) {
        return vector<vector<int>>(-1, vector<int>(-1));
    }
    
    for (int k = 0; k < m_vSize; k++) {
        for (int i = 0; i < m_vSize; i++) {
            for (int j = 0; j < m_vSize; j++) {
                if (result_path[i][k] + result_path[k][j] < result_path[i][j]) {
                    result_path[i][j] = result_path[i][k] + result_path[k][j]; 
                    //min distance select
                }
            }
        }
    } //floyd's shortest path
    
    return result_path;
}
