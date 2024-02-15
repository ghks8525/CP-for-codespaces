#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <string>

using namespace std;
pair<int, int> NONE = make_pair(0, 0);
pair<int, int> arr[4][4];
pair<int, int> shark;
pair<int, int> shark_metric;
vector<int> v;
int sum = 0;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int num;
            int direction;

            v.push_back(num);
            cin >> num >> direction;
            arr[i][j] = make_pair(num, direction);
        }
    }

    sort(v.begin(), v.end());
    v.erase(v.begin());
    shark = arr[0][0];
    shark_metric = make_pair(0, 0);
    sum += shark.first;
    while (true)
    {
        int a = 0;
        int b = 0;
        if (shark.second == 1)
        {
            b -= 1;
        }
        else if (shark.second == 2)
        {
            a -= 1;
            b -= 1;
        }
        else if (shark.second == 3)
        {
            a -= 1;
        }
        else if (shark.second == 4)
        {
            a -= 1;
            b += 1;
        }
        else if (shark.second == 5)
        {
            b += 1;
        }
        else if (shark.second == 6)
        {
            a += 1;
            b += 1;
        }
        else if (shark.second == 7)
        {
            a += 1;
        }
        else if (shark.second == 8)
        {
            a += 1;
            b -= 1;
        }
        int i = shark_metric.first + a;
        int j = shark_metric.second + b;
        pair<int, int> max = make_pair(-1, -1);

        while (true)
        {
             if (i > 3 || i < 0 || j > 3 || j < 0)
             break;
             if (arr[max.second][max.first].first < arr[j][i].first)
            {
                max = make_pair(j, i);
            }
            i += a;
            j += b;

        }
        arr[shark_metric.second][shark_metric.first] = NONE;
        shark_metric = max;
        shark = arr[shark_metric.second][shark_metric.first];
        sum += shark.first;

        if (max == make_pair(-1, -1))
            break;
        if(shark_metric.second < 0 ||shark_metric.second > 3 ||shark_metric.first < 0 || shark_metric.first > 3)
     break;
    }
    cout << sum << endl;

    return 0;
}

void move_fish()
{
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                if (arr[j][k].first == v[i])
                {
                    bool isCan = true;
                    while (isCan)
                    {
                        if (arr[j][k].second == 1)
                        {
                            if (j - 1 < 0 || arr[j - 1][k] == shark)
                            {
                                if (arr[j][k].second == 8)
                                    arr[j][k].second = 1;
                                else
                                    arr[j][k].second += 1;
                                continue;
                            }
                            pair<int, int> tmp = arr[j][k];
                            arr[j][k] = arr[j - 1][k];
                            arr[j - 1][k] = tmp;
                            isCan = false;
                        }
                        else if (arr[j][k].second == 2)
                        {
                            if (k - 1 < 0 || j - 1 < 0 || arr[j - 1][k - 1] == shark)
                            {
                                if (arr[j][k].second == 8)
                                    arr[j][k].second = 1;
                                else
                                    arr[j][k].second += 1;
                                continue;
                            }

                            pair<int, int> tmp = arr[j][k];
                            arr[j][k] = arr[j - 1][k - 1];
                            arr[j - 1][k - 1] = tmp;
                            isCan = false;
                        }
                        else if (arr[j][k].second == 3)
                        {
                            if (k - 1 < 0 || arr[j][k - 1] == shark)
                            {
                                if (arr[j][k].second == 8)
                                    arr[j][k].second = 1;
                                else
                                    arr[j][k].second += 1;
                                continue;
                            }

                            pair<int, int> tmp = arr[j][k];
                            arr[j][k] = arr[j - 1][k];
                            arr[j - 1][k] = tmp;
                            isCan = false;
                        }
                        else if (arr[j][k].second == 4)
                        {
                            if (k - 1 < 0 || j + 1 > 3 || arr[j + 1][k - 1] == shark)
                            {
                                if (arr[j][k].second == 8)
                                    arr[j][k].second = 1;
                                else
                                    arr[j][k].second += 1;
                                continue;
                            }

                            pair<int, int> tmp = arr[j][k];
                            arr[j][k] = arr[j + 1][k - 1];
                            arr[j + 1][k - 1] = tmp;
                            isCan = false;
                        }
                        else if (arr[j][k].second == 5)
                        {
                            if (j + 1 > 3 || arr[j + 1][k] == shark)
                            {
                                if (arr[j][k].second == 8)
                                    arr[j][k].second = 1;
                                else
                                    arr[j][k].second += 1;
                                continue;
                            }

                            pair<int, int> tmp = arr[j][k];
                            arr[j][k] = arr[j + 1][k];
                            arr[j + 1][k] = tmp;
                            isCan = false;
                        }
                        else if (arr[j][k].second == 6)
                        {
                            if (k + 1 > 3 || j + 1 > 3 || arr[j + 1][k + 1] == shark)
                            {
                                if (arr[j][k].second == 8)
                                    arr[j][k].second = 1;
                                else
                                    arr[j][k].second += 1;
                                continue;
                            }

                            pair<int, int> tmp = arr[j][k];
                            arr[j][k] = arr[j + 1][k + 1];
                            arr[j + 1][k + 1] = tmp;
                            isCan = false;
                        }
                        else if (arr[j][k].second == 7)
                        {
                            if (k + 1 > 3 || arr[j][k + 1] == shark)
                            {
                                if (arr[j][k].second == 8)
                                    arr[j][k].second = 1;
                                else
                                    arr[j][k].second += 1;
                                continue;
                            }

                            pair<int, int> tmp = arr[j][k];
                            arr[j][k] = arr[j][k + 1];
                            arr[j][k + 1] = tmp;
                            isCan = false;
                        }
                        else if (arr[j][k].second == 8)
                        {
                            if (k + 1 > 3 || j - 1 < 0 || arr[j][k - 1] == shark)
                            {
                                arr[j][k].second = 1;
                                continue;
                            }

                            pair<int, int> tmp = arr[j][k];
                            arr[j][k] = arr[j - 1][k + 1];
                            arr[j - 1][k + 1] = tmp;
                            isCan = false;
                        }
                    }
                }
            }
        }
    }
}