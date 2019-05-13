#ifndef COUNTER_H
#define COUNTER_H


class Counter
{
    public:
        Counter();
        const Counter& operator++();
        char getStarState() const;
        char getEndState() const;
    private:
        char startState;
        char endState;
};

#endif // COUNTER_H
