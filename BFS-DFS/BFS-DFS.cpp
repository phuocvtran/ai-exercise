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
                this->matrix[i].push_back(0);
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
        return this->matrix[u - 1][v - 1] == 1;
    }

    vector<int> BFS(int start)
    {
        queue<int> q;
        vector<int> result;
        vector<bool> explored(this->nVertex + 1, false);

        q.push(start);
        explored[start] = true;

        while (!q.empty())
        {
            int currVertex = q.front();
            result.push_back(currVertex);
            q.pop();

            for (int i = 1; i <= this->nVertex; i++)
            {
                if (isConnected(currVertex, i) && !explored[i])
                {
                    q.push(i);
                    explored[i] = true;
                }
            }
        }

        return result;
    }

    vector<int> DFS(int start)
    {
        stack<int> s;
        vector<int> result;
        vector<bool> explored(this->nVertex + 1, false);

        s.push(start);
        explored[start] = true;

        while (!s.empty())
        {
            int currVertex = s.top();
            result.push_back(currVertex);
            s.pop();

            for (int i = 1; i <= this->nVertex; i++)
            {
                if (isConnected(currVertex, i) && !explored[i])
                {
                    s.push(i);
                    explored[i] = true;
                }
            }
        }

        return result;
    }
};

int main()
{
    int nVertex, nEdge, start;
    int a, b;
    cout << "Enter number of vertices, edges and the starting position: ";
    cin >> nVertex >> nEdge >> start;
    Graph g(nVertex, nEdge);
    for (int i = 0; i < nEdge; i++)
    {
        cout << "Enter edge " << i + 1 << ": ";
        cin >> a >> b;
        g.addEdge(a, b);
    }

    cout << "BFS result: ";
    vector<int> bfs = g.BFS(start);

    for (int i = 0; i < bfs.size(); i++)
    {
        cout << bfs[i] << " ";
    }

    cout << endl;

    cout << "DFS result: ";
    vector<int> dfs = g.DFS(start);

    for (int i = 0; i < dfs.size(); i++)
    {
        cout << dfs[i] << " ";
    }

    cout << endl;
    system("pause");
    return 0;
}