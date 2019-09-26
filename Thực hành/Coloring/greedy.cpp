#include <iostream>
#include <vector>
#include <algorithm>

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

    // Kiểm tra đã hoàn thành tô màu chưa nếu tìm thấy
    // -1 trong vector tức còn đỉnh chưa tô màu
    bool isDoneColoring(vector<int> isColoredWith)
    {
        return find(isColoredWith.begin() + 1, isColoredWith.end(), -1) == isColoredWith.end();
    }

    // Đếm bậc của từng đỉnh
    vector<vector<int>> countRank()
    {
        vector<vector<int>> result;
        vector<int> pair;

        for (int i = 0; i < nVertex; i++)
        {
            pair.push_back(i + 1);
            pair.push_back(0);

            result.push_back(pair);
            pair.clear();
        }

        for (int i = 0; i < nVertex; i++)
        {
            for (int j = 0; j < nVertex; j++)
            {
                if (matrix[i][j] == 1)
                {
                    result[i][1]++;
                }
            }
        }

        return result;
    }

    // Sắp xếp đỉnh theo bậc giảm dần
    static bool sortRankDes(const vector<int> &v1, const vector<int> &v2)
    {
        return v1[1] > v2[1];
    }

    vector<vector<int>> greedyColoring(bool isOrdered = false)
    {
        vector<vector<int>> result;
        vector<int> vertexList;
        // Đếm bậc
        vector<vector<int>> rank = countRank();
        // Vector lưu màu của từng đỉnh
        // -1 tức chưa tô
        vector<int> isColoredWith(this->nVertex + 1, -1);
        // Màu đang sử dụng
        int currColor = 0;

        // Sắp xếp
        if (isOrdered == true)
            sort(rank.begin(), rank.end(), sortRankDes);

        /**
        Khi chưa tô màu hết tất cả các đỉnh
        thì tô màu đang sử dụng cho tất cả các đỉnh hợp lệ
        sau đó đổi màu và tiếp tục tô màu cho đến khi tô hết
        **/
        while (!isDoneColoring(isColoredWith))
        {
            // Duyệt từng đỉnh một và thực hiện tô màu các đỉnh hợp lệ
            for (int i = 0; i < this->nVertex; i++)
            {
                // Đỉnh đang xét
                int currVert = rank[i][0];
                // Nếu đỉnh đó chưa được tô màu
                if (isColoredWith[currVert] == -1)
                {
                    // Màu đang sử dụng có thích hợp tô cho đỉnh i không
                    bool isValid = true;

                    // Kiểm tra đỉnh đang xét i có trùng màu với các đỉnh j kề nó không
                    // Nếu trùng màu thì màu đang sử dụng không thích hợp cho đỉnh i
                    for (int j = 1; j <= this->nVertex; j++)
                    {
                        if (isConnected(currVert, j) && isColoredWith[j] == currColor)
                        {
                            isValid = false;
                            break;
                        }
                    }
                    // Nếu màu thích hợp cho đỉnh i thì tô màu cho nó
                    if (isValid == true)
                    {
                        vertexList.push_back(currVert);
                        isColoredWith[currVert] = currColor;
                    }
                }
            }
            // Các đỉnh vừa được tô
            result.push_back(vertexList);
            vertexList.clear();
            // Đổi màu khác
            currColor++;
        }

        return result;
    }
};

int main()
{
    int nVertex, nEdge;
    int a, b;
    cout << "Enter number of vertices, edges: ";
    cin >> nVertex >> nEdge;
    Graph g(nVertex, nEdge);
    for (int i = 0; i < nEdge; i++)
    {
        cout << "Enter edge " << i + 1 << ": ";
        cin >> a >> b;
        g.addEdge(a, b);
    }

    vector<vector<int>> result = g.greedyColoring();
    cout << "\n-------Greedy coloring result-------\n";
    for (int i = 0; i < result.size(); i++)
    {
        cout << "Color " << i << ": ";
        for (int j = 0; j < result[i].size(); j++)
        {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    result = g.greedyColoring(true);
    cout << "\n-------Order coloring result-------\n";
    for (int i = 0; i < result.size(); i++)
    {
        cout << "Color " << i << ": ";
        for (int j = 0; j < result[i].size(); j++)
        {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
    system("pause");
    return 0;
}