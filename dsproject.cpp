#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <cmath>
#include <algorithm>
#include <cstdlib>

using namespace std;

#define bike 10
#define area 10

struct Node {
    int x, y;

    Node() : x(0), y(0) {}
    Node(int xx, int yy) : x(xx), y(yy) {}
};

class Person {
public:
    string name;
    float amount;
    int pass;

    Person() : amount(1000), pass(0), name("Unknown") {}
    Person(string n, int p,int a) : name(n), pass(p),amount(a) {
        
    }
};

map<string, Person> details;
string name;

class BikeRentalSystem {
public:
    map<int, string> ar;
    vector<Node> g[100];
    map<string,Node> bikes;
    vector<vector<int>> allPaths;
    map<string, Node> areas;
    map<string, int> are;
    int visited[100] = {0};
    vector<int> path;
    int x, y, x1, y1, weight;
    string s,b1;

    BikeRentalSystem() {
        ifstream fin("input.txt");
        while (fin >> x >> y >> weight) {
            g[x].push_back(Node(y, weight));
            g[y].push_back(Node(x, weight));
        }
        fin.close();

        int u, v;

        ifstream in("bike.txt");
        
        while (in >> x >> y>>ws&&getline(in,s)) {
            
            bikes[s]=Node(x, y);
        }
        ifstream fn("areas.txt");
        int i=1;
        while (fn >> x >> y >> ws && getline(fn, s)) {
            are[s] = i;
            ar[i] = s;
            areas[s] = Node(x, y);
            i++;
        }
        
    }

    void sortPaths() {
        sort(allPaths.begin(), allPaths.end(),
             [](const vector<int> &a, const vector<int> &b) {
                 return a[0] < b[0];
             });
        cout<<"The first one of these paths is the sorthest path"<<endl;
        for (int i = 0; i < allPaths.size(); ++i) {
            cout<<i+1<<")";
            for (int j = 1; j < allPaths[i].size() - 1; ++j) {
                cout << ar[allPaths[i][j]] << "->";
            }
            cout << ar[allPaths[i][allPaths[i].size() - 1]] << " Distance : " << allPaths[i][0] << endl;
        }
    }

    void dfs(int visited[100], int u, int v, vector<int> &path, int d) {
        visited[u] = 1;
        path.push_back(u);
        if (u == v) {
            vector<int> currentPath;
            currentPath.push_back(d);
            for (int i = 0; i < path.size(); ++i) {
                currentPath.push_back(path[i]);
            }
            allPaths.push_back(currentPath);
        } else {
            for (int j = 0; j < g[u].size(); j++) {
                int y = g[u][j].x;
                if (visited[y] == 0) {
                    dfs(visited, y, v, path, d + g[u][j].y);
                }
            }
        }
        visited[u] = 0;
        path.pop_back();
    }

    int distance(int x, int y, int x1, int y1) {
        x = x - x1;
        y = y - y1;
        return sqrt(x * x + y * y);
    }

