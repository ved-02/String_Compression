#include <bits/stdc++.h>
using namespace std;
#include "./helper.h"
string compressedString(string &s, unordered_map<char, string> &m)
{
    string compressed = "";
    for (int i = 0; i < s.size(); i++)
    {
        compressed += m[s[i]];
    }
    return compressed;
}
string stringToBitsString(string s)
{
    string binary = "";
    for (int i = 0; i < s.size(); i++)
    {
        binary += bitset<8>(s[i]).to_string();
    }
    return binary;
}
void generateAllCodes(Node *root, string &ans, unordered_map<char, string> &m)
{
    if (root == NULL)
        return;
    if (!root->left && !root->right)
    {
        m[root->c] = ans;
        return;
    }
    ans.push_back('0');
    generateAllCodes(root->left, ans, m);
    ans.pop_back();
    ans.push_back('1');
    generateAllCodes(root->right, ans, m);
    ans.pop_back();
    return;
}
unordered_map<char, string> huffmannCode(string s)
{
    unordered_map<char, int> freq;
    for (int i = 0; i < s.size(); i++)
    {
        freq[s[i]]++;
    }
    PriorityQueue pq;
    for (auto it = freq.begin(); it != freq.end(); it++)
    {
        Node *temp = new Node();
        temp->c = it->first;
        temp->frequency = it->second;
        pq.insert(temp);
    }
    while (pq.size() != 1)
    {
        Node *n1 = pq.getMin();
        pq.removeMin();
        Node *n2 = pq.getMin();
        pq.removeMin();
        Node *parent = new Node();
        parent->frequency = n1->frequency + n2->frequency;
        parent->left = n1;
        parent->right = n2;
        pq.insert(parent);
    }
    Node *root = pq.getMin();
    string temp = "";
    unordered_map<char, string> codes;
    generateAllCodes(root, temp, codes);
    return codes;
}
string retrieveString(string &compressed, unordered_map<string, char> &m)
{
    string retrieved = "";
    int i=0;
    while (i < compressed.size())
    {
        string temp = "";
        char c = '\0';
        int j = i;
        while (j < compressed.size())
        {
            temp.push_back(compressed[j]);
            if(m.find(temp) != m.end())
            {
                c = m[temp];
                break;
            }
            j++;
        }
        retrieved.push_back(c);
        i = j+1;
    }
    return retrieved;
}
int main()
{
    string s;
    getline(cin, s);
    string binaryRep = stringToBitsString(s);
    unordered_map<char, string> code = huffmannCode(s);
    unordered_map<string, char> codeToChar;
    for (auto it = code.begin(); it != code.end(); it++)
    {
        codeToChar[it->second] = it->first;
    }
    string compressed = compressedString(s, code);
    cout << "BINARY REPRESENTATION OF STRING:" << endl;
    cout << binaryRep << endl;
    cout << "COMPRESSED FORM OF STRING:" << endl;
    cout << compressed << endl;
    cout << "RETRIEVED STRING FROM COMPRESSED STRING:" << endl;
    string retrievedString = retrieveString(compressed, codeToChar);
    cout << retrievedString << endl;
    return 0;
}
