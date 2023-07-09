#include<iostream>
#include<fstream>

#define deckMax 52

class Deck
{
    int cards[deckMax]; // хранение карт
    int top_; //верхушка колоды
    int bottom_; //дно колоды
    int size_; // текущий размер
public:
    Deck(int size)
    {
        top_ = -1;
        bottom_ = 0;
        size_ = size;
    }
    bool isFull() const;
    bool isEmpty() const;
    int getTop() const;
    int getBottom() const;
    void insertTop(int card);
    void insertBottom(int card);
    void deleteTop();
    void deleteBottom();

    void print();
};

bool Deck::isFull() const
{
    return ((top_ == 0 && bottom_ == size_ - 1) || top_ == bottom_ + 1);
}

bool Deck::isEmpty() const
{
    return (top_ == -1);
}

int Deck::getTop() const
{
    return (isEmpty() || top_ < 0) ? -1 : cards[top_];
}

int Deck::getBottom() const
{
    return (isEmpty() || bottom_ < 0) ? -1 : cards[bottom_];
}

void Deck::insertTop(int card)
{
    if (isFull())
    {
        std::cerr << "top overflow..." << std::endl;
        return;
    }

    if (top_ == -1)
    {
        top_ = 0;
        bottom_ = 0;
    }

    else if (top_ == 0)
    {
        top_ = size_ - 1;
    }

    else
    {
        --top_;
    }

    cards[top_] = card;
}

void Deck::insertBottom(int card)
{
    if (isFull())
    {
        std::cerr << "bottom overflow..." << std::endl;
        return;
    }
    if (top_ == -1)
    {
        top_ = 0;
        bottom_ = 0;
    }
    else if (bottom_ == size_ - 1)
    {
        bottom_ = 0;
    }
    else
    {
        ++bottom_;
    }
    cards[bottom_] = card;
}

void Deck::deleteBottom() {
    if (isEmpty()) {
        std::cerr << "overflow!" << std::endl;
        return;
    }

    if (top_ == bottom_) {
        top_ = -1;
        bottom_ = -1;
    }
    else if (bottom_ == 0)
    {
        bottom_ = size_ - 1;
    }
    else
    {
        --bottom_;
    }
}

void Deck::deleteTop()
{
    if (isEmpty()) {
        std::cout << "Error! Overflow!\n"
            << std::endl;
        return;
    }
    if (top_ == bottom_)
    {
        top_ = -1;
        bottom_ = -1;
    }
    else if (top_ == size_ - 1)
    {
        top_ = 0;
    }
    else
    {
        ++top_;
    }
}