    void process() {
        system("clear");
        cout << "Enter your coordinates:";
        cin >> x >> y;

        int min = 1e9;
        
        for (const auto &it : bikes) {
            int d = distance(x, y, it.second.x, it.second.y);
            if (min > d) {
                min = d;
                b1=it.first;
            }
        }
        system("clear");
        cout << min << " The nearest bike to you is at (" << bikes[b1].x << "," << bikes[b1].y << ")" <<endl;
        
        cout<<"Bike numer :"<<b1<< endl;

        min = 1e9;

        for (const auto &it : areas) {
            int d = distance(x1, y1, it.second.x, it.second.y);
            if (min > d) {
                min = d;
                s = it.first;
               
            }
        }

        int n;
        cout << "If you want to rent a bike, press 1" << endl;
        cout << "If you want to go to nearby places, press 2" << endl;
        cin >> n;

        if (n == 1) {
            cout << "If you want to rent for a day, press 0" << endl;
            cout << "If you want to rent for hours, enter the hours" << endl;
            cout << "Cost per hour is 50 rupees " << endl;

            cin >> n;

            if (n == 0) {
                cout << "The total charge per day is 400. Need to return in 8 hours from now "<<endl;
            Person &p1 = details[name];

            if (p1.amount - 400 < 0) {
                cout << "Please recharge the wallet and try again"<<endl;
            } else {
                p1.amount -= 400;
                cout << "Your balance in the account is " << p1.amount<<endl;
            }
            } else {
                if (n > 8) {
                    cout << "No of hours must be less than 8" << endl;
                }

                cout << "The total charge is " << ceil((n * 50) + (n * 50) * 0.05)<<endl;
                Person &p1 = details[name];

            if (p1.amount - ceil((n * 50) + (n * 50) * 0.05) < 0) {
                cout << "Please recharge the wallet and try again"<<endl;
            } else {
                p1.amount -= ceil((n * 50) + (n * 50) * 0.05);
                cout << "Your balance in the account is " << p1.amount<<endl;
            }
            }
        } else if (n == 2) {
            cout << "You are starting from " << s << " (" << areas[s].x << "," << areas[s].y << ") to";
            string a;
            cin >> a;
            dfs(visited, are[s], are[a], path, 0);

            int n, i;

            while (1) {
                sortPaths();
                cout << "Which path do you want to select?" << endl;
                cin >> n;

                for (int j = 1; j < allPaths[n-1].size() - 1; ++j) {
                    cout << ar[allPaths[n-1][j]] << "->";
                }

                cout << ar[allPaths[n-1][allPaths[n-1].size() - 1]] << " Distance : " << allPaths[n-1][0] << endl;
                cout << "Is this the way that you have selected?" << endl;
                cout << "Press 1 for yes and 0 for no (or) change" << endl;
                cin >> i;

                if (i == 1) {
                    break;
                }
            }
            cout<<"HI";
            cout << "The cost for the ride is " << allPaths[n-1][0] * 2<<endl;
            
            Person &p1 = details[name];

            if (p1.amount - allPaths[n-1][0] * 2 < 0) {
                cout << "Please recharge the wallet and try again"<<endl;
            } else {
                p1.amount -= allPaths[n-1][0] * 2;
                cout << "Your balance in the account is " << p1.amount<<endl;
            }
            allPaths.clear();
            cout<<"enter the cordinates of the place where the bike is parked"<<endl;
            int x2,y2;
            cin>>x2>>y2;
            bikes[b1].x=x2;
            bikes[b1].y=y2;
            ofstream fout("bike.txt");
             for (const auto &it : bikes) {
               fout<<it.second.x<<" "<<it.second.y<<" "<<it.first<<endl;
            }
            system("clear");
            cout<<"Bike Rental System"<<endl;
        } else {
            cout << "Invalid input";
        }
    }
};

int main() {
    BikeRentalSystem sys;
    int pass;
    ifstream fin("user_data.txt");

    while (fin >> pass >> ws && getline(fin, name)) {
        Person p1(name, pass,1000);
        details[name] = p1;
    }

    cout<<"Bike Rental System"<<endl;
    while (1) {
        cout << "Enter your use_id:" ;
        cin >> name;

        Person &p1 = details[name];

        if (p1.name == "Unknown") {
            int n;
            cout << "You do not have an account;" << endl;
            cout << "Press 1 to create a new account " << endl;
            cout << "If you want to re-enter your name press 2" << endl;
            cin >> n;

            if (n == 1) {
                cout << "Enter your user_id:";
                cin.ignore();
                getline(cin, name);

                cout << "Set a password (it must be an int):";
                cin >> pass;

                Person p1(name, pass,1000);
                details[name] = p1;

                cout << "Successfully created.";
                ofstream fout("user_data.txt",ios::app);
                // for (const auto &it : details) {
                //     fout<<it.second.pass<<" "<<it.second.name<<endl;
                // }
                fout<<pass<<" "<<name<<endl;
            }
        } else {
            system("clear");
            cout<<"Bike Rental System"<<endl;
            cout << "Enter your password" << endl;
            cin >> pass;
            if (p1.pass == pass) {
                int n = 1;

                while (n) {
                    system("clear");
                    cout<<"Bike Rental System"<<endl;
                    cout << "To continue, press 1" << endl;
                    cout << "To logout, press 0" << endl;
                    cin >> n;
                    system("clear");
                    cout<<"Bike Rental System"<<endl;
                    if (n == 1) {
                        sys.process();
                    }

                    cout << "Thank you for visiting";
                }
            }
        }
    }

    return 0;
}
