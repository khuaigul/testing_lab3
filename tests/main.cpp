#include <gtest/gtest.h>

#include "test_m.h"

 QHash<QString, QStringList> words;
QStringList decks_names;
 QHash < QString, QHash < QString, QString > > decks;
QString current_deck;
 QString current_card;
 QHash<QString, QHash<QString, QPair <int, int> > > stats;
 int sgn;

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