void drunkard(Deck& firstPlayer, Deck& secondPlayer)
{
    int firstPlayerCard;
    int secondPlayerCard;
    int currMove = 0;

    while ((!firstPlayer.isEmpty() && !secondPlayer.isEmpty()) && (currMove < 1000000))
    {
        firstPlayerCard = firstPlayer.getTop();
        firstPlayer.deleteTop();

        secondPlayerCard = secondPlayer.getTop();
        secondPlayer.deleteTop();

        if (firstPlayerCard == secondPlayerCard) // если обе карты равны
        {
            Deck eqFight(52); //очередь для накидывания карт, 52 тк в сумме могут в итоге вывались все карты и получится ничья
            while (firstPlayerCard == secondPlayerCard) // цикл пока они равны
            {

                eqFight.insertTop(firstPlayerCard); // потом достать снизу
                eqFight.insertTop(secondPlayerCard);


                firstPlayerCard = firstPlayer.getTop();
                firstPlayer.deleteTop();

                secondPlayerCard = secondPlayer.getTop();
                secondPlayer.deleteTop();

                if (firstPlayerCard != secondPlayerCard)
                {
                    if ((firstPlayerCard > secondPlayerCard) && secondPlayerCard != 2) //случай, когда у первого игрока карта старше (!= 2 тк у первого игрока может быть туз, а двойка бьет туз)
                    {
                        while (!eqFight.isEmpty())
                        {
                            firstPlayer.insertBottom(eqFight.getBottom());
                            eqFight.deleteBottom();
                        }
                    }

                    else if ((secondPlayerCard > firstPlayerCard) && firstPlayerCard != 2)//случай, когда у второго игрока карта старше (!= 2 тк у второго игрока может быть туз, а двойка бьет туз)
                    {
                        while (!eqFight.isEmpty())
                        {
                            secondPlayer.insertBottom(eqFight.getBottom());
                            eqFight.deleteBottom();
                        }
                    }

                    else if (((firstPlayerCard > secondPlayerCard) || (secondPlayerCard > firstPlayerCard)) && (secondPlayerCard == 2 || firstPlayerCard == 2)) //первый игрок > второго или второй игрок > первого и у одного из игроков карта == 2
                    {
                        if (firstPlayerCard == 14 && secondPlayerCard == 2) //первый игрок - туз, второй - 2 ==> двойка бьет туз ==> передаем карты второму игроку
                        {
                            while (!eqFight.isEmpty())
                            {
                                secondPlayer.insertBottom(eqFight.getBottom());
                                eqFight.deleteBottom();
                            }
                        }

                        else if (secondPlayerCard == 14 && firstPlayerCard == 2) //второй игрок - туз, первый - 2 ==> двойка бьет туз ==> передаем карты первому игроку
                        {
                            while (!eqFight.isEmpty())
                            {
                                firstPlayer.insertBottom(eqFight.getBottom());
                                eqFight.deleteBottom();
                            }
                        }

                        else if (firstPlayerCard > secondPlayerCard) // по классике, как раньше было
                        {
                            while (!eqFight.isEmpty())
                            {
                                firstPlayer.insertBottom(eqFight.getBottom());
                                eqFight.deleteBottom();
                            }
                        }

                        else if (secondPlayerCard > firstPlayerCard) // сейм
                        {
                            while (!eqFight.isEmpty())
                            {
                                secondPlayer.insertBottom(eqFight.getBottom());
                                eqFight.deleteBottom();
                            }
                        }
                    }
                    ++currMove;
                    break;
                }
                if (firstPlayer.isEmpty() || secondPlayer.isEmpty())
                {
                    break;
                }

                ++currMove;
            }
        }

        if ((firstPlayerCard > secondPlayerCard) && secondPlayerCard != 2) // случай, когда у первого игрока карта старше (!= 2 тк у первого игрока может быть туз, а двойка бьет туз)
        {
            firstPlayer.insertBottom(firstPlayerCard);
            firstPlayer.insertBottom(secondPlayerCard);
        }

        else if ((secondPlayerCard > firstPlayerCard) && firstPlayerCard != 2)//случай, когда у второго игрока карта старше (!= 2 тк у второго игрока может быть туз, а двойка бьет туз)
        {
            secondPlayer.insertBottom(firstPlayerCard);
            secondPlayer.insertBottom(secondPlayerCard);
        }

        else if (((firstPlayerCard > secondPlayerCard) || (secondPlayerCard > firstPlayerCard)) && (secondPlayerCard == 2 || firstPlayerCard == 2)) //первый игрок > второго или второй игрок > первого и у одного из игроков карта == 2
        {


            if (firstPlayerCard == 14 && secondPlayerCard == 2) //первый игрок - туз, второй - 2 ==> двойка бьет туз ==> передаем карты второму игроку
            {
                secondPlayer.insertBottom(firstPlayerCard);
                secondPlayer.insertBottom(secondPlayerCard);
            }

            else if (secondPlayerCard == 14 && firstPlayerCard == 2) //второй игрок - туз, первый - 2 ==> двойка бьет туз ==> передаем карты первому игроку
            {
                firstPlayer.insertBottom(firstPlayerCard);
                firstPlayer.insertBottom(secondPlayerCard);
            }

            else if (firstPlayerCard > secondPlayerCard) // по классике, как раньше было
            {
                firstPlayer.insertBottom(firstPlayerCard);
                firstPlayer.insertBottom(secondPlayerCard);
            }

            else if (secondPlayerCard > firstPlayerCard) // сейм
            {
                secondPlayer.insertBottom(firstPlayerCard);
                secondPlayer.insertBottom(secondPlayerCard);
            }
        }

        ++currMove;
    }/*end while(!firstPlayer.isEmpty() && !secondPlayer.isEmpty()) || (currMove > 1000000)*/

    if (firstPlayer.isEmpty() && !secondPlayer.isEmpty())
    {
        std::cout << "second";
    }
    else if (secondPlayer.isEmpty() && !firstPlayer.isEmpty())
    {
        std::cout << "first";
    }
    else if (firstPlayer.isEmpty() && secondPlayer.isEmpty())
    {
        std::cout << "draw";
    }
    else if (currMove > 1000000)
    {
        std::cout << "unknown";
    }
    else
    {
        std::cout << "unknown";
    }

}


int main(int argc, char* argv[])
{
    int allCards[deckMax] = { 0 };
    int index = 0;

    std::ifstream inFile(argv[1]);
    if (!inFile.is_open())
    {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    char line[10];
    while (inFile.getline(line, 10) && index < deckMax)
    {
        char letter = line[0];
        int value = 0;

        if (letter == 'J')
        {
            value = 11;
        }
        else if (letter == 'Q')
        {
            value = 12;
        }
        else if (letter == 'K')
        {
            value = 13;
        }
        else if (letter == 'A')
        {
            value = 14;
        }
        else if (letter >= '2' && letter <= '9') {
            value = letter - '0';
        }
        else if (letter == '1')
        {
            // Handle "10"
            if (line[1] == '0' && line[2] == ' ')
            {
                value = 10;
            }
            else
            {
                std::cerr << "Invalid input: " << line << std::endl;
                continue;
            }
        }
        else
        {
            std::cerr << "Invalid input: " << line << std::endl;
            continue;
        }

        allCards[index] = value;
        ++index;
    }
    inFile.close();

    Deck firstPlayer(52);
    Deck secondPlayer(52);
    int count = 0;
    for (; count < 52; ++count)
    {
        if (count < 26)
        {
            firstPlayer.insertBottom(allCards[count]);
        }
        else
        {
            secondPlayer.insertBottom(allCards[count]);
        }
    }

    drunkard(firstPlayer, secondPlayer);

    return 0;
}