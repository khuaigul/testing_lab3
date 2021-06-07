#ifndef TEST_M_H
#define TEST_M_H
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <string.h>
//#include "text.h"
//#include "_text.h"

#include "mwindow.h"

using namespace std;

//TEST(a, b)
//{
//    sgn = 0;
//    int ex = on_change_deck_clicked("English");
//    ASSERT_EQ(ex, 0);
//}


TEST(changeDeck, isDeck)
{
    QHash<QString, QString> cur;
    cur.insert("apple", "яблоко");
    cur.insert("open", "открыть");
    cur.insert("pen", "ручка");
    decks.insert("English", cur);
    cur.clear();
    cur.insert("봄", "весна");
    decks.insert("Korean", cur);
    current_deck = "English";
    on_change_deck_clicked("Korean");
    int id = 0;
    if (current_deck == QString("Korean"))
        id = 1;
    QString ex = "Korean";
    ASSERT_EQ(current_deck, ex);

}
TEST(changeDeck, noDeck)
{
    decks.clear();
    current_deck = "";
    on_change_deck_clicked("Korean");
    ASSERT_EQ(current_deck, "");
}
TEST(addDeck, newName)
{
    QHash<QString, QString> cur;
    QHash<QString, QHash<QString, QString> > ex;
    cur.insert("apple", "яблоко");
    cur.insert("open", "открыть");
    cur.insert("pen", "ручка");
    decks.insert("English", cur);
    cur.clear();
    cur.insert("봄", "весна");
    decks.insert("Korean", cur);
    ex = decks;
    current_deck = "English";
    on_add_deck_clicked("Spanish");
    cur.clear();
    ex.insert(QString("Spanish"), cur);
    ASSERT_EQ(decks, ex);
    ASSERT_EQ(current_deck, "Spanish");
}
TEST(addDeck, isDeck)
{
    QHash<QString, QString> cur;
    QHash<QString, QHash<QString, QString> > ex;
    cur.insert("apple", "яблоко");
    cur.insert("open", "открыть");
    cur.insert("pen", "ручка");
    decks.insert("English", cur);
    cur.clear();
    cur.insert("봄", "весна");
    decks.insert("Korean", cur);
    ex = decks;
    current_deck = "English";
    on_add_deck_clicked("English");
    cur.clear();
    ASSERT_EQ(decks, ex);
    ASSERT_EQ(current_deck, "English");
}
TEST(removeDeck, isDeck)
{
    QHash<QString, QString> cur;
    QHash<QString, QHash<QString, QString> > ex;
    cur.insert("apple", "яблоко");
    cur.insert("open", "открыть");
    cur.insert("pen", "ручка");
    decks.insert("English", cur);
    cur.clear();
    cur.insert("봄", "весна");
    decks.insert("Korean", cur);
    ex.insert("Korean", cur);
    current_deck = "English";
    cur.clear();
    QHash<QString, QHash<QString, QString> >::iterator e = ex.begin();
    while (e != ex.end())
    {
        if (e.key() == QString("English"))
        {
            ex[e.key()].clear();
            ex.erase(e);
            break;
        }
        e++;
    }
    int id = 0;
    on_remove_deck_clicked();
    if (decks["English"].empty())
        id = 1;
    ASSERT_EQ(id, 1);
    ASSERT_EQ(current_deck, QString("Spanish"));

}
TEST(removeDeck, noDeck)
{
    QHash<QString, QString> cur;
    QHash<QString, QHash<QString, QString> > ex;
    cur.insert("apple", "яблоко");
    cur.insert("open", "открыть");
    cur.insert("pen", "ручка");
    decks.insert("English", cur);
    cur.clear();
    cur.insert("봄", "весна");
    decks.insert("Korean", cur);
    ex.insert("Korean", cur);
    current_deck = "";
    cur.clear();
    ex = decks;
    int id = 0;
    on_remove_deck_clicked();
    ASSERT_EQ(current_deck, QString(""));
}
TEST(addCard, newCard)
{
    QHash<QString, QString> cur;
    QHash<QString, QHash<QString, QString> > ex;
    cur.insert("apple", "яблоко");
    cur.insert("open", "открыть");
    cur.insert("pen", "ручка");
    decks.insert("English", cur);
    cur.clear();
    cur.insert("봄", "весна");
    decks.insert("Korean", cur);
    ex.insert("Korean", cur);
    current_deck = "";
    cur.clear();
    ex = decks;
    ex["English"].insert("rain", "дождь");
    current_deck = "English";
    on_add_card_clicked("rain", "дождь");
    ASSERT_EQ(decks, ex);
}
TEST(addCard, emptyWord)
{
    QHash<QString, QString> cur;
    QHash<QString, QHash<QString, QString> > ex;
    cur.insert("apple", "яблоко");
    cur.insert("open", "открыть");
    cur.insert("pen", "ручка");
    decks.insert("English", cur);
    cur.clear();
    cur.insert("봄", "весна");
    decks.insert("Korean", cur);
    ex.insert("Korean", cur);
    current_deck = "";
    cur.clear();
    ex = decks;
    current_deck = "English";
    on_add_card_clicked(" ", "дождь");
    ASSERT_EQ(decks, ex);
}
TEST(addCard, existingWord)
{
    QHash<QString, QString> cur;
    QHash<QString, QHash<QString, QString> > ex;
    cur.insert("apple", "яблоко");
    cur.insert("open", "открыть");
    cur.insert("pen", "ручка");
    decks.insert("English", cur);
    cur.clear();
    cur.insert("봄", "весна");
    decks.insert("Korean", cur);
    ex.insert("Korean", cur);
    current_deck = "";
    cur.clear();
    ex = decks;
    current_deck = "English";
    on_add_card_clicked("apple", "яблоко");
    ASSERT_EQ(decks, ex);
}
TEST(addCard, emptyTranslate)
{
    QHash<QString, QString> cur;
    QHash<QString, QHash<QString, QString> > ex;
    cur.insert("apple", "яблоко");
    cur.insert("open", "открыть");
    cur.insert("pen", "ручка");
    decks.insert("English", cur);
    cur.clear();
    cur.insert("봄", "весна");
    decks.insert("Korean", cur);
    ex.insert("Korean", cur);
    current_deck = "";
    cur.clear();
    ex = decks;
    current_deck = "English";
    on_add_card_clicked("rain", "  ");
    ASSERT_EQ(decks, ex);
}
TEST(addCard, noDeck)
{
    QHash<QString, QString> cur;
    QHash<QString, QHash<QString, QString> > ex;
    cur.insert("apple", "яблоко");
    cur.insert("open", "открыть");
    cur.insert("pen", "ручка");
    decks.insert("English", cur);
    cur.clear();
    cur.insert("봄", "весна");
    decks.insert("Korean", cur);
    ex.insert("Korean", cur);
    current_deck = "";
    cur.clear();
    ex = decks;
    current_deck = "";
    on_add_card_clicked("apple", "яблоко");
    ASSERT_EQ(decks, ex);
}
TEST(removeCard, isCard)
{
    QHash<QString, QString> cur;
    QHash<QString, QHash<QString, QString> > ex;
    cur.insert("apple", "яблоко");
    cur.insert("open", "открыть");
    ex.insert("English", cur);
    cur.insert("pen", "ручка");
    decks.insert("English", cur);
    cur.clear();
    cur.insert("봄", "весна");
    decks.insert("Korean", cur);
    ex.insert("Korean", cur);
    current_deck = "English";
    current_card = "pen";
    cur.clear();
    int id = 0;
    on_remov_card_clicked();
    if (decks["English"]["pen"].isEmpty())
        id = 1;
    ASSERT_EQ(id, 1);
    ASSERT_EQ(current_card, QString(""));
}
TEST(removeCard, onlyCard)
{
    QHash<QString, QString> cur;
    QHash<QString, QHash<QString, QString> > ex;
    cur.insert("apple", "яблоко");
    cur.insert("open", "открыть");
    cur.insert("pen", "ручка");
    decks.insert("English", cur);
    cur.clear();
    cur.insert("봄", "весна");
    decks.insert("Korean", cur);
    ex.insert("Korean", cur);
    current_deck = "Korean";
    current_card = "봄";
    cur.clear();
    int id = 0;
    on_remov_card_clicked();
    if (decks["Korean"]["봄"].isEmpty())
        id = 1;
    ASSERT_EQ(id, 1);
    ASSERT_EQ(current_card, QString(""));
}
TEST(removeCard, noCard)
{
    QHash<QString, QString> cur;
    QHash<QString, QHash<QString, QString> > ex;
    cur.insert("apple", "яблоко");
    cur.insert("open", "открыть");
    ex.insert("English", cur);
    cur.insert("pen", "ручка");
    decks.insert("English", cur);
    cur.clear();
    cur.insert("봄", "весна");
    decks.insert("Korean", cur);
    ex.insert("Korean", cur);
    current_deck = "English";
    current_card = "";
    cur.clear();
    ex = decks;
    int id = 0;
    on_remov_card_clicked();
    ASSERT_EQ(decks, ex);
    ASSERT_EQ(current_card, QString(""));
}

#endif // TEST_M_H
