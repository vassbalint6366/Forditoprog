#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;


map<string, string> szabalyok = { {"S1", "T+S"},{"S2", "T"},{"T1", "a"},{"T2", "b"}, };
//Szabalyok felvetele map segitsegevel (szoveg-szoveg)


//pair: meg tudjuk hivni az elemeit pl ha az S1-et akarjuk nezni vagy az S2-t)
vector<pair<string, string>> szabalyKereses(string search) //megkeressuk a stringet a szabalyok kozott
{
    vector<pair<string, string>> eredmeny; //az eredmenyunk is egy ilyen par lesz 

    for (map<string, string>::iterator ite = szabalyok.begin(); ite != szabalyok.end(); ite++)
    {
        if (ite->first.find(search) != string::npos)
        {
            pair<string, string> sor;
            sor.first = ite->first; //pair meghivas (elso elem)
            sor.second = ite->second; //(masodik elem)
            eredmeny.push_back(sor);
        }
    }
    return eredmeny;
}

int main()
{



    const string Input = "a+a+b+b+a"; //INPUT



    vector<string> nemterminalis = {"S", "T"};

    bool sikeres = false;
    int iterator = 0;
    vector<string> eredmeny;
    string build = "S";

    while (!sikeres)
    {
        string buildFirst(1, build[0]);
        string keresettbetu(1, Input[iterator]);

        vector<pair<string, string>> keresettszabalyok = szabalyKereses(buildFirst);

        if (keresettbetu == buildFirst) //Sikeres input illesztés
        {
            eredmeny.push_back(buildFirst);
            build.erase(0, 1); //erase: torol
            iterator++;
            if (iterator == Input.length() && build.empty())
            {
                sikeres = true;
                break;
            }
        }
        else if (keresettszabalyok.size() > 0) //Nem terminális kiterjesztése
        {
            eredmeny.push_back(keresettszabalyok[0].first);
            build.replace(build.find(buildFirst), buildFirst.length(), keresettszabalyok[0].second);
        }
        else //Sikertelen input illesztés
        {
            while (!eredmeny.empty())
            {
                string utolsoeredmeny = eredmeny[eredmeny.size() - 1];
                string utolsobetu = utolsoeredmeny.substr(0, 1);

                if (find(nemterminalis.begin(), nemterminalis.end(), utolsobetu) != nemterminalis.end()) //Nem terminalis esete
                {
                    string szabalyszam;
                    for (int i = 0; i < utolsoeredmeny.length(); i++)
                    {
                        if (isdigit(utolsoeredmeny[i]))
                        {
                            szabalyszam.push_back(utolsoeredmeny[i]);
                        }
                    }
                    int szabalyszamString = stoi(szabalyszam); // stoi: Convert string to integer

                    vector<pair<string, string>> visszakeresettszabalyok = szabalyKereses(utolsobetu);

                    if (visszakeresettszabalyok.size() > szabalyszamString) //Nem terminális alternatív kiterjesztése
                    {
                        eredmeny[eredmeny.size() - 1] = visszakeresettszabalyok[szabalyszamString].first;
                        build.replace(build.find(visszakeresettszabalyok[szabalyszamString - 1].second),
                                      visszakeresettszabalyok[szabalyszamString - 1].second.length(),
                                      visszakeresettszabalyok[szabalyszamString].second);
                        break;
                    }
                    else //backtrack
                    {
                        eredmeny.erase(eredmeny.end() - 1);
                        build.replace(build.find(visszakeresettszabalyok[szabalyszamString - 1].second),
                                      visszakeresettszabalyok[szabalyszamString - 1].second.length(),
                                      utolsobetu);
                    }
                }
                else //Terminalis jon
                {
                    eredmeny.erase(eredmeny.end() - 1);
                    build.insert(0, utolsoeredmeny);
                    iterator--;
                }
            }

            if (eredmeny.empty()) //Hiba
            {
                break;
            }
        }
    }

    //kiiratas
    if (sikeres)
    {
        string eredmenyString;
        for_each(eredmeny.begin(), eredmeny.end(), [&](const std::string &piece) { eredmenyString += "(" + piece + ")"; });
            //egyesevel vegigmegy a result-on es kiszedi a parametereket belole majd zarojelek koze teszi (osszefuzve a meglevovel)
        cout << "Eredmeny: " << eredmenyString << endl;
    }
    else
    {
        cout << "Nem sikerult az elemzes!" << endl;
    }
}