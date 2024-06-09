#include "Manager.h"
#include <vector>
#include <cstring>
#include <algorithm>

Manager::~Manager()
{
    if (fout.is_open())
        fout.close();

    if (ferr.is_open())
        ferr.close();
}


void Manager::Run(const char* filepath)
{
    fout.open(RESULT_LOG_PATH); //result log.txt
    ferr.open(ERROR_LOG_PATH); //result error.txt
    fin.open(filepath); //file open

    // TODO: implement
    

    char cmd[64];

    while (!fin.eof()) {
        fin.getline(cmd, 40);
        char* tmp = strtok(cmd, " ");
        if (tmp == NULL) continue;
        cout << "========" << cmd << "========" << endl;
        fout << "========" << cmd << "========" << endl;

        if (tmp[0] == '/') {
            continue;
        } //remark

        //////////////////LOAD//////////////////////////
        if (strcmp(tmp, "LOAD") == 0) {
            char* txt = strtok(NULL, " ");
            if (txt == NULL) {
                PrintError(LoadFileNotExist);
                continue;
            }
            Result success = Load(txt);

            if (success == 0) { // 0: success
               // cout << "========" << cmd << "========" << endl;
                cout << "Success" << endl;
                cout << "=================" << endl;
                fout << "Success" << endl;
                fout << "=================" << endl;
            }

            PrintError(success);
        }

        //////////////////PRINT//////////////////////////
        else if (strcmp(tmp, "PRINT") == 0) {
            Result success = Print();

            PrintError(success);
        }

        //////////////////BFS?//////////////////////////
        else if (strcmp(tmp, "BFS") == 0) {
            int start, end;
            char* tmp = strtok(NULL, " ");
            if (tmp == NULL) {
                PrintError(VertexKeyNotExist);
                continue;
            }
            start = atoi(tmp);
            tmp = strtok(NULL, " ");
            if (tmp == NULL) {
                PrintError(VertexKeyNotExist);
                continue;
            }
            end = atoi(tmp);
            //lack of vertex

            Result success = FindPathDfs(start, end);

            PrintError(success);
        }

        //////////////////DIJKSTRA//////////////////////////
        else if (strcmp(tmp, "DIJKSTRA") == 0) {
            int start, end;
            char* tmp = strtok(NULL, " ");
            if (tmp == NULL) {
                PrintError(VertexKeyNotExist);
                continue;
            }
            start = atoi(tmp);
            tmp = strtok(NULL, " ");
            if (tmp == NULL) {
                PrintError(VertexKeyNotExist);
                continue;

            }
            end = atoi(tmp);
            //lack of vertex

            Result success = FindShortestPathDijkstraUsingSet(start, end);

            PrintError(success);
        }

        //////////////////DIJKSTRAMIN//////////////////////////
        else if (strcmp(tmp, "DIJKSTRAMIN") == 0) {
            int start, end;
            char* tmp = strtok(NULL, " ");
            if (tmp == NULL) {
                PrintError(VertexKeyNotExist);
                continue;
            }
            start = atoi(tmp);
            tmp = strtok(NULL, " ");
            if (tmp == NULL) {
                PrintError(VertexKeyNotExist);
                continue;

            }
            end = atoi(tmp);
            //lack of vertex

            Result success = FindShortestPathDijkstraUsingMinHeap(start, end);

            PrintError(success);

        }

        //////////////////BELLMANFORD//////////////////////////
        else if (strcmp(tmp, "BELLMANFORD") == 0) {
            int start, end;
            char* tmp = strtok(NULL, " ");
            if (tmp == NULL) {
                PrintError(VertexKeyNotExist);
                continue;
            }
            start = atoi(tmp);
            tmp = strtok(NULL, " ");
            if (tmp == NULL) {
                PrintError(VertexKeyNotExist);
                continue;
            }
            end = atoi(tmp);
            //lack of vertex

            Result success = FindShortestPathBellmanFord(start, end);

            PrintError(success);

        }

        //////////////////FLOYD//////////////////////////
        else if (strcmp(tmp, "FLOYD") == 0) {

            Result success = FindShortestPathFloyd();

            PrintError(success);

        }

        // not exist
        else {
            cout << "not command" << endl;
            fout << "not command" << endl;
            cout << "=================" << endl;
            fout << "=================" << endl;
        }
    }

}

void Manager::PrintError(Result result)
{
    //ferr << "Error code: " << result << std::endl;
    cout << endl << "=================" << endl;
    cout << "Error code: " << result << std::endl;
    cout << "=================" << endl << endl;

    fout << endl << "=================" << endl;
    fout << "Error code: " << result << std::endl;
    fout << "=================" << endl << endl;
}

