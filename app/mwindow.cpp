#include "mwindow.h"

#include <QDebug>
#include <QString>
#include <QTextStream>
//#include <QInputDialog>
#include <QDir>
//#include <QMessageBox>
#include <QListIterator>

void load_cards()
{
    QFile inFile("cards");
    if (!inFile.open(QIODevice::ReadOnly))
    {
        return;
    }
    QTextStream in(&inFile);
    QString line;
    QString deck_name;
    QString word;
    QString translation;
    qint64 id = 0;
    QHash <QString, QString> cur_deck;
    while (!in.atEnd())
    {
        line = in.readLine();
        if (!line.isEmpty() && line[0].isSpace())
        {
            if (!deck_name.isEmpty())
            {
                if (!word.isEmpty())
                {
                    words[deck_name].append(word);
                    cur_deck.insert(word, translation);
                }
                word.clear();
                decks.insert(deck_name, cur_deck);
                cur_deck.clear();
                decks_names.append(deck_name);
            }
            deck_name = line.simplified();
            id = 0;
        }
        else
        {
            if (id == 0)
            {
                if (!word.isEmpty())
                {
                    words[deck_name].append(word);
                    cur_deck.insert(word, translation);
                }
                word = line.simplified();
            }
            else
            {
                translation = line.simplified();
            }
            id++;
            id = id % 2;
        }
    }
    if (!word.isEmpty())
    {
        words[deck_name].append(word);
        cur_deck.insert(word, translation);
    }
    if (!deck_name.isEmpty())
    {
        decks.insert(deck_name, cur_deck);
        decks_names.append(deck_name);
        cur_deck.clear();
    }
    if (!decks_names.empty())
    {
        current_deck = decks_names[0];
    }
//    QHash<QString, QString> db;
//    db.insert("a", "b");
//    decks.insert("c", db);
    inFile.close();
    load_stats();
}

void on_change_deck_clicked(QString item)
{
    if (decks.empty())
    {
        return;
    }
    item = item.simplified();
    if (!item.isEmpty())
    {
        current_deck = item;
        updateDeck();
    }
    current_deck = "Korean";
    //return current_deck;
}

void updateDeck()
{

}

void on_add_deck_clicked(QString newDeck)
{
    QHash<QString, QString> cur;
    cur.clear();
    bool ok = 1;
    //QString newDeck = QInputDialog::getText(this, tr("Add a new deck"), tr("New deck name:"), QLineEdit::Normal, QDir::home().dirName(), &ok);
    newDeck = newDeck.simplified();
    if (ok && !newDeck.isEmpty())
    {
        if (decks.find(newDeck) != decks.end())
        {
//            QMessageBox msg;
//            msg.setText("This name already exists");
//            msg.setStandardButtons(QMessageBox::Ok);
//            int ret = msg.exec();
            return;
        }
        decks.insert(newDeck, cur);
        current_deck = newDeck;
        decks_names.append(newDeck);
        updateDeck();
    }
    addDeckStats();
}

void on_remove_deck_clicked()
{
    if (current_deck.isEmpty())
        return;

            QHash<QString, QHash<QString, QString>>::iterator i = decks.begin();
            while (i != decks.end())
            {
                if (i.key() == current_deck)
                {
                    decks.erase(i);
                    break;
                }
                i++;
            }
            QHash<QString, QStringList>::iterator j = words.begin();
            while (j != words.end())
            {
                if (j.key() == current_deck)
                {
                    words.erase(j);
                    break;
                }
                j++;
            }
            decks_names.removeAll(current_deck);
            removeDeckStats(current_deck);
            current_deck.clear();
            if(!decks_names.isEmpty())
                current_deck = decks_names[0];
            updateDeck();
}

void on_add_card_clicked(QString newWord, QString newTranslation)
{
    if (current_deck.isEmpty())
    {
        qDebug() << "empty";
        return;
    }
    bool ok = 1;
    //QString newWord = QInputDialog::getText(this, tr("Add a new card"), tr("Enter a word:"), QLineEdit::Normal, QDir::home().dirName(), &ok);
    newWord = newWord.simplified();
    if (ok && !newWord.isEmpty())
    {
        if(decks[current_deck].find(newWord) != decks[current_deck].end())
        {
//            QMessageBox msg;
//            msg.setText("This word already exists");
//            msg.setStandardButtons(QMessageBox::Ok);
//            int ret = msg.exec();
            return;
        }
        bool ok1 = 1;
        //QString newTranslation = QInputDialog::getText(this, tr("Add a new card"), tr("Enter a translation:"), QLineEdit::Normal, QDir::home().dirName(), &ok1);
        newTranslation = newTranslation.simplified();
        if (ok1 && !newTranslation.isEmpty())
        {
            decks[current_deck].insert(newWord, newTranslation);
            words[current_deck].append(newWord);
            updateDeck();
        }
        else if (newTranslation.isEmpty())
        {
            return;
        }
    }
    addWordStats(current_deck, newWord);
}


