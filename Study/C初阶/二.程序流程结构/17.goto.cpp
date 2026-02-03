#include <iostream>

using namespace std;

int main()
{
    int i = 0;
    while (i < 10)
    {
        i++;
        if (i == 5)
        {
            goto label;
        }
        cout << i << " ";
    }
    label:
    cout << "goto label" << endl;
    return 0;
}