#include <bits/stdc++.h>
using namespace std;
class Node
{
public:
    char c;
    int frequency;
    Node *left, *right;
    Node()
    {
        c = '\0';
        frequency = 0;
        left = NULL;
        right = NULL;
    }
};
class PriorityQueue
{
    vector<Node *> pq;
public:
    PriorityQueue() {}
    int size()
    {
        return pq.size();
    }
    Node *getMin()
    {
        if (pq.size() == 0)
            return NULL;
        return pq[0];
    }
    void insert(Node *element)
    {
        pq.push_back(element);
        int curIndex = pq.size() - 1;
        while (curIndex > 0)
        {
            int parentIndex = (curIndex - 1) / 2;
            if (pq[parentIndex]->frequency > pq[curIndex]->frequency)
            {
                swap(pq[parentIndex], pq[curIndex]);
                curIndex = parentIndex;
            }
            else
                return;
        }
        return;
    }
    void removeMin()
    {
        if (pq.size() == 0)
            return;
        int lastIdx = pq.size() - 1;
        if (lastIdx == 0)
        {
            pq.pop_back();
            return;
        }
        swap(pq[lastIdx], pq[0]);
        pq.pop_back();
        int curIdx = 0;
        int leftIdx = (2 * curIdx) + 1, rightIdx = (2 * curIdx) + 2;
        while (leftIdx < pq.size())
        {
            int minIdx = curIdx;
            if (pq[minIdx]->frequency > pq[leftIdx]->frequency)
            {
                minIdx = leftIdx;
            }
            if (rightIdx < pq.size() && pq[minIdx]->frequency > pq[rightIdx]->frequency)
            {
                minIdx = rightIdx;
            }
            if (curIdx == minIdx)
                return;
            swap(pq[minIdx], pq[curIdx]);
            curIdx = minIdx;
            leftIdx = (2 * curIdx) + 1;
            rightIdx = (2 * curIdx) + 2;
        }
    }
};