void on_remov_card_clicked()
{
    if (current_card.isEmpty())
        return;
            QHash<QString, QString>::iterator it = decks[current_deck].begin();
            while (it != decks[current_deck].end())
            {
                if (it.key() == current_card)
                {
                    decks[current_deck].erase(it);
                    break;
                }
                it++;
            }
            removeWordStats(current_deck, current_card);
            words[current_deck].removeAll(current_card);
            current_card.clear();
            updateDeck();
}

void on_actionQuit_triggered()
{
            QFile outFile("cards");
            if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text))
                return;
            QTextStream out(&outFile);
            QHash<QString, QHash<QString, QString>>::iterator i = decks.begin();
            while (i != decks.end())
            {
                out << " " + i.key() + "\n";
                current_deck = i.key();
                QHash<QString, QString>::iterator j = decks[current_deck].begin();
                while (j != decks[current_deck].end())
                {
                    out << j.key() + "\n" + *j + "\n";
                    j++;
                }
                i++;
            }
            saveStats();
            outFile.close();
}
void load_stats()
{
    QFile inFile("stats");
    if (!inFile.open(QIODevice::ReadOnly))
    {
        return;
    }
    QTextStream in(&inFile);
    QString line;
    QString deck_name;
    QString word;
    int trueAns;
    int allAns;
    QHash<QString, QPair<int, int>> cur;
    while (!in.atEnd())
    {
        line = in.readLine();
        if (!line.isEmpty() && line[0].isSpace())
        {
            if (!deck_name.isEmpty())
            {
                if (!word.isEmpty())
                {
                    cur.insert(word, qMakePair(trueAns, allAns));
                }
                word.clear();
                stats.insert(deck_name, cur);
                cur.clear();
            }
            deck_name = line.simplified();
        }
        else if (!line.isEmpty())
        {
            in >> trueAns >> allAns;
            if (!word.isEmpty())
            {
                cur.insert(word, qMakePair(trueAns, allAns));
            }
            word = line.simplified();
        }
    }
    if (!word.isEmpty())
    {
        cur.insert(word, qMakePair(trueAns, allAns));
    }
    if (!deck_name.isEmpty())
    {
        word.clear();
        stats.insert(deck_name, cur);
        cur.clear();
    }
}


void removeDeckStats(QString cd)
{
    QHash<QString, QHash<QString, QPair <int, int>>>::iterator it = stats.begin();
    while (it != stats.end())
    {
        if (it.key() == cd)
        {
            stats.erase(it);
            break;
        }
        it++;
    }
}

void addWordStats(QString cd, QString cw)
{
    QHash<QString, QHash<QString, QPair <int, int>>>::iterator it = stats.begin();
    while (it != stats.end())
    {
        if (it.key() == cd)
        {
            stats[it.key()].insert(cw, qMakePair(0, 0));
            break;
        }
        it++;
    }
}

void removeWordStats(QString cd, QString cw)
{
    QHash<QString, QHash<QString, QPair <int, int>>>::iterator it = stats.begin();
    while (it != stats.end())
    {
        if (it.key() == cd)
        {
            QHash<QString, QPair <int, int>>::iterator i = stats[it.key()].begin();
            while (i != stats[it.key()].end())
            {
                if (i.key() == cw)
                {
                    stats[it.key()].erase(i);
                    break;
                }
            }
            break;
        }
        it++;
    }
}

void addDeckStats()
{
    QHash<QString, QPair<int, int>> cur_stats;
    stats.insert(current_deck, cur_stats);
}

void saveStats()
{
    QFile outFile("stats");
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&outFile);
    QHash<QString, QHash<QString, QPair <int, int>>>::iterator it = stats.begin();
    while (it != stats.end())
    {
        out << " " << it.key()  << "\n";
        QHash<QString, QPair <int, int>>::iterator i = stats[it.key()].begin();
        while (i != stats[it.key()].end())
        {
            out << i.key() << "\n" << stats[it.key()][i.key()].first << " " << stats[it.key()][i.key()].second << "\n";
            i++;
        }
        it++;
    }
}