/// <summary>
/// make a graph
/// </summary>
///
/// <param name="filepath">
/// the filepath to read to make the graph
/// </param>
///
/// <returns>
/// Result::Success if load is successful.
/// Result::LoadFileNotExist if file is not exist.
/// </returns>
Result Manager::Load(const char* filepath)
{
    // TODO: implement
    std::ifstream fdata;

    fdata.open(filepath); //mapdata file open

    if (!fdata) {
        return LoadFileNotExist;
    }

    char cmd[64];

    fdata.getline(cmd, 64);
    char* tmp = strtok(cmd, " ");
    m_graph.SetSize(atoi(tmp));
    //cout << tmp << endl;

    int n = atoi(tmp);
    for (int i = 0; i < n; i++) {
        fdata.getline(cmd, 64);

        char* shop = strtok(cmd, "/");
        //shop = strtok(cmd, "/");
        //cout << shop << endl;
        m_graph.AddVertex(i); // add vertex
        store[i] = shop;

        for (int j = 0; j < n; j++) {
            char* tmp_w = strtok(NULL, " "); //strtok
            //cout << tmp_w << endl;
            if (atoi(tmp_w) == 0) //when weight = 0
                continue;
            m_graph.AddEdge(i, j, atoi(tmp_w)); //add edge
        }
    }

    return Success;
}
/// <summary>
/// print out the graph as matrix form
/// </summary>
///
/// <returns>
/// Result::Success if the printing is successful
/// Result::GraphNotExist if there is no graph
/// </returns>
Result Manager::Print()
{
    // TODO: implement
    if (m_graph.Size()==0){
        return GraphNotExist; // graph not exist
    }

    m_graph.Print(fout); //print matrix
    
    cout << "=================" << endl;
    fout << "=================" << endl;

    return Success;
}
/// <summary>
/// find the path from startVertexKey to endVertexKey with BFS (stack and queue)
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindPathDfs(int startVertexKey, int endVertexKey)
{
    // TODO: implement
    if (m_graph.Size() <= startVertexKey || m_graph.Size() <= endVertexKey) {
        return InvalidVertexKey; // not exist vertex in graph
    }
    if (0 > startVertexKey || 0> endVertexKey) {
        return InvalidVertexKey; // not exist vertex in graph
    }
    
    vector<int> v;
    v = m_graph.FindPathDfs(startVertexKey, endVertexKey);

    cout << "shortest path: ";
    fout << "shortest path: ";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
        fout << v[i] << " ";
    }
    cout << endl; 
    fout << endl;
    //print path 

    vector<int> v_sort;
    v_sort = v;
    sort(v_sort.begin(), v_sort.end()); //sort ascending, declare algorithm header

    cout << "sorted nodes: ";
    fout << "sorted nodes: ";
    for (int i = 0; i < v_sort.size(); i++) {
        cout << v_sort[i] << " ";
        fout << v_sort[i] << " ";
    }
    cout << endl;
    fout << endl;
    //print sort path

    int cost = 0;
    for (int i = 0; i < v.size() - 1; i++) {
        cost = cost + m_graph.FindEdge(v[i], v[i + 1])->GetWeight();
    } //add findedge weight
    cout << "path length: " << cost << endl;
    fout << "path length: " << cost << endl;
    //print path length

    const char* compared = store[0].c_str();
    for (int i = 1; i < v_sort.size(); i++) {
        compared = Compare(compared, store[i].c_str());
    }

    cout << "Course : ";
    fout << "Course : ";
    for (int i = 0; i < v.size(); i++) {
        cout << store[v[i]];
        fout << store[v[i]];
    }
    cout << endl;
    fout << endl;
    //print course
    cout << "=================" << endl;
    fout << "=================" << endl;
    

    return Success;
}
/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Dijkstra using std::set
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey)
{
    // TODO: implement
    if (m_graph.Size() <= startVertexKey || m_graph.Size() <= endVertexKey) {
        return InvalidVertexKey; // not exist vertex in graph
    }
    if (0 > startVertexKey || 0 > endVertexKey) {
        return InvalidVertexKey; // not exist vertex in graph
    }

    vector<int> v; //result path
    v = m_graph.FindShortestPathDijkstraUsingSet(startVertexKey, endVertexKey); //Dijkstra

    cout << "shortest path: ";
    fout << "shortest path: ";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
        fout << v[i] << " ";
    }
    cout << endl;
    fout << endl;
    //print path 

    vector<int> v_sort;
    v_sort = v;
    sort(v_sort.begin(), v_sort.end()); //sort ascending, declare algorithm header

    cout << "sorted nodes: ";
    fout << "sorted nodes: ";
    for (int i = 0; i < v_sort.size(); i++) {
        cout << v_sort[i] << " ";
        fout << v_sort[i] << " ";
    }
    cout << endl;
    fout << endl;
    //print sort path

    int cost = 0;
    for (int i = 0; i < v.size() - 1; i++) {
        cost = cost + m_graph.FindEdge(v[i], v[i + 1])->GetWeight();
    } //add findedge weight
    cout << "path length: " << cost << endl;
    fout << "path length: " << cost << endl;
    //print path length

    cout << "Course : ";
    fout << "Course : ";
    for (int i = 0; i < v.size(); i++) {
        cout << store[v[i]];
        fout << store[v[i]];
    }
    cout << endl;
    fout << endl;
    //print course
    cout << "=================" << endl;
    fout << "=================" << endl;

    return Success;
}
/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Dijkstra using MinHeap
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey)
{
    // TODO: implement

    if (m_graph.Size() <= startVertexKey || m_graph.Size() <= endVertexKey) {
        return InvalidVertexKey; // not exist vertex in graph
    }
    if (0 > startVertexKey || 0 > endVertexKey) {
        return InvalidVertexKey; // not exist vertex in graph
    }

    vector<int> v; //result path
    v = m_graph.FindShortestPathDijkstraUsingMinHeap(startVertexKey, endVertexKey); //Dijkstra

    cout << "shortest path: ";
    fout << "shortest path: ";


    for (int i = 0; i < v.size(); i++) {
        if (v[i] == 999999) {
            break;
        }
        cout << v[i] << " ";
        fout << v[i] << " ";
    }
    cout << endl;
    fout << endl;
    //print path 

    vector<int> v_sort;
    v_sort = v;
    sort(v_sort.begin(), v_sort.end()); //sort ascending, declare algorithm header

    cout << "sorted nodes: ";
    fout << "sorted nodes: ";
    for (int i = 0; i < v_sort.size(); i++) {
        if (v_sort[i] == 999999) {
            break;
        }
        cout << v_sort[i] << " ";
        fout << v_sort[i] << " ";
    }
    cout << endl;
    fout << endl;
    //print sort path

    int cost = 0;
    for (int i = 0; i < v.size() - 1; i++) {
        if (v[i+1] == 999999) {
            break;
        }
        cost = cost + m_graph.FindEdge(v[i], v[i + 1])->GetWeight();
    } //add findedge weight
    cout << "path length: " << cost << endl;
    fout << "path length: " << cost << endl;
    //print path length

    cout << "Course : ";
    fout << "Course : ";
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == 999999) {
            break;
        }
        cout << store[v[i]];
        fout << store[v[i]];
    }
    cout << endl;
    fout << endl;
    //print course
    cout << "=================" << endl;
    fout << "=================" << endl;

    return Success;
}
/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Bellman-Ford
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::NegativeCycleDetected if exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey)
{
    // TODO: implement
    if (m_graph.Size() <= startVertexKey || m_graph.Size() <= endVertexKey) {
        return InvalidVertexKey; // not exist vertex in graph
    }
    if (0 > startVertexKey || 0 > endVertexKey) {
        return InvalidVertexKey; // not exist vertex in graph
    }

    vector<int> v; //result path
    v = m_graph.FindShortestPathBellmanFord(startVertexKey, endVertexKey); //Dijkstra

    if (v[0] == -1) {
        return NegativeCycleDetected;
    }// negative cycle


    cout << "shortest path: ";
    fout << "shortest path: ";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
        fout << v[i] << " ";
    }
    cout << endl;
    fout << endl;
    //print path 

    vector<int> v_sort;
    v_sort = v;
    sort(v_sort.begin(), v_sort.end()); //sort ascending, declare algorithm header

    cout << "sorted nodes: ";
    fout << "sorted nodes: ";
    for (int i = 0; i < v_sort.size(); i++) {
        cout << v_sort[i] << " ";
        fout << v_sort[i] << " ";
    }
    cout << endl;
    fout << endl;
    //print sort path

    int cost = 0;
    for (int i = 0; i < v.size() - 1; i++) {
        cost = cost + m_graph.FindEdge(v[i], v[i + 1])->GetWeight();
    } //add findedge weight
    cout << "path length: " << cost << endl;
    fout << "path length: " << cost << endl;
    //print path length

    cout << "Course : ";
    fout << "Course : ";
    for (int i = 0; i < v.size(); i++) {
        cout << store[v[i]];
        fout << store[v[i]];
    }
    cout << endl;
    fout << endl;
    //print course
    cout << "=================" << endl;
    fout << "=================" << endl;

    return Success;
}

Result Manager::FindShortestPathFloyd()
{
    vector<vector<int>> v;
    v = m_graph.FindShortestPathFloyd();

    if (v[0][0] == -1) {
        return NegativeCycleDetected; //negative cycle 
    }

    for (int i = 0; i < m_graph.Size(); i++) {
        for (int j = 0; j < m_graph.Size(); j++) {
            cout << v[i][j] << " ";
            fout << v[i][j] << " ";
        }
        cout << endl;
        fout << endl;
    } // print 2D array 

    cout << "=================" << endl;
    fout << "=================" << endl;

    return Success;
}

Result Manager::RabinKarpCompare(const char* CompareString,const char* ComparedString)
{
    // TODO: implement
    return Success;
}

char* Manager::Compare(const char* CompareString, const char* ComparedString)
{
    return nullptr;
}
