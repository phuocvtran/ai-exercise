#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class Graph
{
private:
    int nVertex, nEdge;
    vector<vector<int>> matrix;

public:
    Graph(int nVertex = 2, int nEdge = 1)
    {
        this->nVertex = nVertex < 2 ? 2 : nVertex;
        this->nEdge = nEdge < 1 ? 1 : nEdge;

        for (int i = 0; i < nVertex; i++)
        {
            this->matrix.push_back(vector<int>());
            for (int j = 0; j < nVertex; j++)
            {
                this->matrix[i].push_back(-1);
            }
        }
    }

    void addEdge(int u, int v)
    {
        this->matrix[u - 1][v - 1] = 1;
        this->matrix[v - 1][u - 1] = 1;
    }

    bool isConnected(int u, int v)
    {
        return this->matrix[u - 1][v - 1] != -1;
    }

    void BFS(int curr, int goal, vector<int> currPath, vector<vector<int>> &allPaths, vector<bool> isVisited)
    {
        // Nếu gặp goal thì hoàn thành 1 đường
        if (curr == goal)
        {
            currPath.push_back(curr);
            allPaths.push_back(currPath);
            return;
        }

        // Lưu đỉnh vào đường đi hiện tại
        currPath.push_back(curr);
        isVisited[curr] = true;

        // Tìm tất cả các đỉnh nối với đỉnh hiện tại đang xét và chưa đi qua
        // cho vào hàng đợi
        queue<int> q;
        for (int i = 1; i <= this->nVertex; i++)
        {
            if (isConnected(curr, i) && isVisited[i] == false)
            {
                q.push(i);
            }
        }

        // Xét đỉnh tiếp theo trong hàng đợi
        while (!q.empty())
        {
            int next = q.front();
            q.pop();
            BFS(next, goal, currPath, allPaths, isVisited);
        }
    }

    void DFS(int curr, int goal, vector<int> currPath, vector<vector<int>> &allPaths, vector<bool> isVisited)
    {
        if (curr == goal)
        {
            currPath.push_back(curr);
            allPaths.push_back(currPath);
            return;
        }

        currPath.push_back(curr);
        isVisited[curr] = true;

        stack<int> s;
        for (int i = 1; i <= this->nVertex; i++)
        {
            if (isConnected(curr, i) && isVisited[i] == false)
            {
                s.push(i);
            }
        }

        while (!s.empty())
        {
            int next = s.top();
            s.pop();
            DFS(next, goal, currPath, allPaths, isVisited);
        }
    }
};

int main()
{
    int nVertex, nEdge, start, goal;
    int a, b, n;
    cout << "Enter number of vertices, edges and the starting, goal position: ";
    cin >> nVertex >> nEdge >> start >> goal;
    Graph g(nVertex, nEdge);
    for (int i = 0; i < nEdge; i++)
    {
        cout << "Enter edge " << i + 1 << ": ";
        cin >> a >> b;
        g.addEdge(a, b);
    }

    vector<vector<int>> allPathsDFS, allPathsBFS;
    g.DFS(start, goal, vector<int>(), allPathsDFS, vector<bool>(nVertex + 1, false));
    g.BFS(start, goal, vector<int>(), allPathsBFS, vector<bool>(nVertex + 1, false));

    // Xuất các đường đi
    cout << "\n###### DFS result ######\n";
    for (int i = 0; i < allPathsDFS.size(); i++)
    {
        for (int j = 0; j < allPathsDFS[i].size(); j++)
        {
            int v = allPathsDFS[i][j];
            cout << v;
            if (j < allPathsDFS[i].size() - 1)
            {
                cout << " -> ";
            }
        }
        cout << endl;
    }

    cout << endl;

    cout << "\n###### BFS result ######\n";
    for (int i = 0; i < allPathsBFS.size(); i++)
    {

        for (int j = 0; j < allPathsBFS[i].size(); j++)
        {
            int v = allPathsBFS[i][j];
            cout << v;
            if (j < allPathsBFS[i].size() - 1)
            {
                cout << " -> ";
            }
        }
        cout << endl;
    }

    cout << endl;

    system("pause");
    return 0;
}