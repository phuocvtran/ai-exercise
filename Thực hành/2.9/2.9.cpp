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

    void addEdge(int u, int v, int n)
    {
        this->matrix[u - 1][v - 1] = n;
        this->matrix[v - 1][u - 1] = n;
    }

    bool isConnected(int u, int v)
    {
        return this->matrix[u - 1][v - 1] != -1;
    }

    int getLength(int u, int v)
    {
        return this->matrix[u - 1][v - 1];
    }

    void DFS(int curr, int goal, vector<int> currPath, vector<vector<int>> &allPaths, int time, int tmpTime, vector<bool> isVisited)
    {
        // Nếu đỉnh đã đi qua
        if (isVisited[curr - 1] == true)
        {
            // Nếu quay lại vị trí đầu thì coi như hoàn thành 1 đường đi
            // lưu đỉnh hiện tại vào đường đi đang xét và lưu thời gian vào cuối vector
            if (curr == goal)
            {
                time += tmpTime;
                currPath.push_back(curr);
                currPath.push_back(time);
                allPaths.push_back(currPath);
                return;
            }
            return;
        }

        // Nếu đỉnh chưa đi qua thì lưu đỉnh vào đường hiện tại và cập nhật tổng thời gian
        isVisited[curr - 1] = true;
        currPath.push_back(curr);
        time += tmpTime;

        // Tìm tất cả các đỉnh nối với đỉnh hiện tại đang xét
        // lưu tất cả trọng số và cho vào ngăn xếp
        vector<int> vTime;
        stack<int> s;
        for (int i = 1; i <= this->nVertex; i++)
        {
            if (isConnected(curr, i))
            {
                vTime.push_back(getLength(curr, i));
                s.push(i);
            }
        }

        // Xét đỉnh tiếp theo trong hàng đợi
        for (int i = 0; !s.empty(); ++i)
        {
            int next = s.top();
            s.pop();
            DFS(next, goal, currPath, allPaths, time, vTime[i], isVisited);
        }
    }
};

int main()
{
    int nVertex, nEdge, start;
    int a, b, n;
    cout << "Enter number of vertices, edges and the starting position: ";
    cin >> nVertex >> nEdge >> start;
    Graph g(nVertex, nEdge);
    for (int i = 0; i < nEdge; i++)
    {
        cout << "Enter edge and length " << i + 1 << ": ";
        cin >> a >> b >> n;
        g.addEdge(a, b, n);
    }

    vector<vector<int>> allPaths;
    g.DFS(start, start, vector<int>(), allPaths, 0, 0, vector<bool>(nVertex, false));

    // Tìm thời gian nhỏ nhất
    int minTime = INT32_MAX;
    bool foundHamiltonCycle = false;
    for (int i = 0; i < allPaths.size(); ++i)
    {
        if (allPaths[i].size() == nVertex + 2)
        {
            if (allPaths[i].back() < minTime)
            {
                foundHamiltonCycle = true;
                minTime = allPaths[i].back();
            }
        }
    }

    if (!foundHamiltonCycle)
    {
        cout << "\nNo cycle found!\n";
        system("pause");
        return 0;
    }

    // Xuất các đường đi có thời gian bằng minTime
    cout << "\n###### DFS time result: " << minTime << " ######\n";
    for (int i = 0; i < allPaths.size(); i++)
    {
        if (allPaths[i].size() == nVertex + 2)
        {
            if (allPaths[i].back() == minTime)
            {
                for (int j = 0; j < allPaths[i].size() - 1; j++)
                {
                    int v = allPaths[i][j];
                    cout << v << " ";
                    if (j < nVertex)
                    {
                        cout << "-> ";
                    }
                }
                cout << endl;
            }
        }
    }

    cout << endl;

    system("pause");
    return 0;
}