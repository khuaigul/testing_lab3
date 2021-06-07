#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H
#include <QString>
#include <QHash>
#include <QStringList>
#include <QDebug>
#include <QString>
#include <QTextStream>
//#include <QInputDialog>
#include <QDir>
//#include <QMessageBox>
#include <QListIterator>

#include <bits/stdc++.h>

using namespace std;


extern QHash<QString, QStringList> words;
extern QStringList decks_names;
extern QHash < QString, QHash < QString, QString > > decks;
extern QString current_deck;
extern QString current_card;
extern QHash<QString, QHash<QString, QPair <int, int>>> stats;
extern int sgn;


    void on_cards_list_currentTextChanged(const QString &currentText);

    void on_search_line_textChanged(const QString &arg1);

    void on_change_deck_clicked(QString item);

    void on_add_deck_clicked(QString newDeck);

    void on_remove_deck_clicked();

    void on_add_card_clicked(QString newWord, QString newTranslation);

    void on_remov_card_clicked();

    void on_actionQuit_triggered();

    void on_start_practise_clicked();

    void load_cards();
    void updateDeck();
    void play();
    void reset();
    void load_stats();
    void removeDeckStats(QString cd);
    void addWordStats(QString cd, QString cw);
    void removeWordStats(QString cd, QString cw);
    void saveStats();
    void practise();
    void addDeckStats();
#endif // MAINWINDOW2_H
