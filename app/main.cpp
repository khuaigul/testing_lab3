#include <stdio.h>

#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <iostream>
#include <QDebug>
#include <QString>
#include <QTextStream>
//#include <QInputDialog>
#include <QDir>
//#include <QMessageBox>
#include <QListIterator>

QHash<QString, QStringList> words;
QStringList decks_names;
QHash < QString, QHash < QString, QString > > decks;
QString current_deck;
QString current_card;
QHash<QString, QHash<QString, QPair <int, int> > > stats;
int sgn;

using namespace std;

int main()
{
//    text cur = create_text();
//    char *filename;
//    filename = (char*)"tt.txt";
//    load(cur, filename);
//    printf("dfd");
//    show(cur);

//    ifstream c;
//    c.open ( "tt.txt" );
//    string line;
//    getline (c, line, '=');


//    printf("%s", (char*)line);

//    return 0;
}
