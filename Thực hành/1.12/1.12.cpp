#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Job
{
    char name;
    int group;
    int minTime;

    Job(char name)
    {
        this->name = name;
        this->group = -1;
        this->minTime = -1;
    }
};

bool isShorter(Job j1, Job j2)
{
    return j1.minTime < j2.minTime;
}

bool isLonger(Job j1, Job j2)
{
    return j1.minTime > j2.minTime;
}

int main()
{
    vector<vector<int>> machines;
    vector<Job> jobs;
    cout << "Enter number of machines and jobs: ";
    int nM, nJ;
    cin >> nM >> nJ;

    if (nJ > 26)
    {
        cout << "Number of jobs must < 27" << endl;
        system("pause");
        return 1;
    }

    for (char i = 'A'; i < 'A' + nJ; i++)
    {
        Job tmpJob(i);
        jobs.push_back(tmpJob);
    }

    for (int i = 0; i < nM; i++)
    {
        vector<int> tempMachine;
        cout << "Enter time for machine " << i + 1 << " to finish each job: ";
        int tmpTime;
        for (int j = 0; j < nJ; j++)
        {
            cin >> tmpTime;
            tempMachine.push_back(tmpTime);
        }
        machines.push_back(tempMachine);
    }

    // Phân nhóm các công việc cho từng máy
    for (int i = 0; i < nJ; i++)
    {
        int minMachine = 0;
        int minTime = machines[0][i];
        for (int j = 1; j < nM; j++)
        {
            if (machines[j][i] <= minTime)
            {
                minMachine = j;
                minTime = machines[j][i];
            }
        }
        jobs[i].group = minMachine + 1;
        jobs[i].minTime = minTime;
    }

    // Tách các nhóm công việc ra từng vector riêng biệt
    vector<vector<Job>> jobGroup(nM, vector<Job>());
    for (int i = 0; i < nJ; i++)
    {
        jobGroup[jobs[i].group - 1].push_back(jobs[i]);
    }

    // Sắp xếp thứ tự các công việc nếu máy lẻ (i % 2 == 0) thì sắp theo thời gian tăng dần, chẵn thì sắp giảm dần
    vector<vector<Job>>::iterator currGroup;
    vector<Job>::iterator currJob;
    int i = 0;
    for (currGroup = jobGroup.begin(); currGroup != jobGroup.end(); currGroup++)
    {
        if (i == 0 || i % 2 == 0)
            sort(currGroup->begin(), currGroup->end(), isShorter);
        else
            sort(currGroup->begin(), currGroup->end(), isLonger);
        i++;
    }

    // Xuất kết quả
    i = 1;
    cout << "Result: ";
    for (currGroup = jobGroup.begin(); currGroup != jobGroup.end(); currGroup++)
    {
        for (currJob = currGroup->begin(); currJob != currGroup->end(); currJob++)
        {
            cout << currJob->name << " ";
        }
    }

    cout << endl;
    system("pause");
    return 0;
}