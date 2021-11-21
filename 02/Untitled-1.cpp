double f1 (vector <double> x) {

    return 0;
}


double f2 (vector <double> x) {

    return 2;
}

int main () {

    map<string, function<double(vector<double>)>> functions;
    functions["f1"] = f1;
    functions["f2"] = f2;


    if(argc > 1) {

        cout << functions.at(argv[1])({1, 2}) << endl
    }
    
    retiurn 0;
}