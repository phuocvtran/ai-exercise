#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

int main()
{
    int nM, nJ;
    std::vector<int> M, J;
    std::vector<std::vector<int>> task;

    std::cout << "Enter number of machines: ";
    std::cin >> nM;
    std::cout << "Enter number of tasks: ";
    std::cin >> nJ;
    std::cout << std::endl;

    for (int i = 0; i < nJ; i++)
    {
        int tmp;
        std::cout << "Enter time to finish task " << i + 1 << ": ";
        std::cin >> tmp;
        J.push_back(tmp);
    }

    for (int i = 0; i < nM; i++)
    {
        task.push_back(std::vector<int>());
    }

    int dummy = 0;
    while (dummy < nJ)
    {
        if (dummy < nM)
        {
            M.push_back(J[dummy]);
            task[dummy].push_back(dummy + 1);
            J[dummy] = INT_MIN;
        }
        else
        {
            int maxJIndex = std::max_element(J.begin(), J.end()) - J.begin();
            int minIndex = std::min_element(M.begin(), M.end()) - M.begin();
            M[minIndex] += J[maxJIndex];
            task[minIndex].push_back(maxJIndex + 1);
            J[maxJIndex] = INT_MIN;
        }
        dummy++;
    }

    std::cout << std::endl
              << "===============Result===============" << std::endl;
    std::cout << "Time finish: " << *std::max_element(M.begin(), M.end()) << std::endl;
    for (int i = 0; i < task.size(); i++)
    {
        std::cout << "Machine " << i + 1 << "\'s task: ";
        for (int j = 0; j < task[i].size(); j++)
        {
            std::cout << task[i][j] << " ";
        }
        std::cout << std::endl;
    }

    /*std::sort(J.rbegin(), J.rend());
    
    for (int i = 0; i < nJ; i++) {
        if(i < nM) {
            M.push_back(J[i]);
        }
        else {
            int minIndex = std::min_element(M.begin(), M.end()) - M.begin();
            M[minIndex] += J[i];
        }
    }*/
    system("pause");

    return 0;
}