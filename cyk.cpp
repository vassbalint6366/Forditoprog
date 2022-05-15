#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <iterator>
#include <sstream>
using namespace std;



int main()
{
    map<string, string> szabalyok = { {"AB", "S"},{"CD", "S"},{"CB", "S"},{"SS", "S"},{"BC", "A"},{"a", "A"},{"SC", "B"},{"b", "B,C"},{"DD", "C"},{"BA", "D"}, }; 
    //Szabalyok felvetele map segitsegevel (szoveg-szoveg)



    string Input = "aabbabbabbaababa"; // INPUT



    
    vector<vector<string>> piramis;


    for (int i = 0; i < Input.length(); i++) //feltoltjuk az elso sort
    {
        string InputChar(1, Input[i]);

        string ertek = szabalyok.at(InputChar);

        vector<string> sor;

        sor.push_back(ertek);
        piramis.push_back(sor);
    }

    map<string, string>::iterator ite;
    
    for (int i = 1; i < piramis.size(); i++) //vegigfut a piramis sorain
    {
        for (int j = 0; j < piramis.size() - i; j++) //vegigfut a piramis sorainak elemein
        {
            string ujbetu;

            for (int k = 0; k < i; k++) //Annyiszor fut le ahany eleme van balra es jobbra
            {
                string bal = piramis[j][k];
                string jobb = piramis[j + k + 1][i - k - 1];
                string keresettszoveg;

                //piramis feltoltese
                if (bal.find(",") == string::npos && jobb.find(",") == string::npos) // npos: largest value
                {
                    keresettszoveg = bal + jobb;
                    ite = szabalyok.find(keresettszoveg);
                    if (ite != szabalyok.end())
                    {
                        if (ujbetu.empty())
                        {
                            ujbetu.append(ite->second); //append -> kiegesziti a stringet az adott betuvel (vegere teszi be)
                        }
                        else
                        {
                            ujbetu.append("," + ite->second);
                        }
                    }
                }
                else
                {
                    vector<string> osztottbalbetuk;
                    vector<string> osztottjobbbetuk;

                    stringstream ssbal(bal);
                    stringstream ssjobb(jobb);

                    string token;
                    
                    while (getline(ssbal, token, ','))
                    {
                        osztottbalbetuk.push_back(token);
                    }

                    while (getline(ssjobb, token, ','))
                    {
                        osztottjobbbetuk.push_back(token);
                    }

                    for (int x = 0; x < osztottbalbetuk.size(); x++)
                    {
                        for (int y = 0; y < osztottjobbbetuk.size(); y++)
                        {
                            keresettszoveg = osztottbalbetuk[x] + osztottjobbbetuk[y];
                            ite = szabalyok.find(keresettszoveg);
                            if (ite != szabalyok.end())
                            {
                                if (ujbetu.empty())
                                {
                                    ujbetu.append(ite->second);
                                }
                                else
                                {
                                    ujbetu.append("," + ite->second);
                                }
                            }
                        }
                    }
                }
            }
            if (ujbetu.empty())
            {
                ujbetu.append("-");
            }

            piramis[j].push_back(ujbetu);
        }
    }

    //Piramis kiiratasa
    int i = 0;
    int j = piramis[i].size() - 1;
    cout << string(j + 1, ' ');
    while (j >= 0)
    {

        cout << piramis[i][j] << " ";

        if (piramis[i].size() - 1 == j)
        {
            i = 0;
            j--;

            cout << endl;
            cout << string(j + 1, ' ');
        }
        else
        {
            i++;
        }
    }

    cout << endl;
    if (piramis[0][piramis[0].size() - 1] != "-")
    {
        cout << "A szo levezetheto!" << endl;
    }
    else
    {
        cout << "A szo nem vezetheto le!" << endl;
    }

    return 0;
}