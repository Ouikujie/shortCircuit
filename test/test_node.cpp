#include "parser.hpp"
#include "components.hpp"
#include "circuit.hpp"

#include <iostream>
#include <iomanip>
#include <cassert>
#include <sstream>
#include <fstream>

using namespace std;

int main()
{
    ifstream input("./input/test_input_2.net");
    string line;

    double f = 1000;
    double step = 0.001;

    vector<Component *> circuit;
    vector<Node *> nodes;
    vector<string> node_names;
    vector<double> instants;

    while (getline(input, line))
    {
        if (is_component(line))
        {
            cerr << "Parsing component: " << line << endl;
            circuit.push_back(parse_component(line, nodes));
        }
        else if (is_directive(line))
        {
            if (is_tran(line))
            {
                cerr << "Parsing directive: " << line << endl;
                instants = generate_instants(line);
            }
            else if (is_end(line))
            {
                cerr << "🎬 Reach END of file: " << line << endl;
                break;
            }
            else
            {
                cerr << "Unsupported syntax: " << line << endl;
            }
        }
    }
    cout << endl;
    cout << endl;
    cout << "==============================" << endl;
    cout << "✅ " << instants.size() << " instants in total" << endl;
    cout << "==============================" << endl;
    cout << "From: " << instants[0] << " to: " << instants[instants.size() - 1] << " with step: " << instants[1] << endl;

    cout << endl;
    cout << endl;
    cout << "==============================" << endl;
    cout << "✅ " << circuit.size() << " components in total" << endl;
    cout << "==============================" << endl;
    cout << setw(12) << "get_type()" << setw(20) << "get_conductance()" << setw(16) << "get_node(\"p\")" << setw(18) << "get_node(\"n\")" << setw(18) << "get_current(t)" << setw(18) << "get_voltage_across(t)" << setw(18) << "check_grounded()" << endl;
    for (auto it = circuit.begin(); it != circuit.end(); it++)
    {
        cout << setw(12) << (*it)->get_type() << setw(20) << (*it)->get_conductance() << setw(16) << (*it)->get_node("p") << setw(18) << (*it)->get_node("n") << setw(18) << (*it)->get_current((*it)->get_node("p")) << setw(18) << (*it)->get_voltage_across(step, (*it)->get_node("p")) << setw(18) << (*it)->check_grounded() << endl;
    }

    cout << endl;
    cout << endl;
    cout << "==============================" << endl;
    cout << "✅ " << nodes.size() << " nodes in total execpt for ground" << endl;
    cout << "==============================" << endl;
    cout << setw(5);
    for (auto it = node_names.begin(); it != node_names.end(); it++)
    {
        cout << setw(22) << (*it);
    }
    cout << setw(10) << "b" << endl;
    for (auto it = nodes.begin(); it != nodes.end(); it++)
    {
        cout << setw(5) << (*it)->get_name();
        for (auto jt = nodes.begin(); jt != nodes.end(); jt++)
        {
            cout << setw(22) << (*it)->get_conductance((*jt));
        }
        cout << setw(20) << (*it)->get_current() << endl;
    }
}